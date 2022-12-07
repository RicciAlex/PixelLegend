//=============================================================================
//
// gamePride.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "gamePride.h"
#include "pride.h"
#include "player.h"
#include "inputKeyboard.h"
#include "inputMouse.h"
#include "bg.h"
#include "button.h"
#include "application.h"
#include "object2D.h"
#include "object.h"
#include "sound.h"
#include "target.h"

//コンストラクタ
CGamePride::CGamePride()
{
	m_bPause = false;

	m_pBg = nullptr;
	m_pPlayer = nullptr;
	m_pEnemy = nullptr;

	m_pMenuBg = nullptr;

	for (int nCnt = 0; nCnt < button_max; nCnt++)
	{
		m_pButton[nCnt] = nullptr;
	}

	for (int nCnt = 0; nCnt < Max_Obj; nCnt++)
	{
		m_pBalloon[nCnt] = nullptr;
	}

	m_nBalloonNumber = 0;
	m_nCntAnim = 0;
}

//デストラクタ
CGamePride::~CGamePride()
{

}

//初期化処理
HRESULT CGamePride::Init(void)
{
	m_bPause = false;

	m_pBg = nullptr;
	m_pPlayer = nullptr;
	m_pEnemy = nullptr;

	m_pMenuBg = nullptr;

	for (int nCnt = 0; nCnt < button_max; nCnt++)
	{
		m_pButton[nCnt] = nullptr;
	}

	for (int nCnt = 0; nCnt < Max_Obj; nCnt++)
	{
		m_pBalloon[nCnt] = nullptr;
	}

	m_nBalloonNumber = 0;
	m_nCntAnim = 0;

	CTarget::Create();

	return S_OK;
}

//終了処理
void CGamePride::Uninit(void)
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

	if (m_pEnemy != nullptr)
	{
		m_pEnemy->Release();
		m_pEnemy = nullptr;
	}

	if (m_pMenuBg != nullptr)
	{
		m_pMenuBg->Release();
		m_pMenuBg = nullptr;
	}

	for (int nCnt = 0; nCnt < button_max; nCnt++)
	{
		if (m_pButton[nCnt] != nullptr)
		{
			m_pButton[nCnt]->Uninit();
			m_pButton[nCnt] = nullptr;
		}
	}

	for (int nCnt = 0; nCnt < Max_Obj; nCnt++)
	{
		if (m_pBalloon[nCnt] != nullptr)
		{
			m_pBalloon[nCnt]->Release();
			m_pBalloon[nCnt] = nullptr;
		}
	}
}

//更新処理
void CGamePride::Update(void)
{
	m_nCntAnim++;

	if (m_nCntAnim % 300 == 30)
	{
		if (m_nBalloonNumber <= Max_Obj)
		{
			for (int nCnt = 0; nCnt < Max_Obj; nCnt++)
			{
				if (m_pBalloon[nCnt] == nullptr)
				{
					m_pBalloon[nCnt] = CObject_2D::Create();

					if (m_pBalloon[nCnt] != nullptr)
					{
						m_pBalloon[nCnt]->SetPos(D3DXVECTOR3((float)CObject::random(50, 1080), (float)SCREEN_HEIGHT + 100.0f, 0.0f));
						m_pBalloon[nCnt]->SetSize(D3DXVECTOR2(15.0f, 25.0f));
						m_pBalloon[nCnt]->SetTexture(CObject::TextureBalloon);
						m_pBalloon[nCnt]->SetTextureParameter(1, 1, 1, INT_MAX);
						m_pBalloon[nCnt]->SetMove(D3DXVECTOR3(0.5f, -2.0f, 0.0f));
						m_pBalloon[nCnt]->SetStartingRot(D3DX_PI * 0.5f);
						m_pBalloon[nCnt]->SetPriority(1);
						m_nBalloonNumber++;

						D3DXCOLOR col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

						switch (CObject::random(0,5))
						{
						case 0:
							col = D3DXCOLOR(0.75f, 0.0f, 0.0f, 1.0f);
							break;
						case 1:
							col = D3DXCOLOR(0.0f, 0.75f, 0.0f, 1.0f);
							break;
						case 2:
							col = D3DXCOLOR(0.0f, 0.0f, 0.75f, 1.0f);
							break;
						case 3:
							col = D3DXCOLOR(0.75f, 0.75f, 0.0f, 1.0f);
							break;
						case 4:
							col = D3DXCOLOR(0.75f, 0.0f, 0.75f, 1.0f);
							break;
						case 5:
							col = D3DXCOLOR(0.0f, 0.75f, 0.75f, 1.0f);
							break;
						default:
							break;
						}

						m_pBalloon[nCnt]->SetColor(col);

						break;
					}
				}
			}
		}
	}

	if (m_nBalloonNumber > 0)
	{
		for (int nCnt = 0; nCnt < Max_Obj; nCnt++)
		{
			if (m_pBalloon[nCnt] != nullptr)
			{
				D3DXVECTOR3 pos = m_pBalloon[nCnt]->GetPos();

				if (pos.x >= (float)SCREEN_WIDTH + 20.0f || pos.y <= -30.0f)
				{
					m_pBalloon[nCnt]->Release();
					m_pBalloon[nCnt] = nullptr;
					m_nBalloonNumber--;
				}
			}
		}
	}

	if (m_pEnemy != nullptr)
	{
		if (m_pEnemy->GetEnd())
		{
			if (m_pPlayer != nullptr)
			{
				CApplication::SetRemainingLife(m_pPlayer->GetLife());
			}

			//CApplication::SetMode(CApplication::Mode_Result);		
			CApplication::SetFade(CApplication::Mode_Result);
		}
		else
		{
			UpdateMenu();
		}
	}

	if (m_pPlayer != nullptr)
	{
		if (m_pPlayer->GetEnd())
		{
			CApplication::SetFade(CApplication::Mode_Result);					//フェードの設定処理
		}
	}
}





