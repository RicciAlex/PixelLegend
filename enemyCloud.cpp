//=============================================================================
//
// enemyCloud.cpp
// Author : Ricci Alex
//
//=============================================================================

//�C���N���[�h�t�@�C��
#include "enemyCloud.h"
#include "player.h"
#include "thunderEnemy.h"

//�R���X�g���N�^
CEnemyCloud::CEnemyCloud()
{
	//�����o�[�ϐ����N���A����
	m_nCntMove = 0;
	m_fAngleMove = 0.0f;
	m_nPhase = state_max;
	m_nShootDelay = 0;
}

//�f�X�g���N�^ 
CEnemyCloud::~CEnemyCloud()
{

}

//����������
HRESULT CEnemyCloud::Init(void)
{
	//�����o�[�ϐ�������������

	//��{�N���X�̏���������
	if (FAILED(CEnemy::Init()))
	{
		return -1;
	}

	//�����o�[�ϐ��̏�����
	m_nCntMove = 0;
	m_fAngleMove = 0.0f;
	m_nPhase = state_max;
	m_nShootDelay = 0;

	return S_OK;
}

//�I������
void CEnemyCloud::Uninit(void)
{
	//��{�N���X�̏I������
	CEnemy::Uninit();
}

//�X�V����
void CEnemyCloud::Update(void)
{
	float maxSpeed = GetMaxSpeed();
	LPDIRECT3DVERTEXBUFFER9 pBuffer = CObject_2D::GetVtxbuff();									//�o�b�t�@�̎擾����
	D3DXVECTOR3 pos = GetPos();																	//�ʒu�̎擾����
	CPlayer* pPlayer = CPlayer::GetPlayer();													//�v���C���[���̎擾����
	D3DXVECTOR3 PosPlayer = pPlayer->GetPos();													//�v���C���[�̈ʒu�̎擾����
	D3DXVECTOR3 move = GetMove();																//���x�̎擾����
	D3DXVECTOR3 acc = GetAcceleration();														//�����̎擾����
	D3DXVECTOR2 Size = pPlayer->GetSize();														//�T�C�Y�̎擾����
	D3DXVECTOR3 target = D3DXVECTOR3(PosPlayer.x, PosPlayer.y - (1.5f * Size.y), 0.0f);			//�ړI�̈ʒu�̍��W���v�Z����
	int nColumn = 0;

	VERTEX_2D* pVtx = nullptr;					//���_���ւ̃|�C���^

	switch (m_nPhase)
	{
	case state_pursuit:

	{//�v���C���[�̏�Ɍ�����

		move = target - pos;			//���x�̌������v�Z����
		D3DXVec3Normalize(&move, &move);			//�����𐳋K������
		move.x *= maxSpeed;
		move.y *= maxSpeed;

		pos += move;								//�ʒu�̍X�V

													//�v���C���[�Ƃ̋������v�Z����
		float fDistance = sqrtf(((target.x - pos.x) * (target.x - pos.x)) + ((target.y - pos.y) * (target.y - pos.y)));

		if (fDistance <= 5.0f)
		{//���֐i��
			m_nPhase = state_aim;
		}

	}
	break;

	case state_aim:

		//1.5�b�ԃv���C���[�̏�ɐݒ肷��

		m_nShootDelay++;

		pos = target;				//�ʒu�̐ݒ�

		if (m_nShootDelay >= 90)
		{//1.5�b�Ԍ㎟�֐i��
			m_nShootDelay = 0;
			m_nPhase = state_fire;
		}

		break;

	case state_fire:

		//�����Ȃ��Ȃ�����A�e�N�X�`���A�j���[�V�����ƒe�̔���

		m_nShootDelay++;

		if (m_nShootDelay < 30 || m_nShootDelay >= 110)
		{//�����_
			nColumn = 0;
		}
		else if (m_nShootDelay >= 30 && m_nShootDelay < 60 || m_nShootDelay >= 100 && m_nShootDelay < 110)
		{//�D�F�̉_
			nColumn = 1;
		}
		else if (m_nShootDelay >= 60 && m_nShootDelay < 100)
		{//�����_
			nColumn = 2;
		}

		if (m_nShootDelay == 90)
		{//�e�𐶐�����
			CThunderEnemy* pBullet = CThunderEnemy::Create(D3DXVECTOR3(pos.x, pos.y + 75.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(20.0f, 66.0f));
		}
		if (m_nShootDelay == 120)
		{//���֐i��
			move = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);		//���x�̐ݒ�
			acc = D3DXVECTOR3(0.0f, -0.3f, 0.0f);		//�����̐ݒ�
			m_nShootDelay = 0;							//�J�E���^�[�̐ݒ�
			m_nPhase = state_flee;
		}

		break;

	case state_flee:

		//��ʂ��o��

		pos += move;			//�ʒu�̍X�V
		move += acc;			//���x�̍X�V

		if (pos.x <= -GetSize().x || pos.y <= -GetSize().y)
		{//��ʂ��o����A�e������
			Release();
			return;
		}

		break;

	default:
		break;
	}

	SetPos(pos);				//�ʒu�̐ݒ�
	SetMove(move);				//���x�̐ݒ�
	SetAcceleration(acc);		//�����̐ݒ�

								//�A�j���[�V��������
	m_fAngleMove += 1.0f;		//�J�E���^�[�̍X�V

	if (m_fAngleMove >= 15.0f)
	{
		m_fAngleMove = 0.0f;
		m_nCntMove ^= 1;
	}

	//���_�o�b�t�@�����b�N����
	pBuffer->Lock(0, 0, (void**)&pVtx, 0);

	Size = GetSize();

	//���_���W�̍X�V
	pVtx[0].pos = D3DXVECTOR3(pos.x - (Size.x * 0.5f), pos.y - (Size.y * 0.5f), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + (Size.x * 0.5f), pos.y - (Size.y * 0.5f), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - (Size.x * 0.5f), pos.y + (Size.y * 0.5f), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + (Size.x * 0.5f), pos.y + (Size.y * 0.5f), 0.0f);

	//�e�N�X�`�����W�̍X�V
	pVtx[0].tex = D3DXVECTOR2(0.0f + 0.5f * (m_nCntMove), 0.0f + 0.3334f * (nColumn));
	pVtx[1].tex = D3DXVECTOR2(0.5f + 0.5f * (m_nCntMove), 0.0f + 0.3334f * (nColumn));
	pVtx[2].tex = D3DXVECTOR2(0.0f + 0.5f * (m_nCntMove), 0.3334f + 0.3334f * (nColumn));
	pVtx[3].tex = D3DXVECTOR2(0.5f + 0.5f * (m_nCntMove), 0.3334f + 0.3334f * (nColumn));

	//���_�o�b�t�@���A�����b�N����
	pBuffer->Unlock();
}

