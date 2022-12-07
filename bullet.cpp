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

	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR2 size = GetSize();

	if (pos.x + size.x <= 0.0f || pos.x + size.x >= (float)SCREEN_WIDTH ||
		pos.y + size.y <= 0.0f || pos.y - size.y >= (float)SCREEN_HEIGHT)
	{
		Release();
		return;
	}
	
} 

int CBullet::GetLife(void)
{
	return m_nLife;
}

void CBullet::SetLife(const int life)
{
	m_nLife = life;
}

CBullet::BULLET_TYPE CBullet::GetBulletType(void)
{
	return m_BulletType;
}

void CBullet::SetBulletType(BULLET_TYPE type)
{
	m_BulletType = type;
}

//==================================================================================================================
//
//		静的関数
//
//==================================================================================================================

//CBullet* CBullet::Create(void)
//{
//	CBullet* pBullet = nullptr;
//
//	pBullet = new CBullet;
//
//	if (FAILED(pBullet->Init()))
//	{
//		if (pBullet != nullptr)
//		{
//			delete pBullet;
//			pBullet = nullptr;
//		}
//
//		return nullptr;
//	}
//
//	return pBullet;
//}

//弾の破棄処理
void CBullet::DestroyBullet(void)
{
	D3DXVECTOR3 pos = GetPos();
	CExplosion* pExplosion = nullptr;

	if (m_BulletType == BULLET_FIREBALL)
	{
		pExplosion = CExplosion::Create();				//爆発の生成

		pExplosion->SetPos(pos);						//爆発の位置の設定

	}
	Release();											//弾を消す
}