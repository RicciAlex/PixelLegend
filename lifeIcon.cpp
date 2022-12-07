//=============================================================================
//
// lifeIcon.h
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "lifeIcon.h"
#include "object2D.h"
#include "player.h"

//�R���X�g���N�^
CLifeIcon::CLifeIcon()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	for (int nCnt = 0; nCnt < MaxHeart; nCnt++)
	{
		m_pHeart[nCnt] = nullptr;
	}
}

//�f�X�g���N�^
CLifeIcon::~CLifeIcon()
{

}

//����������
HRESULT CLifeIcon::Init(void)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	for (int nCnt = 0; nCnt < MaxHeart; nCnt++)
	{
		m_pHeart[nCnt] = nullptr;
	}

	return S_OK;
}

//�I������
void CLifeIcon::Uninit(void)
{
	for (int nCnt = 0; nCnt < MaxHeart; nCnt++)
	{
		if (m_pHeart[nCnt] != nullptr)
		{
			m_pHeart[nCnt]->Release();
			m_pHeart[nCnt] = nullptr;
		}
	}
}

//�X�V����
void CLifeIcon::Update(void)
{
	int nLife = CPlayer::GetPlayer()->GetLife();

	if (nLife <= 0)
	{
		m_pHeart[0]->SetAnimPattern(3);
	}
	else if (nLife < 15)
	{
		m_pHeart[nLife / 3]->SetAnimPattern(3 - (nLife % 3));
	}
}

//�`�揈��
void CLifeIcon::Draw(void)
{

}

//�ʒu�̐ݒ菈��
void CLifeIcon::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//�T�C�Y�̎擾����
const D3DXVECTOR2 CLifeIcon::GetSize(void)
{
	return m_size;
}

//�ʒu�̎擾����
const D3DXVECTOR3  CLifeIcon::GetPos(void)
{
	return m_pos;
}




CLifeIcon* CLifeIcon::Create(const D3DXVECTOR3 pos)
{
	CLifeIcon* pIcon = new CLifeIcon;

	if (FAILED(pIcon->Init()))
	{
		return nullptr;
	}

	pIcon->m_pos = pos;
	pIcon->m_size = D3DXVECTOR2(40.0f * MaxHeart, 30.0f);

	for (int nCnt = 0; nCnt < MaxHeart; nCnt++)
	{
		pIcon->m_pHeart[nCnt] = CObject_2D::Create();

		D3DXVECTOR3 heartPos = pos;
		heartPos.x += 42.5f * nCnt;

		pIcon->m_pHeart[nCnt]->SetPos(heartPos);
		pIcon->m_pHeart[nCnt]->SetSize(D3DXVECTOR2(22.5f, 22.5f));
		pIcon->m_pHeart[nCnt]->SetStartingRot(D3DX_PI * 0.5f);
		pIcon->m_pHeart[nCnt]->SetTexture(CObject::TextureLifeIcon);
		pIcon->m_pHeart[nCnt]->SetTextureParameter(1, 4, 1, INT_MAX);
		pIcon->m_pHeart[nCnt]->SetPriority(2);
		pIcon->m_pHeart[nCnt]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
	}

	return pIcon;
}