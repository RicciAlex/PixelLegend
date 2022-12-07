//=============================================================================
//
// gameSloth.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef GAME_SLOTH_H
#define GAME_SLOTH_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "mode.h"

//=============================================================================
//前方宣言
//=============================================================================
class CBg;
class CSloth;
class CPlayer;
class CButton;

class CGameSloth : public CMode
{
public:

	enum Button
	{
		button_continue = 0,
		button_quit,
		button_max
	};

	CGameSloth();
	~CGameSloth();

	HRESULT Init(void) override;				//初期化処理
	void Uninit(void) override;					//終了処理
	void Update(void) override;					//更新処理

	static CGameSloth* Create(void);					//生成処理

private:

	void UpdateMenu(void);

	bool m_bPause;

	CBg* m_pBg;
	CPlayer* m_pPlayer;
	CSloth* m_pEnemy;

	CBg* m_pMenuBg;
	CButton* m_pButton[button_max];
};

#endif