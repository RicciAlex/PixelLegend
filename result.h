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
	CResult();							//�R���X�g���N
	~CResult();							//�f�X�g���N�^
										
	HRESULT Init(void) override;		//����������
	void Uninit(void) override;			//�I������
	void Update(void) override;			//�X�V����

	static CResult* Create(const int nScore);		//��������

private:

	static const int MaxDigit = 8;		//�X�R�A�̌���

	int m_nDelay;						//�f�B���C
	float m_fAnim;						//�A�j���[�V�����p�̕ϐ�
										
	CLetter* m_pScore[MaxDigit];		//�X�R�A�̌��ւ̃|�C���^
	CLetter* m_pUI[12];					//UI�ւ̃|�C���^
};

#endif