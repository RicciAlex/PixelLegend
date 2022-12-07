//=============================================================================
//
// result.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef RESULT_H
#define RESULT_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "mode.h"

//=============================================================================
//�O���錾
//=============================================================================
class CLetter;

class CResult : public CMode
{
public:
	CResult();
	~CResult();

	HRESULT Init(void) override;
	void Uninit(void) override;
	void Update(void) override;

	static CResult* Create(const int nScore);

private:

	static const int MaxDigit = 8;

	int m_nDelay;
	float m_fAnim;

	CLetter* m_pScore[MaxDigit];
	CLetter* m_pUI[12];
};

#endif