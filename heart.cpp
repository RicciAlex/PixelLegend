//=============================================================================
//
// heart.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "heart.h"
#include "squareHitbox.h"
#include "heartBullet.h"
#include "player.h"
#include "enemyLife.h"

//コンストラクタ
CHeart::CHeart()
{
	m_fAngleShoot = 0.0f;
	m_state = state_spawn;

	m_bEnd = false;

	m_pLife = nullptr;
	m_pHitbox = nullptr;
}

//デストラクタ
CHeart::~CHeart()
{

}

//初期化処理
HRESULT CHeart::Init(void)
{
	if (FAILED(CEnemy::Init()))
	{
		return -1;
	}

	m_fAngleShoot = 0.0f;
	m_state = state_spawn;
	m_bEnd = false;

	m_pLife = nullptr;
	m_pHitbox = nullptr;

	return S_OK;
}

//終了処理
void CHeart::Uninit(void)
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
void CHeart::Update(void)
{
	UpdateState();

	CObject_2D::Update();

	if (m_pHitbox != nullptr)
	{
		if (m_pHitbox->GetHitState())
		{
			m_pHitbox->SetHitState(false);

			int nDamage = CPlayer::GetPlayer()->GetAttack();

			int nLife = GetLife();

			nLife -= nDamage;

			if (m_pLife != nullptr)
			{
				m_pLife->SubtractLife(nDamage);
			}

			if (nLife <= 0)
			{
				m_state = state_death;
				m_pHitbox->Release();
				m_pHitbox = nullptr;
				SetLife(0);
				m_nCntMove = 0;
			}
			else
			{
				SetLife(nLife);
			}
		}
	}
}

//描画処理
void CHeart::Draw(void)
{
	CObject_2D::Draw();
}

void CHeart::SetActive(void)
{
	m_state = state_awake;
	SetMove(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
}

const bool CHeart::GetEnd(void)
{
	return m_bEnd;
}






//生成処理
CHeart* CHeart::Create(void)
{
	CHeart* pEnemy = new CHeart;

	if (FAILED(pEnemy->Init()))
	{
		return nullptr;
	}

	pEnemy->SetPos(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, 150.0f, 0.0f));
	pEnemy->SetSize(D3DXVECTOR2(70.0f, 103.6f));
	pEnemy->SetStartingRot(D3DX_PI * 0.5f);
	pEnemy->SetTexture(CObject::TextureGluttonyHeart);
	pEnemy->SetTextureParameter(2, 2, 1, 20);
	pEnemy->SetPriority(2);
	pEnemy->SetLife(10000);

	pEnemy->m_pLife = CEnemyLife::Create(D3DXVECTOR3(850.0f, 40.0f, 0.0f), D3DXCOLOR(0.0f, 1.0f, 0.3f, 0.5f), 10000, "gluttony");

	return pEnemy;
}




void CHeart::UpdateState(void)
{
	switch (m_state)
	{
	case CHeart::state_spawn:

	{
		m_nCntMove++;

		if (m_nCntMove == 30)
		{
			SetMove(D3DXVECTOR3(0.0f, -1.0f, 0.0f));
		}

		if (GetPos().y <= -150.0f)
		{
			SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			m_nCntMove = 0;
			m_state = state_sleep;
		}
	}

		break;

	case CHeart::state_awake:

	{
		if (GetPos().y >= 150.0f)
		{
			SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			m_state = state_vulnerable;

			if (m_pHitbox == nullptr)
			{
				m_pHitbox = CSquareHitbox::Create(GetPos(), D3DXVECTOR2(40.0f, 70.0f), CHitbox::Type_Enemy);
			}
		}
	}

		break;

	case CHeart::state_vulnerable:

	{
		m_nShootDelay++;

		if (m_nShootDelay % 90 == 30)
		{
			CHeartBullet* pBullet = nullptr;

			for (int nCnt = 0; nCnt < 6; nCnt++)
			{
				D3DXVECTOR3 move = D3DXVECTOR3(5.0f * (cosf(nCnt * (D3DX_PI / 6)) * cosf(m_fAngleShoot) + sinf(nCnt * (D3DX_PI / 6)) * sinf(m_fAngleShoot)),
					5.0f * (sinf((nCnt * (D3DX_PI / 6))) * cosf(m_fAngleShoot) - cosf(nCnt * (D3DX_PI / 6)) * sinf(m_fAngleShoot)), 0.0f);

				pBullet = CHeartBullet::Create(GetPos(), move, D3DXCOLOR(1.0f, 0.51f, 0.5f, 0.75f));
				pBullet->SetLife(90);
			}

			m_fAngleShoot -= D3DX_PI * 0.05f;

			if (m_fAngleShoot <= -D3DX_PI * 0.17f)
			{
				m_fAngleShoot = 0.0f;
			}

			if (m_nShootDelay >= 550)
			{
				m_nShootDelay = 0;
				m_state = state_return;
				SetMove(D3DXVECTOR3(0.0f, -1.0f, 0.0f));
				m_pHitbox->Release();
				m_pHitbox = nullptr;
			}
		}
	}

		break;

	case CHeart::state_return:

	{
		if (GetPos().y <= -150.0f)
		{
			SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			m_nCntMove = 0;
			m_state = state_sleep;
		}
	}

		break;

	case CHeart::state_death:

	{
		m_nCntMove++;

		D3DXCOLOR col = GetColor();

		if (col.r >= 0.25f)
		{
			col.r -= 0.0125f;
			col.g -= 0.0125f;
			col.b -= 0.0125f;

			SetColor(col);
		}
		else
		{
			m_bEnd = true;
		}
	}


		break;

	case CHeart::state_sleep:


		break;

	default:
		break;
	}
}