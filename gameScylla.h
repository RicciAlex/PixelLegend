//=============================================================================
//
// gameScylla.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef GAME_SCYLLA_H
#define GAME_SCYLLA_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "mode.h"

//=============================================================================
//前方宣言
//=============================================================================
class CBg;
class CScylla;
class CPlayer;
class CPauseMenu;
class CButton;

class CGameScylla : public CMode
{
public:

	//ボタンの列挙型
	enum Button
	{
		button_continue = 0,		//コンティニューボタン
		button_quit,				//タイトルに戻るボタン
		button_max
	};

	CGameScylla();					//コンストラクタ
	~CGameScylla() override;		//デストラクタ

	HRESULT Init(void) override;	//初期化処理
	void Uninit(void) override;		//終了処理
	void Update(void) override;		//更新処理

	static CGameScylla* Create(void);					//生成処理

private:

	void UpdateMenu(void);			//メニューの更新処理

	bool m_bPause;					//ポーズ中であるかどうか

	CBg* m_pBg;						//背景へのポインタ
	CPlayer* m_pPlayer;				//プレイヤーへのポインタ
	CScylla* m_pEnemy;				//敵へのポインタ
	CBg* m_pMenuBg;					//メニューの背景へのポインタ
	CButton* m_pButton[button_max];	//ボタンへのポインタ
};

#endif