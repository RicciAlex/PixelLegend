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
}

//更新処理
void CSkullTentacle::Update(void)
{
	if (!m_bDead)
	{//死んでいない場合

		D3DXVECTOR3 PlayerPos = CPlayer::GetPlayer()->GetPos();				//プレイヤーの位置の取得
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

		if (m_pSkull->GetFlipX() && m_SkullDir.x == -1.0f || !m_pSkull->GetFlipX() && m_SkullDir.x == 1.0f)
		{
			m_pSkull->FlipX();
		}

		UpdateState();							//更新処理

		m_nLife = m_pSkull->GetLife();


		////==================================================================================================================================================
		////																一時的
		//if (CInputKeyboard::GetKeyboardTrigger(DIK_I))
		//{
		//	D3DXVECTOR3 move = PlayerPos - SkullPos;
		//	D3DXVec3Normalize(&move, &move);
		//	move.x *= 2.0f;
		//	move.y *= 2.0f;
		//	move.z = 0.0f;

		//	CHeartBullet* pBullet = CHeartBullet::Create(SkullPos, move, D3DXCOLOR(0.97f, 0.51f, 1.0f, 0.75f));
		//}

		//if (CInputKeyboard::GetKeyboardTrigger(DIK_O))
		//{
		//	/*D3DXVECTOR3 move = PlayerPos - SkullPos;
		//	D3DXVec3Normalize(&move, &move);
		//	move.x *= 2.0f;
		//	move.y *= 2.0f;
		//	move.z = 0.0f;*/

		//	for (int nCnt = 0; nCnt < 80; nCnt++)
		//	{
		//		CStarEffect* pBullet = CStarEffect::Create(D3DXVECTOR3(300.0f, 300.0f, 0.0f), 6.0f * nCnt * D3DX_PI / 80.0f, 18.0f * D3DX_PI / 40.0f, D3DXCOLOR(1.0f, 1.0f, 0.015f, 0.25f), D3DXVECTOR2(4.0f, 4.0f), 640);
		//	}
		//}
		//if (CInputKeyboard::GetKeyboardTrigger(DIK_M))
		//{
		//	CLetter* letter = CLetter::Create(D3DXVECTOR3(500.0f, 300.0f, 0.0f), D3DXVECTOR2(30.0f, 30.0f), 'a');
		//	letter = CLetter::Create(D3DXVECTOR3(550.0f, 300.0f, 0.0f), D3DXVECTOR2(30.0f, 30.0f), 'h');
		//	letter = CLetter::Create(D3DXVECTOR3(600.0f, 300.0f, 0.0f), D3DXVECTOR2(30.0f, 30.0f), 'a');
		//	letter = CLetter::Create(D3DXVECTOR3(650.0f, 300.0f, 0.0f), D3DXVECTOR2(30.0f, 30.0f), 'h');
		//	letter = CLetter::Create(D3DXVECTOR3(700.0f, 300.0f, 0.0f), D3DXVECTOR2(30.0f, 30.0f), 'a');
		//	letter = CLetter::Create(D3DXVECTOR3(750.0f, 300.0f, 0.0f), D3DXVECTOR2(30.0f, 30.0f), 'h');
		//}
		//if (CInputKeyboard::GetKeyboardTrigger(DIK_N))
		//{
		//	int rand = random(0, 1);

		//	D3DXVECTOR3 dir = D3DXVECTOR3((float)random(5, 30) * 0.1f, (float)random(40, 70) * -0.1f, 0.0f);

		//	if (rand == 0)
		//	{
		//		dir.x *= -1.0f;
		//	}

		//	CTearBullet* pBullet = CTearBullet::Create(D3DXVECTOR3(400.0f, 400.0f, 0.0f), dir);
		//}
	}
	else
	{//死んだら

		//死亡アニメーション処理
		m_nCntDeath++;

		if (m_nCntDeath >= 120)
		{
			Release();
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
	m_pSkull->Kill();
	m_pSkull = nullptr;
	m_pSpine->Kill();
	m_pSpine = nullptr;
	m_bDead = true;
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

	pTentacle->m_pSpine = CSpine::Create(pos, headPos);								
	pTentacle->m_pSkull = CSkull::Create(headPos, D3DXVECTOR2(60.0f, 60.0f));		
	pTentacle->m_pSpine->SetHeadPos(headPos);										
	pTentacle->m_pSpine->SetPos(pos);												
	pTentacle->m_SkullPos = headPos;												
																					
	pTentacle->m_nLife = 5000;														//ライフの設定

	return pTentacle;
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

	{
		D3DXVECTOR3 pos, PlayerPos, move;

		pos = m_pSkull->GetPos();
		PlayerPos = CPlayer::GetPlayer()->GetPos();

		move = PlayerPos - pos;
		D3DXVec3Normalize(&move, &move);
		move.x *= 1.0f;
		move.y *= 1.0f;

		pos += move;

		m_nCntMove++;

		m_pSkull->SetPos(pos);
		m_pSpine->SetHeadPos(pos);
		m_SkullPos = pos;

		if (m_nCntMove >= 30)
		{
			m_nCntMove = 0;
			m_state = state_Idle;
		}
	}

	break;

	case CSkullTentacle::state_Idle:

	{
		m_pSkull->SetAnimPattern(0);
		D3DXVECTOR3 pos = m_pSkull->GetPos();
		D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		m_nCntMove--;

		if (m_nCntMove <= 0)
		{
			move = D3DXVECTOR3((float)random(-100, 100), (float)random(-100, 100), 0.0f);
			D3DXVec3Normalize(&move, &move);
			move.x *= 0.5f;
			move.y *= 0.5f;
			m_pSkull->SetMove(move);
			m_nCntMove = 30;
		}

		m_SkullPos = m_pSkull->GetPos();

		move = m_pSkull->GetMove();

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

		m_pSpine->SetHeadPos(m_SkullPos);
		m_pSkull->SetMove(move);
		m_target = m_SkullPos;
	}

	break;

	case CSkullTentacle::state_Bite:

		m_nCntAtk++;

		if (m_nCntAtk <= 1)
		{

			m_pSkull->SetAnimPattern(1);
			D3DXVECTOR3 PlayerPos = CPlayer::GetPlayer()->GetPos();

			D3DXVECTOR3 pos = m_pSkull->GetPos();
			D3DXVECTOR3 target = PlayerPos - pos;
			target /= 45;
			m_pSkull->SetMove(target);
		}
		else if (m_nCntAtk == 46)
		{
			D3DXVECTOR3 move = m_pSkull->GetMove();
			move.x *= -1.0f;
			move.y *= -1.0f;
			m_pSkull->SetMove(move);
			m_pSkull->SetAnimPattern(0);
		}
		else if (m_nCntAtk > 90)
		{
			D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			m_pSkull->SetMove(move);
			m_nCntAtk = 0;
			m_state = state_Idle;
			m_nCntMove = 0;
		}

		m_SkullPos = m_pSkull->GetPos();
		m_pSpine->SetHeadPos(m_SkullPos);

		break;

	case state_Pursuit:

	{
		m_nCntMove++;
		D3DXVECTOR3 pos = m_pSkull->GetPos();
		D3DXVECTOR3 PlayerPos = CPlayer::GetPlayer()->GetPos();

		if (pos.x > PlayerPos.x)
		{
			PlayerPos.x += 150.0f;
		}
		else
		{
			PlayerPos.x -= 150.0f;
		}

		D3DXVECTOR3 target = PlayerPos - pos;

		D3DXVECTOR3 dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVec3Normalize(&dir, &target);
		dir.x *= 10.0f;
		dir.y *= 10.0f;

		m_pSkull->SetMove(dir);


		if (sqrtf(((PlayerPos.x - pos.x) * (PlayerPos.x - pos.x)) + ((PlayerPos.y - pos.y) * (PlayerPos.y - pos.y))) <= 100.0f)
		{
			m_SkullPos = PlayerPos;
			m_pSkull->SetPos(m_SkullPos);
			m_state = state_Aim;
			m_nCntMove = 0;
			m_pSkull->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}

		m_SkullPos = m_pSkull->GetPos();
		m_pSpine->SetHeadPos(m_SkullPos);
	}
	break;

	case state_Aim:
	{
		D3DXVECTOR3 pos = m_pSkull->GetPos();
		D3DXVECTOR3 PlayerPos = CPlayer::GetPlayer()->GetPos();

		if (pos.x > PlayerPos.x)
		{
			PlayerPos.x += 150.0f;
		}
		else
		{
			PlayerPos.x -= 150.0f;
		}

		D3DXVECTOR3 target = PlayerPos;

		m_SkullPos = target;
		m_pSkull->SetPos(m_SkullPos);
		m_pSpine->SetHeadPos(m_SkullPos);

		m_pSkull->SetAnimPattern(1);

		m_nCntMove++;

		if (m_nCntMove < 100)
		{
			ChargeAnimation(D3DXCOLOR(0.97f, 1.0f, 0.58f, 0.25f));

			if (m_nCntMove % 20 == 0)
			{
				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_BEAM_CHARGE);
			}
		}

		if (m_nCntMove >= 140)
		{
			m_nCntMove = 0;
			m_state = state_ShootBeam;
		}
	}
	break;

	case state_ShootBeam:

	{
		D3DXVECTOR3 PlayerPos = CPlayer::GetPlayer()->GetPos();
		float fDir = 1.0f;

		if (PlayerPos.x < m_SkullPos.x)
		{
			fDir = -1.0f;
		}

		if (m_nCntAtk >= 20)
		{
			CBeam* pBullet = CBeam::Create(D3DXVECTOR3(m_SkullPos.x + (fDir * 40.0f), m_SkullPos.y, 0.0f), D3DXVECTOR3(25.0f * fDir, 0.0f, 0.0f), D3DXVECTOR2(20.0f, 20.0f), D3DXCOLOR(0.97f, 1.0f, 0.58f, 1.0f));
			
			if (m_nCntAtk % 20 == 0)
			{
				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_FIRE);
			}
		}

		if (m_nCntAtk >= 120)
		{
			m_pSkull->SetAnimPattern(0);
			m_nCntAtk = 0;
			m_state = state_Return;

			D3DXVECTOR3 pos, move;

			pos = m_pSkull->GetPos();
			move = m_target - pos;
			move /= 240.0f;
			m_nCntMove = 240;
			m_pSkull->SetMove(move);

			return;
		}
		m_nCntAtk++;


		m_pSkull->SetPos(m_SkullPos);
		m_pSpine->SetHeadPos(m_SkullPos);
	}
	break;

	case state_Flamethrower:

		m_pSkull->SetAnimPattern(1);
		m_nCntAtk++;

		if (m_nCntAtk % 30 == 29)
		{
			CSkullFireball* pBullet = nullptr;
			D3DXVECTOR3 pos = m_pSkull->GetPos();
			float fAngle = 0;

			for (int nCnt = 0; nCnt < 10; nCnt++)
			{
				pBullet = CSkullFireball::Create(pos, D3DXVECTOR3(3.0f * cosf(fAngle + m_fAngleMove), 3.0f * sinf(fAngle + m_fAngleMove), 0.0f));
				fAngle += D3DX_PI * 0.2f;
			}

			m_fAngleMove += D3DX_PI * 0.05f;

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_FIRE);
		}

		if (m_nCntAtk >= 421)
		{
			m_nCntAtk = 0;
			m_fAngleMove = 0.0f;
			m_state = state_Idle;
		}

		m_pSkull->SetPos(m_SkullPos);
		m_pSpine->SetHeadPos(m_SkullPos);

		break;

	case state_Pull:

		m_pSkull->SetAnimPattern(2);

		m_nCntAtk++;

		if (m_nCntAtk % 30 == 29 && m_nCntAtk < 330)
		{
			CRingEffect* pEffect = CRingEffect::Create(m_SkullPos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(500.0f, 500.0f), D3DXVECTOR2(-7.0f, -7.0f),
				D3DXCOLOR(0.47f, 0.0f, 0.71f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.01f));
		}

		{
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
		{
			m_nCntAtk = 0;
			m_fAngleMove = 0.0f;
			m_state = state_Idle;
		}

		m_pSkull->SetPos(m_SkullPos);
		m_pSpine->SetHeadPos(m_SkullPos);

		break;

	case state_Return:

	{
		m_nCntMove--;

		D3DXVECTOR3 pos = m_pSkull->GetPos() + m_pSkull->GetMove();

		m_SkullPos = pos;

		if (sqrtf(((m_SkullPos.x - m_target.x) * (m_SkullPos.x - m_target.x)) + ((m_SkullPos.y - m_target.y) * (m_SkullPos.y - m_target.y))) <= 10.0f)
		{
			m_nCntMove = 0;
			m_pSkull->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}

		m_pSkull->SetPos(m_SkullPos);
		m_pSpine->SetHeadPos(m_SkullPos);
	}

	if (m_nCntMove <= 0)
	{
		m_nCntMove = 0;
		m_pSkull->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		m_state = state_Idle;
	}

	break;

	default:

		break;
	}
}

