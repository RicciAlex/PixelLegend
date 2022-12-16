//=============================================================================
//
// heart.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "heart.h"
#include "squareHitbox.h"
#include "heartBullet.h"
#include "player.h"
#include "enemyLife.h"

//コンストラクタ
CHeart::CHeart()
{
	//メンバー変数をクリアする
	m_fAngleShoot = 0.0f;
	m_state = state_spawn;

	m_bEnd = false;

	m_pLife = nullptr;
	m_pHitbox = nullptr;
}

//デストラクタ
CHeart::~CHeart()
{

}

//初期化処理
HRESULT CHeart::Init(void)
{
	if (FAILED(CEnemy::Init()))
	{//基本クラスの初期化処理
		return -1;
	}

	//メンバー変数を初期化する
	m_fAngleShoot = 0.0f;
	m_state = state_spawn;
	m_bEnd = false;

	m_pLife = nullptr;
	m_pHitbox = nullptr;

	return S_OK;
}

//終了処理
void CHeart::Uninit(void)
{
	//ヒットボックスの破棄処理
	if (m_pHitbox != nullptr)
	{//nullチェック
		m_pHitbox->Release();		//メモリを解放する
		m_pHitbox = nullptr;		//ポインタをnullにする
	}

	//体力UIの破棄処理
	if (m_pLife != nullptr)
	{//nullチェック
		m_pLife->Release();			//メモリを解放する
		m_pLife = nullptr;			//ポインタをnullにする
	}

	//基本クラスの終了処理
	CEnemy::Uninit();
}

//更新処理
void CHeart::Update(void)
{
	//状態によっての更新処理
	UpdateState();

	//基本クラスの更新処理
	CObject_2D::Update();

	//ヒットボックスの更新処理
	if (m_pHitbox != nullptr)
	{//nullチェック

		if (m_pHitbox->GetHitState())
		{//終わった状態だったら、

			m_pHitbox->SetHitState(false);			//当っていない状態に戻す

			int nDamage = CPlayer::GetPlayer()->GetAttack();		//プレイヤーの攻撃力の取得

			int nLife = GetLife();					//体力の取得
				
			nLife -= nDamage;						//体力の更新

			//体力UIの更新
			if (m_pLife != nullptr)
			{//nullチェック
				m_pLife->SubtractLife(nDamage);
			}

			if (nLife <= 0)
			{//体力が0以下になったら

				m_state = state_death;	//死亡状態にする
				m_pHitbox->Release();	//ヒットボックスを破棄する
				m_pHitbox = nullptr;	//ヒットボックスへのポインタをnullにする
				SetLife(0);				//体力の設定
				m_nCntMove = 0;			//移動カウンターを0にする
			}
			else
			{//体力が0以下ではなかったら
				SetLife(nLife);			//体力の設定
			}
		}
	}
}

//描画処理
void CHeart::Draw(void)
{
	//基本クラスの描画処理
	CObject_2D::Draw();
}

//起きる状態の設定処理
void CHeart::SetActive(void)
{
	m_state = state_awake;						//状態の設定
	SetMove(D3DXVECTOR3(0.0f, 1.0f, 0.0f));		//速度の設定
}

//終わったかどうかの設定処理
const bool CHeart::GetEnd(void)
{
	return m_bEnd;
}



//=============================================================================
//
//								静的関数
//
//=============================================================================



//生成処理
CHeart* CHeart::Create(void)
{
	CHeart* pEnemy = new CHeart;			//インスタンスを生成する

	if (FAILED(pEnemy->Init()))
	{//初期化処理
		return nullptr;
	}

	pEnemy->SetPos(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, 150.0f, 0.0f));		//位置の設定
	pEnemy->SetSize(D3DXVECTOR2(70.0f, 103.6f));								//サイズの設定
	pEnemy->SetStartingRot(D3DX_PI * 0.5f);										//向きの初期値の設定
	pEnemy->SetTexture(CObject::TextureGluttonyHeart);							//テクスチャの設定
	pEnemy->SetTextureParameter(2, 2, 1, 20);									//テクスチャパラメータの設定
	pEnemy->SetPriority(2);														//プライオリティの設定
	pEnemy->SetLife(10000);														//体力の設定

	//ヒットボックスの生成
	pEnemy->m_pLife = CEnemyLife::Create(D3DXVECTOR3(850.0f, 40.0f, 0.0f), D3DXCOLOR(0.0f, 1.0f, 0.3f, 0.5f), 10000, "gluttony");

	return pEnemy;					//生成したインスタンスを返す
}



