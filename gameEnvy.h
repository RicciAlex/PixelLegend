//=============================================================================
//
// gameEnvy.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef GAME_ENVY_H
#define GAME_ENVY_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "mode.h"

//=============================================================================
//�O���錾
//=============================================================================
class CBg;
class CEnvy;
class CPlayer;
class CButton;
class CObject_2D;

class CGameEnvy : public CMode
{
public:

	enum Button
	{
		button_continue = 0,
		button_quit,
		button_max
	};

	CGameEnvy();
	~CGameEnvy();

	HRESULT Init(void) override;				//����������
	void Uninit(void) override;					//�I������
	void Update(void) override;					//�X�V����

	static CGameEnvy* Create(void);					//��������

private:

	void UpdateMenu(void);

	bool m_bPause;
	int m_nCntAnim;

	CBg* m_pBg;
	CPlayer* m_pPlayer;
	CEnvy* m_pEnemy;

	CBg* m_pMenuBg;
	CButton* m_pButton[button_max];
	CObject_2D* m_pThunderBg;
};




#endif