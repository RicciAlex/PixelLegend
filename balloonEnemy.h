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
	CBalloonEnemy();							//コンストラクタ
	~CBalloonEnemy() override;					//デストラクタ
												
	HRESULT Init(void) override;				//初期化処理
	void Uninit(void) override;					//終了処理
	void Update(void) override;					//更新処理
	void Draw(void) override;					//描画処理

	static CBalloonEnemy* Create(D3DXVECTOR3 pos);				//生成処理

private:

	CCircleHitbox* m_pHitbox;					//ヒットボックス
};

#endif