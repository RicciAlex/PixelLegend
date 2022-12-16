//=============================================================================
//
// enemyCloud.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef ENEMY_CLOUD_H
#define ENEMY_CLOUD_H

//インクルードファイル
#include "enemy.h"

class CEnemyCloud : public CEnemy
{
public:
	
	//状態の列挙型
	enum state
	{
		state_pursuit = 0,				//追いかける
		state_aim,						//狙う
		state_fire,						//うつ
		state_flee,						//逃げる
		state_max
	};

	CEnemyCloud();								//コンストラクタ
	~CEnemyCloud() override;					//デストラクタ

	HRESULT Init(void) override;
	void Uninit(void) override;					//終了処理
	void Update(void) override;					//更新処理
	void Draw(void) override;					//描画処理

	static CEnemyCloud* Create(D3DXVECTOR3 pos);			//生成処理

private:

	int m_nCntMove;										//アニメーションや移動用のカウンター
	float m_fAngleMove;									//アニメーションや移動用のカウンター
	state m_nPhase;										//アニメーションや移動用のカウンター
	int m_nShootDelay;									//アニメーションや移動用のカウンター
};

#endif // !ENEMY_CLOUD_H