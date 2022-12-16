//=============================================================================
//
// towerJewel.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "towerJewel.h"
#include "circleHitbox.h"
#include "greedBullet.h"
#include "application.h"
#include "sound.h"

//�R���X�g���N�^
CTowerJewel::CTowerJewel()
{
	//�����o�[�ϐ����N���A����
	m_state = state_spawn;

	m_pHitBox = nullptr;
}

//�f�X�g���N�^
CTowerJewel::~CTowerJewel()
{

}

//����������
HRESULT CTowerJewel::Init(void)
{
	//�����o�[�ϐ�������������
	if (FAILED(CEnemy::Init()))
	{//��{�N���X�̏���������
		return -1;
	}

	m_state = state_wait;

	m_pHitBox = nullptr;

	return S_OK;
}

//�I������
void CTowerJewel::Uninit(void)
{
	//�q�b�g�{�b�N�X�̔j������
	if (m_pHitBox != nullptr)
	{//null�`�F�b�N
		m_pHitBox->Release();			//���������������
		m_pHitBox = nullptr;			//null�ɂ���
	}
}

//�X�V����
void CTowerJewel::Update(void)
{
	//�q�b�g�{�b�N�X�̍X�V
	if (m_pHitBox != nullptr)
	{//null�`�F�b�N
		m_pHitBox->SetPos(GetPos());			//�ʒu�̐ݒ�
	}

	switch (m_state)
	{//��Ԃɂ���čX�V����

	case CTowerJewel::state_spawn:

	{//�X�|�[�����
		D3DXVECTOR3 pos = GetPos();							//�ʒu�̎擾
		D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//���x

		//�ړ��ʂ̐ݒ�
		if (pos.x < (float)SCREEN_WIDTH * 0.5f)
		{
			move.x = 2.0f;
		}
		else
		{
			move.x = -2.0f;
		}

		if (pos.x >= 100.0f && move.x > 0.0f || pos.x < (float)SCREEN_WIDTH - 100.0f && move.x < 0.0f)
		{//���܂������W�𒴂�����A��Ԃ�ς���
			move.x = 0.0f;				//�ړ��ʂ�0�ɂ���
			m_state = state_shoot;		//��Ԃ̐ݒ�
		}

		SetMove(move);					//�ړ��ʂ̐ݒ�
	}

		break;

	case CTowerJewel::state_shoot:

	{//�V���b�g���

		D3DXVECTOR3 pos = GetPos();									//�ʒu�̎擾
		D3DXVECTOR3 move = D3DXVECTOR3(4.0f, 0.0f, 0.0f);			//���x

		//���x�̐ݒ�
		if (pos.x > (float)SCREEN_WIDTH * 0.5f)
		{
			move.x *= -1.0f;
		}

		m_nShootDelay++;				//�J�E���^�[���C���N�������g����

		CGreedBullet* pBullet = nullptr;
		int a = GetPresentAnimPattern();

		if (m_nShootDelay % 30 == 29)
		{//30�t���[�����o������

			//�e�̐���
			pBullet = CGreedBullet::Create(pos, move);

			//�T�E���h���Đ�����
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_SHOT);

			if (pBullet != nullptr)
			{//�����o������
				pBullet->SetTexture(TextureJewel);		//�e�N�X�`���̐ݒ�
				pBullet->SetAnimPattern(a);				//�A�j���V�����p�^�[���̐ݒ�
				pBullet = nullptr;						
			}
		}
		if (m_nShootDelay % 60 == 59)
		{//60�t���[�����o������
			move.y = 1.0f;				//�e�̈ړ��ʂ�Y���W�̐ݒ�

			//�e�̐���
			pBullet = CGreedBullet::Create(pos, move);

			if (pBullet != nullptr)
			{	//�����o������
				pBullet->SetTexture(TextureJewel);		//�e�N�X�`���̐ݒ�
				pBullet->SetAnimPattern(a);				//�A�j���V�����p�^�[���̐ݒ�
				pBullet = nullptr;
			}

			move.y = -1.0f;				//�e�̈ړ��ʂ�Y���W�̐ݒ�
			//�e�̐���
			pBullet = CGreedBullet::Create(pos, move);

			if (pBullet != nullptr)
			{//�����o������
				pBullet->SetTexture(TextureJewel);		//�e�N�X�`���̐ݒ�
				pBullet->SetAnimPattern(a);				//�A�j���V�����p�^�[���̐ݒ�
				pBullet = nullptr;
			}
		}
		if (m_nShootDelay >= 90)
		{//90�t���[�����o������
			move.y = 1.0f;				//�e�̈ړ��ʂ�Y���W�̐ݒ�
			//�e�̐���
			pBullet = CGreedBullet::Create(pos, move);

			if (pBullet != nullptr)
			{//�����o������
				pBullet->SetTexture(TextureJewel);			//�e�N�X�`���̐ݒ�
				pBullet->SetAnimPattern(a);					//�A�j���V�����p�^�[���̐ݒ�
				pBullet = nullptr;
			}

			move.y = -1.0f;				//�e�̈ړ��ʂ�Y���W�̐ݒ�
			//�e�̐���
			pBullet = CGreedBullet::Create(pos, move);

			if (pBullet != nullptr)
			{//�����o������
				pBullet->SetTexture(TextureJewel);			//�e�N�X�`���̐ݒ�
				pBullet->SetAnimPattern(a);					//�A�j���V�����p�^�[���̐ݒ�
				pBullet = nullptr;
			}

			move.y = 2.0f;				//�e�̈ړ��ʂ�Y���W�̐ݒ�
			//�e�̐���
			pBullet = CGreedBullet::Create(pos, move);

			if (pBullet != nullptr)
			{//�����o������
				pBullet->SetTexture(TextureJewel);			//�e�N�X�`���̐ݒ�
				pBullet->SetAnimPattern(a);					//�A�j���V�����p�^�[���̐ݒ�
				pBullet = nullptr;
			}

			move.y = -2.0f;				//�e�̈ړ��ʂ�Y���W�̐ݒ�
			//�e�̐���
			pBullet = CGreedBullet::Create(pos, move);

			if (pBullet != nullptr)
			{//�����o������
				pBullet->SetTexture(TextureJewel);			//�e�N�X�`���̐ݒ�
				pBullet->SetAnimPattern(a);					//�A�j���V�����p�^�[���̐ݒ�
				pBullet = nullptr;
			}

			m_nShootDelay = 0;			//�J�E���^�[��0�ɖ߂�

			//���x�̐ݒ�
			if (pos.x < (float)SCREEN_WIDTH * 0.5f)
			{
				SetMove(D3DXVECTOR3(-2.0f, 0.0f, 0.0f));
			}
			else
			{
				SetMove(D3DXVECTOR3(2.0f, 0.0f, 0.0f));
			}

			m_state = state_despawn;	//��Ԃ̍X�V
		}
	}

		break;

	case CTowerJewel::state_despawn:

	{//�f�B�X�|�[�����

		D3DXVECTOR3 pos = GetPos();			//�ʒu�̎擾
		D3DXVECTOR3 move = GetMove();		//���x�̎擾

		if (move.x < 0.0f)
		{//��ʂ̍����̂ق��ֈړ�������
			if (pos.x <= -100.0f)
			{//-100.0f�𒴂�����A��Ԃ�؂�ւ���
				SetAnimPattern(random(0, 5));				//�A�j���V�����p�^�[���̐ݒ�
				SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//�ړ��̐ݒ�
				m_state = state_wait;						//��Ԃ̐ݒ�
			}
		}
		else
		{//��ʂ̉E���̂ق��ֈړ�������
			if (pos.x >= (float)SCREEN_WIDTH + 100.0f)
			{//+100.0f�𒴂�����A��Ԃ�؂�ւ���
				SetAnimPattern(random(0, 5));				//�A�j���V�����p�^�[���̐ݒ�
				SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//�ړ��̐ݒ�
				m_state = state_wait;						//��Ԃ̐ݒ�
			}
		}
	}

		break;

	case CTowerJewel::state_wait:
		break;

	default:
		break;
	}

	//��{�N���X�̍X�V����
	CObject_2D::Update();
}

