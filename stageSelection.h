//=============================================================================
//
// stageSelection.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef STAGE_SELECTION_H
#define STAGE_SELECTION_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "mode.h"

//=============================================================================
//�O���錾
//=============================================================================
class CStageSelectionMenu;
class CBg;
class CButton;
class CLetter;
class CObject_2D;

class CStageSelection : public CMode
{
public:

	//�X�e�[�W�̗񋓌^
	enum stage
	{
		stage_Scylla = 0,
		stage_Thanatos,
		stage_Pride,
		stage_Envy,
		stage_Wrath,
		stage_Sloth,
		stage_Greed,
		stage_Gluttony,
		stage_Max
	};

	//�{�^���̗񋓌^
	enum Button
	{
		button_play = 0,			//�v���C�{�^��
		button_leaderboard,			//�����L���O�{�^��
		button_title,				//�^�C�g���{�^��
		button_Max
	};

	static const char m_aStage[stage_Max][24];	//�X�e�[�W�̖��O�̔z��

	CStageSelection();							//�R���X�g���N�^
	~CStageSelection() override;				//�f�X�g���N�^

	HRESULT Init(void) override;				//����������
	void Uninit(void) override;					//�I������
	void Update(void) override;					//�X�V����

	static CStageSelection* Create(void);		//��������

private:

	void UpdateMenu(void);				//���j���[�̍X�V����

	int m_nSelectedStage;				//���݂̃X�e�[�W
	int m_nCntDelay;					//�f�B���C
	int m_nDifficulty;					//��Փx
										
	CBg* m_pBg;							//�w�i�ւ̃|�C���^
	CButton* m_pButton[button_Max];		//�{�^���ւ̃|�C���^
	CButton* m_pLateralButton[2];		//�{�^���ւ̃|�C���^
	CLetter* m_pStageName[24];			//�X�e�[�W�̖��O�ւ̃|�C���^
	CLetter* m_pLateralIcon[2];			//UI�ւ̃|�C���^
	CLetter* m_pStageSelectTitle[16];	//�����ւ̃|�C���^
	CObject_2D* m_pDifficultyIcon[5];	//��ՓxUI�ւ̃|�C���^
};

#endif