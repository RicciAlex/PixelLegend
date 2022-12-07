//=============================================================================
//
// skullShield.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "skullShield.h"
#include "circleHitbox.h"

CSkullShield::CSkullShield()
{
	m_pHitbox = nullptr;
}

CSkullShield::~CSkullShield()
{

}

//����������
HRESULT CSkullShield::Init(void)
{
	if (FAILED(CEnemy::Init()))
	{
		return -1;
	}

	m_pHitbox = nullptr;

	return S_OK;
}

//�I������
void CSkullShield::Uninit(void)
{
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}

	CEnemy::Uninit();
}

//�X�V����
void CSkullShield::Update(void)
{
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->SetPos(GetPos());

		if (m_pHitbox->GetHitState())
		{
			m_pHitbox->SetHitState(false);
			int nLife = GetLife();

			nLife -= 100;

			if (nLife <= 0)
			{
				Release();
				return;
			}
			else
			{
				SetLife(nLife);
			}
		}
	}

	CObject_2D::Update();
}

//�`�揈��
void CSkullShield::Draw(void)
{
	CObject_2D::Draw();
}




//��������
CSkullShield* CSkullShield::Create(const D3DXVECTOR3 pos, const float fStartAngle)
{
	CSkullShield* pEnemy = new CSkullShield;

	if (FAILED(pEnemy->Init()))
	{
		return nullptr;
	}

	pEnemy->SetPos(pos);
	pEnemy->SetStartingRot(D3DX_PI * 0.5f);
	pEnemy->SetPresentRevolutionAngle(fStartAngle);
	pEnemy->SetTexture(CObject::TextureSkullShield);
	pEnemy->SetTextureParameter(1, 1, 1, INT_MAX);
	pEnemy->SetRevolution(pos, D3DX_PI * 0.01f, 60.0f);
	pEnemy->SetSize(D3DXVECTOR2(22.5f, 22.5f));
	pEnemy->SetLife(30000);

	pEnemy->m_pHitbox = CCircleHitbox::Create(pEnemy->GetPos(), 18.0f, CHitbox::Type_Enemy);

	return pEnemy;
}