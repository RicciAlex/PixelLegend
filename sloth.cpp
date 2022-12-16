//=============================================================================
//
// sloth.cpp
// Author : Ricci Alex
//
//=============================================================================

//インクルードファイル
#include "sloth.h"
#include "application.h"
#include "sound.h"
#include "tear.h"
#include "enemyCloud.h"
#include "Zbullet.h"
#include "player.h"
#include "squareHitbox.h"
#include "enemyLife.h"

//コンストラクタ
CSloth::CSloth()
{
	//メンバー変数をクリアする
	m_bEnd = false;
	m_nCntState = 0;
	m_fYCoord = 0.0f;
	m_state = state_Spawn;
	m_nCntDmg = 0;
	m_nCntSpawn = 0;
	m_nCntSound = 0;
	m_nSoundDelay = 0;
	m_nChange = 0;
	m_nCntAnim = 0;
	m_HitboxRelativePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pHitbox = nullptr;
	m_pLife = nullptr;
}

//デストラクタ
CSloth::~CSloth()
{

}

//初期化処理
HRESULT CSloth::Init(void)
{
	//基本クラスの初期化
	if (FAILED(CEnemy::Init()))
	{
		return -1;
	}

	//メンバー変数の初期化
	m_bEnd = false;
	SetLife(20000);
	m_state = state_Spawn;
	m_nCntState = 30;
	m_nCntDmg = 0;
	m_nCntSpawn = 0;
	m_nCntSound = 0;
	m_nSoundDelay = 0;
	m_nChange = 0;
	m_nCntAnim = 0;
	m_HitboxRelativePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pHitbox = nullptr;
	m_pLife = nullptr;

	return S_OK;
}

//終了処理
void CSloth::Uninit(void)
{
	//ヒットボックスの破棄処理
	if (m_pHitbox != nullptr)
	{//nullチェック
		m_pHitbox->Release();			//メモリを解放する
		m_pHitbox = nullptr;			//nullにする
	}

	//体力UIの破棄処理
	if (m_pLife != nullptr)
	{//nullチェック
		m_pLife->Release();				//メモリを解放する
		m_pLife = nullptr;				//nullにする
	}

	//基本クラスの終了処理
	CEnemy::Uninit();
}

//更新処理
void CSloth::Update(void)
{
	SlothBehavior();					//更新処理

	//ヒットボックスの更新処理
	if (m_pHitbox != nullptr)
	{//nullチェック

		m_pHitbox->SetPos(GetPos() + m_HitboxRelativePos);		//ヒットボックスの位置の設定

		if (m_nCntDmg <= 0)
		{//無敵状態ではなかったら

			if (m_pHitbox->GetHitState())
			{//当たった状態だったら

				m_pHitbox->SetHitState(false);						//当っていない状態に戻す
				int nLife = GetLife();								//体力の取得
				int nDamage = CPlayer::GetPlayer()->GetAttack();	//プレイヤーの攻撃力の取得
				nLife -= nDamage;									//体力の更新
				m_nCntDmg = 20;										//無敵状態カウンターを設定する

				if (nLife <= 0)
				{//体力が0以下になったら

					SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));	//速度の設定
					m_nSoundDelay = 45;						//サウンドディレイの更新
					m_state = state_Death;					//状態の更新
					m_pHitbox->Release();					//ヒットボックスの破棄
					m_pHitbox = nullptr;					//ヒットボックスへのポインタをnullにする
					m_nChange++;							//カウンターをインクリメントする
					SetAnimPattern(14);						//アニメションパターンの設定
					return;
				}

				if (nLife <= 15000 && m_nChange == 0)
				{//体力が15000以下7500より小さかったら、灰色テクスチャのアニメションパターンに設定する

					SetTextureParameter(1, 6, 3, INT_MAX);		//テクスチャパラメータの設定
					SetAnimPattern(6);							//アニメションパターンの設定
					m_nChange++;								//カウンターをインクリメントする

					CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_THUNDER);			//雷のサウンドを再生する
				}
				else if (nLife <= 7500 && m_nChange == 1)
				{//体力が7500以下だったら、黒いテクスチャのアニメションパターンに設定する

					SetAnimPattern(12);				//アニメションパターンの設定
					m_nChange++;					//カウンターをインクリメントする

					CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_THUNDER);			//雷のサウンドを再生する
				}

				//体力UIの更新
				if (m_pLife != nullptr)
				{//nullチェック
					m_pLife->SubtractLife(nDamage);			//UIの更新
				}

				SetLife(nLife);				//体力の更新
			}
		}
		else
		{
			m_nCntDmg--;					//無敵状態カウンターをデクリメントする
		}
	}

	if (m_nChange == 1)
	{
		m_nCntAnim++;			//アニメーションカウンターの更新

		if (m_nCntAnim >= 30)
		{//30フレームごとテクスチャを更新する

			m_nCntAnim = 0;		//アニメーションカウンターを0に戻す
			
			if (GetPresentAnimPattern() == 6)
			{
				SetAnimPattern(7);
			}
			else
			{
				SetAnimPattern(6);
			}
		}
	}
	else if (m_nChange == 2)
	{
		m_nCntAnim++;			//アニメーションカウンターの更新

		if (m_nCntAnim >= 30)
		{//30フレームごとテクスチャを更新する

			m_nCntAnim = 0;		//アニメーションカウンターを0に戻す

			if (GetPresentAnimPattern() == 12)
			{
				SetAnimPattern(13);
			}
			else
			{
				SetAnimPattern(12);
			}
		}
	}
	else if (m_nChange == 3)
	{
		m_nCntAnim++;			//アニメーションカウンターの更新

		if (m_nCntAnim >= 30)
		{//30フレームごとテクスチャを更新する

			m_nCntAnim = 0;		//アニメーションカウンターを0に戻す

			if (GetPresentAnimPattern() == 14)
			{
				SetAnimPattern(15);
			}
			else
			{
				SetAnimPattern(14);
			}
		}
	}

	CObject_2D::Update();				//基本クラスの更新処理
}

