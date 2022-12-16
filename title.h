//=============================================================================
//
// title.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef TITLE_H
#define TITLE_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "mode.h"

//=============================================================================
//�O���錾
//=============================================================================
class CBg;
class CTitleMenu;
class CButton;
class CSkullCursor;
class CLetter;

class CTitle : public CMode
{
public:

	//�^�C�g���A�j���[�V�����̐F
	enum TargetCol
	{
		TargetCol_Red = 0,		//��
		TargetCol_Green,		//��
		TargetCol_Blue,			//��
		TargetCol_Yellow,		//��
		TargetCol_Magenta,		//�}�[���^
		TargetCol_Cyan,			//�V�A��
		TargetCol_Max
	};

	//�{�^���̗񋓌^
	enum Button
	{
		button_play = 0,		//�v���C�{�^��
		button_tutorial,		//�`���[�g���A���{�^��
		button_leaderboard,		//�����L���O�{�^��
		button_max
	};

	CTitle();								//�R���X�g���N�^
	~CTitle() override;						//�f�X�g���N�^

	HRESULT Init(void) override;			//����������
	void Uninit(void) override;				//�I������
	void Update(void) override;				//�X�V����

	static CTitle* Create(void);			//��������

private:

	void UpdateTitleColor(void);			//�^�C�g���̐F�̍X�V����
		
	static D3DXCOLOR targetColors[TargetCol_Max];		//�^�C�g���A�j���[�V�����̐F

	TargetCol m_TargetCol;				//���̖ړI�̐F�̔ԍ�
	D3DXCOLOR m_changeCol;				//�A�j���[�V�����̑��x(���t���[�����Z����Ă���J���[)
	int m_nChangeFrame;					//�A�j���[�V�����t���[��

	CBg* m_pBg;							//�w�i�ւ̃|�C���^
	CButton* m_pButton[button_max];		//�{�^���ւ̃|�C���^
	CSkullCursor* m_pCursor[2];			//�J�[�\���ւ̃|�C���^
	CLetter* m_pTitle[16];				//�^�C�g���̕����ւ̃|�C���^
};

#endif