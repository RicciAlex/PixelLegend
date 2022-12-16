//=============================================================================
//
// Zbullet.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef ZBULLET_H
#define ZBULLET_H

//インクルードファイル
#include "bullet.h"

//=============================================================================
//前方宣言
//=============================================================================
class CSquareHitbox;

class CZBullet : public CBullet
{
public:
	CZBullet();																		//コンストラクタ
	~CZBullet() override;															//デストラクタ

	HRESULT Init(void) override;													//初期化処理
	void Uninit(void) override;														//終了処理
	void Update(void) override;														//更新処理


	static CZBullet* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);						//生成処理

private:

	int m_nCntSize;					//サイズのカウンター
	float m_fGrowth;				//大きさの減数
									
	CSquareHitbox* m_pHitbox;		//ヒットボックスへのポインタ
};

#endif
