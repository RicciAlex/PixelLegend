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
		state_Spawn = 0,
		state_Normal,
		state_Hide,
		state_BouncingBall,
		state_Star,
		state_LaughAttack,
		state_CreateEnemy,
		state_Balloon,
		state_LaughAnim,
		state_Death,
		state_Max
	};

	CPride();									//コンストラクタ
	~CPride() override;							//デストラクタ

	HRESULT Init(void) override;				//初期化処理
	void Uninit(void) override;					//終了処理
	void Update(void) override;					//更新処理
	void Draw(void) override;					//描画処理

	const bool GetEnd(void);

	static CPride* Create(void);				//生成処理

private:

	State m_state;								//状態
	int m_nSpawnFrame;
	bool m_bEnd;

	CCircleHitbox* m_pHitbox;
	CEnemyLife* m_pLife;
};

#endif