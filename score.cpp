//=============================================================================
//
// score.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "score.h"

//�R���X�g���N�^
CScore::CScore()
{
	m_nScore = 0;

	m_stage = CStageSelection::stage_Max;
	m_nBaseScore = 0;
	m_nDifficulty = 0;
	m_nRemainingLife = 0;
	m_nStartingTime = 0;
	m_nTime = 0;
}

//�f�X�g���N�^
CScore::~CScore()
{

}

//����������
HRESULT CScore::Init(void)
{
	m_nScore = 0;

	m_nBaseScore = 0;
	m_nDifficulty = 1;
	m_nRemainingLife = 0;
	m_nStartingTime = timeGetTime();	// ���݂̎��Ԃ��擾

	return S_OK;
}

//�I������
void CScore::Uninit(void)
{

}



void CScore::SetBaseScore(const int nBase)
{
	m_nBaseScore = nBase;
}


void CScore::SetDifficulty(const int nDifficulty)
{
	m_nDifficulty = nDifficulty;
}

//�v���C���[�̎c�������C�t
void CScore::SetLife(const int nLife)
{
	m_nRemainingLife = nLife;
}



const int CScore::GetFinalScore(void)
{
	CalcScore();

	return m_nScore;
}


CStageSelection::stage CScore::GetStage(void)
{
	return m_stage;
}


void CScore::SetLevel(CStageSelection::stage stage)
{
	m_stage = stage;
}


void CScore::Clear(void)
{
	m_nScore = 0;

	m_stage = CStageSelection::stage_Max;
	m_nBaseScore = 0;
	m_nDifficulty = 1;
	m_nRemainingLife = 0;
	m_nTime = 0;
	m_nStartingTime = timeGetTime();
}



void CScore::CalcScore(void)
{
	m_nTime = (int)((timeGetTime() - m_nStartingTime) * 0.001f);

	int nScore = (m_nBaseScore * m_nDifficulty) + (m_nRemainingLife * m_nDifficulty * 5000) - (m_nTime * 50);

	if (m_nRemainingLife == 15)
	{
		nScore += m_nBaseScore / 2;
	}
	else if (m_nRemainingLife <= 0)
	{
		nScore = 0;
	}

	m_nScore = nScore;
}



//��������
CScore* CScore::Create(void)
{
	CScore* pScore = new CScore;

	if (FAILED(pScore->Init()))
	{
		return nullptr;
	}

	return pScore;
}