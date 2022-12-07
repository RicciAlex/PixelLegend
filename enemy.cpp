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

const int CEnemy::GetLife(void)
{
	return m_nLife;
}

void CEnemy::SetLife(const int nLife)
{
	m_nLife = nLife;
}

//�ő呬�x�̐ݒ菈��
void CEnemy::SetMaxSpeed(const float maxSpeed)
{
	m_maxSpeed = maxSpeed;
}

const float CEnemy::GetMaxSpeed(void)
{
	return m_maxSpeed;
}

//�G�̎�ނ̐ݒ�
void CEnemy::SetSubtype(const EnemyType subType)
{
	m_subType = subType;
}

const bool CEnemy::GetDamageableState(void)
{
	return m_bDamageable;
}

void CEnemy::SetDamageableState(const bool bDamageable)
{
	m_bDamageable = bDamageable;
}

//�G�̎�ނ̎擾����
const CEnemy::EnemyType CEnemy::GetSubtype(void)
{
	return m_subType;
}

////�G�̐�������(��ނɂ����)
//CEnemy* CEnemy::Create(CEnemy::EnemyType type)
//{
//	CEnemy* pEnemy = new CEnemy;			//�V�����G�𐶐�����
//
//	if (pEnemy != nullptr)
//	{
//		//����������
//		if (FAILED(pEnemy->Init()))
//		{
//			delete pEnemy;					//���������������
//			return nullptr;					//null��Ԃ�
//		}
//
//		pEnemy->SetObjType(CObject::OBJTYPE_ENEMY);		//�I�u�W�F�N�g�̎�ނ̐ݒ�
//
//		switch (type)
//		{
//		case CObject::ENEMYTYPE_CLOCK:
//
//			pEnemy->SetStartingRot(D3DX_PI * 0.5f);						//��]�p�x�̏����l�̐ݒ�
//			pEnemy->m_maxSpeed = 2.0f;									//�ő呬�x�̐ݒ�
//			pEnemy->m_fAngleMove = 0.0f;								//�J�E���^�̐ݒ�
//			pEnemy->m_nCntMove = 0;										//�J�E���^�̐ݒ�
//			pEnemy->m_nShootDelay = 0;									//�J�E���^�̐ݒ�
//			pEnemy->SetTextureParameter(1, 1, 1, INT_MAX);				//�e�N�X�`���p�����[�^�̐ݒ�
//			pEnemy->SetSize(D3DXVECTOR2(40.0f, 40.0f));					//�T�C�Y�̐ݒ�
//																		
//			pEnemy->SetMove(D3DXVECTOR3(-1.5f, 0.0f, 0.0f));			//���x�̐ݒ�
//			pEnemy->SetAcceleration(D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//�����̐ݒ�
//			pEnemy->SetSubtype(type);									//�G�̎�ނ̐ݒ�
//																		
//			pEnemy->SetTexture(TextureClock);							//�e�N�X�`���̐ݒ�
//
//			break;
//
//		case CObject::ENEMYTYPE_CLOUD:
//
//			pEnemy->m_maxSpeed = 10.0f;									//�ő呬�x�̐ݒ�
//			pEnemy->m_fAngleMove = 0.0f;								//��]�p�x�̏����l�̐ݒ�
//			pEnemy->m_nCntMove = 0;										//�J�E���^�[�̐ݒ�
//			pEnemy->m_nShootDelay = 0;									//�J�E���^�[�̐ݒ�
//			pEnemy->SetTextureParameter(2, 2, 3, 15);					//�e�N�X�`���p�����[�^�̐ݒ�
//			pEnemy->SetSize(D3DXVECTOR2(50.0f, 40.0f));					//�T�C�Y�̐ݒ�
//																		
//			pEnemy->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));				//���x�̐ݒ�
//			pEnemy->SetAcceleration(D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//�����̐ݒ�
//			pEnemy->SetSubtype(type);									//�G�̎�ނ̐ݒ�
//																		
//			pEnemy->SetTexture(TextureCloud);							//�e�N�X�`���̐ݒ�
//
//			break;
//
//		case CObject::ENEMYTYPE_BOUND_CLOCK:
//
//			pEnemy->m_maxSpeed = 2.0f;									//�ő呬�x�̐ݒ�
//			pEnemy->m_fAngleMove = 0.0f;								//��]�p�x�̏����l�̐ݒ�
//			pEnemy->m_nCntMove = 0;										//�J�E���^�[�̐ݒ�
//			pEnemy->m_nShootDelay = 0;									//�J�E���^�[�̐ݒ�
//			pEnemy->SetTextureParameter(1, 1, 1, INT_MAX);				//�e�N�X�`���p�����[�^�̐ݒ�
//			pEnemy->SetSize(D3DXVECTOR2(40.0f, 40.0f));					//�T�C�Y�̐ݒ�
//
//			pEnemy->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));				//���x�̐ݒ�
//			pEnemy->SetAcceleration(D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//�����̐ݒ�
//			pEnemy->SetSubtype(type);									//�G�̎�ނ̐ݒ�
//
//			pEnemy->SetTexture(TextureClock);							//�e�N�X�`���̐ݒ�
//
//			break;
//
//		default:
//			break;
//		}
//	}
//
//	return pEnemy;				//�������ꂽ�C���X�^���X�ւ̃|���^��Ԃ�
//}

