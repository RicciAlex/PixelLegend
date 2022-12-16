//=============================================================================
//
// gameGreed.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef GAME_GREED_H
#define GAME_GREED_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "mode.h"

//=============================================================================
//前方宣言
//=============================================================================
class CBg;
class CGreed;
class CPlayer;
class CButton;

class CGameGreed : public CMode
{
public:

	//ボタンの列挙型
	enum Button
	{
		button_continue = 0,		//コンティニューボタン
		button_quit,				//タイトルに戻るボタン
		button_max
	};

	CGameGreed();
	~CGameGreed();

	HRESULT Init(void) override;				//初期化処理
	void Uninit(void) override;					//終了処理
	void Update(void) override;					//更新処理

	static CGameGreed* Create(void);					//生成処理

private:

	void UpdateMenu(void);					//メニューの更新処理

	bool m_bPause;

	CBg* m_pBg;
	CPlayer* m_pPlayer;
	CGreed* m_pEnemy;

	CBg* m_pMenuBg;
	CButton* m_pButton[button_max];
};

#endif