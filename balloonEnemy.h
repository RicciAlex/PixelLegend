//=============================================================================
//
// enemy.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef BALLOON_ENEMY_H
#define BALLOON_ENEMY_H

//インクルードファイル
#include "enemy.h"

//前方宣言
class CCircleHitbox;

class CBalloonEnemy : public CEnemy
{
public:
	CBalloonEnemy();
	~CBalloonEnemy() override;

	HRESULT Init(void) override;
	void Uninit(void) override;					//終了処理
	void Update(void) override;					//更新処理
	void Draw(void) override;					//描画処理

	static CBalloonEnemy* Create(D3DXVECTOR3 pos);

private:

	CCircleHitbox* m_pHitbox;
};

#endif