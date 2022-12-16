//=============================================================================
//
// bullet.cpp
// Author : Ricci Alex
//
//=============================================================================

//�C���N���[�h�t�@�C��
#include "bullet.h"
#include "main.h"
#include "explosion.h"
#include "enemy.h"
#include "player.h"

//�R���X�g���N�^
CBullet::CBullet()
{
	//�����o�[�ϐ����N���A����
	m_nLife = 0;
}

//�f�X�g���N�^
CBullet::~CBullet()
{

}

//����������
HRESULT CBullet::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CObject_2D::Init()))
	{
		return -1;
	}

	m_nLife = 0;
	CObject::SetObjType(CObject::OBJTYPE_BULLET);

	return S_OK;
}

//�I������
void CBullet::Uninit(void)
{
	//��{�N���X�̏I������
	CObject_2D::Uninit();
}

//�X�V����
void CBullet::Update(void)
{
	CObject_2D::Update();								//��{�N���X�̍X�V����

	D3DXVECTOR3 pos = GetPos();			//�ʒu�̎擾
	D3DXVECTOR2 size = GetSize();		//�T�C�Y�̎擾

	if (pos.x + size.x <= 0.0f || pos.x + size.x >= (float)SCREEN_WIDTH ||
		pos.y + size.y <= 0.0f || pos.y - size.y >= (float)SCREEN_HEIGHT)
	{//��ʂ��o����A����
		Release();
		return;
	}
	
} 

//�����̎擾����
int CBullet::GetLife(void)
{
	return m_nLife;
}

//�����̐ݒ菈��
void CBullet::SetLife(const int life)
{
	m_nLife = life;
}

//�e�̎�ނ̎擾����
CBullet::BULLET_TYPE CBullet::GetBulletType(void)
{
	return m_BulletType;
}

//�e�̎�ނ̐ݒ菈��
void CBullet::SetBulletType(BULLET_TYPE type)
{
	m_BulletType = type;
}

//==================================================================================================================
//
//											�ÓI�֐�
//
//==================================================================================================================

//�e�̔j������
void CBullet::DestroyBullet(void)
{
	D3DXVECTOR3 pos = GetPos();							//�ʒu�̎擾
	CExplosion* pExplosion = nullptr;

	if (m_BulletType == BULLET_FIREBALL)
	{
		pExplosion = CExplosion::Create();				//�����̐���

		pExplosion->SetPos(pos);						//�����̈ʒu�̐ݒ�

	}

	Release();											//�e������
}