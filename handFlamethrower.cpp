//=============================================================================
//
// handFlamethrower.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "handFlamethrower.h"
#include "circleHitbox.h"
#include "handFireball.h"
#include "player.h"
#include "wrath.h"
#include "application.h"
#include "sound.h"

//コンストラクタ
CHandFlamethrower::CHandFlamethrower()
{
	//メンバー変数をクリアする
	m_state = state_spawn;

	m_pHitbox = nullptr;
	m_pParent = nullptr;
}

//デストラクタ
CHandFlamethrower::~CHandFlamethrower()
{

}

//初期化処理
HRESULT CHandFlamethrower::Init(void)
{
	//メンバー変数を初期化する
	if(FAILED(CEnemy::Init()))
	{
		return -1;
	}

	m_state = state_spawn;

	m_pHitbox = nullptr;
	m_pParent = nullptr;

	return S_OK;
}

//終了処理
void CHandFlamethrower::Uninit(void)
{
	//ヒットボックスの破棄処理
	if (m_pHitbox != nullptr)
	{//nullチェック
		m_pHitbox->Release();			//メモリを解放する
		m_pHitbox = nullptr;			//nullにする
	}

	//親へのポインタがnullではなかったら、nullにする
	if (m_pParent != nullptr)
	{
		m_pParent = nullptr;
	}

	//基本クラスの終了処理
	CEnemy::Uninit();
}

//更新処理
void CHandFlamethrower::Update(void)
{
	//基本クラスの更新処理
	CObject_2D::Update();

	//ヒットボックスの更新処理
	if (m_pHitbox != nullptr)
	{//nullチェック

		m_pHitbox->SetPos(GetPos());			//位置の設定

		if (m_pHitbox->GetHitState())
		{//当たった状態だったら

			m_pHitbox->SetHitState(false);		//当っていない状態に戻す

			int nDamage = CPlayer::GetPlayer()->GetAttack();		//プレイヤーの攻撃力を取得する

			if (m_pParent != nullptr)
			{//親へのポインタがnullではなかったら、

				m_pParent->Damage(nDamage);				//親にダメージを与える
			}
		}
	}

	//死亡状態の確認
	if (m_pParent != nullptr)
	{//nullチェック
		if (m_pParent->GetDeath() && m_state != state_death)
		{//親が死亡状態だったら

			m_state = state_death;						//死亡状態にする
			SetMove(D3DXVECTOR3(0.0f, 2.0f, 0.0f));		//移動量の設定
			m_nPhase = 0;								//カウンターを0に戻す
		}
	}

	updateState();				//状態によっての更新処理
}

//親へのポインタの設定処理
void CHandFlamethrower::SetParent(CWrath* pParent)
{
	m_pParent = pParent;
}



//=============================================================================
//
//								静的関数
//
//=============================================================================



//生成処理
CHandFlamethrower* CHandFlamethrower::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CHandFlamethrower* pEnemy = new CHandFlamethrower;			//インスタンスを生成する

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
	pEnemy->SetAnimPattern(1);								//アニメションパターンの設定
	pEnemy->SetPriority(2);									//プライオリティの設定

	//位置によってテクスチャを反転する
	if (pos.x <= 0.0f)
	{
		pEnemy->FlipX();
	}

	//ヒットボックスの生成
	pEnemy->m_pHitbox = CCircleHitbox::Create(pos, 75.0f, CHitbox::Type_Enemy);

	return pEnemy;					//生成したインスタンスを返す
}





void CHandFlamethrower::updateState(void)
{
	switch (m_state)
	{
	case CHandFlamethrower::state_spawn:

	{
		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 move = GetMove();

		if (move.x >= 0.0f && pos.x >= 100.0f || move.x < 0.0f && pos.x <= (float)SCREEN_WIDTH - 100.0f)
		{
			SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			m_state = state_shoot;
		}
	}

		break;

	case CHandFlamethrower::state_shoot:

	{
		m_nShootDelay++;

		if (m_nShootDelay % 20 == 1)
		{
			D3DXVECTOR3 pos = GetPos();

			if (pos.x < (float)SCREEN_WIDTH * 0.5f)
			{
				CHandFireball::Create(D3DXVECTOR3(pos.x + 100.0f, pos.y - 20.0f, 0.0f), D3DXVECTOR3(4.0f, 2.0f, 0.0f));
			}
			else
			{
				CHandFireball::Create(D3DXVECTOR3(pos.x - 100.0f, pos.y - 20.0f, 0.0f), D3DXVECTOR3(-4.0f, 2.0f, 0.0f));
			}

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_FIRE);
		}

		if (m_nShootDelay >= 300)
		{
			m_nShootDelay = 0;
			m_state = state_return;
		}
	}

		break;

	case CHandFlamethrower::state_return:

	{
		D3DXVECTOR3 pos = GetPos();

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

	case CHandFlamethrower::state_despawn:

	{
		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 move = GetMove();

		if (move.x >= 0.0f && pos.x >= 100.0f || move.x < 0.0f && pos.x <= (float)SCREEN_WIDTH - 100.0f)
		{
			Release();
			return;
		}
	}

	break;

	case CHandFlamethrower::state_death:

	{
		m_nPhase++;

		if (m_nPhase % 15 == 0)
		{
			D3DXCOLOR col = GetColor();

			if (col.g < 0.5f)
			{
				SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else
			{
				SetColor(D3DXCOLOR(1.0f, 0.3f, 0.3f, 1.0f));
			}
		}
		
	}

	break;

	default:
		break;
	}
}