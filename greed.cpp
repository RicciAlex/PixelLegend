//=============================================================================
//
// greed.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "greed.h"
#include "circleHitbox.h"
#include "squareHitbox.h"
#include "greedBullet.h"
#include "player.h"
#include "towerJewel.h"
#include "enemyLife.h"
#include "application.h"
#include "sound.h"

//=============================================================================
//							静的変数の初期化
//=============================================================================

//目的の位置の初期化処理
const D3DXVECTOR3 CGreed::TargetPos[nTargetNum] = 
{
	D3DXVECTOR3(150.0f, 150.0f, 0.0f),
	D3DXVECTOR3((float)SCREEN_WIDTH - 150.0f, 150.0f, 0.0f),
	D3DXVECTOR3(150.0f, (float)SCREEN_HEIGHT - 150.0f, 0.0f),
	D3DXVECTOR3((float)SCREEN_WIDTH - 150.0f, (float)SCREEN_HEIGHT - 150.0f, 0.0f),
	D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f)
};

//コンストラクタ
CGreed::CGreed()
{
	//メンバー変数をクリアする
	m_bEnd = false;
	m_fSumAngle = 0.0f;
	m_fShotAngle = 0.0f;
	m_targetIdx = 0;
	m_nAnimCnt = 0;
	m_nTowerDelay = 0;
	m_state = state_spawn;

	m_HitboxUpRelativePos   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_HitboxDownRelativePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_pHitboxUp = nullptr;
	m_pHitboxDown = nullptr;
	m_pLife = nullptr;

	for (int nCnt = 0; nCnt < MaxTower; nCnt++)
	{
		m_pTower[nCnt] = nullptr;
	}
}

//デストラクタ
CGreed::~CGreed()
{

}

//初期化処理
HRESULT CGreed::Init(void)
{
	if (FAILED(CEnemy::Init()))
	{//基本クラスの初期化処理
		return -1;
	}

	//メンバー変数を初期化する
	m_bEnd = false;
	m_fSumAngle = 0.22f;
	m_fShotAngle = 0.0f;
	m_targetIdx = 0;
	m_nAnimCnt = 0;
	m_nTowerDelay = 0;
	m_state = state_spawn;

	m_HitboxUpRelativePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_HitboxDownRelativePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_pHitboxUp = nullptr;
	m_pHitboxDown = nullptr;
	m_pLife = nullptr;

	for (int nCnt = 0; nCnt < MaxTower; nCnt++)
	{
		m_pTower[nCnt] = nullptr;
	}

	return S_OK;
}

//終了処理
void CGreed::Uninit(void)
{
	//体の上側のヒットボックスの破棄処理
	if (m_pHitboxUp != nullptr)
	{//nullチェック
		m_pHitboxUp->Release();				//メモリを解放する
		m_pHitboxUp = nullptr;				//ポインタをnullにする
	}

	//体の下側のヒットボックスの破棄処理
	if (m_pHitboxDown != nullptr)
	{//nullチェック	 
		m_pHitboxDown->Release();			//メモリを解放する
		m_pHitboxDown = nullptr;			//ポインタをnullにする
	}

	//左右の敵の破棄処理
	for (int nCnt = 0; nCnt < MaxTower; nCnt++)
	{
		if (m_pTower[nCnt])
		{//nullチェック
			m_pTower[nCnt]->Release();		//メモリを解放する
			m_pTower[nCnt] = nullptr;		//ポインタをnullにする
		}
	}

	//体力UIの破棄処理
	if (m_pLife != nullptr)
	{//nullチェック
		m_pLife->Release();					//メモリを解放する
		m_pLife = nullptr;					//ポインタをnullにする
	}

	//基本クラスの終了処理
	CEnemy::Uninit();
}

