//=============================================================================
//
// tutorial.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef TUTORIAL_H
#define TUTORIAL_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "mode.h"

//=============================================================================
//�O���錾
//=============================================================================
class CBg;
class CObject_2D;

class CTutorial : public CMode
{
public:

	CTutorial();
	~CTutorial();

	HRESULT Init(void) override;				//����������
	void Uninit(void) override;					//�I������
	void Update(void) override;					//�X�V����

	static CTutorial* Create(void);					//��������

private:

	int m_nCntAnim;

	CBg*        m_pBg;
	CObject_2D* m_pPlayer;
	CObject_2D* m_pButton;
	CObject_2D* m_pTarget;
};

#endif