//=============================================================================
//
// title.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "title.h"
#include "bg.h"
#include "inputKeyboard.h"
#include "inputMouse.h"
#include "application.h"
#include "button.h"
#include "sound.h"
#include "skullCursor.h"
#include "Letter.h"


D3DXCOLOR CTitle::targetColors[CTitle::TargetCol_Max] = 
{
	{1.0f, 0.0f, 0.0f, 1.0f},
	{0.0f, 1.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f, 1.0f},
	{1.0f, 1.0f, 0.0f, 1.0f},
	{1.0f, 0.0f, 1.0f, 1.0f},
	{0.0f, 1.0f, 1.0f, 1.0f}
};

//コンストラクタ
CTitle::CTitle()
{
	m_pBg = nullptr;

	for (int nCnt = 0; nCnt < button_max; nCnt++)
	{
		m_pButton[nCnt] = nullptr;
	}
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_pCursor[nCnt] = nullptr;
	}
	for (int nCnt = 0; nCnt < 16; nCnt++)
	{
		m_pTitle[nCnt] = nullptr;
	}

	m_TargetCol = TargetCol_Red;
	m_changeCol = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_nChangeFrame = 0;


	//m_pTitleMenu = nullptr;
}

//デストラクタ
CTitle::~CTitle()
{

}

//初期化処理
HRESULT CTitle::Init(void)
{
	m_pBg = nullptr;

	for (int nCnt = 0; nCnt < button_max; nCnt++)
	{
		m_pButton[nCnt] = nullptr;
	}
	for (int nCnt = 0; nCnt < 16; nCnt++)
	{
		m_pTitle[nCnt] = nullptr;
	}

	m_TargetCol = TargetCol_Red;
	m_changeCol = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_nChangeFrame = 0;

	return S_OK;
}

//終了処理
void CTitle::Uninit(void)
{
	if (m_pBg != nullptr)
	{
		m_pBg->Release();
		m_pBg = nullptr;
	}

	for (int nCnt = 0; nCnt < button_max; nCnt++)
	{
		if (m_pButton[nCnt] != nullptr)
		{
			m_pButton[nCnt]->Uninit();
			m_pButton[nCnt] = nullptr;
		}
	}
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pCursor[nCnt] != nullptr)
		{
			m_pCursor[nCnt]->Uninit();
			m_pCursor[nCnt] = nullptr;
		}
	}
	for (int nCnt = 0; nCnt < 16; nCnt++)
	{
		if (m_pTitle[nCnt] != nullptr)
		{
			m_pTitle[nCnt]->Release();
			m_pTitle[nCnt] = nullptr;
		}
	}
}

//更新処理
void CTitle::Update(void)
{
	UpdateTitleColor();

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pCursor[nCnt] != nullptr)
		{
			m_pCursor[nCnt]->Update();
		}
	}

		if (m_pButton[button_play] != nullptr)
		{
			m_pButton[button_play]->Update();

			if (m_pButton[button_play]->GetTriggerState())
			{
				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_CLICK);

				//CApplication::SetMode(CApplication::Mode_StageSelection);
				CApplication::SetFade(CApplication::Mode_StageSelection);
				return;
			}
		}
		if (m_pButton[button_tutorial] != nullptr)
		{
			m_pButton[button_tutorial]->Update();

			if (m_pButton[button_tutorial]->GetTriggerState())
			{
				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_CLICK);

				CApplication::SetFade(CApplication::Mode_Tutorial);
				return;
			}
		}
		if (m_pButton[button_leaderboard] != nullptr)
		{
			m_pButton[button_leaderboard]->Update();

			if (m_pButton[button_leaderboard]->GetTriggerState())
			{
				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_CLICK);

				//CApplication::SetMode(CApplication::Mode_Ranking);
				CApplication::SetFade(CApplication::Mode_Ranking);
				return;
			}
		}

	/*if (CInputKeyboard::GetKeyboardTrigger(DIK_RETURN))
	{
		CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_CLICK);

		CApplication::SetMode(CApplication::Mode_StageSelection);
	}*/
}



