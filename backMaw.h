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

	//状態
	enum state
	{
		state_sleep = 0,							//寝る状態
		state_roar,									//鳴き声を出す
		state_shoot,								//攻撃状態
		state_bite,									//嚙む攻撃
		state_awake,								//起きる状態
		state_wait,									//待機状態
		state_return								//戻る状態
	};

	CBackMaw();										//コンストラクタ
	~CBackMaw() override;							//デストラクタ

	HRESULT Init(void) override;					//初期化処理
	void Uninit(void) override;						//終了処理
	void Update(void) override;						//更新処理
	void Draw(void) override;						//描画処理

	void SetState(CBackMaw::state state);			//状態の設定処理

	static CBackMaw* Create(void);					//生成処理

private:

	static const D3DXVECTOR2 m_BackMawSize;			//ヒットボックスのサイズ

	void UpdateState(void);							//状態の更新処理

	D3DXVECTOR3 m_target;							//目的の位置
	state m_state;									//状態
													
	CSquareHitbox* m_pHitbox;						//ヒットボックスへのポインタ
};



#endif