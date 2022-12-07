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

CEnvy::CEnvy()
{
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
	if (FAILED(CEnemy::Init()))
	{
		return -1;
	}

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
	for (int nCnt = 0; nCnt < nGearNum; nCnt++)
	{
		if (m_pGear[nCnt] != nullptr)
		{
			m_pGear[nCnt]->Release();
			m_pGear[nCnt] = nullptr;
		}
	}

	if (m_pHat != nullptr)
	{
		m_pHat->Release();
		m_pHat = nullptr;
	}

	if (m_pCannon != nullptr)
	{	   
		m_pCannon->Release();
		m_pCannon = nullptr;
	}

	for (int nCnt = 0; nCnt < nPipeNum; nCnt++)
	{
		if (m_pPipe[nCnt] != nullptr)
		{
			m_pPipe[nCnt]->Release();
			m_pPipe[nCnt] = nullptr;
		}
	}
	
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}
	if (m_pHatHitbox != nullptr)
	{
		m_pHatHitbox->Release();
		m_pHatHitbox = nullptr;
	}
	if (m_pLife != nullptr)
	{
		m_pLife->Release();
		m_pLife = nullptr;
	}
}

//更新処理
void CEnvy::Update(void)
{
	UpdatePointers();

	if (m_state != state_death)
	{
		m_fAngleMove += D3DX_PI * 0.02f;
		D3DXVECTOR3 pos = GetPos();
		pos.y += 0.5f * sinf(m_fAngleMove);
		SetPos(pos);
	}

	UpdateState();

	if (!m_bEnd)
	{
		CObject_2D::Update();
	}
}

//描画処理
void CEnvy::Draw(void)
{
	CObject_2D::Draw();
}


const bool CEnvy::GetEnd(void)
{
	return m_bEnd;
}





//生成処理
CEnvy* CEnvy::Create(void)
{
	CEnvy* pEnemy = new CEnvy;

	if (FAILED(pEnemy->Init()))
	{
		return nullptr;
	}

	D3DXVECTOR3 pos = D3DXVECTOR3(1500.0f, 400.0f, 0.0f);

	pEnemy->SetPos(pos);
	pEnemy->SetSize(D3DXVECTOR2(140.0f, 118.0f));
	pEnemy->SetTexture(CObject::TextureFace);
	pEnemy->SetTextureParameter(1, 1, 1, INT_MAX);
	pEnemy->SetStartingRot(D3DX_PI * 0.5f);
	pEnemy->SetMove(D3DXVECTOR3(-5.0f, 0.0f, 0.0f));
	pEnemy->SetLife(15000);

	pEnemy->CreateGears();

	pEnemy->m_pHitbox = CSquareHitbox::Create(pos, D3DXVECTOR2(110.0f, 120.0f), CHitbox::Type_Enemy);
	pEnemy->m_pHatHitbox = CSquareHitbox::Create(pos + pEnemy->m_hatRelativePos, D3DXVECTOR2(95.0f, 115.0f), CHitbox::Type_Enemy);

	pEnemy->m_pLife = CEnemyLife::Create(D3DXVECTOR3(900.0f, 40.0f, 0.0f), D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.4f), 15000, "envy");

	return pEnemy;
}


