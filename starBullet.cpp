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
	{
		return -1;
	}

	for (int nCnt = 0; nCnt < MaxEffect; nCnt++)
	{
		m_pEffect[nCnt] = nullptr;
	}

	return S_OK;
}

//終了処理
void CStarBullet::Uninit(void)
{
	for (int nCnt = 0; nCnt < MaxEffect; nCnt++)
	{
		if (m_pEffect[nCnt] != nullptr)
		{
			m_pEffect[nCnt]->Release();
			m_pEffect[nCnt] = nullptr;
		}
	}

	CBullet::Uninit();
}

//更新処理
void CStarBullet::Update(void)
{
	for (int nCnt = 0; nCnt < MaxEffect; nCnt++)
	{
		if (m_pEffect[nCnt] != nullptr)
		{
			if (m_pEffect[nCnt]->GetActiveState())
			{
				m_pEffect[nCnt]->SetCenterPos(GetPos());
			}
			else
			{
				m_pEffect[nCnt]->Release();
				m_pEffect[nCnt] = nullptr;
			}
		}
	}

	CBullet::Update();
}



//生成処理
CStarBullet* CStarBullet::Create(const D3DXVECTOR3 CenterPos, const D3DXVECTOR3 move)
{
	CStarBullet* pBullet = new CStarBullet;

	if (FAILED(pBullet->Init()))
	{
		return nullptr;
	}

	pBullet->SetPos(CenterPos);
	pBullet->SetMove(move);
	pBullet->SetLife(240);

	for (int nCnt = 0; nCnt < pBullet->MaxEffect; nCnt++)
	{
		pBullet->m_pEffect[nCnt] = CStarEffect::Create(CenterPos, 6.0f * nCnt * D3DX_PI / 80.0f, 18.0f * D3DX_PI / 40.0f, D3DXCOLOR(1.0f, 1.0f, 0.015f, 0.75f), D3DXVECTOR2(4.0f, 4.0f), 240);
	}

	return pBullet;
}