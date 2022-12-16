//=============================================================================
//
// greed.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef GREED_H
#define GREED_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "enemy.h"

//=============================================================================
//前方宣言
//=============================================================================
class CSquareHitbox;
class CCircleHitbox;
class CTowerJewel;
class CEnemyLife;

class CGreed : public CEnemy
{
public:

	//状態
	enum state
	{
		state_spawn = 0,		//スポーン状態
		state_normal,			//普通の状態
		state_walk,				//移動状態
		state_shot,				//攻撃状態
		state_rage,				//怒り攻撃
		state_death,			//死亡状態
		state_max
	};

	CGreed();												//コンストラクタ
	~CGreed();												//デストラクタ

	HRESULT Init(void) override;							//初期化処理
	void Uninit(void) override;								//終了処理
	void Update(void) override;								//更新処理
	void Draw(void) override;								//描画処理

	const bool GetEnd(void);								//終わったかどうかの取得処理

	static CGreed* Create(void);							//生成処理

private:

	void UpdateState(void);									//状態によっての更新処理

	static const int nTargetNum = 5;						//目的の位置の数
	static const int MaxTower = 2;							//左右から攻撃する敵の数
	static const D3DXVECTOR3 TargetPos[nTargetNum];			//目的の位置

	bool m_bEnd;								//終わったかどうか
	float m_fSumAngle;							//攻撃用の角度
	float m_fShotAngle;							//攻撃の間の角度
	int m_targetIdx;							//目的の位置のインデックス
	int m_nAnimCnt;								//アニメーション用のカウンター
	int m_nTowerDelay;							//左右の敵のの攻撃のディレイ
	state m_state;								//状態
												
	D3DXVECTOR3 m_HitboxUpRelativePos;			//体の上側のヒットボックスの相対位置
	D3DXVECTOR3 m_HitboxDownRelativePos;		//体の下側のヒットボックスの相対位置
												
	CCircleHitbox* m_pHitboxUp;					//体の上側のヒットボックスへのポインタ
	CSquareHitbox* m_pHitboxDown;				//体の下側のヒットボックスへのポインタ
	CTowerJewel* m_pTower[MaxTower];			//左右の敵へのポインタ
	CEnemyLife* m_pLife;						//体力UIへのポインタ
};






#endif