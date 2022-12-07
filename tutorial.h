//=============================================================================
//
// tutorial.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef TUTORIAL_H
#define TUTORIAL_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "mode.h"

//=============================================================================
//前方宣言
//=============================================================================
class CBg;
class CObject_2D;

class CTutorial : public CMode
{
public:

	CTutorial();
	~CTutorial();

	HRESULT Init(void) override;				//初期化処理
	void Uninit(void) override;					//終了処理
	void Update(void) override;					//更新処理

	static CTutorial* Create(void);					//生成処理

private:

	int m_nCntAnim;

	CBg*        m_pBg;
	CObject_2D* m_pPlayer;
	CObject_2D* m_pButton;
	CObject_2D* m_pTarget;
};

#endif