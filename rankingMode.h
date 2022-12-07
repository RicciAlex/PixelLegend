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
	CRankingMode();							//�R���X�g���N�^
	~CRankingMode() override;				//�f�X�g���N�^

	HRESULT Init(void) override;		//����������
	void Uninit(void) override;			//�I������
	void Update(void) override;			//�X�V����

	static CRankingMode* Create(const int nStage);

private:

	void UpdateMenu(void);

	static const int MaxRank = 5;
	static const int MaxDigit = 8;

	int m_nSelectedStage;
	int m_nCntDelay;

	CBg* m_pBg;
	CLetter* m_pStageName[24];
	CLetter* m_pRank[MaxRank][MaxDigit];
	CButton* m_pLateralButton[2];
	CLetter* m_pLateralIcon[2];
};

#endif