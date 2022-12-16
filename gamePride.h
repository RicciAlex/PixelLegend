//=============================================================================
//
// gamePride.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef GAME_PRIDE_H
#define GAME_PRIDE_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "mode.h"

//=============================================================================
//�O���錾
//=============================================================================
class CBg;
class CPride;
class CPlayer;
class CButton;
class CObject_2D;

class CGamePride : public CMode
{
public:

	//�{�^���̗񋓌^
	enum Button
	{
		button_continue = 0,		//�R���e�B�j���[�{�^��
		button_quit,				//�^�C�g���ɖ߂�{�^��
		button_max
	};

	CGamePride();						//�R���X�g���N�^
	~CGamePride() override;				//�f�X�g���N�^

	HRESULT Init(void) override;		//����������
	void Uninit(void) override;			//�I������
	void Update(void) override;			//�X�V����

	static CGamePride* Create(void);	//��������

private:

	static const int Max_Obj = 5;		//�w�i�̕��D�̐�

	void UpdateMenu(void);				//���j���[�̍X�V����

	bool m_bPause;						//�|�[�Y���ł��邩�ǂ���
	int m_nBalloonNumber;				//���݂��Ă��镗�D�̐�
	int m_nCntAnim;						//�A�j���[�V�����J�E���^�[
										
	CBg* m_pBg;							//�w�i�ւ̃|�C���^
	CPlayer* m_pPlayer;					//�v���C���[�ւ̃|�C���^
	CPride* m_pEnemy;					//�G�ւ̃|�C���^
										
	CBg* m_pMenuBg;						//���j���[�̔w�i�ւ̃|�C���^
	CButton* m_pButton[button_max];		//�{�^���ւ̃|�C���^
										
	CObject_2D* m_pBalloon[Max_Obj];	//���D�ւ̃|�C���^
};

#endif