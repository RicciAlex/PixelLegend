//=============================================================================
//
// pride.cpp
// Author : Ricci Alex
//
//=============================================================================

//インクルードファイル
#include "pride.h"
#include "circleHitbox.h"
#include "balloon.h"
#include "player.h"
#include "laugh.h"
#include "balloonEnemy.h"
#include "starBullet.h"
#include "bouncingBullet.h"
#include "enemyLife.h"
#include "application.h"
#include "sound.h"

//コンストラクタ
CPride::CPride()
{
	//メンバー変数をクリアする
	m_state = state_Spawn;
	m_nSpawnFrame = 0;
	m_bEnd = false;

	m_pHitbox = nullptr;
	m_pLife = nullptr;
}

//デストラクタ
CPride::~CPride()
{

}

//初期化処理
HRESULT CPride::Init(void)
{
	if (FAILED(CEnemy::Init()))
	{//基本クラスの初期化処理
		return -1;
	}

	//メンバー変数を初期化する
	m_state = state_Spawn;
	m_nSpawnFrame = 0;
	m_bEnd = false;

	SetTexture(CObject::TexturePride);
	SetTextureParameter(1, 3, 2, INT_MAX);

	m_pLife = nullptr;

	return S_OK;
}

//終了処理
void CPride::Uninit(void)
{
	//ヒットボックスの破棄処理
	if (m_pHitbox != nullptr)
	{//nullチェック
		m_pHitbox->Release();			//メモリを解放する
		m_pHitbox = nullptr;			//ポインタをnullにする
	}

	//体力UIの破棄処理
	if (m_pLife != nullptr)
	{//nullチェック
		m_pLife->Release();				//メモリを解放する
		m_pLife = nullptr;				//ポインタをnullにする
	}

	//基本クラスの終了処理
	CEnemy::Uninit();
}

//更新処理
void CPride::Update(void)
{
	//基本クラスの更新処理
	CObject_2D::Update();

	//ヒットボックスの更新処理
	if (m_pHitbox != nullptr)
	{//nullチェック

		m_pHitbox->SetPos(GetPos());		//位置の更新

		if (m_pHitbox->GetHitState())
		{//当たった状態だったら

			m_pHitbox->SetHitState(false);	//当っていない状態に戻す

			int nLife = GetLife();								//体力の取得
			int nDamage = CPlayer::GetPlayer()->GetAttack();	//プレイヤーの攻撃力の取得
			nLife -= nDamage;									//体力の更新

			if (nLife <= 0)
			{//体力が0以下になったら

				m_state = state_Death;							//死亡状態にする
				SetAnimPattern(4);								//アニメションパターンの更新
				m_nCntMove = 0;									//移動カウンターを0に戻す
				m_nPhase = 0;									//カウンターを0に戻す
				m_fAngleMove = 0;								//移動角度を0に戻す
				SetMove(D3DXVECTOR3(0.0f, 3.0f, 0.0f));			//速度の設定
				m_pHitbox->Release();							//ヒットボックスの破棄
				m_pHitbox = nullptr;							//ポインタをnullにする
				SetLife(0);										//体力を0に設定する
			}
			else
			{//体力は0以下ではなかったら

				SetLife(nLife);				//体力の設定

				//体力のUIの更新
				if (m_pLife != nullptr)
				{//nullチェック

					m_pLife->SubtractLife(nDamage);			//UIの更新
				}
			}
		}
	}

	UpdateState();					//状態によっての更新処理
}

//描画処理
void CPride::Draw(void)
{
	//基本クラスの描画処理
	CEnemy::Draw();
}

//終わったかどうかの取得処理
const bool CPride::GetEnd(void)
{
	return m_bEnd;
}



//=============================================================================
//
//								静的関数
//
//=============================================================================



//生成処理
CPride* CPride::Create(void)
{
	CPride* pEnemy = new CPride;				//インスタンスの生成

	if (FAILED(pEnemy->Init()))
	{//初期化処理
		return nullptr;
	}

	pEnemy->SetPos(D3DXVECTOR3(1000.0f, -180.0f, 0.0f));		//位置の設定
	pEnemy->SetMove(D3DXVECTOR3(0.0f, 1.5f, 0.0f));				//速度の設定
	pEnemy->SetSize(D3DXVECTOR2(140.0f, 140.0f));				//サイズの設定
	pEnemy->SetStartingRot(D3DX_PI * 0.5f);						//向きの初期値の設定
	pEnemy->SetLife(25000);										//体力の設定

	//ヒットボックスの生成
	pEnemy->m_pHitbox = CCircleHitbox::Create(D3DXVECTOR3(500.0f, 300.0f, 0.0f), 125.0f, CHitbox::Type_Enemy);

	//体力のUIの生成
	pEnemy->m_pLife = CEnemyLife::Create(D3DXVECTOR3(900.0f, 40.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.75f, 0.4f), 25000, "pride");

	return pEnemy;							//生成したインスタンスを返す
}





