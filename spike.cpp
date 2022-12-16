//=============================================================================
//
// spike.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "spike.h"
#include "squareHitbox.h"

//コンストラクタ
CSpike::CSpike()
{
	//メンバー変数をクリアする
	m_pHitbox = nullptr;
}

//デストラクタ
CSpike::~CSpike()
{

}

//初期化処理
HRESULT CSpike::Init(void)
{
	if (FAILED(CBullet::Init()))
	{//基本クラスの初期化処理
		return -1;
	}

	//メンバー変数を初期化する
	m_pHitbox = nullptr;

	return S_OK;
}

//終了処理
void CSpike::Uninit(void)
{
	//ヒットボックスの破棄処理
	if (m_pHitbox != nullptr)
	{//nullチェック
		m_pHitbox->Release();			//メモリを解放する
		m_pHitbox = nullptr;			//ポインタをnullにする
	}

	//基本クラスの終了処理
	CBullet::Uninit();
}

//更新処理
void CSpike::Update(void)
{
	//ヒットボックスの更新処理
	if (m_pHitbox != nullptr)
	{//nullチェック

		m_pHitbox->SetPos(GetPos());		//ヒットボックスの位置の更新
		
		if (m_pHitbox->Hit())
		{//何かと当たったら

			Release();			//破棄する
			return;				
		}
	}

	//速度と加速を取得して、比べて、速度の向きが逆になったら、消す
	D3DXVECTOR3 move, acc;
	move = GetMove();
	acc = GetAcceleration();

	if (move.x * acc.x > 0 || move.y * acc.y > 0)
	{
		Release();
		return;
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
CSpike* CSpike::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move)
{
	CSpike* pBullet = new CSpike;			//インスタンスを生成する

	if (FAILED(pBullet->Init()))
	{//初期化処理
		return nullptr;
	}

	pBullet->SetPos(pos);								//位置の設定
	pBullet->SetMove(move);								//速度の設定
	pBullet->SetSize(D3DXVECTOR2(10.0f, 13.7f));		//サイズの設定
	pBullet->SetTexture(CObject::TextureSpike);			//テクスチャの設定
	pBullet->SetTextureParameter(1, 1, 1, INT_MAX);		//テクスチャパラメータの設定
	pBullet->SetStartingRot(D3DX_PI * 0.5f);			//向きの初期値の設定
	
	//加速を計算して、設定する
	D3DXVECTOR3 acc;

	D3DXVec3Normalize(&acc, &move);

	float fLenght = D3DXVec3Length(&move);
	fLenght *= -0.01f;

	acc.x *= fLenght;
	acc.y *= fLenght;

	pBullet->SetAcceleration(acc);

	//ヒットボックスの生成
	pBullet->m_pHitbox = CSquareHitbox::Create(pos, D3DXVECTOR2(9.0f, 12.0f), CHitbox::Type_EnemyBullet);

	return pBullet;					//生成したインスタンスを返す
}