//更新処理
void CGreed::Update(void)
{
	D3DXVECTOR3 pos = GetPos();			//位置の取得

	//体の上側のヒットボックスの更新
	if (m_pHitboxUp != nullptr)
	{//nullチェック

		m_pHitboxUp->SetPos(GetPos() + m_HitboxUpRelativePos);		//ヒットボックスの位置の更新

		if (m_pHitboxUp->GetHitState())
		{//当たった状態だったら

			m_pHitboxUp->SetHitState(false);		//体の上側のヒットボックスを当っていない状態に戻す
			m_pHitboxDown->SetHitState(false);		//体の下側のヒットボックスを当っていない状態に戻す

			int nLife = GetLife();								//体力の取得
			int nDamage = CPlayer::GetPlayer()->GetAttack();	//プレイヤーの攻撃力の取得
			nLife -= nDamage;									//体力を更新する

			if (nLife <= 0)
			{//体力が0以下になったら
				m_state = state_death;			//死亡状態にする
				nLife = 0;
				SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

				//ヒットボックスを破棄する
				m_pHitboxUp->Release();
				m_pHitboxUp = nullptr;

				if (m_pHitboxDown)
				{
					m_pHitboxDown->Release();
					m_pHitboxDown = nullptr;
				}
			}
			else
			{//体力が0以下ではなかったら

				SetLife(nLife);					//体力の設定

				//1～2の弾の生成
				for (int nCnt = 0; nCnt < random(1, 2); nCnt++)
				{
					//初期化の時の速度は上向きで、下向きの速度がある
					D3DXVECTOR3 move = D3DXVECTOR3((float)random(-500, 500) * 0.01f, (float)random(400, 800) * -0.01f, 0.0f);

					//弾の生成
					CGreedBullet::Create(pos, move, D3DXVECTOR3(0.0f, 0.05f, 0.0f));

					//サウンドを再生する
					CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_COIN);
				}
			}

			//体力のUIの更新
			if (m_pLife != nullptr)
			{//nullチェック
				m_pLife->SubtractLife(nDamage);
			}
		}
	}
	//体の下側のヒットボックスの更新
	if (m_pHitboxDown != nullptr)
	{//nullチェック
		m_pHitboxDown->SetPos(GetPos() + m_HitboxDownRelativePos);	//ヒットボックスの位置の更新

		if (m_pHitboxDown->GetHitState())
		{//当たった状態だったら
			m_pHitboxDown->SetHitState(false);				//体の下側のヒットボックスを当っていない状態に戻す

			int nLife = GetLife();								//体力の取得
			int nDamage = CPlayer::GetPlayer()->GetAttack();	//プレイヤーの攻撃力の取得
			nLife -= nDamage;									//体力を更新する

			if (nLife <= 0)
			{//体力が0以下になったら
				m_state = state_death;
				nLife = 0;
				SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

				//ヒットボックスを破棄する
				m_pHitboxDown->Release();
				m_pHitboxDown = nullptr;

				if (m_pHitboxUp)
				{
					m_pHitboxUp->Release();
					m_pHitboxUp = nullptr;
				}
			}
			else
			{//体力が0以下ではなかったら

				SetLife(nLife);			//体力の設定

				//1～3の弾の生成
				for (int nCnt = 0; nCnt < random(1, 3); nCnt++)
				{
					//初期化の時の速度は上向きで、下向きの速度がある
					D3DXVECTOR3 move = D3DXVECTOR3((float)random(-500, 500) * 0.01f, (float)random(400, 800) * -0.01f, 0.0f);

					//弾の生成
					CGreedBullet::Create(pos, move, D3DXVECTOR3(0.0f, 0.05f, 0.0f));

					//サウンドを再生する
					CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_COIN);
				}
			}

			//体力のUIの更新
			if (m_pLife != nullptr)
			{//nullチェック
				m_pLife->SubtractLife(nDamage);
			}
		}
	}

	UpdateState();

	if (m_state != state_spawn && m_state != state_death && GetLife() < 15000)
	{
		m_nTowerDelay++;

		if (m_nTowerDelay >= 600)
		{
			m_nTowerDelay = 0;

			int nIdx = random(0, 1);

			if (m_pTower[nIdx] != nullptr)
			{
				D3DXVECTOR3 Tpos = m_pTower[nIdx]->GetPos();
				Tpos.y = CPlayer::GetPlayer()->GetPos().y;

				m_pTower[nIdx]->SetPos(Tpos);
				m_pTower[nIdx]->SetState(CTowerJewel::state_spawn);
			}
		}
	}

	//基本クラスの更新処理
	CObject_2D::Update();
}

