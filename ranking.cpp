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
	LoadRanking();

	m_nSelectedStage = 0;
	m_nCntDelay = 0;

	return S_OK;
}

//終了処理
void CRanking::Uninit(void)
{
	SaveRanking();
}

void CRanking::SetStage(CStageSelection::stage stage)
{
	m_nSelectedStage = stage;
}

int CRanking::GetStage(void)
{
	return m_nSelectedStage;
}

//ランキングの設定処理
int CRanking::SetRanking(CStageSelection::stage stage, const int nScore)
{
	LoadRanking();

	int aScore[MaxRank + 1] = {};

	for (int nCnt = 0; nCnt < MaxRank + 1; nCnt++)
	{
		aScore[nCnt] = m_aRanking[stage][nCnt];
	}

	aScore[MaxRank] = nScore;

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

	for (int nCnt = 0; nCnt < MaxRank; nCnt++)
	{
		m_aRanking[stage][nCnt] = aScore[nCnt];
	}

	SaveRanking();

	return Rank;
}

int* CRanking::GetRanking(CStageSelection::stage stage)
{
	return &m_aRanking[stage][0];
}

//ランキングの書き出し処理
void CRanking::SaveRanking(void)
{
	FILE*pFile = fopen("data\\Ranking\\Ranking.txt", "w");

	if (pFile != nullptr)
	{
		char aStr[256] = {};

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
	{
		printf("\n\n ***** ファイルが開けませんでした*****");
	}

	//ファイルを閉じる
	fclose(pFile);
}

//ランキングの読み込む処理
void CRanking::LoadRanking(void)
{
	FILE*pFile = fopen("data\\Ranking\\Ranking.txt", "r");

	if (pFile != nullptr)
	{
		char aStr[256] = {};

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
	{
		printf("\n\n ***** ファイルが開けませんでした*****");
	}

	//ファイルを閉じる
	fclose(pFile);
}




//生成処理
CRanking* CRanking::Create(void)
{
	CRanking* pStage = new CRanking;

	if (FAILED(pStage->Init()))
	{
		return nullptr;
	}

	return pStage;
}
