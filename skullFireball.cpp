//=============================================================================
//
// skullFireball.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "skullFireball.h"
#include "circleHitbox.h"

//�R���X�g���N�^
CSkullFireball::CSkullFireball()
{
	//�����o�[�ϐ����N���A����
	m_pHitbox = nullptr;
}

//�f�X�g���N�^
CSkullFireball::~CSkullFireball()
{

}

//����������
HRESULT CSkullFireball::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CBullet::Init()))
	{
		return -1;
	}

	return S_OK;
}

//�I������
void CSkullFireball::Uninit(void)
{
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}

	//��{�N���X�̏I������
	CBullet::Uninit();
}

//�X�V����
void CSkullFireball::Update(void)
{
	m_pHitbox->SetPos(GetPos());

	if (m_pHitbox->Hit())
	{//�v���C���[�Ɠ��������ꍇ�A�e������
		Release();
		return;
	}

	//��{�N���X�̍X�V����
	CBullet::Update();
}


//=============================================================================
//�ÓI�֐�
//=============================================================================

//��������
CSkullFireball* CSkullFireball::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CSkullFireball* pBullet = new CSkullFireball;			//�V�����e�𐶐�����

	//����������
	if (FAILED(pBullet->Init()))
	{
		return nullptr;
	}

	pBullet->SetPos(pos);									//�ʒu�̐ݒ�
	pBullet->SetMove(move);									//���x�̐ݒ�

	pBullet->SetBulletType(BULLET_SKULL_FIREBALL);			//�e�̎�ނ̐ݒ�
	pBullet->SetTexture(CObject::TextureSkullFireball);		//�e�N�X�`���̐ݒ�
	pBullet->SetTextureParameter(1, 1, 1, INT_MAX);			//�e�N�X�`���p�����[�^�̐ݒ菈��
	pBullet->SetSize(D3DXVECTOR2(15.0f, 15.0f));			//�T�C�Y�̐ݒ�
	pBullet->SetRotation(-D3DX_PI * 0.025f);				//��]���x�̐ݒ�

	pBullet->m_pHitbox = CCircleHitbox::Create(pos, 12.0f, CHitbox::Type_EnemyBullet);

	return pBullet;
} 