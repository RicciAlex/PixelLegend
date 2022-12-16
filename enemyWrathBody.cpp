//=============================================================================
//
// enemyWrathBody.cpp
// Author : Ricci Alex
//
//=============================================================================

//インクルードファイル
#include "enemyWrathBody.h"
#include "circleHitbox.h"
#include "squareHitbox.h"
#include "application.h"
#include "sound.h"
#include "skullFireball.h"
#include "player.h"
#include "wrath.h"


//コンストラクタ
CWrathBody::CWrathBody()
{
	//メンバー変数をクリアする
	m_nCntShoot = 0;
	m_nCntState = 0;
	m_state = state_spawn;

	m_pHitbox = nullptr;
	m_pHeadHitbox = nullptr;
	m_bDead = false;
	m_bBound = false;
	m_pArm = nullptr;
	m_pParent = nullptr;

	m_posArm =D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posBodyHitbox = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posHeadHitbox = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_targetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//デストラクタ
CWrathBody::~CWrathBody()
{

}

//初期化処理
HRESULT CWrathBody::Init(void)
{
	//メンバー変数を初期化する

	//基本クラスの初期化処理
	if (FAILED(CEnemy::Init()))
	{
		return -1;
	}

	m_nCntShoot = 0;
	m_nCntState = 0;
	m_state = state_spawn;

	m_pHitbox = nullptr;
	m_pHeadHitbox = nullptr;
	m_bDead = false;
	m_bBound = true;
	m_pArm = nullptr;
	m_pParent = nullptr;

	m_posArm = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posBodyHitbox = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posHeadHitbox = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_targetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return S_OK;
}

//終了処理
void CWrathBody::Uninit(void)
{
	//体のヒットボックスの破棄処理
	if (m_pHitbox != nullptr)
	{//nullチェック
		m_pHitbox->Release();			//メモリを解放する
		m_pHitbox = nullptr;			//nullにする
	}
	//頭のヒットボックスの破棄処理
	if (m_pHeadHitbox != nullptr)
	{//nullチェック
		m_pHeadHitbox->Release();		//メモリを解放する
		m_pHeadHitbox = nullptr;		//nullにする
	}
	//腕の破棄処理
	if (m_pArm != nullptr)
	{//nullチェック
		m_pArm->Release();				//メモリを解放する
		m_pArm = nullptr;				//nullにする
	}
	//親へのポインタがnullではなかったら、nullにする
	if (m_pParent != nullptr)
	{//nullチェック
		m_pParent = nullptr;			//nullにする
	}

	//基本クラスの終了処理
	CEnemy::Uninit();
}
//更新処理
void CWrathBody::Update(void)
{
	//状態によっての更新処理
	UpdateState();

	//基本クラスの更新処理
	CObject_2D::Update();

	D3DXVECTOR3 pos = GetPos();				//位置の取得

	//体のヒットボックスの更新
	if (m_pHitbox != nullptr)
	{//nullチェック

		m_pHitbox->SetPos(pos + m_posBodyHitbox);			//体のヒットボックスの位置の設定

		if (m_pHitbox->GetHitState())
		{//当たった状態だったら

			m_pHitbox->SetHitState(false);				//当っていない状態に戻す

			int nDamage = CPlayer::GetPlayer()->GetAttack();	//プレイヤーの攻撃力の取得

			int nLife = GetLife() - nDamage;			//体力の更新

			//親へのポインタがnullではなかったら、ダメージを与える
			if (m_pParent != nullptr)
			{//nullチェック
				m_pParent->Damage(nDamage);
			}

			if (nLife <= 0)
			{//体力が0以下になったら

				m_pHitbox->Release();			//ヒットボックスを破棄する
				m_pHitbox = nullptr;			//ポインタをnullにする

				if (m_pHeadHitbox != nullptr)
				{//頭のヒットボックスがnullではなかったら、

					m_pHeadHitbox->Release();	//ヒットボックスを破棄する
					m_pHeadHitbox = nullptr;	//ポインタをnullにする
				}

				SetMove(D3DXVECTOR3(4.0f, -10.0f, 0.0f));			//速度の設定
				SetAcceleration(D3DXVECTOR3(0.0f, 0.5f, 0.0f));		//加速の設定
				SetAnimPattern(4);									//アニメションパターンの設定
				m_nPhase = 0;										//カウンターを0に戻す
				m_bBound = false;									//親に結んでいない状態にする
				m_state = state_death;								//状態の更新
				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_WRATH_DEATH);			//サウンドを再生する

				return;
			}
			
			SetLife(nLife);				//体力の更新
		}
	}

	//頭のヒットボックスの更新
	if (m_pHeadHitbox != nullptr)
	{//nullチェック

		m_pHeadHitbox->SetPos(pos + m_posHeadHitbox);			//頭のヒットボックスの位置の設定

		if (m_pHeadHitbox->GetHitState())
		{//当たった状態だったら

			m_pHeadHitbox->SetHitState(false);					//当っていない状態に戻す

			int nDamage = CPlayer::GetPlayer()->GetAttack();	//プレイヤーの攻撃力の取得

			int nLife = GetLife() - nDamage;					//体力の更新

			//親へのポインタがnullではなかったら
			if (m_pParent != nullptr)
			{
				m_pParent->Damage(nDamage);		//親にダメージを与える
			}

			if (nLife <= 0)
			{//体力が0以下になったら
				m_pHeadHitbox->Release();			//ヒットボックスを破棄する
				m_pHeadHitbox = nullptr;			//ポインタをnullにする

				if (m_pHitbox != nullptr)
				{//体へのポインタがnullではなかったら
					m_pHitbox->Release();			//ヒットボックスを破棄する
					m_pHitbox = nullptr;			//ポインタをnullにする
				}

				SetMove(D3DXVECTOR3(4.0f, -13.0f, 0.0f));				//速度の設定
				SetAcceleration(D3DXVECTOR3(0.0f, 0.5f, 0.0f));			//加速の設定
				SetAnimPattern(4);										//アニメションパターンの設定
				m_nPhase = 0;											//カウンターを0に戻す
				m_bBound = false;										//親に結んでいない状態にする
				m_state = state_death;									//状態の更新
				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_WRATH_DEATH);			//サウンドを再生する

				return;
			}

			SetLife(nLife);				//体力の設定
		}
	}
	//腕の更新
	if (m_pArm != nullptr && m_bBound)
	{//腕へのポインタがnullではなくて、親に結んでいる状態だったら

		m_pArm->SetPos(pos + m_posArm);			//位置の設定
	}
}

