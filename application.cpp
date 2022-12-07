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
#include "bg.h"
#include "input.h"
#include "inputKeyboard.h"
#include "inputMouse.h"
#include"player.h"
#include "blackHole.h"
#include "enemy.h"
#include "enemyClock.h"
#include "enemyCloud.h"
#include "enemyWrathBody.h"
#include "SkullTentacle.h"
#include "Scylla.h"
#include "ScyllaBody.h"
#include "spine.h"
#include "skull.h"
#include "sloth.h"
#include "pride.h"
#include "candle.h"
#include "Thanatos.h"
#include "envy.h"
#include "greed.h"
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
	if (FAILED(m_pRenderer->Init(hWnd, FALSE)))
	{
		return -1;
	}

	//テクスチャ全部をロード処理
	CObject_2D::LoadTextures();

	m_pMode = CTitle::Create();

	//CObject::ReleaseAll();

	////CBg* pBg = CBg::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f), D3DXVECTOR2(0.000025f, -0.000025f));

	///*CBg* pBg = CBg::Create(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR2(0.000005f, -0.0001f));
	//pBg->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//pBg->SetSize(D3DXVECTOR2(1000.0f, 500.0f));
	//pBg->SetTexture(CObject::TextureGreedBg);
	//pBg->SetTextureParameter(1, 1, 1, INT_MAX);*/

	////pBg->SetTexture(CObject::TextureThanatosBG);
	//
	//CBg* pBg = CBg::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	//pBg->SetTexture(CObject::TextureGluttonyBg);
	//pBg->SetTextureParameter(1, 1, 1, INT_MAX);

	///*CObject_2D* pObj = CObject_2D::Create();
	//pObj->SetPos(D3DXVECTOR3(640.0f, 100.0f, 0.0f));
	//pObj->SetSize(D3DXVECTOR2(50.0f, 100.0f));
	//pObj->SetColor(D3DCOLOR_ARGB(255, 255, 45, 45));
	//pBg->SetTextureParameter(1, 1, 1, INT_MAX);*/

	//////オブジェクト4つ分の生成処理
	////for (int nCnt = 0; nCnt < 4; nCnt++)
	////{
	////	CObject* pObject = CObject::Create(CObject::OBJECT2D);
	////
	////	//オブジェクトの初期化処理
	////	if (FAILED(pObject->Init()))
	////	{
	////		return -1;
	////	}

	////	pObject->SetPos(D3DXVECTOR3(SCREEN_WIDTH * (0.25f + 0.5f * (nCnt % 2)), SCREEN_HEIGHT * (0.25f + (0.5f * (nCnt / 2))), 0.0f));	//位置の設定処理
	////	pObject->SetTextureParameter(8, 4, 2, 3);			//テクスチャパラメータの設定処理
	////	pObject->SetTexture(CObject::TextureThunder);				//テクスチャ種類の設定処理
	////}

	////プレイヤーの生成処理
	//CPlayer* pPlayer = CPlayer::Create();

	////プレイヤーの初期化処理
	//if (FAILED(pPlayer->Init()))
	//{
	//	return -1;
	//}

	////プレイヤーの位置の設定処理
	//pPlayer->SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));

	///*CEnemyCloud* pEnemy = CEnemyCloud::Create(D3DXVECTOR3((float)(SCREEN_WIDTH), (float)(SCREEN_HEIGHT) * 0.5f, 0.0f));

	//CEnemyClock* pBEnemy = CEnemyClock::Create(D3DXVECTOR3((float)(SCREEN_WIDTH * 0.89f), (float)(SCREEN_HEIGHT) * 0.5f, 0.0f));*/

	//
	///*CWrathBody* pWBEnemy = CWrathBody::Create(D3DXVECTOR3(1000.0f, 400.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//CEnemyWrathArm* pWEnemy = CEnemyWrathArm::Create(D3DXVECTOR3(1000.0f, 400.0f, 0.0f), D3DXVECTOR3(60.0f, 95.0f, 0.0f));
	//pWEnemy->SetTargetAngle(D3DX_PI - (D3DX_PI * 0.1f));
	//pWEnemy = CEnemyWrathArm::Create(D3DXVECTOR3(1000.0f, 400.0f, 0.0f), D3DXVECTOR3(-60.0f, 100.0f, 0.0f));
	//pWEnemy->SetTargetAngle(-D3DX_PI + (D3DX_PI * 0.1f));
	//pWEnemy->ChangeKey();*/
	//

	///*CSpine* pSpine = CSpine::Create(D3DXVECTOR3((float)SCREEN_WIDTH * 0.85f, 550.0f, 0.0f), D3DXVECTOR3((float)SCREEN_WIDTH * 0.9f, 800.0f, 0.0f));
	//pSpine = CSpine::Create(D3DXVECTOR3((float)SCREEN_WIDTH * 0.825f, 550.0f, 0.0f), D3DXVECTOR3((float)SCREEN_WIDTH * 0.85f, 800.0f, 0.0f));
	//pSpine = CSpine::Create(D3DXVECTOR3((float)SCREEN_WIDTH * 0.8f, 550.0f, 0.0f), D3DXVECTOR3((float)SCREEN_WIDTH * 0.8f, 800.0f, 0.0f));
	//pSpine = CSpine::Create(D3DXVECTOR3((float)SCREEN_WIDTH * 0.775f, 550.0f, 0.0f), D3DXVECTOR3((float)SCREEN_WIDTH * 0.75f, 800.0f, 0.0f));
	//pSpine = CSpine::Create(D3DXVECTOR3((float)SCREEN_WIDTH * 0.75f, 550.0f, 0.0f), D3DXVECTOR3((float)SCREEN_WIDTH * 0.7f, 800.0f, 0.0f));
	//pSpine = CSpine::Create(D3DXVECTOR3((float)SCREEN_WIDTH * 0.725f, 550.0f, 0.0f), D3DXVECTOR3((float)SCREEN_WIDTH * 0.65f, 800.0f, 0.0f));
	//CSkullTentacle* pTentacle = CSkullTentacle::Create(D3DXVECTOR3((float)SCREEN_WIDTH * 0.6f, (float)SCREEN_HEIGHT, 0.0f), D3DXVECTOR3((float)SCREEN_WIDTH * 0.6f, (float)SCREEN_HEIGHT * 0.8f, 0.0f));
	//pTentacle = CSkullTentacle::Create(D3DXVECTOR3((float)SCREEN_WIDTH * 0.4f, (float)SCREEN_HEIGHT, 0.0f), D3DXVECTOR3((float)SCREEN_WIDTH * 0.4f, (float)SCREEN_HEIGHT * 0.8f, 0.0f));
	//pTentacle = CSkullTentacle::Create(D3DXVECTOR3((float)SCREEN_WIDTH * 0.4f, 0.0f, 0.0f), D3DXVECTOR3((float)SCREEN_WIDTH * 0.4f, (float)SCREEN_HEIGHT * 0.2f, 0.0f));
	//pTentacle = CSkullTentacle::Create(D3DXVECTOR3((float)SCREEN_WIDTH * 0.6f, 0.0f, 0.0f), D3DXVECTOR3((float)SCREEN_WIDTH * 0.6f, (float)SCREEN_HEIGHT * 0.2f, 0.0f));
	//pTentacle = CSkullTentacle::Create(D3DXVECTOR3((float)SCREEN_WIDTH * 0.2f, 0.0f, 0.0f), D3DXVECTOR3((float)SCREEN_WIDTH * 0.2f, (float)SCREEN_HEIGHT * 0.2f, 0.0f));
	//pTentacle = CSkullTentacle::Create(D3DXVECTOR3((float)SCREEN_WIDTH * 0.2f, (float)SCREEN_HEIGHT, 0.0f), D3DXVECTOR3((float)SCREEN_WIDTH * 0.2f, (float)SCREEN_HEIGHT * 0.8f, 0.0f));
	//CScyllaBody* pBody = CScyllaBody::Create();*/

	////CScylla* pScylla = CScylla::Create();

	////CPride* pPride = CPride::Create();

	////CSloth* pSloth = CSloth::Create();

	///*CObject_2D* pObject = CObject_2D::Create();
	//pObject->SetPos(D3DXVECTOR3(600.0f, 300.0f, 0.0f));
	//pObject->SetSize(D3DXVECTOR2(30.0f, 30.0f));
	//pObject->SetTexture(CObject::TextureGear);
	//pObject->SetTextureParameter(1, 3, 2, INT_MAX);
	//pObject->SetRotation(D3DX_PI * 0.01f);

	//pObject = CObject_2D::Create();
	//pObject->SetPos(D3DXVECTOR3(650.0f, 320.0f, 0.0f));
	//pObject->SetSize(D3DXVECTOR2(45.0f, 45.0f));
	//pObject->SetTexture(CObject::TextureGear);
	//pObject->SetTextureParameter(1, 3, 2, INT_MAX);
	//pObject->SetRotation(-D3DX_PI * 0.015f);*/

	///*CThanatos* pThanatos = CThanatos::Create();
	//pThanatos->SetBgPointer(pBg);*/

	////CEnvy* pEnvy = CEnvy::Create();

	//CGreed* pGreed = CGreed::Create();

	//キーボードインスタンスの生成処理
	m_pInput[0] = new CInputKeyboard;

	//キーボードの初期化処理
	if (FAILED(m_pInput[0]->Init(hInstance, hWnd, GUID_SysKeyboard)))
	{
		return -1;
	}

	m_pMouse = new CInputMouse;

	//キーボードの初期化処理
	if (FAILED(m_pMouse->Init(hInstance, hWnd, GUID_SysMouse)))
	{
		return -1;
	}

	m_pScore = CScore::Create();

	m_pRanking = CRanking::Create();

	m_pSound = CSound::Create(hWnd);

	if (m_pSound != nullptr)
	{
		m_pSound->Play(CSound::SOUND_LABEL_BGM_TITLE);
	}

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
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}

	//インプットデバイスの破棄
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pInput[nCnt] != nullptr)
		{
			m_pInput[nCnt]->Uninit();
			delete m_pInput[nCnt];
			m_pInput[nCnt] = nullptr;
		}
	}

	if (m_pMouse != nullptr)
	{
		m_pMouse->Uninit();
		delete m_pMouse;
		m_pMouse = nullptr;
	}

	if (m_pScore != nullptr)
	{
		m_pScore->Uninit();
		delete m_pScore;
		m_pScore = nullptr;
	}

	if (m_pRanking != nullptr)
	{
		m_pRanking->Uninit();
		delete m_pRanking;
		m_pRanking = nullptr;
	}

	if (m_pSound != nullptr)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}

	if (m_pFade != nullptr)
	{
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = nullptr;
	}

	//オブジェクト全体の終了処理
	CObject::ReleaseAll();
}

