//=============================================================================
//
// handCharger.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "handCharger.h"
#include "squareHitbox.h"
#include "handblade.h"
#include "player.h"
#include "wrath.h"
#include"application.h"
#include "sound.h"

//コンストラクタ
CHandCharger::CHandCharger()
{
	//メンバー変数をクリアする
	m_targetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_state = state_spawn;

	m_pHitbox = nullptr;
	m_pParent = nullptr;
}

//デストラクタ
CHandCharger::~CHandCharger()
{

}

//初期化処理
HRESULT CHandCharger::Init(void)
{
	//メンバー変数を初期化する
	if (FAILED(CEnemy::Init()))
	{//基本クラスの初期化処理
		return -1;
	}

	m_targetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_state = state_spawn;

	m_pHitbox = nullptr;
	m_pParent = nullptr;

	return S_OK;
}

//終了処理
void CHandCharger::Uninit(void)
{
	//ヒットボックスの破棄処理
	if (m_pHitbox != nullptr)
	{//nullチェック
		m_pHitbox->Release();				//メモリを解放する
		m_pHitbox = nullptr;				//nullにする
	}

	//親へのポインタがnullではなかったら、nullに戻す
	if (m_pParent != nullptr)
	{
		m_pParent = nullptr;
	}

	//基本クラスの終了処理
	CEnemy::Uninit();
}

//更新処理
void CHandCharger::Update(void)
{
	//基本クラスの更新処理
	CObject_2D::Update();

	//ヒットボックスの更新
	if (m_pHitbox != nullptr)
	{//nullチェック

		m_pHitbox->SetPos(GetPos());			//位置の設定

		if (m_pHitbox->GetHitState())
		{//当たった状態だったら

			m_pHitbox->SetHitState(false);		//当っていない状態に戻す

			int nDamage = CPlayer::GetPlayer()->GetAttack();		//プレイヤーの攻撃力を取得する

			if (m_pParent != nullptr)
			{//親へのポインタがnullではなかったら

				m_pParent->Damage(nDamage);			//親にダメージを与える
			}
		}
	}

	//親が死んだかどうかを確認する
	if (m_pParent != nullptr)
	{//nullチェック
		if (m_pParent->GetDeath() && m_state != state_death)
		{//死んだ状態だったら

			m_state = state_death;								//状態の更新
			SetMove(D3DXVECTOR3(5.0f, -5.0f, 0.0f));			//移動量の設定
			SetAcceleration(D3DXVECTOR3(0.0f, 0.1f, 0.0f));		//加速の設定
			SetRotation(D3DX_PI * 0.01f);						//回転させる
			m_nPhase = 0;										//カウンターを0に戻す
		}
	}

	UpdateState();				//状態によっての更新処理
}

//親へのポインタの設定処理
void CHandCharger::SetParent(CWrath* pParent)
{
	m_pParent = pParent;
}



//=============================================================================
//
//								静的関数
//
//=============================================================================



//生成処理
CHandCharger* CHandCharger::Create(D3DXVECTOR3 pos)
{
	CHandCharger* pEnemy = new CHandCharger;			//インスタンスを生成する
		
	if (FAILED(pEnemy->Init()))
	{//初期化処理
		return nullptr;
	}

	pEnemy->SetPos(pos);									//位置の設定
	pEnemy->SetMove(D3DXVECTOR3(0.0f, 2.0f, 0.0f));			//速度の設定
	pEnemy->SetStartingRot(D3DX_PI * 0.5f);					//向きの初期値の設定
	pEnemy->SetSize(D3DXVECTOR2(120.0f, 80.0f));			//サイズの設定
	pEnemy->SetTexture(CObject::TextureHand);				//テクスチャの設定
	pEnemy->SetTextureParameter(1, 4, 2, INT_MAX);			//テクスチャパラメータの設定
	pEnemy->SetAnimPattern(5);								//アニメションパターンの設定
	pEnemy->SetPriority(3);									//プライオリティの設定

	//ヒットボックスの生成
	pEnemy->m_pHitbox = CSquareHitbox::Create(pos, D3DXVECTOR2(75.0f, 20.0f), CHitbox::Type_Enemy);

	return pEnemy;				//生成したインスタンスを返す
}


//=============================================================================
//
//							プライベート関数
//
//=============================================================================

//状態によっての更新処理
void CHandCharger::UpdateState(void)
{
	D3DXVECTOR3 pos = GetPos();			//位置の取得

	switch (m_state)
	{
	case CHandCharger::state_spawn:

	{//スポーン状態

		if (m_nPhase == 0)
		{
			if (pos.y >= 100.0f)
			{//見えるようになったら、止まる
				SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				m_nPhase++;
			}
		}
		else if (m_nPhase == 1)
		{
			m_nShootDelay++;			//攻撃カウンターを更新する

			if (m_nShootDelay >= 30)
			{//30フレームが経ったら
				m_nShootDelay = 0;														//攻撃カウンターを0に戻す
				m_nPhase = 0;															//カウンターを0に戻す
				m_state = state_attack;													//状態を更新する
				SetMove(D3DXVECTOR3(0.0f, 20.0f, 0.0f));								//移動量の設定
				m_targetPos = CPlayer::GetPlayer()->GetPos();							//プレイヤーの位置の取得
				m_targetPos.x = pos.x;													//目的の位置の設定
				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_HAND_WOOSH);		//サウンドを再生する
			}
		}
	}

	break;

	case CHandCharger::state_attack:

	{//攻撃状態

		if (pos.y >= m_targetPos.y)
		{//目的の位置を超えたら

			SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));								//速度の設定
			m_state = state_return;												//状態の更新
			SetAnimPattern(6);													//アニメションパターンの設定
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_HAND_HIT);	//サウンドを再生する
		}
	}

	break;

	case CHandCharger::state_return:

	{//戻る状態

		m_nCntMove++;			//移動カウンターの更新

		if (m_nCntMove == 60)
		{//1秒が経ったら

			SetMove(D3DXVECTOR3(0.0f, -7.0f, 0.0f));			//速度の設定
			m_state = state_despawn;							//状態の更新
			SetAnimPattern(5);									//アニメションパターンの設定
		}
	}

	break;

	case CHandCharger::state_despawn:

	{//ディスポーン状態

		if (pos.y <= -100.0f)
		{//見えなくなったら
			Release();			//破棄する
			return;
		}
	}

	break;

	case CHandCharger::state_death:

	{//死亡状態

		m_nPhase++;			//カウンターの更新

		if (m_nPhase % 15 == 0)
		{//15フレームごと

			D3DXCOLOR col = GetColor();			//色の取得

			if (col.g < 0.5f)
			{//赤かったら、普通の色に戻す
				SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else
			{//普通の色だったら、赤くする
				SetColor(D3DXCOLOR(1.0f, 0.3f, 0.3f, 1.0f));
			}
		}

	}

		break;

	default:
		break;
	}
}