void CSkullTentacle::ChargeAnimation(const D3DXCOLOR color)
{
	D3DXVECTOR3 pos, PosPlayer, move, acc;
	D3DXCOLOR col, Dcol;
	D3DXVECTOR2 size;
	float fX, fY;

	PosPlayer = CPlayer::GetPlayer()->GetPos();
	fX = (float)random(-5000, 5000);
	fY = (float)random(-5000, 5000);

	pos = D3DXVECTOR3(fX, fY, 0.0f);
	D3DXVec3Normalize(&pos, &pos);
	pos.x *= 100.0f;
	pos.y *= 100.0f;
	pos += m_SkullPos;

	move = m_SkullPos - pos;
	D3DXVec3Normalize(&move, &move);
	acc = move;
	acc.x *= 0.2f;
	acc.y *= 0.2f;
	move.x *= 0.0f;
	move.y *= 0.0f;

	col = color;
	fX = fX = (float)random(-10, 10) * 0.01f;
	col.r += fX;
	fX = fX = (float)random(-10, 10) * 0.01f;
	col.g += fX;
	fX = fX = (float)random(-10, 10) * 0.01f;
	col.b += fX;

	Dcol = D3DXCOLOR(0.0f, 0.0f, 0.0f, -0.25f / (float)121);

	fX = fX = (float)random(-10, 10) * D3DX_PI * 0.05f;

	CRotSimpleEff* pEffect = CRotSimpleEff::Create(pos, m_pSkull->GetPos(), move, col, 120, Dcol, D3DXVECTOR2(10.0f, 4.0f), fX);
	pEffect->SetAcceleration(acc);
}