//更新処理
void CApplication::Update(void)
{
#ifdef _DEBUG

	CBlackHole* pBullet = nullptr;
	if (CInputKeyboard::GetKeyboardTrigger(DIK_L))
	{
		pBullet = CBlackHole::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(100.0f, 100.0f), 300);
		pBullet->SetRotation(-D3DX_PI * 0.01f);
		pBullet = CBlackHole::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(50.0f, 50.0f), 300);
		pBullet->SetRotation(-D3DX_PI * 0.05f);
		pBullet->SetRevolution(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DX_PI * 0.01f, 200.0f);
	}
#endif

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pInput[nCnt] != nullptr)
		{
			m_pInput[nCnt]->Update();
		}
	}

	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Update();
	}

	if (m_pFade != nullptr)
	{
		m_pFade->Update();
	}

	if (m_pMode != nullptr)
	{
		m_pMode->Update();
	}
}

//描画処理
void CApplication::Draw(void)
{
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Draw();
	}
}

CRenderer* CApplication::GetRenderer(void)
{
	return m_pRenderer;
}

CInputMouse* CApplication::GetMouse(void)
{
	return m_pMouse;
}

HWND CApplication::GetWindow(void)
{
	return m_hWnd;
}

void CApplication::SetDifficulty(const int difficulty)
{
	m_pScore->SetDifficulty(difficulty);
	m_nDifficulty = difficulty;
}

