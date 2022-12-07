//=============================================================================
//
// skullFireball.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "skullFireball.h"
#include "circleHitbox.h"

//コンストラクタ
CSkullFireball::CSkullFireball()
{
	//メンバー変数をクリアする
	m_pHitbox = nullptr;
}

//デストラクタ
CSkullFireball::~CSkullFireball()
{

}

//初期化処理
HRESULT CSkullFireball::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CBullet::Init()))
	{
		return -1;
	}

	return S_OK;
}

//終了処理
void CSkullFireball::Uninit(void)
{
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}

	//基本クラスの終了処理
	CBullet::Uninit();
}

//更新処理
void CSkullFireball::Update(void)
{
	m_pHitbox->SetPos(GetPos());

	if (m_pHitbox->Hit())
	{//プレイヤーと当たった場合、弾を消す
		Release();
		return;
	}

	//基本クラスの更新処理
	CBullet::Update();
}


//=============================================================================
//静的関数
//=============================================================================

//生成処理
CSkullFireball* CSkullFireball::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CSkullFireball* pBullet = new CSkullFireball;			//新しい弾を生成する

	//初期化処理
	if (FAILED(pBullet->Init()))
	{
		return nullptr;
	}

	pBullet->SetPos(pos);									//位置の設定
	pBullet->SetMove(move);									//速度の設定

	pBullet->SetBulletType(BULLET_SKULL_FIREBALL);			//弾の種類の設定
	pBullet->SetTexture(CObject::TextureSkullFireball);		//テクスチャの設定
	pBullet->SetTextureParameter(1, 1, 1, INT_MAX);			//テクスチャパラメータの設定処理
	pBullet->SetSize(D3DXVECTOR2(15.0f, 15.0f));			//サイズの設定
	pBullet->SetRotation(-D3DX_PI * 0.025f);				//回転速度の設定

	pBullet->m_pHitbox = CCircleHitbox::Create(pos, 12.0f, CHitbox::Type_EnemyBullet);

	return pBullet;
} 