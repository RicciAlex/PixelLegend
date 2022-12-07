//=============================================================================
//
// Thanatos.h
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "Thanatos.h"
#include "squareHitbox.h"
#include "candle.h"
#include "player.h"
#include "scythe.h"
#include "enemyLife.h"
#include "application.h"
#include "sound.h"

//コンストラクタ
CThanatos::CThanatos()
{
	m_nTargetLife = 0;
	m_nLitCandle = 0;
	m_nCntState = 0;
	m_state = state_Spawn;
	m_bEnd = false;

	for (int nCnt = 0; nCnt < Max_Candle; nCnt++)
	{
		m_pCandle[nCnt] = nullptr;
	}

	m_pLife = nullptr;

	m_pHitbox = nullptr;
}

//デストラクタ
CThanatos::~CThanatos()
{

}

//初期化処理
HRESULT CThanatos::Init(void)
{
	if (FAILED(CEnemy::Init()))
	{
		return -1;
	}

	m_nTargetLife = 4000;
	m_nLitCandle = 0;
	m_nCntState = 0;
	m_state = state_Spawn;
	m_bEnd = false;

	for (int nCnt = 0; nCnt < Max_Candle; nCnt++)
	{
		m_pCandle[nCnt] = nullptr;
	}

	m_pLife = nullptr;

	m_pHitbox = nullptr;

	return S_OK;
}

//終了処理
void CThanatos::Uninit(void)
{
	for (int nCnt = 0; nCnt < Max_Candle; nCnt++)
	{
		if (m_pCandle[nCnt] != nullptr)
		{
			m_pCandle[nCnt]->Release();
			m_pCandle[nCnt] = nullptr;
		}
	}

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
void CThanatos::Update(void)
{
	switch (m_state)
	{
	case CThanatos::state_Spawn:

	{
		D3DXCOLOR col = GetColor();

		col.a += 0.005f;

		if (col.a >= 1.0f)
		{
			col.a = 1.0f;
			m_state = state_Hide;
		}

		SetColor(col);
	}

		break;

	case CThanatos::state_Normal:

		break;

	case CThanatos::state_Hide:

	{
		D3DXCOLOR col = GetColor();

		col.a -= 0.005f;

		if (col.a <= 0.0f)
		{
			col.a = 0.0f;
			m_state = state_ShowEyes;
			SetAnimPattern(1);
		}

		SetColor(col);
	}

		break;

	case CThanatos::state_ShowEyes:

	{
		D3DXCOLOR col = GetColor();

		col.a += 0.005f;

		if (col.a >= 1.0f)
		{
			col.a = 1.0f;
			m_state = state_Hidden;
			m_nShootDelay = 30;
		}

		SetColor(col);
	}

	break;

	case CThanatos::state_Hidden:

	{
		m_nShootDelay--;

		D3DXVECTOR3 target = CPlayer::GetPlayer()->GetPos();
		target -= GetPos();
		D3DXVec3Normalize(&target, &target);
		target.x *= 0.25f;
		target.y *= 0.25f;

		SetMove(target);


		if (m_nShootDelay <= 0)
		{
			m_nShootDelay = 90;

		
			D3DXVec3Normalize(&target, &target);

			target.x *= 4.0f;
			target.y *= 4.0f;

			CScythe* pBullet = CScythe::Create(GetPos(), target);

			/*D3DXVec3Normalize(&target, &target);
			D3DXVECTOR3 speed = target;
			speed.x *= (float)random(2000, 5000) * 0.001f;
			speed.y = (float)random(2000, 4000) * -0.001f;

			pBullet = CScythe::Create(GetPos(), speed);

			pBullet->SetAcceleration(D3DXVECTOR3(0.0f, 0.05f, 0.0f));
			pBullet->AddAngularSpeed(D3DX_PI * 0.05f);*/

			if (GetLife() <= 4000)
			{
				int nMax = 1;

				if (GetLife() <= 2000)
				{
					nMax = 2;
				}

				for (int nCnt = 0; nCnt < nMax; nCnt++)
				{
					D3DXVec3Normalize(&target, &target);

					D3DXVECTOR3 speed = target;
					speed.x *= (float)random(2000, 5000) * 0.001f;
					speed.y = (float)random(2000, 4000) * -0.001f;

					pBullet = CScythe::Create(GetPos(), speed);

					pBullet->SetAcceleration(D3DXVECTOR3(0.0f, 0.05f, 0.0f));
					pBullet->AddAngularSpeed(D3DX_PI * 0.05f);

					if (target.x >= target.y)
					{
						target.x += target.x;
					}
					else
					{
						target.y += target.y;
					}

					D3DXVec3Normalize(&target, &target);
					target.x *= 4.0f;
					target.y *= 4.0f;

					pBullet = CScythe::Create(GetPos(), target);
				}
			}

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_SCYTHE);
		}
		
		if (m_nLitCandle >= 4)
		{
			m_state = state_Vulnerable;
			SetAnimPattern(0);

			if (m_pHitbox == nullptr)
			{
				D3DXVECTOR2 size = GetSize();
				size.x *= 0.7f;
				size.y *= 0.9f;

				m_pHitbox = CSquareHitbox::Create(GetPos(), size, CHitbox::Type_Enemy);
			}
		}
	}

	break;

	case CThanatos::state_Vulnerable:

	{
		m_nShootDelay -= 2;

		SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		if (m_nShootDelay <= 0)
		{
			m_nShootDelay = 90;

			D3DXVECTOR3 target = CPlayer::GetPlayer()->GetPos();
			target -= GetPos();
			D3DXVec3Normalize(&target, &target);
			target.x *= 4.0f;
			target.y *= 4.0f;

			CScythe* pBullet = CScythe::Create(GetPos(), target);

			if (GetLife() <= 4000)
			{
				int nMax = 1;

				if (GetLife() <= 2000)
				{
					nMax = 2;
				}

				for (int nCnt = 0; nCnt < nMax; nCnt++)
				{
					D3DXVec3Normalize(&target, &target);

					D3DXVECTOR3 speed = target;
					speed.x *= (float)random(2000, 5000) * 0.001f;
					speed.y = (float)random(2000, 4000) * -0.001f;

					pBullet = CScythe::Create(GetPos(), speed);

					pBullet->SetAcceleration(D3DXVECTOR3(0.0f, 0.05f, 0.0f));
					pBullet->AddAngularSpeed(D3DX_PI * 0.05f);

					if (target.x >= target.y)
					{
						target.x += target.x;
					}
					else
					{
						target.y += target.y;
					}

					D3DXVec3Normalize(&target, &target);
					target.x *= 4.0f;
					target.y *= 4.0f;

					pBullet = CScythe::Create(GetPos(), target);
				}
			}

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_SCYTHE);
		}

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
				m_state = state_Death;
				m_pHitbox->Release();
				m_pHitbox = nullptr;
			}
			else if(nLife <= m_nTargetLife)
			{
				nLife = m_nTargetLife;
				m_nTargetLife -= 2000;
				SetLife(nLife);

				for (int nCnt = 0; nCnt < Max_Candle; nCnt++)
				{
					m_pCandle[nCnt]->Unlit();
				}

				m_pHitbox->Release();
				m_pHitbox = nullptr;
				m_nLitCandle = 0;
				m_state = state_Hide;
			}
			else
			{
				SetLife(nLife);
			}
		}
	}

	break;

	case CThanatos::state_Death:

	{
		D3DXCOLOR col = GetColor();

		col.a -= 0.005f;

		if (col.a <= 0.0f)
		{
			col.a = 0.0f;

			m_bEnd = true;
		}

		SetColor(col);

		for (int nCnt = 0; nCnt < Max_Candle; nCnt++)
		{
			m_pCandle[nCnt]->Despawn();
		}
	}

	break;
	
	default:
		break;
	}

	if (m_state != state_Spawn && m_state != state_Death)
	{
		D3DXVECTOR3 PlayerPos = CPlayer::GetPlayer()->GetPos();
		D3DXVECTOR3 pos = GetPos();

		if (PlayerPos.x < pos.x && GetFlipX() || PlayerPos.x > pos.x && !GetFlipX())
		{
			FlipX();
		}

		pos.y += 0.20f * sinf(m_fAngleMove);
		m_fAngleMove += D3DX_PI * 0.015f;

		SetPos(pos);
	}
	

	if (m_pHitbox != nullptr)
	{
		m_pHitbox->SetPos(GetPos());
	}

	CObject_2D::Update();
}

