//=============================================================================
//
// backMaw.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef BACK_MAW_H
#define BACK_MAW_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "enemy.h"

//=============================================================================
//前方宣言
//=============================================================================
class CSquareHitbox;

class CBackMaw : public CEnemy
{
public:

	enum state
	{
		state_sleep = 0,
		state_roar,
		state_shoot,
		state_bite,
		state_awake,
		state_wait,
		state_return
	};

	CBackMaw();
	~CBackMaw() override;

	HRESULT Init(void) override;					//初期化処理
	void Uninit(void) override;						//終了処理
	void Update(void) override;						//更新処理
	void Draw(void) override;						//描画処理

	void SetState(CBackMaw::state state);			//状態の設定処理

	static CBackMaw* Create(void);					//生成処理

private:

	void UpdateState(void);							//状態の更新処理

	D3DXVECTOR3 m_target;
	state m_state;

	CSquareHitbox* m_pHitbox;
};



#endif