//=============================================================================
//
// rankingMode.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "rankingMode.h"
#include "Letter.h"
#include "button.h"
#include "inputKeyboard.h"
#include "application.h"
#include "bg.h"
#include "ranking.h"
#include "sound.h"

//コンストラクタ
CRankingMode::CRankingMode()
{
	//メンバー変数をクリアする
	m_nSelectedStage = 0;
	m_nCntDelay = 0;

	for (int nCnt = 0; nCnt < 24; nCnt++)
	{
		m_pStageName[nCnt] = nullptr;
	}

	for (int nCnt2 = 0; nCnt2 < MaxRank; nCnt2++)
	{
		for (int nCnt = 0; nCnt < MaxDigit; nCnt++)
		{
			m_pRank[nCnt2][nCnt] = nullptr;
		}
	}

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_pLateralIcon[nCnt] = nullptr;
		m_pLateralButton[nCnt] = nullptr;
	}

	m_pBg = nullptr;
}

//デストラクタ
CRankingMode::~CRankingMode()
{

}

//初期化処理
HRESULT CRankingMode::Init(void)
{
	//メンバー変数を初期化する
	m_nSelectedStage = 0;
	m_nCntDelay = 0;

	for (int nCnt = 0; nCnt < 24; nCnt++)
	{
		m_pStageName[nCnt] = nullptr;
	}

	for (int nCnt2 = 0; nCnt2 < MaxRank; nCnt2++)
	{
		for (int nCnt = 0; nCnt < MaxDigit; nCnt++)
		{
			m_pRank[nCnt2][nCnt] = nullptr;
		}
	}

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_pLateralIcon[nCnt] = nullptr;
		m_pLateralButton[nCnt] = nullptr;
	}

	m_pBg = nullptr;

	//UIの生成
	CObject_2D* pObj = CObject_2D::Create();

	//生成出来たら、必要なパラメータを設定する
	if (pObj)
	{
		pObj->SetPos(D3DXVECTOR3(1000.0f, 600.0f, 0.0f));
		pObj->SetSize(D3DXVECTOR2(100.0f, 65.4f));
		pObj->SetTexture(CObject::TexturePressSpaceIcon);
		pObj->SetTextureParameter(2, 2, 1, 30);
		pObj->SetStartingRot(D3DX_PI * 0.5f);
	}

	return S_OK;
}

//終了処理
void CRankingMode::Uninit(void)
{
	//ステージの名前の破棄
	for (int nCnt = 0; nCnt < 24; nCnt++)
	{
		if (m_pStageName[nCnt] != nullptr)
		{//nullチェック
			m_pStageName[nCnt]->Release();			//メモリを解放する
			m_pStageName[nCnt] = nullptr;			//ポインタをnullにする
		}
	}

	//スコアの破棄
	for (int nCnt2 = 0; nCnt2 < MaxRank; nCnt2++)
	{
		for (int nCnt = 0; nCnt < MaxDigit; nCnt++)
		{
			if (m_pRank[nCnt2][nCnt] != nullptr)
			{//nullチェック
				m_pRank[nCnt2][nCnt]->Release();	//メモリを解放する
				m_pRank[nCnt2][nCnt] = nullptr;		//ポインタをnullにする
			}
		}
	}

	//ボタンとUIの破棄
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pLateralIcon[nCnt] != nullptr)
		{//nullチェック
			m_pLateralIcon[nCnt]->Release();		//メモリを解放する	
			m_pLateralIcon[nCnt] = nullptr;			//ポインタをnullにする
		}

		if (m_pLateralButton[nCnt] != nullptr)
		{//nullチェック
			m_pLateralButton[nCnt]->Uninit();		//メモリを解放する
			m_pLateralButton[nCnt] = nullptr;		//ポインタをnullにする
		}
	}

	//背景の破棄
	if (m_pBg != nullptr)
	{//nullチェック
		m_pBg->Release();			//メモリを解放する
		m_pBg = nullptr;			//ポインタをnullにする
	}

}

//更新処理
void CRankingMode::Update(void)
{
	if (m_nCntDelay >= 30)
	{//フェード中ではなかったら

		bool bDx = false;
		bool bSx = false;

		//=========================================================================================================================
		//								ボタンを更新して、押されたかどうかを取得する
		if (m_pLateralButton[0] != nullptr)
		{
			m_pLateralButton[0]->Update();
			bSx = m_pLateralButton[0]->GetTriggerState();
		}
		if (m_pLateralButton[1] != nullptr)
		{
			m_pLateralButton[1]->Update();
			bDx = m_pLateralButton[1]->GetTriggerState();
		}
		//=========================================================================================================================
		//=========================================================================================================================
		//				右/左アローボタン、A/Dボタン、又は左右のボタンが押されたら、選択されている画面を変える
		if (CInputKeyboard::GetKeyboardTrigger(DIK_RIGHT) || CInputKeyboard::GetKeyboardTrigger(DIK_D) || bDx)
		{
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_CLICK);

			m_nSelectedStage++;
			m_nCntDelay = 0;

			if (m_nSelectedStage >= CStageSelection::stage_Max)
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
				m_nSelectedStage = CStageSelection::stage_Max - 1;
			}

			UpdateMenu();
		}
		//=========================================================================================================================
	}
	else
	{//フェード中だったら、カウンターをインクリメントする
		m_nCntDelay++;
	}

	//スペースキー、又はエンターキーが押されたら、タイトル画面に切り替える
	if (CInputKeyboard::GetKeyboardTrigger(DIK_SPACE) || CInputKeyboard::GetKeyboardTrigger(DIK_RETURN))
	{
		CApplication::SetFade(CApplication::Mode_Title);
	}
}



