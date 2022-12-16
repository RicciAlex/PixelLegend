//=============================================================================
//
// spikeBomb.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "spikeBomb.h"
#include "circleHitbox.h"
#include "spike.h"

//コンストラクタ
CSpikeBomb::CSpikeBomb()
{
	//メンバー変数をクリアする
	m_pHitbox = nullptr;
}

//デストラクタ
CSpikeBomb::~CSpikeBomb()
{

}

//初期化処理
HRESULT CSpikeBomb::Init(void)
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
void CSpikeBomb::Uninit(void)
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
void CSpikeBomb::Update(void)
{
	//ヒットボックスの更新処理
	if (m_pHitbox != nullptr)
	{//nullチェック

		m_pHitbox->SetPos(GetPos());			//ヒットボックスの位置の設定

		if (m_pHitbox->Hit())
		{//当たった状態だったら

			//トゲ型の弾を4つ生成して、向きの初期値を設定する
			CSpike* pBullet = CSpike::Create(GetPos(), D3DXVECTOR3(0.0f, -1.0f, 0.0f));
			pBullet = CSpike::Create(GetPos(), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
			pBullet->SetStartingRot(-D3DX_PI * 0.5f);
			pBullet = CSpike::Create(GetPos(), D3DXVECTOR3(-1.0f, 0.0f, 0.0f));
			pBullet->SetStartingRot(D3DX_PI);
			pBullet = CSpike::Create(GetPos(), D3DXVECTOR3(1.0f, 0.0f, 0.0f));
			pBullet->SetStartingRot(0.0f);

			Release();							//破棄する
			return;
		}
	}

	int nLife = GetLife();		//体力の取得
	nLife--;					//体力の更新

	if (nLife <= 0)
	{//体力が0以下になったら

		//トゲ型の弾を4つ生成して、向きの初期値を設定する
		CSpike* pBullet = CSpike::Create(GetPos(), D3DXVECTOR3(0.0f, -1.0f, 0.0f));
		pBullet = CSpike::Create(GetPos(), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
		pBullet->SetStartingRot(-D3DX_PI * 0.5f);
		pBullet = CSpike::Create(GetPos(), D3DXVECTOR3(-1.0f, 0.0f, 0.0f));
		pBullet->SetStartingRot(D3DX_PI);
		pBullet = CSpike::Create(GetPos(), D3DXVECTOR3(1.0f, 0.0f, 0.0f));
		pBullet->SetStartingRot(0.0f);

		Release();				//破棄する
		return;
	}
	else
	{//体力が0以上だったら

		SetLife(nLife);			//体力の設定
	}

	CBullet::Update();			//基本クラスの更新処理
}


//=============================================================================
//
//								静的関数
//
//=============================================================================


//生成処理
CSpikeBomb* CSpikeBomb::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CSpikeBomb* pBullet = new CSpikeBomb;		//インスタンスを生成する

	if (FAILED(pBullet->Init()))
	{//初期化処理
		return nullptr;
	}

	pBullet->SetPos(pos);									//位置の設定
	pBullet->SetSize(D3DXVECTOR2(20.0f, 20.0f));			//サイズの設定
	pBullet->SetMove(move);									//速度の設定
	pBullet->SetRotation(-D3DX_PI * 0.05f);					//向きの初期値の設定
	pBullet->SetTexture(CObject::TextureSpikeBomb);			//テクスチャの設定
	pBullet->SetTextureParameter(1, 1, 1, INT_MAX);			//テクスチャパラメータの設定
	pBullet->SetLife(90);									//体力の設定

	//ヒットボックスの設定
	pBullet->m_pHitbox = CCircleHitbox::Create(pos, 10.0f, CHitbox::Type_EnemyBullet);

	return pBullet;				//生成したインスタンスを返す
}