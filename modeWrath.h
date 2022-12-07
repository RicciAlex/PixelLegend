//=============================================================================
//
// gameWrath.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef GAME_WRATH_H
#define GAME_WRATH_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "mode.h"

//=============================================================================
//前方宣言
//=============================================================================
class CBg;
class CWrath;
class CPlayer;
class CButton;
class CObject_2D;

class CGameWrath : public CMode
{
public:

	enum Button
	{
		button_continue = 0,
		button_quit,
		button_max
	};

	CGameWrath();
	~CGameWrath();

	HRESULT Init(void) override;				//初期化処理
	void Uninit(void) override;					//終了処理
	void Update(void) override;					//更新処理

	static CGameWrath* Create(void);					//生成処理

private:

	void UpdateMenu(void);

	bool m_bPause;

	int m_nCntBg;
	float m_fColAnim;

	CBg* m_pBg;
	CObject_2D* m_pBackBg;
	CPlayer* m_pPlayer;
	CWrath* m_pEnemy;

	CBg* m_pMenuBg;
	CButton* m_pButton[button_max];

	int m_nAnim;
	CObject_2D* m_pObj;
};

#endif