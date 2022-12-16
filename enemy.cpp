//=============================================================================
//
// enemy.cpp
// Author : Ricci Alex
//
//=============================================================================

//インクルードファイル
#include "enemy.h"
#include "bullet.h"
#include "player.h"
#include <stdlib.h>

//コンストラクタ
CEnemy::CEnemy()
{
	//メンバー変数をクリアする
	m_maxSpeed = 0.0f;
	m_fAngleMove = 0.0f;
	m_nCntMove = 0;
	m_nShootDelay = 0;
	m_bDamageable = false;
	m_subType = ENEMYTYPE_MAX;
}

//デストラクタ
CEnemy::~CEnemy()
{

}

//初期化処理
HRESULT CEnemy::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CObject_2D::Init()))
	{
		return -1;
	}

	m_bDamageable = false;
	SetObjType(OBJTYPE_ENEMY);

	return S_OK;
}

//終了処理
void CEnemy::Uninit(void)
{
	//基本クラスの終了処理
	CObject_2D::Uninit();
}

//更新処理 
void CEnemy::Update(void)
{
	
}

//描画処理
void CEnemy::Draw(void)
{
	CObject_2D::Draw();
}

//体力の取得処理
const int CEnemy::GetLife(void)
{
	return m_nLife;
}

//体力の設定処理
void CEnemy::SetLife(const int nLife)
{
	m_nLife = nLife;
}

//最大速度の設定処理
void CEnemy::SetMaxSpeed(const float maxSpeed)
{
	m_maxSpeed = maxSpeed;
}

//最大スピードの取得処理
const float CEnemy::GetMaxSpeed(void)
{
	return m_maxSpeed;
}

//敵の種類の設定
void CEnemy::SetSubtype(const EnemyType subType)
{
	m_subType = subType;
}

//ダメージを受けるかどうかの取得処理
const bool CEnemy::GetDamageableState(void)
{
	return m_bDamageable;
}

//ダメージを受けるかどうかの設定処理
void CEnemy::SetDamageableState(const bool bDamageable)
{
	m_bDamageable = bDamageable;
}

//敵の種類の取得処理
const CEnemy::EnemyType CEnemy::GetSubtype(void)
{
	return m_subType;
}