void CEnvy::CreateGears(void)
{
	m_pipeRelativePos[0] = D3DXVECTOR3(-25.0f, -125.0f, 0.0f);
	m_pipeRelativePos[1] = D3DXVECTOR3(35.0f, -140.0f, 0.0f);

	for (int nCnt = 0; nCnt < nPipeNum; nCnt++)
	{
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
		m_cannonRelativePos = D3DXVECTOR3(0.0f, -75.0f, 0.0f);
		m_pCannon = CObject_2D::Create();
		m_pCannon->SetPos(GetPos() + m_cannonRelativePos);
		m_pCannon->SetTexture(CObject::TexturePipe);
		m_pCannon->SetTextureParameter(1, 1, 1, INT_MAX);
		m_pCannon->SetPriority(2);
		m_pCannon->SetSize(D3DXVECTOR2(15.0f, 48.75f));
		m_pCannon->SetStartingRot(D3DX_PI);
	}

	m_pPipe[0]->SetSize(D3DXVECTOR2(33.75f, 45.0f));
	m_pPipe[1]->SetSize(D3DXVECTOR2(22.5f, 67.5f));

	m_gearRelativePos[0] = D3DXVECTOR3(10.0f, -110.0f, 0.0f);
	m_gearRelativePos[1] = D3DXVECTOR3(70.0f, -120.0f, 0.0f);
	m_gearRelativePos[2] = D3DXVECTOR3(30.0f, -105.0f, 0.0f);
	m_gearRelativePos[3] = D3DXVECTOR3(100.0f, -110.0f, 0.0f);
	m_gearRelativePos[4] = D3DXVECTOR3(-20.0f, -100.0f, 0.0f);
	m_gearRelativePos[5] = D3DXVECTOR3(-60.0f, -110.0f, 0.0f);

	D3DXVECTOR2 size[nGearNum] = { {26.25f, 26.25f },{ 45.0f, 45.0f },{ 26.25f, 26.25f },{ 22.5f, 22.5f },{ 52.5f, 52.5f },{ 30.0f, 30.0f }};
	float fRotSpeed[nGearNum] = { D3DX_PI * 0.01f, -D3DX_PI * 0.01f, D3DX_PI * 0.02f, D3DX_PI * 0.008f, -D3DX_PI * 0.009f, D3DX_PI * 0.025f };

	for (int nCnt = 0; nCnt < nGearNum; nCnt++)
	{
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

	m_pGear[0]->SetAnimPattern(5);
	m_pGear[1]->SetAnimPattern(2);
	m_pGear[2]->SetAnimPattern(1);
	m_pGear[3]->SetAnimPattern(3);
	m_pGear[4]->SetAnimPattern(2);
	m_pGear[5]->SetAnimPattern(4);

	m_hatRelativePos = D3DXVECTOR3(20.0f, -230.0f, 0.0f);

	m_pHat = CObject_2D::Create();
	m_pHat->SetPos(GetPos() + m_hatRelativePos);
	m_pHat->SetSize(D3DXVECTOR2(160.0f, 144.0f));
	m_pHat->SetTexture(CObject::TextureTopHat);
	m_pHat->SetTextureParameter(1, 1, 1, INT_MAX);
	m_pHat->SetStartingRot(D3DX_PI * 0.5f);
}




void CEnvy::UpdateState(void)
{
	D3DXVECTOR3 pos = GetPos();


	switch (m_state)
	{
	case CEnvy::state_spawn:

	{
		if (pos.x <= 900.0f)
		{
			SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			m_state = state_normal;
		}
	}

		break;

	case CEnvy::state_normal:

	{
		m_nCntState++;
		m_nShootDelay++;
		

		if (m_nShootDelay >= 120)
		{
			m_nShootDelay = 0;

			CMissile* pBullet = CMissile::Create(D3DXVECTOR3(pos.x - 23.0f, pos.y - 180.0f, 0.0f), D3DXVECTOR3(0.0f, -3.0f, 0.0f));

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_ROCKET_START);
		}

		D3DXVECTOR3 target = CPlayer::GetPlayer()->GetPos();
		target -= pos + m_cannonRelativePos;
		target.x -= 20.0f;

		if (fabsf(target.x) < 100.0f || m_nCntState >= 1200)
		{
			m_nCntState = 0;

			SetMove(D3DXVECTOR3(3.0f, 0.0f, 0.0f));

			m_state = state_hide;
		}
	}

		break;
	case CEnvy::state_hide:

	{
		m_nShootDelay++;

		if (pos.x >= 1450.0f)
		{
			SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

			m_state = state_strike;
			m_nShootDelay = 0;
		}
	}

		break;

	case CEnvy::state_strike:

	{
		m_nCntState++;
		m_nShootDelay++;

		if (m_nShootDelay % 40 == 39)
		{
			CMissile* pBullet = CMissile::Create(D3DXVECTOR3(1400.0f, 240.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.5f, 0.0f, 0.0f));
			pBullet = CMissile::Create(D3DXVECTOR3(1400.0f, 480.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.5f, 0.0f, 0.0f));

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_ROCKET_START);
		}

		if (m_nShootDelay >= 60)
		{
			m_nShootDelay = 0;

			float fY = (float)random(50, 190);
			CMissile* pBullet = CMissile::Create(D3DXVECTOR3(1400.0f, fY, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.5f, 0.0f, 0.0f));
			pBullet = CMissile::Create(D3DXVECTOR3(1400.0f, fY + 240.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.5f, 0.0f, 0.0f));
			pBullet = CMissile::Create(D3DXVECTOR3(1400.0f, fY + 480.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.5f, 0.0f, 0.0f));

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_ROCKET_START);

			//pBullet = CMissile::Create(D3DXVECTOR3(pos.x - 23.0f, pos.y - 180.0f, 0.0f), D3DXVECTOR3(0.0f, -3.0f, 0.0f));
		}

		if (m_nCntState >= 310)
		{
			m_nCntState = 0;
			m_nShootDelay = 0;
			m_state = state_spawn;
			SetMove(D3DXVECTOR3(-5.0f, 0.0f, 0.0f));
		}
	}

		break;

	case state_death:

	{
		m_nCntState++;
		m_nShootDelay++;

		pos.y -= 50.0f;

		if (m_nShootDelay % 30 == 0)
		{
			int nRand = random(1, 3);

			D3DXVECTOR3 P = pos;
			float radius = GetSize().x * 0.45f;

			P.x += (float)random((int)-radius, (int)radius);
			P.y += (float)random((int)-radius, (int)radius);

			CExplosion* pExplosion = CExplosion::Create();
			pExplosion->SetPos(P);
			pExplosion->SetSize(D3DXVECTOR2(50.0f, 50.0f));
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_BIG_EXPLOSION);

			for (int nCnt = 0; nCnt < nRand; nCnt++)
			{
				CEnvyPieces::Create(pos, radius);
			}
		}

		if (GetPos().y >= 1000.0f)
		{
			m_bEnd = true;
		}
	}

		break;
	
	default:
		break;
	}
}


