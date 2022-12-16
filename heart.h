//=============================================================================
//
// heart.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef HEART_H
#define HEART_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "enemy.h"

//=============================================================================
//前方宣言
//=============================================================================
class CSquareHitbox;
class CEnemyLife;

class CHeart : public CEnemy
{
public:

	//状態
	enum state
	{
		state_spawn = 0,		//スポーン状態
		state_awake,			//起きる状態
		state_sleep,			//寝る状態
		state_vulnerable,		//ダメージを受ける状態
		state_return,			//戻る状態
		state_death,			//死亡状態
		state_max
	};
		
	CHeart();										//コンストラクタ
	~CHeart() override;								//デストラクタ

	HRESULT Init(void) override;					//初期化処理
	void Uninit(void) override;						//終了処理
	void Update(void) override;						//更新処理
	void Draw(void) override;						//描画処理

	void SetActive(void);							//起きる状態の設定処理
	const bool GetEnd(void);						//終わったかどうかの終了処理

	static CHeart* Create(void);					//生成処理

private:

	void UpdateState(void);				//状態によっての更新処理

	
	bool m_bEnd;						//終わったかどうか
	float m_fAngleShoot;				//攻撃角度
	state m_state;						//状態
										
	CSquareHitbox* m_pHitbox;			//ヒットボックス
	CEnemyLife* m_pLife;				//体力UI
};

#endif