//=============================================================================
//
// SkullTentacle.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "SkullTentacle.h"
#include "skull.h"
#include "spine.h"
#include "player.h"
#include "rotatingSimpleEffect.h"
#include "beam.h"
#include "skullFireball.h"
#include "ringEffect.h"
#include "application.h"
#include "sound.h"

//一時的
#include "inputKeyboard.h"
#include "heartBullet.h"
#include "starEffect.h"
#include "Letter.h"
#include "tear.h"

//コンストラクタ
CSkullTentacle::CSkullTentacle()
{
	//メンバー変数をクリアする
	m_pSkull = nullptr;
	m_pSpine = nullptr;
	m_nLife = 0;
	m_SkullPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_SkullDir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_state = state_Spawn;
	m_nCntAtk = 0;
	m_nCntDeath = 0;
	m_nCntMove = 0;
	m_fAngleMove = 0.0f;
	m_bDead = false;
}

//デストラクタ
CSkullTentacle::~CSkullTentacle()
{

}

//初期化処理
HRESULT CSkullTentacle::Init(void)
{
	//メンバー変数の初期化
	if (m_pSkull != nullptr)
	{
		m_pSkull->Release();
		m_pSkull = nullptr;
	}
	if (m_pSpine != nullptr)
	{
		m_pSpine->Release();
		m_pSpine = nullptr;
	}

	m_nLife = 0;
	m_SkullPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_SkullDir = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	m_state = state_Spawn;
	m_nCntAtk = 0;
	m_nCntDeath = 0;
	m_nCntMove = 0;
	m_fAngleMove = 0.0f;
	m_bDead = false;

	return S_OK;
}

//終了処理
void CSkullTentacle::Uninit(void)
{
	//頭の破棄処理
	if (m_pSkull != nullptr)
	{//nullチェック
		m_pSkull->Release();		//メモリを解放する
		m_pSkull = nullptr;			//ポインタをnullにする
	}
	//骨の破棄処理
	if (m_pSpine != nullptr)
	{//nullチェック
		m_pSpine->Release();		//メモリを解放する
		m_pSpine = nullptr;			//ポインタをnullにする
	}
}

//更新処理
void CSkullTentacle::Update(void)
{
	if (!m_bDead)
	{//死んでいない場合

		D3DXVECTOR3 PlayerPos = CPlayer::GetPlayer()->GetPos();		//プレイヤーの位置の取得
		D3DXVECTOR3 SkullPos = m_pSkull->GetPos();					//頭の位置の取得

		//頭の向きの設定処理
		if (PlayerPos.x >= SkullPos.x)
		{
			m_SkullDir.x = 1.0f;
		}
		else
		{
			m_SkullDir.x = -1.0f;
		}

		//プレイヤーの位置と向きを比べて、必要だったら、テクスチャを反転する
		if (m_pSkull->GetFlipX() && m_SkullDir.x == -1.0f || !m_pSkull->GetFlipX() && m_SkullDir.x == 1.0f)
		{
			m_pSkull->FlipX();
		}

		UpdateState();							//更新処理

		m_nLife = m_pSkull->GetLife();			//体力の設定
	}
	else
	{//死んだら

		//死亡アニメーション処理
		m_nCntDeath++;

		if (m_nCntDeath >= 120)
		{//120フレームが経ったら
			Release();			//インスタンスを消す
		}
	}
}

//描画処理
void CSkullTentacle::Draw(void)
{

}

//位置の設定処理
void CSkullTentacle::SetPos(const D3DXVECTOR3 pos)
{

}

//サイズの取得処理
const D3DXVECTOR2 CSkullTentacle::GetSize(void)
{
	return D3DXVECTOR2(0.0f, 0.0f);
}

