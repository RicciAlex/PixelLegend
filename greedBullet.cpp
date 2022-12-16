//=============================================================================
//
// greedBullet.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "greedBullet.h"
#include "circleHitbox.h"

//コンストラクタ
CGreedBullet::CGreedBullet()
{
	//メンバー変数をクリアする
	m_pHitbox = nullptr;
}

//デストラクタ
CGreedBullet::~CGreedBullet()
{

}

//初期化処理
HRESULT CGreedBullet::Init(void)
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
void CGreedBullet::Uninit(void)
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
void CGreedBullet::Update(void)
{
	//基本クラスの更新処理
	CObject_2D::Update();

	//体力の更新
	int nLife = GetLife();
	nLife--;

	if (nLife <= 0)
	{//体力が0以下になったら、消す
		Release();
		return;
	}

	D3DXVECTOR3 pos = GetPos();		//位置の取得

	if (pos.y >= 850.0f || pos.x <= -400.0f || pos.x >= 1700.0f)
	{//画面を出たら、消す
		Release();
		return;
	}

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
CGreedBullet* CGreedBullet::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move)
{
	CGreedBullet* pBullet = new CGreedBullet;		//インスタンスを生成する

	if (FAILED(pBullet->Init()))
	{//初期化処理
		return nullptr;
	}

	pBullet->SetPos(pos);							//位置の設定
	pBullet->SetMove(move);							//速度の設定
	pBullet->SetSize(D3DXVECTOR2(13.0f, 13.0f));	//サイズの設定
	pBullet->SetRotation((float)random(-100, 100) * 0.001f * D3DX_PI);		//回転させる
	pBullet->SetLife(800);							//体力の設定

	//ランダムでテクスチャを設定する
	int nRand = random(1, 10);

	if (nRand == 1)
	{//10%は宝石
		pBullet->SetTexture(CObject::TextureJewel);
		pBullet->SetTextureParameter(1, 3, 2, INT_MAX);
		pBullet->SetAnimPattern(random(0, 5));
	}
	else
	{//90%はコイン
		pBullet->SetTexture(CObject::TextureCoin);
		pBullet->SetTextureParameter(1, 3, 2, INT_MAX);
		pBullet->SetAnimPattern(random(0, 5));
	}

	//ヒットボックスの生成
	pBullet->m_pHitbox = CCircleHitbox::Create(pos, 17.0f, CHitbox::Type_EnemyBullet);

	return pBullet;				//生成したインスタンスを返す
}

//生成処理
CGreedBullet* CGreedBullet::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const D3DXVECTOR3 acc)
{
	CGreedBullet* pBullet = new CGreedBullet;			//インスタンスを生成する

	if (FAILED(pBullet->Init()))
	{//初期化処理
		return nullptr;
	}

	pBullet->SetPos(pos);							//位置の設定
	pBullet->SetMove(move);							//速度の設定
	pBullet->SetAcceleration(acc);					//加速の設定
	pBullet->SetSize(D3DXVECTOR2(13.0f, 13.0f));	//サイズの設定
	pBullet->SetRotation((float)random(-100, 100) * 0.001f * D3DX_PI);		//回転させる
	pBullet->SetLife(800);							//体力の設定

	//ランダムでテクスチャを設定する
	int nRand = random(1, 10);

	if (nRand == 1)
	{//10%は宝石
		pBullet->SetTexture(CObject::TextureJewel);
		pBullet->SetTextureParameter(1, 3, 2, INT_MAX);
		pBullet->SetAnimPattern(random(0, 5));
	}
	else
	{//90%はコイン
		pBullet->SetTexture(CObject::TextureCoin);
		pBullet->SetTextureParameter(1, 3, 2, INT_MAX);
		pBullet->SetAnimPattern(random(0, 5));
	}

	//ヒットボックスの生成
	pBullet->m_pHitbox = CCircleHitbox::Create(pos, 17.0f, CHitbox::Type_EnemyBullet);

	return pBullet;			//生成したインスタンスを返す
}