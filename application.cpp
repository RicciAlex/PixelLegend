//=============================================================================
//
// application.cpp
// Author : Ricci Alex
//
//=============================================================================

//インクルードファイル
#include "application.h"
#include "rendering.h"
#include "object.h"
#include "object2D.h"
#include "input.h"
#include "inputKeyboard.h"
#include "inputMouse.h"
#include"player.h"
#include "mode.h"
#include "title.h"
#include "gameScylla.h"
#include "gameThanatos.h"
#include "stageSelection.h"
#include "gamePride.h"
#include "gameEnvy.h"
#include "gameGreed.h"
#include "score.h"
#include "result.h"
#include "sound.h"
#include "ranking.h"
#include "rankingMode.h"
#include "gameGluttony.h"
#include "gameSloth.h"
#include "modeWrath.h"
#include "fade.h"
#include "hitbox.h"
#include "tutorial.h"

//静的メンバー変数の宣言
HWND CApplication::m_hWnd;
CRenderer* CApplication::m_pRenderer = nullptr;			//レンディングインスタンスへのポインタ
CInput* CApplication::m_pInput[2] = {};					//インプットインスタンスへのポインタ
CInputMouse* CApplication::m_pMouse = nullptr;			//マウスインスタンスへのポインタ
CApplication::Mode CApplication::m_mode = CApplication::Mode_Title;
CMode* CApplication::m_pMode = nullptr;
CScore* CApplication::m_pScore = nullptr;
CSound* CApplication::m_pSound = nullptr;
CRanking* CApplication::m_pRanking = nullptr;
CFade* CApplication::m_pFade = nullptr;
bool CApplication::m_bFade = false;
int CApplication::m_nDifficulty = 1;

//コンストラクタ
CApplication::CApplication()
{
	
}

//デストラクタ
CApplication::~CApplication()
{
	
}

//初期化処理
HRESULT CApplication::Init(HINSTANCE hInstance, HWND hWnd)
{
	m_hWnd = hWnd;

	//レンディングインスタンスの生成処理
	if (m_pRenderer == nullptr)
	{//ポインタはnullではなかったら
		m_pRenderer = new CRenderer;
	}

	//レンディングインスタンスの初期化処理
	if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
	{
		return -1;
	}

	//テクスチャ全部をロード処理
	CObject_2D::LoadTextures();

	//モードの生成
	m_pMode = CTitle::Create();

	//キーボードインスタンスの生成処理
	m_pInput[0] = new CInputKeyboard;

	//キーボードの初期化処理
	if (FAILED(m_pInput[0]->Init(hInstance, hWnd, GUID_SysKeyboard)))
	{
		return -1;
	}

	//マウスインプットの生成
	m_pMouse = new CInputMouse;

	//キーボードの初期化処理
	if (FAILED(m_pMouse->Init(hInstance, hWnd, GUID_SysMouse)))
	{
		return -1;
	}

	//スコアの生成
	m_pScore = CScore::Create();

	//ランキングの生成
	m_pRanking = CRanking::Create();

	//サウンドの生成
	m_pSound = CSound::Create(hWnd);

	if (m_pSound != nullptr)
	{//生成出来たら、BGMを再生する

		m_pSound->Play(CSound::SOUND_LABEL_BGM_TITLE);
	}

	//フェードを生成する
	m_pFade = CFade::Create();		
	m_bFade = true;

	return S_OK;
}

