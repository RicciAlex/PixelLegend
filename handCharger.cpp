//=============================================================================
//
// handCharger.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "handCharger.h"
#include "squareHitbox.h"
#include "handblade.h"
#include "player.h"
#include "wrath.h"
#include"application.h"
#include "sound.h"

//�R���X�g���N�^
CHandCharger::CHandCharger()
{
	//�����o�[�ϐ����N���A����
	m_targetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_state = state_spawn;

	m_pHitbox = nullptr;
	m_pParent = nullptr;
}

//�f�X�g���N�^
CHandCharger::~CHandCharger()
{

}

//����������
HRESULT CHandCharger::Init(void)
{
	//�����o�[�ϐ�������������
	if (FAILED(CEnemy::Init()))
	{//��{�N���X�̏���������
		return -1;
	}

	m_targetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_state = state_spawn;

	m_pHitbox = nullptr;
	m_pParent = nullptr;

	return S_OK;
}

//�I������
void CHandCharger::Uninit(void)
{
	//�q�b�g�{�b�N�X�̔j������
	if (m_pHitbox != nullptr)
	{//null�`�F�b�N
		m_pHitbox->Release();				//���������������
		m_pHitbox = nullptr;				//null�ɂ���
	}

	//�e�ւ̃|�C���^��null�ł͂Ȃ�������Anull�ɖ߂�
	if (m_pParent != nullptr)
	{
		m_pParent = nullptr;
	}

	//��{�N���X�̏I������
	CEnemy::Uninit();
}

//�X�V����
void CHandCharger::Update(void)
{
	//��{�N���X�̍X�V����
	CObject_2D::Update();

	//�q�b�g�{�b�N�X�̍X�V
	if (m_pHitbox != nullptr)
	{//null�`�F�b�N

		m_pHitbox->SetPos(GetPos());			//�ʒu�̐ݒ�

		if (m_pHitbox->GetHitState())
		{//����������Ԃ�������

			m_pHitbox->SetHitState(false);		//�����Ă��Ȃ���Ԃɖ߂�

			int nDamage = CPlayer::GetPlayer()->GetAttack();		//�v���C���[�̍U���͂��擾����

			if (m_pParent != nullptr)
			{//�e�ւ̃|�C���^��null�ł͂Ȃ�������

				m_pParent->Damage(nDamage);			//�e�Ƀ_���[�W��^����
			}
		}
	}

	//�e�����񂾂��ǂ������m�F����
	if (m_pParent != nullptr)
	{//null�`�F�b�N
		if (m_pParent->GetDeath() && m_state != state_death)
		{//���񂾏�Ԃ�������

			m_state = state_death;								//��Ԃ̍X�V
			SetMove(D3DXVECTOR3(5.0f, -5.0f, 0.0f));			//�ړ��ʂ̐ݒ�
			SetAcceleration(D3DXVECTOR3(0.0f, 0.1f, 0.0f));		//�����̐ݒ�
			SetRotation(D3DX_PI * 0.01f);						//��]������
			m_nPhase = 0;										//�J�E���^�[��0�ɖ߂�
		}
	}

	UpdateState();				//��Ԃɂ���Ă̍X�V����
}

//�e�ւ̃|�C���^�̐ݒ菈��
void CHandCharger::SetParent(CWrath* pParent)
{
	m_pParent = pParent;
}



//=============================================================================
//
//								�ÓI�֐�
//
//=============================================================================