//位置の取得処理
const D3DXVECTOR3 CSkullTentacle::GetPos(void)
{
	return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//状態の取得処理
const CSkullTentacle::State CSkullTentacle::GetState(void)
{
	return m_state;
}

//状態の設定処理
void CSkullTentacle::SetState(const State state)
{
	m_state = state;
}

//ライフの設定処理
void CSkullTentacle::SetLife(const int nLife)
{
	m_nLife = nLife;
}

//ライフの取得処理
const int CSkullTentacle::GetLife(void)
{
	return m_nLife;
}

//死亡アニメーションの設定処理
void CSkullTentacle::Kill(void)
{
	m_pSkull->Kill();		//頭の死亡アニメーションを設定する
	m_pSkull = nullptr;		//頭へのポインタをnullにする
	m_pSpine->Kill();		//骨の死亡アニメーションを設定する
	m_pSpine = nullptr;		//骨へのポインタをnullにする
	m_bDead = true;			//死んだ状態にする
}


//==================================================================================================
//										静的関数
//==================================================================================================

//生成処理		pos = CSpineのanchor
CSkullTentacle* CSkullTentacle::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 headPos)
{
	CSkullTentacle* pTentacle = new CSkullTentacle;					//メモリを確保する

	//初期化処理
	if (FAILED(pTentacle->Init()))
	{
		return nullptr;
	}

	D3DXVECTOR3 PlayerPos = CPlayer::GetPlayer()->GetPos();							//プレイヤーの位置の取得

	pTentacle->m_pSpine = CSpine::Create(pos, headPos);								//頭の生成					
	pTentacle->m_pSkull = CSkull::Create(headPos, D3DXVECTOR2(60.0f, 60.0f));		//骨の生成

	if (pTentacle->m_pSpine)
	{//nullチェック
		pTentacle->m_pSpine->SetHeadPos(headPos);					//頭の位置の設定
		pTentacle->m_pSpine->SetPos(pos);							//スポーン位置の設定
	}
													
	pTentacle->m_SkullPos = headPos;								//頭の位置の設定
																	
	pTentacle->m_nLife = 5000;										//ライフの設定

	return pTentacle;						//生成したインスタンスを返す
}	



//==================================================================================================
//									プライベート関数 
//==================================================================================================