//=============================================================================
//
//							プライベート関数
//
//=============================================================================




//状態によっての更新処理
void CPride::UpdateState(void)
{
	switch (m_state)
	{

	case state_Spawn:

	{//スポーン状態

		D3DXVECTOR3 pos = GetPos();				//位置の取得

		if (pos.y >= 180.0f)
		{//決まった位置に着いたら

			SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));							//速度の設定
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_LAUGH);	//笑うサウンドを再生する
			m_state = state_LaughAnim;										//笑う状態に切り替える
			SetAnimPattern(1);												//テクスチャパラメータの設定
		}
	}

	break;

	case state_Normal:

	{//普通の状態

		m_state = state_BouncingBall;
	}

	break;

	case state_Hide:

	{//隠す状態

		D3DXVECTOR3 pos = GetPos();							//位置の取得
		D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//速度

		//下内の位置によって速度を設定する
		if (pos.x >= (float)SCREEN_WIDTH * 0.5f)
		{//画面の右側にいたら

			move.x += 5.0f;			//右側を向かうように設定する
		}
		else
		{//画面の左側にいたら
			move.x += -5.0f;		//左側を向かうように設定する
		}
		if (pos.y >= (float)SCREEN_HEIGHT * 0.5f)
		{//画面の上側にいたら
			move.y += 5.0f;			//上側を向かうように設定する
		}
		else
		{//画面の下側にいたら
			move.y += -5.0f;		//下側を向かうように設定する
		}

		if (pos.x >= (float)SCREEN_WIDTH + 200.0f || pos.x <= -200.0f || pos.y >= (float)SCREEN_HEIGHT + 200.0f || pos.y <= -200.0f)
		{//画面を出たら

			//速度を設定する
			move.x = 0.0f;
			move.y = 3.0f;
			m_state = state_Spawn;							//状態の更新
			SetPos(D3DXVECTOR3(1000.0f, -180.0f, 0.0f));	//位置を設定する
		}

		SetMove(move);				//速度の設定

	}

	break;

	case state_BouncingBall:

	{//玉弾

		m_nShootDelay++;				//攻撃カウンターをインクリメントする

		//アニメーション処理
		if (m_nShootDelay == 10)
		{
			SetAnimPattern(3);
		}
		else if (m_nShootDelay == 55)
		{
			SetAnimPattern(4);
		}

		//弾を発生する
		if (m_nShootDelay >= 60)
		{//60フレームごと弾を発生する

			m_nShootDelay = 0;				//攻撃カウンターを0に戻す

			for (int nCnt = 0; nCnt < 3; nCnt++)
			{//弾を発生する(３つ)

				//ランダムな方向に弾を発生する
				D3DXVECTOR3 PlayerPos = CPlayer::GetPlayer()->GetPos();
				D3DXVECTOR3 Target = PlayerPos - D3DXVECTOR3(GetPos().x, GetPos().y + 90.0f, 0.0f);
				D3DXVec3Normalize(&Target, &Target);
				D3DXVECTOR3 V = D3DXVECTOR3((float)random(-5000, 5000), (float)random(-5000, 5000), 0.0f);
				D3DXVec3Normalize(&V, &V);
				Target += V;
				D3DXVec3Normalize(&Target, &Target);
				Target.x *= 6.0f;
				Target.y *= 6.0f;

				//弾の生成
				CBouncingBullet* pBullet = CBouncingBullet::Create(D3DXVECTOR3(GetPos().x, GetPos().y + 90.0f, 0.0f), Target);
			}

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_SHOT);			//弾の発生のサウンドを再生する

			m_nPhase++;				//攻撃数のカウンターをインクリメントする
		}

		if (m_nPhase >= 10)
		{//10回攻撃したら

			m_nShootDelay = 0;			//攻撃カウンターを0に戻す
			m_nPhase = 0;				//攻撃数のカウンターを0に戻す
			SetAnimPattern(0);			//テクスチャパラメータを0に戻す
			m_state = state_Hide;		//隠す状態に戻す
		}
	}

	break;

	case state_Star:

	{//星攻撃の状態

		m_nCntMove++;			//移動カウンターの更新

		if (m_nCntMove >= m_nSpawnFrame)
		{//移動カウンターがスポーンフレーム以上になったら

			m_nSpawnFrame = random(40, 150);			//次のスポーンフレームを設定する

			//星型の弾の生成
			CStarBullet* pBullet = CStarBullet::Create(GetPos(), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_STAR_BULLET);			//サウンドを再生する

			m_nCntMove = 0;				//移動カウンターを0に戻す
		}

		if (GetPos().x < -201.0f || GetPos().x > 1481.0f)
		{//画面を出たら

			D3DXVECTOR3 move = GetMove();			//速度の取得
			move.x *= -1.0f;						//X座標を逆にする
			SetMove(move);							//速度の設定
			D3DXVECTOR3 pos = D3DXVECTOR3(GetPos().x, CPlayer::GetPlayer()->GetPos().y, 0.0f);			//位置のY座標をプレイヤーの同じ高さに設定する
			SetPos(pos);							//位置の設定
			m_nPhase++;								//カウンターをインクリメントする

			if (m_nPhase >= 5)
			{//5回この攻撃をしたら、

				m_nPhase = 0;			//カウンターを0に戻す
				m_state = state_Hide;	//隠す状態にする
			}
		}
	}

	break;

	case state_CreateEnemy:

	{//召喚攻撃

		m_nCntMove++;				//移動カウンターをインクリメントする

		if (m_nCntMove % 80 == 79)
		{//テクスチャパラメータの設定
			SetAnimPattern(4);
		}

		if (m_nCntMove >= 100)
		{//100フレームを超えたら、敵を生成する

			//敵の生成
			CBalloonEnemy* pEnemy = CBalloonEnemy::Create(D3DXVECTOR3(GetPos().x, GetPos().y + 90.0f, 0.0f));

			SetAnimPattern(0);			//テクスチャパラメータの設定

			m_nCntMove = 0;				//移動カウンターを0に戻す

			m_nPhase++;					//攻撃数のカウンターをインクリメントする

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_BALLOON_POP);			//サウンドを再生する

			if (m_nPhase >= 7)
			{//7回この攻撃をしたら

				m_nPhase = 0;				//攻撃数のカウンターを0に戻す
				m_state = state_Hide;		//隠す状態に戻す
			}
		}
	}

	break;

	case state_LaughAttack:

	{//笑う攻撃

		m_nCntMove++;			//移動カウンターをインクリメントする

		if (m_nCntMove % 20 == 19)
		{//20フレームごとアニメションパターンを更新する
			if (GetPresentAnimPattern() == 1)
			{
				SetAnimPattern(2);
			}
			else if (GetPresentAnimPattern() == 2)
			{
				SetAnimPattern(1);
			}
		}

		if (m_nCntMove >= 40)
		{//40フレームごと弾を発生する

			m_nCntMove = 0;			//移動カウンターを0に戻す

			//この敵からプレイヤーまでのベクトルを計算して、正規化したら、弾の速度のとして使う
			D3DXVECTOR3 PlayerPos = CPlayer::GetPlayer()->GetPos();	
			D3DXVECTOR3 Target = PlayerPos - D3DXVECTOR3(GetPos().x, GetPos().y + 90.0f, 0.0f);
			D3DXVec3Normalize(&Target, &Target);
			Target.x *= 5.0f;
			Target.y *= 5.0f;

			//弾の生成
			CLaughBullet* pBullet = CLaughBullet::Create(D3DXVECTOR3(GetPos().x, GetPos().y + 90.0f, 0.0f), Target);

			m_nPhase++;			//攻撃数のカウンターをインクリメントする

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_LAUGH);			//サウンドを再生する

			if (m_nPhase >= 15)
			{//15回この攻撃をしたら

				m_nPhase = 0;				//攻撃数のカウンターを0に戻す
				SetAnimPattern(0);			//テクスチャパラメータの設定
				m_state = state_Hide;		//隠す状態に戻す
			}
		}
	}

	break;

	case state_Balloon:

	{
		D3DXVECTOR3 pos = GetPos();			//位置の取得

		if (pos.y <= -150.0f)
		{//画面を出たら

			SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));			//速度の設定

			m_nCntMove++;				//移動カウンターをインクリメントする

			if (m_nCntMove >= 20)
			{//20フレームごと弾を発生する

				m_nCntMove = 0;			//移動カウンターを0に戻す

				D3DXVECTOR3 PlayerPos = CPlayer::GetPlayer()->GetPos();		//プレイヤーの位置の取得
					
				//発生する弾の数の設定
				////プレイヤーは画面の上側にいたら
				int nMax = 1;

				if (PlayerPos.y >= (float)SCREEN_HEIGHT * 0.34f && PlayerPos.y < (float)SCREEN_HEIGHT * 0.67f)
				{//プレイヤーは画面の真ん中にいたら
					nMax = 2;
				}
				else if (PlayerPos.y >= (float)SCREEN_HEIGHT * 0.67f)
				{//プレイヤーは画面の下側にいたら
					nMax = 3;
				}

				for (int nCnt = 0; nCnt < nMax; nCnt++)
				{
					//ランダムな速度の設定
					D3DXVECTOR3 move = D3DXVECTOR3(random(-100, 100) * 0.05f, random(50, 100) * 0.05f, 0.0f);
					int nColor = random(0, 5);
					D3DXCOLOR col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

					//色の設定(赤、緑、青、黄、マゼンタ、シアン)
					switch (nColor)
					{
					case 0:
						col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
						break;
					case 1:
						col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
						break;
					case 2:
						col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
						break;
					case 3:
						col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
						break;
					case 4:
						col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
						break;
					case 5:
						col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
						break;
					default:
						break;
					}

					//弾の生成
					CBalloonBullet* pBullet = CBalloonBullet::Create(D3DXVECTOR3(PlayerPos.x, -15.0f, 0.0f), move, col);
				}

				m_nPhase++;				//攻撃数のカウンターをインクリメントする

				if (m_nPhase >= 15)
				{//15回この攻撃をしたら

					m_nPhase = 0;				//攻撃カウンターを0に戻す
					m_state = state_Hide;		//隠す状態に戻す
				}
			}
		}
	}

	break;

	case state_LaughAnim:

	{//笑うアニメーション

		m_nCntMove++;			//移動カウンターをインクリメントする

		if (m_nCntMove % 8 == 0)
		{//8フレームごとテクスチャパターンを更新する

			if (GetPresentAnimPattern() == 1)
			{
				SetAnimPattern(2);
			}
			else if (GetPresentAnimPattern() == 2)
			{
				SetAnimPattern(1);
			}
		}

		if (m_nCntMove >= 91)
		{//90フレームが経ったら

			SetAnimPattern(0);			//アニメションパターンを0に戻す
			m_nCntMove = 0;				//移動カウンターを0に戻す

			int nSelect = random(3, 7);	//ランダムで次の攻撃を設定する

			switch (nSelect)
			{
			case state_BouncingBall:

				//弾型の攻撃
				SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				m_state = state_BouncingBall;

				break;

			case state_Star:

				//星型の攻撃
				SetMove(D3DXVECTOR3(-8.0f, 0.0f, 0.0f));
				m_state = state_Star;

				break;

			case state_LaughAttack:

				//笑う攻撃
				SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				SetAnimPattern(1);
				m_state = state_LaughAttack;

				break;

			case state_CreateEnemy:

				//敵の召喚
				SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				m_state = state_CreateEnemy;

				break;

			case state_Balloon:

				//風船攻撃
				SetMove(D3DXVECTOR3(0.0f, -2.0f, 0.0f));
				m_state = state_Balloon;

				break;
			}
		}
	}

	break;

	case state_Death:

	{//死亡状態

		if (m_nPhase == 0)
		{//少しずつ小さくしながら、画面の下側に移動させる

			m_nCntMove++;			//移動カウンターをインクリメントする

			if (m_nCntMove % 30 < 20)
			{
				//サイズを小さくする
				D3DXVECTOR2 size = GetSize();
				size.x -= 0.5f;
				size.y -= 0.5f;
				SetSize(size);
			}
			if (m_nCntMove >= 92)
			{
				//回転させて、上側向きの加速を設定する
				m_nPhase++;
				m_nCntMove = 0;
				SetAcceleration(D3DXVECTOR3(0.0f, -0.5f, 0.0f));
				SetRotation(D3DX_PI * 0.2f);
			}
		}
		else
		{
			D3DXVECTOR3 pos = GetPos();				//位置の取得
			pos.x += 3.0f * sinf(m_fAngleMove);		//左右移動を追加する
			SetPos(pos);							//位置を設定する
			m_fAngleMove += D3DX_PI * 0.05f;		//左右移動用の角度を更新する

			if (pos.y <= -200.0f)
			{//画面を出たら、終わったことにする

				m_bEnd = true;
			}
		}
	}

	break;

	default:

		break;
	}
}