//��Ԃ̐ݒ菈��
void CTowerJewel::SetState(CTowerJewel::state state)
{
	m_state = state;
}


//��������
CTowerJewel* CTowerJewel::Create(const D3DXVECTOR3 pos)
{
	CTowerJewel* pEnemy = new CTowerJewel;			//�C���X�^���X�𐶐�����

	if (FAILED(pEnemy->Init()))
	{//����������
		return nullptr;
	}

	pEnemy->SetPos(pos);								//�ʒu�̐ݒ�
	pEnemy->SetSize(D3DXVECTOR2(50.0f, 36.8f));			//�T�C�Y�̐ݒ�
	pEnemy->SetTexture(CObject::TextureJewel);			//�e�N�X�`���̐ݒ�
	pEnemy->SetTextureParameter(1, 3, 2, INT_MAX);		//�e�N�X�`���p�����[�^�̐ݒ�
	pEnemy->SetAnimPattern(random(0, 5));				//�A�j���V�����p�^�[���̐ݒ�
	pEnemy->SetStartingRot(D3DX_PI * 0.5f);				//�����̏����l�̐ݒ�

	//�q�b�g�{�b�N�X�̐���
	pEnemy->m_pHitBox = CCircleHitbox::Create(pos, 30.0f, CHitbox::Type_Enemy);

	return pEnemy;					//���������C���X�^���X��Ԃ�
}