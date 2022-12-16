//=============================================================================
//
// Thanatos.h
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "Thanatos.h"
#include "squareHitbox.h"
#include "candle.h"
#include "player.h"
#include "scythe.h"
#include "enemyLife.h"
#include "application.h"
#include "sound.h"

//コンストラクタ
CThanatos::CThanatos()
{
	//メンバー変数をクリアする
	m_nTargetLife = 0;
	m_nLitCandle = 0;
	m_nCntState = 0;
	m_state = state_Spawn;
	m_bEnd = false;

	for (int nCnt = 0; nCnt < Max_Candle; nCnt++)
	{
		m_pCandle[nCnt] = nullptr;
	}

	m_pLife = nullptr;

	m_pHitbox = nullptr;
}

//デストラクタ
CThanatos::~CThanatos()
{

}

//初期化処理
HRESULT CThanatos::Init(void)
{
	//メンバー変数を初期化する
	if (FAILED(CEnemy::Init()))
	{//基本クラスの初期化処理
		return -1;
	}

	m_nTargetLife = 4000;
	m_nLitCandle = 0;
	m_nCntState = 0;
	m_state = state_Spawn;
	m_bEnd = false;

	for (int nCnt = 0; nCnt < Max_Candle; nCnt++)
	{
		m_pCandle[nCnt] = nullptr;
	}

	m_pLife = nullptr;

	m_pHitbox = nullptr;

	return S_OK;
}

//終了処理
void CThanatos::Uninit(void)
{
	//ロウソクの破棄処理
	for (int nCnt = 0; nCnt < Max_Candle; nCnt++)
	{
		if (m_pCandle[nCnt] != nullptr)
		{//nullチェック
			m_pCandle[nCnt]->Release();			//メモリを解放する
			m_pCandle[nCnt] = nullptr;			//nullにする
		}
	}

	//ヒットボックスの破棄処理
	if (m_pHitbox != nullptr)
	{//nullチェック
		m_pHitbox->Release();					//メモリを解放する			
		m_pHitbox = nullptr;					//nullにする
	}

	//体力UIの破棄処理
	if (m_pLife != nullptr)
	{//nullチェック
		m_pLife->Release();						//メモリを解放する
		m_pLife = nullptr;						//nullにする
	}

	//基本クラスの終了処理
	CEnemy::Uninit();
}

