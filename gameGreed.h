//=============================================================================
//
// gameGreed.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef GAME_GREED_H
#define GAME_GREED_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "mode.h"

//=============================================================================
//�O���錾
//=============================================================================
class CBg;
class CGreed;
class CPlayer;
class CButton;

class CGameGreed : public CMode
{
public:

	//�{�^���̗񋓌^
	enum Button
	{
		button_continue = 0,		//�R���e�B�j���[�{�^��
		button_quit,				//�^�C�g���ɖ߂�{�^��
		button_max
	};

	CGameGreed();
	~CGameGreed();

	HRESULT Init(void) override;				//����������
	void Uninit(void) override;					//�I������
	void Update(void) override;					//�X�V����

	static CGameGreed* Create(void);					//��������

private:

	void UpdateMenu(void);					//���j���[�̍X�V����

	bool m_bPause;

	CBg* m_pBg;
	CPlayer* m_pPlayer;
	CGreed* m_pEnemy;

	CBg* m_pMenuBg;
	CButton* m_pButton[button_max];
};

#endif