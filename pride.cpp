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
	{
		return -1;
	}

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
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}

	if (m_pLife != nullptr)
	{
		m_pLife->Release();
		m_pLife = nullptr;
	}

	CEnemy::Uninit();
}

//更新処理
void CPride::Update(void)
{
	CObject_2D::Update();

	if (m_pHitbox != nullptr)
	{
		m_pHitbox->SetPos(GetPos());

		if (m_pHitbox->GetHitState())
		{
			m_pHitbox->SetHitState(false);

			int nLife = GetLife();
			int nDamage = CPlayer::GetPlayer()->GetAttack();
			nLife -= nDamage;

			if (nLife <= 0)
			{
				m_state = state_Death;
				SetAnimPattern(4);
				m_nCntMove = 0;
				m_nPhase = 0;
				m_fAngleMove = 0;
				SetMove(D3DXVECTOR3(0.0f, 3.0f, 0.0f));
				m_pHitbox->Release();
				m_pHitbox = nullptr;
				SetLife(0);
			}
			else
			{
				SetLife(nLife);

				if (m_pLife != nullptr)
				{
					m_pLife->SubtractLife(nDamage);
				}
			}
		}
	}

	switch (m_state)
	{
	case state_Spawn:

	{
		D3DXVECTOR3 pos = GetPos();

		if (pos.y >= 180.0f)
		{
			SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_LAUGH);
			m_state = state_LaughAnim;
			SetAnimPattern(1);
		}
	}

		break;

	case state_Normal:

	{
		
		m_state = state_BouncingBall;
	}

		break;

	case state_Hide:

	{
		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		if (pos.x >= (float)SCREEN_WIDTH * 0.5f)
		{
			move.x += 5.0f;
		}
		else
		{
			move.x += -5.0f;
		}
		if (pos.y >= (float)SCREEN_HEIGHT * 0.5f)
		{
			move.y += 5.0f;
		}
		else
		{
			move.y += -5.0f;
		}

		if (pos.x >= (float)SCREEN_WIDTH + 200.0f || pos.x <= -200.0f || pos.y >= (float)SCREEN_HEIGHT + 200.0f || pos.y <= -200.0f)
		{
			move.x = 0.0f;
			move.y = 3.0f;
			m_state = state_Spawn;
			SetPos(D3DXVECTOR3(1000.0f, -180.0f, 0.0f));
		}
			SetMove(move);

	}

	break;

	case state_BouncingBall:

	{
		m_nShootDelay++;

		if (m_nShootDelay == 10)
		{
			SetAnimPattern(3);
		}
		else if (m_nShootDelay == 55)
		{
			SetAnimPattern(4);
		}

		if (m_nShootDelay >= 60)
		{
			m_nShootDelay = 0;

			for (int nCnt = 0; nCnt < 3; nCnt++)
			{
				D3DXVECTOR3 PlayerPos = CPlayer::GetPlayer()->GetPos();
				D3DXVECTOR3 Target = PlayerPos - D3DXVECTOR3(GetPos().x, GetPos().y + 90.0f, 0.0f);
				D3DXVec3Normalize(&Target, &Target);
				D3DXVECTOR3 V = D3DXVECTOR3((float)random(-5000, 5000), (float)random(-5000, 5000), 0.0f);
				D3DXVec3Normalize(&V, &V);
				Target += V;
				D3DXVec3Normalize(&Target, &Target);
				Target.x *= 6.0f;
				Target.y *= 6.0f;

				CBouncingBullet* pBullet = CBouncingBullet::Create(D3DXVECTOR3(GetPos().x, GetPos().y + 90.0f, 0.0f), Target);								
			}

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_SHOT);

			m_nPhase++;
		}

		if (m_nPhase >= 10)
		{
			m_nShootDelay = 0;
			m_nPhase = 0;
			SetAnimPattern(0);
			m_state = state_Hide;
		}
	}

		break;

	case state_Star:

		//ricordare di controllare che sia fuori dallo schermo quando si inizia

	{
		m_nCntMove++;

		if (m_nCntMove >= m_nSpawnFrame)
		{
			m_nSpawnFrame = random(40, 150);

			CStarBullet* pBullet = CStarBullet::Create(GetPos(), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_STAR_BULLET);

			m_nCntMove = 0;
		}

		if (GetPos().x < -201.0f || GetPos().x > 1481.0f)
		{
			D3DXVECTOR3 move = GetMove();
			move.x *= -1.0f;
			SetMove(move);
			D3DXVECTOR3 pos = D3DXVECTOR3(GetPos().x, CPlayer::GetPlayer()->GetPos().y, 0.0f);
			SetPos(pos);
			m_nPhase++;

			if (m_nPhase >= 5)
			{
				m_nPhase = 0;
				m_state = state_Hide;
			}
		}
	}

		break;

	case state_CreateEnemy:

	{
		m_nCntMove++;

		if (m_nCntMove % 80 == 79)
		{
			SetAnimPattern(4);
		}

		if (m_nCntMove >= 100)
		{
			CBalloonEnemy* pEnemy = CBalloonEnemy::Create(D3DXVECTOR3(GetPos().x, GetPos().y + 90.0f, 0.0f));

			SetAnimPattern(0);

			m_nCntMove = 0;

			m_nPhase++;

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_BALLOON_POP);

			if (m_nPhase >= 7)
			{
				m_nPhase = 0;
				m_state = state_Hide;
			}
		}
	}

		break;

	case state_LaughAttack:

		//ricordarsi di cambiare la cella della texture quando si cambia lo stato
	{
		m_nCntMove++;

		if (m_nCntMove % 20 == 19)
		{
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
		{
			m_nCntMove = 0;

			D3DXVECTOR3 PlayerPos = CPlayer::GetPlayer()->GetPos();
			D3DXVECTOR3 Target = PlayerPos - D3DXVECTOR3(GetPos().x, GetPos().y + 90.0f, 0.0f);
			D3DXVec3Normalize(&Target, &Target);
			Target.x *= 5.0f;
			Target.y *= 5.0f;

			CLaughBullet* pBullet = CLaughBullet::Create(D3DXVECTOR3(GetPos().x, GetPos().y + 90.0f, 0.0f), Target);

			m_nPhase++;

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_LAUGH);

			if (m_nPhase >= 15)
			{
				m_nPhase = 0;
				SetAnimPattern(0);
				m_state = state_Hide;
			}
		}
	}

		break;

	case state_Balloon:

	{
		D3DXVECTOR3 pos = GetPos();

		if (pos.y <= -150.0f)
		{
			SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

			m_nCntMove++;

			if (m_nCntMove >= 20)
			{
				m_nCntMove = 0;

				D3DXVECTOR3 PlayerPos = CPlayer::GetPlayer()->GetPos();

				int nMax = 1;

				if (PlayerPos.y >= (float)SCREEN_HEIGHT * 0.34f && PlayerPos.y < (float)SCREEN_HEIGHT * 0.67f)
				{
					nMax = 2;
				}
				else if (PlayerPos.y >= (float)SCREEN_HEIGHT * 0.67f)
				{
					nMax = 3;
				}

				for (int nCnt = 0; nCnt < nMax; nCnt++)
				{
					D3DXVECTOR3 move = D3DXVECTOR3(random(-100, 100) * 0.05f, random(50, 100) * 0.05f, 0.0f);
					int nColor = random(0, 5);
					D3DXCOLOR col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

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

					CBalloonBullet* pBullet = CBalloonBullet::Create(D3DXVECTOR3(PlayerPos.x, -15.0f, 0.0f), move, col);
				}

				m_nPhase++;

				if (m_nPhase >= 15)
				{
					m_nPhase = 0;
					m_state = state_Hide;
				}
			}
		}
	}

		break;

	case state_LaughAnim:

	{
		m_nCntMove++;

		if (m_nCntMove % 8 == 0)
		{
			if (GetPresentAnimPattern() == 1)
			{
				SetAnimPattern(2);
			}
			else if(GetPresentAnimPattern() == 2)
			{
				SetAnimPattern(1);
			}
		}

		if (m_nCntMove >= 91)
		{
			SetAnimPattern(0);
			m_nCntMove = 0;

			int nSelect = random(3, 7);

			switch (nSelect)
			{
			case state_BouncingBall:

				SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				m_state = state_BouncingBall;

				break;

			case state_Star:

				SetMove(D3DXVECTOR3(-8.0f, 0.0f, 0.0f));
				m_state = state_Star;

				break;

			case state_LaughAttack:

				SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				SetAnimPattern(1);
				m_state = state_LaughAttack;

				break;

			case state_CreateEnemy:

				SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				m_state = state_CreateEnemy;

				break;

			case state_Balloon:

				SetMove(D3DXVECTOR3(0.0f, -2.0f, 0.0f));
				m_state = state_Balloon;

				break;
			}
		}
	}

		break;

	case state_Death:

	{
		if (m_nPhase == 0)
		{
			m_nCntMove++;

			if (m_nCntMove % 30 < 20)
			{
				D3DXVECTOR2 size = GetSize();
				size.x -= 0.5f;
				size.y -= 0.5f;
				SetSize(size);
			}
			if (m_nCntMove >= 92)
			{
				m_nPhase++;
				m_nCntMove = 0;
				SetAcceleration(D3DXVECTOR3(0.0f, -0.5f, 0.0f));
				SetRotation(D3DX_PI * 0.2f);
			}
		}
		else
		{
			D3DXVECTOR3 pos = GetPos();
			pos.x += 3.0f * sinf(m_fAngleMove);
			SetPos(pos);
			m_fAngleMove += D3DX_PI * 0.05f;

			if (pos.y <= -200.0f)
			{
				m_bEnd = true;
			}
		}
	}

		break;

	default:

		break;
	}
}

//描画処理
void CPride::Draw(void)
{
	CEnemy::Draw();
}

const bool CPride::GetEnd(void)
{
	return m_bEnd;
}




//生成処理
CPride* CPride::Create(void)
{
	CPride* pEnemy = new CPride;

	if (FAILED(pEnemy->Init()))
	{
		return nullptr;
	}

	pEnemy->SetPos(D3DXVECTOR3(1000.0f, -180.0f, 0.0f));
	pEnemy->SetMove(D3DXVECTOR3(0.0f, 1.5f, 0.0f));
	pEnemy->SetSize(D3DXVECTOR2(140.0f, 140.0f));
	pEnemy->SetStartingRot(D3DX_PI * 0.5f);
	pEnemy->SetLife(25000);

	pEnemy->m_pHitbox = CCircleHitbox::Create(D3DXVECTOR3(500.0f, 300.0f, 0.0f), 125.0f, CHitbox::Type_Enemy);

	pEnemy->m_pLife = CEnemyLife::Create(D3DXVECTOR3(900.0f, 40.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.75f, 0.4f), 25000, "pride");

	return pEnemy;
}