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

//=============================================================================
//							静的変数の初期化
//=============================================================================
D3DXCOLOR CTitle::targetColors[CTitle::TargetCol_Max] =				//タイトルアニメーションの色
{
	{1.0f, 0.0f, 0.0f, 1.0f},			//赤
	{0.0f, 1.0f, 0.0f, 1.0f},			//緑
	{0.0f, 0.0f, 1.0f, 1.0f},			//青
	{1.0f, 1.0f, 0.0f, 1.0f},			//黄
	{1.0f, 0.0f, 1.0f, 1.0f},			//マゼンタ
	{0.0f, 1.0f, 1.0f, 1.0f}			//シアン
};

//コンストラクタ
CTitle::CTitle()
{
	//メンバー変数をクリアする
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
	//メンバー変数を初期化する
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
	//背景の破棄
	if (m_pBg != nullptr)
	{//nullチェック
		m_pBg->Release();					//メモリを解放する
		m_pBg = nullptr;					//ポインタをnullにする
	}

	//ボタンの破棄
	for (int nCnt = 0; nCnt < button_max; nCnt++)
	{
		if (m_pButton[nCnt] != nullptr)
		{//nullチェック
			m_pButton[nCnt]->Uninit();		//メモリを解放する
			m_pButton[nCnt] = nullptr;		//ポインタをnullにする
		}
	}

	//カーソルの破棄
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pCursor[nCnt] != nullptr)
		{//nullチェック
			m_pCursor[nCnt]->Uninit();		//メモリを解放する
			m_pCursor[nCnt] = nullptr;		//ポインタをnullにする
		}
	}

	//タイトルの文字の破棄
	for (int nCnt = 0; nCnt < 16; nCnt++)
	{
		if (m_pTitle[nCnt] != nullptr)
		{//nullチェック
			m_pTitle[nCnt]->Release();		//メモリを解放する
			m_pTitle[nCnt] = nullptr;		//ポインタをnullにする
		}
	}
}

//更新処理
void CTitle::Update(void)
{
	UpdateTitleColor();						//タイトルの色の更新処理

	//カーソルの更新処理
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pCursor[nCnt] != nullptr)
		{//nullチェック
			m_pCursor[nCnt]->Update();
		}
	}

	//ボタンの更新処理
	if (m_pButton[button_play] != nullptr)
	{//プレイボタンのnullチェック

		m_pButton[button_play]->Update();			//プレイボタンの更新処理

		if (m_pButton[button_play]->GetTriggerState())
		{//押されたら

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_CLICK);		//クリックのサウンドを再生する

			CApplication::SetFade(CApplication::Mode_StageSelection);			//ステージ選択画面に移動
			return;		
		}
	}
	if (m_pButton[button_tutorial] != nullptr)
	{//チュートリアルボタンのnullチェック

		m_pButton[button_tutorial]->Update();		//チュートリアルボタンの更新処理

		if (m_pButton[button_tutorial]->GetTriggerState())
		{//押されたら

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_CLICK);		//クリックのサウンドを再生する

			CApplication::SetFade(CApplication::Mode_Tutorial);					//チュートリアル画面に移動
			return;
		}
	}
	if (m_pButton[button_leaderboard] != nullptr)
	{//ランキングボタンのnullチェック

		m_pButton[button_leaderboard]->Update();	//ランキングボタンの更新処理

		if (m_pButton[button_leaderboard]->GetTriggerState())
		{//押されたら

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_CLICK);		//クリックのサウンドを再生する

			CApplication::SetFade(CApplication::Mode_Ranking);					//ランキング画面に移動
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
CTitle* CTitle::Create(void)
{
	CTitle* pTitle = new CTitle;			//インスタンスを生成する

	if (FAILED(pTitle->Init()))
	{//初期化処理
		return nullptr;
	}

	pTitle->m_pBg = CBg::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));		//タイトルの生成

	if (pTitle->m_pBg)
	{//生成出来たら、必要なパラメータの設定

		pTitle->m_pBg->SetTexture(CObject::TextureMenuBg);
		pTitle->m_pBg->SetTextureParameter(1, 1, 1, INT_MAX);
		pTitle->m_pBg->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		pTitle->m_pCursor[0] = CSkullCursor::Create(D3DXVECTOR3(0.0f, (float)SCREEN_HEIGHT * 0.5f, 0.0f));
		pTitle->m_pCursor[1] = CSkullCursor::Create(D3DXVECTOR3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT * 0.5f, 0.0f));
	}

	char aStr[16] = "pixel legend";			//タイトルの文字列

	int Lenght = strlen(aStr);

	for (int nCnt = 0; nCnt < Lenght; nCnt++)
	{
		//タイトルの文字の生成
		pTitle->m_pTitle[nCnt] = CLetter::Create(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f - 75.0f * (Lenght * 0.5f) + (80.0f * nCnt), (float)SCREEN_HEIGHT * 0.25f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), aStr[nCnt]);
		
		if (pTitle->m_pTitle[nCnt] != nullptr)
		{//生成出来たら、色とプライオリティの設定

			pTitle->m_pTitle[nCnt]->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			pTitle->m_pTitle[nCnt]->SetPriority(2);
		}
	}

	pTitle->m_TargetCol = TargetCol_Yellow;		//目的の色の設定

	char aText[button_max][24] = { { "play" }, { "tutorial" },{ "leaderboard" } };			//ボタンの文字列

	for (int nCnt = 0; nCnt < button_max; nCnt++)
	{
		//ボタンの生成
		pTitle->m_pButton[nCnt] = CButton::Create(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f + 50.0f * 2.5f * nCnt, 0.0f), D3DXVECTOR2(300.0f, 55.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), aText[nCnt]);
	}

	return pTitle;				//生成したインスタンスを返す
}



//=============================================================================
//
//							プライベート関数
//
//=============================================================================


//タイトルの色の更新処理
void CTitle::UpdateTitleColor(void)
{
	m_nChangeFrame--;				//アニメーションカウンターをデクリメントする

	if (m_nChangeFrame <= 0)
	{//アニメーションカウンターが0以下になったら

		m_nChangeFrame = 120;		//120に戻す

		//現在の色によって、次の目的の色を設定する
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

		m_changeCol = targetColors[m_TargetCol] - m_pTitle[0]->GetColor();
		m_changeCol.r /= 120.0f;
		m_changeCol.g /= 120.0f;
		m_changeCol.b /= 120.0f;
		m_changeCol.a = 0.0f;
	}
	else
	{//アニメーションがまだ途中だったら

		D3DXCOLOR col = m_pTitle[0]->GetColor();		//現在の色を取得する

		col += m_changeCol;			//色を更新する

		//色を設定する
		for (int nCnt = 0; nCnt < 16; nCnt++)
		{
			if (m_pTitle[nCnt] != nullptr)
			{//nullチェック

				m_pTitle[nCnt]->SetColor(col);
			}
		}
	}

}