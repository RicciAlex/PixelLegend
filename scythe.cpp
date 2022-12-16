//=============================================================================
//
// scythe.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "Scythe.h"
#include "circleHitbox.h"

//�R���X�g���N�^
CScythe::CScythe()
{
	//�����o�[�ϐ����N���A����
	fCntSize = 0.0f;

	m_pHitbox = nullptr;
}

//�f�X�g���N�^
CScythe::~CScythe()
{

}

//����������
HRESULT CScythe::Init(void)
{
	if (FAILED(CBullet::Init()))
	{//��{�N���X�̏���������
		return -1;
	}

	//�����o�[�ϐ�������������
	fCntSize = 0.0f;

	m_pHitbox = nullptr;

	return S_OK;
}

//�I������
void CScythe::Uninit(void)
{
	//�q�b�g�{�b�N�X�̔j������
	if (m_pHitbox != nullptr)
	{//null�`�F�b�N
		m_pHitbox->Release();		//���������������
		m_pHitbox = nullptr;		//�|�C���^��null�ɂ���
	}

	//��{�N���X�̏I������
	CBullet::Uninit();
}

//�X�V����
void CScythe::Update(void)
{
	//�q�b�g�{�b�N�X�̍X�V����
	if (m_pHitbox != nullptr)
	{//null�`�F�b�N

		m_pHitbox->SetPos(GetPos());	//�q�b�g�{�b�N�X�̈ʒu�̍X�V

		if (m_pHitbox->Hit())
		{//�����Ɠ���������A����
			Release();
			return;
		}
	}
	
	//��{�N���X�̍X�V����
	CBullet::Update();
}


//=============================================================================
//
//								�ÓI�֐�
//
//=============================================================================


//��������
CScythe* CScythe::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CScythe* pBullet = new CScythe;			//�C���X�^���X�𐶐�����

	if (FAILED(pBullet->Init()))
	{//����������
		return nullptr;
	}

	pBullet->SetPos(pos);								//�ʒu�̐ݒ�
	pBullet->SetMove(move);								//���x�̐ݒ�
	pBullet->SetSize(D3DXVECTOR2(45.0f, 45.0f));		//�T�C�Y�̐ݒ�
	pBullet->SetTexture(CObject::TextureScythe);		//�e�N�X�`���̐ݒ�
	pBullet->SetTextureParameter(1, 1, 1, INT_MAX);		//�e�N�X�`���p�����[�^�̐ݒ�
	pBullet->SetRotation(D3DX_PI * 0.05f);				//�����̏����l�̐ݒ�
	pBullet->FlipX();									//�e�N�X�`���𔽓]����

	//�q�b�g�{�b�N�X�̐�������
	pBullet->m_pHitbox = CCircleHitbox::Create(pos, 25.0f, CHitbox::Type_EnemyBullet);

	return pBullet;				//���������C���X�^���X��Ԃ�
}