//=============================================================================
//
// clockNeedle.cpp
// Author : Ricci Alex
//
//=============================================================================

//インクルードファイル
#include "clockNeedle.h"
#include "player.h"

CClockNeedle::CClockNeedle()
{

}

CClockNeedle::~CClockNeedle()
{

} 

//初期化処理
HRESULT CClockNeedle::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CObject_2D::Init()))
	{
		return -1;
	}

	SetBulletType(CBullet::BULLET_CLOCK_NEEDLE);

	SetTexture(CObject::TextureClockNeedle);	//テクスチャの設定
	SetTextureParameter(1, 1, 1, INT_MAX);		//テクスチャパラメータの設定処理

	return S_OK;
}

//終了処理
void CClockNeedle::Uninit(void)
{
	//基本クラスの終了処理
	CObject_2D::Uninit();
}

//更新処理
void CClockNeedle::Update(void)
{
	int nLife = GetLife();

	nLife--;											//寿命の更新

	if (nLife <= 0)
	{//寿命が0になったら

		DestroyBullet();

		return;
	}

	SetLife(nLife);										//ライフの設定

	CObject_2D::Update();								//基本クラスの更新処理

	D3DXVECTOR3 move = GetMove();
	D3DXVECTOR3 pos = GetPos() + move;					//位置の更新

	SetPos(pos);										//位置の設定

	move += GetAcceleration();							//移動量の更新
	SetMove(move);		

	if (pos.x > SCREEN_WIDTH || pos.x < 0.0f || pos.y > SCREEN_HEIGHT || pos.y < 0.0f)
	{//画面を出たら

		Release();										//弾を消す
		return;
	}
}

//当たり判定
bool CClockNeedle::Hit(void)
{
	D3DXVECTOR3 pos = GetPos();								//弾の位置の取得

	CPlayer* pPlayer = CPlayer::GetPlayer();					//プレイヤー情報の取得
	D3DXVECTOR3 PosPlayer = pPlayer->GetPos();					//プレイヤーの位置の取得
	D3DXVECTOR2 size = GetSize();								//弾のサイズの取得
	D3DXVECTOR2 SizePlayer = pPlayer->GetSize();				//プレイヤーのサイズの取得

																//当たり判定
	if (CObject::HitBox(&pos, &PosPlayer, size, SizePlayer))
	{
		return true;
	}

	return false;
}

//==================================================================================================================
//
//		静的関数
//
//==================================================================================================================

//生成処理
CClockNeedle* CClockNeedle::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const D3DXVECTOR3 acc, const D3DXVECTOR2 Size)
{
	CClockNeedle* pBullet = new CClockNeedle;				//弾を生成する

	if (pBullet != nullptr)
	{
		//初期化処理
		if (FAILED(pBullet->Init()))
		{
			return nullptr;			//nullを返す
		}

		
		pBullet->SetPos(pos);									//位置の設定
		pBullet->SetMove(move);									//移動量の設定
		pBullet->SetAcceleration(acc);							//加速の設定

		pBullet->SetSize(Size);								//サイズの設定
		pBullet->SetLife(INT_MAX);							//寿命の設定
		pBullet->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));	//速度の設定

	}

	return pBullet;						//弾を返す
}