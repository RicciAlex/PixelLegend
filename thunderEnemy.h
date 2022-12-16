//=============================================================================
//
// thunderEnemy.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef ENEMY_THUNDER_H
#define ENEMY_THUNDER_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "bullet.h"

//=============================================================================
//前方宣言
//=============================================================================
class CSquareHitbox;

class CThunderEnemy : public CBullet
{
public:
	CThunderEnemy();																//コンストラクタ
	~CThunderEnemy();																//デストラクタ

	HRESULT Init(void) override;													//初期化処理
	void Uninit(void) override;														//終了処理
	void Update(void) override;														//更新処理

	static CThunderEnemy* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move,
		const D3DXVECTOR3 acc, const D3DXVECTOR2 dim);								//生成処理

private:

	CSquareHitbox* m_pHitbox;				//ヒットボックス
};

#endif // !ENEMY_THUNDER_H