//描画処理
void CSloth::Draw(void)
{
	//基本クラスの描画処理
	CEnemy::Draw();
}

//終わったかどうかの取得処理
const bool CSloth::GetEnd(void)
{
	return m_bEnd;
}


//==================================================================================================
//										静的関数
//==================================================================================================

//生成処理
CSloth* CSloth::Create(void)
{
	CSloth* pBoss = new CSloth;					//メモリを確保する

	//初期化処理
	if (FAILED(pBoss->Init()))
	{
		return nullptr;
	}

	pBoss->SetPos(D3DXVECTOR3((float)SCREEN_WIDTH * 0.75f, (float)SCREEN_HEIGHT * 0.25f, 0.0f));	//位置の設定
	pBoss->SetSize(D3DXVECTOR2(180.0f, 104.0f));													//サイズの設定
	pBoss->SetStartingRot(D3DX_PI * 0.5f);															//回転角度の設定
	pBoss->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));													//速度の設定
	pBoss->m_fYCoord = pBoss->GetPos().y;															//Y座標を保存する
	pBoss->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));												//色の設定
																									
	pBoss->SetTexture(CObject::TextureSloth);														//テクスチャの設定
	pBoss->SetTextureParameter(2, 6, 3, 30);														//テクスチャパラメータの設定

	D3DXVECTOR3 pos = pBoss->GetPos();

	pBoss->m_HitboxRelativePos = D3DXVECTOR3(30.0f, 0.0f, 0.0f);			//相対位置の設定

	//ヒットボックスの生成
	pBoss->m_pHitbox = CSquareHitbox::Create(D3DXVECTOR3(pos.x + pBoss->m_HitboxRelativePos.x, pos.y, 0.0f), D3DXVECTOR2(100.0f, 80.0f), CHitbox::Type_Enemy);

	//体力UIの生成
	pBoss->m_pLife = CEnemyLife::Create(D3DXVECTOR3(900.0f, 40.0f, 0.0f), D3DXCOLOR(0.0f, 0.4f, 1.0f, 0.5f), 20000, "sloth");

	return pBoss;								//敵を返す
}



//==================================================================================================
//										プライベート関数 
//==================================================================================================