//�`�揈��
void CEnemyCloud::Draw(void)
{
	//��{�N���X�̕`�揈��
	CEnemy::Draw();
}

CEnemyCloud* CEnemyCloud::Create(D3DXVECTOR3 pos)
{
	CEnemyCloud* pEnemy = new CEnemyCloud;			//�V�����G�𐶐�����

	if (pEnemy != nullptr)
	{
		//����������
		if (FAILED(pEnemy->Init()))
		{
			delete pEnemy;					//���������������
			return nullptr;					//null��Ԃ�
		}

		pEnemy->SetObjType(CObject::OBJTYPE_ENEMY);					//�I�u�W�F�N�g�̎�ނ̐ݒ�
		pEnemy->SetPos(pos);										//�ʒu�̐ݒ�
		pEnemy->SetMaxSpeed(10.0f);									//�ő呬�x�̐ݒ�
		pEnemy->SetTextureParameter(2, 2, 3, 15);					//�e�N�X�`���p�����[�^�̐ݒ�
		pEnemy->SetSize(D3DXVECTOR2(50.0f, 40.0f));					//�T�C�Y�̐ݒ�

		pEnemy->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));				//���x�̐ݒ�
		pEnemy->SetAcceleration(D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//�����̐ݒ�
		pEnemy->SetSubtype(CEnemy::ENEMYTYPE_CLOUD);				//�G�̎�ނ̐ݒ�
		pEnemy->m_nPhase = state_pursuit;

		pEnemy->SetTexture(TextureCloud);							//�e�N�X�`���̐ݒ�
	}

	return pEnemy;				//�������ꂽ�C���X�^���X�ւ̃|���^��Ԃ�
}