//=============================================================================
//
// gameThanatos.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "gameThanatos.h"
#include "Thanatos.h"
#include "player.h"
#include "inputKeyboard.h"
#include "inputMouse.h"
#include "bg.h"
#include "button.h"
#include "application.h"
#include "sound.h"
#include "target.h"

//コンストラクタ
CGameThanatos::CGameThanatos()
{
	//メンバー変数をクリックする
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
CGameThanatos::~CGameThanatos()
{

}

//初期化処理
HRESULT CGameThanatos::Init(void)
{
	//メンバー変数を初期化する
	m_bPause = false;

	m_pBg = nullptr;
	m_pPlayer = nullptr;
	m_pEnemy = nullptr;

	m_pMenuBg = nullptr;

	CTarget::Create();

	for (int nCnt = 0; nCnt < button_max; nCnt++)
	{
		m_pButton[nCnt] = nullptr;
	}

	return S_OK;
}

//終了処理
void CGameThanatos::Uninit(void)
{
	//背景の破棄
	if (m_pBg != nullptr)
	{//nullチェック
		m_pBg->Release();			//メモリを解放する
		m_pBg = nullptr;			//ポインタをnullにする
	}
	//プレイヤーの破棄
	if (m_pPlayer != nullptr)
	{//nullチェック
		m_pPlayer->Release();		//メモリを解放する
		m_pPlayer = nullptr;		//ポインタをnullにする
	}
	//敵の破棄
	if (m_pEnemy != nullptr)
	{//nullチェック
		m_pEnemy->Release();		//メモリを解放する
		m_pEnemy = nullptr;			//ポインタをnullにする
	}
	//メニューの背景の破棄
	if (m_pMenuBg != nullptr)
	{//nullチェック
		m_pMenuBg->Release();		//メモリを解放する
		m_pMenuBg = nullptr;		//ポインタをnullにする
	}
	//ボタンの破棄
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
void CGameThanatos::Update(void)
{
	if (m_pEnemy != nullptr)
	{//敵のnullチェック

		if (m_pEnemy->GetEnd())
		{//敵が死んだら

			if (m_pPlayer != nullptr)
			{//プレイヤーのnullチェック

				CApplication::SetRemainingLife(m_pPlayer->GetLife());		//プレイヤーの残った体力の取得
			}

			CApplication::SetFade(CApplication::Mode_Result);				//リザルト画面に切り替える
		}
		else
		{//まだ死んでいなかったら

			UpdateMenu();			//メニューを更新する
		}
	}

	if (m_pPlayer != nullptr)
	{//プレイヤーのnullチェック

		if (m_pPlayer->GetEnd())
		{//プレイヤーが死んだら

			CApplication::SetFade(CApplication::Mode_Result);		//リザルト画面に切り替える
		}
	}
}



//=============================================================================
//
//								静的関数
//
//=============================================================================



//生成処理
CGameThanatos* CGameThanatos::Create(void)
{
	CGameThanatos* pGame = new CGameThanatos;		//インスタンスを生成する

	if (FAILED(pGame->Init()))
	{//初期化処理
		return nullptr;
	}

	//背景を生成する
	pGame->m_pBg = CBg::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, -0.0f));		

	if (pGame->m_pBg != nullptr)
	{//生成出来たら、必要なパラメータの設定
		pGame->m_pBg->SetTexture(CObject::TextureThanatosBG);
		pGame->m_pBg->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
		pGame->m_pBg->SetTextureParameter(1, 1, 1, INT_MAX);
	}

	//プレイヤーの生成
	pGame->m_pPlayer = CPlayer::Create();

	if (pGame->m_pPlayer != nullptr)
	{//生成出来たら、位置を設定する
		pGame->m_pPlayer->SetPos(D3DXVECTOR3(300.0f, (float)SCREEN_HEIGHT * 0.5f, 0.0f));
	}

	//敵の生成
	pGame->m_pEnemy = CThanatos::Create();

	if (pGame->m_pEnemy)
	{//生成出来たら、背景へのポインタを設定する
		pGame->m_pEnemy->SetBgPointer(pGame->m_pBg);
	}

	return pGame;			//生成したインスタンスを返す
}


//=============================================================================
//
//							プライベート関数
//
//=============================================================================


//メニューの更新処理
void CGameThanatos::UpdateMenu(void)
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