//描画処理
void CGreed::Draw(void)
{
	CObject_2D::Draw();
}

const bool CGreed::GetEnd(void)
{
	return m_bEnd;
}




//生成処理
CGreed* CGreed::Create(void)
{
	CGreed* pEnemy = new CGreed;

	if (FAILED(pEnemy->Init()))
	{
		return nullptr;
	}

	D3DXVECTOR3 pos = D3DXVECTOR3(800.0f, 500.0f, 0.0f);
	pEnemy->m_HitboxUpRelativePos = D3DXVECTOR3(0.0f, -30.0f, 0.0f);
	pEnemy->m_HitboxDownRelativePos = D3DXVECTOR3(0.0f, 75.0f, 0.0f);

	pEnemy->SetPos(D3DXVECTOR3(1400.0f, 350.0f, 0.0f));
	pEnemy->SetMove(D3DXVECTOR3(-1.0f, 0.0f, 0.0f));
	pEnemy->SetSize(D3DXVECTOR2(175.0f, 131.6f));
	pEnemy->SetStartingRot(D3DX_PI * 0.5f);
	pEnemy->SetTexture(CObject::TextureGreed);
	pEnemy->SetTextureParameter(1, 1, 2, INT_MAX);
	pEnemy->SetAnimPattern(1);
	pEnemy->SetLife(20000);

	pEnemy->m_pHitboxUp = CCircleHitbox::Create(pos + pEnemy->m_HitboxUpRelativePos, 95.0f, CHitbox::Type_Enemy);
	pEnemy->m_pHitboxDown = CSquareHitbox::Create(pos + pEnemy->m_HitboxDownRelativePos, D3DXVECTOR2(130.0f, 40.0f), CHitbox::Type_Enemy);
	pEnemy->SetMaxSpeed(2.0f);

	pEnemy->m_pTower[0] = CTowerJewel::Create(D3DXVECTOR3(-100.0f, 0.0f, 0.0f));

	if (pEnemy->m_pTower[0] != nullptr)
	{
		pEnemy->m_pTower[0]->SetStartingRot(0.0f);
	}

	pEnemy->m_pTower[1] = CTowerJewel::Create(D3DXVECTOR3((float)SCREEN_WIDTH + 100.0f, 0.0f, 0.0f));

	if (pEnemy->m_pTower[1])
	{
		pEnemy->m_pTower[1]->SetStartingRot(D3DX_PI);
	}

	pEnemy->m_pLife = CEnemyLife::Create(D3DXVECTOR3(900.0f, 40.0f, 0.0f), D3DXCOLOR(0.0f, 0.4f, 1.0f, 0.5f), 20000, "greed");

	return pEnemy;
}

