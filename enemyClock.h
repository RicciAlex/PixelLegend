//=============================================================================
//
// enemyClock.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef ENEMY_CLOCK_H
#define ENEMY_CLOCK_H

//インクルードファイル
#include "enemy.h"

//前方宣言
class CClockNeedle;

//階層構造アニメーションの敵クラス(敵クラスの派生クラス)
class CEnemyClock : public CEnemy
{
public:

	static const int MAX_BOUND_BULLET = 2;										//階層構造のメンバーの最大数

	CEnemyClock();																//コンストラクタ		
	~CEnemyClock();																//デストラクタ

	HRESULT Init(void) override;												//初期化処理
	void Uninit(void) override;													//終了処理
	void Update(void) override;													//更新処理
	void Draw(void) override;													//描画処理

	static CEnemyClock* Create(D3DXVECTOR3 pos);								//生成処理


private:

	void UpdateClock(void);										//時計型敵の更新処理
	void RespawnNeedle(void);									//時計型敵の弾のリスポーン処理

	CClockNeedle* m_pBoundBullet[MAX_BOUND_BULLET];				//階層構造のオブジェクトへのポインタ
	bool m_bBound[MAX_BOUND_BULLET];							//階層構造のオブジェクトはリリースされたかどうか
	int m_nCntBoundAnimation;									//階層構造アニメーション用のカウンター

};

#endif // !ENEMY_CLOCK_H