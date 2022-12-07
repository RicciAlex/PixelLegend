//=============================================================================
//
// spine.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "spine.h"
#include "vertebra.h"

//�R���X�g���N�^
CSpine::CSpine()
{
	//�����o�[�ϐ����N���A����
	for (int nCnt = 0; nCnt < VertebraNumber; nCnt++)
	{
		m_pVertebra[nCnt] = nullptr;
	}
	m_anchor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_head = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCntDestroy = 0;
	m_bDead = false;
}

//�f�X�g���N�^
CSpine::~CSpine()
{

}

//����������
HRESULT CSpine::Init(void)
{
	//�����o�[�ϐ��̏���������
	for (int nCnt = 0; nCnt < VertebraNumber; nCnt++)
	{
		if (m_pVertebra[nCnt] != nullptr)
		{
			m_pVertebra[nCnt] = nullptr;
		}
	}

	m_anchor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_head = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCntDestroy = 0;
	m_bDead = false;

	return S_OK;
}

//�I������
void CSpine::Uninit(void)
{
	for (int nCnt = 0; nCnt < VertebraNumber; nCnt++)
	{
		if (m_pVertebra[nCnt] != nullptr)
		{
			m_pVertebra[nCnt]->Release();
			m_pVertebra[nCnt] = nullptr;
		}
	}
}

//�X�V����
void CSpine::Update(void)
{
	if (!m_bDead)
	{//����ł��Ȃ��ꍇ
		D3DXVECTOR3 dir = (m_head - m_anchor) * 0.125f;

		for (int nCnt = 0; nCnt < VertebraNumber; nCnt++)
		{
			m_pVertebra[nCnt]->SetPos(m_anchor + (dir * (float)(nCnt + 1)));
		}
	}
	else
	{//���񂾏ꍇ

		//���S�A�j���[�V��������
		m_nCntDestroy--;

		if (m_nCntDestroy <= 0)
		{
			Release();
		}
	}
}

//�`�揈��
void CSpine::Draw(void)
{
	
}

//�ʒu�̐ݒ菈��
void CSpine::SetPos(const D3DXVECTOR3 pos)
{
	m_anchor = pos;
}

//���̈ʒu�̐ݒ菈��
void CSpine::SetHeadPos(const D3DXVECTOR3 pos)
{
	m_head = pos;
}

//�T�C�Y�̎擾����
const D3DXVECTOR2 CSpine::GetSize(void)
{
	return D3DXVECTOR2(0.0f, 0.0f);
}

//�ʒu�̐ݒ菈��
const D3DXVECTOR3 CSpine::GetPos(void)
{
	return m_anchor;
}

//���S�A�j���[�V��������
void CSpine::Kill(void)
{
	m_bDead = true;
	D3DXVECTOR3 dir;

	for (int nCnt = 0; nCnt < VertebraNumber; nCnt++)
	{
		dir = D3DXVECTOR3((float)random(-5000, 5000), (float)random(-5000, 5000), 0.0f);
		D3DXVec3Normalize(&dir, &dir);
		dir.x *= 2.0f;
		dir.y *= 2.0f;

		m_pVertebra[nCnt]->SetMove(dir);
		m_pVertebra[nCnt]->SetRotation(((float)random(-100, 100) * 0.01f) * D3DX_PI * 0.25f);
		m_pVertebra[nCnt]->SetAcceleration(D3DXVECTOR3(0.0f, 0.05f, 0.0f));
		m_nCntDestroy = 120;
	}
}

void CSpine::Flip(void)
{
	for (int nCnt = 0; nCnt < CSpine::VertebraNumber; nCnt++)
	{
		if (m_pVertebra[nCnt] != nullptr)
		{
			m_pVertebra[nCnt]->FlipX();
		}
	}
}


//==================================================================================================
//								�ÓI�֐�
//==================================================================================================

//��������
CSpine* CSpine::Create(D3DXVECTOR3 anchor, D3DXVECTOR3 head)
{
	D3DXVECTOR3 dir = (head - anchor) * 0.125f;

	CSpine* pSpine = new CSpine;

	if (FAILED(pSpine->Init()))
	{
		return nullptr;
	}
	
	for (int nCnt = 0; nCnt < VertebraNumber; nCnt++)
	{
		pSpine->m_anchor = anchor;
		pSpine->m_head = head;
		pSpine->m_pVertebra[nCnt] = CVertebra::Create(anchor + (dir * (float)(nCnt + 1)), D3DXVECTOR2(18.75f, 18.75f));
	}

	return pSpine;
} 