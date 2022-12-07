//=============================================================================
//
// gluttony.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef GLUTTONY_H
#define GLUTTONY_H

//�C���N���[�h�t�@�C��
#include "enemy.h"

//�O���錾
class CSquareHitbox;
class CMaw;
class CBackMaw;
class CHeart;

class CGluttony
{
public:
	CGluttony();
	~CGluttony();							//�f�X�g���N�^

	HRESULT Init(void);				//����������
	void Uninit(void);					//�I������
	void Update(void);					//�X�V����

	const bool GetEnd(void);

	static CGluttony* Create(void);				//��������

private:

	static const int MaxMaw = 3;

	int m_nTargetFrame;
	int m_nCntState;
	int m_nPhase;

	CSquareHitbox* m_pHitbox;
	CMaw*     m_pMaw[MaxMaw];
	CBackMaw* m_pBackMaw;
	CHeart*   m_pHeart;
};

#endif