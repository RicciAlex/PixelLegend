//=============================================================================
//
// handGun.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "handGun.h"
#include "circleHitbox.h"
#include "handblade.h"
#include "player.h"
#include "wrath.h"
#include "application.h"
#include "sound.h"

//コンストラクタ
CHandGun::CHandGun()
{
	//メンバー変数をクリアする
	m_state = state_spawn;

	m_pHitbox = nullptr;
	m_pParent = nullptr;
}

//デストラクタ
CHandGun::~CHandGun()
{

}

//初期化処理
HRESULT CHandGun::Init(void)
{
	//メンバー変数を初期化する
	if (FAILED(CEnemy::Init()))
	{//基本クラスの初期化処理
		return -1;
	}

	m_state = state_spawn;

	m_pHitbox = nullptr;
	m_pParent = nullptr;

	return S_OK;
}

//終了処理
void CHandGun::Uninit(void)
{
	//ヒットボックスの破棄処理
	if (m_pHitbox != nullptr)
	{//nullチェック
		m_pHitbox->Release();			//メモリを解放する
		m_pHitbox = nullptr;			//nullにする
	}

	//親へのポインタはnullではなかったら、nullにする
	if (m_pParent != nullptr)
	{
		m_pParent = nullptr;
	}

	//基本クラスの終了処理
	CEnemy::Uninit();
}

//更新処理
void CHandGun::Update(void)
{
	//基本クラスの更新処理
	CObject_2D::Update();

	//ヒットボックスの更新処理
	if (m_pHitbox != nullptr)
	{//nullチェック

		m_pHitbox->SetPos(GetPos());			//位置の設定

		if (m_pHitbox->GetHitState())
		{//当たった状態だったら

			m_pHitbox->SetHitState(false);		//普通状態に戻す

			int nDamage = CPlayer::GetPlayer()->GetAttack();			//プレイヤーの攻撃力を取得する

			//親にダメージを与える
			if (m_pParent != nullptr)
			{//nullチェック
				m_pParent->Damage(nDamage);				//ダメージの設定
			}
		}
	}

	//死亡状態の確認
	if (m_pParent != nullptr)
	{//nullチェック
		if (m_pParent->GetDeath() && m_state != state_death)
		{//死んだら、死亡アニメーションを再生する

			m_state = state_death;							//状態の更新
			m_nPhase = 0;									//カウンターを0に戻す
			SetMove(D3DXVECTOR3(0.0f, 2.0f, 0.0f));			//移動量の設定
		}
	}

	UpdateState();		//状態によっての更新処理
}

//親へのポインタの生成処理
void CHandGun::SetParent(CWrath* pParent)
{
	m_pParent = pParent;
}



//=============================================================================
//
//								静的関数
//
//=============================================================================



//生成処理
CHandGun* CHandGun::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CHandGun* pEnemy = new CHandGun;			//インスタンスを生成する

	if (FAILED(pEnemy->Init()))
	{//初期化処理
		return nullptr;
	}

	pEnemy->SetPos(pos);									//位置の設定
	pEnemy->SetMove(move);									//速度の設定
	pEnemy->SetStartingRot(D3DX_PI * 0.5f);					//向きの初期値の設定
	pEnemy->SetSize(D3DXVECTOR2(120.0f, 80.0f));			//サイズの設定
	pEnemy->SetTexture(CObject::TextureHand);				//テクスチャの設定
	pEnemy->SetTextureParameter(1, 4, 2, INT_MAX);			//テクスチャパラメータの設定
	pEnemy->SetAnimPattern(2);								//アニメションパターンの設定
	pEnemy->SetPriority(3);									//プライオリティの設定

	//X座標によってテクスチャを反転する
	if (pos.x <= 0.0f)
	{
		pEnemy->FlipX();
	}

	//ヒットボックスの生成
	pEnemy->m_pHitbox = CCircleHitbox::Create(pos, 60.0f, CHitbox::Type_Enemy);

	return pEnemy;					//生成したインスタンスを返す
}


//=============================================================================
//
//							プライベート関数
//
//=============================================================================

