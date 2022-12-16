//=============================================================================
//
// stageSelection.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "stageSelection.h"
#include "application.h"
#include "inputKeyboard.h"
#include "bg.h"
#include "button.h"
#include "Letter.h"
#include "sound.h"
#include "object2D.h"

//=============================================================================
//								静的変数の初期化
//=============================================================================
const char CStageSelection::m_aStage[CStageSelection::stage_Max][24] =			//ステージの名前
{
	{ "scylla" },
	{ "thanatos" },
	{ "pride" },
	{ "envy" },
	{ "wrath" },
	{ "sloth" },
	{ "greed" },
	{ "gluttony" }
};

//コンストラクタ
CStageSelection::CStageSelection()
{
	//メンバー変数をクリアする

	m_nSelectedStage = 0;
	m_nCntDelay = 0;
	m_nDifficulty = 0;

	m_pBg = nullptr;

	for (int nCnt = 0; nCnt < button_Max; nCnt++)
	{
		m_pButton[nCnt] = nullptr;
	}

	for (int nCnt = 0; nCnt < 24; nCnt++)
	{
		m_pStageName[nCnt] = nullptr;
	}

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_pLateralButton[nCnt] = nullptr;
		m_pLateralIcon[nCnt] = nullptr;
	}

	for (int nCnt = 0; nCnt < 16; nCnt++)
	{
		m_pStageSelectTitle[nCnt] = nullptr;
	}

	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		m_pDifficultyIcon[nCnt] = nullptr;
	}
}

//デストラクタ
CStageSelection::~CStageSelection()
{

}

//初期化処理
HRESULT CStageSelection::Init(void)
{
	//メンバー変数を初期化する

	m_nSelectedStage = 0;
	m_nCntDelay = 0;
	m_nDifficulty = 1;

	m_pBg = nullptr;

	for (int nCnt = 0; nCnt < button_Max; nCnt++)
	{
		m_pButton[nCnt] = nullptr;
	}

	for (int nCnt = 0; nCnt < 24; nCnt++)
	{
		m_pStageName[nCnt] = nullptr;
	}

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_pLateralButton[nCnt] = nullptr;
		m_pLateralIcon[nCnt] = nullptr;
	}

	for (int nCnt = 0; nCnt < 16; nCnt++)
	{
		m_pStageSelectTitle[nCnt] = nullptr;
	}

	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		m_pDifficultyIcon[nCnt] = nullptr;
	}

	return S_OK;
}

//終了処理
void CStageSelection::Uninit(void)
{
	//背景の破棄
	if (m_pBg != nullptr)
	{//nullチェック
		m_pBg->Release();		//メモリを解放する
		m_pBg = nullptr;		//ポインタをnullにする
	}

	//ボタンの破棄
	for (int nCnt = 0; nCnt < button_Max; nCnt++)
	{
		if (m_pButton[nCnt] != nullptr)
		{//nullチェック
			m_pButton[nCnt]->Uninit();		//メモリを解放する
			m_pButton[nCnt] = nullptr;		//ポインタをnullにする
		}
	}

	//ステージの名前の破棄
	for (int nCnt = 0; nCnt < 24; nCnt++)
	{
		if (m_pStageName[nCnt] != nullptr)
		{//nullチェック
			m_pStageName[nCnt]->Release();	//メモリを解放する
			m_pStageName[nCnt] = nullptr;	//ポインタをnullにする
		}
	}

	//ボタンとアイコンの破棄
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pLateralButton[nCnt] != nullptr)
		{//nullチェック
			m_pLateralButton[nCnt]->Uninit();	//メモリを解放する
			m_pLateralButton[nCnt] = nullptr;	//ポインタをnullにする
		}

		if (m_pLateralIcon[nCnt] != nullptr)
		{//nullチェック
			m_pLateralIcon[nCnt]->Release();	//メモリを解放する
			m_pLateralIcon[nCnt] = nullptr;		//ポインタをnullにする
		}
	}

	//文字列の破棄
	for (int nCnt = 0; nCnt < 16; nCnt++)
	{
		if (m_pStageSelectTitle[nCnt] != nullptr)
		{//nullチェック
			m_pStageSelectTitle[nCnt]->Release();	//メモリを解放する
			m_pStageSelectTitle[nCnt] = nullptr;	//ポインタをnullにする
		}
	}

	//難易度UIの破棄
	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		if (m_pDifficultyIcon[nCnt] != nullptr)
		{
			m_pDifficultyIcon[nCnt]->Release();		//メモリを解放する
			m_pDifficultyIcon[nCnt] = nullptr;		//ポインタをnullにする
		}
	}
}