//終了処理
void CApplication::Uninit(void)
{
	//テクスチャ全部の破棄
	CObject_2D::DestroyLoadedTextures();

	//レンディングインスタンスの破棄
	if (m_pRenderer != nullptr)
	{//nullチェック

		m_pRenderer->Uninit();		//終了処理
		delete m_pRenderer;			//メモリを解放する
		m_pRenderer = nullptr;		//ポインタをnullにする
	}

	//インプットデバイスの破棄
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pInput[nCnt] != nullptr)
		{//nullチェック

			m_pInput[nCnt]->Uninit();	//終了処理
			delete m_pInput[nCnt];		//メモリを解放する
			m_pInput[nCnt] = nullptr;	//ポインタをnullにする
		}
	}

	//マウスの破棄処理
	if (m_pMouse != nullptr)
	{//nullチェック

		m_pMouse->Uninit();			//終了処理
		delete m_pMouse;			//メモリを解放する
		m_pMouse = nullptr;			//ポインタをnullにする
	}

	//スコアの破棄処理
	if (m_pScore != nullptr)
	{//nullチェック

		m_pScore->Uninit();			//終了処理
		delete m_pScore;			//メモリを解放する
		m_pScore = nullptr;			//ポインタをnullにする
	}

	//ランキングの破棄処理
	if (m_pRanking != nullptr)
	{//nullチェック

		m_pRanking->Uninit();		//終了処理
		delete m_pRanking;			//メモリを解放する
		m_pRanking = nullptr;		//ポインタをnullにする
	}

	//サウンドの破棄処理
	if (m_pSound != nullptr)
	{//nullチェック

		m_pSound->Uninit();			//終了処理
		delete m_pSound;			//メモリを解放する
		m_pSound = nullptr;			//ポインタをnullにする
	}

	//フェードの破棄処理
	if (m_pFade != nullptr)
	{//nullチェック

		m_pFade->Uninit();			//終了処理
		delete m_pFade;				//メモリを解放する
		m_pFade = nullptr;			//ポインタをnullにする
	}

	//オブジェクト全体の終了処理
	CObject::ReleaseAll();
}

//更新処理
void CApplication::Update(void)
{
	//インプットデバイスの更新処理
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pInput[nCnt] != nullptr)
		{//nullチェック
			m_pInput[nCnt]->Update();
		}
	}

	//レンディングの更新処理
	if (m_pRenderer != nullptr)
	{//nullチェック
		m_pRenderer->Update();
	}

	//フェードの更新処理
	if (m_pFade != nullptr)
	{//nullチェック
		m_pFade->Update();
	}

	//モードの更新処理
	if (m_pMode != nullptr)
	{//nullチェック
		m_pMode->Update();
	}
}

//描画処理
void CApplication::Draw(void)
{
	//レンディングの描画処理
	if (m_pRenderer != nullptr)
	{//nullチェック

		m_pRenderer->Draw();
	}
}

//レンディングへのポインタの取得処理
CRenderer* CApplication::GetRenderer(void)
{
	return m_pRenderer;
}

//マウスの取得処理
CInputMouse* CApplication::GetMouse(void)
{
	return m_pMouse;
}

//ウインドウの取得処理
HWND CApplication::GetWindow(void)
{
	return m_hWnd;
}

//難易度の設定処理
void CApplication::SetDifficulty(const int difficulty)
{
	m_pScore->SetDifficulty(difficulty);
	m_nDifficulty = difficulty;
}

//難易度の取得処理
const int CApplication::GetDifficulty(void)
{
	return m_nDifficulty;
}

//プレイヤーの残った体力の設定処理
void CApplication::SetRemainingLife(const int nLife)
{
	m_pScore->SetLife(nLife);
}

//モードの取得処理
CApplication::Mode CApplication::GetMode(void)
{
	return m_mode;
}

