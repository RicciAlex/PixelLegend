//=============================================================================
//
// clockNeedle.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef CLOCK_NEEDLE_H
#define CLOCK_NEEDLE_H

//インクルードファイル
#include "bullet.h"

class CClockNeedle : public CBullet
{
public:
	CClockNeedle();																	//コンストラクタ
	~CClockNeedle() override;														//デストラクタ

	HRESULT Init(void) override;													//初期化処理
	void Uninit(void) override;														//終了処理
	void Update(void) override;														//更新処理

	bool Hit(void);																	//弾の当たり判定

	static CClockNeedle* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move,
		const D3DXVECTOR3 acc, const D3DXVECTOR2 dim);								//生成処理

private:

};

#endif // !CLOCK_NEEDLE_H