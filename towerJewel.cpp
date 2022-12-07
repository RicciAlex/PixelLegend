//=============================================================================
//
// towerJewel.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "towerJewel.h"
#include "circleHitbox.h"
#include "greedBullet.h"
#include "application.h"
#include "sound.h"

//コンストラクタ
CTowerJewel::CTowerJewel()
{
	m_state = state_spawn;

	m_pHitBox = nullptr;
}

//デストラクタ
CTowerJewel::~CTowerJewel()
{

}

//初期化処理
HRESULT CTowerJewel::Init(void)
{
	if (FAILED(CEnemy::Init()))
	{
		return -1;
	}

	m_state = state_wait;

	m_pHitBox = nullptr;

	return S_OK;
}

//終了処理
void CTowerJewel::Uninit(void)
{
	if (m_pHitBox != nullptr)
	{
		m_pHitBox->Release();
		m_pHitBox = nullptr;
	}
}

//更新処理
void CTowerJewel::Update(void)
{
	if (m_pHitBox != nullptr)
	{
		m_pHitBox->SetPos(GetPos());
	}

	switch (m_state)
	{
	case CTowerJewel::state_spawn:

	{
		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		if (pos.x < (float)SCREEN_WIDTH * 0.5f)
		{
			move.x = 2.0f;
		}
		else
		{
			move.x = -2.0f;
		}

		if (pos.x >= 100.0f && move.x > 0.0f || pos.x < (float)SCREEN_WIDTH - 100.0f && move.x < 0.0f)
		{
			move.x = 0.0f;
			m_state = state_shoot;
		}

		SetMove(move);
	}

		break;

	case CTowerJewel::state_shoot:

	{
		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 move = D3DXVECTOR3(4.0f, 0.0f, 0.0f);

		if (pos.x > (float)SCREEN_WIDTH * 0.5f)
		{
			move.x *= -1.0f;
		}

		m_nShootDelay++;

		CGreedBullet* pBullet = nullptr;
		int a = GetPresentAnimPattern();

		if (m_nShootDelay % 30 == 29)
		{
			pBullet = CGreedBullet::Create(pos, move);

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_SHOT);

			if (pBullet != nullptr)
			{
				pBullet->SetTexture(TextureJewel);
				pBullet->SetAnimPattern(a);
				pBullet = nullptr;
			}
		}
		if (m_nShootDelay % 60 == 59)
		{
			move.y = 1.0f;
			pBullet = CGreedBullet::Create(pos, move);

			if (pBullet != nullptr)
			{
				pBullet->SetTexture(TextureJewel);
				pBullet->SetAnimPattern(a);
				pBullet = nullptr;
			}

			move.y = -1.0f;
			pBullet = CGreedBullet::Create(pos, move);

			if (pBullet != nullptr)
			{
				pBullet->SetTexture(TextureJewel);
				pBullet->SetAnimPattern(a);
				pBullet = nullptr;
			}
		}
		if (m_nShootDelay >= 90)
		{
			move.y = 1.0f;
			pBullet = CGreedBullet::Create(pos, move);

			if (pBullet != nullptr)
			{
				pBullet->SetTexture(TextureJewel);
				pBullet->SetAnimPattern(a);
				pBullet = nullptr;
			}

			move.y = -1.0f;
			pBullet = CGreedBullet::Create(pos, move);

			if (pBullet != nullptr)
			{
				pBullet->SetTexture(TextureJewel);
				pBullet->SetAnimPattern(a);
				pBullet = nullptr;
			}

			move.y = 2.0f;
			pBullet = CGreedBullet::Create(pos, move);

			if (pBullet != nullptr)
			{
				pBullet->SetTexture(TextureJewel);
				pBullet->SetAnimPattern(a);
				pBullet = nullptr;
			}

			move.y = -2.0f;
			pBullet = CGreedBullet::Create(pos, move);

			if (pBullet != nullptr)
			{
				pBullet->SetTexture(TextureJewel);
				pBullet->SetAnimPattern(a);
				pBullet = nullptr;
			}

			m_nShootDelay = 0;

			if (pos.x < (float)SCREEN_WIDTH * 0.5f)
			{
				SetMove(D3DXVECTOR3(-2.0f, 0.0f, 0.0f));
			}
			else
			{
				SetMove(D3DXVECTOR3(2.0f, 0.0f, 0.0f));
			}

			m_state = state_despawn;
		}
	}

		break;

	case CTowerJewel::state_despawn:

	{
		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 move = GetMove();

		if (move.x < 0.0f)
		{
			if (pos.x <= -100.0f)
			{
				SetAnimPattern(random(0, 5));
				SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				m_state = state_wait;
			}
		}
		else
		{
			if (pos.x >= (float)SCREEN_WIDTH + 100.0f)
			{
				SetAnimPattern(random(0, 5));
				SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				m_state = state_wait;
			}
		}
	}

		break;

	case CTowerJewel::state_wait:
		break;

	default:
		break;
	}

	CObject_2D::Update();
}

void CTowerJewel::SetState(CTowerJewel::state state)
{
	m_state = state;
}


//生成処理
CTowerJewel* CTowerJewel::Create(const D3DXVECTOR3 pos)
{
	CTowerJewel* pEnemy = new CTowerJewel;

	if (FAILED(pEnemy->Init()))
	{
		return nullptr;
	}

	pEnemy->SetPos(pos);
	pEnemy->SetSize(D3DXVECTOR2(50.0f, 36.8f));
	pEnemy->SetTexture(CObject::TextureJewel);
	pEnemy->SetTextureParameter(1, 3, 2, INT_MAX);
	pEnemy->SetAnimPattern(random(0, 5));
	pEnemy->SetStartingRot(D3DX_PI * 0.5f);

	pEnemy->m_pHitBox = CCircleHitbox::Create(pos, 30.0f, CHitbox::Type_Enemy);

	return pEnemy;
}