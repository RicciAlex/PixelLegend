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

	enum Button
	{
		button_play = 0,
		button_leaderboard,
		button_title,
		button_Max
	};

	static const char m_aStage[stage_Max][24];

	CStageSelection();							//�R���X�g���N�^
	~CStageSelection() override;				//�f�X�g���N�^

	HRESULT Init(void) override;				//����������
	void Uninit(void) override;					//�I������
	void Update(void) override;					//�X�V����

	static CStageSelection* Create(void);		//��������

private:

	void UpdateMenu(void);

	int m_nSelectedStage;
	int m_nCntDelay;
	int m_nDifficulty;

	//CStageSelectionMenu* m_pMenu;
	CBg* m_pBg;
	CButton* m_pButton[button_Max];
	CButton* m_pLateralButton[2];
	CLetter* m_pStageName[24];
	CLetter* m_pLateralIcon[2];
	CLetter* m_pStageSelectTitle[16];
	CObject_2D* m_pDifficultyIcon[5];
};

#endif