const int CApplication::GetDifficulty(void)
{
	return m_nDifficulty;
}

void CApplication::SetRemainingLife(const int nLife)
{
	m_pScore->SetLife(nLife);
}

CApplication::Mode CApplication::GetMode(void)
{
	return m_mode;
}

void CApplication::SetMode(Mode mode)
{
	if (m_pMode != nullptr)
	{
		m_pMode->Uninit();
		delete m_pMode;
		m_pMode = nullptr;
	}

	CObject::ReleaseAll();
	CHitbox::ReleaseAll();

	if (m_pSound != nullptr)
	{
		m_pSound->Stop();
	}

	Sleep(150);

	switch (mode)
	{
	case CApplication::Mode_Title:

	{
		m_pMode = CTitle::Create();
		
		if (m_pMode != nullptr)
		{
			m_mode = mode;
		}

		if (m_pRanking != nullptr)
		{
			m_pRanking->SetStage(CStageSelection::stage_Scylla);
		}

		if (m_pSound != nullptr)
		{
			m_pSound->Play(CSound::SOUND_LABEL_BGM_TITLE);
		}
	}

		break;

	case CApplication::Mode_StageSelection:

	{
		m_pMode = CStageSelection::Create();

		if (m_pMode != nullptr)
		{
			m_mode = mode;
		}

		if (m_pRanking != nullptr)
		{
			m_pRanking->SetStage(CStageSelection::stage_Scylla);
		}

		if (m_pSound != nullptr)
		{
			m_pSound->Play(CSound::SOUND_LABEL_BGM_STAGE_SELECTION);
		}
	}

		break;

	case CApplication::Mode_Tutorial:

	{
		m_pMode = CTutorial::Create();

		if (m_pMode != nullptr)
		{
			m_mode = mode;
		}

		if (m_pRanking != nullptr)
		{
			m_pRanking->SetStage(CStageSelection::stage_Scylla);
		}

		if (m_pSound != nullptr)
		{
			m_pSound->Play(CSound::SOUND_LABEL_BGM_STAGE_SELECTION);
		}
	}

	break;

	case CApplication::Mode_Game:

	{
		/*m_pMode = CGameScylla::Create();

		if (m_pMode != nullptr)
		{
			m_pMode->Init();
			m_mode = mode;
		}*/
	}

		break;

	case CApplication::Mode_Game_Scylla:

	{
		m_pMode = CGameScylla::Create();

		if (m_pMode != nullptr)
		{
			m_mode = mode;
		}

		if (m_pScore != nullptr)
		{
			m_pScore->Clear();
			m_pScore->SetBaseScore(200000);
		}

		if (m_pRanking != nullptr)
		{
			m_pRanking->SetStage(CStageSelection::stage_Scylla);
		}

		if (m_pSound != nullptr)
		{
			m_pSound->Play(CSound::SOUND_LABEL_BGM_GAME);
		}
	}

		break;

	case CApplication::Mode_Game_Thanatos:

	{
		m_pMode = CGameThanatos::Create();

		if (m_pMode != nullptr)
		{
			m_mode = mode;
		}

		if (m_pScore != nullptr)
		{
			m_pScore->Clear();
			m_pScore->SetBaseScore(300000);
		}

		if (m_pRanking != nullptr)
		{
			m_pRanking->SetStage(CStageSelection::stage_Thanatos);
		}

		if (m_pSound != nullptr)
		{
			m_pSound->Play(CSound::SOUND_LABEL_BGM_THANATOS);
		}
	}

	break;

	case CApplication::Mode_Game_Pride:

	{
		m_pMode = CGamePride::Create();

		if (m_pMode != nullptr)
		{
			m_mode = mode;
		}

		if (m_pScore != nullptr)
		{
			m_pScore->Clear();
			m_pScore->SetBaseScore(150000);
		}

		if (m_pRanking != nullptr)
		{
			m_pRanking->SetStage(CStageSelection::stage_Pride);
		}

		if (m_pSound != nullptr)
		{
			m_pSound->Play(CSound::SOUND_LABEL_BGM_GAME);
		}
	}

	break;

	case CApplication::Mode_Game_Envy:

	{
		m_pMode = CGameEnvy::Create();

		if (m_pMode != nullptr)
		{
			m_mode = mode;
		}

		if (m_pScore != nullptr)
		{
			m_pScore->Clear();
			m_pScore->SetBaseScore(500000);
		}

		if (m_pRanking != nullptr)
		{
			m_pRanking->SetStage(CStageSelection::stage_Envy);
		}

		if (m_pSound != nullptr)
		{
			m_pSound->Play(CSound::SOUND_LABEL_BGM_GAME);
		}
	}

	break;

	case CApplication::Mode_Game_Wrath:

	{
		m_pMode = CGameWrath::Create();

		if (m_pMode != nullptr)
		{
			m_mode = mode;
		}

		if (m_pScore != nullptr)
		{
			m_pScore->Clear();
			m_pScore->SetBaseScore(500000);
		}

		if (m_pRanking != nullptr)
		{
			m_pRanking->SetStage(CStageSelection::stage_Wrath);
		}

		if (m_pSound != nullptr)
		{
			m_pSound->Play(CSound::SOUND_LABEL_BGM_GAME);
		}
	}

	break;

	case CApplication::Mode_Game_Sloth:

	{
		m_pMode = CGameSloth::Create();

		if (m_pMode != nullptr)
		{
			m_mode = mode;
		}

		if (m_pScore != nullptr)
		{
			m_pScore->Clear();
			m_pScore->SetBaseScore(250000);
		}

		if (m_pRanking != nullptr)
		{
			m_pRanking->SetStage(CStageSelection::stage_Sloth);
		}

		if (m_pSound != nullptr)
		{
			m_pSound->Play(CSound::SOUND_LABEL_BGM_GAME);
		}
	}

	break;

	case CApplication::Mode_Game_Greed:

	{
		m_pMode = CGameGreed::Create();

		if (m_pMode != nullptr)
		{
			m_mode = mode;
		}

		if (m_pScore != nullptr)
		{
			m_pScore->Clear();
			m_pScore->SetBaseScore(350000);
		}

		if (m_pRanking != nullptr)
		{
			m_pRanking->SetStage(CStageSelection::stage_Greed);
		}

		if (m_pSound != nullptr)
		{
			m_pSound->Play(CSound::SOUND_LABEL_BGM_GAME);
		}
	}

	break;

	case CApplication::Mode_Game_Gluttony:

	{
		m_pMode = CGameGluttony::Create();

		if (m_pMode != nullptr)
		{
			m_mode = mode;
		}

		if (m_pScore != nullptr)
		{
			m_pScore->Clear();
			m_pScore->SetBaseScore(250000);
		}

		if (m_pRanking != nullptr)
		{
			m_pRanking->SetStage(CStageSelection::stage_Gluttony);
		}

		if (m_pSound != nullptr)
		{
			m_pSound->Play(CSound::SOUND_LABEL_BGM_GAME);
		}
	}

	break;

	case CApplication::Mode_Result:

	{
		int nScore = m_pScore->GetFinalScore();

		if (m_pRanking != nullptr)
		{
			m_pRanking->SetRanking((CStageSelection::stage)m_pRanking->GetStage(), nScore);
		}

		m_pMode = CResult::Create(nScore);

		if (m_pMode != nullptr)
		{
			m_mode = mode;
		}
	}

		break;

	case CApplication::Mode_Ranking:

	{
		int stage = 0;

		if (m_pRanking != nullptr)
		{
			stage = m_pRanking->GetStage();
		}

		m_pMode = CRankingMode::Create(stage);

		if (m_pMode != nullptr)
		{
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

CRanking* CApplication::GetRanking(void)
{
	return m_pRanking;
}


void CApplication::SetFade(CApplication::Mode mode)
{
	if (m_pFade != nullptr)
	{
		m_pFade->SetFadeOut(mode);
	}
}

void CApplication::SetFade(const bool bFade)
{
	m_bFade = bFade;
}

const bool CApplication::GetFade(void)
{
	return m_bFade;
}