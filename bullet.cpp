//=============================================================================
//
// bullet.cpp
// Author : Ricci Alex
//
//=============================================================================

//インクルードファイル
#include "bullet.h"
#include "main.h"
#include "explosion.h"
#include "enemy.h"
#include "player.h"

//コンストラクタ
CBullet::CBullet()
{
	//メンバー変数をクリアする
	m_nLife = 0;
}

//デストラクタ
CBullet::~CBullet()
{

}

//初期化処理
HRESULT CBullet::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CObject_2D::Init()))
	{
		return -1;
	}

	m_nLife = 0;
	CObject::SetObjType(CObject::OBJTYPE_BULLET);

	return S_OK;
}

//終了処理
void CBullet::Uninit(void)
{
	//基本クラスの終了処理
	CObject_2D::Uninit();
}

//更新処理
void CBullet::Update(void)
{
	CObject_2D::Update();								//基本クラスの更新処理

	D3DXVECTOR3 pos = GetPos();			//位置の取得
	D3DXVECTOR2 size = GetSize();		//サイズの取得

	if (pos.x + size.x <= 0.0f || pos.x + size.x >= (float)SCREEN_WIDTH ||
		pos.y + size.y <= 0.0f || pos.y - size.y >= (float)SCREEN_HEIGHT)
	{//画面を出たら、消す
		Release();
		return;
	}
	
} 

//寿命の取得処理
int CBullet::GetLife(void)
{
	return m_nLife;
}

//寿命の設定処理
void CBullet::SetLife(const int life)
{
	m_nLife = life;
}

//弾の種類の取得処理
CBullet::BULLET_TYPE CBullet::GetBulletType(void)
{
	return m_BulletType;
}

//弾の種類の設定処理
void CBullet::SetBulletType(BULLET_TYPE type)
{
	m_BulletType = type;
}

//==================================================================================================================
//
//											静的関数
//
//==================================================================================================================

//弾の破棄処理
void CBullet::DestroyBullet(void)
{
	D3DXVECTOR3 pos = GetPos();							//位置の取得
	CExplosion* pExplosion = nullptr;

	if (m_BulletType == BULLET_FIREBALL)
	{
		pExplosion = CExplosion::Create();				//爆発の生成

		pExplosion->SetPos(pos);						//爆発の位置の設定

	}

	Release();											//弾を消す
}