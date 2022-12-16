//=============================================================================
//
// scythe.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "Scythe.h"
#include "circleHitbox.h"

//コンストラクタ
CScythe::CScythe()
{
	//メンバー変数をクリアする
	fCntSize = 0.0f;

	m_pHitbox = nullptr;
}

//デストラクタ
CScythe::~CScythe()
{

}

//初期化処理
HRESULT CScythe::Init(void)
{
	if (FAILED(CBullet::Init()))
	{//基本クラスの初期化処理
		return -1;
	}

	//メンバー変数を初期化する
	fCntSize = 0.0f;

	m_pHitbox = nullptr;

	return S_OK;
}

//終了処理
void CScythe::Uninit(void)
{
	//ヒットボックスの破棄処理
	if (m_pHitbox != nullptr)
	{//nullチェック
		m_pHitbox->Release();		//メモリを解放する
		m_pHitbox = nullptr;		//ポインタをnullにする
	}

	//基本クラスの終了処理
	CBullet::Uninit();
}

//更新処理
void CScythe::Update(void)
{
	//ヒットボックスの更新処理
	if (m_pHitbox != nullptr)
	{//nullチェック

		m_pHitbox->SetPos(GetPos());	//ヒットボックスの位置の更新

		if (m_pHitbox->Hit())
		{//何かと当たったら、消す
			Release();
			return;
		}
	}
	
	//基本クラスの更新処理
	CBullet::Update();
}


//=============================================================================
//
//								静的関数
//
//=============================================================================


//生成処理
CScythe* CScythe::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CScythe* pBullet = new CScythe;			//インスタンスを生成する

	if (FAILED(pBullet->Init()))
	{//初期化処理
		return nullptr;
	}

	pBullet->SetPos(pos);								//位置の設定
	pBullet->SetMove(move);								//速度の設定
	pBullet->SetSize(D3DXVECTOR2(45.0f, 45.0f));		//サイズの設定
	pBullet->SetTexture(CObject::TextureScythe);		//テクスチャの設定
	pBullet->SetTextureParameter(1, 1, 1, INT_MAX);		//テクスチャパラメータの設定
	pBullet->SetRotation(D3DX_PI * 0.05f);				//向きの初期値の設定
	pBullet->FlipX();									//テクスチャを反転する

	//ヒットボックスの生成処理
	pBullet->m_pHitbox = CCircleHitbox::Create(pos, 25.0f, CHitbox::Type_EnemyBullet);

	return pBullet;				//生成したインスタンスを返す
}