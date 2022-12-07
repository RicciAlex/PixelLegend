//=============================================================================
//
// maw.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "maw.h"
#include "squareHitbox.h"
#include "player.h"
#include "bone.h"
#include "skeleton.h"

#include "inputKeyboard.h"

//コンストラクタ
CMaw::CMaw()
{
	m_state = state_normal;

	m_pHitbox = nullptr;
}

//デストラクタ
CMaw::~CMaw()
{

}

//初期化処理
HRESULT CMaw::Init(void)
{
	if (FAILED(CEnemy::Init()))
	{
		return -1;
	}

	m_state = state_normal;

	m_pHitbox = nullptr;

	return S_OK;
}

//終了処理
void CMaw::Uninit(void)
{
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}

	CEnemy::Uninit();
}

//更新処理
void CMaw::Update(void)
{
	CObject_2D::Update();

	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Hit();
	}

	UpdateState();

	if (CInputKeyboard::GetKeyboardTrigger(DIK_O))
	{
		m_state = state_open;
	}
	if (CInputKeyboard::GetKeyboardTrigger(DIK_K))
	{
		CSkeleton::Create(GetPos());
	}
}

//描画処理
void CMaw::Draw(void)
{
	CObject_2D::Draw();
}

void CMaw::Open(void)
{
	m_state = state_open;

	m_nPhase = 0;
	m_nShootDelay = 0;
}






//生成処理
CMaw* CMaw::Create(Position Pos)
{
	CMaw* pEnemy = new CMaw;

	if (FAILED(pEnemy->Init()))
	{
		return nullptr;
	}

	pEnemy->SetSize(D3DXVECTOR2(150.0f, 20.0f));
	pEnemy->SetTexture(CObject::TextureGluttonyMaw);
	pEnemy->SetTextureParameter(1, 1, 5, INT_MAX);

	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float fStartingAngle = 0.0f;
	D3DXVECTOR2 size = D3DXVECTOR2(0.0f, 0.0f);

	switch (Pos)
	{
	case CMaw::left:

	{
		pos = D3DXVECTOR3(85.0f, (float)SCREEN_HEIGHT * 0.5f, 0.0f);
		fStartingAngle = -D3DX_PI * 0.5f;
		size = D3DXVECTOR2(15.0f, 90.0f);
	}

		break;

	case CMaw::up:

	{
		pos = D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, 85.0f, 0.0f);
		fStartingAngle = D3DX_PI;
		size = D3DXVECTOR2(90.0f, 15.0f);
	}

		break;

	case CMaw::right:

	{
		pos = D3DXVECTOR3((float)SCREEN_WIDTH - 85.0f, (float)SCREEN_HEIGHT * 0.5f, 0.0f);
		fStartingAngle = D3DX_PI * 0.5f;
		size = D3DXVECTOR2(15.0f, 90.0f);
	}

		break;

	case CMaw::down:

	{
		pos = D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT - 85.0f, 0.0f);
		fStartingAngle = 0.0f;
		size = D3DXVECTOR2(90.0f, 15.0f);
	}

		break;

	default:
		break;
	}

	pEnemy->SetPos(pos);
	pEnemy->SetStartingRot(D3DX_PI * 0.5f + fStartingAngle);
	pEnemy->m_pHitbox = CSquareHitbox::Create(pos, size, CHitbox::Type_Enemy);

	return pEnemy;
}



