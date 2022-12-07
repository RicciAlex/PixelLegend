//=============================================================================
//
// hitbox.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "hitbox.h"

//�ÓI�ϐ��̏�����
CHitbox* CHitbox::m_pHitbox[MaxHitbox] = {};

//�R���X�g���N�^
CHitbox::CHitbox()
{
	//�����o�[�ϐ����N���A����
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Type = Type_Max;
	m_Shape = shape_Max;
	m_bHit = false;

	for (int nCnt = 0; nCnt < MaxHitbox; nCnt++)
	{
		if (m_pHitbox[nCnt] == nullptr)
		{
			m_nIdx = nCnt;
			m_pHitbox[nCnt] = this;
			break;
		}
	}
}

//�f�X�g���N�^
CHitbox::~CHitbox()
{

}

//����������
HRESULT CHitbox::Init(void)
{
	//�����o�[�ϐ��̏�����
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Type = Type_Max;
	m_Shape = shape_Max;
	m_bHit = false;

	return S_OK;
}

//�I������
void CHitbox::Uninit(void)
{

}

//�C���X�^���X�P����������
void CHitbox::Release(void)
{
	int Idx = m_nIdx;					//�z��̃C���f�b�N�X��ۑ�����
	m_pHitbox[Idx]->Uninit();			//�I�u�W�F�N�g�̏I������
	delete m_pHitbox[Idx];				//�I�u�W�F�N�g������
	m_pHitbox[Idx] = nullptr;			//�|�C���^��null�ɂ���
}

//�ʒu�̎擾����
const D3DXVECTOR3 CHitbox::GetPos(void)
{
	return m_pos;
}

//�`�̎擾����
const CHitbox::Shape CHitbox::GetShape(void)
{
	return m_Shape;
}

//��ނ̎擾����
const CHitbox::Type CHitbox::GetType(void)
{
	return m_Type;
}

//�����������ǂ���
const bool CHitbox::GetHitState(void)
{
	return m_bHit;
}

//�ʒu�̐ݒ菈��
void CHitbox::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//�T�C�Y�̐ݒ菈��
void CHitbox::SetType(const CHitbox::Type type)
{
	m_Type = type;
}

//�`�̐ݒ菈��
void CHitbox::SetShape(const CHitbox::Shape shape)
{
	m_Shape = shape;
}

//�����������ǂ���
void CHitbox::SetHitState(const bool bHit)
{
	m_bHit = bHit;
}


//=============================================================================
//�ÓI�֐�
//=============================================================================

//�C���X�^���X�S���̏I������
void CHitbox::ReleaseAll(void)
{
	for (int nCnt = 0; nCnt < MaxHitbox; nCnt++)
	{
		if (m_pHitbox[nCnt] != nullptr)
		{//null�`�F�b�N
			m_pHitbox[nCnt]->Uninit();		//�I������
			delete m_pHitbox[nCnt];			//���������������
			m_pHitbox[nCnt] = nullptr;		//null�ɂ���
		}
	}
}

//�S���̃C���X�^���X�̏��̎擾����
CHitbox** CHitbox::GetAllHitbox(void)
{
	return &m_pHitbox[0];
}