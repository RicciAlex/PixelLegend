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

	//�{�^���̗񋓌^
	enum Button
	{
		button_continue = 0,		//�R���e�B�j���[�{�^��
		button_quit,				//�^�C�g���ɖ߂�{�^��
		button_max
	};

	CGameThanatos();							//�R���X�g���N�^
	~CGameThanatos() override;					//�f�X�g���N�^

	HRESULT Init(void) override;				//����������
	void Uninit(void) override;					//�I������
	void Update(void) override;					//�X�V����

	static CGameThanatos* Create(void);			//��������

private:

	void UpdateMenu(void);				//���j���[�̍X�V����
		
	bool m_bPause;						//�|�[�Y���ł��邩�ǂ���
										
	CBg* m_pBg;							//�w�i�ւ̃|�C���^
	CPlayer* m_pPlayer;					//�v���C���[�ւ̃|�C���^
	CThanatos* m_pEnemy;				//�G�ւ̃|�C���^
									
	CBg* m_pMenuBg;						//���j���[�̔w�i�ւ̃|�C���^
	CButton* m_pButton[button_max];		//�{�^���ւ̃|�C���^
};

#endif