//=============================================================================
//
//							プライベート関数
//
//=============================================================================



//状態によっての更新処理
void CHeart::UpdateState(void)
{
	switch (m_state)
	{
	case CHeart::state_spawn:

	{//スポーン状態

		m_nCntMove++;		//移動カウンターを更新する

		if (m_nCntMove == 30)
		{//30フレームが経ったら、上側のほうに動かす
			SetMove(D3DXVECTOR3(0.0f, -1.0f, 0.0f));
		}

		if (GetPos().y <= -150.0f)
		{//画面を出たら

			SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));			//速度の設定
			m_nCntMove = 0;									//移動カウンターを設定する
			m_state = state_sleep;							//寝る状態に設定する
		}
	}

		break;

	case CHeart::state_awake:

	{//起きる状態

		if (GetPos().y >= 150.0f)
		{//決まった位置に着いたら

			SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//速度の設定
			m_state = state_vulnerable;					//ダメージを受ける状態にする

			//ヒットボックスの生成
			if (m_pHitbox == nullptr)
			{
				m_pHitbox = CSquareHitbox::Create(GetPos(), D3DXVECTOR2(40.0f, 70.0f), CHitbox::Type_Enemy);
			}
		}
	}

		break;

	case CHeart::state_vulnerable:

	{//ダメージを受ける状態

		m_nShootDelay++;				//攻撃カウンターをインクリメントする

		if (m_nShootDelay % 90 == 30)
		{//90フレームごと弾を発生する

			CHeartBullet* pBullet = nullptr;

			for (int nCnt = 0; nCnt < 6; nCnt++)
			{//心形の弾を6つ生成する

				D3DXVECTOR3 move = D3DXVECTOR3(5.0f * (cosf(nCnt * (D3DX_PI / 6)) * cosf(m_fAngleShoot) + sinf(nCnt * (D3DX_PI / 6)) * sinf(m_fAngleShoot)),
					5.0f * (sinf((nCnt * (D3DX_PI / 6))) * cosf(m_fAngleShoot) - cosf(nCnt * (D3DX_PI / 6)) * sinf(m_fAngleShoot)), 0.0f);

				pBullet = CHeartBullet::Create(GetPos(), move, D3DXCOLOR(1.0f, 0.51f, 0.5f, 0.75f));
				pBullet->SetLife(90);
			}

			m_fAngleShoot -= D3DX_PI * 0.05f;			//攻撃の角度の更新

			if (m_fAngleShoot <= -D3DX_PI * 0.17f)
			{//決まった角度を超えたら、0に戻す
				m_fAngleShoot = 0.0f;
			}

			if (m_nShootDelay >= 550)
			{//550フレームが経ったら
				m_nShootDelay = 0;							//攻撃カウンターを0に戻す
				m_state = state_return;						//戻る状態にする
				SetMove(D3DXVECTOR3(0.0f, -1.0f, 0.0f));	//速度の設定
				m_pHitbox->Release();						//ヒットボックスの破棄
				m_pHitbox = nullptr;						//ヒットボックスへのポインタをnullにする
			}
		}
	}

		break;

	case CHeart::state_return:

	{//戻る状態

		if (GetPos().y <= -150.0f)
		{//決まった位置に着いたら

			SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));			//速度の設定
			m_nCntMove = 0;									//移動カウンターを0に戻す
			m_state = state_sleep;							//寝る状態に戻す
		}
	}

		break;

	case CHeart::state_death:

	{//死亡状態

		m_nCntMove++;			//カウンターをインクリメントする

		D3DXCOLOR col = GetColor();		//色の取得

		if (col.r >= 0.25f)
		{//まだ黒くない場合

			//色を暗くする
			col.r -= 0.0125f;
			col.g -= 0.0125f;
			col.b -= 0.0125f;

			SetColor(col);			//色の設定
		}
		else
		{//黒くなったら、終わった状態にする
			m_bEnd = true;
		}
	}


		break;

	case CHeart::state_sleep:


		break;

	default:
		break;
	}
}