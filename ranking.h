//=============================================================================
//
// ranking.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef RANKING_H
#define RANKING_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "stageSelection.h"

class CRanking
{
public:
	CRanking();							//�R���X�g���N�^
	~CRanking();						//�f�X�g���N�^

	HRESULT Init(void);					//����������
	void Uninit(void);					//�I������

	void SetStage(CStageSelection::stage stage);	//���݂̃X�e�[�W�̐ݒ菈��
	int GetStage(void);								//���݂̃X�e�[�W�̎擾����
	int SetRanking(CStageSelection::stage stage, const int nScore);	//�����L���O�̐ݒ菈��
	int* GetRanking(CStageSelection::stage stage);					//�����L���O�̎擾����
	void SaveRanking(void);				//�����L���O�̏����o������
	void LoadRanking(void);				//�����L���O�̓ǂݍ��ޏ���


	static CRanking* Create(void);		//��������

private:

	static const int MaxRank = 5;		//�X�R�A�̐�

	int m_aRanking[CStageSelection::stage_Max][MaxRank];		//�X�R�A�̔z��
	int m_nSelectedStage;										//���݂̃X�e�[�W
	int m_nCntDelay;											//�f�B���C
};



#endif