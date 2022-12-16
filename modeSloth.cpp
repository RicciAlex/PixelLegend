//=============================================================================
//
// gameSloth.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "gameSloth.h"
#include "application.h"
#include "sloth.h"
#include "player.h"
#include "inputKeyboard.h"
#include "bg.h"
#include "button.h"
#include "object2D.h"
#include "sound.h"
#include "backMaw.h"
#include "target.h"

//コンストラクタ
CGameSloth::CGameSloth()
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
CGameSloth::~CGameSloth()
{

}

//初期化処理
HRESULT CGameSloth::Init(void)
{
	//メンバー変数の初期化

	m_bPause = false;

	m_pBg = nullptr;
	m_pPlayer = nullptr;
	m_pEnemy = nullptr;

	m_pMenuBg = nullptr;

	for (int nCnt = 0; nCnt < button_max; nCnt++)
	{
		m_pButton[nCnt] = nullptr;
	}

	return S_OK;
}

//終了処理
void CGameSloth::Uninit(void)
{
	//ポインタの破棄
	if (m_pBg != nullptr)
	{//nullチェック
		m_pBg->Release();				//メモリを解放する
		m_pBg = nullptr;				//ポインタをnullにする
	}

	if (m_pPlayer != nullptr)
	{//nullチェック
		m_pPlayer->Release();			//メモリを解放する
		m_pPlayer = nullptr;			//ポインタをnullにする
	}

	if (m_pEnemy != nullptr)
	{//nullチェック
		m_pEnemy->Uninit();				//メモリを解放する
		m_pEnemy = nullptr;				//ポインタをnullにする
	}

	if (m_pMenuBg != nullptr)
	{//nullチェック
		m_pMenuBg->Release();			//メモリを解放する
		m_pMenuBg = nullptr;			//ポインタをnullにする
	}


	for (int nCnt = 0; nCnt < button_max; nCnt++)
	{
		if (m_pButton[nCnt] != nullptr)
		{//nullチェック
			m_pButton[nCnt]->Uninit();			//メモリを解放する
			m_pButton[nCnt] = nullptr;			//ポインタをnullにする
		}
	}
}

//更新処理
void CGameSloth::Update(void)
{
	if (m_pEnemy != nullptr)
	{
		if (m_pEnemy->GetEnd())
		{//敵が死んでいるかどうか確認する
			if (m_pPlayer != nullptr)
			{
				CApplication::SetRemainingLife(m_pPlayer->GetLife());			//プレイヤーの残った体力の設定
			}

			CApplication::SetMode(CApplication::Mode_Result);					//モードを切り替える
			return;
		}
		else
		{
			UpdateMenu();														//メニューの更新処理
		}
	}

	if (m_pPlayer != nullptr)
	{
		if (m_pPlayer->GetEnd())
		{
			CApplication::SetFade(CApplication::Mode_Result);					//フェードの設定処理
			return;
		}
	}
}



//=============================================================================
//
//								静的関数
//
//=============================================================================



//生成処理
CGameSloth* CGameSloth::Create(void)
{
	CGameSloth* pGame = new CGameSloth;				//ステージ画面の生成

	if (FAILED(pGame->Init()))
	{//初期化処理
		return nullptr;
	}

	pGame->m_pBg = CBg::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));			//背景の生成

	if (pGame->m_pBg != nullptr)
	{//生成出来た場合、テクスチャを設定する
		pGame->m_pBg->SetTexture(CObject::TextureSlothBg);
		pGame->m_pBg->SetTextureParameter(1, 1, 1, INT_MAX);
	}

	pGame->m_pPlayer = CPlayer::Create();		//プレイヤーの生成

	if (pGame->m_pPlayer != nullptr)
	{//生成できた場合、位置を設定する
		pGame->m_pPlayer->SetPos(D3DXVECTOR3(300.0f, (float)SCREEN_HEIGHT * 0.5f, 0.0f));
	}

	pGame->m_pEnemy = CSloth::Create();			//敵の生成

	return pGame;				//生成したインスタンスを返す
}



//=============================================================================
//
//								プライベート関数
//
//=============================================================================



//メニューの更新処理
void CGameSloth::UpdateMenu(void)
{
	if (CInputKeyboard::GetKeyboardTrigger(DIK_RETURN))
	{//エンターキーを押したら
		if (m_bPause)
		{//ポーズ状態だったら
			m_bPause = false;			//普通状態にする

										//ボタンを破棄する
			for (int nCnt = 0; nCnt < button_max; nCnt++)
			{
				if (m_pButton[nCnt] != nullptr)
				{
					m_pButton[nCnt]->Uninit();
					m_pButton[nCnt] = nullptr;
				}
			}
			//メニューの背景を破棄する
			if (m_pMenuBg != nullptr)
			{
				m_pMenuBg->Release();
				m_pMenuBg = nullptr;
			}

			CObject::SetPause(false);			//ポーズ中ではない状態にする
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
			{//nullチェック
				m_pButton[nCnt]->Update();

				if (m_pButton[nCnt]->GetTriggerState())
				{//押されたら

					CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_CLICK);		//クリックサウンドを再生する

																						//どんなボタンが押されたによって更新する
					switch (nCnt)
					{
					case button_continue:

					{//コンティニューボタンだったら、ポーズメニューを破棄する
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

					{//タイトルに戻るボタンだったら、タイトル画面に切り替える

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