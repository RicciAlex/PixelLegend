//=============================================================================
//
// skullFireball.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef SKULL_FIREBALL_H
#define SKULL_FIREBALL_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "bullet.h"

//=============================================================================
//前方宣言
//=============================================================================
class CCircleHitbox;

class CSkullFireball : public CBullet
{
public:
	CSkullFireball();						//コンストラクタ
	~CSkullFireball() override;				//デストラクタ

	HRESULT Init(void) override;			//初期化処理
	void Uninit(void) override;				//終了処理
	void Update(void) override;				//更新処理

	static CSkullFireball* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);		//生成処理

private:

	CCircleHitbox* m_pHitbox;				//ヒットボックスへのポインタ
};

#endif