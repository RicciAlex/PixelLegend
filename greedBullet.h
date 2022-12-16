//=============================================================================
//
// greedBullet.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef GREED_BULLET_H
#define GREED_BULLET_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "bullet.h"

//=============================================================================
//前方宣言
//=============================================================================
class CCircleHitbox;

class CGreedBullet : public CBullet
{
public:
	CGreedBullet();							//コンストラクタ
	~CGreedBullet() override;				//デストラクタ

	HRESULT Init(void) override;			//初期化処理
	void Uninit(void) override;				//終了処理
	void Update(void) override;				//更新処理


	static CGreedBullet* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move);											//生成処理
	static CGreedBullet* CGreedBullet::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const D3DXVECTOR3 acc);	//生成処理

private:

	CCircleHitbox* m_pHitbox;				//ヒットボックスへのポインタ
};

#endif