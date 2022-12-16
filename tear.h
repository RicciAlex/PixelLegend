//=============================================================================
//
// tear.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef TEAR_H
#define TEAR_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "bullet.h"

//=============================================================================
//前方宣言
//=============================================================================
class CCircleHitbox;

class CTearBullet : public CBullet
{
public:
	CTearBullet();						//コンストラクタ
	~CTearBullet() override;			//デストラクタ

	HRESULT Init(void) override;		//初期化処理
	void Uninit(void) override;			//終了処理
	void Update(void) override;			//更新処理

	static CTearBullet* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move);		//生成処理

private:

	CCircleHitbox* m_pHitbox;			//ヒットボックス
};


#endif