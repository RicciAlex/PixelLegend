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

	//�{�^���̗񋓌^
	enum Button
	{
		button_continue = 0,		//�R���e�B�j���[�{�^��
		button_quit,				//�^�C�g���ɖ߂�{�^��
		button_max					
	};

	CGameWrath();					//�R���X�g���N�^
	~CGameWrath();					//�f�X�g���N�^

	HRESULT Init(void) override;	//����������
	void Uninit(void) override;		//�I������
	void Update(void) override;		//�X�V����

	static CGameWrath* Create(void);		//��������

private:

	void UpdateMenu(void);			//���j���[�̍X�V����

	bool m_bPause;					//�|�[�Y���ł��邩�ǂ���

	int m_nCntBg;					//�w�i�A�j���[�V�����p�̃J�E���^�[
	float m_fColAnim;				//�w�i�A�j���[�V�����p�̕ϐ�

	CBg* m_pBg;						//�w�i�ւ̃|�C���^
	CObject_2D* m_pBackBg;			//�w�i�A�j���[�V�����p��2D�|���S���ւ̃|�C���^
	CPlayer* m_pPlayer;				//�v���C���[�ւ̃|�C���^
	CWrath* m_pEnemy;				//�G�ւ̃|�C���^
									
	CBg* m_pMenuBg;					//���j���[�ւ̃|�C���^
	CButton* m_pButton[button_max];	//�{�^���ւ̃|�C���^
									
	int m_nAnim;					//�A�j���[�V�����J�E���^�[
	CObject_2D* m_pObj;				//UI�ւ̃|�C���^
};

#endif