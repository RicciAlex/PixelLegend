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
	{
		return -1;
	}

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

	/*CObject_2D* pEnemy = CObject_2D::Create();
	pEnemy->SetPos(D3DXVECTOR3(300.0f, 300.0f, 0.0f));
	pEnemy->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pEnemy->SetSize(D3DXVECTOR2(232.5f, 345.0f));
	pEnemy->SetTexture(CObject::TextureGluttonyHeart);
	pEnemy->SetTextureParameter(2, 2, 1, 15);
	pEnemy->SetStartingRot(D3DX_PI * 0.5f);*/

	return S_OK;
}

//終了処理
void CGreed::Uninit(void)
{
	if (m_pHitboxUp != nullptr)
	{
		m_pHitboxUp->Release();
		m_pHitboxUp = nullptr;
	}
	if (m_pHitboxDown != nullptr)
	{			 
		m_pHitboxDown->Release();
		m_pHitboxDown = nullptr;
	}

	for (int nCnt = 0; nCnt < MaxTower; nCnt++)
	{
		m_pTower[nCnt]->Release();
		m_pTower[nCnt] = nullptr;
	}

	if (m_pLife != nullptr)
	{
		m_pLife->Release();
		m_pLife = nullptr;
	}

	CEnemy::Uninit();
}

