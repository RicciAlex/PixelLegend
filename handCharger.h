//=============================================================================
//
// handCharger.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef HAND_CHARGER_H
#define HAND_CHARGER_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "enemy.h"

//=============================================================================
//前方宣言
//=============================================================================
class CSquareHitbox;
class CWrath;

class CHandCharger : public CEnemy
{
public:

	enum state
	{
		state_spawn = 0,
		state_attack,
		state_return,
		state_despawn,
		state_death,
		state_max
	};

	CHandCharger();																		//コンストラクタ
	~CHandCharger() override;															//デストラクタ

	HRESULT Init(void) override;													//初期化処理
	void Uninit(void) override;														//終了処理
	void Update(void) override;														//更新処理

	void SetParent(CWrath* pParent);

	static CHandCharger* Create(D3DXVECTOR3 pos);						//生成処理

private:

	void UpdateState(void);

	D3DXVECTOR3 m_targetPos;
	state m_state;

	CSquareHitbox* m_pHitbox;
	CWrath* m_pParent;
};




#endif