//=============================================================================
//
// pride.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef PRIDE_H
#define PRIDE_H

//インクルードファイル
#include "enemy.h"

//前方宣言
class CCircleHitbox;
class CEnemyLife;

class CPride : public CEnemy
{
public:

	//状態
	enum State
	{
		state_Spawn = 0,			//スポーン
		state_Normal,				//普通
		state_Hide,					//隠す
		state_BouncingBall,			//玉弾
		state_Star,					//星弾
		state_LaughAttack,			//笑う
		state_CreateEnemy,			//召喚
		state_Balloon,				//風船
		state_LaughAnim,			//笑うアニメーション
		state_Death,				//死亡
		state_Max
	};

	CPride();									//コンストラクタ
	~CPride() override;							//デストラクタ

	HRESULT Init(void) override;				//初期化処理
	void Uninit(void) override;					//終了処理
	void Update(void) override;					//更新処理
	void Draw(void) override;					//描画処理

	const bool GetEnd(void);					//終わったかどうかの取得処理

	static CPride* Create(void);				//生成処理

private:

	void UpdateState(void);						//状態によっての更新処理

	State m_state;								//状態
	int m_nSpawnFrame;							//召喚フレーム
	bool m_bEnd;								//終わったかどうか

	CCircleHitbox* m_pHitbox;					//ヒットボックスへのポインタ
	CEnemyLife* m_pLife;						//体力UIへのポインタ
};

#endif