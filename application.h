//=============================================================================
//
// application.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef APPLICATION_H
#define APPLICATION_H

//�C���N���[�h�t�@�C��
#include "object.h"

//�O���錾
class CRenderer;
class CInput;
class CInputMouse;
class CMode;
class CScore;
class CSound;
class CRanking;
class CFade;

//�A�v���P�[�V�����̃N���X
class CApplication
{
public:

	enum Mode
	{
		Mode_Title = 0,					//�^�C�g��
		Mode_StageSelection,			//�X�e�[�W�I��
		Mode_Tutorial,					//�`���[�g���A��
		Mode_Game,						//�Q�[��
		Mode_Game_Scylla,				//�X�e�[�W1
		Mode_Game_Thanatos,				//�X�e�[�W2
		Mode_Game_Pride,				//�X�e�[�W3
		Mode_Game_Envy,					//�X�e�[�W4
		Mode_Game_Wrath,				//�X�e�[�W5
		Mode_Game_Sloth,				//�X�e�[�W6
		Mode_Game_Greed,				//�X�e�[�W7
		Mode_Game_Gluttony,				//�X�e�[�W8
		Mode_Result,					//���U���g
		Mode_Ranking,					//�����L���O
		Mode_Max
	};

	CApplication();										//�R���X�g���N�^
	~CApplication();									//�f�X�g���N�^
														
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);		//����������
	void Uninit(void);									//�I������
	void Update(void);									//�X�V����
	void Draw(void);									//�`�揈��
	static CRenderer* GetRenderer(void);				//�����f�B���O�C���X�^���X�̎擾����
	static CInputMouse* GetMouse(void);					//�}�E�X�C���X�^���X�̎擾����
	static HWND GetWindow(void);						//�E�C���h�E�̎擾����
	static void SetDifficulty(const int difficulty);	//��Փx�̐ݒ菈��
	static const int GetDifficulty(void);				//��Փx�̎擾����
	static void SetRemainingLife(const int nLife);		//�c�����̗͂̐ݒ菈��
	static Mode GetMode(void);							//���[�h�̎擾����
	static void SetMode(Mode mode);						//���[�h�̐ݒ菈��
	static CSound* GetSound(void);						//�T�E���h�̎擾����
	static CRanking* GetRanking(void);					//�����L���O�̎擾����
	static void SetFade(Mode mode);						//�t�F�[�h�̐ݒ菈��
	static void SetFade(const bool bFade);				//�t�F�[�h�̐ݒ菈��
	static const bool GetFade(void);					//�t�F�[�h�̎擾����

private:
	static HWND m_hWnd;									//�N���C�G���g���
	static CRenderer* m_pRenderer;						//�����f�B���O�C���X�^���X�ւ̃|�C���^
	static CInput* m_pInput[2];							//�C���v�b�g�f�o�C�X�ւ̃|�C���^
	static CInputMouse* m_pMouse;						//�}�E�X�C���X�^���X
	static Mode m_mode;									//���[�h
	static CScore* m_pScore;							//�X�R�A�ւ̃|�C���^
	static CRanking* m_pRanking;						//�����L���O�ւ̃|�C���^
	static CSound* m_pSound;							//�T�E���h�ւ̃|�C���^
	static CFade* m_pFade;								//�t�F�[�h�ւ̃|�C���^
														
	static CMode* m_pMode;								//���[�h�ւ̃|�C���^
	static bool m_bFade;								//�t�F�[�h���ł��邩�ǂ���
	static int m_nDifficulty;							//��Փx
};



#endif // !APPLICATION_H
