//=============================================================================
//
// gameThanatos.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef GAME_THANATOS_H
#define GAME_THANATOS_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "mode.h"

//=============================================================================
//�O���錾
//=============================================================================
class CBg;
class CThanatos;
class CPlayer;
class CButton;

class CGameThanatos : public CMode
{
public:

	enum Button
	{
		button_continue = 0,
		button_quit,
		button_max
	};

	CGameThanatos();									//�R���X�g���N�^
	~CGameThanatos() override;							//�f�X�g���N�^

	HRESULT Init(void) override;				//����������
	void Uninit(void) override;					//�I������
	void Update(void) override;					//�X�V����

	static CGameThanatos* Create(void);					//��������

private:

	void UpdateMenu(void);

	bool m_bPause;

	CBg* m_pBg;
	CPlayer* m_pPlayer;
	CThanatos* m_pEnemy;

	CBg* m_pMenuBg;
	CButton* m_pButton[button_max];
};

#endif