//更新処理
void CStageSelection::Update(void)
{
	if (m_nCntDelay >= 30)
	{//フェードが終わったら

		bool bDx = false;
		bool bSx = false;

		{
			//マウスカーソルの位置を取得して、変換する
			POINT pt;
			GetCursorPos(&pt);
			HWND wnd = CApplication::GetWindow();
			ScreenToClient(wnd, &pt);
			D3DXVECTOR3 MousePos;
			MousePos.x = (float)pt.x;
			MousePos.y = (float)pt.y;
			MousePos.z = 0.0f;

			//========================================================================================================================
			//				ボタンの更新処理。マウスカーソルと重なったら、色を変えて、押されたらかどうかを取得する
			if (m_pLateralButton[0] != nullptr)
			{
				D3DXVECTOR2 size = m_pLateralButton[0]->GetSize();
				D3DXVECTOR3 pos = m_pLateralButton[0]->GetPos();

				float fLeft, fRight, fTop, fBottom;

				fLeft = pos.x - size.x;
				fRight = pos.x + size.x;
				fTop = pos.y - size.y;
				fBottom = pos.y + size.y;

				if (MousePos.x > fLeft && MousePos.x < fRight && MousePos.y > fTop && MousePos.y < fBottom)
				{
					m_pLateralIcon[0]->SetColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
				}
				else
				{
					m_pLateralIcon[0]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				}

				m_pLateralButton[0]->Update();
				bSx = m_pLateralButton[0]->GetTriggerState();
			}
			if (m_pLateralButton[1] != nullptr)
			{
				D3DXVECTOR2 size = m_pLateralButton[1]->GetSize();
				D3DXVECTOR3 pos = m_pLateralButton[1]->GetPos();

				float fLeft, fRight, fTop, fBottom;

				fLeft = pos.x - size.x;
				fRight = pos.x + size.x;
				fTop = pos.y - size.y;
				fBottom = pos.y + size.y;

				if (MousePos.x > fLeft && MousePos.x < fRight && MousePos.y > fTop && MousePos.y < fBottom)
				{
					m_pLateralIcon[1]->SetColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
				}
				else
				{
					m_pLateralIcon[1]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				}

				m_pLateralButton[1]->Update();
				bDx = m_pLateralButton[1]->GetTriggerState();
			}
		}
		//========================================================================================================================
		//========================================================================================================================
		//			右/左アローボタン、A/Dボタン、又は左右のボタンが押されたら、選択されているステージを変える
		if (CInputKeyboard::GetKeyboardTrigger(DIK_RIGHT) || CInputKeyboard::GetKeyboardTrigger(DIK_D) || bDx)
		{
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_CLICK);

			m_nSelectedStage++;
			m_nCntDelay = 0;

			if (m_nSelectedStage >= stage_Max)
			{
				m_nSelectedStage = 0;
			}

			UpdateMenu();

		}
		else if (CInputKeyboard::GetKeyboardTrigger(DIK_LEFT) || CInputKeyboard::GetKeyboardTrigger(DIK_A) || bSx)
		{
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_CLICK);

			m_nSelectedStage--;
			m_nCntDelay = 0;

			if (m_nSelectedStage < 0)
			{
				m_nSelectedStage = stage_Max - 1;
			}

			UpdateMenu();
		}
		//========================================================================================================================
		//========================================================================================================================
		//									Q/Eボタンが押されたら、難易度を変える
		if (CInputKeyboard::GetKeyboardTrigger(DIK_Q))
		{
			int a = 0;

			if (m_nDifficulty > 1)
			{
				m_pDifficultyIcon[m_nDifficulty]->SetAnimPattern(0);

				m_nDifficulty--;
			}
		}
		else if (CInputKeyboard::GetKeyboardTrigger(DIK_E))
		{
			int a = 0;

			if (m_nDifficulty < 3)
			{
				m_nDifficulty++;
				m_pDifficultyIcon[m_nDifficulty]->SetAnimPattern(1);
			}
		}
		//========================================================================================================================
	}
	else
	{//まだフェード中だったら
		m_nCntDelay++;				//カウンターを更新する
	}

	//============================================================================================================================
	//							プレイボタンが押されたら、選択されているステージモードに切り替える
	if (m_pButton[button_play] != nullptr)
	{
		m_pButton[button_play]->Update();

		if (m_pButton[button_play]->GetTriggerState())
		{
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_CLICK);

			switch (m_nSelectedStage)
			{
			case stage_Scylla:

			{
				CApplication::SetFade(CApplication::Mode_Game_Scylla);
			}

			break;

			case stage_Thanatos:

			{
				CApplication::SetFade(CApplication::Mode_Game_Thanatos);
			}

			break;

			case stage_Pride:

			{
				CApplication::SetFade(CApplication::Mode_Game_Pride);
			}

			break;

			case stage_Envy:

			{
				CApplication::SetFade(CApplication::Mode_Game_Envy);
			}

			break;

			case stage_Wrath:

			{
				CApplication::SetFade(CApplication::Mode_Game_Wrath);
			}

			break;

			case stage_Sloth:

			{
				CApplication::SetFade(CApplication::Mode_Game_Sloth);
			}

			break;

			case stage_Greed:

			{
				CApplication::SetFade(CApplication::Mode_Game_Greed);
			}

			break;

			case stage_Gluttony:

			{
				CApplication::SetFade(CApplication::Mode_Game_Gluttony);
			}

			break;

			default:
				break;
			}

			CApplication::SetDifficulty(m_nDifficulty);

			return;
		}
	}
	//============================================================================================================================
	//============================================================================================================================
	//							ランキングボタンが押されたら、ランキングモードに切り替える
	if (m_pButton[button_leaderboard] != nullptr)
	{
		m_pButton[button_leaderboard]->Update();

		if (m_pButton[button_leaderboard]->GetTriggerState())
		{
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_CLICK);

			CApplication::SetFade(CApplication::Mode_Ranking);
			return;
		}
	}
	//============================================================================================================================
	//============================================================================================================================
	//							タイトルボタンが押されたら、タイトルモードに切り替える
	if (m_pButton[button_title] != nullptr)
	{
		m_pButton[button_title]->Update();

		if (m_pButton[button_title]->GetTriggerState())
		{
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_CLICK);

			CApplication::SetFade(CApplication::Mode_Title);
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
CStageSelection* CStageSelection::Create(void)
{
	CStageSelection* pStage = new CStageSelection;			//インスタンスを生成する

	if (pStage == nullptr)
	{//生成できなかったら、nullを返す
		return nullptr;
	}

	//背景を生成して、生成出来たら、必要なパラメータを設定する
	pStage->m_pBg = CBg::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));

	if (pStage->m_pBg)
	{
		pStage->m_pBg->SetTexture(CObject::TextureSeaBG);
		pStage->m_pBg->SetTextureParameter(2, 1, 2, 30);
		pStage->m_nDifficulty = 1;
	}

	char Str[16] = "stage selection";

	for (int nCnt = 0; nCnt < 16; nCnt++)
	{
		if (pStage->m_pStageSelectTitle[nCnt] == nullptr)
		{
			//文字列の生成
			pStage->m_pStageSelectTitle[nCnt] = CLetter::Create(D3DXVECTOR3(40.0f + 50.0f * nCnt, 40.0f, 0.0f), D3DXVECTOR2(25.0f, 25.0f), Str[nCnt]);

			if (pStage->m_pStageSelectTitle[nCnt] != nullptr)
			{//文字が生成出来たら、必要なパラメータを設定する
				pStage->m_pStageSelectTitle[nCnt]->SetPriority(5);
				pStage->m_pStageSelectTitle[nCnt]->SetColor(D3DXCOLOR(0.25f, 1.0f, 0.6f, 1.0f));
				pStage->m_pStageSelectTitle[nCnt]->SetObjType(CObject::OBJTYPE_MENU);
			}
		}
	}

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		//難易度UIの生成
		pStage->m_pDifficultyIcon[(4 * nCnt)] = CObject_2D::Create();

		if (pStage->m_pDifficultyIcon[(4 * nCnt)] != nullptr)
		{//生成出来たら、必要なパラメータを設定する
			pStage->m_pDifficultyIcon[(4 * nCnt)]->SetPos(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f - 125.0f + 250.0f * nCnt, (float)SCREEN_HEIGHT * 0.5f - 100.0f, 0.0f));
			pStage->m_pDifficultyIcon[(4 * nCnt)]->SetSize(D3DXVECTOR2(20.0f, 53.0f));
			pStage->m_pDifficultyIcon[(4 * nCnt)]->SetTextureParameter(2, 2, 1, 15);
			pStage->m_pDifficultyIcon[(4 * nCnt)]->SetStartingRot(D3DX_PI * 0.5f);
			pStage->m_pDifficultyIcon[(4 * nCnt)]->SetPriority(5);
		}
	}

	pStage->m_pDifficultyIcon[0]->SetTexture(CObject::TextureLateralQIcon);		//難易度UIのテクスチャの設定
	pStage->m_pDifficultyIcon[4]->SetTexture(CObject::TextureLateralEIcon);		//難易度UIのテクスチャの設定

	for (int nCnt = 1; nCnt < 4; nCnt++)
	{
		pStage->m_pDifficultyIcon[nCnt] = CObject_2D::Create();

		if (pStage->m_pDifficultyIcon[nCnt] != nullptr)
		{
			pStage->m_pDifficultyIcon[nCnt]->SetPos(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f - 100.0f + 50.0f * nCnt, (float)SCREEN_HEIGHT * 0.5f - 90.0f, 0.0f));
			pStage->m_pDifficultyIcon[nCnt]->SetSize(D3DXVECTOR2(25.0f, 25.0f));
			pStage->m_pDifficultyIcon[nCnt]->SetTexture(CObject::TextureDifficultyIcon);
			pStage->m_pDifficultyIcon[nCnt]->SetTextureParameter(1, 2, 1, INT_MAX);
			pStage->m_pDifficultyIcon[nCnt]->SetStartingRot(D3DX_PI * 0.5f);
			pStage->m_pDifficultyIcon[nCnt]->SetPriority(5);
		}
	}

	pStage->m_pDifficultyIcon[1]->SetAnimPattern(1);

	//UIの生成
	CObject_2D* pLogo = CObject_2D::Create();

	if (pLogo)
	{//生成出来たら、必要なパラメータを設定する
		pLogo->SetPos(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f + 280.0f, (float)SCREEN_HEIGHT * 0.5f - 90.0f, 0.0f));
		pLogo->SetSize(D3DXVECTOR2(80.0f, 40.0f));
		pLogo->SetTexture(CObject::TextureDifficultyLogo);
		pLogo->SetTextureParameter(1, 1, 1, INT_MAX);
		pLogo->SetStartingRot(D3DX_PI * 0.5f);
		pLogo->SetPriority(5);
	}

	//ステージの名前の生成
	char aStrg[24] = {};
	strcpy(aStrg, m_aStage[pStage->m_nSelectedStage]);

	for (int nCnt = 0; nCnt < 24; nCnt++)
	{
		if (aStrg[nCnt] != ' ' && pStage->m_pStageName[nCnt] == nullptr)
		{
			pStage->m_pStageName[nCnt] = CLetter::Create(D3DXVECTOR3(((float)SCREEN_WIDTH * 0.35f) + 60.0f * nCnt, (float)SCREEN_HEIGHT * 0.2f, 0.0f), D3DXVECTOR2(50.0f * 0.5f, 50.0f * 0.5f), aStrg[nCnt]);

			if (pStage->m_pStageName[nCnt] != nullptr)
			{//生成出来たら、必要なパラメータを設定する

				pStage->m_pStageName[nCnt]->SetPriority(5);
				pStage->m_pStageName[nCnt]->SetColor(D3DXCOLOR(1.0f, 8.0f, 0.0f, 1.0f));
				pStage->m_pStageName[nCnt]->SetObjType(CObject::OBJTYPE_MENU);
			}
		}
	}

	//ボタンを生成して、出来たら、必要なパラメータの設定する
	char aButton[CStageSelection::button_Max][24] = { "play" , "leaderboard", "title"};

	for (int nCnt = 0; nCnt < CStageSelection::button_Max; nCnt++)
	{
		pStage->m_pButton[nCnt] = CButton::Create(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.6f + 100.0f * nCnt, 0.0f), D3DXVECTOR2(280.0f, 55.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), aButton[nCnt]);
	}

	pStage->m_pLateralButton[0] = CButton::Create(D3DXVECTOR3(150.0f, (float)SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR2(100.0f, 100.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), " ");

	if (pStage->m_pLateralButton[0])
	{
		pStage->m_pLateralIcon[0] = CLetter::Create(D3DXVECTOR3(150.0f, (float)SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR2(100.0f, 100.0f), 0);
		pStage->m_pLateralIcon[0]->SetAnimPattern(13);
	}

	pStage->m_pLateralButton[1] = CButton::Create(D3DXVECTOR3((float)SCREEN_WIDTH - 150.0f, (float)SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR2(100.0f, 100.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), " ");
	
	if (pStage->m_pLateralButton[1])
	{
		pStage->m_pLateralIcon[1] = CLetter::Create(D3DXVECTOR3((float)SCREEN_WIDTH - 150.0f, (float)SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR2(100.0f, 100.0f), 0);
		pStage->m_pLateralIcon[1]->SetAnimPattern(14);
	}

	return pStage;				//生成したインスタンスを返す
}



//=============================================================================
//
//							プライベート関数
//
//=============================================================================



void CStageSelection::UpdateMenu(void)
{
	char aStrg[24] = {};
	strcpy(aStrg, m_aStage[m_nSelectedStage]);
	D3DXCOLOR col = m_pStageName[0]->GetColor();

	for (int nCnt = 0; nCnt < 24; nCnt++)
	{
		if (m_pStageName[nCnt] != nullptr)
		{
			m_pStageName[nCnt]->Release();
			m_pStageName[nCnt] = nullptr;
		}

		if (aStrg[nCnt] != ' ' && m_pStageName[nCnt] == nullptr)
		{
			m_pStageName[nCnt] = CLetter::Create(D3DXVECTOR3(((float)SCREEN_WIDTH * 0.35f) + 60.0f * nCnt, (float)SCREEN_HEIGHT * 0.2f, 0.0f), D3DXVECTOR2(50.0f * 0.5f, 50.0f * 0.5f), aStrg[nCnt]);

			if (m_pStageName[nCnt] != nullptr)
			{
				m_pStageName[nCnt]->SetPriority(5);
				m_pStageName[nCnt]->SetColor(col);
				m_pStageName[nCnt]->SetObjType(CObject::OBJTYPE_MENU);
			}
		}
	}

	CObject::TextType aText[stage_Max] = { CObject::TextureSeaBG, CObject::TextureThanatosBG , CObject::TexturePrideBg,  CObject::TextureEnvyBg, CObject::TextureWrathBg, CObject::TextureSlothBg, CObject::TextureGreedBg, CObject::TextureGluttonyBg};

	if (m_pBg != nullptr)
	{
		m_pBg->SetTexture(aText[m_nSelectedStage]);

		if (m_nSelectedStage == stage_Scylla)
		{
			m_pBg->SetTextureParameter(2, 1, 2, 30);
			m_pBg->SetAnimPattern(0);
		}
		else if (m_nSelectedStage == stage_Wrath)
		{
			m_pBg->SetTextureParameter(1, 1, 2, INT_MAX);
			m_pBg->SetAnimPattern(1);
		}
		else
		{
			m_pBg->SetTextureParameter(1, 1, 1, INT_MAX);
			m_pBg->SetAnimPattern(0);
		}
	}
}