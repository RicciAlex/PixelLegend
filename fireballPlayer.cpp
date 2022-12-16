//=============================================================================
//
// fireballPlayer.h
// Author : Ricci Alex
//
//=============================================================================

//インクルードファイル
#include "fireballPlayer.h"
#include "main.h"
#include "explosion.h"
#include "enemy.h"
#include "player.h"
#include "circleHitbox.h"
#include "application.h"
#include "sound.h"

//コンストラクタ
CFireballPlayer::CFireballPlayer()
{
	//メンバー変数をクリアする
	m_fBulletAngle = 0.0f;
	m_fBulletInclination = 0.0f;
	m_BulletVector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_origin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pHitbox = nullptr;
}

//デストラクタ
CFireballPlayer::~CFireballPlayer()
{

}

//初期化処理
HRESULT CFireballPlayer::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CObject_2D::Init()))
	{
		return -1;
	}

	//メンバー変数の初期化
	SetLife(300);										
	m_fBulletAngle = 0.0f;								
	m_fBulletInclination = 0.0f;						
	m_BulletVector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		
	m_origin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			

	return S_OK;
}

//終了処理
void CFireballPlayer::Uninit(void)
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
void CFireballPlayer::Update(void)
{
	CObject_2D::Update();								//基本クラスの更新処理

	D3DXVECTOR3 move = GetMove();
	D3DXVECTOR3 pos = GetPos() + move;					//位置の更新

	//パラメトリック方程式を使って、位置を設定する
	m_fBulletInclination;
	m_BulletVector += D3DXVECTOR3(10.0f, 5.0f * (float)sin(m_fBulletAngle), 0.0f);
	m_fBulletAngle += D3DX_PI * 0.1f;

	pos.x = (m_BulletVector.x - m_origin.x) * cosf(m_fBulletInclination) - (m_BulletVector.y - m_origin.y) * sinf(m_fBulletInclination) + m_origin.x;
	pos.y = (m_BulletVector.x - m_origin.x) * sinf(m_fBulletInclination) + (m_BulletVector.y - m_origin.y) * cosf(m_fBulletInclination) + m_origin.y;

	SetPos(pos);										//位置の設定

	//ヒットボックスの更新処理
	if (m_pHitbox)
	{//nullチェック
		m_pHitbox->SetPos(pos);				//ヒットボックスの位置の更新
	}

	//移動量の更新
	move += GetAcceleration();							
	SetMove(move);

	int nLife = GetLife();

	nLife--;											//寿命の更新

	if (nLife <= 0)
	{//寿命が0になったら

		DestroyBullet();

		return;
	}

	if (pos.x > SCREEN_WIDTH || pos.x < 0.0f || pos.y > SCREEN_HEIGHT || pos.y < 0.0f)
	{//画面を出たら

		Release();										//弾を消す
		return;
	}

	if (Hit())
	{
		CExplosion* pExplosion = nullptr;					//爆発インスタンスへのポインタ

		CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_EXPLOSION);		//爆発のサウンドエフェクト

		pExplosion = CExplosion::Create();				//爆発の生成

		pExplosion->SetPos(pos);						//爆発の位置の設定

		Release();										//弾を消す
		return;
	}
}

//当たり判定
bool CFireballPlayer::Hit(void)
{
	if (m_pHitbox->Hit())
	{
		return true;
	}

	return false;
}

//角度の初期値の設定処理
void CFireballPlayer::SetStartingAngle(const float fAngle)
{
	m_fBulletAngle = fAngle;
}

//==================================================================================================================
//
//		静的関数
//
//==================================================================================================================

//生成処理
CFireballPlayer* CFireballPlayer::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const D3DXVECTOR3 acc, const D3DXVECTOR2 Size)
{
	CFireballPlayer* pBullet = new CFireballPlayer;				//弾を生成する

	if (pBullet != nullptr)
	{
		//初期化処理
		if (FAILED(pBullet->Init()))
		{
			delete pBullet;			//メモリを解放する
			return nullptr;			//nullを返す
		}

		pBullet->SetBulletType(CBullet::BULLET_PLAYER_FIREBALL);
		pBullet->SetPos(pos);									//位置の設定
		pBullet->SetMove(move);									//移動量の設定
		pBullet->SetAcceleration(acc);							//加速の設定
		pBullet->m_BulletVector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pBullet->m_origin = pos;

		D3DXVECTOR3 Vec, unit;
		unit = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		D3DXVec3Normalize(&Vec, &move);
		pBullet->m_fBulletInclination = (float)acos(D3DXVec3Dot(&Vec, &unit));

		if (Vec.y < unit.y)
		{
			pBullet->m_fBulletInclination *= -1.0f;
		}

		pBullet->SetTexture(CObject::TextureFireball);		//テクスチャの設定
		pBullet->SetTextureParameter(8, 4, 2, 3);			//テクスチャパラメータの設定処理
		pBullet->SetSize(Size);								//サイズの設定
		pBullet->m_BulletVector = pos;						//ローカル座標の位置の設定

		//ヒットボックスの生成
		pBullet->m_pHitbox = CCircleHitbox::Create(pos, Size.x, CHitbox::Type_PlayerBullet);

	}

	return pBullet;						//弾を返す
} 