//描画処理
void CWrathBody::Draw(void)
{
	//基本クラスの描画処理
	CEnemy::Draw();
}

//親へのポインタの設定処理
void CWrathBody::SetParent(CWrath* pParent)
{
	m_pParent = pParent;
}

//死亡したかどうかの取得処理
const bool CWrathBody::GetDeath(void)
{
	return m_bDead;
}

//==========================================================================================================
//
//											静的関数
//
//==========================================================================================================


//生成処理
CWrathBody* CWrathBody::Create(D3DXVECTOR3 pos)
{
	CWrathBody* pEnemy = new CWrathBody;			//新しい敵を生成する

		//初期化処理
	if (FAILED(pEnemy->Init()))
	{
		return nullptr;					//nullを返す
	}

	pEnemy->SetPos(pos);										//位置の設定
	pEnemy->SetObjType(CObject::OBJTYPE_ENEMY);					//オブジェクトの種類の設定
	pEnemy->SetStartingRot(D3DX_PI * 0.5f);						//回転角度の初期値の設定
	pEnemy->m_nCntMove = 0;										//カウンタの設定
	pEnemy->m_nShootDelay = 0;									//カウンタの設定
	pEnemy->SetTextureParameter(1, 2, 3, INT_MAX);				//テクスチャパラメータの設定
	pEnemy->SetSize(D3DXVECTOR2(120.0f, 241.0f));				//サイズの設定

	pEnemy->SetMove(D3DXVECTOR3(-2.0f, 0.0f, 0.0f));			//速度の設定
	pEnemy->SetAcceleration(D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//加速の設定
	pEnemy->SetSubtype(ENEMYTYPE_WRATH_BODY);					//敵の種類の設定
	pEnemy->SetLife(15000);										//体力の設定

	pEnemy->SetTexture(TextureWrath);						//テクスチャの設定

	pEnemy->m_posBodyHitbox = D3DXVECTOR3(0.0f, 135.0f, 0.0f);	//体のヒットボックスの位置の設定
	pEnemy->m_posHeadHitbox = D3DXVECTOR3(5.0f, -85.0f, 0.0f);	//頭のヒットボックスの位置の設定

	//体のヒットボックスの生成
	pEnemy->m_pHitbox = CSquareHitbox::Create(pos + pEnemy->m_posBodyHitbox, D3DXVECTOR2(60.0f, 85.0f), CHitbox::Type_Enemy);

	//頭のヒットボックスの生成
	pEnemy->m_pHeadHitbox = CCircleHitbox::Create(pos + pEnemy->m_posHeadHitbox, 100.0f, CHitbox::Type_Enemy);

	pEnemy->m_posArm = D3DXVECTOR3(0.0f, 250.0f, 0.0f);			//腕の位置の設定

	//腕の生成
	pEnemy->m_pArm = CObject_2D::Create();						//インスタンスを生成する
	pEnemy->m_pArm->SetPos(pos + pEnemy->m_posArm);				//位置の設定
	pEnemy->m_pArm->SetSize(D3DXVECTOR2(126.0f, 193.5));		//サイズの設定
	pEnemy->m_pArm->SetTexture(CObject::TextureHand);			//テクスチャの設定
	pEnemy->m_pArm->SetTextureParameter(1, 4, 1, INT_MAX);		//テクスチャパラメータの設定
	pEnemy->m_pArm->SetPriority(2);								//プライオリティの設定
	pEnemy->m_pArm->SetStartingRot(D3DX_PI * 0.5f);				//向きの初期値の設定

	return pEnemy;				//生成されたインスタンスへのポンタを返す
}



//==========================================================================================================
//
//										プライベート関数
//
//==========================================================================================================


//状態によっての更新処理
void CWrathBody::UpdateState(void)
{
	D3DXVECTOR3 pos = GetPos();					//位置の取得
		
	switch (m_state)
	{
	case CWrathBody::state_spawn:

	{//スポーン状態

		//上下移動の設定
		pos.y += 0.5f * sinf(m_fAngleMove);				
		m_fAngleMove += D3DX_PI * 0.01f;

		if (pos.x <= 950.0f)
		{//決まった位置についたら
			m_state = state_normal;							//普通の状態にする
			SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));			//速度の設定
		}

		SetPos(pos);					//位置の設定
	}

		break;

	case CWrathBody::state_normal:

	{//普通状態

	 //上下移動の設定
		pos.y += 0.5f * sinf(m_fAngleMove);
		m_fAngleMove += D3DX_PI * 0.01f;

		SetPos(pos);			//位置の設定

		m_nCntState++;			//カウンターを更新する

		if (m_nCntState >= 90)
		{//90フレームが経ったら

			m_nCntState = 0;				//カウンターを0に戻す

			//ランダムで次の攻撃を決める
			int nSelect = CObject::random(CWrathBody::state_flamethrower, CWrathBody::state_swirl);

			switch (nSelect)
			{
			case state_flamethrower:

			{//炎攻撃

				m_state = state_flamethrower;		//状態の更新
				SetAnimPattern(1);					//アニメションパターンの設定
			}

				break;

			case state_rage:

			{//怒りの攻撃

				m_state = state_rage;						//状態の更新
				SetAnimPattern(1);							//アニメションパターンの設定
				SetMove(D3DXVECTOR3(2.0f, 0.0f, 0.0f));		//速度の設定
			}

				break;

			case state_swirl:

			{//渦巻攻撃
				m_state = state_swirl;				//状態の更新
			}

				break;

			default:
				break;
			}
		}
	}

		break;

	case CWrathBody::state_flamethrower:

	{//炎攻撃

		m_nShootDelay++;				//攻撃カウンターを更新する

		if (m_nShootDelay >= 50)
		{//50フレームが経ったら

			if (m_nShootDelay % 20 == 19)
			{//20フレームごとアニメションパターンを更新する

				if (GetPresentAnimPattern() == 2)
				{
					SetAnimPattern(3);		//アニメションパターンを更新する
				}
				else
				{
					SetAnimPattern(2);		//アニメションパターンを更新する
				}
			}

			if (m_nShootDelay % 20 == 19)
			{//20フレームごと弾を発生する

				D3DXVECTOR3 playerPos = CPlayer::GetPlayer()->GetPos();			//プレイヤーの位置の取得
				D3DXVECTOR3 move = playerPos - pos;								//速度の計算
				D3DXVec3Normalize(&move, &move);								//速度を正規化する

				//弾を生成する
				CSkullFireball::Create(pos, D3DXVECTOR3(move.x * 3.0f, move.y * 3.0f, 0.0f));

				//中心線から±15°と±30°にも弾を発生する
				D3DXVECTOR3 unit = D3DXVECTOR3(1.0f, 0.0f, 0.0f);		//単位ベクトルの宣言

				float fAngle = acosf(D3DXVec3Dot(&move, &unit));		//最初の弾の角度を計算する

				if (playerPos.y < pos.y)
				{//必要だったら、正規化する
					fAngle *= -1.0f;
				}

				//時間によって弾を発生する(最初に1つだけ、次は３つ、最後に５つ)
				if (m_nPhase > 0)
				{//±15°の弾を生成するする
					D3DXVECTOR3 NewMove = D3DXVECTOR3(cosf(fAngle) * cosf(D3DX_PI / 12.0f) - sinf(fAngle) * sinf(D3DX_PI / 12.0f),
						sinf(fAngle) * cosf(D3DX_PI / 12.0f) + cosf(fAngle) * sinf(D3DX_PI / 12.0f), 0.0f);

					CSkullFireball::Create(pos, D3DXVECTOR3(NewMove.x * 3.0f, NewMove.y * 3.0f, 0.0f));

					NewMove = D3DXVECTOR3(cosf(fAngle) * cosf(-D3DX_PI / 12.0f) - sinf(fAngle) * sinf(-D3DX_PI / 12.0f),
						sinf(fAngle) * cosf(-D3DX_PI / 12.0f) + cosf(fAngle) * sinf(-D3DX_PI / 12.0f), 0.0f);

					CSkullFireball::Create(pos, D3DXVECTOR3(NewMove.x * 3.0f, NewMove.y * 3.0f, 0.0f));
				}
				if (m_nPhase == 2)
				{//±30°の弾を生成するする
					D3DXVECTOR3 NewMove = D3DXVECTOR3(cosf(fAngle) * cosf(D3DX_PI / 6.0f) - sinf(fAngle) * sinf(D3DX_PI / 6.0f),
						sinf(fAngle) * cosf(D3DX_PI / 6.0f) + cosf(fAngle) * sinf(D3DX_PI / 6.0f), 0.0f);

					CSkullFireball::Create(pos, D3DXVECTOR3(NewMove.x * 3.0f, NewMove.y * 3.0f, 0.0f));

					NewMove = D3DXVECTOR3(cosf(fAngle) * cosf(-D3DX_PI / 6.0f) - sinf(fAngle) * sinf(-D3DX_PI / 6.0f),
						sinf(fAngle) * cosf(-D3DX_PI / 6.0f) + cosf(fAngle) * sinf(-D3DX_PI / 6.0f), 0.0f);

					CSkullFireball::Create(pos, D3DXVECTOR3(NewMove.x * 3.0f, NewMove.y * 3.0f, 0.0f));
				}

				if (m_nShootDelay == 99 || m_nShootDelay == 159)
				{//100フレームと160フレームが経ったら、カウンターをインクリメントする
					m_nPhase++;
				}
				else if(m_nShootDelay == 240 || m_nShootDelay == 300)
				{//240フレームと300フレームが経ったら、カウンターをデクリメントする
					m_nPhase--;
				}
				
				if (m_nShootDelay >= 360)
				{//360フレームを超えたら、普通の状態に戻す

					if (m_nCntShoot >= 2)
					{//3回この攻撃をしたら
						SetAnimPattern(1);			//アニメションパターンの設定
						m_state = state_normal;		//状態の更新
						m_nPhase = 0;				//カウンターを0に戻す
						m_nShootDelay = 0;			//攻撃カウンターを0に戻す
						m_nCntShoot = 0;			//攻撃数のカウンターを0に戻す
					}
					else
					{
						m_nPhase = 0;				//カウンターを0に戻す
						m_nShootDelay = -70;		//攻撃カウンターを-70に設定する(70フレームを待って、もう一度攻撃する)
						m_nCntShoot++;				//攻撃数のカウンターをインクリメントする
					}
				}

				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_FIRE);			//サウンドを再生する
			}
		}
	}

		break;

	case CWrathBody::state_rage:

	{//怒り攻撃

		switch (m_nPhase)
		{
		case 0:

		{
			if (pos.x >= 1400.0f)
			{//画面を出たら

				SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));			//速度の設定
				m_nPhase++;				//カウンターをインクリメントする
			}
		}

			break;

		case 1:

		{
			m_nShootDelay++;			//攻撃カウンターをインクリメントする

			if (m_nShootDelay == 5)
			{
				m_targetPos = CPlayer::GetPlayer()->GetPos();			//目的の位置の設定
			}

			if (m_nShootDelay % 10 == 9 && m_nShootDelay >= 60)
			{//画面の上側と下側から弾を発生する

				CSkullFireball::Create(D3DXVECTOR3(m_targetPos.x, (float)SCREEN_HEIGHT - 1.0f, 0.0f), D3DXVECTOR3(0.0f, -5.0f, 0.0f));
				CSkullFireball::Create(D3DXVECTOR3(m_targetPos.x - 20.0f, 1.0f, 0.0f), D3DXVECTOR3(0.0f, 5.0f, 0.0f));
				CSkullFireball::Create(D3DXVECTOR3(m_targetPos.x + 20.0f, 1.0f, 0.0f), D3DXVECTOR3(0.0f, 5.0f, 0.0f));

				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_FIRE);			//サウンドを再生する
			}

			if (m_nShootDelay >= 180)
			{//3秒が経ったら
				m_nShootDelay = 0;		//攻撃カウンターを0に戻す
				m_nCntShoot++;			//攻撃数のカウンターをインクリメントする
			}

			if (m_nCntShoot >= 5)
			{//この攻撃を5回したら

				//カウンターを0に戻す
				m_nShootDelay = 0;
				m_nCntShoot = 0;
				m_nPhase++;

				SetMove(D3DXVECTOR3(-2.0f, 0.0f, 0.0f));		//移動量の設定
			}
		}

			break;

		case 2:

		{
			{
				//上下の移動の設定
				pos.y += 0.5f * sinf(m_fAngleMove);
				m_fAngleMove += D3DX_PI * 0.01f;

				if (pos.x <= 950.0f)
				{//決まった位置に着いたら
					m_nPhase = 0;								//カウンターを0に戻す
					m_state = state_normal;						//状態の更新
					SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//速度の設定
				}
					
				SetPos(pos);					//位置の設定
			}
		}

		default:
			break;
		}
	}

		break;

	case CWrathBody::state_swirl:

	{//渦巻の攻撃

		m_nShootDelay++;				//攻撃カウンターをインクリメントする

		{
			//上下の移動の設定
			pos.y += 0.5f * sinf(m_fAngleMove);
			m_fAngleMove += D3DX_PI * 0.01f;

			SetPos(pos);			//位置の設定
		}

		if (m_nShootDelay % 20 == 19)
		{//20フレームごとアニメションパターンを更新する
			if (GetPresentAnimPattern() == 2)
			{
				SetAnimPattern(3);
			}
			else
			{
				SetAnimPattern(2);
			}
		}

		if (m_nShootDelay % 40 == 39)
		{//40フレームごと渦巻の弾を発生する

			float fStart = D3DX_PI * random(-500, 500) * 0.01f;

			for (int nCnt = 0; nCnt < 10; nCnt++)
			{
				D3DXVECTOR3 move = D3DXVECTOR3(5.0f * cosf(fStart + D3DX_PI * 2.0f * nCnt / 10.0f), 5.0f * sinf(fStart + D3DX_PI * 2.0f * nCnt / 10.0f), 0.0f);

				CSkullFireball::Create(pos, move);			//弾の生成
			}

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_FIRE);			//サウンドを再生する
		}

		if (m_nShootDelay % 40 == 19)
		{//40フレームごとプレイヤーの位置を狙った弾を発生する

			//速度を計算する
			D3DXVECTOR3 move = D3DXVECTOR3(CPlayer::GetPlayer()->GetPos() - pos);
			D3DXVec3Normalize(&move, &move);
			move.x *= 5.0f;
			move.y *= 5.0f;

			CSkullFireball::Create(pos, move);			//弾を発生する
		}

		if (m_nShootDelay >= 600)
		{//600フレームが経ったら、普通の状態に戻す
			m_nShootDelay = 0;				//攻撃カウンターを0に戻す
			m_state = state_normal;			//普通の状態に戻す
		}
	}

		break;

	case CWrathBody::state_death:

	{//死亡状態

		if (m_nPhase == 0)
		{
			if (pos.y >= (float)SCREEN_HEIGHT + GetSize().y * 0.5f)
			{

				//腕がnullではなかったら
				if (m_pArm != nullptr)
				{//nullチェック
					m_pArm->SetMove(D3DXVECTOR3(0.0f, 2.0f, 0.0f));		//速度の設定
					m_nPhase++;											//カウンターをインクリメントする
				}
			}
		}
		else if (m_nPhase == 1)
		{
			if (m_pArm->GetPos().y >= (float)SCREEN_HEIGHT + m_pArm->GetSize().y)
			{//このインスタンスが画面を出たら、死亡状態にする
				m_bDead = true;
			}
		}
	}

		break;

	default:
		break;
	}
}