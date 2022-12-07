//=============================================================================
//
// bullet.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef BULLET_H
#define BULLET_H

//インクルードファイル
#include "object2D.h"

//弾クラス(CObject2Dの派生クラス)
class CBullet : public CObject_2D
{
public:

	//弾の種類
	enum BULLET_TYPE
	{
		BULLET_FIREBALL = 0,
		BULLET_PLAYER_FIREBALL,
		BULLET_THUNDER,
		BULLET_BLACKHOLE,
		BULLET_CLOCK_NEEDLE,
		BULLET_BEAM,
		BULLET_HEART,
		BULLET_SKULL_FIREBALL,
		BULLET_TYPE_MAX
	};

	CBullet();																				//コンストラクタ
	virtual ~CBullet();																		//デストラクタ

	virtual HRESULT Init(void) override;													//初期化処理
	virtual void Uninit(void) override;														//終了処理
	virtual void Update(void) override;														//更新処理

	void DestroyBullet(void);																//弾の破棄処理

	int GetLife(void);																		//ライフの取得処理
	void SetLife(const int life);															//ライフの設定処理
	BULLET_TYPE GetBulletType(void);														//弾の種類の取得処理
	void SetBulletType(BULLET_TYPE type);													//弾の種類の設定処理

private:
	
	int m_nLife;						//寿命
	BULLET_TYPE m_BulletType;			//弾の種類
};

#endif // !BULLET_H