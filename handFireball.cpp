//=============================================================================
//
// handFireball.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "handFireball.h"
#include "circleHitbox.h"

//コンストラクタ
CHandFireball::CHandFireball()
{
	//メンバー変数をクリアする
	m_fChange = 0.0f;
	m_Rot = false;

	m_pHitbox = nullptr;
}

//デストラクタ
CHandFireball::~CHandFireball()
{

}

//初期化処理
HRESULT CHandFireball::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CBullet::Init()))
	{
		return -1;
	}

	//メンバー変数を初期化する
	m_fChange = 0.0f;
	m_Rot = false;

	m_pHitbox = nullptr;

	return S_OK;
}

//終了処理
void CHandFireball::Uninit(void)
{
	//ヒットボックスの破棄
	if (m_pHitbox != nullptr)
	{//nullチェック
		m_pHitbox->Release();		//メモリを解放する
		m_pHitbox = nullptr;		//ポインタをnullにする
	}

	//基本クラスの終了処理
	CBullet::Uninit();
}

//更新処理
void CHandFireball::Update(void)
{
	//基本クラスの更新処理
	CObject_2D::Update();

	D3DXVECTOR3 pos = GetPos();		//位置の取得
	D3DXVECTOR3 move = GetMove();	//速度の取得

	if (pos.x >= m_fChange && move.x >= 0.0f || pos.x <= m_fChange && move.x <= 0.0f)
	{//目的の位置を超えたら、次の目的の位置を設定して、向きを変える
		if (move.x >= 0.0f)
		{
			m_fChange += 100.0f;
		}
		else
		{
			m_fChange -= 100.0f;
		}
		
		move.y *= -1.0f;

		SetMove(move);

		if (!m_Rot)
		{
			float fRot = GetRot() + D3DX_PI * 0.5f;
			SetStartingRot(fRot);
			m_Rot = true;
		}
		else
		{
			float fRot = GetRot() - D3DX_PI * 0.5f;
			SetStartingRot(fRot);
			m_Rot = false;
		}
	}

	//ヒットボックスの更新処理
	if (m_pHitbox != nullptr)
	{//nullチェック

		m_pHitbox->SetPos(GetPos());		//ヒットボックスの位置の更新

		if (m_pHitbox->Hit())
		{//何かと当たったら、消す
			Release();
			return;
		}
	}

	if (pos.x <= -100.0f || pos.x >= 1380.0f)
	{//画面を出たら、消す
		Release();
		return;
	}
}


//=============================================================================
//
//								静的関数
//
//=============================================================================


//生成処理
CHandFireball* CHandFireball::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CHandFireball* pBullet = new CHandFireball;		//インスタンスを生成する

	if (FAILED(pBullet->Init()))
	{//初期化処理
		return nullptr;
	}

	pBullet->SetPos(pos);									//位置の設定
	pBullet->SetSize(D3DXVECTOR2(25.0f, 25.0f));			//サイズの設定
	pBullet->SetMove(move);									//速度の設定
	pBullet->SetTexture(CObject::TextureHandFireball);		//テクスチャの設定
	pBullet->SetTextureParameter(1, 1, 1, INT_MAX);			//テクスチャパラメータの設定
	pBullet->m_fChange = 100.0f;							//目的の位置の設定

	//必要だったら、テクスチャを反転する
	if (move.x < 0.0)
	{
		pBullet->FlipX();

		pBullet->m_Rot = true;
		pBullet->m_fChange = (float)SCREEN_WIDTH - 100.0f;

		pBullet->SetStartingRot(D3DX_PI);
	}

	//ヒットボックスの生成
	pBullet->m_pHitbox = CCircleHitbox::Create(pos, 20.0f, CHitbox::Type_EnemyBullet);

	return pBullet;				//生成したインスタンスを返す
}