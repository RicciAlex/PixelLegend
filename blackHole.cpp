//=============================================================================
//
// blackHole.cpp
// Author : Ricci Alex
//
//=============================================================================

//インクルードファイル
#include "blackHole.h"
#include "player.h"

//コンストラク
CBlackHole::CBlackHole()
{

}

//デストラクタ
CBlackHole::~CBlackHole()
{
	 
}

//初期化処理
HRESULT CBlackHole::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CObject_2D::Init()))
	{
		return -1;
	}

	return S_OK;
}

//終了処理
void CBlackHole::Uninit(void)
{
	//基本クラスの終了処理
	CObject_2D::Uninit();
}

//更新処理
void CBlackHole::Update(void)
{
	CObject_2D::Update();								//基本クラスの更新処理

	CPlayer* pPlayer = CPlayer::GetPlayer();			//プレイヤー情報の取得処理
	D3DXVECTOR3 pos, PosPlayer, Dir;
	pos = GetPos();										//弾の位置の取得
	PosPlayer = pPlayer->GetPos();						//プレイヤーの位置の取得
	Dir = pos - PosPlayer;								//向きを計算する
	D3DXVec3Normalize(&Dir, &Dir);						//向きを正規化する
	Dir.x *= 3.0f;
	Dir.y *= 3.0f;
	PosPlayer += Dir;									//プレイヤーの位置の更新
	pPlayer->SetPos(PosPlayer);							//プレイヤーの位置の設定

	int nLife = GetLife();
	nLife--;											//寿命の更新

	if (nLife <= 0)
	{//寿命が0になったら

		DestroyBullet();			//破棄する

		return;
	}
	
	SetLife(nLife);					//寿命の設定
}	



//=============================================================================
//
//								静的関数
//
//=============================================================================



//生成処理
CBlackHole* CBlackHole::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const D3DXVECTOR3 acc, const D3DXVECTOR2 size, const int nLife)
{
	CBlackHole* pBullet = new CBlackHole;				//弾を生成する

	if (pBullet != nullptr)
	{
		//初期化処理
		if (FAILED(pBullet->Init()))
		{
			return nullptr;			//生成できなかったら、nullを返す
		}

		pBullet->SetBulletType(CBullet::BULLET_BLACKHOLE);
		pBullet->SetPos(pos);									//位置の設定
		pBullet->SetMove(move);									//移動量の設定
		pBullet->SetAcceleration(acc);							//加速の設定

		pBullet->SetTexture(CObject::TextureBlackHole);		//テクスチャの設定
		pBullet->SetTextureParameter(1, 1, 1, INT_MAX);		//テクスチャパラメータの設定処理
		pBullet->SetSize(size);								//サイズの設定
		pBullet->SetLife(nLife);							//寿命の設定

	}

	return pBullet;						//弾を返す
}