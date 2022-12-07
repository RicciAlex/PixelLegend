//=============================================================================
//
// skeleton.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "skeleton.h"
#include "squareHitbox.h"
#include "player.h"
#include "bone.h"

//コンストラクタ
CSkeleton::CSkeleton()
{
	m_state = state_spawn;
	m_type = type_legs;
	m_fTaget = 0.0f;

	m_pHitbox = nullptr;
}

//デストラクタ
CSkeleton::~CSkeleton()
{

}

//初期化処理
HRESULT CSkeleton::Init(void)
{
	if (FAILED(CEnemy::Init()))
	{
		return -1;
	}

	m_state = state_spawn;
	m_type = type_legs;
	m_fTaget = 0.0f;

	m_pHitbox = nullptr;

	return S_OK;
}

//終了処理
void CSkeleton::Uninit(void)
{
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}

	CEnemy::Uninit();
}

//更新処理
void CSkeleton::Update(void)
{
	CObject_2D::Update();

	if (m_pHitbox != nullptr)
	{
		m_pHitbox->SetPos(GetPos());

		if (m_pHitbox->GetHitState())
		{
			m_pHitbox->SetHitState(false);

			int nLife = GetLife();
			nLife -= CPlayer::GetPlayer()->GetAttack();

			if (nLife <= 0)
			{
				int nRand = random(1, 3);

				for (int nCnt = 0; nCnt < nRand; nCnt++)
				{
					D3DXVECTOR3 move = D3DXVECTOR3((float)random(-1000, 1000), (float)random(-1000, 1000), 0.0f);

					if (move.x == 0.0f && move.y == 0.0f)
					{
						move.x = 1.0f;
					}

					D3DXVec3Normalize(&move, &move);
					move.x *= 3.0f;
					move.y *= 3.0f;

					CBone::Create(GetPos(), move);
				}

				Release();
				return;
			}
			else
			{
				SetLife(nLife);
			}
		}
	}

	UpdateMove();
}

//描画処理
void CSkeleton::Draw(void)
{
	CObject_2D::Draw();
}





//生成処理
CSkeleton* CSkeleton::Create(const D3DXVECTOR3 pos)
{
	CSkeleton* pEnemy = new CSkeleton;

	if (FAILED(pEnemy->Init()))
	{
		return nullptr;
	}

	pEnemy->SetPos(pos);

	int nSelect = random(0, 2);

	pEnemy->SetTexture(CObject::TextureGluttonyMinion);
	D3DXVECTOR2 size = D3DXVECTOR2(25.0f, 36.25);
	pEnemy->m_type = (type)nSelect;
	
	if (pos.x < (float)SCREEN_WIDTH * 0.5f)
	{
		pEnemy->SetMove(D3DXVECTOR3(random(100, 500) * 0.01f, -7.0f, 0.0f));
	}
	else
	{
		pEnemy->SetMove(D3DXVECTOR3(random(100, 500) * -0.01f, -7.0f, 0.0f));
	}

	pEnemy->SetAcceleration(D3DXVECTOR3(0.0f, 0.2f, 0.0f));
	pEnemy->SetRotation(D3DX_PI * (float)random(500, 1000) * 0.00025f);
	pEnemy->m_fTaget = (float)random(150, 600);
	pEnemy->SetLife(random(2, 4) * 100);

	
	switch (nSelect)
	{
	case 0:

	{
		pEnemy->SetTextureParameter(4, 4, 4, 10);
		pEnemy->SetAnimPattern(nSelect * 4);
	}

	break;

	case 1:

	{
		pEnemy->SetTextureParameter(1, 4, 4, INT_MAX);
		pEnemy->SetAnimPattern(nSelect * 4);
	}

	break;

	case 2:

	{
		pEnemy->SetTextureParameter(1, 4, 2, INT_MAX);
		pEnemy->SetAnimPattern(4);
		size.y *= 2.0f;
	}

	break;

	default:
		break;
	}

	
	pEnemy->SetSize(size);

	pEnemy->m_pHitbox = CSquareHitbox::Create(pos, D3DXVECTOR2(size.x - 3.0f, size.y - 5.0f), CHitbox::Type_Enemy);

	return pEnemy;
}




void CSkeleton::UpdateMove(void)
{

	D3DXVECTOR3 pos = GetPos();

	
	switch (m_state)
	{
	case CSkeleton::state_spawn:

	{
		if (pos.y >= m_fTaget && GetMove().y >= 0.0f)
		{
			SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			SetAcceleration(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			SetStartingRot(D3DX_PI * 0.5f);
			SetRotation(0.0f);
			m_state = state_wait;
		}
	}

		break;

	case CSkeleton::state_wait:

	{
		m_nPhase++;

		if (m_nPhase >= 60)
		{
			m_nPhase = 0;
			m_state = state_pursuit;
			
			D3DXVECTOR3 PlayerPos = CPlayer::GetPlayer()->GetPos();
			D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			move = PlayerPos - pos;
			D3DXVec3Normalize(&move, &move);
			move.x *= 2.0f;
			move.y *= 2.0f;

			SetMove(move);

		}
	}

		break;

	case CSkeleton::state_pursuit:

	{
		m_nCntMove++;

		if (m_nCntMove > 10)
		{
			m_nCntMove = 0;

			if (m_type != type_legs)
			{
				int anim = GetPresentAnimPattern();
				anim++;

				if (anim >= 8)
				{
					anim = 4;
				}

				SetAnimPattern(anim);
			}
			
			D3DXVECTOR3 PlayerPos = CPlayer::GetPlayer()->GetPos();
			D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			move = PlayerPos - pos;
			D3DXVec3Normalize(&move, &move);
			move.x *= 2.0f;
			move.y *= 2.0f;

			SetMove(move);
		}
	}

		break;

	default:
		break;
	}
}