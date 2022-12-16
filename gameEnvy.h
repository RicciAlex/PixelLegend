//=============================================================================
//
// gameEnvy.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef GAME_ENVY_H
#define GAME_ENVY_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "mode.h"

//=============================================================================
//前方宣言
//=============================================================================
class CBg;
class CEnvy;
class CPlayer;
class CButton;
class CObject_2D;

class CGameEnvy : public CMode
{
public:

	//ボタンの列挙型
	enum Button
	{
		button_continue = 0,		//コンティニューボタン
		button_quit,				//タイトルに戻るボタン
		button_max
	};

	CGameEnvy();					//コンストラクタ
	~CGameEnvy();					//デストラクタ

	HRESULT Init(void) override;	//初期化処理
	void Uninit(void) override;		//終了処理
	void Update(void) override;		//更新処理

	static CGameEnvy* Create(void);					//生成処理

private:

	void UpdateMenu(void);			//メニューの更新処理

	bool m_bPause;
	int m_nCntAnim;

	CBg* m_pBg;
	CPlayer* m_pPlayer;
	CEnvy* m_pEnemy;

	CBg* m_pMenuBg;
	CButton* m_pButton[button_max];
	CObject_2D* m_pThunderBg;
};




#endif