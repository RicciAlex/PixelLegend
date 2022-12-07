//=============================================================================
//
// gameWrath.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef GAME_WRATH_H
#define GAME_WRATH_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "mode.h"

//=============================================================================
//�O���錾
//=============================================================================
class CBg;
class CWrath;
class CPlayer;
class CButton;
class CObject_2D;

class CGameWrath : public CMode
{
public:

	enum Button
	{
		button_continue = 0,
		button_quit,
		button_max
	};

	CGameWrath();
	~CGameWrath();

	HRESULT Init(void) override;				//����������
	void Uninit(void) override;					//�I������
	void Update(void) override;					//�X�V����

	static CGameWrath* Create(void);					//��������

private:

	void UpdateMenu(void);

	bool m_bPause;

	int m_nCntBg;
	float m_fColAnim;

	CBg* m_pBg;
	CObject_2D* m_pBackBg;
	CPlayer* m_pPlayer;
	CWrath* m_pEnemy;

	CBg* m_pMenuBg;
	CButton* m_pButton[button_max];

	int m_nAnim;
	CObject_2D* m_pObj;
};

#endif