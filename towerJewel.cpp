//=============================================================================
//
// towerJewel.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "towerJewel.h"
#include "circleHitbox.h"
#include "greedBullet.h"
#include "application.h"
#include "sound.h"

//コンストラクタ
CTowerJewel::CTowerJewel()
{
	//メンバー変数をクリアする
	m_state = state_spawn;

	m_pHitBox = nullptr;
}

//デストラクタ
CTowerJewel::~CTowerJewel()
{

}

//初期化処理
HRESULT CTowerJewel::Init(void)
{
	//メンバー変数を初期化する
	if (FAILED(CEnemy::Init()))
	{//基本クラスの初期化処理
		return -1;
	}

	m_state = state_wait;

	m_pHitBox = nullptr;

	return S_OK;
}

//終了処理
void CTowerJewel::Uninit(void)
{
	//ヒットボックスの破棄処理
	if (m_pHitBox != nullptr)
	{//nullチェック
		m_pHitBox->Release();			//メモリを解放する
		m_pHitBox = nullptr;			//nullにする
	}
}

//更新処理
void CTowerJewel::Update(void)
{
	//ヒットボックスの更新
	if (m_pHitBox != nullptr)
	{//nullチェック
		m_pHitBox->SetPos(GetPos());			//位置の設定
	}

	switch (m_state)
	{//状態によって更新する

	case CTowerJewel::state_spawn:

	{//スポーン状態
		D3DXVECTOR3 pos = GetPos();							//位置の取得
		D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//速度

		//移動量の設定
		if (pos.x < (float)SCREEN_WIDTH * 0.5f)
		{
			move.x = 2.0f;
		}
		else
		{
			move.x = -2.0f;
		}

		if (pos.x >= 100.0f && move.x > 0.0f || pos.x < (float)SCREEN_WIDTH - 100.0f && move.x < 0.0f)
		{//決まった座標を超えたら、状態を変える
			move.x = 0.0f;				//移動量を0にする
			m_state = state_shoot;		//状態の設定
		}

		SetMove(move);					//移動量の設定
	}

		break;

	case CTowerJewel::state_shoot:

	{//ショット状態

		D3DXVECTOR3 pos = GetPos();									//位置の取得
		D3DXVECTOR3 move = D3DXVECTOR3(4.0f, 0.0f, 0.0f);			//速度

		//速度の設定
		if (pos.x > (float)SCREEN_WIDTH * 0.5f)
		{
			move.x *= -1.0f;
		}

		m_nShootDelay++;				//カウンターをインクリメントする

		CGreedBullet* pBullet = nullptr;
		int a = GetPresentAnimPattern();

		if (m_nShootDelay % 30 == 29)
		{//30フレームが経ったら

			//弾の生成
			pBullet = CGreedBullet::Create(pos, move);

			//サウンドを再生する
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_SHOT);

			if (pBullet != nullptr)
			{//生成出来たら
				pBullet->SetTexture(TextureJewel);		//テクスチャの設定
				pBullet->SetAnimPattern(a);				//アニメションパターンの設定
				pBullet = nullptr;						
			}
		}
		if (m_nShootDelay % 60 == 59)
		{//60フレームが経ったら
			move.y = 1.0f;				//弾の移動量のY座標の設定

			//弾の生成
			pBullet = CGreedBullet::Create(pos, move);

			if (pBullet != nullptr)
			{	//生成出来たら
				pBullet->SetTexture(TextureJewel);		//テクスチャの設定
				pBullet->SetAnimPattern(a);				//アニメションパターンの設定
				pBullet = nullptr;
			}

			move.y = -1.0f;				//弾の移動量のY座標の設定
			//弾の生成
			pBullet = CGreedBullet::Create(pos, move);

			if (pBullet != nullptr)
			{//生成出来たら
				pBullet->SetTexture(TextureJewel);		//テクスチャの設定
				pBullet->SetAnimPattern(a);				//アニメションパターンの設定
				pBullet = nullptr;
			}
		}
		if (m_nShootDelay >= 90)
		{//90フレームが経ったら
			move.y = 1.0f;				//弾の移動量のY座標の設定
			//弾の生成
			pBullet = CGreedBullet::Create(pos, move);

			if (pBullet != nullptr)
			{//生成出来たら
				pBullet->SetTexture(TextureJewel);			//テクスチャの設定
				pBullet->SetAnimPattern(a);					//アニメションパターンの設定
				pBullet = nullptr;
			}

			move.y = -1.0f;				//弾の移動量のY座標の設定
			//弾の生成
			pBullet = CGreedBullet::Create(pos, move);

			if (pBullet != nullptr)
			{//生成出来たら
				pBullet->SetTexture(TextureJewel);			//テクスチャの設定
				pBullet->SetAnimPattern(a);					//アニメションパターンの設定
				pBullet = nullptr;
			}

			move.y = 2.0f;				//弾の移動量のY座標の設定
			//弾の生成
			pBullet = CGreedBullet::Create(pos, move);

			if (pBullet != nullptr)
			{//生成出来たら
				pBullet->SetTexture(TextureJewel);			//テクスチャの設定
				pBullet->SetAnimPattern(a);					//アニメションパターンの設定
				pBullet = nullptr;
			}

			move.y = -2.0f;				//弾の移動量のY座標の設定
			//弾の生成
			pBullet = CGreedBullet::Create(pos, move);

			if (pBullet != nullptr)
			{//生成出来たら
				pBullet->SetTexture(TextureJewel);			//テクスチャの設定
				pBullet->SetAnimPattern(a);					//アニメションパターンの設定
				pBullet = nullptr;
			}

			m_nShootDelay = 0;			//カウンターを0に戻す

			//速度の設定
			if (pos.x < (float)SCREEN_WIDTH * 0.5f)
			{
				SetMove(D3DXVECTOR3(-2.0f, 0.0f, 0.0f));
			}
			else
			{
				SetMove(D3DXVECTOR3(2.0f, 0.0f, 0.0f));
			}

			m_state = state_despawn;	//状態の更新
		}
	}

		break;

	case CTowerJewel::state_despawn:

	{//ディスポーン状態

		D3DXVECTOR3 pos = GetPos();			//位置の取得
		D3DXVECTOR3 move = GetMove();		//速度の取得

		if (move.x < 0.0f)
		{//画面の左側のほうへ移動したら
			if (pos.x <= -100.0f)
			{//-100.0fを超えたら、状態を切り替える
				SetAnimPattern(random(0, 5));				//アニメションパターンの設定
				SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//移動の設定
				m_state = state_wait;						//状態の設定
			}
		}
		else
		{//画面の右側のほうへ移動したら
			if (pos.x >= (float)SCREEN_WIDTH + 100.0f)
			{//+100.0fを超えたら、状態を切り替える
				SetAnimPattern(random(0, 5));				//アニメションパターンの設定
				SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//移動の設定
				m_state = state_wait;						//状態の設定
			}
		}
	}

		break;

	case CTowerJewel::state_wait:
		break;

	default:
		break;
	}

	//基本クラスの更新処理
	CObject_2D::Update();
}

//状態の設定処理
void CTowerJewel::SetState(CTowerJewel::state state)
{
	m_state = state;
}


//生成処理
CTowerJewel* CTowerJewel::Create(const D3DXVECTOR3 pos)
{
	CTowerJewel* pEnemy = new CTowerJewel;			//インスタンスを生成する

	if (FAILED(pEnemy->Init()))
	{//初期化処理
		return nullptr;
	}

	pEnemy->SetPos(pos);								//位置の設定
	pEnemy->SetSize(D3DXVECTOR2(50.0f, 36.8f));			//サイズの設定
	pEnemy->SetTexture(CObject::TextureJewel);			//テクスチャの設定
	pEnemy->SetTextureParameter(1, 3, 2, INT_MAX);		//テクスチャパラメータの設定
	pEnemy->SetAnimPattern(random(0, 5));				//アニメションパターンの設定
	pEnemy->SetStartingRot(D3DX_PI * 0.5f);				//向きの初期値の設定

	//ヒットボックスの生成
	pEnemy->m_pHitBox = CCircleHitbox::Create(pos, 30.0f, CHitbox::Type_Enemy);

	return pEnemy;					//生成したインスタンスを返す
}