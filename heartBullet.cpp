//=============================================================================
//
// heartBullet.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "heartBullet.h"
#include "heartEffect.h"

//コンストラクタ
CHeartBullet::CHeartBullet()
{
	//メンバー変数をクリアする
	for (int nCnt = 0; nCnt < MaxEffect; nCnt++)
	{
		m_pEffect[nCnt] = nullptr;
	}
}

//デストラクタ
CHeartBullet::~CHeartBullet()
{
	
}

//初期化処理
HRESULT CHeartBullet::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CBullet::Init()))
	{
		return -1;
	}

	//ポインタをnullにする
	for (int nCnt = 0; nCnt < MaxEffect; nCnt++)
	{
		if (m_pEffect[nCnt] != nullptr)
		{
			m_pEffect[nCnt]->Release();
			m_pEffect[nCnt] = nullptr;
		}
	}

	return S_OK;
}

//終了処理
void CHeartBullet::Uninit(void)
{
	//基本クラスの終了処理
	CBullet::Uninit();

	//エフェクトの破棄
	for (int nCnt = 0; nCnt < MaxEffect; nCnt++)
	{
		if (m_pEffect[nCnt] != nullptr)
		{//nullチェック
			m_pEffect[nCnt]->Release();			//メモリを解放する
			m_pEffect[nCnt] = nullptr;			//ポインタをnullにする
		}
	}
}

//更新処理
void CHeartBullet::Update(void)
{
	//基本クラスの更新処理
	CObject_2D::Update();

	D3DXVECTOR3 pos = GetPos();		//位置の取得処理

	//エフェクトの更新処理
	for (int nCnt = 0; nCnt < 40; nCnt++)
	{
		if (m_pEffect[nCnt] != nullptr)
		{//nullチェック

			if (m_pEffect[nCnt]->GetActiveState())
			{//まだあったら
				m_pEffect[nCnt]->SetCenterPos(pos);		//中心点の更新
			}
			else
			{//何かと当たったら、消す

				m_pEffect[nCnt]->Release();
				m_pEffect[nCnt] = nullptr;
			}
		}
	}

	int nLife = GetLife() - 1;		//体力の更新

	if (nLife <= 0)
	{//体力が0以下になったら、消す
		Release();
		return;
	}
	else
	{//体力が0より大きかったら

		SetLife(nLife);				//体力の設定
	}

	if (pos.x <= -50.0f || pos.y <= -50.0f || pos.x >= (float)SCREEN_WIDTH + 50.0f || pos.y >= (float)SCREEN_HEIGHT + 50.0f)
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
CHeartBullet* CHeartBullet::Create(const D3DXVECTOR3 CenterPos, const D3DXVECTOR3 move, const D3DXCOLOR col)
{
	CHeartBullet* pBullet = new CHeartBullet;		//弾を生成する

	//基本クラスの初期化処理
	if (FAILED(pBullet->Init()))
	{
		return nullptr;
	}

	pBullet->SetPos(CenterPos);			//位置の設定
	pBullet->SetMove(move);				//速度の設定

	//エフェクトの生成
	for (int nCnt = 0; nCnt < 40; nCnt++)
	{
		pBullet->m_pEffect[nCnt] = CHeartEffect::Create(CenterPos, D3DX_PI * 0.05f * nCnt, D3DX_PI, col, D3DXVECTOR2(10.0f, 10.0f), 480);
	}

	return pBullet;						//弾を返す
} 