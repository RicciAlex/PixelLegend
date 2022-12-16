//=============================================================================
//
// starBullet.cpp
// Author : Ricci Alex
//
//=============================================================================

//インクルードファイル
#include "starBullet.h"
#include "starEffect.h"

//コンストラクタ
CStarBullet::CStarBullet()
{
	//メンバー変数をクリアする
	for (int nCnt = 0; nCnt < MaxEffect; nCnt++)
	{
		m_pEffect[nCnt] = nullptr;
	}
}

//デストラクタ
CStarBullet::~CStarBullet()
{

}

//初期化処理
HRESULT CStarBullet::Init(void)
{
	if (FAILED(CBullet::Init()))
	{//基本クラスの初期化処理
		return -1;
	}

	//メンバー変数を初期化する

	for (int nCnt = 0; nCnt < MaxEffect; nCnt++)
	{
		m_pEffect[nCnt] = nullptr;
	}

	return S_OK;
}

//終了処理
void CStarBullet::Uninit(void)
{
	//エフェクトの破棄処理
	for (int nCnt = 0; nCnt < MaxEffect; nCnt++)
	{
		if (m_pEffect[nCnt] != nullptr)
		{//nullチェック
			m_pEffect[nCnt]->Release();			//メモリを解放する
			m_pEffect[nCnt] = nullptr;			//ポインタをnullにする
		}
	}

	//基本クラスの終了処理
	CBullet::Uninit();
}

//更新処理
void CStarBullet::Update(void)
{
	//エフェクトの更新処理
	for (int nCnt = 0; nCnt < MaxEffect; nCnt++)
	{
		if (m_pEffect[nCnt] != nullptr)
		{//nullチェック

			if (m_pEffect[nCnt]->GetActiveState())
			{//まだあったら

				m_pEffect[nCnt]->SetCenterPos(GetPos());			//中心点の設定
			}
			else
			{//何かと当たったら

				m_pEffect[nCnt]->Release();							//エフェクトを破棄する
				m_pEffect[nCnt] = nullptr;							//ポインタをnullにする
			}
		}
	}

	CBullet::Update();				//基本クラスの更新処理
}



//生成処理
CStarBullet* CStarBullet::Create(const D3DXVECTOR3 CenterPos, const D3DXVECTOR3 move)
{
	CStarBullet* pBullet = new CStarBullet;			//インスタンスを生成する

	if (FAILED(pBullet->Init()))
	{//初期化処理
		return nullptr;
	}

	pBullet->SetPos(CenterPos);						//中心点の設定
	pBullet->SetMove(move);							//速度の設定
	pBullet->SetLife(240);							//体力の設定

	//エフェクトの生成
	for (int nCnt = 0; nCnt < pBullet->MaxEffect; nCnt++)
	{
		pBullet->m_pEffect[nCnt] = CStarEffect::Create(CenterPos, 6.0f * nCnt * D3DX_PI / 80.0f, 18.0f * D3DX_PI / 40.0f, D3DXCOLOR(1.0f, 1.0f, 0.015f, 0.75f), D3DXVECTOR2(4.0f, 4.0f), 240);
	}

	return pBullet;					//生成したインスタンスを返す
}