//更新処理
void CThanatos::Update(void)
{
	switch (m_state)
	{//状態によって更新する
	case CThanatos::state_Spawn:

	{//スポーン状態
		D3DXCOLOR col = GetColor();		//色の取得	

		col.a += 0.005f;				//α値の更新

		if (col.a >= 1.0f)
		{//α値が1以上になったら
			col.a = 1.0f;				//1.0fに戻す
			m_state = state_Hide;		//状態を更新する
		}

		SetColor(col);					//色の設定
	}

		break;

	case CThanatos::state_Normal:
		//普通状態
		break;

	case CThanatos::state_Hide:

	{//隠す状態
		D3DXCOLOR col = GetColor();		//色の取得

		col.a -= 0.005f;				//α値の更新

		if (col.a <= 0.0f)
		{//α値が0以下になったら
			col.a = 0.0f;				//0.0fに戻す
			m_state = state_ShowEyes;	//状態を更新する
			SetAnimPattern(1);			//アニメションパターンの設定
		}

		SetColor(col);					//色の設定
	}

		break;

	case CThanatos::state_ShowEyes:

	{//目が見える状態
		D3DXCOLOR col = GetColor();		//色の取得

		col.a += 0.005f;				//α値を更新する

		if (col.a >= 1.0f)
		{//α値が1.0f以上になったら
			col.a = 1.0f;				//1.0fに戻す
			m_state = state_Hidden;		//状態を更新する
			m_nShootDelay = 30;			//カウンターの設定
		}

		SetColor(col);					//色の設定
	}

	break;

	case CThanatos::state_Hidden:

	{//隠した状態
		m_nShootDelay--;				//カウンターの更新

		//目的の座標を計算する
		D3DXVECTOR3 target = CPlayer::GetPlayer()->GetPos();		
		target -= GetPos();
		D3DXVec3Normalize(&target, &target);
		target.x *= 0.25f;
		target.y *= 0.25f;

		SetMove(target);				//速度の設定


		if (m_nShootDelay <= 0)
		{//カウンターが0以下になったら
			m_nShootDelay = 90;				//カウンターの設定

			//弾の移動量の計算
			D3DXVec3Normalize(&target, &target);		
			target.x *= 4.0f;
			target.y *= 4.0f;

			//弾の生成
			CScythe* pBullet = CScythe::Create(GetPos(), target);

			if (GetLife() <= 4000)
			{//体力が4000以下だったら	
				int nMax = 1;			//一回だけ繰り返す

				if (GetLife() <= 2000)
				{//体力が2000以下だったら
					nMax = 2;			//二回繰り返す
				}

				for (int nCnt = 0; nCnt < nMax; nCnt++)
				{
					//新しい弾の速度の計算
					D3DXVec3Normalize(&target, &target);

					D3DXVECTOR3 speed = target;
					speed.x *= (float)random(2000, 5000) * 0.001f;
					speed.y = (float)random(2000, 4000) * -0.001f;

					//弾の生成
					pBullet = CScythe::Create(GetPos(), speed);

					pBullet->SetAcceleration(D3DXVECTOR3(0.0f, 0.05f, 0.0f));		//加速の設定
					pBullet->AddAngularSpeed(D3DX_PI * 0.05f);						//回転させる

					//新しい弾の移動量の計算
					if (target.x >= target.y)
					{
						target.x += target.x;
					}
					else
					{
						target.y += target.y;
					}

					D3DXVec3Normalize(&target, &target);
					target.x *= 4.0f;
					target.y *= 4.0f;

					//弾の生成
					pBullet = CScythe::Create(GetPos(), target);
				}
			}

			//サウンドを再生する
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_SCYTHE);
		}
		
		if (m_nLitCandle >= 4)
		{//全部のロウソクがついたら

			m_state = state_Vulnerable;			//状態の更新
			SetAnimPattern(0);					//アニメションパターンの設定

			//ヒットボックスの生成
			if (m_pHitbox == nullptr)
			{//nullだったら
				//ヒットボックスのサイズを計算する
				D3DXVECTOR2 size = GetSize();
				size.x *= 0.7f;
				size.y *= 0.9f;

				//ヒットボックスを生成する
				m_pHitbox = CSquareHitbox::Create(GetPos(), size, CHitbox::Type_Enemy);
			}
		}
	}

	break;

	case CThanatos::state_Vulnerable:

	{//ダメージを受ける状態

		m_nShootDelay -= 2;				//普通より2倍早く弾をうつ

		SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));			//移動量

		if (m_nShootDelay <= 0)
		{//カウンターが0以下になったら
			m_nShootDelay = 90;				//カウンタの設定

			//目的の位置を計算する
			D3DXVECTOR3 target = CPlayer::GetPlayer()->GetPos();
			target -= GetPos();
			D3DXVec3Normalize(&target, &target);
			target.x *= 4.0f;
			target.y *= 4.0f;

			//弾の生成
			CScythe* pBullet = CScythe::Create(GetPos(), target);

			if (GetLife() <= 4000)
			{//体力が4000以下だったら
				int nMax = 1;

				if (GetLife() <= 2000)
				{//体力が2000以下だったら
					nMax = 2;
				}

				for (int nCnt = 0; nCnt < nMax; nCnt++)
				{
					//新しい弾の移動量の計算
					D3DXVec3Normalize(&target, &target);

					D3DXVECTOR3 speed = target;
					speed.x *= (float)random(2000, 5000) * 0.001f;
					speed.y = (float)random(2000, 4000) * -0.001f;

					//弾の生成
					pBullet = CScythe::Create(GetPos(), speed);

					pBullet->SetAcceleration(D3DXVECTOR3(0.0f, 0.05f, 0.0f));			//加速の設定
					pBullet->AddAngularSpeed(D3DX_PI * 0.05f);							//回転させる

					//新しい弾の速度の計算
					if (target.x >= target.y)
					{
						target.x += target.x;
					}
					else
					{
						target.y += target.y;
					}

					D3DXVec3Normalize(&target, &target);
					target.x *= 4.0f;
					target.y *= 4.0f;

					//弾の生成
					pBullet = CScythe::Create(GetPos(), target);
				}
			}

			//サウンドを再生する
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_SCYTHE);
		}

		if (m_pHitbox->GetHitState())
		{//当たったら
			m_pHitbox->SetHitState(false);						//当っていない状態にする
			int nLife = GetLife();								//体力の取得
			int nDamage = CPlayer::GetPlayer()->GetAttack();	//受けたダメージの取得

			nLife -= nDamage;			//体力の更新

			//UIの更新
			if (m_pLife != nullptr)
			{//nullチェック
				m_pLife->SubtractLife(nDamage);				//体力UIの更新
			}

			if (nLife <= 0)
			{//体力が0以下になったら
				m_state = state_Death;			//死亡状態にする
				m_pHitbox->Release();			//ヒットボックスを破棄する
				m_pHitbox = nullptr;			//nullにする
			}
			else if(nLife <= m_nTargetLife)
			{//目的の体力以下になったら
				nLife = m_nTargetLife;		//体力の設定
				m_nTargetLife -= 2000;		//次の目的の体力を計算する
				SetLife(nLife);				//体力の設定

				for (int nCnt = 0; nCnt < Max_Candle; nCnt++)
				{//ロウソクを消す
					if (m_pCandle[nCnt])
					{//nullチェック
						m_pCandle[nCnt]->Unlit();
					}
				}

				m_pHitbox->Release();			//ヒットボックスを破棄する
				m_pHitbox = nullptr;			//nullにする
				m_nLitCandle = 0;				//つけたロウソクの数を0に戻す
				m_state = state_Hide;			//状態の更新
			}
			else
			{
				SetLife(nLife);					//体力の設定
			}
		}
	}

	break;

	case CThanatos::state_Death:

	{//死亡状態
		D3DXCOLOR col = GetColor();			//色の取得

		col.a -= 0.005f;					//α値の更新

		if (col.a <= 0.0f)
		{//α値が0以下になったら
			col.a = 0.0f;					//α値を0以下に戻す

			m_bEnd = true;					//終わった状態にする
		}

		SetColor(col);						//色の設定

		for (int nCnt = 0; nCnt < Max_Candle; nCnt++)
		{//ロウソクの破棄処理
			m_pCandle[nCnt]->Despawn();
		}
	}

	break;
	
	default:
		break;
	}

	
	if (m_state != state_Spawn && m_state != state_Death)
	{//スポーンと死亡状態以外

		//プレイヤーの位置によってテクスチャを反転します
		D3DXVECTOR3 PlayerPos = CPlayer::GetPlayer()->GetPos();
		D3DXVECTOR3 pos = GetPos();

		if (PlayerPos.x < pos.x && GetFlipX() || PlayerPos.x > pos.x && !GetFlipX())
		{
			FlipX();
		}

		//上下の移動をつける
		pos.y += 0.20f * sinf(m_fAngleMove);
		m_fAngleMove += D3DX_PI * 0.015f;

		SetPos(pos);				//位置の設定
	}
	
	//ヒットボックスの更新処理
	if (m_pHitbox != nullptr)
	{//nullチェック
		m_pHitbox->SetPos(GetPos());		//位置の設定
	}

	//基本クラスの更新処理
	CObject_2D::Update();
}

