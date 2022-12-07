//=============================================================================
//
// gluttony.cpp
// Author : Ricci Alex
//
//=============================================================================

//インクルードファイル
#include "gluttony.h"
#include "squareHitbox.h"
#include "maw.h"
#include "backMaw.h"
#include "heart.h"
#include "application.h"

//コンストラクタ
CGluttony::CGluttony()
{
	m_pHitbox = nullptr;

	for (int nCnt = 0; nCnt < MaxMaw; nCnt++)
	{
		m_pMaw[nCnt] = nullptr;
	}

	m_nCntState = 0;
	m_nTargetFrame = 0;
	m_nPhase = 0;

	m_pBackMaw = nullptr;
	m_pHeart = nullptr;
}

//デストラクタ
CGluttony::~CGluttony()
{

}

//初期化処理
HRESULT CGluttony::Init(void)
{
	m_pHitbox = nullptr;

	for (int nCnt = 0; nCnt < MaxMaw; nCnt++)
	{
		m_pMaw[nCnt] = nullptr;
	}

	m_nCntState = 0;
	m_nTargetFrame = 0;
	m_nPhase = 0;

	m_pBackMaw = nullptr;
	m_pHeart = nullptr;

	return S_OK;
}

//終了処理
void CGluttony::Uninit(void)
{
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}

	for (int nCnt = 0; nCnt < MaxMaw; nCnt++)
	{
		if (m_pMaw[nCnt] != nullptr)
		{
			m_pMaw[nCnt]->Release();
			m_pMaw[nCnt] = nullptr;
		}
	}

	if (m_pBackMaw != nullptr)
	{
		m_pBackMaw->Release();
		m_pBackMaw = nullptr;
	}
	if (m_pHeart != nullptr)
	{
		m_pHeart->Release();
		m_pHeart = nullptr;
	}
}

//更新処理
void CGluttony::Update(void)
{
	m_nCntState++;

	if (m_pHeart != nullptr)
	{
		if (m_pHeart->GetLife() <= 6250 && m_nPhase == 0)
		{
			m_nPhase++;
		}
		
		if (m_pHeart->GetEnd())
		{
			CApplication::SetFade(CApplication::Mode_Result);
		}
	}

	if (m_nCntState % 1000 == 999)
	{
		if (m_nPhase == 0)
		{
			int nIdx = CObject::random(0, 2);

			if (m_pMaw[nIdx] != nullptr)
			{
				m_pMaw[nIdx]->Open();
			}
		}
		else
		{
			if (m_pBackMaw != nullptr)
			{
				m_pBackMaw->SetState(CBackMaw::state_awake);
			}
		}

		if (m_nCntState >= m_nTargetFrame)
		{
			m_nCntState = 0;
			m_nTargetFrame = CObject::random(3, 5) * 1000;

			if (m_pHeart != nullptr)
			{
				m_pHeart->SetActive();
			}
		}
	}
}

const bool CGluttony::GetEnd(void)
{
	if (m_pHeart != nullptr)
	{
		return m_pHeart->GetEnd();
	}

	return false;
}




//生成処理
CGluttony* CGluttony::Create(void)
{
	CGluttony* pEnemy = new CGluttony;

	if (pEnemy == nullptr)
	{
		return nullptr;
	}

	pEnemy->m_pBackMaw = CBackMaw::Create();
	pEnemy->m_pMaw[0] = CMaw::Create(CMaw::left);
	pEnemy->m_pMaw[1] = CMaw::Create(CMaw::down);
	pEnemy->m_pMaw[2] = CMaw::Create(CMaw::right);
	pEnemy->m_pHeart = CHeart::Create();
	pEnemy->m_nCntState = 700;
	pEnemy->m_nTargetFrame = CObject::random(1, 3) * 1000;

	return pEnemy;
}