//=============================================================================
//
// envy.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "envy.h"
#include "squareHitbox.h"
#include "missile.h"
#include "spikeBomb.h"
#include "player.h"
#include "envyPieces.h"
#include "explosion.h"
#include "enemyLife.h"
#include "application.h"
#include "sound.h"

//=============================================================================
//							静的変数の初期化
//=============================================================================
const D3DXVECTOR2 CEnvy::m_EnvySize = D3DXVECTOR2(140.0f, 118.0f);			//サイズ
const D3DXVECTOR2 CEnvy::m_HitboxEnvySize = D3DXVECTOR2(110.0f, 120.0f);	//ヒットボックスサイズ
const D3DXVECTOR2 CEnvy::m_HitboxHatSize = D3DXVECTOR2(95.0f, 115.0f);		//帽子のヒットボックスサイズ

//コンストラクタ
CEnvy::CEnvy()
{
	//メンバー変数をクリアする
	for (int nCnt = 0; nCnt < nGearNum; nCnt++)
	{
		m_pGear[nCnt] = nullptr;
		m_gearRelativePos[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	for (int nCnt = 0; nCnt < nPipeNum; nCnt++)
	{
		m_pPipe[nCnt] = nullptr;
		m_pipeRelativePos[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	m_hatRelativePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_cannonRelativePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_nCntState = 0;
	m_state = state_spawn;
	m_bEnd = false;

	m_pCannon = nullptr;
	m_pHat = nullptr;
	m_pHitbox = nullptr;
	m_pHatHitbox = nullptr;
	m_pLife = nullptr;
}

CEnvy::~CEnvy()
{

}

//初期化処理
HRESULT CEnvy::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CEnemy::Init()))
	{
		return -1;
	}

	//メンバー変数を初期化する
	for (int nCnt = 0; nCnt < nGearNum; nCnt++)
	{
		m_pGear[nCnt] = nullptr;
		m_gearRelativePos[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	
	for (int nCnt = 0; nCnt < nPipeNum; nCnt++)
	{
		m_pPipe[nCnt] = nullptr;
		m_pipeRelativePos[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	m_hatRelativePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_cannonRelativePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_nCntState = 0;
	m_state = state_spawn;
	m_bEnd = false;

	m_pCannon = nullptr;
	m_pHat = nullptr;
	m_pHitbox = nullptr;
	m_pHatHitbox = nullptr;
	m_pLife = nullptr;

	return S_OK;
}

//終了処理
void CEnvy::Uninit(void)
{
	//歯車の破棄処理
	for (int nCnt = 0; nCnt < nGearNum; nCnt++)
	{
		if (m_pGear[nCnt] != nullptr)
		{//nullチェック
			m_pGear[nCnt]->Release();			//メモリを解放する
			m_pGear[nCnt] = nullptr;			//ポインタをnullにする
		}
	}

	//帽子の破棄処理
	if (m_pHat != nullptr)
	{//nullチェック
		m_pHat->Release();						//メモリを解放する
		m_pHat = nullptr;						//ポインタをnullにする
	}

	//大砲の破棄処理
	if (m_pCannon != nullptr)
	{//nullチェック 
		m_pCannon->Release();					//メモリを解放する
		m_pCannon = nullptr;					//ポインタをnullにする
	}

	//管の破棄処理
	for (int nCnt = 0; nCnt < nPipeNum; nCnt++)
	{
		if (m_pPipe[nCnt] != nullptr)
		{//nullチェック
			m_pPipe[nCnt]->Release();			//メモリを解放する
			m_pPipe[nCnt] = nullptr;			//ポインタをnullにする
		}
	}
	
	//ヒットボックスの破棄処理
	if (m_pHitbox != nullptr)
	{//nullチェック
		m_pHitbox->Release();					//メモリを解放する
		m_pHitbox = nullptr;					//ポインタをnullにする
	}

	//帽子の破棄処理
	if (m_pHatHitbox != nullptr)
	{//nullチェック
		m_pHatHitbox->Release();				//メモリを解放する
		m_pHatHitbox = nullptr;					//ポインタをnullにする
	}

	//体力UIの破棄処理
	if (m_pLife != nullptr)
	{//nullチェック
		m_pLife->Release();						//メモリを解放する
		m_pLife = nullptr;						//ポインタをnullにする
	}
}

//更新処理
void CEnvy::Update(void)
{
	UpdatePointers();				//ポイントの更新処理

	//死んでいなかったら、上下に移動させる
	if (m_state != state_death)
	{
		m_fAngleMove += D3DX_PI * 0.02f;
		D3DXVECTOR3 pos = GetPos();
		pos.y += 0.5f * sinf(m_fAngleMove);
		SetPos(pos);
	}

	UpdateState();			//状態によっての更新処理

	if (!m_bEnd)
	{//死んでいなかったら
		CObject_2D::Update();	//基本クラスの更新処理
	}
}

//描画処理
void CEnvy::Draw(void)
{
	//基本クラスの描画処理
	CObject_2D::Draw();
}

//終わったかどうかの取得処理
const bool CEnvy::GetEnd(void)
{
	return m_bEnd;
}



//=============================================================================
//
//								静的関数
//
//=============================================================================



//生成処理
CEnvy* CEnvy::Create(void)
{
	CEnvy* pEnemy = new CEnvy;		//インスタンスを生成する

	if (FAILED(pEnemy->Init()))
	{//初期化処理
		return nullptr;
	}

	D3DXVECTOR3 pos = D3DXVECTOR3(1500.0f, 400.0f, 0.0f);

	pEnemy->SetPos(pos);									//位置の設定
	pEnemy->SetSize(m_EnvySize);							//サイズの設定
	pEnemy->SetTexture(CObject::TextureFace);				//テクスチャの設定
	pEnemy->SetTextureParameter(1, 1, 1, INT_MAX);			//テクスチャパラメータの設定
	pEnemy->SetStartingRot(D3DX_PI * 0.5f);					//向きの初期値の設定
	pEnemy->SetMove(D3DXVECTOR3(-5.0f, 0.0f, 0.0f));		//速度の設定
	pEnemy->SetLife(15000);									//体力の設定

	pEnemy->CreateGears();			//歯車の生成処理

	//ヒットボックスの生成処理
	pEnemy->m_pHitbox = CSquareHitbox::Create(pos, m_HitboxEnvySize, CHitbox::Type_Enemy);
	pEnemy->m_pHatHitbox = CSquareHitbox::Create(pos + pEnemy->m_hatRelativePos, m_HitboxHatSize, CHitbox::Type_Enemy);

	//体力のUIの生成処理
	pEnemy->m_pLife = CEnemyLife::Create(D3DXVECTOR3(900.0f, 40.0f, 0.0f), D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.4f), 15000, "envy");

	return pEnemy;					//生成したインスタンスを返す
}



//=============================================================================
//
//							プライベート関数
//
//=============================================================================



//歯車の生成処理
void CEnvy::CreateGears(void)
{
	//管の相対位置の設定
	m_pipeRelativePos[0] = D3DXVECTOR3(-25.0f, -125.0f, 0.0f);
	m_pipeRelativePos[1] = D3DXVECTOR3(35.0f, -140.0f, 0.0f);

	for (int nCnt = 0; nCnt < nPipeNum; nCnt++)
	{
		//管の生成と必要な情報の設定
		if (m_pPipe[nCnt] == nullptr)
		{
			m_pPipe[nCnt] = CObject_2D::Create();
			m_pPipe[nCnt]->SetPos(GetPos() + m_pipeRelativePos[nCnt]);
			m_pPipe[nCnt]->SetStartingRot(D3DX_PI * 0.5f);
			m_pPipe[nCnt]->SetTexture(CObject::TexturePipe);
			m_pPipe[nCnt]->SetTextureParameter(1, 1, 1, INT_MAX);
			m_pPipe[nCnt]->SetPriority(2);
		}
	}

	if (m_pCannon == nullptr)
	{
		//大砲の生成と必要な情報の設定
		m_cannonRelativePos = D3DXVECTOR3(0.0f, -75.0f, 0.0f);
		m_pCannon = CObject_2D::Create();
		m_pCannon->SetPos(GetPos() + m_cannonRelativePos);
		m_pCannon->SetTexture(CObject::TexturePipe);
		m_pCannon->SetTextureParameter(1, 1, 1, INT_MAX);
		m_pCannon->SetPriority(2);
		m_pCannon->SetSize(D3DXVECTOR2(15.0f, 48.75f));
		m_pCannon->SetStartingRot(D3DX_PI);
	}

	//管のサイズの設定
	m_pPipe[0]->SetSize(D3DXVECTOR2(33.75f, 45.0f));
	m_pPipe[1]->SetSize(D3DXVECTOR2(22.5f, 67.5f));

	//歯車の相対位置の設定
	m_gearRelativePos[0] = D3DXVECTOR3(10.0f, -110.0f, 0.0f);
	m_gearRelativePos[1] = D3DXVECTOR3(70.0f, -120.0f, 0.0f);
	m_gearRelativePos[2] = D3DXVECTOR3(30.0f, -105.0f, 0.0f);
	m_gearRelativePos[3] = D3DXVECTOR3(100.0f, -110.0f, 0.0f);
	m_gearRelativePos[4] = D3DXVECTOR3(-20.0f, -100.0f, 0.0f);
	m_gearRelativePos[5] = D3DXVECTOR3(-60.0f, -110.0f, 0.0f);

	//歯車のサイズと回転速度の設定
	D3DXVECTOR2 size[nGearNum] = { {26.25f, 26.25f },{ 45.0f, 45.0f },{ 26.25f, 26.25f },{ 22.5f, 22.5f },{ 52.5f, 52.5f },{ 30.0f, 30.0f }};
	float fRotSpeed[nGearNum] = { D3DX_PI * 0.01f, -D3DX_PI * 0.01f, D3DX_PI * 0.02f, D3DX_PI * 0.008f, -D3DX_PI * 0.009f, D3DX_PI * 0.025f };

	for (int nCnt = 0; nCnt < nGearNum; nCnt++)
	{
		//歯車の生成と必要な情報の設定
		if (m_pGear[nCnt] == nullptr)
		{
			m_pGear[nCnt] = CObject_2D::Create();
			m_pGear[nCnt]->SetPos(GetPos() + m_gearRelativePos[nCnt]);
			m_pGear[nCnt]->SetSize(size[nCnt]);
			m_pGear[nCnt]->SetRotation(fRotSpeed[nCnt]);
			m_pGear[nCnt]->SetTexture(CObject::TextureGear);
			m_pGear[nCnt]->SetTextureParameter(1, 3, 2, INT_MAX);
			m_pGear[nCnt]->SetPriority(2);
		}
	}

	//歯車のアニメーションパターンの設定
	m_pGear[0]->SetAnimPattern(5);
	m_pGear[1]->SetAnimPattern(2);
	m_pGear[2]->SetAnimPattern(1);
	m_pGear[3]->SetAnimPattern(3);
	m_pGear[4]->SetAnimPattern(2);
	m_pGear[5]->SetAnimPattern(4);

	//帽子の相対位置の設定
	m_hatRelativePos = D3DXVECTOR3(20.0f, -230.0f, 0.0f);

	//帽子の生成と必要な情報の設定
	m_pHat = CObject_2D::Create();
	m_pHat->SetPos(GetPos() + m_hatRelativePos);
	m_pHat->SetSize(D3DXVECTOR2(160.0f, 144.0f));
	m_pHat->SetTexture(CObject::TextureTopHat);
	m_pHat->SetTextureParameter(1, 1, 1, INT_MAX);
	m_pHat->SetStartingRot(D3DX_PI * 0.5f);
}

//状態によっての更新処理
void CEnvy::UpdateState(void)
{
	D3DXVECTOR3 pos = GetPos();			//位置の取得

	switch (m_state)
	{
	case CEnvy::state_spawn:

	{//スポーン状態

		if (pos.x <= 900.0f)
		{//決まった位置に着いたら

			SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));	//速度の設定
			m_state = state_normal;					//普通の状態に設定する
		}
	}

		break;

	case CEnvy::state_normal:

	{//普通の状態

		m_nCntState++;			//状態カウンターをインクリメントする
		m_nShootDelay++;		//攻撃カウンターをインクリメントする		

		if (m_nShootDelay >= 120)
		{//120フレームごと弾を発生する

			m_nShootDelay = 0;			//攻撃カウンターを0に戻す

			//弾を発生する
			CMissile* pBullet = CMissile::Create(D3DXVECTOR3(pos.x - 23.0f, pos.y - 180.0f, 0.0f), D3DXVECTOR3(0.0f, -3.0f, 0.0f));

			//サウンドを再生する
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_ROCKET_START);
		}

		//位置までの距離を計算する
		D3DXVECTOR3 target = CPlayer::GetPlayer()->GetPos();
		target -= pos + m_cannonRelativePos;
		target.x -= 20.0f;

		if (fabsf(target.x) < 100.0f || m_nCntState >= 1200)
		{//位置までの距離は100.0f以下だったら、又は状態カウンターは1200を超えたら

			m_nCntState = 0;			//状態カウンターを0に戻す

			SetMove(D3DXVECTOR3(3.0f, 0.0f, 0.0f));		//速度の設定(画面の右側から出る)

			m_state = state_hide;						//隠す状態にする
		}
	}

		break;
	case CEnvy::state_hide:

	{//隠す状態

		m_nShootDelay++;			//攻撃カウンターをインクリメントする

		if (pos.x >= 1450.0f)
		{//画面を出たら

			SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));			//止まる

			m_state = state_strike;		//攻撃状態にする
			m_nShootDelay = 0;			//攻撃カウンターを0に戻す
		}
	}

		break;

	case CEnvy::state_strike:

	{//攻撃状態

		m_nCntState++;			//状態カウンターをインクリメントする
		m_nShootDelay++;		//攻撃カウンターをインクリメントする

		if (m_nShootDelay % 40 == 39)
		{//40フレームが経ったら

			//弾2つを生成する
			CMissile* pBullet = CMissile::Create(D3DXVECTOR3(1400.0f, 240.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.5f, 0.0f, 0.0f));
			pBullet = CMissile::Create(D3DXVECTOR3(1400.0f, 480.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.5f, 0.0f, 0.0f));

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_ROCKET_START);		//サウンドを再生する
		}

		if (m_nShootDelay >= 60)
		{//60フレームが経ったら

			m_nShootDelay = 0;			//攻撃カウンターを0に戻す

			//弾3つを生成する
			float fY = (float)random(50, 190);
			CMissile* pBullet = CMissile::Create(D3DXVECTOR3(1400.0f, fY, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.5f, 0.0f, 0.0f));
			pBullet = CMissile::Create(D3DXVECTOR3(1400.0f, fY + 240.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.5f, 0.0f, 0.0f));
			pBullet = CMissile::Create(D3DXVECTOR3(1400.0f, fY + 480.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.5f, 0.0f, 0.0f));

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_ROCKET_START);		//サウンドを再生する]
		}

		if (m_nCntState >= 310)
		{//310フレームが経ったら

			m_nCntState = 0;							//状態カウンターを0に戻す
			m_nShootDelay = 0;							//攻撃カウンターを0に戻す
			m_state = state_spawn;						//状態をスポーン状態にする
			SetMove(D3DXVECTOR3(-5.0f, 0.0f, 0.0f));	//速度を設定する(右側から入る)
		}
	}

		break;

	case state_death:

	{//死亡状態

		m_nCntState++;			//状態カウンターをインクリメントする
		m_nShootDelay++;		//攻撃カウンターをインクリメントする

		pos.y -= 50.0f;			//中心点の下から弾を発生する(ダメージを与えない弾)

		if (m_nShootDelay % 30 == 0)
		{//30フレームごと

			int nRand = random(1, 3);		//発生する弾の数を1～3にする

			//============================================================================
			//半径の中に位置を設定して、爆発を生成する
			D3DXVECTOR3 P = pos;
			float radius = GetSize().x * 0.45f;

			P.x += (float)random((int)-radius, (int)radius);
			P.y += (float)random((int)-radius, (int)radius);

			CExplosion* pExplosion = CExplosion::Create();
			pExplosion->SetPos(P);
			pExplosion->SetSize(D3DXVECTOR2(50.0f, 50.0f));
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_BIG_EXPLOSION);
			//============================================================================

			for (int nCnt = 0; nCnt < nRand; nCnt++)
			{//発生する弾の数を1～3にする
				CEnvyPieces::Create(pos, radius);
			}
		}

		if (GetPos().y >= 1000.0f)
		{//画面を出たら、終わった状態にする
			m_bEnd = true;
		}
	}

		break;
	
	default:
		break;
	}
}

