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

	CTutorial();							//�R���X�g���N
	~CTutorial();							//�f�X�g���N�^

	HRESULT Init(void) override;			//����������
	void Uninit(void) override;				//�I������
	void Update(void) override;				//�X�V����

	static CTutorial* Create(void);			//��������

private:

	int m_nCntAnim;							//�A�j���[�V�����p�̃J�E���^�[
											
	CBg*        m_pBg;						//�w�i�ւ̃|�C���^
	CObject_2D* m_pPlayer;					//�v���C���[�ւ̃|�C���^
	CObject_2D* m_pButton;					//�{�^���ւ̃|�C���^
	CObject_2D* m_pTarget;					//�^�[�Q�b�g�ւ̃|�C���^
};

#endif