//更新処理
void CSkullTentacle::UpdateState(void)
{
	switch (m_state)
	{
	case CSkullTentacle::state_Spawn:

	{//スポーン状態

		D3DXVECTOR3 pos, PlayerPos, move;

		pos = m_pSkull->GetPos();						//位置の取得
		PlayerPos = CPlayer::GetPlayer()->GetPos();		//プレイヤーの位置の取得

		//プレイヤーの方向に動かせる
		move = PlayerPos - pos;
		D3DXVec3Normalize(&move, &move);
		move.x *= 1.0f;
		move.y *= 1.0f;

		pos += move;		//位置の更新

		m_nCntMove++;		//移動カウンターをインクリメントする

		//位置の設定
		m_pSkull->SetPos(pos);
		m_pSpine->SetHeadPos(pos);
		m_SkullPos = pos;

		if (m_nCntMove >= 30)
		{//30フレームが経ったら
			m_nCntMove = 0;				//移動カウンターを0に戻す
			m_state = state_Idle;		//待機状態にする
		}
	}

	break;

	case CSkullTentacle::state_Idle:

	{//待機状態

		m_pSkull->SetAnimPattern(0);						
		D3DXVECTOR3 pos = m_pSkull->GetPos();
		D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		m_nCntMove--;				//移動カウンターをデクリメントする

		if (m_nCntMove <= 0)
		{//移動カウンターが0以下になったら

			//別のランダムな方向に動かせる
			move = D3DXVECTOR3((float)random(-100, 100), (float)random(-100, 100), 0.0f);
			D3DXVec3Normalize(&move, &move);
			move.x *= 0.5f;
			move.y *= 0.5f;
			m_pSkull->SetMove(move);
			m_nCntMove = 30;
		}

		m_SkullPos = m_pSkull->GetPos();			//頭の位置の設定

		move = m_pSkull->GetMove();					//速度の取得

		//==============================================================================================================
		//画面を出ないようにする(画面を出ようとすると戻したら、その座標の速度を逆にする)
		if (m_SkullPos.x > (float)SCREEN_WIDTH)
		{
			m_SkullPos.x = (float)SCREEN_WIDTH;
			move.x *= -1.0f;
		}
		if (m_SkullPos.x < 0.0f)
		{
			m_SkullPos.x = 0.0f;
			move.x *= -1.0f;
		}
		if (m_SkullPos.y > (float)SCREEN_HEIGHT)
		{
			m_SkullPos.y = (float)SCREEN_HEIGHT;
			move.y *= -1.0f;
		}
		if (m_SkullPos.y < 0.0f)
		{
			m_SkullPos.y = 0.0f;
			move.y *= -1.0f;
		}
		//==============================================================================================================

		//位置の設定
		if (m_pSpine)
		{
			m_pSpine->SetHeadPos(m_SkullPos);
		}
		if (m_pSkull)
		{
			m_pSkull->SetMove(move);
		}
		m_target = m_SkullPos;
	}

	break;

	case CSkullTentacle::state_Bite:

	{//嚙む攻撃

		m_nCntAtk++;			//攻撃カウンターをインクリメントする

		if (m_nCntAtk <= 1)
		{//プレイヤーを追いかける

			m_pSkull->SetAnimPattern(1);								
			D3DXVECTOR3 PlayerPos = CPlayer::GetPlayer()->GetPos();

			D3DXVECTOR3 pos = m_pSkull->GetPos();
			D3DXVECTOR3 target = PlayerPos - pos;
			target /= 45;
			m_pSkull->SetMove(target);
		}
		else if (m_nCntAtk == 46)
		{//嚙むアニメーションと速度を逆にする

			D3DXVECTOR3 move = m_pSkull->GetMove();
			move.x *= -1.0f;
			move.y *= -1.0f;
			m_pSkull->SetMove(move);
			m_pSkull->SetAnimPattern(0);
		}
		else if (m_nCntAtk > 90)
		{//速度を0にして、待機状態に戻る

			D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			m_pSkull->SetMove(move);
			m_nCntAtk = 0;
			m_state = state_Idle;
			m_nCntMove = 0;
		}

		//位置の設定
		m_SkullPos = m_pSkull->GetPos();
		m_pSpine->SetHeadPos(m_SkullPos);
	}

		break;

	case state_Pursuit:

	{//追いかける

		m_nCntMove++;				//移動カウンターをインクリメントする

		D3DXVECTOR3 pos = m_pSkull->GetPos();
		D3DXVECTOR3 PlayerPos = CPlayer::GetPlayer()->GetPos();

		//プレイヤーの位置によって目的の位置を設定する
		if (pos.x > PlayerPos.x)
		{
			PlayerPos.x += 150.0f;
		}
		else
		{
			PlayerPos.x -= 150.0f;
		}

		//目的の位置の方向に動かせる
		D3DXVECTOR3 target = PlayerPos - pos;

		D3DXVECTOR3 dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVec3Normalize(&dir, &target);
		dir.x *= 10.0f;
		dir.y *= 10.0f;

		m_pSkull->SetMove(dir);


		if (sqrtf(((PlayerPos.x - pos.x) * (PlayerPos.x - pos.x)) + ((PlayerPos.y - pos.y) * (PlayerPos.y - pos.y))) <= 100.0f)
		{//プレイヤーに近づいたら、狙う状態に切り替える

			m_SkullPos = PlayerPos;
			m_pSkull->SetPos(m_SkullPos);
			m_state = state_Aim;
			m_nCntMove = 0;
			m_pSkull->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}

		//位置の設定
		m_SkullPos = m_pSkull->GetPos();
		m_pSpine->SetHeadPos(m_SkullPos);
	}
	break;

	case state_Aim:
	{//狙う状態

		//位置の取得
		D3DXVECTOR3 pos = m_pSkull->GetPos();
		D3DXVECTOR3 PlayerPos = CPlayer::GetPlayer()->GetPos();

		//プレイヤーの位置によって目的の位置の設定
		if (pos.x > PlayerPos.x)
		{
			PlayerPos.x += 150.0f;
		}
		else
		{
			PlayerPos.x -= 150.0f;
		}

		//位置を目的の位置にする
		D3DXVECTOR3 target = PlayerPos;

		m_SkullPos = target;
		m_pSkull->SetPos(m_SkullPos);
		m_pSpine->SetHeadPos(m_SkullPos);

		m_pSkull->SetAnimPattern(1);		//アニメーションパターンの設定

		m_nCntMove++;						//移動カウンターをインクリメントする

		if (m_nCntMove < 100)
		{//100フレームまでエネルギーを集まるアニメーションをする

			ChargeAnimation(D3DXCOLOR(0.97f, 1.0f, 0.58f, 0.25f));			//エネルギーを集まるアニメーションの処理

			if (m_nCntMove % 20 == 0)
			{//20フレームごとサウンドを再生する
				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_BEAM_CHARGE);
			}
		}

		if (m_nCntMove >= 140)
		{//140フレームが経ったら
			m_nCntMove = 0;				//移動カウンターを0に戻す
			m_state = state_ShootBeam;	//ビーム攻撃にする
		}
	}
	break;

	case state_ShootBeam:

	{//ビーム攻撃

		D3DXVECTOR3 PlayerPos = CPlayer::GetPlayer()->GetPos();		//プレイヤーの位置の取得
		float fDir = 1.0f;

		//向きとプレイヤーの位置を比べて、ビーム攻撃の方向を設定する
		if (PlayerPos.x < m_SkullPos.x)
		{
			fDir = -1.0f;
		}

		if (m_nCntAtk >= 20)
		{//20フレームごと弾を発生する
			CBeam* pBullet = CBeam::Create(D3DXVECTOR3(m_SkullPos.x + (fDir * 40.0f), m_SkullPos.y, 0.0f), D3DXVECTOR3(25.0f * fDir, 0.0f, 0.0f), D3DXVECTOR2(20.0f, 20.0f), D3DXCOLOR(0.97f, 1.0f, 0.58f, 1.0f));
			
			if (m_nCntAtk % 20 == 0)
			{
				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_FIRE);			//サウンドを再生する
			}
		}

		if (m_nCntAtk >= 120)
		{//120フレームが経ったら、戻る状態にする

			m_pSkull->SetAnimPattern(0);
			m_nCntAtk = 0;
			m_state = state_Return;

			D3DXVECTOR3 pos, move;

			//元に戻すために、速度を計算して、設定する
			pos = m_pSkull->GetPos();
			move = m_target - pos;
			move /= 240.0f;
			m_nCntMove = 240;
			m_pSkull->SetMove(move);

			return;
		}
		m_nCntAtk++;			//攻撃カウンターをインクリメントする

		//位置の設定
		m_pSkull->SetPos(m_SkullPos);
		m_pSpine->SetHeadPos(m_SkullPos);
	}
	break;

	case state_Flamethrower:

		m_pSkull->SetAnimPattern(1);		//アニメーションパターンの設定
		m_nCntAtk++;						//攻撃カウンターをインクリメントする

		if (m_nCntAtk % 30 == 29)
		{//30フレームごと弾を発生する
			CSkullFireball* pBullet = nullptr;
			D3DXVECTOR3 pos = m_pSkull->GetPos();			//位置の取得
			float fAngle = 0;								//弾の角度

			for (int nCnt = 0; nCnt < 10; nCnt++)
			{//弾を10個生成する
				pBullet = CSkullFireball::Create(pos, D3DXVECTOR3(3.0f * cosf(fAngle + m_fAngleMove), 3.0f * sinf(fAngle + m_fAngleMove), 0.0f));
				fAngle += D3DX_PI * 0.2f;
			}

			m_fAngleMove += D3DX_PI * 0.05f;				//弾のスポーン角度の更新

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_FIRE);		//サウンドを再生する
		}

		if (m_nCntAtk >= 421)
		{//421フレームが経ったら、待機状態に戻す
			m_nCntAtk = 0;
			m_fAngleMove = 0.0f;
			m_state = state_Idle;
		}

		//位置の設定
		m_pSkull->SetPos(m_SkullPos);
		m_pSpine->SetHeadPos(m_SkullPos);

		break;

	case state_Pull:

	{//引く攻撃

		m_pSkull->SetAnimPattern(2);			//アニメーションパターンの設定

		m_nCntAtk++;							//攻撃カウンターをインクリメントする

		if (m_nCntAtk % 30 == 29 && m_nCntAtk < 330)
		{//330フレームまで30フレームごとエフェクトを生成する
			CRingEffect* pEffect = CRingEffect::Create(m_SkullPos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(500.0f, 500.0f), D3DXVECTOR2(-7.0f, -7.0f),
				D3DXCOLOR(0.47f, 0.0f, 0.71f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.01f));
		}

		{//プレイヤーの位置を頭の方向に少し動かす
			D3DXVECTOR3 pos = m_pSkull->GetPos();
			D3DXVECTOR3 PlayerPos = CPlayer::GetPlayer()->GetPos();
			D3DXVECTOR3 dir = pos - PlayerPos;
			D3DXVec3Normalize(&dir, &dir);
			dir.x *= 3.0f;
			dir.y *= 3.0f;

			CPlayer* pPlayer = CPlayer::GetPlayer();
			pPlayer->SetPos(PlayerPos + dir);
		}

		if (m_nCntAtk >= 421)
		{//421フレームが経ったら、待機状態に戻す
			m_nCntAtk = 0;
			m_fAngleMove = 0.0f;
			m_state = state_Idle;
		}

		//位置の設定
		m_pSkull->SetPos(m_SkullPos);
		m_pSpine->SetHeadPos(m_SkullPos);

	}

		break;

	case state_Return:

	{//戻る状態

		m_nCntMove--;			//移動カウンターをデクリメントする

		D3DXVECTOR3 pos = m_pSkull->GetPos() + m_pSkull->GetMove();			//位置の取得

		m_SkullPos = pos;			//頭の位置の設定

		if (sqrtf(((m_SkullPos.x - m_target.x) * (m_SkullPos.x - m_target.x)) + ((m_SkullPos.y - m_target.y) * (m_SkullPos.y - m_target.y))) <= 10.0f)
		{//元の位置に着いたら、止まる
			m_nCntMove = 0;
			m_pSkull->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}

		//位置の設定
		m_pSkull->SetPos(m_SkullPos);
		m_pSpine->SetHeadPos(m_SkullPos);
	}

	if (m_nCntMove <= 0)
	{//移動カウンターが0以下になったら、待機状態に戻す
		m_nCntMove = 0;
		m_pSkull->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		m_state = state_Idle;
	}

	break;

	default:

		break;
	}
}