//ポインタの更新処理
void CEnvy::UpdatePointers(void)
{
	//帽子の更新処理
	if (m_pHat != nullptr)
	{//nullチェック

		//帽子のヒットボックスの更新処理
		if (m_pHatHitbox != nullptr)
		{//nullチェック

			//位置とヒットボックスの位置を設定する
			m_pHat->SetPos(GetPos() + m_hatRelativePos);
			m_pHatHitbox->SetPos(m_pHat->GetPos());

			int life = GetLife();			//体力の取得

			if (m_pHatHitbox->GetHitState())
			{//当たった状態だったら

				m_pHatHitbox->SetHitState(false);					//当っていない状態に戻す
				int nDamage = CPlayer::GetPlayer()->GetAttack();	//プレイヤーの攻撃力の取得
				life -= nDamage;									//体力の更新
				SetLife(life);										//体力の設定

				//体力UIの更新
				if (m_pLife != nullptr)
				{//nullチェック
					m_pLife->SubtractLife(nDamage);
				}
			}

			if (life < 10000)
			{//体力が10000以下になったら

				//帽子の速度と加速を設定して、回転させる。帽子のヒットボックスを破棄する
				m_pHat->SetMove(D3DXVECTOR3(4.0f, -8.0f, 0.0f));
				m_pHat->SetAcceleration(D3DXVECTOR3(0.0f, 0.2f, 0.0f));
				m_pHat->SetRotation(-D3DX_PI * 0.025f);
				m_pHatHitbox->Release();
				m_pHatHitbox = nullptr;
			}
		}
		else
		{//帽子のヒットボックスへのポインタがnullだったら

			if (m_pHat->GetPos().y > 1000.0f || m_pHat->GetPos().x > 1500.0f)
			{//画面を出たら、帽子を破棄する
				m_pHat->Release();
				m_pHat = nullptr;
			}
		}
	}

	//===========================================================================================================================================
	//大砲の更新処理
	if (m_pCannon != nullptr && GetLife() < 12500)
	{//体力が12500以下になったら

		int a = 0;
		if (m_cannonRelativePos.x > -115.0f)
		{//大砲が見えるまで、左へ移動させる
			m_cannonRelativePos.x += -0.5f;
		}
		else
		{//決まった位置に着いたら

			if (m_nShootDelay % 60 == 0 && (m_state == state_normal || m_state == state_hide))
			{//60フレームごと弾を発生する

				//大砲からプレイヤーまでのベクトルを計算する
				D3DXVECTOR3 target = CPlayer::GetPlayer()->GetPos();
				target -= GetPos() + m_cannonRelativePos;
				target.x -= 20.0f;

				if (fabsf(target.x) >= 100.0f)
				{//近すぎない場合

					//弾を発生する
					D3DXVec3Normalize(&target, &target);
					target.x *= 5.0f;
					target.y *= 5.0f;

					D3DXVECTOR3 P = GetPos() + m_cannonRelativePos;
					P.x -= 20.0f;

					CSpikeBomb* pBullet = CSpikeBomb::Create(P, target);				//弾の生成

					CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_CANNON);		//サウンドを再生する
				}
			}
		}
	}

	//歯車の更新処理
	for (int nCnt = 0; nCnt < nGearNum; nCnt++)
	{
		if (m_pGear[nCnt] != nullptr)
		{//nullチェック
			m_pGear[nCnt]->SetPos(GetPos() + m_gearRelativePos[nCnt]);		//位置の更新
		}
	}

	//管の更新処理
	for (int nCnt = 0; nCnt < nPipeNum; nCnt++)
	{
		if (m_pPipe[nCnt] != nullptr)
		{//nullチェック
			m_pPipe[nCnt]->SetPos(GetPos() + m_pipeRelativePos[nCnt]);		//位置の更新
		}
	}

	//大砲の位置の更新
	if (m_pCannon != nullptr)
	{//nullチェック
		m_pCannon->SetPos(GetPos() + m_cannonRelativePos);
	}

	//ヒットボックスの更新処理
	if (m_pHitbox != nullptr)
	{//nullチェック

		m_pHitbox->SetPos(GetPos());		//ヒットボックスの位置の更新

		if (m_state != state_death)
		{//死亡状態ではなかったら

			if (m_pHitbox->GetHitState())
			{//当たった状態だったら

				m_pHitbox->SetHitState(false);			//当っていない状態に戻す

				int nLife = GetLife();								//体力の取得
				int nDamage = CPlayer::GetPlayer()->GetAttack();	//プレイヤーの攻撃力の取得
				nLife -= nDamage;									//体力の更新

				//体力のUIの更新
				if (m_pLife != nullptr)
				{//nullチェック
					m_pLife->SubtractLife(nDamage);
				}

				if (nLife <= 0)
				{//体力が0以下になったら

					//死亡状態にして、ヒットボックスを破棄する
					m_state = state_death;
					SetMove(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
					m_nCntState = 0;
					m_nShootDelay = 0;
					m_pHitbox->Release();
					m_pHitbox = nullptr;
					SetLife(0);
					return;
				}
				else
				{//体力が0以上だったら

					SetLife(nLife);		//体力の設定
				}

				//帽子のヒットボックスへのポインタがnullだったら(帽子が落ちた時)
				if (m_pHatHitbox == nullptr)
				{
					//位置と速度を設定する(プレイヤーの方向で上に設定する。重量があるので、上から落ちてくる)
					D3DXVECTOR3 pos = GetPos();
					pos.y -= 100.0f;

					D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					move.x = -0.01f * (float)random(100, 500);
					move.y = -0.01f * (float)random(400, 800);

					int nRand = random(1, 3);			//ランダムでスポーンする弾の個数を設定する

					for (int nCnt = 0; nCnt < nRand; nCnt++)
					{
						move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
						move.x = -0.01f * (float)random(100, 500);
						move.y = -0.01f * (float)random(400, 800);

						CEnvyPieces::Create(pos, move);
					}
				}
			}
		}
	}
}