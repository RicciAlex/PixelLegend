//=============================================================================
//
// skull.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "Skull.h"
#include "player.h"
#include "squareHitbox.h"

//�R���X�g���N�^
CSkull::CSkull()
{
	//�����o�[�ϐ����N���A����
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCntDestroy = 0;
	m_bDead = false;

	m_pHitbox = nullptr;
}

//�f�X�g���N�^
CSkull::~CSkull()
{

}

//����������
HRESULT CSkull::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CEnemy::Init()))
	{
		return -1;
	}

	//�����o�[�ϐ��̏�����
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCntDestroy = 0;
	m_bDead = false;
	SetLife(5000);

	return S_OK;
}

//�I������
void CSkull::Uninit(void)
{
	//�q�b�g�{�b�N�X�̔j������
	if (m_pHitbox != nullptr)
	{//null�`�F�b�N
		m_pHitbox->Release();		//���������������
		m_pHitbox = nullptr;		//�|�C���^��null�ɂ���
	}

	//��{�N���X�̏I������
	CEnemy::Uninit();
}

//�X�V����
void CSkull::Update(void)
{
	//��{�N���X�̍X�V����
	CObject_2D::Update();

	//�q�b�g�{�b�N�X�̍X�V����
	if (m_pHitbox)
	{//null�`�F�b�N

		m_pHitbox->SetPos(GetPos());		//�ʒu�̐ݒ�

		if (m_pHitbox->Hit() || m_pHitbox->GetHitState())
		{//����������Ԃ�������

			int nDamage = CPlayer::GetPlayer()->GetAttack();		//�v���C���[�̍U���͂̎擾
			SetLife(GetLife() - nDamage);							//�̗͍X�V�Ƃ̐ݒ�
			m_pHitbox->SetHitState(false);							//�����Ă��Ȃ���Ԃɖ߂�
		}
	}

	//���S�A�j���[�V��������
	if (m_bDead)
	{
		m_nCntDestroy--;			//���S�J�E���^�[���f�N�������g����

		if (m_nCntDestroy <= 0)
		{//���S�J�E���^�[��0�ȉ��ɂȂ�����
			Release();				//�j������
		}
	}
}

//���S�A�j���[�V��������
void CSkull::Kill(void)
{
	m_bDead = true;			//���񂾏�Ԃɂ���

	//�����_���ȕ����Ɉړ������āA��]������
	D3DXVECTOR3 dir = D3DXVECTOR3((float)random(-5000, 5000), (float)random(-5000, 5000), 0.0f);
	D3DXVec3Normalize(&dir, &dir);
	dir.x *= 2.0f;
	dir.y *= 2.0f;

	SetMove(dir);
	SetRotation(((float)random(-100, 100) * 0.01f) * D3DX_PI * 0.1f);
	SetAcceleration(D3DXVECTOR3(0.0f, 0.05f, 0.0f));
	m_nCntDestroy = 120;
}


//========================================================================================================
//										�ÓI�֐�
//========================================================================================================

//��������
CSkull* CSkull::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	CSkull* pSkull = new CSkull;					//���������m�ۂ���

	//����������
	if (FAILED(pSkull->Init()))
	{
		return nullptr;
	}

	pSkull->SetPos(pos);										//�ʒu�̐ݒ�
	pSkull->SetSize(size);										//�T�C�Y�̐ݒ�

	pSkull->SetObjType(CObject::OBJTYPE_ENEMY);					//�I�u�W�F�N�g�̎�ނ̐ݒ�

	pSkull->SetStartingRot(D3DX_PI * 0.5f);						//��]�p�x�̏����l�̐ݒ�
	pSkull->SetMaxSpeed(12.5f);									//�ő呬�x�̐ݒ�
	pSkull->SetTextureParameter(1, 3, 1, INT_MAX);				//�e�N�X�`���p�����[�^�̐ݒ�
	pSkull->SetSize(size);										//�T�C�Y�̐ݒ�

	pSkull->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));				//���x�̐ݒ�
	pSkull->SetAcceleration(D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//�����̐ݒ�
	pSkull->SetSubtype(ENEMYTYPE_SKULL);						//�G�̎�ނ̐ݒ�

	pSkull->SetTexture(TextureSkull);							//�e�N�X�`���̐ݒ�

	//�q�b�g�{�b�N�X�̐���
	pSkull->m_pHitbox = CSquareHitbox::Create(pos, D3DXVECTOR2(size.x * 0.5f, size.y * 0.5f), CHitbox::Type_Enemy);

	return pSkull;							//���������C���X�^���X��Ԃ�
} 