//描画処理
void CThanatos::Draw(void)
{
	CObject_2D::Draw();
}

const bool CThanatos::GetEnd(void)
{
	return m_bEnd;
}

void CThanatos::SetBgPointer(CBg* pPointer)
{
	m_pBg = pPointer;

	for (int nCnt = 0; nCnt < Max_Candle; nCnt++)
	{
		m_pCandle[nCnt]->SetBgPointer(m_pBg);
	}
}

void CThanatos::AddLitCandle(void)
{
	m_nLitCandle++;
}





//生成処理
CThanatos* CThanatos::Create(void)
{
	CThanatos* pEnemy = new CThanatos;

	if (FAILED(pEnemy->Init()))
	{
		return nullptr;
	}

	pEnemy->SetPos(D3DXVECTOR3(900.0f, 250.0f, 0.0f));
	pEnemy->SetStartingRot(D3DX_PI * 0.5f);
	pEnemy->SetTexture(CObject::TextureThanatos);
	pEnemy->SetTextureParameter(1, 2, 1, INT_MAX);
	pEnemy->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	pEnemy->SetSize(D3DXVECTOR2(100.0f, 182.4f));
	pEnemy->SetLife(6000);

	pEnemy->m_pCandle[0] = CCandle::Create(D3DXVECTOR3(160.0f, 100.0f, 0.0f));
	pEnemy->m_pCandle[1] = CCandle::Create(D3DXVECTOR3(160.0f, (float)SCREEN_HEIGHT - 100.0f, 0.0f));
	pEnemy->m_pCandle[2] = CCandle::Create(D3DXVECTOR3((float)SCREEN_WIDTH - 152.5f, 100.0f, 0.0f));
	pEnemy->m_pCandle[3] = CCandle::Create(D3DXVECTOR3((float)SCREEN_WIDTH - 152.5f, (float)SCREEN_HEIGHT - 100.0f, 0.0f));

	for (int nCnt = 0; nCnt < CThanatos::Max_Candle; nCnt++)
	{
		pEnemy->m_pCandle[nCnt]->SetParent(pEnemy);
	}

	pEnemy->m_pLife = CEnemyLife::Create(D3DXVECTOR3(800.0f, 40.0f, 0.0f), D3DXCOLOR(8.0f, 0.8f, 0.8f, 0.5f), 6000, "thanatos");
	
	return pEnemy;
}