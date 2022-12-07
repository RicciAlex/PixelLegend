//=============================================================================
//
// ranking.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "ranking.h"
#include <stdio.h>

//�R���X�g���N�^
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

//�f�X�g���N�^
CRanking::~CRanking()
{
	
}

//����������
HRESULT CRanking::Init(void)
{
	LoadRanking();

	m_nSelectedStage = 0;
	m_nCntDelay = 0;

	return S_OK;
}

//�I������
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

//�����L���O�̐ݒ菈��
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

//�����L���O�̏����o������
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
		printf("\n\n ***** �t�@�C�����J���܂���ł���*****");
	}

	//�t�@�C�������
	fclose(pFile);
}

//�����L���O�̓ǂݍ��ޏ���
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
		printf("\n\n ***** �t�@�C�����J���܂���ł���*****");
	}

	//�t�@�C�������
	fclose(pFile);
}




//��������
CRanking* CRanking::Create(void)
{
	CRanking* pStage = new CRanking;

	if (FAILED(pStage->Init()))
	{
		return nullptr;
	}

	return pStage;
}
