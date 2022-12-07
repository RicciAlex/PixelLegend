//=============================================================================
//
// tutorial.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "tutorial.h"
#include "bg.h"
#include "object2D.h"
#include "fireballPlayer.h"
#include "application.h"
#include "inputKeyboard.h"
#include "Letter.h"

//コンストラクタ
CTutorial::CTutorial()
{
	m_nCntAnim = 0;
	
	m_pBg = nullptr;
	m_pPlayer = nullptr;
	m_pButton = nullptr;
	m_pTarget = nullptr;
}

//デストラクタ
CTutorial::~CTutorial()
{

}

//初期化処理
HRESULT CTutorial::Init(void)
{
	m_nCntAnim = 0;

	m_pBg = nullptr;
	m_pPlayer = nullptr;
	m_pButton = nullptr;
	m_pTarget = nullptr;

	return S_OK;
}

//終了処理
void CTutorial::Uninit(void)
{
	if (m_pBg != nullptr)
	{
		m_pBg->Release();
		m_pBg = nullptr;
	}
	if (m_pPlayer != nullptr)
	{
		m_pPlayer->Release();
		m_pPlayer = nullptr;
	}
	if (m_pButton != nullptr)
	{
		m_pButton->Release();
		m_pButton = nullptr;
	}
	if (m_pTarget != nullptr)
	{
		m_pTarget->Release();
		m_pTarget = nullptr;
	}
}

//更新処理
void CTutorial::Update(void)
{
	if (m_pPlayer != nullptr)
	{
		D3DXVECTOR3 pos = m_pPlayer->GetPos() + D3DXVECTOR3(-150.0f, 0.0f, 0.0f);

		m_nCntAnim++;

		if (m_nCntAnim == 120)
		{
			m_pPlayer->SetMove(D3DXVECTOR3(2.0f, 0.0f, 0.0f));
			
			if (m_pButton == nullptr)
			{
				m_pButton = CObject_2D::Create();

				if (m_pButton != nullptr)
				{
					m_pButton->SetPos(pos);
					m_pButton->SetSize(D3DXVECTOR2(20.0f, 53.0f));
					m_pButton->SetStartingRot(D3DX_PI * 0.5f);
					m_pButton->SetTexture(CObject::TextureIconD);
					m_pButton->SetTextureParameter(2, 2, 1, 30);
				}
			}
		}
		else if (m_nCntAnim == 240)
		{
			m_pPlayer->SetMove(D3DXVECTOR3(-2.0f, 0.0f, 0.0f));

			if (m_pButton != nullptr)
			{
				m_pButton->SetTexture(CObject::TextureIconA);
			}
		}
		else if (m_nCntAnim == 360)
		{
			m_pPlayer->SetMove(D3DXVECTOR3(0.0f, -2.0f, 0.0f));

			if (m_pButton != nullptr)
			{
				m_pButton->SetTexture(CObject::TextureIconW);
			}
		}
		else if (m_nCntAnim == 480)
		{
			m_pPlayer->SetMove(D3DXVECTOR3(.0f, 2.0f, 0.0f));

			if (m_pButton != nullptr)
			{
				m_pButton->SetTexture(CObject::TextureIconS);
			}
		}
		else if (m_nCntAnim == 600)
		{
			m_pPlayer->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

			if (m_pButton != nullptr)
			{
				m_pButton->SetTexture(CObject::TextureIconMouse);
				m_pButton->SetSize(D3DXVECTOR2(20.0f, 28.7f));
				m_pButton->SetTextureParameter(1, 2, 1, INT_MAX);
				m_pButton->SetAnimPattern(1);

				if (m_pTarget != nullptr)
				{
					m_pButton->SetPos(m_pTarget->GetPos() + D3DXVECTOR3(-50.0f, -20.0f, 0.0f));
					m_pButton->SetRevolution(m_pPlayer->GetPos(), D3DX_PI * 0.01f, 140.0f);
					m_pTarget->SetRevolution(m_pPlayer->GetPos(), D3DX_PI * 0.01f, 200.0f);
					m_pTarget->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				}
			}
		}
		else if (m_nCntAnim >= 720 && m_nCntAnim <= 1020 && m_nCntAnim % 20 == 0)
		{
			if (m_pButton != nullptr)
			{
				m_pButton->SetAnimPattern(0);
			}
			if (m_pTarget != nullptr)
			{
				D3DXVECTOR3 target = m_pTarget->GetPos();

				target -= m_pPlayer->GetPos();
				D3DXVec3Normalize(&target, &target);

				D3DXVECTOR3 P = m_pPlayer->GetPos();

				CFireballPlayer::Create(P + D3DXVECTOR3(35.0f, -3.0f, 0.0f), D3DXVECTOR3(10.0f * target.x, 10.0f * target.y, 0.0f),
					D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(16.0f, 16.0f));
				CFireballPlayer* pBullet = CFireballPlayer::Create(P + D3DXVECTOR3(35.0f, -3.0f, 0.0f), D3DXVECTOR3(10.0f * target.x, 10.0f * target.y, 0.0f),
					D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(16.0f, 16.0f));
				pBullet->SetStartingAngle(D3DX_PI);
			}
		}
		else if (m_nCntAnim > 1020 && m_nCntAnim < 1200)
		{
			if (m_pButton != nullptr)
			{
				m_pButton->SetRevolution(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f);
				m_pButton->SetAnimPattern(1);
			}
			if (m_pTarget != nullptr)
			{
				m_pTarget->SetRevolution(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f);
			}
		}
		else if (m_nCntAnim >= 1200)
		{
			CApplication::SetFade(CApplication::Mode_Title);
		}

		if (CInputKeyboard::GetKeyboardTrigger(DIK_SPACE))
		{
			CApplication::SetFade(CApplication::Mode_Title);
		}

		if (m_pButton != nullptr)
		{
			m_pButton->SetPos(pos);
		}
	}
}