//モードの設定処理
void CApplication::SetMode(Mode mode)
{
	//現在のモードを破棄する
	if (m_pMode != nullptr)
	{//nullチェック
		m_pMode->Uninit();		//終了処理
		delete m_pMode;			//メモリを解放する
		m_pMode = nullptr;		//ポインタをnullにする
	}

	CObject::ReleaseAll();		//全部のオブジェクトの破棄処理
	CHitbox::ReleaseAll();		//全部のヒットボックスの破棄処理

	//サウンドを停止する
	if (m_pSound != nullptr)
	{//nullチェック
		m_pSound->Stop();
	}

	Sleep(150);

	switch (mode)
	{
	case CApplication::Mode_Title:

	{//タイトル

		m_pMode = CTitle::Create();			//新しいモードの生成
		
		if (m_pMode != nullptr)
		{//nullチェック
			m_mode = mode;
		}

		//選択されたステージの設定
		if (m_pRanking != nullptr)
		{//nullチェック
			m_pRanking->SetStage(CStageSelection::stage_Scylla);
		}

		//BGMを再生する
		if (m_pSound != nullptr)
		{//nullチェック
			m_pSound->Play(CSound::SOUND_LABEL_BGM_TITLE);
		}
	}

		break;

	case CApplication::Mode_StageSelection:

	{//ステージ選択画面

		m_pMode = CStageSelection::Create();			//新しいモードの生成

		if (m_pMode != nullptr)
		{//nullチェック
			m_mode = mode;
		}

		//選択されたステージの設定
		if (m_pRanking != nullptr)
		{//nullチェック
			m_pRanking->SetStage(CStageSelection::stage_Scylla);
		}

		//BGMを再生する
		if (m_pSound != nullptr)
		{//nullチェック
			m_pSound->Play(CSound::SOUND_LABEL_BGM_STAGE_SELECTION);
		}
	}

		break;

	case CApplication::Mode_Tutorial:			

	{//チュートリアル

		m_pMode = CTutorial::Create();				//新しいモードの生成

		if (m_pMode != nullptr)
		{//nullチェック
			m_mode = mode;
		}

		//選択されたステージの設定
		if (m_pRanking != nullptr)
		{//nullチェック
			m_pRanking->SetStage(CStageSelection::stage_Scylla);
		}

		//BGMを再生する
		if (m_pSound != nullptr)
		{//nullチェック
			m_pSound->Play(CSound::SOUND_LABEL_BGM_STAGE_SELECTION);
		}
	}

	break;

	case CApplication::Mode_Game:

	{
		
	}

		break;

	case CApplication::Mode_Game_Scylla:

	{
		m_pMode = CGameScylla::Create();				//新しいモードの生成

		if (m_pMode != nullptr)
		{//nullチェック
			m_mode = mode;
		}

		//スコアをクリアしてから、ベーススコアを設定する
		if (m_pScore != nullptr)
		{//nullチェック
			m_pScore->Clear();
			m_pScore->SetBaseScore(200000);
		}

		//選択されたステージの設定
		if (m_pRanking != nullptr)
		{//nullチェック
			m_pRanking->SetStage(CStageSelection::stage_Scylla);
		}

		//BGMを再生する
		if (m_pSound != nullptr)
		{//nullチェック
			m_pSound->Play(CSound::SOUND_LABEL_BGM_GAME);
		}
	}

		break;

	case CApplication::Mode_Game_Thanatos:

	{
		m_pMode = CGameThanatos::Create();				//新しいモードの生成

		if (m_pMode != nullptr)
		{//nullチェック
			m_mode = mode;
		}

		//スコアをクリアしてから、ベーススコアを設定する
		if (m_pScore != nullptr)
		{//nullチェック
			m_pScore->Clear();
			m_pScore->SetBaseScore(300000);
		}

		//選択されたステージの設定
		if (m_pRanking != nullptr)
		{//nullチェック
			m_pRanking->SetStage(CStageSelection::stage_Thanatos);
		}

		//BGMを再生する
		if (m_pSound != nullptr)
		{//nullチェック
			m_pSound->Play(CSound::SOUND_LABEL_BGM_THANATOS);
		}
	}

	break;

	case CApplication::Mode_Game_Pride:

	{
		m_pMode = CGamePride::Create();					//新しいモードの生成

		if (m_pMode != nullptr)
		{//nullチェック
			m_mode = mode;
		}

		//スコアをクリアしてから、ベーススコアを設定する
		if (m_pScore != nullptr)
		{//nullチェック
			m_pScore->Clear();
			m_pScore->SetBaseScore(150000);
		}

		//選択されたステージの設定
		if (m_pRanking != nullptr)
		{//nullチェック
			m_pRanking->SetStage(CStageSelection::stage_Pride);
		}

		//BGMを再生する
		if (m_pSound != nullptr)
		{//nullチェック
			m_pSound->Play(CSound::SOUND_LABEL_BGM_GAME);
		}
	}

	break;

	case CApplication::Mode_Game_Envy:

	{
		m_pMode = CGameEnvy::Create();					//新しいモードの生成

		if (m_pMode != nullptr)
		{//nullチェック
			m_mode = mode;
		}

		//スコアをクリアしてから、ベーススコアを設定する
		if (m_pScore != nullptr)
		{//nullチェック
			m_pScore->Clear();
			m_pScore->SetBaseScore(500000);
		}

		//選択されたステージの設定
		if (m_pRanking != nullptr)
		{//nullチェック
			m_pRanking->SetStage(CStageSelection::stage_Envy);
		}

		//BGMを再生する
		if (m_pSound != nullptr)
		{//nullチェック
			m_pSound->Play(CSound::SOUND_LABEL_BGM_GAME);
		}
	}

	break;

	case CApplication::Mode_Game_Wrath:

	{
		m_pMode = CGameWrath::Create();					//新しいモードの生成

		if (m_pMode != nullptr)
		{//nullチェック
			m_mode = mode;
		}

		//スコアをクリアしてから、ベーススコアを設定する
		if (m_pScore != nullptr)
		{//nullチェック
			m_pScore->Clear();
			m_pScore->SetBaseScore(500000);
		}

		//選択されたステージの設定
		if (m_pRanking != nullptr)
		{//nullチェック
			m_pRanking->SetStage(CStageSelection::stage_Wrath);
		}

		//BGMを再生する
		if (m_pSound != nullptr)
		{//nullチェック
			m_pSound->Play(CSound::SOUND_LABEL_BGM_GAME);
		}
	}

	break;

	case CApplication::Mode_Game_Sloth:

	{
		m_pMode = CGameSloth::Create();					//新しいモードの生成

		if (m_pMode != nullptr)
		{//nullチェック
			m_mode = mode;
		}

		//スコアをクリアしてから、ベーススコアを設定する
		if (m_pScore != nullptr)
		{//nullチェック
			m_pScore->Clear();
			m_pScore->SetBaseScore(250000);
		}

		//選択されたステージの設定
		if (m_pRanking != nullptr)
		{//nullチェック
			m_pRanking->SetStage(CStageSelection::stage_Sloth);
		}

		//BGMを再生する
		if (m_pSound != nullptr)
		{//nullチェック
			m_pSound->Play(CSound::SOUND_LABEL_BGM_GAME);
		}
	}

	break;

	case CApplication::Mode_Game_Greed:

	{
		m_pMode = CGameGreed::Create();					//新しいモードの生成

		if (m_pMode != nullptr)
		{//nullチェック
			m_mode = mode;
		}

		//スコアをクリアしてから、ベーススコアを設定する
		if (m_pScore != nullptr)
		{//nullチェック
			m_pScore->Clear();
			m_pScore->SetBaseScore(350000);
		}

		//選択されたステージの設定
		if (m_pRanking != nullptr)
		{//nullチェック
			m_pRanking->SetStage(CStageSelection::stage_Greed);
		}

		//BGMを再生する
		if (m_pSound != nullptr)
		{//nullチェック
			m_pSound->Play(CSound::SOUND_LABEL_BGM_GAME);
		}
	}

	break;

	case CApplication::Mode_Game_Gluttony:

	{
		m_pMode = CGameGluttony::Create();					//新しいモードの生成

		if (m_pMode != nullptr)
		{//nullチェック
			m_mode = mode;
		}

		//スコアをクリアしてから、ベーススコアを設定する
		if (m_pScore != nullptr)
		{//nullチェック
			m_pScore->Clear();
			m_pScore->SetBaseScore(250000);
		}

		//選択されたステージの設定
		if (m_pRanking != nullptr)
		{//nullチェック
			m_pRanking->SetStage(CStageSelection::stage_Gluttony);
		}

		//BGMを再生する
		if (m_pSound != nullptr)
		{//nullチェック
			m_pSound->Play(CSound::SOUND_LABEL_BGM_GAME);
		}
	}

	break;

	case CApplication::Mode_Result:

	{
		int nScore = m_pScore->GetFinalScore();				//スコアの取得処理

		//ランキングの更新
		if (m_pRanking != nullptr)
		{//nullチェック
			m_pRanking->SetRanking((CStageSelection::stage)m_pRanking->GetStage(), nScore);
		}

		m_pMode = CResult::Create(nScore);					//新しいモードの生成

		if (m_pMode != nullptr)
		{//nullチェック
			m_mode = mode;
		}
	}

		break;

	case CApplication::Mode_Ranking:

	{
		int stage = 0;

		//ステージの設定
		if (m_pRanking != nullptr)
		{//nullチェック
			stage = m_pRanking->GetStage();
		}

		m_pMode = CRankingMode::Create(stage);				//新しいモードの生成

		if (m_pMode != nullptr)
		{//nullチェック
			m_mode = mode;
		}
	}

		break;

	default:

		break;
	}
}

//サウンドの取得処理
CSound* CApplication::GetSound(void)
{
	return m_pSound;
}

//ランキングの取得処理
CRanking* CApplication::GetRanking(void)
{
	return m_pRanking;
}

//フェードの設定処理
void CApplication::SetFade(CApplication::Mode mode)
{
	if (m_pFade != nullptr)
	{
		m_pFade->SetFadeOut(mode);
	}
}

//フェード状態の設定処理
void CApplication::SetFade(const bool bFade)
{
	m_bFade = bFade;
}

//フェード状態の設定処理
const bool CApplication::GetFade(void)
{
	return m_bFade;
}