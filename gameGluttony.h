//=============================================================================
//
// gameGluttony.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef GAME_GLUTTONY_H
#define GAME_GLUTTONY_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "mode.h"

//=============================================================================
//前方宣言
//=============================================================================
class CBg;
class CGluttony;
class CPlayer;
class CButton;

class CGameGluttony : public CMode
{
public:

	//ボタンの列挙型
	enum Button
	{
		button_continue = 0,		//コンティニューボタン
		button_quit,				//タイトルに戻るボタン
		button_max
	};

	CGameGluttony();
	~CGameGluttony();

	HRESULT Init(void) override;				//初期化処理
	void Uninit(void) override;					//終了処理
	void Update(void) override;					//更新処理

	static CGameGluttony* Create(void);					//生成処理

private:

	void UpdateMenu(void);				//メニューの更新処理

	bool m_bPause;

	CBg* m_pBg;
	CPlayer* m_pPlayer;
	CGluttony* m_pEnemy;

	CBg* m_pMenuBg;
	CButton* m_pButton[button_max];
};

#endif