//描画処理
void CThanatos::Draw(void)
{
	CObject_2D::Draw();
}

//終わったかどうかの取得処理
const bool CThanatos::GetEnd(void)
{
	return m_bEnd;
}

//背景へのポインタの設定処理
void CThanatos::SetBgPointer(CBg* pPointer)
{
	m_pBg = pPointer;

	for (int nCnt = 0; nCnt < Max_Candle; nCnt++)
	{
		m_pCandle[nCnt]->SetBgPointer(m_pBg);
	}
}

//つけたロウソクの追加処理
void CThanatos::AddLitCandle(void)
{
	m_nLitCandle++;
}





//生成処理
CThanatos* CThanatos::Create(void)
{
	CThanatos* pEnemy = new CThanatos;			//インスタンスを生成する

	if (FAILED(pEnemy->Init()))
	{//初期化処理
		return nullptr;
	}

	pEnemy->SetPos(D3DXVECTOR3(900.0f, 250.0f, 0.0f));				//位置の設定
	pEnemy->SetStartingRot(D3DX_PI * 0.5f);							//向きの初期値の設定
	pEnemy->SetTexture(CObject::TextureThanatos);					//テクスチャの設定
	pEnemy->SetTextureParameter(1, 2, 1, INT_MAX);					//テクスチャパラメータの設定
	pEnemy->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));			//色の設定
	pEnemy->SetSize(D3DXVECTOR2(100.0f, 182.4f));					//サイズの設定
	pEnemy->SetLife(6000);											//体力の設定

	//ロウソクの生成処理
	pEnemy->m_pCandle[0] = CCandle::Create(D3DXVECTOR3(160.0f, 100.0f, 0.0f));
	pEnemy->m_pCandle[1] = CCandle::Create(D3DXVECTOR3(160.0f, (float)SCREEN_HEIGHT - 100.0f, 0.0f));
	pEnemy->m_pCandle[2] = CCandle::Create(D3DXVECTOR3((float)SCREEN_WIDTH - 152.5f, 100.0f, 0.0f));
	pEnemy->m_pCandle[3] = CCandle::Create(D3DXVECTOR3((float)SCREEN_WIDTH - 152.5f, (float)SCREEN_HEIGHT - 100.0f, 0.0f));

	for (int nCnt = 0; nCnt < CThanatos::Max_Candle; nCnt++)
	{//ロウソクの親子関係を作る
		pEnemy->m_pCandle[nCnt]->SetParent(pEnemy);
	}

	//体力UIの生成
	pEnemy->m_pLife = CEnemyLife::Create(D3DXVECTOR3(800.0f, 40.0f, 0.0f), D3DXCOLOR(8.0f, 0.8f, 0.8f, 0.5f), 6000, "thanatos");
	
	return pEnemy;					//生成したインスタンスを返す
}