//生成処理
CTutorial* CTutorial::Create(void)
{
	CTutorial* pMode = new CTutorial;

	if (FAILED(pMode->Init()))
	{
		return nullptr;
	}

	pMode->m_pBg = CBg::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));

	if (pMode->m_pBg != nullptr)
	{
		pMode->m_pBg->SetTexture(CObject::TextureSlothBg);
		pMode->m_pBg->SetTextureParameter(1, 1, 1, INT_MAX);
		pMode->m_pBg->SetPriority(1);
	}

	pMode->m_pPlayer = CObject_2D::Create();

	if (pMode->m_pPlayer != nullptr)
	{
		pMode->m_pPlayer->SetPos(D3DXVECTOR3(650.0f, 360.0f, 0.0f));
		pMode->m_pPlayer->SetSize(D3DXVECTOR2(50.0f, 50.0f));
		pMode->m_pPlayer->SetStartingRot(D3DX_PI * 0.5f);
		pMode->m_pPlayer->SetTexture(CObject::TextureDragon);
		pMode->m_pPlayer->SetTextureParameter(2, 2, 3, 16);
	}

	pMode->m_pTarget = CObject_2D::Create();

	if (pMode->m_pTarget != nullptr)
	{
		pMode->m_pTarget->SetPos(D3DXVECTOR3(850.0f, 360.0f, 0.0f));
		pMode->m_pTarget->SetSize(D3DXVECTOR2(40.0f, 40.0f));
		pMode->m_pTarget->SetTexture(CObject::TextureTarget);
		pMode->m_pTarget->SetTextureParameter(1, 1, 1, INT_MAX);
		pMode->m_pTarget->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}

	CObject_2D* pObj = CObject_2D::Create();

	if (pObj != nullptr)
	{
		pObj->SetPos(D3DXVECTOR3(250.0f, 600.0f, 0.0f));
		pObj->SetSize(D3DXVECTOR2(50.0f, 42.0f));
		pObj->SetStartingRot(D3DX_PI * 0.5f);
		pObj->SetTexture(CObject::TexturePressSpaceIcon);
		pObj->SetTextureParameter(2, 2, 1, 30);
	}

	char* aStr = "end tutorial";
	int nLenght = strlen(aStr);

	for (int nCnt = 0; nCnt < nLenght; nCnt++)
	{
		CLetter* pLetter = CLetter::Create(D3DXVECTOR3(250.0f + 100.0f + 20.0f * nCnt, 600.0f + 35.0f, 0.0f), D3DXVECTOR2(10.0f, 10.0f), aStr[nCnt]);

		if (pLetter != nullptr)
		{
			pLetter->SetColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		}
	}


	return pMode;
}