//=============================================================================
//
// skull.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef SKULL_H
#define SKULL_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "enemy.h"

//=============================================================================
//前方宣言
//=============================================================================
class CSquareHitbox;

class CSkull : public CEnemy
{
public:
	CSkull();									//コンストラクタ
	~CSkull() override;							//デストラクタ

	HRESULT Init(void) override;				//初期化処理
	void Uninit(void) override;					//終了処理
	void Update(void) override;					//更新処理

	void Kill(void);							//死亡アニメーションの設定処理

	static CSkull* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);			//生成処理

private:

	D3DXVECTOR3 m_move;							//速度
	int m_nCntDestroy;							//死亡アニメーション用のカウンター
	bool m_bDead;								//死んでいるかどうか

	CSquareHitbox* m_pHitbox;					//ヒットボックス
};

#endif