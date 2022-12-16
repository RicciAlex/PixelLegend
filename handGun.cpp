//=============================================================================
//
// handGun.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "handGun.h"
#include "circleHitbox.h"
#include "handblade.h"
#include "player.h"
#include "wrath.h"
#include "application.h"
#include "sound.h"

//�R���X�g���N�^
CHandGun::CHandGun()
{
	//�����o�[�ϐ����N���A����
	m_state = state_spawn;

	m_pHitbox = nullptr;
	m_pParent = nullptr;
}

//�f�X�g���N�^
CHandGun::~CHandGun()
{

}

//����������
HRESULT CHandGun::Init(void)
{
	//�����o�[�ϐ�������������
	if (FAILED(CEnemy::Init()))
	{//��{�N���X�̏���������
		return -1;
	}

	m_state = state_spawn;

	m_pHitbox = nullptr;
	m_pParent = nullptr;

	return S_OK;
}

//�I������
void CHandGun::Uninit(void)
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
void CHandGun::Update(void)
{
	//��{�N���X�̍X�V����
	CObject_2D::Update();

	//�q�b�g�{�b�N�X�̍X�V����
	if (m_pHitbox != nullptr)
	{//null�`�F�b�N

		m_pHitbox->SetPos(GetPos());			//�ʒu�̐ݒ�

		if (m_pHitbox->GetHitState())
		{//����������Ԃ�������

			m_pHitbox->SetHitState(false);		//���ʏ�Ԃɖ߂�

			int nDamage = CPlayer::GetPlayer()->GetAttack();			//�v���C���[�̍U���͂��擾����

			//�e�Ƀ_���[�W��^����
			if (m_pParent != nullptr)
			{//null�`�F�b�N
				m_pParent->Damage(nDamage);				//�_���[�W�̐ݒ�
			}
		}
	}

	//���S��Ԃ̊m�F
	if (m_pParent != nullptr)
	{//null�`�F�b�N
		if (m_pParent->GetDeath() && m_state != state_death)
		{//���񂾂�A���S�A�j���[�V�������Đ�����

			m_state = state_death;							//��Ԃ̍X�V
			m_nPhase = 0;									//�J�E���^�[��0�ɖ߂�
			SetMove(D3DXVECTOR3(0.0f, 2.0f, 0.0f));			//�ړ��ʂ̐ݒ�
		}
	}

	UpdateState();		//��Ԃɂ���Ă̍X�V����
}

//�e�ւ̃|�C���^�̐�������
void CHandGun::SetParent(CWrath* pParent)
{
	m_pParent = pParent;
}



//=============================================================================
//
//								�ÓI�֐�
//
//=============================================================================



//��������
CHandGun* CHandGun::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CHandGun* pEnemy = new CHandGun;			//�C���X�^���X�𐶐�����

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
	pEnemy->SetAnimPattern(2);								//�A�j���V�����p�^�[���̐ݒ�
	pEnemy->SetPriority(3);									//�v���C�I���e�B�̐ݒ�

	//X���W�ɂ���ăe�N�X�`���𔽓]����
	if (pos.x <= 0.0f)
	{
		pEnemy->FlipX();
	}

	//�q�b�g�{�b�N�X�̐���
	pEnemy->m_pHitbox = CCircleHitbox::Create(pos, 60.0f, CHitbox::Type_Enemy);

	return pEnemy;					//���������C���X�^���X��Ԃ�
}


//=============================================================================
//
//							�v���C�x�[�g�֐�
//
//=============================================================================

