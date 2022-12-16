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

	//ボタンの列挙型
	enum Button
	{
		button_continue = 0,		//コンティニューボタン
		button_quit,				//タイトルに戻るボタン
		button_max					
	};

	CGameWrath();					//コンストラクタ
	~CGameWrath();					//デストラクタ

	HRESULT Init(void) override;	//初期化処理
	void Uninit(void) override;		//終了処理
	void Update(void) override;		//更新処理

	static CGameWrath* Create(void);		//生成処理

private:

	void UpdateMenu(void);			//メニューの更新処理

	bool m_bPause;					//ポーズ中であるかどうか

	int m_nCntBg;					//背景アニメーション用のカウンター
	float m_fColAnim;				//背景アニメーション用の変数

	CBg* m_pBg;						//背景へのポインタ
	CObject_2D* m_pBackBg;			//背景アニメーション用の2Dポリゴンへのポインタ
	CPlayer* m_pPlayer;				//プレイヤーへのポインタ
	CWrath* m_pEnemy;				//敵へのポインタ
									
	CBg* m_pMenuBg;					//メニューへのポインタ
	CButton* m_pButton[button_max];	//ボタンへのポインタ
									
	int m_nAnim;					//アニメーションカウンター
	CObject_2D* m_pObj;				//UIへのポインタ
};

#endif