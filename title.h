//=============================================================================
//
// title.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef TITLE_H
#define TITLE_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "mode.h"

//=============================================================================
//前方宣言
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

	CTitle();								//コンストラクタ
	~CTitle() override;						//デストラクタ

	HRESULT Init(void) override;			//初期化処理
	void Uninit(void) override;				//終了処理
	void Update(void) override;				//更新処理

	static CTitle* Create(void);			//生成処理

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