//=============================================================================
//
// gameGluttony.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef GAME_GLUTTONY_H
#define GAME_GLUTTONY_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "mode.h"

//=============================================================================
//�O���錾
//=============================================================================
class CBg;
class CGluttony;
class CPlayer;
class CButton;

class CGameGluttony : public CMode
{
public:

	enum Button
	{
		button_continue = 0,
		button_quit,
		button_max
	};

	CGameGluttony();
	~CGameGluttony();

	HRESULT Init(void) override;				//����������
	void Uninit(void) override;					//�I������
	void Update(void) override;					//�X�V����

	static CGameGluttony* Create(void);					//��������

private:

	void UpdateMenu(void);

	bool m_bPause;

	CBg* m_pBg;
	CPlayer* m_pPlayer;
	CGluttony* m_pEnemy;

	CBg* m_pMenuBg;
	CButton* m_pButton[button_max];
};

#endif