//��������
CHandCharger* CHandCharger::Create(D3DXVECTOR3 pos)
{
	CHandCharger* pEnemy = new CHandCharger;			//�C���X�^���X�𐶐�����
		
	if (FAILED(pEnemy->Init()))
	{//����������
		return nullptr;
	}

	pEnemy->SetPos(pos);									//�ʒu�̐ݒ�
	pEnemy->SetMove(D3DXVECTOR3(0.0f, 2.0f, 0.0f));			//���x�̐ݒ�
	pEnemy->SetStartingRot(D3DX_PI * 0.5f);					//�����̏����l�̐ݒ�
	pEnemy->SetSize(D3DXVECTOR2(120.0f, 80.0f));			//�T�C�Y�̐ݒ�
	pEnemy->SetTexture(CObject::TextureHand);				//�e�N�X�`���̐ݒ�
	pEnemy->SetTextureParameter(1, 4, 2, INT_MAX);			//�e�N�X�`���p�����[�^�̐ݒ�
	pEnemy->SetAnimPattern(5);								//�A�j���V�����p�^�[���̐ݒ�
	pEnemy->SetPriority(3);									//�v���C�I���e�B�̐ݒ�

	//�q�b�g�{�b�N�X�̐���
	pEnemy->m_pHitbox = CSquareHitbox::Create(pos, D3DXVECTOR2(75.0f, 20.0f), CHitbox::Type_Enemy);

	return pEnemy;				//���������C���X�^���X��Ԃ�
}


//=============================================================================
//
//							�v���C�x�[�g�֐�
//
//=============================================================================

//��Ԃɂ���Ă̍X�V����
void CHandCharger::UpdateState(void)
{
	D3DXVECTOR3 pos = GetPos();			//�ʒu�̎擾

	switch (m_state)
	{
	case CHandCharger::state_spawn:

	{//�X�|�[�����

		if (m_nPhase == 0)
		{
			if (pos.y >= 100.0f)
			{//������悤�ɂȂ�����A�~�܂�
				SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				m_nPhase++;
			}
		}
		else if (m_nPhase == 1)
		{
			m_nShootDelay++;			//�U���J�E���^�[���X�V����

			if (m_nShootDelay >= 30)
			{//30�t���[�����o������
				m_nShootDelay = 0;														//�U���J�E���^�[��0�ɖ߂�
				m_nPhase = 0;															//�J�E���^�[��0�ɖ߂�
				m_state = state_attack;													//��Ԃ��X�V����
				SetMove(D3DXVECTOR3(0.0f, 20.0f, 0.0f));								//�ړ��ʂ̐ݒ�
				m_targetPos = CPlayer::GetPlayer()->GetPos();							//�v���C���[�̈ʒu�̎擾
				m_targetPos.x = pos.x;													//�ړI�̈ʒu�̐ݒ�
				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_HAND_WOOSH);		//�T�E���h���Đ�����
			}
		}
	}

	break;

	case CHandCharger::state_attack:

	{//�U�����

		if (pos.y >= m_targetPos.y)
		{//�ړI�̈ʒu�𒴂�����

			SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));								//���x�̐ݒ�
			m_state = state_return;												//��Ԃ̍X�V
			SetAnimPattern(6);													//�A�j���V�����p�^�[���̐ݒ�
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_HAND_HIT);	//�T�E���h���Đ�����
		}
	}

	break;

	case CHandCharger::state_return:

	{//�߂���

		m_nCntMove++;			//�ړ��J�E���^�[�̍X�V

		if (m_nCntMove == 60)
		{//1�b���o������

			SetMove(D3DXVECTOR3(0.0f, -7.0f, 0.0f));			//���x�̐ݒ�
			m_state = state_despawn;							//��Ԃ̍X�V
			SetAnimPattern(5);									//�A�j���V�����p�^�[���̐ݒ�
		}
	}

	break;

	case CHandCharger::state_despawn:

	{//�f�B�X�|�[�����

		if (pos.y <= -100.0f)
		{//�����Ȃ��Ȃ�����
			Release();			//�j������
			return;
		}
	}

	break;

	case CHandCharger::state_death:

	{//���S���

		m_nPhase++;			//�J�E���^�[�̍X�V

		if (m_nPhase % 15 == 0)
		{//15�t���[������

			D3DXCOLOR col = GetColor();			//�F�̎擾

			if (col.g < 0.5f)
			{//�Ԃ�������A���ʂ̐F�ɖ߂�
				SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else
			{//���ʂ̐F��������A�Ԃ�����
				SetColor(D3DXCOLOR(1.0f, 0.3f, 0.3f, 1.0f));
			}
		}

	}

		break;

	default:
		break;
	}
}