//生成処理
CTitle* CTitle::Create(void)
{
	CTitle* pTitle = new CTitle;

	if (FAILED(pTitle->Init()))
	{
		return nullptr;
	}

	pTitle->m_pBg = CBg::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	pTitle->m_pBg->SetTexture(CObject::TextureMenuBg);
	pTitle->m_pBg->SetTextureParameter(1, 1, 1, INT_MAX);
	pTitle->m_pBg->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	pTitle->m_pCursor[0] = CSkullCursor::Create(D3DXVECTOR3(0.0f, (float)SCREEN_HEIGHT * 0.5f, 0.0f));
	pTitle->m_pCursor[1] = CSkullCursor::Create(D3DXVECTOR3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT * 0.5f, 0.0f));

	char aStr[16] = "pixel legend";

	int Lenght = strlen(aStr);

	for (int nCnt = 0; nCnt < Lenght; nCnt++)
	{
		pTitle->m_pTitle[nCnt] = CLetter::Create(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f - 75.0f * (Lenght * 0.5f) + (80.0f * nCnt), (float)SCREEN_HEIGHT * 0.25f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), aStr[nCnt]);
		
		if (pTitle->m_pTitle[nCnt] != nullptr)
		{
			pTitle->m_pTitle[nCnt]->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			pTitle->m_pTitle[nCnt]->SetPriority(2);
		}
	}

	pTitle->m_TargetCol = TargetCol_Yellow;

	char aText[button_max][24] = { { "play" }, { "tutorial" },{ "leaderboard" } };

	for (int nCnt = 0; nCnt < button_max; nCnt++)
	{
		pTitle->m_pButton[nCnt] = CButton::Create(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f + 50.0f * 2.5f * nCnt, 0.0f), D3DXVECTOR2(300.0f, 55.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), aText[nCnt]);
	}

	//pTitle->m_pTitleMenu = CTitleMenu::Create(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR2(500.0f, 350.0f), D3DXVECTOR2(350.0f, 50.0f));


	return pTitle;
}


void CTitle::UpdateTitleColor(void)
{
	m_nChangeFrame--;

	if (m_nChangeFrame <= 0)
	{
		m_nChangeFrame = 120;

		int nRand = -1;

		/*while (1)
		{
			nRand = CObject::random(0, TargetCol_Max);

			if ((TargetCol)nRand != m_TargetCol)
			{
				break;
			}
		}*/

		switch (m_TargetCol)
		{
		case CTitle::TargetCol_Red:

			m_TargetCol = TargetCol_Yellow;

			break;

		case CTitle::TargetCol_Green:

			m_TargetCol = TargetCol_Cyan;

			break;

		case CTitle::TargetCol_Blue:

			m_TargetCol = TargetCol_Magenta;

			break;

		case CTitle::TargetCol_Yellow:

			m_TargetCol = TargetCol_Green;

			break;

		case CTitle::TargetCol_Magenta:

			m_TargetCol = TargetCol_Red;

			break;

		case CTitle::TargetCol_Cyan:

			m_TargetCol = TargetCol_Blue;

			break;
		
		default:
			break;
		}

		//m_TargetCol = (TargetCol)nRand;
		m_changeCol = targetColors[m_TargetCol] - m_pTitle[0]->GetColor();
		m_changeCol.r /= 120.0f;
		m_changeCol.g /= 120.0f;
		m_changeCol.b /= 120.0f;
		m_changeCol.a = 0.0f;
	}
	else
	{
		D3DXCOLOR col = m_pTitle[0]->GetColor();

		col += m_changeCol;

		for (int nCnt = 0; nCnt < 16; nCnt++)
		{
			if (m_pTitle[nCnt] != nullptr)
			{
				m_pTitle[nCnt]->SetColor(col);
			}
		}
	}

}