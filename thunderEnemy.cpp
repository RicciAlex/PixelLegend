//=============================================================================
//
// thunderEnemy.cpp
// Author : Ricci Alex
//
//=============================================================================

//インクルードファイル
#include "thunderEnemy.h"
#include "player.h"
#include "squareHitbox.h"
#include "application.h"
#include "sound.h"


CThunderEnemy::CThunderEnemy()
{
	m_pHitbox = nullptr;
}

CThunderEnemy::~CThunderEnemy()
{

}

//初期化処理
HRESULT CThunderEnemy::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CObject_2D::Init()))
	{
		return -1;
	}

	SetLife(24);
	CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_THUNDER);		//雷のサウンドエフェクト

	return S_OK;
}

//終了処理
void CThunderEnemy::Uninit(void)
{
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}

	//基本クラスの終了処理
	CObject_2D::Uninit();
}

//更新処理
void CThunderEnemy::Update(void)
{
	CObject_2D::Update();								//基本クラスの更新処理

	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Hit();
	}

	int nLife = GetLife();

	nLife--;											//寿命の更新

	if (nLife <= 0)
	{//寿命が0になったら

		DestroyBullet();

		return;
	}
	else
	{
		SetLife(nLife);
	}
}

//==================================================================================================================
//
//		静的関数 
//
//==================================================================================================================

//生成処理
CThunderEnemy* CThunderEnemy::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const D3DXVECTOR3 acc, const D3DXVECTOR2 Size)
{
	CThunderEnemy* pBullet = new CThunderEnemy;				//弾を生成する

	if (pBullet != nullptr)
	{
		//初期化処理
		if (FAILED(pBullet->Init()))
		{
			delete pBullet;			//メモリを解放する
			return nullptr;			//nullを返す
		}

		pBullet->SetBulletType(CBullet::BULLET_THUNDER);
		pBullet->SetPos(pos);									//位置の設定
		pBullet->SetMove(move);									//移動量の設定
		pBullet->SetAcceleration(acc);							//加速の設定

		pBullet->SetTexture(CObject::TextureThunder);		//テクスチャの設定
		pBullet->SetTextureParameter(8, 4, 2, 3);			//テクスチャパラメータの設定処理
		pBullet->SetSize(Size);								//サイズの設定
		pBullet->SetStartingRot(D3DX_PI * 0.5f);			//回転角度の設定

		pBullet->m_pHitbox = CSquareHitbox::Create(pos, Size, CHitbox::Type_EnemyBullet);

	}

	return pBullet;						//弾を返す
}