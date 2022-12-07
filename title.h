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

	enum TargetCol
	{
		TargetCol_Red = 0,
		TargetCol_Green,
		TargetCol_Blue,
		TargetCol_Yellow,
		TargetCol_Magenta,
		TargetCol_Cyan,
		TargetCol_Max
	};

	enum Button
	{
		button_play = 0,
		button_tutorial,
		button_leaderboard,
		button_max
	};

	CTitle();								//�R���X�g���N�^
	~CTitle() override;						//�f�X�g���N�^

	HRESULT Init(void) override;			//����������
	void Uninit(void) override;				//�I������
	void Update(void) override;				//�X�V����

	static CTitle* Create(void);			//��������

private:

	void UpdateTitleColor(void);

	static D3DXCOLOR targetColors[TargetCol_Max];

	TargetCol m_TargetCol;
	D3DXCOLOR m_changeCol;
	int m_nChangeFrame;

	CBg* m_pBg;
	CButton* m_pButton[button_max];
	CSkullCursor* m_pCursor[2];
	CLetter* m_pTitle[16];
	//CTitleMenu* m_pTitleMenu;
};

#endif