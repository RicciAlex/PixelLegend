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

	enum Button
	{
		button_continue = 0,
		button_quit,
		button_max
	};

	CGamePride();									//コンストラクタ
	~CGamePride() override;							//デストラクタ

	HRESULT Init(void) override;				//初期化処理
	void Uninit(void) override;					//終了処理
	void Update(void) override;					//更新処理

	static CGamePride* Create(void);					//生成処理

private:

	static const int Max_Obj = 5;

	void UpdateMenu(void);

	bool m_bPause;
	int m_nBalloonNumber;
	int m_nCntAnim;

	CBg* m_pBg;
	CPlayer* m_pPlayer;
	CPride* m_pEnemy;

	CBg* m_pMenuBg;
	CButton* m_pButton[button_max];

	CObject_2D* m_pBalloon[Max_Obj];
};

#endif