//生成処理
CGamePride* CGamePride::Create(void)
{
	CGamePride* pGame = new CGamePride;

	if (FAILED(pGame->Init()))
	{
		return nullptr;
	}

	pGame->m_pBg = CBg::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, -0.0f));

	if (pGame->m_pBg != nullptr)
	{
		pGame->m_pBg->SetTexture(CObject::TexturePrideBg);
		pGame->m_pBg->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		pGame->m_pBg->SetTextureParameter(1, 1, 1, INT_MAX);
	}

	pGame->m_pPlayer = CPlayer::Create();

	if (pGame->m_pPlayer != nullptr)
	{
		pGame->m_pPlayer->SetPos(D3DXVECTOR3(300.0f, (float)SCREEN_HEIGHT * 0.5f, 0.0f));
	}

	pGame->m_pEnemy = CPride::Create();

	return pGame;
}




void CGamePride::UpdateMenu(void)
{
	if (CInputKeyboard::GetKeyboardTrigger(DIK_RETURN))
	{//エンターキーを押したら
		if (m_bPause)
		{//ポーズ状態だったら
			m_bPause = false;			//普通状態にする

			for (int nCnt = 0; nCnt < button_max; nCnt++)
			{
				if (m_pButton[nCnt] != nullptr)
				{
					m_pButton[nCnt]->Uninit();
					m_pButton[nCnt] = nullptr;
				}
			}
			if (m_pMenuBg != nullptr)
			{
				m_pMenuBg->Release();
				m_pMenuBg = nullptr;
			}

			CObject::SetPause(false);
		}
		else
		{//普通状態だったら、ポーズメニューを生成して、ポーズ状態にする

			m_pMenuBg = CBg::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
			m_pMenuBg->SetTexture(CObject::TextureMenuBg);
			m_pMenuBg->SetTextureParameter(1, 1, 1, INT_MAX);
			m_pMenuBg->SetSize(D3DXVECTOR2(250.0f, 150.0f));
			m_pMenuBg->SetPos(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, 360.0f, 0.0f));
			m_pMenuBg->SetPriority(5);
			m_pMenuBg->Update();

			char aText[button_max][24] = { { "continue" },{ "quit" } };

			for (int nCnt = 0; nCnt < button_max; nCnt++)
			{
				m_pButton[nCnt] = CButton::Create(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, 300.0f + 60.0f * 2.0f * nCnt, 0.0f), D3DXVECTOR2(55.0f, 55.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), aText[nCnt]);
			}

			CObject::SetPause(true);

			m_bPause = true;
		}
	}

	if (m_bPause)
	{//ポーズ状態だったら
		for (int nCnt = 0; nCnt < button_max; nCnt++)
		{//ボタンの更新処理
			if (m_pButton[nCnt] != nullptr)
			{
				m_pButton[nCnt]->Update();

				if (m_pButton[nCnt]->GetTriggerState())
				{
					CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_CLICK);

					switch (nCnt)
					{
					case button_continue:

					{
						m_bPause = false;

						for (int nCnt2 = 0; nCnt2 < button_max; nCnt2++)
						{
							if (m_pButton[nCnt2] != nullptr)
							{
								m_pButton[nCnt2]->Uninit();
								m_pButton[nCnt2] = nullptr;
							}
						}

						if (m_pMenuBg != nullptr)
						{
							m_pMenuBg->Release();
							m_pMenuBg = nullptr;
						}

						CObject::SetPause(false);
					}

					break;

					case button_quit:

					{
						m_bPause = false;
						CObject::SetPause(false);
						CApplication::SetFade(CApplication::Mode_Title);
						return;
					}

					break;

					default:
						break;
					}
				}
			}
		}
	}
}