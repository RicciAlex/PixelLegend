//=============================================================================
//
// missile.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "missile.h"
#include "squareHitbox.h"
#include "player.h"
#include "application.h"
#include "sound.h"

//コンストラクタ
CMissile::CMissile()
{
	//メンバー変数をクリアする
	m_state = state_max;
	m_pHitbox = nullptr;
}

//デストラクタ
CMissile::~CMissile()
{

}

//初期化処理
HRESULT CMissile::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CBullet::Init()))
	{
		return -1;
	}

	//メンバー変数を初期化する
	m_state = state_ascend;
	m_pHitbox = nullptr;

	return S_OK;
}

//終了処理
void CMissile::Uninit(void)
{
	//ヒットボックスの破棄処理
	if (m_pHitbox != nullptr)
	{//nullチェック
		m_pHitbox->Release();		//メモリを解放する
		m_pHitbox = nullptr;		//ポインタをnullにする
	}

	//基本クラスの終了処理
	CBullet::Uninit();
}

//更新処理
void CMissile::Update(void)
{
	CObject_2D::Update();				//基本クラスの更新処理
			
	D3DXVECTOR3 pos = GetPos();			//位置の取得
	D3DXVECTOR2 size = GetSize();		//サイズの取得

	switch (m_state)
	{
	case CMissile::state_ascend:

		if (pos.y <= -150.0f)
		{//画面を出たら

			SetStartingRot(D3DX_PI);						//向きを逆にする
			pos.x = CPlayer::GetPlayer()->GetPos().x;		//プレイヤーの同じX座標に設定する

			//速度を0にする
			D3DXVECTOR3 move = GetMove();
			move.x = 0.0f;
			move.y = 0.0f;

			SetAcceleration(D3DXVECTOR3(0.0f, 0.2f, 0.0f));		//加速の設定
			SetPos(pos);										//位置の設定
			SetMove(move);										//速度の設定
			
			m_state = state_descend;							//落ちる状態にする
		}

		break;

	case CMissile::state_descend:

		if (pos.y - 200.0f >= (float)SCREEN_HEIGHT)
		{//画面を出たら、消す
			Release();
			return;
		}

		break;

	case state_strike:



		break;

	default:
		break;
	}

	//ヒットボックスの更新処理
	if (m_pHitbox != nullptr)
	{//nullチェック

		m_pHitbox->SetPos(GetPos());		//ヒットボックスの位置の更新

		if (m_pHitbox->Hit())
		{//何かと当たったら

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_BIG_EXPLOSION);	//爆発のサウンドを再生する
			Release();																//破棄する
			return;
		}
	}
}


//=============================================================================
//
//								静的関数
//
//=============================================================================


//生成処理
CMissile* CMissile::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move)
{
	CMissile* pBullet = new CMissile;		//インスタンスを生成する

	if (FAILED(pBullet->Init()))
	{//初期化処理
		return nullptr;
	}

	pBullet->SetPos(pos);							//位置の設定
	pBullet->SetMove(move);							//速度の設定
	pBullet->SetSize(D3DXVECTOR2(67.5f, 16.5f));	//サイズの設定
	pBullet->SetTexture(CObject::TextureMissile);	//テクスチャの設定
	pBullet->SetTextureParameter(2, 1, 2, 15);		//テクスチャパラメータの設定
	pBullet->SetPriority(2);						//プライオリティの設定

	//ヒットボックスの生成
	pBullet->m_pHitbox = CSquareHitbox::Create(pos ,D3DXVECTOR2(30.0f, 8.0f), CHitbox::Type_EnemyBullet);

	return pBullet;					//生成したインスタンスを返す
}

//生成処理
CMissile* CMissile::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const D3DXVECTOR3 acc)
{
	CMissile* pBullet = new CMissile;			//インスタンスを生成する

	if (FAILED(pBullet->Init()))
	{//初期化処理
		return nullptr;
	}

	pBullet->SetPos(pos);								//位置の設定
	pBullet->SetMove(move);								//速度の設定
	pBullet->SetSize(D3DXVECTOR2(67.5f, 16.5f));		//サイズの設定
	pBullet->SetTexture(CObject::TextureMissile);		//テクスチャの設定
	pBullet->SetTextureParameter(2, 1, 2, 15);			//テクスチャパラメータの設定
	pBullet->SetPriority(2);							//プライオリティの設定
	pBullet->SetAcceleration(acc);						//加速の設定
	pBullet->m_state = state_strike;					//状態の設定
	pBullet->SetStartingRot(D3DX_PI * 0.5f);			//向きの初期値の設定

														//ヒットボックスの生成
	pBullet->m_pHitbox = CSquareHitbox::Create(pos, D3DXVECTOR2(30.0f, 8.0f), CHitbox::Type_EnemyBullet);

	return pBullet;				//生成したインスタンスを返す
}