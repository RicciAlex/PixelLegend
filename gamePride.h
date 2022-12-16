//=============================================================================
//
// gamePride.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef GAME_PRIDE_H
#define GAME_PRIDE_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "mode.h"

//=============================================================================
//前方宣言
//=============================================================================
class CBg;
class CPride;
class CPlayer;
class CButton;
class CObject_2D;

class CGamePride : public CMode
{
public:

	//ボタンの列挙型
	enum Button
	{
		button_continue = 0,		//コンティニューボタン
		button_quit,				//タイトルに戻るボタン
		button_max
	};

	CGamePride();						//コンストラクタ
	~CGamePride() override;				//デストラクタ

	HRESULT Init(void) override;		//初期化処理
	void Uninit(void) override;			//終了処理
	void Update(void) override;			//更新処理

	static CGamePride* Create(void);	//生成処理

private:

	static const int Max_Obj = 5;		//背景の風船の数

	void UpdateMenu(void);				//メニューの更新処理

	bool m_bPause;						//ポーズ中であるかどうか
	int m_nBalloonNumber;				//存在している風船の数
	int m_nCntAnim;						//アニメーションカウンター
										
	CBg* m_pBg;							//背景へのポインタ
	CPlayer* m_pPlayer;					//プレイヤーへのポインタ
	CPride* m_pEnemy;					//敵へのポインタ
										
	CBg* m_pMenuBg;						//メニューの背景へのポインタ
	CButton* m_pButton[button_max];		//ボタンへのポインタ
										
	CObject_2D* m_pBalloon[Max_Obj];	//風船へのポインタ
};

#endif