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


//コンストラクタ
CThunderEnemy::CThunderEnemy()
{
	//メンバー変数をクリアする
	m_pHitbox = nullptr;
}

//デストラクタ
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

	//メンバー変数を初期化する
	SetLife(24);
	CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_THUNDER);		//雷のサウンドエフェクト

	return S_OK;
}

//終了処理
void CThunderEnemy::Uninit(void)
{
	//ヒットボックスの破棄処理
	if (m_pHitbox != nullptr)
	{//nullチェック
		m_pHitbox->Release();			//メモリを解放する
		m_pHitbox = nullptr;			//ポインタをnullにする
	}

	//基本クラスの終了処理
	CObject_2D::Uninit();
}

//更新処理
void CThunderEnemy::Update(void)
{
	CObject_2D::Update();								//基本クラスの更新処理

	//ヒットボックスの破棄処理
	if (m_pHitbox != nullptr)
	{//nullチェック
		m_pHitbox->Hit();					//当たったかどうか確認する
	}

	int nLife = GetLife();					//体力の取得

	nLife--;								//体力の更新

	if (nLife <= 0)
	{//体力が0になったら

		DestroyBullet();					//破棄する

		return;
	}
	else
	{//体力が0以上だったら

		SetLife(nLife);						//体力を設定する
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

		//ヒットボックスの生成
		pBullet->m_pHitbox = CSquareHitbox::Create(pos, Size, CHitbox::Type_EnemyBullet);

	}

	return pBullet;						//弾を返す
}