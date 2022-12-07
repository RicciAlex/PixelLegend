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

	enum state
	{
		state_spawn = 0,
		state_normal,
		state_walk,
		state_shot,
		state_rage,
		state_death,
		state_max
	};

	CGreed();												//コンストラクタ
	~CGreed();												//デストラクタ

	HRESULT Init(void) override;							//初期化処理
	void Uninit(void) override;								//終了処理
	void Update(void) override;								//更新処理
	void Draw(void) override;								//描画処理

	const bool GetEnd(void);

	static CGreed* Create(void);							//生成処理

private:

	static const int nTargetNum = 5;
	static const int MaxTower = 2;
	static const D3DXVECTOR3 TargetPos[nTargetNum];

	bool m_bEnd;
	float m_fSumAngle;
	float m_fShotAngle;
	int m_targetIdx;
	int m_nAnimCnt;
	int m_nTowerDelay;
	state m_state;

	D3DXVECTOR3 m_HitboxUpRelativePos;
	D3DXVECTOR3 m_HitboxDownRelativePos;

	CCircleHitbox* m_pHitboxUp;
	CSquareHitbox* m_pHitboxDown;
	CTowerJewel* m_pTower[MaxTower];
	CEnemyLife* m_pLife;
};






#endif