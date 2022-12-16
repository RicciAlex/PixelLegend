//=============================================================================
//
// enemy.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef ENEMY_H
#define ENEMY_H

//インクルードファイル
#include "main.h"
#include "object2D.h"

//敵の基本クラス
class CEnemy : public CObject_2D
{
public:
	CEnemy();											//コンストラクタ
	virtual ~CEnemy() override;							//デストラクタ
														
	virtual HRESULT Init(void) override;				//初期化処理
	virtual void Uninit(void) override;					//終了処理
	virtual void Update(void) override;					//更新処理
	virtual void Draw(void) override;					//描画処理
														
	const int GetLife(void);							//体力の取得処理
	void SetLife(const int nLife);						//体力の設定処理
	void SetMaxSpeed(const float maxSpeed);				//最大速度の設定処理
	const float GetMaxSpeed(void);						//最大速度の取得処理
	void SetSubtype(const EnemyType subType);			//敵の種類の設定処理
	const bool GetDamageableState(void);				//ダメージを受けるかどうかの取得処理
	void SetDamageableState(const bool bDamageable);	//ダメージを受けるかどうかの設定処理
	const EnemyType GetSubtype(void);					//敵の種類の取得処理

protected:

	int m_nCntMove;										//アニメーションや移動用のカウンター
	float m_fAngleMove;									//アニメーションや移動用のカウンター
	int m_nPhase;										//アニメーションや移動用のカウンター
	int m_nShootDelay;									//アニメーションや移動用のカウンター

private:

	//void UpdateCloud(void);							//雲型敵の更新処理
														
	int m_nLife;										//敵の体力
	float m_maxSpeed;									//敵の最大速度
	bool m_bDamageable;
	EnemyType m_subType;								//敵の種類
	

};




#endif