void CEnvy::UpdatePointers(void)
{
	if (m_pHat != nullptr)
	{
		if (m_pHatHitbox != nullptr)
		{
			m_pHat->SetPos(GetPos() + m_hatRelativePos);
			m_pHatHitbox->SetPos(m_pHat->GetPos());

			int life = GetLife();

			if (m_pHatHitbox->GetHitState())
			{
				m_pHatHitbox->SetHitState(false);
				int nDamage = CPlayer::GetPlayer()->GetAttack();
				life -= nDamage;
				SetLife(life);

				if (m_pLife != nullptr)
				{
					m_pLife->SubtractLife(nDamage);
				}
			}

			if (life < 10000)
			{
				m_pHat->SetMove(D3DXVECTOR3(4.0f, -8.0f, 0.0f));
				m_pHat->SetAcceleration(D3DXVECTOR3(0.0f, 0.2f, 0.0f));
				m_pHat->SetRotation(-D3DX_PI * 0.025f);
				m_pHatHitbox->Release();
				m_pHatHitbox = nullptr;
			}
		}
		else
		{
			if (m_pHat->GetPos().y > 1000.0f || m_pHat->GetPos().x > 1500.0f)
			{
				m_pHat->Release();
				m_pHat = nullptr;
			}
		}
	}

	//===========================================================================================================================================
	if (m_pCannon != nullptr && GetLife() < 12500)
	{
		int a = 0;
		if (m_cannonRelativePos.x > -115.0f)
		{
			m_cannonRelativePos.x += -0.5f;
		}
		else
		{
			if (m_nShootDelay % 60 == 0 && (m_state == state_normal || m_state == state_hide))
			{
				D3DXVECTOR3 target = CPlayer::GetPlayer()->GetPos();
				target -= GetPos() + m_cannonRelativePos;
				target.x -= 20.0f;

				if (fabsf(target.x) >= 100.0f)
				{
					D3DXVec3Normalize(&target, &target);
					target.x *= 5.0f;
					target.y *= 5.0f;

					D3DXVECTOR3 P = GetPos() + m_cannonRelativePos;
					P.x -= 20.0f;

					CSpikeBomb* pBullet = CSpikeBomb::Create(P, target);

					CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_CANNON);
				}
			}
		}
	}


	for (int nCnt = 0; nCnt < nGearNum; nCnt++)
	{
		if (m_pGear[nCnt] != nullptr)
		{
			m_pGear[nCnt]->SetPos(GetPos() + m_gearRelativePos[nCnt]);
		}
	}

	for (int nCnt = 0; nCnt < nPipeNum; nCnt++)
	{
		if (m_pPipe[nCnt] != nullptr)
		{
			m_pPipe[nCnt]->SetPos(GetPos() + m_pipeRelativePos[nCnt]);
		}
	}
	if (m_pCannon != nullptr)
	{
		m_pCannon->SetPos(GetPos() + m_cannonRelativePos);
	}

	if (m_pHitbox != nullptr)
	{
		m_pHitbox->SetPos(GetPos());

		if (m_state != state_death)
		{
			if (m_pHitbox->GetHitState())
			{
				m_pHitbox->SetHitState(false);

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
					SetMove(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
					m_nCntState = 0;
					m_nShootDelay = 0;
					m_pHitbox->Release();
					m_pHitbox = nullptr;
					SetLife(0);
					return;
				}
				else
				{
					SetLife(nLife);
				}

				if (m_pHatHitbox == nullptr)
				{
					D3DXVECTOR3 pos = GetPos();
					pos.y -= 100.0f;

					D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					move.x = -0.01f * (float)random(100, 500);
					move.y = -0.01f * (float)random(400, 800);

					int nRand = random(1, 3);

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