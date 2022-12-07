//=============================================================================
//
// handGun.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "handGun.h"
#include "circleHitbox.h"
#include "handblade.h"
#include "player.h"
#include "wrath.h"
#include "application.h"
#include "sound.h"

//コンストラクタ
CHandGun::CHandGun()
{
	m_state = state_spawn;

	m_pHitbox = nullptr;
	m_pParent = nullptr;
}

//デストラクタ
CHandGun::~CHandGun()
{

}

//初期化処理
HRESULT CHandGun::Init(void)
{
	if (FAILED(CEnemy::Init()))
	{
		return -1;
	}

	m_state = state_spawn;

	m_pHitbox = nullptr;
	m_pParent = nullptr;

	return S_OK;
}

//終了処理
void CHandGun::Uninit(void)
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
void CHandGun::Update(void)
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
			m_nPhase = 0;
			SetMove(D3DXVECTOR3(0.0f, 2.0f, 0.0f));
		}
	}

	UpdateState();
}


void CHandGun::SetParent(CWrath* pParent)
{
	m_pParent = pParent;
}






//生成処理
CHandGun* CHandGun::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CHandGun* pEnemy = new CHandGun;

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
	pEnemy->SetAnimPattern(2);
	pEnemy->SetPriority(3);

	if (pos.x <= 0.0f)
	{
		pEnemy->FlipX();
	}

	pEnemy->m_pHitbox = CCircleHitbox::Create(pos, 60.0f, CHitbox::Type_Enemy);

	return pEnemy;
}





void CHandGun::UpdateState(void)
{
	switch (m_state)
	{
	case CHandGun::state_spawn:

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

	case CHandGun::state_shoot:

	{
		m_nShootDelay++;

		if (m_nShootDelay % 20 == 1)
		{
			D3DXVECTOR3 pos = GetPos();

			D3DXVECTOR3 move, newMove;
			float fAdd = 100.0f;

			move = CPlayer::GetPlayer()->GetPos() - pos;
			D3DXVec3Normalize(&move, &move);

			D3DXVECTOR3 unit = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

			float fAngle = acosf(D3DXVec3Dot(&move, &unit));

			if (CPlayer::GetPlayer()->GetPos().y < pos.y)
			{
				fAngle *= -1.0f;
			}

			if (pos.x > (float)SCREEN_WIDTH * 0.5f)
			{
				fAdd *= -1.0f;
			}

			newMove = D3DXVECTOR3(cosf(fAngle) * cosf(D3DX_PI / 18.0f) - sinf(fAngle) * sinf(D3DX_PI / 18.0f),
				sinf(fAngle) * cosf(D3DX_PI / 18.0f) + cosf(fAngle) * sinf(D3DX_PI / 18.0f), 0.0f);

			CHandBlade::Create(D3DXVECTOR3(pos.x + fAdd, pos.y - 20.0f, 0.0f), D3DXVECTOR3(5.0f * newMove.x, 5.0f * newMove.y, 0.0f));

			newMove = D3DXVECTOR3(cosf(fAngle) * cosf(-D3DX_PI / 18.0f) - sinf(fAngle) * sinf(-D3DX_PI / 18.0f),
				sinf(fAngle) * cosf(-D3DX_PI / 18.0f) + cosf(fAngle) * sinf(-D3DX_PI / 18.0f), 0.0f);

			CHandBlade::Create(D3DXVECTOR3(pos.x + fAdd, pos.y - 20.0f, 0.0f), D3DXVECTOR3(5.0f * newMove.x, 5.0f * newMove.y, 0.0f));

			newMove = D3DXVECTOR3(cosf(fAngle) * cosf(D3DX_PI / 12.0f) - sinf(fAngle) * sinf(D3DX_PI / 12.0f),
				sinf(fAngle) * cosf(D3DX_PI / 12.0f) + cosf(fAngle) * sinf(D3DX_PI / 12.0f), 0.0f);

			CHandBlade::Create(D3DXVECTOR3(pos.x + fAdd, pos.y - 20.0f, 0.0f), D3DXVECTOR3(5.0f * newMove.x, 5.0f * newMove.y, 0.0f));

			newMove = D3DXVECTOR3(cosf(fAngle) * cosf(-D3DX_PI / 12.0f) - sinf(fAngle) * sinf(-D3DX_PI / 12.0f),
				sinf(fAngle) * cosf(-D3DX_PI / 12.0f) + cosf(fAngle) * sinf(-D3DX_PI / 12.0f), 0.0f);

			CHandBlade::Create(D3DXVECTOR3(pos.x + fAdd, pos.y - 20.0f, 0.0f), D3DXVECTOR3(5.0f * newMove.x, 5.0f * newMove.y, 0.0f));

			CHandBlade::Create(D3DXVECTOR3(pos.x + fAdd, pos.y - 20.0f, 0.0f), D3DXVECTOR3(5.0f * move.x, 5.0f * move.y, 0.0f));

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_SHOT);
		}

		if (m_nShootDelay >= 180)
		{
			m_nShootDelay = 0;
			m_state = state_return;
		}
	}

	break;

	case CHandGun::state_return:

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

	case CHandGun::state_despawn:

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

	case CHandGun::state_death:

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