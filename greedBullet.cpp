//=============================================================================
//
// greedBullet.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "greedBullet.h"
#include "circleHitbox.h"

//�R���X�g���N�^
CGreedBullet::CGreedBullet()
{
	m_pHitbox = nullptr;
}

//�f�X�g���N�^
CGreedBullet::~CGreedBullet()
{

}

//����������
HRESULT CGreedBullet::Init(void)
{
	if (FAILED(CBullet::Init()))
	{
		return -1;
	}

	m_pHitbox = nullptr;

	return S_OK;
}

//�I������
void CGreedBullet::Uninit(void)
{
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}

	CBullet::Uninit();
}

//�X�V����
void CGreedBullet::Update(void)
{
	CObject_2D::Update();

	int nLife = GetLife();

	nLife--;

	if (nLife <= 0)
	{
		Release();
		return;
	}

	D3DXVECTOR3 pos = GetPos();

	if (pos.y >= 850.0f || pos.x <= -400.0f || pos.x >= 1700.0f)
	{
		Release();
		return;
	}

	if (m_pHitbox != nullptr)
	{
		m_pHitbox->SetPos(pos);

		if (m_pHitbox->Hit())
		{
			Release();
			return;
		}
	}
}



//��������
CGreedBullet* CGreedBullet::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move)
{
	CGreedBullet* pBullet = new CGreedBullet;

	if (FAILED(pBullet->Init()))
	{
		return nullptr;
	}

	pBullet->SetPos(pos);
	pBullet->SetMove(move);
	pBullet->SetSize(D3DXVECTOR2(13.0f, 13.0f));
	pBullet->SetRotation((float)random(-100, 100) * 0.001f * D3DX_PI);
	pBullet->SetLife(800);

	int nRand = random(1, 10);

	if (nRand == 1)
	{
		pBullet->SetTexture(CObject::TextureJewel);
		pBullet->SetTextureParameter(1, 3, 2, INT_MAX);
		pBullet->SetAnimPattern(random(0, 5));
	}
	else
	{
		pBullet->SetTexture(CObject::TextureCoin);
		pBullet->SetTextureParameter(1, 3, 2, INT_MAX);
		pBullet->SetAnimPattern(random(0, 5));
	}

	pBullet->m_pHitbox = CCircleHitbox::Create(pos, 17.0f, CHitbox::Type_EnemyBullet);

	return pBullet;
}

CGreedBullet* CGreedBullet::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const D3DXVECTOR3 acc)
{
	CGreedBullet* pBullet = new CGreedBullet;

	if (FAILED(pBullet->Init()))
	{
		return nullptr;
	}

	pBullet->SetPos(pos);
	pBullet->SetMove(move);
	pBullet->SetAcceleration(acc);
	pBullet->SetSize(D3DXVECTOR2(13.0f, 13.0f));
	pBullet->SetRotation((float)random(-100, 100) * 0.001f * D3DX_PI);
	pBullet->SetLife(800);

	int nRand = random(1, 10);

	if (nRand == 1)
	{
		pBullet->SetTexture(CObject::TextureJewel);
		pBullet->SetTextureParameter(1, 3, 2, INT_MAX);
		pBullet->SetAnimPattern(random(0, 5));
	}
	else
	{
		pBullet->SetTexture(CObject::TextureCoin);
		pBullet->SetTextureParameter(1, 3, 2, INT_MAX);
		pBullet->SetAnimPattern(random(0, 5));
	}

	pBullet->m_pHitbox = CCircleHitbox::Create(pos, 17.0f, CHitbox::Type_EnemyBullet);

	return pBullet;
}