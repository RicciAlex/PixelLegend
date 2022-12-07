//=============================================================================
//
// handFlamethrower.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef HAND_FLAMETHROWER_H
#define HAND_FLAMETHROWER_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "enemy.h"

//=============================================================================
//前方宣言
//=============================================================================
class CCircleHitbox;
class CWrath;

class CHandFlamethrower : public CEnemy
{
public:

	enum state
	{
		state_spawn = 0,
		state_shoot,
		state_return,
		state_despawn,
		state_death,
		state_max
	};

	CHandFlamethrower();																		//コンストラクタ
	~CHandFlamethrower() override;															//デストラクタ

	HRESULT Init(void) override;													//初期化処理
	void Uninit(void) override;														//終了処理
	void Update(void) override;														//更新処理

	void SetParent(CWrath* pParent);

	static CHandFlamethrower* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);						//生成処理

private:

	void updateState(void);

	state m_state;

	CCircleHitbox* m_pHitbox;
	CWrath* m_pParent;
};




#endif