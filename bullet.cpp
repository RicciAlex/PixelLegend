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

	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR2 size = GetSize();

	if (pos.x + size.x <= 0.0f || pos.x + size.x >= (float)SCREEN_WIDTH ||
		pos.y + size.y <= 0.0f || pos.y - size.y >= (float)SCREEN_HEIGHT)
	{
		Release();
		return;
	}
	
} 

int CBullet::GetLife(void)
{
	return m_nLife;
}

void CBullet::SetLife(const int life)
{
	m_nLife = life;
}

CBullet::BULLET_TYPE CBullet::GetBulletType(void)
{
	return m_BulletType;
}

void CBullet::SetBulletType(BULLET_TYPE type)
{
	m_BulletType = type;
}

//==================================================================================================================
//
//		�ÓI�֐�
//
//==================================================================================================================

//CBullet* CBullet::Create(void)
//{
//	CBullet* pBullet = nullptr;
//
//	pBullet = new CBullet;
//
//	if (FAILED(pBullet->Init()))
//	{
//		if (pBullet != nullptr)
//		{
//			delete pBullet;
//			pBullet = nullptr;
//		}
//
//		return nullptr;
//	}
//
//	return pBullet;
//}

//�e�̔j������
void CBullet::DestroyBullet(void)
{
	D3DXVECTOR3 pos = GetPos();
	CExplosion* pExplosion = nullptr;

	if (m_BulletType == BULLET_FIREBALL)
	{
		pExplosion = CExplosion::Create();				//�����̐���

		pExplosion->SetPos(pos);						//�����̈ʒu�̐ݒ�

	}
	Release();											//�e������
}