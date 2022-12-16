//=============================================================================
//
// ranking.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "ranking.h"
#include <stdio.h>

//コンストラクタ
CRanking::CRanking()
{
	//メンバー変数をクリアする
	m_nSelectedStage = 0;
	m_nCntDelay = 0;

	for (int nCnt2 = 0; nCnt2 < CStageSelection::stage_Max; nCnt2++)
	{
		for (int nCnt = 0; nCnt < MaxRank; nCnt++)
		{
			m_aRanking[nCnt2][nCnt] = 0;
		}
	}
}

//デストラクタ
CRanking::~CRanking()
{
	
}

//初期化処理
HRESULT CRanking::Init(void)
{
	LoadRanking();			//スコアをロードする

	//メンバー変数を初期化する
	m_nSelectedStage = 0;
	m_nCntDelay = 0;

	return S_OK;
}

//終了処理
void CRanking::Uninit(void)
{
	SaveRanking();			//スコアを書き出す
}

//現在のステージの設定処理
void CRanking::SetStage(CStageSelection::stage stage)
{
	m_nSelectedStage = stage;
}

//現在のステージの取得処理
int CRanking::GetStage(void)
{
	return m_nSelectedStage;
}

//ランキングの設定処理
int CRanking::SetRanking(CStageSelection::stage stage, const int nScore)
{
	LoadRanking();			//スコアを読み込む

	int aScore[MaxRank + 1] = {};

	for (int nCnt = 0; nCnt < MaxRank + 1; nCnt++)
	{
		aScore[nCnt] = m_aRanking[stage][nCnt];
	}

	aScore[MaxRank] = nScore;

	//プレイヤーの順位を確認する
	int Rank = 11;

	for (int nCnt = 10; nCnt >= 0; nCnt--)
	{
		if (nScore > aScore[nCnt])
		{
			Rank = nCnt + 1;
		}
		else
		{
			break;
		}
	}

	int nMemory = -1;

	//バブルソートを使って、順番を並び替える
	for (int nCount2 = 0; nCount2 < MaxRank; nCount2++)
	{
		for (int nCount = nCount2 + 1; nCount < MaxRank + 1; nCount++)
		{
			if (aScore[nCount2] <= aScore[nCount])
			{
				nMemory = aScore[nCount];
				aScore[nCount] = aScore[nCount2];
				aScore[nCount2] = nMemory;
			}
		}
	}

	//スコアを更新する
	for (int nCnt = 0; nCnt < MaxRank; nCnt++)
	{
		m_aRanking[stage][nCnt] = aScore[nCnt];
	}

	SaveRanking();			//スコアを書き出す

	return Rank;			//プレイヤーの順位を返す
}

//ランキングの取得処理
int* CRanking::GetRanking(CStageSelection::stage stage)
{
	return &m_aRanking[stage][0];
}

//ランキングの書き出し処理
void CRanking::SaveRanking(void)
{
	//テキストファイルを開く
	FILE*pFile = fopen("data\\Ranking\\Ranking.txt", "w");

	if (pFile != nullptr)
	{//開けたら

		char aStr[256] = {};

		//スコアを書き出す
		for (int nCnt = 0; nCnt < CStageSelection::stage_Max; nCnt++)
		{
			fprintf(pFile, "\n %d \n", nCnt + 1);

			for (int nCnt2 = 0; nCnt2 < MaxRank; nCnt2++)
			{
				fprintf(pFile, "%d\n", m_aRanking[nCnt][nCnt2]);
			}
		}

	}
	else
	{//開けなかったら
		
	}

	//ファイルを閉じる
	fclose(pFile);
}

//ランキングの読み込む処理
void CRanking::LoadRanking(void)
{
	//テキストファイルを開く
	FILE*pFile = fopen("data\\Ranking\\Ranking.txt", "r");

	if (pFile != nullptr)
	{//開けたら

		char aStr[256] = {};

		//スコアを読み込む
		for (int nCnt = 0; nCnt < CStageSelection::stage_Max; nCnt++)
		{
			int i = -1;

			fscanf(pFile, "%d", &i);

			for (int nCnt2 = 0; nCnt2 < MaxRank; nCnt2++)
			{
				fscanf(pFile, "%d", &m_aRanking[nCnt][nCnt2]);
			}
		}

	}
	else
	{//開けなかったら

	}

	//ファイルを閉じる
	fclose(pFile);
}




//生成処理
CRanking* CRanking::Create(void)
{
	CRanking* pStage = new CRanking;		//インスタンスを生成する

	if (FAILED(pStage->Init()))
	{//初期化処理
		return nullptr;
	}

	return pStage;							//生成したインスタンスを返す
}
