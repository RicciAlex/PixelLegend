//=============================================================================
//
// gameScylla.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef GAME_SCYLLA_H
#define GAME_SCYLLA_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "mode.h"

//=============================================================================
//�O���錾
//=============================================================================
class CBg;
class CScylla;
class CPlayer;
class CPauseMenu;
class CButton;

class CGameScylla : public CMode
{
public:

	enum Button
	{
		button_continue = 0,
		button_quit,
		button_max
	};

	CGameScylla();									//�R���X�g���N�^
	~CGameScylla() override;							//�f�X�g���N�^

	HRESULT Init(void) override;				//����������
	void Uninit(void) override;					//�I������
	void Update(void) override;					//�X�V����

	static CGameScylla* Create(void);					//��������

private:

	void UpdateMenu(void);

	bool m_bPause;

	CBg* m_pBg;
	CPlayer* m_pPlayer;
	CScylla* m_pEnemy;
	//CPauseMenu* m_pMenu;
	CBg* m_pMenuBg;
	CButton* m_pButton[button_max];
};

#endif