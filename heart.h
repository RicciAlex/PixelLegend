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

	enum state
	{
		state_spawn = 0,
		state_awake,
		state_sleep,
		state_vulnerable,
		state_return,
		state_death,
		state_max
	};

	CHeart();
	~CHeart() override;								//デストラクタ

	HRESULT Init(void) override;					//初期化処理
	void Uninit(void) override;						//終了処理
	void Update(void) override;						//更新処理
	void Draw(void) override;						//描画処理

	void SetActive(void);
	const bool GetEnd(void);

	static CHeart* Create(void);					//生成処理



private:

	void UpdateState(void);

	
	bool m_bEnd;
	float m_fAngleShoot;
	state m_state;

	CSquareHitbox* m_pHitbox;
	CEnemyLife* m_pLife;
};

#endif