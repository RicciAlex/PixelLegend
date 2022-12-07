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
	~CRanking();				//�f�X�g���N�^

	HRESULT Init(void);					//����������
	void Uninit(void);					//�I������

	void SetStage(CStageSelection::stage stage);
	int GetStage(void);
	int SetRanking(CStageSelection::stage stage, const int nScore);	//�����L���O�̐ݒ菈��
	int* GetRanking(CStageSelection::stage stage);					//�����L���O�̎擾����
	void SaveRanking(void);				//�����L���O�̏����o������
	void LoadRanking(void);				//�����L���O�̓ǂݍ��ޏ���


	static CRanking* Create(void);

private:

	//void UpdateMenu(void);

	static const int MaxRank = 5;
	//static const int MaxDigit = 8;


	int m_aRanking[CStageSelection::stage_Max][MaxRank];
	int m_nSelectedStage;
	int m_nCntDelay;

	/*CBg* m_pBg;
	CLetter* m_pStageName[24];
	CLetter* m_pRank[MaxRank][MaxDigit];
	CButton* m_pLateralButton[2];
	CLetter* m_pLateralIcon[2];*/
};



#endif