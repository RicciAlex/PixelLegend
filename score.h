//=============================================================================
//
// score.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef SCORE_H
#define SCORE_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "stageSelection.h"

class CScore
{
public:
	CScore();													//�R���X�g���N�^
	~CScore();													//�f�X�g���N�^
																
	HRESULT Init(void);											//����������
	void Uninit(void);											//�I������
																
	void SetBaseScore(const int nBase);							//��{�_���̐ݒ菈��
	void SetDifficulty(const int nDifficulty);					//��Փx�̐ݒ菈��
	void SetLife(const int nLife);								//�v���C���[�̎c�������C�t
	void Clear(void);											//�N���A����

	void SetLevel(CStageSelection::stage stage);				//�X�e�[�W�̐ݒ菈��

	CStageSelection::stage GetStage(void);						//�X�e�[�W�̎擾����
	const int GetFinalScore(void);								//�X�R�A�̎擾����


	static CScore* Create(void);								//��������

private:

	void CalcScore(void);										//�X�R�A�̌v�Z����

	int m_nScore;												//�X�R�A
																
	CStageSelection::stage m_stage;								//���݂̃X�e�[�W
	int m_nBaseScore;											//��{�̃X�R�A
	int m_nDifficulty;											//��Փx
	int m_nRemainingLife;										//�c�����̗�
	int m_nStartingTime;										//���߂̎���
	int m_nTime;												//���ݎ���
};




#endif