//=============================================================================
//
//								静的関数
//
//=============================================================================



//生成処理
CRankingMode* CRankingMode::Create(const int nStage)
{
	CRankingMode* pStage = new CRankingMode;			//インスタンスを生成する

	if (FAILED(pStage->Init()))
	{//初期化処理
		return nullptr;
	}

	pStage->m_nSelectedStage = nStage;		//選択されているステージの設定

	//背景の生成
	pStage->m_pBg = CBg::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));

	CObject::TextType aText[CStageSelection::stage_Max] = { CObject::TextureSeaBG, CObject::TextureThanatosBG , CObject::TexturePrideBg,  CObject::TextureEnvyBg, CObject::TextureWrathBg, CObject::TextureSlothBg, CObject::TextureGreedBg, CObject::TextureGluttonyBg };

	if (pStage->m_pBg != nullptr)
	{//生成出来たら、必要なパラメータの設定する
		pStage->m_pBg->SetTexture(aText[pStage->m_nSelectedStage]);

		if (pStage->m_nSelectedStage == CStageSelection::stage_Scylla)
		{
			pStage->m_pBg->SetTextureParameter(2, 1, 2, 30);
			pStage->m_pBg->SetAnimPattern(0);
		}
		else if (pStage->m_nSelectedStage == CStageSelection::stage_Wrath)
		{
			pStage->m_pBg->SetTextureParameter(1, 1, 2, INT_MAX);
			pStage->m_pBg->SetAnimPattern(0);
		}
		else
		{
			pStage->m_pBg->SetTextureParameter(1, 1, 1, INT_MAX);
			pStage->m_pBg->SetAnimPattern(0);
		}
	}

	//ステージの名前の設定
	char aStrg[24] = {};
	strcpy(aStrg, CStageSelection::m_aStage[pStage->m_nSelectedStage]);

	for (int nCnt = 0; nCnt < 24; nCnt++)
	{
		if (aStrg[nCnt] != ' ' && pStage->m_pStageName[nCnt] == nullptr)
		{
			//ステージの名前の生成
			pStage->m_pStageName[nCnt] = CLetter::Create(D3DXVECTOR3(((float)SCREEN_WIDTH * 0.35f) + 60.0f * nCnt, (float)SCREEN_HEIGHT * 0.1f, 0.0f), D3DXVECTOR2(50.0f * 0.5f, 50.0f * 0.5f), aStrg[nCnt]);

			if (pStage->m_pStageName[nCnt] != nullptr)
			{//文字が生成出来たら、必要なパラメータを設定する

				pStage->m_pStageName[nCnt]->SetPriority(5);
				pStage->m_pStageName[nCnt]->SetColor(D3DXCOLOR(1.0f, 8.0f, 0.0f, 1.0f));
				pStage->m_pStageName[nCnt]->SetObjType(CObject::OBJTYPE_MENU);
			}
		}
	}

	//保存されたランキングを取得する
	int* pRanking = CApplication::GetRanking()->GetRanking((CStageSelection::stage)nStage);

	//スコアを配列に変換する
	for (int i = 0; i < MaxRank; i++)
	{

		int aDigit[MaxDigit] = {};

		int nR = pRanking[i];

		if (pRanking[i] > 0)
		{
			for (int nCnt = 0; nCnt < MaxDigit; nCnt++)
			{
				int nDiv = 1;

				for (int nCnt2 = nCnt; nCnt2 < MaxDigit - 1; nCnt2++)
				{
					nDiv *= 10;
				}

				aDigit[nCnt] = (nR / nDiv);
				nR = nR % nDiv;
			}
		}
		else
		{
			for (int nCnt = 0; nCnt < MaxDigit; nCnt++)
			{
				aDigit[nCnt] = 0;
			}
		}


		for (int nCnt = 0; nCnt < MaxDigit; nCnt++)
		{
			//スコアの桁を生成する
			pStage->m_pRank[i][nCnt] = CLetter::Create(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f - 45.0f * (MaxDigit * 0.5f) + 45.0f * nCnt, (float)SCREEN_HEIGHT * 0.25f + (float)SCREEN_HEIGHT * 0.15f * i, 0.0f), D3DXVECTOR2(40.0f, 40.0f), aDigit[nCnt]);

			if (pStage->m_pRank[i][nCnt] != nullptr)
			{//生成出来たら、必要なパラメータを設定する

				pStage->m_pRank[i][nCnt]->SetPriority(4);
				pStage->m_pRank[i][nCnt]->SetColor(D3DXCOLOR(0.0f, 1.0f, 0.75f, 1.0f));
			}
		}
	}


	//ボタンの生成
	pStage->m_pLateralButton[0] = CButton::Create(D3DXVECTOR3(150.0f, (float)SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR2(100.0f, 100.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), " ");
	
	if (pStage->m_pLateralButton[0])
	{//生成出来たら、必要なパラメータを設定する
		pStage->m_pLateralIcon[0] = CLetter::Create(D3DXVECTOR3(150.0f, (float)SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR2(100.0f, 100.0f), 0);
		pStage->m_pLateralIcon[0]->SetAnimPattern(13);
	}

	pStage->m_pLateralButton[1] = CButton::Create(D3DXVECTOR3((float)SCREEN_WIDTH - 150.0f, (float)SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR2(100.0f, 100.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), " ");
	
	if (pStage->m_pLateralButton[1])
	{//生成出来たら、必要なパラメータを設定する
		pStage->m_pLateralIcon[1] = CLetter::Create(D3DXVECTOR3((float)SCREEN_WIDTH - 150.0f, (float)SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR2(100.0f, 100.0f), 0);
		pStage->m_pLateralIcon[1]->SetAnimPattern(14);
	}

	CApplication::GetSound()->Play(CSound::SOUND_LABEL_BGM_RESULTS);			//BGMの設定

	return pStage;				//生成したインスタンスを返す
}



//=============================================================================
//
//								プライベート関数
//
//=============================================================================



//メニューの更新処理
void CRankingMode::UpdateMenu(void)
{
	char aStrg[24] = {};
	strcpy(aStrg, CStageSelection::m_aStage[m_nSelectedStage]);		//ステージの名前をコピーする
	D3DXCOLOR col = m_pStageName[0]->GetColor();					//色の取得

	for (int nCnt = 0; nCnt < 24; nCnt++)
	{
		//ステージの名前を破棄する
		if (m_pStageName[nCnt] != nullptr)
		{
			m_pStageName[nCnt]->Release();
			m_pStageName[nCnt] = nullptr;
		}

		if (aStrg[nCnt] != ' ' && m_pStageName[nCnt] == nullptr)
		{
			//現在のステージの名前を生成する
			m_pStageName[nCnt] = CLetter::Create(D3DXVECTOR3(((float)SCREEN_WIDTH * 0.35f) + 60.0f * nCnt, (float)SCREEN_HEIGHT * 0.1f, 0.0f), D3DXVECTOR2(50.0f * 0.5f, 50.0f * 0.5f), aStrg[nCnt]);

			if (m_pStageName[nCnt] != nullptr)
			{//生成出来たら、必要なパラメータを設定する
				m_pStageName[nCnt]->SetPriority(5);
				m_pStageName[nCnt]->SetColor(col);
				m_pStageName[nCnt]->SetObjType(CObject::OBJTYPE_MENU);
			}
		}
	}

	//背景のテクスチャ
	CObject::TextType aText[CStageSelection::stage_Max] = { CObject::TextureSeaBG, CObject::TextureThanatosBG , CObject::TexturePrideBg,  CObject::TextureEnvyBg, CObject::TextureWrathBg, CObject::TextureSlothBg, CObject::TextureGreedBg, CObject::TextureGluttonyBg };

	if (m_pBg != nullptr)
	{//nullチェック

		//選択されているステージによって、テクスチャとテクスチャパラメータの設定
		m_pBg->SetTexture(aText[m_nSelectedStage]);				

		if (m_nSelectedStage == CStageSelection::stage_Scylla)
		{
			m_pBg->SetTextureParameter(2, 1, 2, 30);
			m_pBg->SetAnimPattern(0);
		}
		else if (m_nSelectedStage == CStageSelection::stage_Wrath)
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

	//ランキングの取得
	int* pRanking = CApplication::GetRanking()->GetRanking((CStageSelection::stage)m_nSelectedStage);

	//取得したスコアを配列に変換する
	for (int nCnt = 0; nCnt < MaxRank; nCnt++)
	{

		int aDigit[MaxDigit] = {};

		int nR = pRanking[nCnt];

		if (pRanking[nCnt] > 0)
		{
			for (int nCnt = 0; nCnt < MaxDigit; nCnt++)
			{
				int nDiv = 1;

				for (int nCnt2 = nCnt; nCnt2 < MaxDigit - 1; nCnt2++)
				{
					nDiv *= 10;
				}

				aDigit[nCnt] = (nR / nDiv);
				nR = nR % nDiv;
			}
		}
		else
		{
			for (int nCnt = 0; nCnt < MaxDigit; nCnt++)
			{
				aDigit[nCnt] = 0;
			}
		}

		for (int i = 0; i < MaxDigit; i++)
		{//スコアのアニメションパターンを設定する
			m_pRank[nCnt][i]->SetAnimPattern(aDigit[i]);
		}
	}
}