//更新処理
void CGreed::Update(void)
{
	D3DXVECTOR3 pos = GetPos();

	if (m_pHitboxUp != nullptr)
	{
		m_pHitboxUp->SetPos(GetPos() + m_HitboxUpRelativePos);

		if (m_pHitboxUp->GetHitState())
		{
			m_pHitboxUp->SetHitState(false);
			m_pHitboxDown->SetHitState(false);

			int nLife = GetLife();
			int nDamage = CPlayer::GetPlayer()->GetAttack();
			nLife -= nDamage;

			if (m_pLife != nullptr)
			{
				m_pLife->SubtractLife(nDamage);
			}

			if (nLife <= 0)
			{
				m_state = state_death;
			}
			else
			{
				SetLife(nLife);

				for (int nCnt = 0; nCnt < random(1, 2); nCnt++)
				{
					D3DXVECTOR3 move = D3DXVECTOR3((float)random(-500, 500) * 0.01f, (float)random(400, 800) * -0.01f, 0.0f);

					CGreedBullet::Create(pos, move, D3DXVECTOR3(0.0f, 0.05f, 0.0f));

					CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_COIN);
				}
			}
		}
	}
	if (m_pHitboxDown != nullptr)
	{
		m_pHitboxDown->SetPos(GetPos() + m_HitboxDownRelativePos);

		if (m_pHitboxDown->GetHitState())
		{
			m_pHitboxDown->SetHitState(false);

			int nLife = GetLife();
			int nDamage = CPlayer::GetPlayer()->GetAttack();
			nLife -= nDamage;

			if (m_pLife != nullptr)
			{
				m_pLife->SubtractLife(nDamage);
			}

			if (nLife <= 0)
			{
				m_state = state_death;
			}
			else
			{
				SetLife(nLife);

				for (int nCnt = 0; nCnt < random(1, 3); nCnt++)
				{
					D3DXVECTOR3 move = D3DXVECTOR3((float)random(-500, 500) * 0.01f, (float)random(400, 800) * -0.01f, 0.0f);

					CGreedBullet::Create(pos, move, D3DXVECTOR3(0.0f, 0.05f, 0.0f));

					CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_COIN);
				}
			}
		}
	}

	switch (m_state)
	{
	case CGreed::state_spawn:

	{
		m_nAnimCnt++;

		if (m_nAnimCnt >= 30)
		{
			m_nAnimCnt = 0;
			SetAnimPattern(GetPresentAnimPattern() ^ 1);
		}

		if (pos.x <= 1000.0f)
		{
			m_nAnimCnt = 0;
			SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			SetAnimPattern(0);
			m_state = state_normal;
		}

		if (GetPresentAnimPattern() == 0)
		{
			m_HitboxUpRelativePos = D3DXVECTOR3(0.0f, 5.0f, 0.0f);
			m_HitboxDownRelativePos = D3DXVECTOR3(0.0f, 85.0f, 0.0f);
			m_pHitboxUp->SetRadius(100.0f);
			m_pHitboxDown->SetSize(D3DXVECTOR2(170.0f, 30.0f));
		}
		else
		{
			m_HitboxUpRelativePos = D3DXVECTOR3(0.0f, -30.0f, 0.0f);
			m_HitboxDownRelativePos = D3DXVECTOR3(0.0f, 75.0f, 0.0f);
			m_pHitboxUp->SetRadius(95.0f);
			m_pHitboxDown->SetSize(D3DXVECTOR2(130.0f, 40.0f));
		}
	}

	break;

	case CGreed::state_normal:

	{
		int k = 0;

		if (GetLife() < 15000)
		{
			k = 2;
			SetMaxSpeed(4.5f);
		}
		else if(GetLife() < 10000)
		{
			k = 4;
			SetMaxSpeed(7.5f);
		}

		if(random(1, 100) > 100 - (k * 10))
		{
			SetAnimPattern(0);
			m_state = state_rage;
			break;
		}

		while (true)
		{
			int nRand = random(0, 4);

			D3DXVECTOR3 L = TargetPos[nRand] - pos;

			if (D3DXVec3Length(&L) > 20.0f)
			{
				D3DXVECTOR3 move;
				D3DXVec3Normalize(&move, &L);
				move.x *= GetMaxSpeed();
				move.y *= GetMaxSpeed();
				SetMove(move);
				m_targetIdx = nRand;
				m_state = state_walk;

				if (move.x > 0 && !GetFlipX() || move.x < 0 && GetFlipX())
				{
					FlipX();
				}

				break;
			}
		}
	}

	break;

	case CGreed::state_walk:

	{
		m_nAnimCnt++;

		if (m_nAnimCnt >= 30)
		{
			m_nAnimCnt = 0;
			SetAnimPattern(GetPresentAnimPattern() ^ 1);
		}

		D3DXVECTOR3 L = TargetPos[m_targetIdx] - pos;

		if (D3DXVec3Length(&L) < 10.0f)
		{
			m_nAnimCnt = 0;
			SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			SetAnimPattern(0);
			m_state = state_shot;
		}

		if (GetPresentAnimPattern() == 0)
		{
			m_HitboxUpRelativePos = D3DXVECTOR3(0.0f, 5.0f, 0.0f);
			m_HitboxDownRelativePos = D3DXVECTOR3(0.0f, 85.0f, 0.0f);
			m_pHitboxUp->SetRadius(100.0f);
			m_pHitboxDown->SetSize(D3DXVECTOR2(170.0f, 30.0f));
		}
		else
		{
			m_HitboxUpRelativePos = D3DXVECTOR3(0.0f, -30.0f, 0.0f);
			m_HitboxDownRelativePos = D3DXVECTOR3(0.0f, 75.0f, 0.0f);
			m_pHitboxUp->SetRadius(95.0f);
			m_pHitboxDown->SetSize(D3DXVECTOR2(130.0f, 40.0f));
		}
	}

	break;

	case CGreed::state_shot:

	{
		D3DXVECTOR3 PlayerPos = CPlayer::GetPlayer()->GetPos();

		if (PlayerPos.x > pos.x && !GetFlipX() || PlayerPos.x < pos.x && GetFlipX())
		{
			FlipX();
		}
		
		int nLife = GetLife();

		m_nShootDelay++;

		if (m_nShootDelay % 30 == 13)
		{
			SetAnimPattern(1);
		}
		else if (m_nShootDelay % 30 == 28)
		{
			SetAnimPattern(0);

			D3DXVECTOR3 move = PlayerPos - pos;
			D3DXVec3Normalize(&move, &move);

			CGreedBullet::Create(pos, D3DXVECTOR3(3.5f * move.x, 3.5f * move.y, 0.0f));

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_COIN);

			if (nLife < 15000)
			{
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

				if (nLife < 10000)
				{
					NewMove = D3DXVECTOR3(cosf(fAngle) * cosf(D3DX_PI / 3.0f) - sinf(fAngle) * sinf(D3DX_PI / 3.0f),
						sinf(fAngle) * cosf(D3DX_PI / 3.0f) + cosf(fAngle) * sinf(D3DX_PI / 3.0f), 0.0f);

					CGreedBullet::Create(pos, D3DXVECTOR3(3.5f * NewMove.x, 3.5f * NewMove.y, 0.0f));

					NewMove = D3DXVECTOR3(cosf(fAngle) * cosf(-D3DX_PI / 3.0f) - sinf(fAngle) * sinf(-D3DX_PI / 3.0f),
						sinf(fAngle) * cosf(-D3DX_PI / 3.0f) + cosf(fAngle) * sinf(-D3DX_PI / 3.0f), 0.0f);

					CGreedBullet::Create(pos, D3DXVECTOR3(3.5f * NewMove.x, 3.5f * NewMove.y, 0.0f));
				}
			}
		}
		else if (m_nShootDelay > 350)
		{
			m_nShootDelay = 0;
			m_state = state_normal;
		}
	}

	break;

	case CGreed::state_rage:

	{
		m_nShootDelay++;
		m_nCntMove++;

		if (m_nCntMove < 100)
		{
			if (m_nCntMove % 20 == 19)
			{
				SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else if (m_nCntMove % 10 == 9)
			{
				SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			}
		}
		else
		{
			SetAnimPattern(1);
			SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			if (m_nShootDelay >= 10)
			{
				m_nShootDelay = 0;

				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_COIN);

				for (int nCnt = 0; nCnt < 8; nCnt++)
				{
					CGreedBullet::Create(pos, D3DXVECTOR3(5.0f * cosf(m_fShotAngle + (nCnt * D3DX_PI / 4.0f)), 5.0f * sinf(m_fShotAngle + (nCnt * D3DX_PI / 4.0f)), 0.0f));
				}

				m_fShotAngle += m_fSumAngle;

				if (m_fShotAngle >= 1.0f || m_fShotAngle <= -1.0f)
				{
					m_fSumAngle *= -1.0f;
				}
			}
		}

		if (m_nCntMove >= 580)
		{
			m_nShootDelay = 0;
			m_nCntMove = 0;
			m_fShotAngle = 0.0f;
			m_state = state_normal;
		}
	}

	break;

	case CGreed::state_death:

	{
		m_nShootDelay++;
		
		if (m_nShootDelay % 20 == 1)
		{
			D3DXCOLOR col = GetColor();

			if (col.g <= 0.5f)
			{
				SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, col.a));
			}
			else
			{
				SetColor(D3DXCOLOR(1.0f, 0.2f, 0.2f, col.a));
			}
		}

		if (m_nShootDelay == 130)
		{
			for (int nCnt = 0; nCnt < 30; nCnt++)
			{
				D3DXVECTOR3 move = D3DXVECTOR3((float)random(-500, 500) * 0.01f, (float)random(-500, 500) * -0.01f, 0.0f);

				CGreedBullet::Create(pos, move);

				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_BIG_EXPLOSION);
			}
		}

		if (m_nShootDelay == 300)
		{
			m_bEnd = true;
		}
	}

	break;

	default:
		break;
	}

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