//状態によっての更新処理
void CGreed::UpdateState(void)
{
	D3DXVECTOR3 pos = GetPos();			//位置の取得

	switch (m_state)
	{
	case CGreed::state_spawn:

	{//スポーン状態

		m_nAnimCnt++;				//アニメーション用のカウンターをインクリメントする

		if (m_nAnimCnt >= 30)
		{//30フレームが経ったら
			m_nAnimCnt = 0;										//アニメーション用のカウンターを0に戻す
			SetAnimPattern(GetPresentAnimPattern() ^ 1);		//アニメションパターンを更新する
		}

		if (pos.x <= 1000.0f)
		{//決まった位置に着いたら

			m_nAnimCnt = 0;								//アニメーション用のカウンターを0に戻す
			SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//速度の設定
			SetAnimPattern(0);							//アニメションパターンを0に戻す
			m_state = state_normal;						//普通の状態に戻す
		}

		//アニメションパターンによって大きさが違うので、ヒットボックスのサイズを更新する
		if (GetPresentAnimPattern() == 0)
		{
			m_HitboxUpRelativePos = D3DXVECTOR3(0.0f, 5.0f, 0.0f);			//体の上側のヒットボックスの相対位置を設定する
			m_HitboxDownRelativePos = D3DXVECTOR3(0.0f, 85.0f, 0.0f);		//体の下側のヒットボックスの相対位置を設定する
			m_pHitboxUp->SetRadius(100.0f);									//体の上側のヒットボックスの半径を設定する
			m_pHitboxDown->SetSize(D3DXVECTOR2(170.0f, 30.0f));				//体の下側のヒットボックスのサイズを設定する
		}
		else
		{
			m_HitboxUpRelativePos = D3DXVECTOR3(0.0f, -30.0f, 0.0f);		//体の上側のヒットボックスの相対位置を設定する
			m_HitboxDownRelativePos = D3DXVECTOR3(0.0f, 75.0f, 0.0f);		//体の下側のヒットボックスの相対位置を設定する
			m_pHitboxUp->SetRadius(95.0f);									//体の上側のヒットボックスの半径を設定する
			m_pHitboxDown->SetSize(D3DXVECTOR2(130.0f, 40.0f));				//体の下側のヒットボックスのサイズを設定する
		}
	}

	break;

	case CGreed::state_normal:

	{//普通の状態

		//=========================================================
		//				怒り攻撃をするかどうか
		//		体力によって0%から20%と40%になります
		int k = 0;

		if (GetLife() < 15000)
		{
			k = 2;
			SetMaxSpeed(4.5f);
		}
		else if (GetLife() < 10000)
		{
			k = 4;
			SetMaxSpeed(7.5f);
		}

		if (random(1, 100) > 100 - (k * 10))
		{
			SetAnimPattern(0);
			m_state = state_rage;
			break;
		}
		//==========================================================

		while (true)
		{//次の目的の位置の設定

			int nRand = random(0, 4);

			D3DXVECTOR3 L = TargetPos[nRand] - pos;			//この敵と目的の位置の距離を計算する

			if (D3DXVec3Length(&L) > 20.0f)
			{//距離が20.0f以上だったら、目的の位置へ移動させる

				D3DXVECTOR3 move;
				D3DXVec3Normalize(&move, &L);
				move.x *= GetMaxSpeed();
				move.y *= GetMaxSpeed();
				SetMove(move);
				m_targetIdx = nRand;
				m_state = state_walk;

				if (move.x > 0 && !GetFlipX() || move.x < 0 && GetFlipX())
				{//向きと速度の向きを比べて、必要だったら、テクスチャを反転する
					FlipX();
				}

				break;
			}
		}
	}

	break;

	case CGreed::state_walk:

	{//移動状態

		m_nAnimCnt++;				//アニメーション用のカウンターをインクリメントする
		
		if (m_nAnimCnt >= 30)
		{//30フレームごとアニメションパターンを更新する
			m_nAnimCnt = 0;
			SetAnimPattern(GetPresentAnimPattern() ^ 1);
		}

		D3DXVECTOR3 L = TargetPos[m_targetIdx] - pos;			//目的の位置までの距離を計算する

		if (D3DXVec3Length(&L) < 10.0f)
		{//10.0f以下だったら
			m_nAnimCnt = 0;								//アニメーション用のカウンターを0に戻す
			SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//速度を設定する
			SetAnimPattern(0);							//アニメーションパターンの設定
			m_state = state_shot;						//攻撃状態にする
		}

		//アニメションパターンによって大きさが違うので、ヒットボックスのサイズを更新する
		if (GetPresentAnimPattern() == 0)
		{
			m_HitboxUpRelativePos = D3DXVECTOR3(0.0f, 5.0f, 0.0f);			//体の上側のヒットボックスの相対位置を設定する
			m_HitboxDownRelativePos = D3DXVECTOR3(0.0f, 85.0f, 0.0f);		//体の下側のヒットボックスの相対位置を設定する
			m_pHitboxUp->SetRadius(100.0f);									//体の上側のヒットボックスの半径を設定する
			m_pHitboxDown->SetSize(D3DXVECTOR2(170.0f, 30.0f));				//体の下側のヒットボックスのサイズを設定する
		}
		else
		{
			m_HitboxUpRelativePos = D3DXVECTOR3(0.0f, -30.0f, 0.0f);		//体の上側のヒットボックスの相対位置を設定する
			m_HitboxDownRelativePos = D3DXVECTOR3(0.0f, 75.0f, 0.0f);		//体の下側のヒットボックスの相対位置を設定する
			m_pHitboxUp->SetRadius(95.0f);									//体の上側のヒットボックスの半径を設定する
			m_pHitboxDown->SetSize(D3DXVECTOR2(130.0f, 40.0f));				//体の下側のヒットボックスのサイズを設定する
		}
	}

	break;

	case CGreed::state_shot:

	{//攻撃状態

		D3DXVECTOR3 PlayerPos = CPlayer::GetPlayer()->GetPos();			//プレイヤーの位置の取得

		if (PlayerPos.x > pos.x && !GetFlipX() || PlayerPos.x < pos.x && GetFlipX())
		{//プレイヤーの位置までのベクトルと向きを比べて、必要だったら、テクスチャを反転する
			FlipX();
		}

		int nLife = GetLife();				//体力の取得

		m_nShootDelay++;					//攻撃カウンターをインクリメントする

		//アニメーションしながら、攻撃する
		if (m_nShootDelay % 30 == 13)
		{
			SetAnimPattern(1);			//アニメーションパターンの設定
		}
		else if (m_nShootDelay % 30 == 28)
		{
			SetAnimPattern(0);			//アニメーションパターンの設定

			//プレイヤーまでのベクトルを計算して、正規化する
			D3DXVECTOR3 move = PlayerPos - pos;	
			D3DXVec3Normalize(&move, &move);

			//弾を生成する
			CGreedBullet::Create(pos, D3DXVECTOR3(3.5f * move.x, 3.5f * move.y, 0.0f));

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_COIN);			//サウンドを再生する

			if (nLife < 15000)
			{//体力が15000以下になったら

				//=================================================================================================================
				//プレイヤーまでのベクトル±30°向きの弾の生成
				D3DXVECTOR3 unit = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

				float fAngle = acosf(D3DXVec3Dot(&move, &unit));

				if (PlayerPos.y < pos.y)
				{
					fAngle *= -1.0f;
				}

				D3DXVECTOR3 NewMove = D3DXVECTOR3(cosf(fAngle) * cosf(D3DX_PI / 6.0f) - sinf(fAngle) * sinf(D3DX_PI / 6.0f),
					sinf(fAngle) * cosf(D3DX_PI / 6.0f) + cosf(fAngle) * sinf(D3DX_PI / 6.0f), 0.0f);

				CGreedBullet::Create(pos, D3DXVECTOR3(3.5f * NewMove.x, 3.5f * NewMove.y, 0.0f));

				NewMove = D3DXVECTOR3(cosf(fAngle) * cosf(-D3DX_PI / 6.0f) - sinf(fAngle) * sinf(-D3DX_PI / 6.0f),
					sinf(fAngle) * cosf(-D3DX_PI / 6.0f) + cosf(fAngle) * sinf(-D3DX_PI / 6.0f), 0.0f);

				CGreedBullet::Create(pos, D3DXVECTOR3(3.5f * NewMove.x, 3.5f * NewMove.y, 0.0f));
				//==================================================================================================================

				if (nLife < 10000)
				{//体力が15000以下になったら

					//=================================================================================================================
					//プレイヤーまでのベクトル±60°向きの弾の生成
					NewMove = D3DXVECTOR3(cosf(fAngle) * cosf(D3DX_PI / 3.0f) - sinf(fAngle) * sinf(D3DX_PI / 3.0f),
						sinf(fAngle) * cosf(D3DX_PI / 3.0f) + cosf(fAngle) * sinf(D3DX_PI / 3.0f), 0.0f);

					CGreedBullet::Create(pos, D3DXVECTOR3(3.5f * NewMove.x, 3.5f * NewMove.y, 0.0f));

					NewMove = D3DXVECTOR3(cosf(fAngle) * cosf(-D3DX_PI / 3.0f) - sinf(fAngle) * sinf(-D3DX_PI / 3.0f),
						sinf(fAngle) * cosf(-D3DX_PI / 3.0f) + cosf(fAngle) * sinf(-D3DX_PI / 3.0f), 0.0f);

					CGreedBullet::Create(pos, D3DXVECTOR3(3.5f * NewMove.x, 3.5f * NewMove.y, 0.0f));
					//==================================================================================================================
				}
			}
		}
		else if (m_nShootDelay > 350)
		{//350フレームが経ったら
			m_nShootDelay = 0;			//攻撃カウンターを0に戻す
			m_state = state_normal;		//普通の状態に戻す
		}
	}

	break;

	case CGreed::state_rage:

	{//怒り攻撃

		m_nShootDelay++;		//攻撃カウンターをインクリメントする
		m_nCntMove++;			//移動カウンターをインクリメントする

		if (m_nCntMove < 100)
		{//100フレームまで色を変えるだけ

			if (m_nCntMove % 20 == 19)
			{//普通の色に設定する
				SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else if (m_nCntMove % 10 == 9)
			{//赤くする
				SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			}
		}
		else
		{//100フレームが経ったら

			SetAnimPattern(1);								//アニメーションパターンの設定
			SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	//普通の色の設定

			if (m_nShootDelay >= 10)
			{//10フレームごと

				m_nShootDelay = 0;			//攻撃カウンターを0に戻す

				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_COIN);		//サウンドを再生する

				for (int nCnt = 0; nCnt < 8; nCnt++)
				{//この敵の周りに８つの弾の生成
					CGreedBullet::Create(pos, D3DXVECTOR3(5.0f * cosf(m_fShotAngle + (nCnt * D3DX_PI / 4.0f)), 5.0f * sinf(m_fShotAngle + (nCnt * D3DX_PI / 4.0f)), 0.0f));
				}

				m_fShotAngle += m_fSumAngle;			//攻撃用の角度の更新

				if (m_fShotAngle >= 1.0f || m_fShotAngle <= -1.0f)
				{//決まった角度を超えたら、角度を逆にする
					m_fSumAngle *= -1.0f;
				}
			}
		}

		if (m_nCntMove >= 580)
		{//580フレームが経ったら

			m_nShootDelay = 0;			//攻撃カウンターを0に戻す
			m_nCntMove = 0;				//移動カウンターを0に戻す
			m_fShotAngle = 0.0f;		//攻撃角度を0に戻す
			m_state = state_normal;		//普通の状態に戻す
		}
	}

	break;

	case CGreed::state_death:

	{//死亡状態

		m_nShootDelay++;			//攻撃カウンターをインクリメントする

		if (m_nShootDelay % 20 == 1)
		{//20フレームごと色を更新する

			D3DXCOLOR col = GetColor();

			if (col.g <= 0.5f)
			{//普通の色に設定する
				SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, col.a));
			}
			else
			{//赤くする
				SetColor(D3DXCOLOR(1.0f, 0.2f, 0.2f, col.a));
			}
		}

		//30個弾の生成
		if (m_nShootDelay == 130)
		{
			for (int nCnt = 0; nCnt < 30; nCnt++)
			{
				//弾の速度を計算する
				D3DXVECTOR3 move = D3DXVECTOR3((float)random(-500, 500) * 0.01f, (float)random(-500, 500) * -0.01f, 0.0f);

				//弾の生成
				CGreedBullet::Create(pos, move);

				//大きい爆発のサウンドを再生する
				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_BIG_EXPLOSION);
			}
		}

		if (m_nShootDelay == 300)
		{//300フレームが経ったら、終わった状態にする
			m_bEnd = true;
		}
	}

	break;

	default:
		break;
	}
}