//状態によっての更新処理
void CHandGun::UpdateState(void)
{
	switch (m_state)
	{
	case CHandGun::state_spawn:

	{//スポーン状態

		D3DXVECTOR3 pos = GetPos();			//位置の取得
		D3DXVECTOR3 move = GetMove();		//速度の取得

		if (move.x >= 0.0f && pos.x >= 100.0f || move.x < 0.0f && pos.x <= (float)SCREEN_WIDTH - 100.0f)
		{//決まった位置を超えたら

			SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));				//速度を0にする
			m_state = state_shoot;								//状態の更新
		}
	}

	break;

	case CHandGun::state_shoot:

	{//ショット状態

		m_nShootDelay++;				//攻撃カウンターを更新する

		if (m_nShootDelay % 20 == 1)
		{//20フレームごと弾をうつ

			D3DXVECTOR3 pos = GetPos();			//位置の取得

			//弾の速度の計算
			D3DXVECTOR3 move, newMove;
			float fAdd = 100.0f;
			move = CPlayer::GetPlayer()->GetPos() - pos;
			D3DXVec3Normalize(&move, &move);
			D3DXVECTOR3 unit = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
			float fAngle = acosf(D3DXVec3Dot(&move, &unit));

			if (CPlayer::GetPlayer()->GetPos().y < pos.y)
			{
				fAngle *= -1.0f;
			}

			if (pos.x > (float)SCREEN_WIDTH * 0.5f)
			{
				fAdd *= -1.0f;
			}

			//弾５つ生成する
			newMove = D3DXVECTOR3(cosf(fAngle) * cosf(D3DX_PI / 18.0f) - sinf(fAngle) * sinf(D3DX_PI / 18.0f),
				sinf(fAngle) * cosf(D3DX_PI / 18.0f) + cosf(fAngle) * sinf(D3DX_PI / 18.0f), 0.0f);

			CHandBlade::Create(D3DXVECTOR3(pos.x + fAdd, pos.y - 20.0f, 0.0f), D3DXVECTOR3(5.0f * newMove.x, 5.0f * newMove.y, 0.0f));

			newMove = D3DXVECTOR3(cosf(fAngle) * cosf(-D3DX_PI / 18.0f) - sinf(fAngle) * sinf(-D3DX_PI / 18.0f),
				sinf(fAngle) * cosf(-D3DX_PI / 18.0f) + cosf(fAngle) * sinf(-D3DX_PI / 18.0f), 0.0f);

			CHandBlade::Create(D3DXVECTOR3(pos.x + fAdd, pos.y - 20.0f, 0.0f), D3DXVECTOR3(5.0f * newMove.x, 5.0f * newMove.y, 0.0f));

			newMove = D3DXVECTOR3(cosf(fAngle) * cosf(D3DX_PI / 12.0f) - sinf(fAngle) * sinf(D3DX_PI / 12.0f),
				sinf(fAngle) * cosf(D3DX_PI / 12.0f) + cosf(fAngle) * sinf(D3DX_PI / 12.0f), 0.0f);

			CHandBlade::Create(D3DXVECTOR3(pos.x + fAdd, pos.y - 20.0f, 0.0f), D3DXVECTOR3(5.0f * newMove.x, 5.0f * newMove.y, 0.0f));

			newMove = D3DXVECTOR3(cosf(fAngle) * cosf(-D3DX_PI / 12.0f) - sinf(fAngle) * sinf(-D3DX_PI / 12.0f),
				sinf(fAngle) * cosf(-D3DX_PI / 12.0f) + cosf(fAngle) * sinf(-D3DX_PI / 12.0f), 0.0f);

			CHandBlade::Create(D3DXVECTOR3(pos.x + fAdd, pos.y - 20.0f, 0.0f), D3DXVECTOR3(5.0f * newMove.x, 5.0f * newMove.y, 0.0f));

			CHandBlade::Create(D3DXVECTOR3(pos.x + fAdd, pos.y - 20.0f, 0.0f), D3DXVECTOR3(5.0f * move.x, 5.0f * move.y, 0.0f));

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_SHOT);			//攻撃サウンドを再生する
		}

		if (m_nShootDelay >= 180)
		{//3秒が経ったら、戻る状態にする

			m_nShootDelay = 0;				//攻撃カウンターを0に戻す
			m_state = state_return;			//状態の更新
		}
	}

	break;

	case CHandGun::state_return:

	{//戻る状態

		D3DXVECTOR3 pos = GetPos();				//位置の取得

		//現在の位置によって移動量の設定
		if (pos.x < (float)SCREEN_WIDTH * 0.5f)
		{
			SetMove(D3DXVECTOR3(-2.0f, 0.0f, 0.0f));
		}
		else
		{
			SetMove(D3DXVECTOR3(2.0f, 0.0f, 0.0f));
		}
	}

	break;

	case CHandGun::state_despawn:

	{//ディスポーン状態

		D3DXVECTOR3 pos = GetPos();				//位置の取得
		D3DXVECTOR3 move = GetMove();			//速度の取得

		if (move.x >= 0.0f && pos.x >= 100.0f || move.x < 0.0f && pos.x <= (float)SCREEN_WIDTH - 100.0f)
		{//決まった位置を超えたら、破棄する
			Release();				//破棄処理
			return;
		}
	}

	break;

	case CHandGun::state_death:

	{//死亡状態

		m_nPhase++;					//カウンターを更新する

		if (m_nPhase % 15 == 0)
		{//15フレームごと色を変える

			D3DXCOLOR col = GetColor();				//色の取得

			if (col.g < 0.5f)
			{//赤いだったら、普通の色に戻す
				SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else
			{//普通の色だったら、赤くします
				SetColor(D3DXCOLOR(1.0f, 0.3f, 0.3f, 1.0f));
			}
		}

	}

	break;

	default:
		break;
	}
}