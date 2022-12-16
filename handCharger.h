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

	//状態
	enum state
	{
		state_spawn = 0,			//スポーン状態
		state_attack,				//攻撃状態
		state_return,				//戻る状態
		state_despawn,				//ディスポーン状態
		state_death,				//死亡状態
		state_max
	};

	CHandCharger();										//コンストラクタ
	~CHandCharger() override;							//デストラクタ

	HRESULT Init(void) override;						//初期化処理
	void Uninit(void) override;							//終了処理
	void Update(void) override;							//更新処理

	void SetParent(CWrath* pParent);					//親へのポインタの設定処理

	static CHandCharger* Create(D3DXVECTOR3 pos);		//生成処理

private:

	void UpdateState(void);					//状態によっての更新処理
											
	D3DXVECTOR3 m_targetPos;				//目的の位置
	state m_state;							//現在の状態
											
	CSquareHitbox* m_pHitbox;				//ヒットボックス
	CWrath* m_pParent;						//親へのポインタ
};




#endif