//��Ԃɂ���Ă̍X�V����
void CHandGun::UpdateState(void)
{
	switch (m_state)
	{
	case CHandGun::state_spawn:

	{//�X�|�[�����

		D3DXVECTOR3 pos = GetPos();			//�ʒu�̎擾
		D3DXVECTOR3 move = GetMove();		//���x�̎擾

		if (move.x >= 0.0f && pos.x >= 100.0f || move.x < 0.0f && pos.x <= (float)SCREEN_WIDTH - 100.0f)
		{//���܂����ʒu�𒴂�����

			SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));				//���x��0�ɂ���
			m_state = state_shoot;								//��Ԃ̍X�V
		}
	}

	break;

	case CHandGun::state_shoot:

	{//�V���b�g���

		m_nShootDelay++;				//�U���J�E���^�[���X�V����

		if (m_nShootDelay % 20 == 1)
		{//20�t���[�����ƒe������

			D3DXVECTOR3 pos = GetPos();			//�ʒu�̎擾

			//�e�̑��x�̌v�Z
			D3DXVECTOR3 move, newMove;
			float fAdd = 100.0f;
			move = CPlayer::GetPlayer()->GetPos() - pos;
			D3DXVec3Normalize(&move, &move);
			D3DXVECTOR3 unit = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
			float fAngle = acosf(D3DXVec3Dot(&move, &unit));

			if (CPlayer::GetPlayer()->GetPos().y < pos.y)
			{
				fAngle *= -1.0f;
			}

			if (pos.x > (float)SCREEN_WIDTH * 0.5f)
			{
				fAdd *= -1.0f;
			}

			//�e�T��������
			newMove = D3DXVECTOR3(cosf(fAngle) * cosf(D3DX_PI / 18.0f) - sinf(fAngle) * sinf(D3DX_PI / 18.0f),
				sinf(fAngle) * cosf(D3DX_PI / 18.0f) + cosf(fAngle) * sinf(D3DX_PI / 18.0f), 0.0f);

			CHandBlade::Create(D3DXVECTOR3(pos.x + fAdd, pos.y - 20.0f, 0.0f), D3DXVECTOR3(5.0f * newMove.x, 5.0f * newMove.y, 0.0f));

			newMove = D3DXVECTOR3(cosf(fAngle) * cosf(-D3DX_PI / 18.0f) - sinf(fAngle) * sinf(-D3DX_PI / 18.0f),
				sinf(fAngle) * cosf(-D3DX_PI / 18.0f) + cosf(fAngle) * sinf(-D3DX_PI / 18.0f), 0.0f);

			CHandBlade::Create(D3DXVECTOR3(pos.x + fAdd, pos.y - 20.0f, 0.0f), D3DXVECTOR3(5.0f * newMove.x, 5.0f * newMove.y, 0.0f));

			newMove = D3DXVECTOR3(cosf(fAngle) * cosf(D3DX_PI / 12.0f) - sinf(fAngle) * sinf(D3DX_PI / 12.0f),
				sinf(fAngle) * cosf(D3DX_PI / 12.0f) + cosf(fAngle) * sinf(D3DX_PI / 12.0f), 0.0f);

			CHandBlade::Create(D3DXVECTOR3(pos.x + fAdd, pos.y - 20.0f, 0.0f), D3DXVECTOR3(5.0f * newMove.x, 5.0f * newMove.y, 0.0f));

			newMove = D3DXVECTOR3(cosf(fAngle) * cosf(-D3DX_PI / 12.0f) - sinf(fAngle) * sinf(-D3DX_PI / 12.0f),
				sinf(fAngle) * cosf(-D3DX_PI / 12.0f) + cosf(fAngle) * sinf(-D3DX_PI / 12.0f), 0.0f);

			CHandBlade::Create(D3DXVECTOR3(pos.x + fAdd, pos.y - 20.0f, 0.0f), D3DXVECTOR3(5.0f * newMove.x, 5.0f * newMove.y, 0.0f));

			CHandBlade::Create(D3DXVECTOR3(pos.x + fAdd, pos.y - 20.0f, 0.0f), D3DXVECTOR3(5.0f * move.x, 5.0f * move.y, 0.0f));

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_SHOT);			//�U���T�E���h���Đ�����
		}

		if (m_nShootDelay >= 180)
		{//3�b���o������A�߂��Ԃɂ���

			m_nShootDelay = 0;				//�U���J�E���^�[��0�ɖ߂�
			m_state = state_return;			//��Ԃ̍X�V
		}
	}

	break;

	case CHandGun::state_return:

	{//�߂���

		D3DXVECTOR3 pos = GetPos();				//�ʒu�̎擾

		//���݂̈ʒu�ɂ���Ĉړ��ʂ̐ݒ�
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

	case CHandGun::state_despawn:

	{//�f�B�X�|�[�����

		D3DXVECTOR3 pos = GetPos();				//�ʒu�̎擾
		D3DXVECTOR3 move = GetMove();			//���x�̎擾

		if (move.x >= 0.0f && pos.x >= 100.0f || move.x < 0.0f && pos.x <= (float)SCREEN_WIDTH - 100.0f)
		{//���܂����ʒu�𒴂�����A�j������
			Release();				//�j������
			return;
		}
	}

	break;

	case CHandGun::state_death:

	{//���S���

		m_nPhase++;					//�J�E���^�[���X�V����

		if (m_nPhase % 15 == 0)
		{//15�t���[�����ƐF��ς���

			D3DXCOLOR col = GetColor();				//�F�̎擾

			if (col.g < 0.5f)
			{//�Ԃ���������A���ʂ̐F�ɖ߂�
				SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else
			{//���ʂ̐F��������A�Ԃ����܂�
				SetColor(D3DXCOLOR(1.0f, 0.3f, 0.3f, 1.0f));
			}
		}

	}

	break;

	default:
		break;
	}
}