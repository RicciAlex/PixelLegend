//=============================================================================
//
// bubbleBat.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "bubbleBat.h"
#include "circleHitbox.h"
#include "Letter.h"
#include "application.h"
#include "inputMouse.h"
#include "player.h"

//�R���X�g���N�^
CBubbleBat::CBubbleBat()
{
	m_letterRelativePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fAngleMove = 0.0f;
	m_state = state_spawn;

	m_pHitbox = nullptr;
	m_pLetter = nullptr;
}

//�f�X�g���N�^
CBubbleBat::~CBubbleBat()
{

}

//����������
HRESULT CBubbleBat::Init(void)
{
	if (FAILED(CEnemy::Init()))
	{
		return -1;
	}

	m_letterRelativePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fAngleMove = 0.0f;
	m_state = state_spawn;

	m_pHitbox = nullptr;
	m_pLetter = nullptr;

	return S_OK;
}

//�I������
void CBubbleBat::Uninit(void)
{
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}
	if (m_pLetter != nullptr)
	{
		m_pLetter->Release();
		m_pLetter = nullptr;
	}

	CEnemy::Uninit();
}

//�X�V����
void CBubbleBat::Update(void)
{
	D3DXVECTOR3 pos = GetPos();

	switch (m_state)
	{
	case CBubbleBat::state_spawn:

	{
		m_nCntMove++;
		
		pos.y += 0.25f * sinf(m_fAngleMove);
		SetPos(pos);

		if (m_nCntMove == 120)
		{
			SetAnimPattern(4);
		}
		else if(m_nCntMove == 150)
		{
			SetAnimPattern(5);
		}
		else if (m_nCntMove == 180)
		{
			SetAnimPattern(0);
		}
		else if (m_nCntMove == 210)
		{
			SetTextureParameter(2, 3, 2, 15);
			m_nCntMove = 0;
			m_state = state_looking;

			m_pLetter = CLetter::Create(GetPos() + m_letterRelativePos, D3DXVECTOR2(20.0f, 20.0f), '?');
			/*m_pLetter->SetStartingRot(D3DX_PI * 0.5f);
			m_pLetter->SetRevolution(GetPos(), D3DX_PI * 0.0005f, 60.0f);
			m_pLetter->SetPresentRevolutionAngle(-D3DX_PI * 0.5f);
			m_pLetter->SetRotation(D3DX_PI * -0.0005f);*/
		}

		m_fAngleMove += D3DX_PI * 0.02f;
	}

		break;

	case CBubbleBat::state_looking:

	{
		pos.y += 0.25f * sinf(m_fAngleMove);
		SetPos(pos);
		m_fAngleMove += D3DX_PI * 0.02f;

		if (CApplication::GetMouse()->GetMouseLeftClick())
		{
			m_pLetter->SetAnimPattern(11);
			m_state = state_charge;

			D3DXVECTOR3 PlayerPos = CPlayer::GetPlayer()->GetPos();
			PlayerPos -= pos;

			if (pos.x > PlayerPos.x && GetFlipX() || pos.x < PlayerPos.x && !GetFlipX())
			{
				FlipX();
			}

			D3DXVec3Normalize(&PlayerPos, &PlayerPos);
			PlayerPos.x *= 6.0f;
			PlayerPos.y *= 6.0f;

			SetMove(PlayerPos);

			if (pos.x <= -150.0f || pos.x >= (float)SCREEN_WIDTH + 150.0f || pos.y <= 150.0f || pos.y >= (float)SCREEN_HEIGHT + 150.0f)
			{
				Release();
				return;
			}
		}
	}

		break;

	case CBubbleBat::state_charge:

	{
		if (m_pLetter != nullptr)
		{
			m_nCntMove++;

			if (m_nCntMove >= 60)
			{
				m_nCntMove = 0;
				m_pLetter->Release();
				m_pLetter = nullptr;

			}
		}

		if (pos.x <= -150.0f || pos.x >= (float)SCREEN_WIDTH + 150.0f || pos.y <= 150.0f || pos.y >= (float)SCREEN_HEIGHT + 150.0f)
		{
			Release();
			return;
		}
	}

		break;

	default:
		break;
	}

	if (m_pLetter != nullptr)
	{
		m_pLetter->SetPos(GetPos() + m_letterRelativePos);

	}

	CObject_2D::Update();

}

//�`�揈��
void CBubbleBat::Draw(void)
{
	CObject_2D::Draw();
}




//��������
CBubbleBat* CBubbleBat::Create(const D3DXVECTOR3 pos)
{
	CBubbleBat* pEnemy = new CBubbleBat;

	if (FAILED(pEnemy->Init()))
	{
		return nullptr;
	}

	pEnemy->SetPos(pos);
	pEnemy->SetSize(D3DXVECTOR2(75.0f, 37.5f));
	pEnemy->SetTexture(CObject::TextureBubbleBat);
	pEnemy->SetTextureParameter(1, 3, 2, INT_MAX);
	pEnemy->SetAnimPattern(3);
	pEnemy->SetStartingRot(D3DX_PI * 0.5f);
	pEnemy->SetMove(D3DXVECTOR3(1.0f, 0.0f, 0.0f));
	
	if (pos.x <= (float)SCREEN_WIDTH * 0.5f)
	{
		pEnemy->FlipX();
	}

	pEnemy->m_letterRelativePos = D3DXVECTOR3(0.0f, -50.0f, 0.0f);

	return pEnemy;
}