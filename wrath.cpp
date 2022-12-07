//=============================================================================
//
// wrath.cpp
// Author : Ricci Alex
//
//=============================================================================

//インクルードファイル
#include "wrath.h"
#include "enemyWrathBody.h"
#include "handFlamethrower.h"
#include "handGun.h"
#include "handCharger.h"
#include "player.h"
#include "enemyLife.h"

//コンストラクタ
CWrath::CWrath()
{
	m_bEnd = false;
	m_bDeath = false;
	m_pBody = nullptr;
	m_pLife = nullptr;
}

//デストラクタ
CWrath::~CWrath()
{

}

//初期化処理
HRESULT CWrath::Init(void)
{
	if (FAILED(CEnemy::Init()))
	{
		return -1;
	}

	m_bEnd = false;
	m_bDeath = false;
	m_pBody = nullptr;
	m_pLife = nullptr;

	return S_OK;
}

//終了処理
void CWrath::Uninit(void)
{
	if (m_pBody != nullptr)
	{
		m_pBody->Release();
		m_pBody = nullptr;
	}

	if (m_pLife != nullptr)
	{
		m_pLife->Release();
		m_pLife = nullptr;
	}

	CEnemy::Uninit();
}

//更新処理
void CWrath::Update(void)
{
	int nLife = GetLife();
	D3DXVECTOR3 playerPos = CPlayer::GetPlayer()->GetPos();


	if (nLife <= 0)
	{
		m_bDeath = true;
	}

	if (m_pBody != nullptr)
	{
		if (m_pBody->GetDeath())
		{
			m_pBody->Release();
			m_pBody = nullptr;
		}
	}
	else
	{
		m_nShootDelay++;

		if (m_nShootDelay >= 500)
		{
			if (nLife >= 12500)
			{
				int nSelect = random(0, 200);

				if (nSelect < 50)
				{
					CHandFlamethrower* pEnemy = CHandFlamethrower::Create(D3DXVECTOR3(-100.0f, playerPos.y, 0.0f), D3DXVECTOR3(2.0f, 0.0f, 0.0f));
					pEnemy->SetParent(this);
				}
				else if (nSelect >= 50 && nSelect < 100)
				{
					CHandFlamethrower* pEnemy = CHandFlamethrower::Create(D3DXVECTOR3((float)SCREEN_WIDTH + 100.0f, playerPos.y, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f));
					pEnemy->SetParent(this);
				}
				else if (nSelect >= 100 && nSelect < 150)
				{
					CHandGun* pEnemy = CHandGun::Create(D3DXVECTOR3(-100.0f, playerPos.y, 0.0f), D3DXVECTOR3(2.0f, 0.0f, 0.0f));
					pEnemy->SetParent(this);
				}
				else
				{
					CHandGun* pEnemy = CHandGun::Create(D3DXVECTOR3((float)SCREEN_WIDTH + 100.0f, playerPos.y, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f));
					pEnemy->SetParent(this);
				}
			}
			else if (nLife < 12500 && nLife >= 10000)
			{
				int nSelect = random(0, 100);

				if (nSelect < 50)
				{
					CHandFlamethrower* pEnemy = CHandFlamethrower::Create(D3DXVECTOR3(-100.0f, playerPos.y, 0.0f), D3DXVECTOR3(2.0f, 0.0f, 0.0f));
					pEnemy->SetParent(this);
					CHandGun* pEnemy2 = CHandGun::Create(D3DXVECTOR3((float)SCREEN_WIDTH + 100.0f, playerPos.y, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f));
					pEnemy2->SetParent(this);
				}
				else
				{
					CHandFlamethrower* pEnemy = CHandFlamethrower::Create(D3DXVECTOR3((float)SCREEN_WIDTH + 100.0f, playerPos.y, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f));
					pEnemy->SetParent(this);
					CHandGun* pEnemy2 = CHandGun::Create(D3DXVECTOR3(-100.0f, playerPos.y, 0.0f), D3DXVECTOR3(2.0f, 0.0f, 0.0f));
					pEnemy2->SetParent(this);
				}
			}
			else
			{
				int nSelect = random(0, 100);

				if (nSelect < 50)
				{
					CHandFlamethrower* pEnemy = CHandFlamethrower::Create(D3DXVECTOR3(-100.0f, playerPos.y, 0.0f), D3DXVECTOR3(2.0f, 0.0f, 0.0f));
					pEnemy->SetParent(this);
					CHandGun* pEnemy2 = CHandGun::Create(D3DXVECTOR3((float)SCREEN_WIDTH + 100.0f, playerPos.y, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f));
					pEnemy2->SetParent(this);
				}
				else
				{
					CHandFlamethrower* pEnemy = CHandFlamethrower::Create(D3DXVECTOR3((float)SCREEN_WIDTH + 100.0f, playerPos.y, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f));
					pEnemy->SetParent(this);
					CHandGun* pEnemy2 = CHandGun::Create(D3DXVECTOR3(-100.0f, playerPos.y, 0.0f), D3DXVECTOR3(2.0f, 0.0f, 0.0f));
					pEnemy2->SetParent(this);
				}

				CHandCharger* pEnemy = CHandCharger::Create(D3DXVECTOR3(playerPos.x, -100.0f, 0.0f));
				pEnemy->SetParent(this);
			}

			m_nShootDelay = 0;
		}
	}

	if (m_bDeath)
	{
		m_nCntMove++;

		if (m_nCntMove >= 60)
		{
			m_bEnd = true;
		}
	}
}

void CWrath::Draw(void)
{
	CObject_2D::Draw();
}



const bool CWrath::GetEnd(void)
{
	return m_bEnd;
}

const bool CWrath::GetDeath(void)
{
	return m_bDeath;
}

void CWrath::Damage(const int nDamage)
{
	int nLife = GetLife();

	if (nLife > 0)
	{
		SetLife(nLife - nDamage);

		if (m_pLife != nullptr)
		{
			m_pLife->SubtractLife(nDamage);
		}
	}
}






//生成処理
CWrath* CWrath::Create(void)
{
	CWrath* pEnemy = new CWrath;

	if (FAILED(pEnemy->Init()))
	{
		return nullptr;
	}

	pEnemy->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pEnemy->SetSize(D3DXVECTOR2(0.0f, 0.0f));
	pEnemy->SetLife(30000);
	pEnemy->SetTexture(CObject::TextureNull);
	pEnemy->SetTextureParameter(1, 1, 1, INT_MAX);

	pEnemy->m_pBody = CWrathBody::Create(D3DXVECTOR3(1400.0f, 350.0f, 0.0f));
	
	if (pEnemy->m_pBody != nullptr)
	{
		pEnemy->m_pBody->SetParent(pEnemy);
	}

	pEnemy->m_nShootDelay = 440;

	pEnemy->m_pLife = CEnemyLife::Create(D3DXVECTOR3(900.0f, 40.0f, 0.0f), D3DXCOLOR(0.0f, 1.0f, 0.5f, 0.4f), 30000, "wrath");

	return pEnemy;
}

