//=============================================================================
//
// handFlamethrower.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "handFlamethrower.h"
#include "circleHitbox.h"
#include "handFireball.h"
#include "player.h"
#include "wrath.h"
#include "application.h"
#include "sound.h"

//�R���X�g���N�^
CHandFlamethrower::CHandFlamethrower()
{
	//�����o�[�ϐ����N���A����
	m_state = state_spawn;

	m_pHitbox = nullptr;
	m_pParent = nullptr;
}

//�f�X�g���N�^
CHandFlamethrower::~CHandFlamethrower()
{

}

//����������
HRESULT CHandFlamethrower::Init(void)
{
	//�����o�[�ϐ�������������
	if(FAILED(CEnemy::Init()))
	{
		return -1;
	}

	m_state = state_spawn;

	m_pHitbox = nullptr;
	m_pParent = nullptr;

	return S_OK;
}

//�I������
void CHandFlamethrower::Uninit(void)
{
	//�q�b�g�{�b�N�X�̔j������
	if (m_pHitbox != nullptr)
	{//null�`�F�b�N
		m_pHitbox->Release();			//���������������
		m_pHitbox = nullptr;			//null�ɂ���
	}

	//�e�ւ̃|�C���^��null�ł͂Ȃ�������Anull�ɂ���
	if (m_pParent != nullptr)
	{
		m_pParent = nullptr;
	}

	//��{�N���X�̏I������
	CEnemy::Uninit();
}

//�X�V����
void CHandFlamethrower::Update(void)
{
	//��{�N���X�̍X�V����
	CObject_2D::Update();

	//�q�b�g�{�b�N�X�̍X�V����
	if (m_pHitbox != nullptr)
	{//null�`�F�b�N

		m_pHitbox->SetPos(GetPos());			//�ʒu�̐ݒ�

		if (m_pHitbox->GetHitState())
		{//����������Ԃ�������

			m_pHitbox->SetHitState(false);		//�����Ă��Ȃ���Ԃɖ߂�

			int nDamage = CPlayer::GetPlayer()->GetAttack();		//�v���C���[�̍U���͂��擾����

			if (m_pParent != nullptr)
			{//�e�ւ̃|�C���^��null�ł͂Ȃ�������A

				m_pParent->Damage(nDamage);				//�e�Ƀ_���[�W��^����
			}
		}
	}

	//���S��Ԃ̊m�F
	if (m_pParent != nullptr)
	{//null�`�F�b�N
		if (m_pParent->GetDeath() && m_state != state_death)
		{//�e�����S��Ԃ�������

			m_state = state_death;						//���S��Ԃɂ���
			SetMove(D3DXVECTOR3(0.0f, 2.0f, 0.0f));		//�ړ��ʂ̐ݒ�
			m_nPhase = 0;								//�J�E���^�[��0�ɖ߂�
		}
	}

	updateState();				//��Ԃɂ���Ă̍X�V����
}

//�e�ւ̃|�C���^�̐ݒ菈��
void CHandFlamethrower::SetParent(CWrath* pParent)
{
	m_pParent = pParent;
}



//=============================================================================
//
//								�ÓI�֐�
//
//=============================================================================



//��������
CHandFlamethrower* CHandFlamethrower::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CHandFlamethrower* pEnemy = new CHandFlamethrower;			//�C���X�^���X�𐶐�����

	if (FAILED(pEnemy->Init()))
	{//����������
		return nullptr;
	}

	pEnemy->SetPos(pos);									//�ʒu�̐ݒ�
	pEnemy->SetMove(move);									//���x�̐ݒ�
	pEnemy->SetStartingRot(D3DX_PI * 0.5f);					//�����̏����l�̐ݒ�
	pEnemy->SetSize(D3DXVECTOR2(120.0f, 80.0f));			//�T�C�Y�̐ݒ�
	pEnemy->SetTexture(CObject::TextureHand);				//�e�N�X�`���̐ݒ�
	pEnemy->SetTextureParameter(1, 4, 2, INT_MAX);			//�e�N�X�`���p�����[�^�̐ݒ�
	pEnemy->SetAnimPattern(1);								//�A�j���V�����p�^�[���̐ݒ�
	pEnemy->SetPriority(2);									//�v���C�I���e�B�̐ݒ�

	//�ʒu�ɂ���ăe�N�X�`���𔽓]����
	if (pos.x <= 0.0f)
	{
		pEnemy->FlipX();
	}

	//�q�b�g�{�b�N�X�̐���
	pEnemy->m_pHitbox = CCircleHitbox::Create(pos, 75.0f, CHitbox::Type_Enemy);

	return pEnemy;					//���������C���X�^���X��Ԃ�
}





void CHandFlamethrower::updateState(void)
{
	switch (m_state)
	{
	case CHandFlamethrower::state_spawn:

	{
		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 move = GetMove();

		if (move.x >= 0.0f && pos.x >= 100.0f || move.x < 0.0f && pos.x <= (float)SCREEN_WIDTH - 100.0f)
		{
			SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			m_state = state_shoot;
		}
	}

		break;

	case CHandFlamethrower::state_shoot:

	{
		m_nShootDelay++;

		if (m_nShootDelay % 20 == 1)
		{
			D3DXVECTOR3 pos = GetPos();

			if (pos.x < (float)SCREEN_WIDTH * 0.5f)
			{
				CHandFireball::Create(D3DXVECTOR3(pos.x + 100.0f, pos.y - 20.0f, 0.0f), D3DXVECTOR3(4.0f, 2.0f, 0.0f));
			}
			else
			{
				CHandFireball::Create(D3DXVECTOR3(pos.x - 100.0f, pos.y - 20.0f, 0.0f), D3DXVECTOR3(-4.0f, 2.0f, 0.0f));
			}

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_FIRE);
		}

		if (m_nShootDelay >= 300)
		{
			m_nShootDelay = 0;
			m_state = state_return;
		}
	}

		break;

	case CHandFlamethrower::state_return:

	{
		D3DXVECTOR3 pos = GetPos();

		if (pos.x < (float)SCREEN_WIDTH * 0.5f)
		{
			SetMove(D3DXVECTOR3(-2.0f, 0.0f, 0.0f));
		}
		else
		{
			SetMove(D3DXVECTOR3(2.0f, 0.0f, 0.0f));
		}
	}

		break;

	case CHandFlamethrower::state_despawn:

	{
		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 move = GetMove();

		if (move.x >= 0.0f && pos.x >= 100.0f || move.x < 0.0f && pos.x <= (float)SCREEN_WIDTH - 100.0f)
		{
			Release();
			return;
		}
	}

	break;

	case CHandFlamethrower::state_death:

	{
		m_nPhase++;

		if (m_nPhase % 15 == 0)
		{
			D3DXCOLOR col = GetColor();

			if (col.g < 0.5f)
			{
				SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else
			{
				SetColor(D3DXCOLOR(1.0f, 0.3f, 0.3f, 1.0f));
			}
		}
		
	}

	break;

	default:
		break;
	}
}