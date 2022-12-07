//=============================================================================
//
// handFlamethrower.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "handFlamethrower.h"
#include "circleHitbox.h"
#include "handFireball.h"
#include "player.h"
#include "wrath.h"
#include "application.h"
#include "sound.h"

//コンストラクタ
CHandFlamethrower::CHandFlamethrower()
{
	m_state = state_spawn;

	m_pHitbox = nullptr;
	m_pParent = nullptr;
}

//デストラクタ
CHandFlamethrower::~CHandFlamethrower()
{

}

//初期化処理
HRESULT CHandFlamethrower::Init(void)
{
	if(FAILED(CEnemy::Init()))
	{
		return -1;
	}

	m_state = state_spawn;

	m_pHitbox = nullptr;
	m_pParent = nullptr;

	return S_OK;
}

//終了処理
void CHandFlamethrower::Uninit(void)
{
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}

	if (m_pParent != nullptr)
	{
		m_pParent = nullptr;
	}

	CEnemy::Uninit();
}

//更新処理
void CHandFlamethrower::Update(void)
{
	CObject_2D::Update();

	if (m_pHitbox != nullptr)
	{
		m_pHitbox->SetPos(GetPos());

		if (m_pHitbox->GetHitState())
		{
			m_pHitbox->SetHitState(false);

			int nDamage = CPlayer::GetPlayer()->GetAttack();

			if (m_pParent != nullptr)
			{
				m_pParent->Damage(nDamage);
			}
		}
	}

	if (m_pParent != nullptr)
	{
		if (m_pParent->GetDeath() && m_state != state_death)
		{
			m_state = state_death;
			SetMove(D3DXVECTOR3(0.0f, 2.0f, 0.0f));
			m_nPhase = 0;
		}
	}

	updateState();
}


void CHandFlamethrower::SetParent(CWrath* pParent)
{
	m_pParent = pParent;
}






//生成処理
CHandFlamethrower* CHandFlamethrower::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CHandFlamethrower* pEnemy = new CHandFlamethrower;

	if (FAILED(pEnemy->Init()))
	{
		return nullptr;
	}

	pEnemy->SetPos(pos);
	pEnemy->SetMove(move);
	pEnemy->SetStartingRot(D3DX_PI * 0.5f);
	pEnemy->SetSize(D3DXVECTOR2(120.0f, 80.0f));
	pEnemy->SetTexture(CObject::TextureHand);
	pEnemy->SetTextureParameter(1, 4, 2, INT_MAX);
	pEnemy->SetAnimPattern(1);
	pEnemy->SetPriority(2);

	if (pos.x <= 0.0f)
	{
		pEnemy->FlipX();
	}

	pEnemy->m_pHitbox = CCircleHitbox::Create(pos, 75.0f, CHitbox::Type_Enemy);

	return pEnemy;
}





void CHandFlamethrower::updateState(void)
{
	switch (m_state)
	{
	case CHandFlamethrower::state_spawn:

	{
		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 move = GetMove();

		if (move.x >= 0.0f && pos.x >= 100.0f || move.x < 0.0f && pos.x <= (float)SCREEN_WIDTH - 100.0f)
		{
			SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			m_state = state_shoot;
		}
	}

		break;

	case CHandFlamethrower::state_shoot:

	{
		m_nShootDelay++;

		if (m_nShootDelay % 20 == 1)
		{
			D3DXVECTOR3 pos = GetPos();

			if (pos.x < (float)SCREEN_WIDTH * 0.5f)
			{
				CHandFireball::Create(D3DXVECTOR3(pos.x + 100.0f, pos.y - 20.0f, 0.0f), D3DXVECTOR3(4.0f, 2.0f, 0.0f));
			}
			else
			{
				CHandFireball::Create(D3DXVECTOR3(pos.x - 100.0f, pos.y - 20.0f, 0.0f), D3DXVECTOR3(-4.0f, 2.0f, 0.0f));
			}

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_FIRE);
		}

		if (m_nShootDelay >= 300)
		{
			m_nShootDelay = 0;
			m_state = state_return;
		}
	}

		break;

	case CHandFlamethrower::state_return:

	{
		D3DXVECTOR3 pos = GetPos();

		if (pos.x < (float)SCREEN_WIDTH * 0.5f)
		{
			SetMove(D3DXVECTOR3(-2.0f, 0.0f, 0.0f));
		}
		else
		{
			SetMove(D3DXVECTOR3(2.0f, 0.0f, 0.0f));
		}
	}

		break;

	case CHandFlamethrower::state_despawn:

	{
		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 move = GetMove();

		if (move.x >= 0.0f && pos.x >= 100.0f || move.x < 0.0f && pos.x <= (float)SCREEN_WIDTH - 100.0f)
		{
			Release();
			return;
		}
	}

	break;

	case CHandFlamethrower::state_death:

	{
		m_nPhase++;

		if (m_nPhase % 15 == 0)
		{
			D3DXCOLOR col = GetColor();

			if (col.g < 0.5f)
			{
				SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else
			{
				SetColor(D3DXCOLOR(1.0f, 0.3f, 0.3f, 1.0f));
			}
		}
		
	}

	break;

	default:
		break;
	}
}