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
	//�����o�[�ϐ����N���A����
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
	LoadRanking();			//�X�R�A�����[�h����

	//�����o�[�ϐ�������������
	m_nSelectedStage = 0;
	m_nCntDelay = 0;

	return S_OK;
}

//�I������
void CRanking::Uninit(void)
{
	SaveRanking();			//�X�R�A�������o��
}

//���݂̃X�e�[�W�̐ݒ菈��
void CRanking::SetStage(CStageSelection::stage stage)
{
	m_nSelectedStage = stage;
}

//���݂̃X�e�[�W�̎擾����
int CRanking::GetStage(void)
{
	return m_nSelectedStage;
}

//�����L���O�̐ݒ菈��
int CRanking::SetRanking(CStageSelection::stage stage, const int nScore)
{
	LoadRanking();			//�X�R�A��ǂݍ���

	int aScore[MaxRank + 1] = {};

	for (int nCnt = 0; nCnt < MaxRank + 1; nCnt++)
	{
		aScore[nCnt] = m_aRanking[stage][nCnt];
	}

	aScore[MaxRank] = nScore;

	//�v���C���[�̏��ʂ��m�F����
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

	//�o�u���\�[�g���g���āA���Ԃ���ёւ���
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

	//�X�R�A���X�V����
	for (int nCnt = 0; nCnt < MaxRank; nCnt++)
	{
		m_aRanking[stage][nCnt] = aScore[nCnt];
	}

	SaveRanking();			//�X�R�A�������o��

	return Rank;			//�v���C���[�̏��ʂ�Ԃ�
}

//�����L���O�̎擾����
int* CRanking::GetRanking(CStageSelection::stage stage)
{
	return &m_aRanking[stage][0];
}

//�����L���O�̏����o������
void CRanking::SaveRanking(void)
{
	//�e�L�X�g�t�@�C�����J��
	FILE*pFile = fopen("data\\Ranking\\Ranking.txt", "w");

	if (pFile != nullptr)
	{//�J������

		char aStr[256] = {};

		//�X�R�A�������o��
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
	{//�J���Ȃ�������
		
	}

	//�t�@�C�������
	fclose(pFile);
}

//�����L���O�̓ǂݍ��ޏ���
void CRanking::LoadRanking(void)
{
	//�e�L�X�g�t�@�C�����J��
	FILE*pFile = fopen("data\\Ranking\\Ranking.txt", "r");

	if (pFile != nullptr)
	{//�J������

		char aStr[256] = {};

		//�X�R�A��ǂݍ���
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
	{//�J���Ȃ�������

	}

	//�t�@�C�������
	fclose(pFile);
}




//��������
CRanking* CRanking::Create(void)
{
	CRanking* pStage = new CRanking;		//�C���X�^���X�𐶐�����

	if (FAILED(pStage->Init()))
	{//����������
		return nullptr;
	}

	return pStage;							//���������C���X�^���X��Ԃ�
}