void CMaw::UpdateState(void)
{
	switch (m_state)
	{
	case CMaw::state_normal:

	{

	}

		break;

	case CMaw::state_open:

	{
		m_nPhase++;

		if (m_nPhase % 8 == 7)
		{
			int anim = GetPresentAnimPattern();

			if (anim >= 4)
			{
				switch (int a = random(0, 3))
				{
				case 0:

					m_state = state_SingleShoot;

					break;

				case 1:

					m_state = state_TripleShoot;

					break;

				case 2:

					m_state = state_RandomShoot;

					break;

				case 3:

					m_state = state_Spawn;

				default:
					break;
				}
				
				m_nPhase = 0;
			}
			else
			{
				anim++;
				SetAnimPattern(anim);
			}
		}
	}

		break;

	case CMaw::state_SingleShoot:

	{
		m_nShootDelay++;

		if (m_nShootDelay % 50 == 5)
		{
			D3DXVECTOR3 pos, PlayerPos, target;

			pos = GetPos();
			PlayerPos = CPlayer::GetPlayer()->GetPos();
			target = PlayerPos - pos;
			D3DXVec3Normalize(&target, &target);
			target.x *= 3.0f;
			target.y *= 3.0f;

			CBone::Create(pos, target);
		}

		if (m_nShootDelay >= 410)
		{
			m_nShootDelay = 0;
			m_state = state_close;
		}
	}

		break;

	case CMaw::state_TripleShoot:

	{
		m_nShootDelay++;

		if (m_nShootDelay % 100 == 5)
		{
			D3DXVECTOR3 pos, PlayerPos, target;

			pos = GetPos();
			PlayerPos = CPlayer::GetPlayer()->GetPos();
			target = PlayerPos - pos;
			D3DXVec3Normalize(&target, &target);

			D3DXVECTOR3 unit = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

			float fAngle = acosf(D3DXVec3Dot(&target, &unit));

			if (PlayerPos.y < pos.y)
			{
				fAngle *= -1.0f;
			}

			CBone::Create(pos, D3DXVECTOR3(3.0f * target.x, 3.0f * target.y, 0.0f));

			D3DXVECTOR3 NewMove = D3DXVECTOR3(cosf(fAngle) * cosf(D3DX_PI / 6.0f) - sinf(fAngle) * sinf(D3DX_PI / 6.0f),
				sinf(fAngle) * cosf(D3DX_PI / 6.0f) + cosf(fAngle) * sinf(D3DX_PI / 6.0f), 0.0f);

			CBone::Create(pos, D3DXVECTOR3(3.0f * NewMove.x, 3.0f * NewMove.y, 0.0f));

			NewMove = D3DXVECTOR3(cosf(fAngle) * cosf(-D3DX_PI / 6.0f) - sinf(fAngle) * sinf(-D3DX_PI / 6.0f),
				sinf(fAngle) * cosf(-D3DX_PI / 6.0f) + cosf(fAngle) * sinf(-D3DX_PI / 6.0f), 0.0f);

			CBone::Create(pos, D3DXVECTOR3(3.0f * NewMove.x, 3.0f * NewMove.y, 0.0f));
		}

		if (m_nShootDelay >= 710)
		{
			m_nShootDelay = 0;
			m_state = state_close;
		}
	}

	break;

	case CMaw::state_RandomShoot:

	{
		m_nShootDelay++;

		if (m_nShootDelay % 30 == 5)
		{
			D3DXVECTOR3 pos, PlayerPos, target;

			pos = GetPos();
			PlayerPos = CPlayer::GetPlayer()->GetPos();
			target = PlayerPos - pos;
			D3DXVec3Normalize(&target, &target);

			D3DXVECTOR3 unit = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

			float fAngle = acosf(D3DXVec3Dot(&target, &unit));

			if (PlayerPos.y < pos.y)
			{
				fAngle *= -1.0f;
			}
			
			float fDiv = random(3000, 8000) * 0.001f;

			D3DXVECTOR3 NewMove = D3DXVECTOR3(cosf(fAngle) * cosf(D3DX_PI / fDiv) - sinf(fAngle) * sinf(D3DX_PI / fDiv),
				sinf(fAngle) * cosf(D3DX_PI / fDiv) + cosf(fAngle) * sinf(D3DX_PI / fDiv), 0.0f);

			CBone::Create(pos, D3DXVECTOR3(4.0f * NewMove.x, 4.0f * NewMove.y, 0.0f));

			NewMove = D3DXVECTOR3(cosf(fAngle) * cosf(-D3DX_PI / fDiv) - sinf(fAngle) * sinf(-D3DX_PI / fDiv),
				sinf(fAngle) * cosf(-D3DX_PI / fDiv) + cosf(fAngle) * sinf(-D3DX_PI / fDiv), 0.0f);

			CBone::Create(pos, D3DXVECTOR3(4.0f * NewMove.x, 4.0f * NewMove.y, 0.0f));
		}

		if (m_nShootDelay >= 410)
		{
			m_nShootDelay = 0;
			m_state = state_close;
		}
	}

	break;

	case CMaw::state_Spawn:

	{
		m_nShootDelay++;

		if (m_nShootDelay % 35 == 5)
		{
			CSkeleton::Create(GetPos());
		}

		if (m_nShootDelay >= 350)
		{
			m_nShootDelay = 0;
			m_state = state_close;
		}
	}

	break;

	case CMaw::state_close:

	{
		m_nPhase++;

		if (m_nPhase % 8 == 7)
		{
			int anim = GetPresentAnimPattern();

			if (anim == 0)
			{
				m_state = state_normal;
				m_nPhase = 0;
			}
			else
			{
				anim--;
				SetAnimPattern(anim);
			}
		}
	}

		break;

	default:
		break;
	}
}