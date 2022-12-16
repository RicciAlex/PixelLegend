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
	CGluttony();						//コンストラクタ
	~CGluttony();						//デストラクタ

	HRESULT Init(void);					//初期化処理
	void Uninit(void);					//終了処理
	void Update(void);					//更新処理

	const bool GetEnd(void);			//終わったかどうかの設定処理

	static CGluttony* Create(void);				//生成処理

private:

	static const int MaxMaw = 3;		//周りの敵の数

	int m_nTargetFrame;					//目的のフレーム
	int m_nCntState;					//状態カウンター
	int m_nPhase;						//カウンター
										
	CSquareHitbox* m_pHitbox;			//ヒットボックスへのポインタ
	CMaw*     m_pMaw[MaxMaw];			//周りの敵へのポインタ
	CBackMaw* m_pBackMaw;				//背景の敵へのポインタ
	CHeart*   m_pHeart;					//心へのポインタ
};

#endif