//エネルギーを集まるアニメーションの処理
void CSkullTentacle::ChargeAnimation(const D3DXCOLOR color)
{
	D3DXVECTOR3 pos, PosPlayer, move, acc;
	D3DXCOLOR col, Dcol;
	D3DXVECTOR2 size;
	float fX, fY;

	//ランダムな位置を設定する
	PosPlayer = CPlayer::GetPlayer()->GetPos();
	fX = (float)random(-5000, 5000);
	fY = (float)random(-5000, 5000);

	pos = D3DXVECTOR3(fX, fY, 0.0f);
	D3DXVec3Normalize(&pos, &pos);
	pos.x *= 100.0f;
	pos.y *= 100.0f;
	pos += m_SkullPos;

	//上の位置を使って、速度を計算する(頭の方向へ動かす)。加速も設定する
	move = m_SkullPos - pos;
	D3DXVec3Normalize(&move, &move);
	acc = move;
	acc.x *= 0.2f;
	acc.y *= 0.2f;
	move.x *= 0.0f;
	move.y *= 0.0f;

	//色の設定
	col = color;
	fX = fX = (float)random(-10, 10) * 0.01f;
	col.r += fX;
	fX = fX = (float)random(-10, 10) * 0.01f;
	col.g += fX;
	fX = fX = (float)random(-10, 10) * 0.01f;
	col.b += fX;

	Dcol = D3DXCOLOR(0.0f, 0.0f, 0.0f, -0.25f / (float)121);

	fX = fX = (float)random(-10, 10) * D3DX_PI * 0.05f;

	//エフェクトの生成
	CRotSimpleEff* pEffect = CRotSimpleEff::Create(pos, m_pSkull->GetPos(), move, col, 120, Dcol, D3DXVECTOR2(10.0f, 4.0f), fX);
	pEffect->SetAcceleration(acc);
}