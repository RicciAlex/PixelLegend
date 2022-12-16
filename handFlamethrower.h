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

	//状態
	enum state
	{
		state_spawn = 0,				//スポーン状態
		state_shoot,					//攻撃状態
		state_return,					//戻る状態
		state_despawn,					//ディスポーン状態
		state_death,					//死亡状態
		state_max
	};

	CHandFlamethrower();															//コンストラクタ
	~CHandFlamethrower() override;													//デストラクタ

	HRESULT Init(void) override;													//初期化処理
	void Uninit(void) override;														//終了処理
	void Update(void) override;														//更新処理

	void SetParent(CWrath* pParent);												//親へのポインタの設定処理

	static CHandFlamethrower* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);						//生成処理

private:

	void updateState(void);					//状態によっての更新処理
											
	state m_state;							//現在の状態
											
	CCircleHitbox* m_pHitbox;				//ヒットボックス
	CWrath* m_pParent;						//親へのポインタ
};




#endif