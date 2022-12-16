//=============================================================================
//
// handBlade.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "handBlade.h"
#include "circleHitbox.h"

//コンストラクタ
CHandBlade::CHandBlade()
{
	//メンバー変数をクリアする
	m_pHitbox = nullptr;
}

//デストラクタ
CHandBlade::~CHandBlade()
{

}

//初期化処理
HRESULT CHandBlade::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CBullet::Init()))
	{
		return -1;
	}

	//メンバー変数を初期化する
	m_pHitbox = nullptr;

	return S_OK;
}

//終了処理
void CHandBlade::Uninit(void)
{
	//ヒットボックスの破棄
	if (m_pHitbox != nullptr)
	{//nullチェック
		m_pHitbox->Release();			//メモリを解放する
		m_pHitbox = nullptr;			//ポインタをnullにする
	}

	//基本クラスの終了処理
	CBullet::Uninit();
}

//更新処理
void CHandBlade::Update(void)
{
	//基本クラスの更新処理
	CObject_2D::Update();

	D3DXVECTOR3 pos, move;
	pos = GetPos();				//位置の取得
	move = GetMove();			//速度の取得

	//外面を出る前、反射させる
	if (pos.y + move.y <= 0.0f || pos.y + move.y >= (float)SCREEN_HEIGHT)
	{
		move.y *= -1.0f;
		SetMove(move);
	}
	if (pos.x <= 0.0f || pos.x >= (float)SCREEN_WIDTH)
	{
		Release();
		return;
	}

	//位置の更新
	int nLife = GetLife() - 1;

	if (nLife <= 0)
	{//体力が0以下になったら、消す
		Release();
		return;
	}
	
	SetLife(nLife);			//体力の設定

	//ヒットボックスの更新処理
	if (m_pHitbox != nullptr)
	{//nullチェック

		m_pHitbox->SetPos(pos);		//ヒットボックスの位置の更新

		if (m_pHitbox->Hit())
		{//何かと当たったら、消す
			Release();
			return;
		}
	}
}




//=============================================================================
//
//								静的関数
//
//=============================================================================



//生成処理
CHandBlade* CHandBlade::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CHandBlade* pBullet = new CHandBlade;		//インスタンスを生成する

	if (FAILED(pBullet->Init()))
	{//初期化処理
		return nullptr;
	}

	pBullet->SetPos(pos);							//位置の設定
	pBullet->SetMove(move);							//速度の設定
	pBullet->SetSize(D3DXVECTOR2(20.0f, 20.0f));	//サイズの設定
	pBullet->SetRotation(-D3DX_PI * 0.025f);		//向きの初期値の設定
	pBullet->SetTexture(CObject::TextureHandBlade);	//テクスチャの設定
	pBullet->SetTextureParameter(1, 1, 1, INT_MAX);	//テクスチャパラメータの設定
	pBullet->SetLife(300);							//体力の設定

	//ヒットボックスの生成
	pBullet->m_pHitbox = CCircleHitbox::Create(pos, 20.0f, CHitbox::Type_EnemyBullet);

	return pBullet;					//生成したインスタンスを返す
}