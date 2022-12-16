//=============================================================================
//
// rankingMode.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef RANKING_MODE_H
#define RANKING_MODE_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "mode.h"
#include "stageSelection.h"

//=============================================================================
//�O���錾
//=============================================================================
class CLetter;
class CBg;
class CButton;

class CRankingMode : public CMode
{
public:
	CRankingMode();						//�R���X�g���N�^
	~CRankingMode() override;			//�f�X�g���N�^

	HRESULT Init(void) override;		//����������
	void Uninit(void) override;			//�I������
	void Update(void) override;			//�X�V����

	static CRankingMode* Create(const int nStage);			//��������

private:

	void UpdateMenu(void);				//���j���[�̍X�V����

	static const int MaxRank = 5;		//�X�R�A�̐�
	static const int MaxDigit = 8;		//�X�R�A�̌���

	int m_nSelectedStage;				//���݂̃X�e�[�W
	int m_nCntDelay;					//�f�B���C

	CBg* m_pBg;							//�w�i�ւ̃|�C���^
	CLetter* m_pStageName[24];			//�X�e�[�W�̖��O�ւ̃|�C���^
	CLetter* m_pRank[MaxRank][MaxDigit];//�X�R�A�ւ̃|�C���^
	CButton* m_pLateralButton[2];		//�{�^���ւ̃|�C���^
	CLetter* m_pLateralIcon[2];			//UI�ւ̃|�C���^
};

#endif