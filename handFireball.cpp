//=============================================================================
//
// handFireball.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "handFireball.h"
#include "circleHitbox.h"

//�R���X�g���N�^
CHandFireball::CHandFireball()
{
	//�����o�[�ϐ����N���A����
	m_fChange = 0.0f;
	m_Rot = false;

	m_pHitbox = nullptr;
}

//�f�X�g���N�^
CHandFireball::~CHandFireball()
{

}

//����������
HRESULT CHandFireball::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CBullet::Init()))
	{
		return -1;
	}

	//�����o�[�ϐ�������������
	m_fChange = 0.0f;
	m_Rot = false;

	m_pHitbox = nullptr;

	return S_OK;
}

//�I������
void CHandFireball::Uninit(void)
{
	//�q�b�g�{�b�N�X�̔j��
	if (m_pHitbox != nullptr)
	{//null�`�F�b�N
		m_pHitbox->Release();		//���������������
		m_pHitbox = nullptr;		//�|�C���^��null�ɂ���
	}

	//��{�N���X�̏I������
	CBullet::Uninit();
}

//�X�V����
void CHandFireball::Update(void)
{
	//��{�N���X�̍X�V����
	CObject_2D::Update();

	D3DXVECTOR3 pos = GetPos();		//�ʒu�̎擾
	D3DXVECTOR3 move = GetMove();	//���x�̎擾

	if (pos.x >= m_fChange && move.x >= 0.0f || pos.x <= m_fChange && move.x <= 0.0f)
	{//�ړI�̈ʒu�𒴂�����A���̖ړI�̈ʒu��ݒ肵�āA������ς���
		if (move.x >= 0.0f)
		{
			m_fChange += 100.0f;
		}
		else
		{
			m_fChange -= 100.0f;
		}
		
		move.y *= -1.0f;

		SetMove(move);

		if (!m_Rot)
		{
			float fRot = GetRot() + D3DX_PI * 0.5f;
			SetStartingRot(fRot);
			m_Rot = true;
		}
		else
		{
			float fRot = GetRot() - D3DX_PI * 0.5f;
			SetStartingRot(fRot);
			m_Rot = false;
		}
	}

	//�q�b�g�{�b�N�X�̍X�V����
	if (m_pHitbox != nullptr)
	{//null�`�F�b�N

		m_pHitbox->SetPos(GetPos());		//�q�b�g�{�b�N�X�̈ʒu�̍X�V

		if (m_pHitbox->Hit())
		{//�����Ɠ���������A����
			Release();
			return;
		}
	}

	if (pos.x <= -100.0f || pos.x >= 1380.0f)
	{//��ʂ��o����A����
		Release();
		return;
	}
}


//=============================================================================
//
//								�ÓI�֐�
//
//=============================================================================


//��������
CHandFireball* CHandFireball::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CHandFireball* pBullet = new CHandFireball;		//�C���X�^���X�𐶐�����

	if (FAILED(pBullet->Init()))
	{//����������
		return nullptr;
	}

	pBullet->SetPos(pos);									//�ʒu�̐ݒ�
	pBullet->SetSize(D3DXVECTOR2(25.0f, 25.0f));			//�T�C�Y�̐ݒ�
	pBullet->SetMove(move);									//���x�̐ݒ�
	pBullet->SetTexture(CObject::TextureHandFireball);		//�e�N�X�`���̐ݒ�
	pBullet->SetTextureParameter(1, 1, 1, INT_MAX);			//�e�N�X�`���p�����[�^�̐ݒ�
	pBullet->m_fChange = 100.0f;							//�ړI�̈ʒu�̐ݒ�

	//�K�v��������A�e�N�X�`���𔽓]����
	if (move.x < 0.0)
	{
		pBullet->FlipX();

		pBullet->m_Rot = true;
		pBullet->m_fChange = (float)SCREEN_WIDTH - 100.0f;

		pBullet->SetStartingRot(D3DX_PI);
	}

	//�q�b�g�{�b�N�X�̐���
	pBullet->m_pHitbox = CCircleHitbox::Create(pos, 20.0f, CHitbox::Type_EnemyBullet);

	return pBullet;				//���������C���X�^���X��Ԃ�
}