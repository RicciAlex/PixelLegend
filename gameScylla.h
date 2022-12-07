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

	enum Button
	{
		button_continue = 0,
		button_quit,
		button_max
	};

	CGameScylla();									//コンストラクタ
	~CGameScylla() override;							//デストラクタ

	HRESULT Init(void) override;				//初期化処理
	void Uninit(void) override;					//終了処理
	void Update(void) override;					//更新処理

	static CGameScylla* Create(void);					//生成処理

private:

	void UpdateMenu(void);

	bool m_bPause;

	CBg* m_pBg;
	CPlayer* m_pPlayer;
	CScylla* m_pEnemy;
	//CPauseMenu* m_pMenu;
	CBg* m_pMenuBg;
	CButton* m_pButton[button_max];
};

#endif