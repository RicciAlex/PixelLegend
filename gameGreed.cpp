//=============================================================================
//
// gameGreed.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "gameGreed.h"
#include "application.h"
#include "greed.h"
#include "player.h"
#include "inputKeyboard.h"
#include "bg.h"
#include "button.h"
#include "sound.h"
#include "target.h"

//コンストラクタ
CGameGreed::CGameGreed()
{
	//メンバー変数をクリアする
	m_bPause = false;

	m_pBg = nullptr;
	m_pPlayer = nullptr;
	m_pEnemy = nullptr;

	m_pMenuBg = nullptr;

	for (int nCnt = 0; nCnt < button_max; nCnt++)
	{
		m_pButton[nCnt] = nullptr;
	}
}

//デストラクタ
CGameGreed::~CGameGreed()
{

}

//初期化処理
HRESULT CGameGreed::Init(void)
{
	//メンバー変数の初期化
	m_bPause = false;

	m_pBg = nullptr;
	m_pPlayer = nullptr;
	m_pEnemy = nullptr;
	//m_pMenu = nullptr;

	m_pMenuBg = nullptr;

	CTarget::Create();

	for (int nCnt = 0; nCnt < button_max; nCnt++)
	{
		m_pButton[nCnt] = nullptr;
	}

	return S_OK;
}

//終了処理
void CGameGreed::Uninit(void)
{
	//ポインタの破棄
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
}

//更新処理
void CGameGreed::Update(void)
{
	if (m_pEnemy != nullptr)
	{
		if (m_pEnemy->GetEnd())
		{//敵が死んだら
			if (m_pPlayer != nullptr)
			{
				CApplication::SetRemainingLife(m_pPlayer->GetLife());
			}

			//CApplication::SetMode(CApplication::Mode_Result);			//モードを切り替える
			CApplication::SetFade(CApplication::Mode_Result);			//フェードの設定処理
		}
		else
		{
			UpdateMenu();												//メニューの更新処理
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
CGameGreed* CGameGreed::Create(void)
{
	CGameGreed* pGame = new CGameGreed;					//ステージ画面を生成する

	if (FAILED(pGame->Init()))
	{//初期化処理
		return nullptr;
	}

	pGame->m_pBg = CBg::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f), D3DXVECTOR2(0.000025f, -0.000025f));		//背景を生成する

	if (pGame->m_pBg != nullptr)
	{//背景が生成出来たら、テクスチャを設定する
		pGame->m_pBg->SetTexture(CObject::TextureGreedBg);
		pGame->m_pBg->SetTextureParameter(1, 1, 1, INT_MAX);
	}

	pGame->m_pPlayer = CPlayer::Create();			//プレイヤーの生成

	if (pGame->m_pPlayer != nullptr)
	{//プレイヤーが生成出来たら、位置を設定する
		pGame->m_pPlayer->SetPos(D3DXVECTOR3(300.0f, (float)SCREEN_HEIGHT * 0.5f, 0.0f));
	}

	pGame->m_pEnemy = CGreed::Create();				//敵を生成する

	return pGame;
}



//メニューの更新処理
void CGameGreed::UpdateMenu(void)
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