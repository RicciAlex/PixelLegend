//=============================================================================
//
// gameSloth.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef GAME_SLOTH_H
#define GAME_SLOTH_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "mode.h"

//=============================================================================
//�O���錾
//=============================================================================
class CBg;
class CSloth;
class CPlayer;
class CButton;

class CGameSloth : public CMode
{
public:

	enum Button
	{
		button_continue = 0,
		button_quit,
		button_max
	};

	CGameSloth();
	~CGameSloth();

	HRESULT Init(void) override;				//����������
	void Uninit(void) override;					//�I������
	void Update(void) override;					//�X�V����

	static CGameSloth* Create(void);					//��������

private:

	void UpdateMenu(void);

	bool m_bPause;

	CBg* m_pBg;
	CPlayer* m_pPlayer;
	CSloth* m_pEnemy;

	CBg* m_pMenuBg;
	CButton* m_pButton[button_max];
};

#endif