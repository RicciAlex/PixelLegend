//=============================================================================
//
// enemy.cpp
// Author : Ricci Alex
//
//=============================================================================

//�C���N���[�h�t�@�C��
#include "enemy.h"
#include "bullet.h"
#include "player.h"
#include <stdlib.h>

//�R���X�g���N�^
CEnemy::CEnemy()
{
	//�����o�[�ϐ����N���A����
	m_maxSpeed = 0.0f;
	m_fAngleMove = 0.0f;
	m_nCntMove = 0;
	m_nShootDelay = 0;
	m_bDamageable = false;
	m_subType = ENEMYTYPE_MAX;
}

//�f�X�g���N�^
CEnemy::~CEnemy()
{

}

//����������
HRESULT CEnemy::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CObject_2D::Init()))
	{
		return -1;
	}

	m_bDamageable = false;
	SetObjType(OBJTYPE_ENEMY);

	return S_OK;
}

//�I������
void CEnemy::Uninit(void)
{
	//��{�N���X�̏I������
	CObject_2D::Uninit();
}

//�X�V���� 
void CEnemy::Update(void)
{
	
}

//�`�揈��
void CEnemy::Draw(void)
{
	CObject_2D::Draw();
}

//�̗͂̎擾����
const int CEnemy::GetLife(void)
{
	return m_nLife;
}

//�̗͂̐ݒ菈��
void CEnemy::SetLife(const int nLife)
{
	m_nLife = nLife;
}

//�ő呬�x�̐ݒ菈��
void CEnemy::SetMaxSpeed(const float maxSpeed)
{
	m_maxSpeed = maxSpeed;
}

//�ő�X�s�[�h�̎擾����
const float CEnemy::GetMaxSpeed(void)
{
	return m_maxSpeed;
}

//�G�̎�ނ̐ݒ�
void CEnemy::SetSubtype(const EnemyType subType)
{
	m_subType = subType;
}

//�_���[�W���󂯂邩�ǂ����̎擾����
const bool CEnemy::GetDamageableState(void)
{
	return m_bDamageable;
}

//�_���[�W���󂯂邩�ǂ����̐ݒ菈��
void CEnemy::SetDamageableState(const bool bDamageable)
{
	m_bDamageable = bDamageable;
}

//�G�̎�ނ̎擾����
const CEnemy::EnemyType CEnemy::GetSubtype(void)
{
	return m_subType;
}