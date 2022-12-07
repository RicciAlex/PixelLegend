//=============================================================================
//
// handCharger.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "handCharger.h"
#include "squareHitbox.h"
#include "handblade.h"
#include "player.h"
#include "wrath.h"
#include"application.h"
#include "sound.h"

//コンストラクタ
CHandCharger::CHandCharger()
{
	m_targetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_state = state_spawn;

	m_pHitbox = nullptr;
	m_pParent = nullptr;
}

//デストラクタ
CHandCharger::~CHandCharger()
{

}

//初期化処理
HRESULT CHandCharger::Init(void)
{
	if (FAILED(CEnemy::Init()))
	{
		return -1;
	}

	m_targetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_state = state_spawn;

	m_pHitbox = nullptr;
	m_pParent = nullptr;

	return S_OK;
}

//終了処理
void CHandCharger::Uninit(void)
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
void CHandCharger::Update(void)
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
			SetMove(D3DXVECTOR3(5.0f, -5.0f, 0.0f));
			SetAcceleration(D3DXVECTOR3(0.0f, 0.1f, 0.0f));
			SetRotation(D3DX_PI * 0.01f);
			m_nPhase = 0;
		}
	}

	UpdateState();
}


void CHandCharger::SetParent(CWrath* pParent)
{
	m_pParent = pParent;
}






//生成処理
CHandCharger* CHandCharger::Create(D3DXVECTOR3 pos)
{
	CHandCharger* pEnemy = new CHandCharger;

	if (FAILED(pEnemy->Init()))
	{
		return nullptr;
	}

	pEnemy->SetPos(pos);
	pEnemy->SetMove(D3DXVECTOR3(0.0f, 2.0f, 0.0f));
	pEnemy->SetStartingRot(D3DX_PI * 0.5f);
	pEnemy->SetSize(D3DXVECTOR2(120.0f, 80.0f));
	pEnemy->SetTexture(CObject::TextureHand);
	pEnemy->SetTextureParameter(1, 4, 2, INT_MAX);
	pEnemy->SetAnimPattern(5);
	pEnemy->SetPriority(3);

	pEnemy->m_pHitbox = CSquareHitbox::Create(pos, D3DXVECTOR2(75.0f, 20.0f), CHitbox::Type_Enemy);

	return pEnemy;
}





void CHandCharger::UpdateState(void)
{
	D3DXVECTOR3 pos = GetPos();

	switch (m_state)
	{
	case CHandCharger::state_spawn:

	{
		if (m_nPhase == 0)
		{
			if (pos.y >= 100.0f)
			{
				SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				m_nPhase++;
			}
		}
		else if (m_nPhase == 1)
		{
			m_nShootDelay++;

			if (m_nShootDelay >= 30)
			{
				m_nShootDelay = 0;
				m_nPhase = 0;
				m_state = state_attack;
				SetMove(D3DXVECTOR3(0.0f, 20.0f, 0.0f));
				m_targetPos = CPlayer::GetPlayer()->GetPos();
				m_targetPos.x = pos.x;
				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_HAND_WOOSH);
			}
		}
	}

	break;

	case CHandCharger::state_attack:

	{
		if (pos.y >= m_targetPos.y)
		{
			SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			m_state = state_return;
			SetAnimPattern(6);
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_HAND_HIT);
		}
	}

	break;

	case CHandCharger::state_return:

	{
		m_nCntMove++;

		if (m_nCntMove == 60)
		{
			SetMove(D3DXVECTOR3(0.0f, -7.0f, 0.0f));
			m_state = state_despawn;
			SetAnimPattern(5);
		}
	}

	break;

	case CHandCharger::state_despawn:

	{
		if (pos.y <= -100.0f)
		{
			Release();
			return;
		}
	}

	break;

	case CHandCharger::state_death:

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