//�܌^�G�̍X�V����
//void CEnemy::UpdateCloud(void)
//{
//	LPDIRECT3DVERTEXBUFFER9 pBuffer = CObject_2D::GetVtxbuff();									//�o�b�t�@�̎擾����
//	D3DXVECTOR3 pos = GetPos();																	//�ʒu�̎擾����
//	CPlayer* pPlayer = CObject::GetPlayer();													//�v���C���[���̎擾����
//	D3DXVECTOR3 PosPlayer = pPlayer->GetPos();													//�v���C���[�̈ʒu�̎擾����
//	D3DXVECTOR3 move = GetMove();																//���x�̎擾����
//	D3DXVECTOR3 acc = GetAcceleration();														//�����̎擾����
//	D3DXVECTOR2 Size = pPlayer->GetSize();														//�T�C�Y�̎擾����
//	D3DXVECTOR3 target = D3DXVECTOR3(PosPlayer.x, PosPlayer.y - (1.5f * Size.y), 0.0f);			//�ړI�̈ʒu�̍��W���v�Z����
//	int nColumn = 0;
//
//	VERTEX_2D* pVtx = nullptr;					//���_���ւ̃|�C���^
//
//	switch (m_nPhase)
//	{
//	case 0:
//
//	{//�v���C���[�̏�Ɍ�����
//
//		D3DXVECTOR3 move = target - pos;			//���x�̌������v�Z����
//		D3DXVec3Normalize(&move, &move);			//�����𐳋K������
//		move.x *= m_maxSpeed;
//		move.y *= m_maxSpeed;
//
//		pos += move;								//�ʒu�̍X�V
//
//													//�v���C���[�Ƃ̋������v�Z����
//		float fDistance = sqrtf(((target.x - pos.x) * (target.x - pos.x)) + ((target.y - pos.y) * (target.y - pos.y)));
//
//		if (fDistance <= 5.0f)
//		{//���֐i��
//			m_nPhase++;
//		}
//
//	}
//	break;
//
//	case 1:
//
//		//1.5�b�ԃv���C���[�̏�ɐݒ肷��
//
//		m_nShootDelay++;
//
//		pos = target;				//�ʒu�̐ݒ�
//
//		if (m_nShootDelay >= 90)
//		{//1.5�b�Ԍ㎟�֐i��
//			m_nShootDelay = 0;
//			m_nPhase++;
//		}
//
//		break;
//
//	case 2:
//
//		//�����Ȃ��Ȃ�����A�e�N�X�`���A�j���[�V�����ƒe�̔���
//
//		m_nShootDelay++;
//
//		if (m_nShootDelay < 30 || m_nShootDelay >= 110)
//		{//�����_
//			nColumn = 0;
//		}
//		else if (m_nShootDelay >= 30 && m_nShootDelay < 60 || m_nShootDelay >= 100 && m_nShootDelay < 110)
//		{//�D�F�̉_
//			nColumn = 1;
//		}
//		else if (m_nShootDelay >= 60 && m_nShootDelay < 100)
//		{//�����_
//			nColumn = 2;
//		}
//
//		if (m_nShootDelay == 90)
//		{//�e�𐶐�����
//			CBullet* pBullet = CBullet::Create(D3DXVECTOR3(pos.x, pos.y + 75.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(30.0f, 100.0f), CBullet::BULLET_THUNDER);
//		}
//		if (m_nShootDelay == 120)
//		{//���֐i��
//			move = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);		//���x�̐ݒ�
//			acc = D3DXVECTOR3(0.0f, -0.3f, 0.0f);		//�����̐ݒ�
//			m_nShootDelay = 0;							//�J�E���^�[�̐ݒ�
//			m_nPhase++;
//		}
//
//		break;
//
//	case 3:
//
//		//��ʂ��o��
//
//		pos += move;			//�ʒu�̍X�V
//		move += acc;			//���x�̍X�V
//
//		if (pos.x <= -GetSize().x || pos.y <= -GetSize().y)
//		{//��ʂ��o����A�e������
//			Release();
//			return;
//		}
//
//		break;
//
//	default:
//		break;
//	}
//
//	SetPos(pos);				//�ʒu�̐ݒ�
//	SetMove(move);				//���x�̐ݒ�
//	SetAcceleration(acc);		//�����̐ݒ�
//
//								//�A�j���[�V��������
//	m_fAngleMove += 1.0f;		//�J�E���^�[�̍X�V
//
//	if (m_fAngleMove >= 15.0f)
//	{
//		m_fAngleMove = 0.0f;
//		m_nCntMove ^= 1;
//	}
//
//	//���_�o�b�t�@�����b�N����
//	pBuffer->Lock(0, 0, (void**)&pVtx, 0);
//
//	//���_���W�̍X�V
//	pVtx[0].pos = D3DXVECTOR3(pos.x - (Size.x * 0.5f), pos.y - (Size.y * 0.5f), 0.0f);
//	pVtx[1].pos = D3DXVECTOR3(pos.x + (Size.x * 0.5f), pos.y - (Size.y * 0.5f), 0.0f);
//	pVtx[2].pos = D3DXVECTOR3(pos.x - (Size.x * 0.5f), pos.y + (Size.y * 0.5f), 0.0f);
//	pVtx[3].pos = D3DXVECTOR3(pos.x + (Size.x * 0.5f), pos.y + (Size.y * 0.5f), 0.0f);
//
//	//�e�N�X�`�����W�̍X�V
//	pVtx[0].tex = D3DXVECTOR2(0.0f + 0.5f * (m_nCntMove), 0.0f + 0.3334f * (nColumn));
//	pVtx[1].tex = D3DXVECTOR2(0.5f + 0.5f * (m_nCntMove), 0.0f + 0.3334f * (nColumn));
//	pVtx[2].tex = D3DXVECTOR2(0.0f + 0.5f * (m_nCntMove), 0.3334f + 0.3334f * (nColumn));
//	pVtx[3].tex = D3DXVECTOR2(0.5f + 0.5f * (m_nCntMove), 0.3334f + 0.3334f * (nColumn));
//
//	//���_�o�b�t�@���A�����b�N����
//	pBuffer->Unlock();
//}