//=============================================================================
//
// result.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "result.h"
#include "letter.h"
#include "inputMouse.h"
#include "application.h"
#include "inputKeyboard.h"
#include "sound.h"
#include "bg.h"

//コンストラクタ
CResult::CResult()
{
	//メンバー変数をクリアする
	m_nDelay = 0;
	m_fAnim = 0.0f;

	for (int nCnt = 0; nCnt < MaxDigit; nCnt++)
	{
		m_pScore[nCnt] = nullptr;
	}

	for (int nCnt = 0; nCnt < 12; nCnt++)
	{
		m_pUI[nCnt] = nullptr;
	}
}

//デストラクタ
CResult::~CResult()
{

}

//初期化処理
HRESULT CResult::Init(void)
{
	//メンバー変数を初期化する
	m_nDelay = 0;
	m_fAnim = -0.01f;

	for (int nCnt = 0; nCnt < MaxDigit; nCnt++)
	{
		m_pScore[nCnt] = nullptr;
	}

	for (int nCnt = 0; nCnt < 12; nCnt++)
	{
		m_pUI[nCnt] = nullptr;
	}

	return S_OK;
}

//終了処理
void CResult::Uninit(void)
{
	//スコアの桁の破棄
	for (int nCnt = 0; nCnt < MaxDigit; nCnt++)
	{
		if (m_pScore[nCnt] != nullptr)
		{//nullチェック
			m_pScore[nCnt]->Release();		//メモリを解放する
			m_pScore[nCnt] = nullptr;		//ポインタをnullにする
		}
	}

	//UIの破棄
	for (int nCnt = 0; nCnt < 12; nCnt++)
	{
		if (m_pUI[nCnt] != nullptr)
		{//nullチェック
			m_pUI[nCnt]->Release();			//メモリを解放する
			m_pUI[nCnt] = nullptr;			//ポインタをnullにする
		}
	}
}

//更新処理
void CResult::Update(void)
{
	if (m_nDelay >= 30)
	{//フェード中ではなかったら

		if (CApplication::GetMouse()->GetMouseLeftClick() || CInputKeyboard::GetKeyboardTrigger(DIK_RETURN) || CInputKeyboard::GetKeyboardTrigger(DIK_SPACE))
		{//マウスの左ボタン、エンターキー、又はスペースキーが押されたら、ランキング画面に切り替える

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_CLICK);
			CApplication::SetFade(CApplication::Mode_Ranking);
			return;
		}
	}
	else
	{//フェード中だったら、カウンターをインクリメントする

		m_nDelay++;
	}

	for (int nCnt = 0; nCnt < MaxDigit; nCnt++)
	{
		//スコアのアニメーション処理
		if (m_pScore[nCnt] != nullptr)
		{//nullチェック

			D3DXCOLOR col = m_pScore[nCnt]->GetColor();		//現在の色の取得

			//色の更新
			col.g += m_fAnim;
			col.r -= m_fAnim;

			if (col.g >= 1.0f || col.g <= 0.0f)
			{//1.0f以上又は0.0以下になかったら、アニメーション用のカウンターを逆にする
				m_fAnim *= -1.0f;
			}
			else
			{
				m_pScore[nCnt]->SetColor(col);			//色の設定
			}			
		}
	}
}



//=============================================================================
//
//								静的関数
//
//=============================================================================



//生成処理
CResult* CResult::Create(const int nScore)
{
	CResult* pResult = new CResult;				//インスタンスを生成する

	if (FAILED(pResult->Init()))
	{//初期化処理
		return nullptr;
	}

	//背景を生成する
	CBg* pBg = CBg::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));

	if (pBg != nullptr)
	{//生成出来たら、必要なパラメータを設定する
		pBg->SetTexture(CObject::TextureMenuBg);
	}	pBg->SetTextureParameter(1, 1, 1, INT_MAX);

	char aStr[12] = "your score";
	int nLenght = strlen(aStr);

	for (int nCnt = 0; nCnt < 12; nCnt++)
	{
		//UIの生成
		pResult->m_pUI[nCnt] = CLetter::Create(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f - 85.0f * (nLenght * 0.5f) + 85.0f * nCnt, (float)SCREEN_HEIGHT * 0.35f, 0.0f), D3DXVECTOR2(50.0f, 50.0f), aStr[nCnt]);

		if (pResult->m_pUI[nCnt] != nullptr)
		{//生成出来たら、必要なパラメータを設定する
			pResult->m_pUI[nCnt]->SetColor(D3DXCOLOR(1.0f, 0.75f, 0.20f, 1.0f));
		}
	}

	//プレイヤーのスコアを配列に変換する
	int aDigit[MaxDigit] = {};

	int nR = nScore;

	if (nScore > 0)
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
		pResult->m_pScore[nCnt] = CLetter::Create(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f - 55.0f * (MaxDigit * 0.5f) + 55.0f * nCnt, (float)SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR2(50.0f, 50.0f), aDigit[nCnt]);

		if (pResult->m_pScore[nCnt] != nullptr)
		{//生成出来たら、必要なパラメータを設定する
			pResult->m_pScore[nCnt]->SetPriority(4);
			pResult->m_pScore[nCnt]->SetColor(D3DXCOLOR(0.0f, 1.0f, 0.75f, 1.0f));
		}
	}

	CApplication::GetSound()->Play(CSound::SOUND_LABEL_BGM_RESULTS);		//BGMを設定する

	return pResult;					//生成したインスタンスを返す
}