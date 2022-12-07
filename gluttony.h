//=============================================================================
//
// gluttony.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef GLUTTONY_H
#define GLUTTONY_H

//インクルードファイル
#include "enemy.h"

//前方宣言
class CSquareHitbox;
class CMaw;
class CBackMaw;
class CHeart;

class CGluttony
{
public:
	CGluttony();
	~CGluttony();							//デストラクタ

	HRESULT Init(void);				//初期化処理
	void Uninit(void);					//終了処理
	void Update(void);					//更新処理

	const bool GetEnd(void);

	static CGluttony* Create(void);				//生成処理

private:

	static const int MaxMaw = 3;

	int m_nTargetFrame;
	int m_nCntState;
	int m_nPhase;

	CSquareHitbox* m_pHitbox;
	CMaw*     m_pMaw[MaxMaw];
	CBackMaw* m_pBackMaw;
	CHeart*   m_pHeart;
};

#endif