//更新処理
void CSloth::SlothBehavior(void)
{
	switch (m_state)
	{//状態によっての更新処理

	case CSloth::state_Spawn:

	{//スポーン状態

		D3DXCOLOR col = GetColor();				//色の取得

		col.a += 0.005f;						//α値の更新

		if (col.a >= 1.0f)
		{//α値が1.0f以上になったら

			col.a = 1.0f;						//1.0fに戻す
			m_state = state_Normal;				//普通の状態にする
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_GOAT);		//サウンドを再生する
		}

		SetColor(col);				//色の設定
	}

	break;

	case CSloth::state_Normal:
		
		//普通の状態
		
		if (m_nCntState > 0)
		{//カウンターが0以上だったら

			m_nCntState--;				//状態カウンターをデクリメントする

			if (m_nCntState <= 0)
			{//状態カウンターが0以下になったら
				m_nCntState = 0;				//0に戻す
			}

			int nState = random(300, 799);		//ランダムで数値を選ぶ

			nState /= 100;			//100で割る

			switch (nState)
			{//上の計算の結果によって次の攻撃を選択する

			case state_Charge:

				m_state = state_Charge;			//体当たり攻撃にする

				m_nSoundDelay = 120;			//サウンドディレイの設定

				SetMove(D3DXVECTOR3(-5.0f, 0.0f, 0.0f));	//速度の設定

				break;

			case state_Snore:

				m_state = state_Snore;			//いびき攻撃にする

				SetMove(D3DXVECTOR3(-2.0f, 0.0f, 0.0f));	//速度の設定

				m_nSoundDelay = 150;			//サウンドディレイの設定

				break;

			case state_Weep:

				m_state = state_Weep;			//泣く攻撃(1)攻撃にする

				SetMove(D3DXVECTOR3(-4.0f, 0.0f, 0.0f));	//速度の設定

				m_nSoundDelay = 60;				//サウンドディレイの設定

				break;

			case state_Cry:

				m_state = state_Cry;			//泣く攻撃(2)攻撃にする

				SetMove(D3DXVECTOR3(-4.0f, 0.0f, 0.0f));	//速度の設定

				m_nSoundDelay = 60;				//サウンドディレイの設定

				break;

			case state_Summon:

				m_state = state_Summon;			//召喚状態にする

				SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//速度の設定

				m_nSoundDelay = 240;			//サウンドディレイの設定

				break;


			default:
				break;
			}
		}

		break;

	case state_Return:

	{//戻る状態だったら

		D3DXVECTOR3 pos = GetPos();				//位置の取得

		if (pos.x <= (float)SCREEN_WIDTH * 0.75f)
		{//決まった位置に着いたら

			m_nCntState = 30;					//状態カウンターを設定する
			m_state = state_Normal;				//普通の状態に戻す
			m_fYCoord = GetPos().y;				//Y座標の設定
			m_nCntMove = 0;						//移動カウンターを0に戻す
			m_fAngleMove = 0.0f;				//現在のアニメーション角度を0に戻す
		}										
	}

	break;


	case CSloth::state_Charge:

	{//体当たり攻撃

		D3DXVECTOR3 pos = GetPos();					//位置の取得
		D3DXVECTOR3 move = GetMove();				//速度の取得
		m_fAngleMove += D3DX_PI * 0.0125f;			//アニメーション角度の更新

		//位置の更新
		pos.x += move.x;
		pos.y = m_fYCoord + 130.0f * sqrtf(cosf(m_fAngleMove) * cosf(m_fAngleMove));

		if (pos.x <= -1.0f * GetSize().x)
		{//画面の左側から出たら

			pos.x = -1.0f * GetSize().x;				//X座標を設定する
			pos.y = (float)random(150, 570);			//Y座標を設定する
			m_fYCoord = pos.y;							//現在のY座標の設定
			move.x *= -1.0f;							//速度のX座標を逆にする
			FlipX();									//テクスチャを反転する
			m_HitboxRelativePos.x *= -1.0f;				//ヒットボックスの位置を更新する
			m_nPhase++;									//攻撃数をインクリメントする
		}
		else if (pos.x >= (float)SCREEN_WIDTH + GetSize().x)
		{//画面の右側から出たら
			pos.x = (float)SCREEN_WIDTH + GetSize().x;	//X座標を設定する
			pos.y = (float)random(150, 570);			//Y座標を設定する
			m_fYCoord = pos.y;							//現在のY座標の設定
			move.x *= -1.0f;							//速度のX座標を逆にする
			FlipX();									//テクスチャを反転する
			m_HitboxRelativePos.x *= -1.0f;				//ヒットボックスの位置を更新する
			m_nPhase++;									//攻撃数をインクリメントする
		}

		if (m_nPhase >= 4)
		{//4回この攻撃をしたら

			//位置と速度を設定して、画面の右上に戻す
			pos = D3DXVECTOR3((float)SCREEN_WIDTH * 1.25f, (float)SCREEN_HEIGHT * 0.25f, 0.0f);
			move = D3DXVECTOR3(-2.0f, 0.0f, 0.0f);
			m_state = state_Return;
			m_nPhase = 0;
		}

		SetPos(pos);			//位置の設定
		SetMove(move);			//速度の設定
		m_nCntSound++;			//サウンドのカウンターの更新
	}

	break;

	case CSloth::state_Snore:

	{//いびき攻撃

		D3DXVECTOR3 pos = GetPos();			//位置の取得
		D3DXVECTOR3 move = GetMove();		//速度の取得

		pos += move;						//位置の更新

		if (pos.x <= -1.0f * GetSize().x)
		{//画面の左側から出たら
			pos.x = -1.0f * GetSize().x;	//X座標を設定する	
			move.x *= -1.0f;				//Y座標を設定する
			FlipX();						//テクスチャを反転する
			m_HitboxRelativePos.x *= -1.0f;	//ヒットボックスの位置を更新する
			m_nPhase++;						//攻撃数をインクリメントする
		}									
		else if (pos.x >= (float)SCREEN_WIDTH + GetSize().x)
		{//画面の右側から出たら
			pos.x = (float)SCREEN_WIDTH + GetSize().x;		//X座標を設定する	
			move.x *= -1.0f;								//Y座標を設定する
			FlipX();										//テクスチャを反転する
			m_HitboxRelativePos.x *= -1.0f;					//ヒットボックスの位置を更新する
			m_nPhase++;										//攻撃数をインクリメントする
		}

		if (pos.x >= 10.0f && pos.x <= (float)SCREEN_WIDTH - 10.0f)
		{//画面内だったら

			m_nShootDelay++;				//攻撃カウンターをインクリメントする

			if (m_nShootDelay >= 60)
			{//60フレームごと弾を発生する

				//速度を計算する
				D3DXVECTOR3 PlayerPos = CPlayer::GetPlayer()->GetPos();
				D3DXVECTOR3 BulletMove = PlayerPos - pos;
				D3DXVec3Normalize(&BulletMove, &BulletMove);

				{//プレイヤーを狙った弾
					CZBullet* pBullet = CZBullet::Create(pos, D3DXVECTOR3(BulletMove.x * 5.0f, BulletMove.y * 5.0f, 0.0f));
				}

				for (int nCnt = 0; nCnt < 2; nCnt++)
				{//上計算した向きにランダムな方向ベクトルを足して、発生する
					D3DXVECTOR3 dir = D3DXVECTOR3((float)random(-1000, 1000) * 0.001f, (float)random(-1000, 1000) * 0.001f, 0.0f);
					dir += BulletMove;
					D3DXVec3Normalize(&dir, &dir);
					CZBullet* pBullet = CZBullet::Create(pos, D3DXVECTOR3(dir.x * 5.0f, dir.y * 5.0f, 0.0f));
				}

				m_nShootDelay = 0;			//攻撃カウンターを0に戻す
			}
		}

		if (m_nPhase >= 4)
		{//4回この攻撃をしたら、普通の状態に戻す
			pos = D3DXVECTOR3((float)SCREEN_WIDTH * 1.25f, (float)SCREEN_HEIGHT * 0.25f, 0.0f);
			move = D3DXVECTOR3(-2.0f, 0.0f, 0.0f);
			m_state = state_Return;
			m_nPhase = 0;
		}

		SetPos(pos);			//位置の設定
		SetMove(move);			//速度の設定
		m_nCntSound++;			//サウンドのカウンターをインクリメントする
	}

	break;

	case CSloth::state_Weep:

	{//泣く攻撃(1)

		D3DXVECTOR3 pos = GetPos();				//位置の取得
		D3DXVECTOR3 move = GetMove();			//速度の取得

		pos.x += move.x;						//位置の更新

		if (pos.x <= -1.0f * GetSize().x)
		{//画面の左側から出たら
			pos.x = -1.0f * GetSize().x;		//X座標を設定する	
			move.x *= -1.0f;					//Y座標を設定する
			FlipX();							//テクスチャを反転する
			m_HitboxRelativePos.x *= -1.0f;		//ヒットボックスの位置を更新する
			m_nPhase++;							//攻撃数をインクリメントする
		}
		else if (pos.x >= (float)SCREEN_WIDTH + GetSize().x)
		{//画面の右側から出たら
			pos.x = (float)SCREEN_WIDTH + GetSize().x;		//X座標を設定する	
			move.x *= -1.0f;								//Y座標を設定する
			FlipX();										//テクスチャを反転する
			m_HitboxRelativePos.x *= -1.0f;					//ヒットボックスの位置を更新する
			m_nPhase++;										//攻撃数をインクリメントする
		}

		if (pos.x >= 50.0f && pos.x <= (float)SCREEN_WIDTH - 50.0f)
		{//画面内だったら

			m_nShootDelay++;					//攻撃カウンターをインクリメントする

			if (m_nShootDelay >= 10)
			{//10フレームごと弾2つを発生する

				for (int nCnt = 0; nCnt < 2; nCnt++)
				{
					//速度の計算
					int rand = random(0, 1);
					D3DXVECTOR3 dir = D3DXVECTOR3((float)random(5, 30) * 0.1f, (float)random(40, 70) * -0.1f, 0.0f);

					if (rand == 0)
					{
						dir.x *= -1.0f;
					}

					//弾の生成
					CTearBullet* pBullet = CTearBullet::Create(D3DXVECTOR3(pos.x + ((float)abs((int)move.x) / move.x) * 150.0f, pos.y - 50.0f, 0.0f), dir);
				}

				m_nShootDelay = 0;				//攻撃カウンターを0に戻す
			}
		}

		if (m_nPhase >= 4)
		{//4回この攻撃をしたら普通の状態に戻す
			pos = D3DXVECTOR3((float)SCREEN_WIDTH * 1.25f, (float)SCREEN_HEIGHT * 0.25f, 0.0f);
			move = D3DXVECTOR3(-2.0f, 0.0f, 0.0f);
			m_state = state_Return;
			m_nPhase = 0;
		}

		SetPos(pos);			//位置の設定
		SetMove(move);			//速度の設定
		m_nCntSound++;			//サウンドのカウンターをインクリメントする
	}

	break;

	case CSloth::state_Cry:

	{
		D3DXVECTOR3 pos = GetPos();			//位置の取得
		D3DXVECTOR3 move = GetMove();		//速度の取得

		pos.x += move.x;					//位置の更新

		if (pos.x <= -1.0f * GetSize().x)
		{//画面の左側から出たら
			pos.x = -1.0f * GetSize().x;		//X座標を設定する	
			move.x *= -1.0f;					//Y座標を設定する
			FlipX();							//テクスチャを反転する
			m_HitboxRelativePos.x *= -1.0f;		//ヒットボックスの位置を更新する
			m_nPhase++;							//攻撃数をインクリメントする
		}
		else if (pos.x >= (float)SCREEN_WIDTH + GetSize().x)
		{//画面の右側から出たら
			pos.x = (float)SCREEN_WIDTH + GetSize().x;		//X座標を設定する	
			move.x *= -1.0f;								//Y座標を設定する
			FlipX();										//テクスチャを反転する
			m_HitboxRelativePos.x *= -1.0f;					//ヒットボックスの位置を更新する
			m_nPhase++;										//攻撃数をインクリメントする
		}

		if (pos.x >= 50.0f && pos.x <= (float)SCREEN_WIDTH - 50.0f)
		{//画面内だったら

			m_nShootDelay++;			//攻撃カウンターをインクリメントする

			if (m_nShootDelay >= 30)
			{//30フレームごと弾を6つ生成する

				for (int nCnt = 0; nCnt < 6; nCnt++)
				{
					//ランダムで速度を設定する
					int rand = random(0, 1);
					D3DXVECTOR3 dir = D3DXVECTOR3((float)random(5, 30) * 0.1f, (float)random(40, 70) * -0.1f, 0.0f);

					if (rand == 0)
					{
						dir.x *= -1.0f;
					}

					//弾の生成
					CTearBullet* pBullet = CTearBullet::Create(D3DXVECTOR3(pos.x + ((float)abs((int)move.x) / move.x) * 150.0f, pos.y - 50.0f, 0.0f), dir);
				}

				m_nShootDelay = 0;			//攻撃カウンターを0に戻す
			}
		}

		if (m_nPhase >= 4)
		{//4回この攻撃をしたら、普通の状態に戻す
			pos = D3DXVECTOR3((float)SCREEN_WIDTH * 1.25f, (float)SCREEN_HEIGHT * 0.25f, 0.0f);
			move = D3DXVECTOR3(-2.0f, 0.0f, 0.0f);
			m_state = state_Return;
			m_nPhase = 0;
		}

		SetPos(pos);					//位置の設定
		SetMove(move);					//速度の設定
		m_nCntSound++;					//サウンドのカウンターをインクリメントする
	}

	break;

	case CSloth::state_Summon:

	{//召喚

		SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));				//速度の設定
		D3DXVECTOR3 pos = GetPos();							//位置の取得

		//上下の移動の設定
		m_fAngleMove += D3DX_PI * 0.025f;					
		pos.y = m_fYCoord + cosf(m_fAngleMove) * 50.0f;		
			
		m_nShootDelay++;					//攻撃カウンターをインクリメントする

		if (m_nShootDelay % 30 == 29)
		{//30フレームごと敵を召喚する
			CEnemyCloud* pEnemy = CEnemyCloud::Create(pos);			//敵の生成
		}

		if (m_nShootDelay >= 610)
		{//610フレームが経ったら、普通の状態に戻す
			m_state = state_Normal;
		}
		m_nCntSound++;				//サウンドのカウンターをインクリメントする
	}

	break;


	case CSloth::state_Death:

	{//死亡状態

		D3DXCOLOR col = GetColor();			//色の取得
		D3DXVECTOR3 pos = GetPos();			//位置の取得

		if (col.a > 0.0f)
		{//α値が0.0f以上だったら

			m_nCntSound++;					//サウンドのカウンターをインクリメントする
			col.a -= 0.005f;				//α値の更新
			SetColor(col);					//色の設定
			m_nShootDelay++;				//攻撃カウンターをインクリメントする

			if (m_nShootDelay >= 15)
			{//15フレームごと弾6つを生成する

				for (int nCnt = 0; nCnt < 6; nCnt++)
				{
					//ランダムで速度を設定する
					int rand = random(0, 1);
					D3DXVECTOR3 dir = D3DXVECTOR3((float)random(5, 30) * 0.1f, (float)random(40, 70) * -0.1f, 0.0f);

					if (rand == 0)
					{
						dir.x *= -1.0f;
					}

					float fDir = 1.0f;

					if (!GetFlipX())
					{
						fDir = -1.0f;
					}

					//弾の生成
					CTearBullet* pBullet = CTearBullet::Create(D3DXVECTOR3(pos.x + (115.0f * fDir), pos.y - 50.0f, 0.0f), dir);
				}

				m_nShootDelay = 0;				//攻撃カウンターを0に戻す
			}
		}
		else
		{//α値が0.0f以下になったら
			m_bEnd = true;			//死んだ状態にする
		}
	}

	break;

	default:
		break;
	}

	//体力によって小さい敵を生成する
	switch (m_nChange)
	{
	case 1:

	{//体力が15000以下7500より大きかったら

		m_nCntSpawn++;			//スポーンカウンターをインクリメントする

		if (m_nCntSpawn >= 120)
		{//120フレームごと敵一体を生成する

			m_nCntSpawn = 0;		//スポーンカウンターを0に戻す

			CEnemyCloud::Create(GetPos());		//敵の生成
		}
	}

		break;

	case 2:

	{//体力が7500未満だったら

		m_nCntSpawn++;				//スポーンカウンターをインクリメントする

		if (m_nCntSpawn >= 60)
		{//60フレームごと敵一体を生成する

			m_nCntSpawn = 0;		//スポーンカウンターを0に戻す

			CEnemyCloud::Create(GetPos());			//敵の生成
		}
	}

		break;

	default:
		break;
	}

	if (m_nCntSound >= m_nSoundDelay)
	{//サウンドのカウンターが決まったディレイを超えたら

		CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_GOAT);			//サウンドを再生する
		m_nCntSound = 0;				//サウンドのカウンターを0に戻す
	}
}