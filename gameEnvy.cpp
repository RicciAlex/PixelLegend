//=============================================================================
//
// gameEnvy.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "gameEnvy.h"
#include "application.h"
#include "envy.h"
#include "player.h"
#include "inputKeyboard.h"
#include "bg.h"
#include "button.h"
#include "object2D.h"
#include "sound.h"
#include "target.h"

//コンストラクタ
CGameEnvy::CGameEnvy()
{
	//メンバー変数をクリアする
	m_nCntAnim = 0;

	m_bPause = false;

	m_pBg = nullptr;
	m_pPlayer = nullptr;
	m_pEnemy = nullptr;

	m_pMenuBg = nullptr;
	m_pThunderBg = nullptr;

	for (int nCnt = 0; nCnt < button_max; nCnt++)
	{
		m_pButton[nCnt] = nullptr;
	}
}

//デストラクタ
CGameEnvy::~CGameEnvy()
{

}

//初期化処理
HRESULT CGameEnvy::Init(void)
{
	//メンバー変数の初期化
	m_nCntAnim = 0;

	m_bPause = false;

	m_pBg = nullptr;
	m_pPlayer = nullptr;
	m_pEnemy = nullptr;
	//m_pMenu = nullptr;

	m_pMenuBg = nullptr;
	m_pThunderBg = nullptr;

	CTarget::Create();

	for (int nCnt = 0; nCnt < button_max; nCnt++)
	{
		m_pButton[nCnt] = nullptr;
	}

	return S_OK;
}

//終了処理
void CGameEnvy::Uninit(void)
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
	//背景の雷の破棄
	if (m_pThunderBg != nullptr)
	{//nullチェック
		m_pThunderBg->Release();				//メモリを解放する
		m_pThunderBg = nullptr;					//ポインタをnullにする
	}
}

//更新処理
void CGameEnvy::Update(void)
{
	m_nCntAnim++;			//アニメーションカウンターをインクリメントする

	if (m_nCntAnim % 400 == 60)
	{//背景の雷アニメーション
		if (m_pThunderBg == nullptr)
		{
			m_pThunderBg = CObject_2D::Create();				//雷を生成する

			if (m_pThunderBg != nullptr)
			{
				m_pThunderBg->SetPos(D3DXVECTOR3((float)CObject::random(200, 1080), 250.0f, 0.0f));		//位置の設定
				m_pThunderBg->SetTexture(CObject::TextureThunder);										//テクスチャの設定
				m_pThunderBg->SetTextureParameter(8, 4, 2, 4);											//テクスチャパラメータの設定処理
				m_pThunderBg->SetSize(D3DXVECTOR2(40.0f, 133.0f));										//サイズの設定
				m_pThunderBg->SetStartingRot(D3DX_PI * 0.5f);											//回転角度の設定
				m_pThunderBg->SetPriority(1);															//プライオリティの設定

				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_THUNDER);		//雷のサウンドエフェクト

				if (m_pBg != nullptr)
				{//背景を明るくする
					m_pBg->SetVtxColor(0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					m_pBg->SetVtxColor(1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				}
			}
		}
	}

	if (m_pThunderBg != nullptr)
	{//雷のテクスチャアニメーション
		int anim = m_pThunderBg->GetPresentAnimPattern();

		if (anim >= 7)
		{
			m_pThunderBg->Release();											//雷の破棄
			m_pThunderBg = nullptr;												//ポインタをnullにする
			m_pBg->SetVtxColor(0, D3DXCOLOR(0.25f, 0.25f, 0.25f, 1.0f));		//背景カラーを元に戻す
			m_pBg->SetVtxColor(1, D3DXCOLOR(0.25f, 0.25f, 0.25f, 1.0f));		//背景カラーを元に戻す
		}
	}

	if (m_pEnemy != nullptr)
	{//敵のnullチェック

		if (m_pEnemy->GetEnd())
		{//敵が死んでいるかどうか確認する

			if (m_pPlayer != nullptr)
			{//プレイヤーのnullチェック

				CApplication::SetRemainingLife(m_pPlayer->GetLife());			//プレイヤーの残った体力の取得
			}

			CApplication::SetFade(CApplication::Mode_Result);					//フェードの設定処理
		}
		else
		{
			UpdateMenu();														//メニューの更新処理
		}
	}

	if (m_pPlayer != nullptr)
	{//プレイヤーのnullチェック

		if (m_pPlayer->GetEnd())
		{//プレイヤーが死んだら

			CApplication::SetFade(CApplication::Mode_Result);					//フェードの設定処理
		}
	}
}


//=============================================================================
//
//								静的関数
//
//=============================================================================


//生成処理
CGameEnvy* CGameEnvy::Create(void)
{
	CGameEnvy* pGame = new CGameEnvy;				//ステージ画面の生成

	if (FAILED(pGame->Init()))
	{//初期化処理
		return nullptr;
	}

	pGame->m_pBg = CBg::Create(D3DXCOLOR(0.25f, 0.25f, 0.25f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));			//背景の生成

	if (pGame->m_pBg != nullptr)
	{//生成出来た場合、テクスチャを設定する
		pGame->m_pBg->SetTexture(CObject::TextureEnvyBg);
		pGame->m_pBg->SetTextureParameter(1, 1, 1, INT_MAX);
	}
		
	pGame->m_pPlayer = CPlayer::Create();		//プレイヤーの生成

	if (pGame->m_pPlayer != nullptr)
	{//生成できた場合、位置を設定する
		pGame->m_pPlayer->SetPos(D3DXVECTOR3(300.0f, (float)SCREEN_HEIGHT * 0.5f, 0.0f));
	}

	pGame->m_pEnemy = CEnvy::Create();			//敵の生成

	return pGame;
}


//=============================================================================
//
//							プライベート関数
//
//=============================================================================


//メニューの更新処理
void CGameEnvy::UpdateMenu(void)
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