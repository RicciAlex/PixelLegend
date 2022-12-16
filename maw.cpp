//=============================================================================
//
// maw.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "maw.h"
#include "squareHitbox.h"
#include "player.h"
#include "bone.h"
#include "skeleton.h"

#include "inputKeyboard.h"

//�R���X�g���N�^
CMaw::CMaw()
{
	//�����o�[�ϐ����N���A����
	m_state = state_normal;

	m_pHitbox = nullptr;
}

//�f�X�g���N�^
CMaw::~CMaw()
{

}

//����������
HRESULT CMaw::Init(void)
{
	if (FAILED(CEnemy::Init()))
	{//��{�N���X�̏���������
		return -1;
	}

	//�����o�[�ϐ�������������
	m_state = state_normal;

	m_pHitbox = nullptr;

	return S_OK;
}

//�I������
void CMaw::Uninit(void)
{
	//�q�b�g�{�b�N�X�̔j������
	if (m_pHitbox != nullptr)
	{//null�`�F�b�N
		m_pHitbox->Release();			//���������������
		m_pHitbox = nullptr;			//�|�C���^��null�ɂ���
	}

	//��{�N���X�̏I������
	CEnemy::Uninit();
}

//�X�V����
void CMaw::Update(void)
{
	//��{�N���X�̍X�V����
	CObject_2D::Update();

	//�q�b�g�{�b�N�X�̍X�V����
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Hit();	//�Փ˂𔻒肷��(���G�ȓG�Ȃ̂ŁA�_���[�W���󂯂Ȃ�)
	}

	UpdateState();			//��Ԃɂ���Ă̍X�V����
}

//�`�揈��
void CMaw::Draw(void)
{
	//��{�N���X�̕`�揈��
	CObject_2D::Draw();
}

//�J������
void CMaw::Open(void)
{
	m_state = state_open;		//�J����Ԃɂ���

	m_nPhase = 0;				//�J�E���^�[��0�ɖ߂�
	m_nShootDelay = 0;			//�U���J�E���^�[��0�ɖ߂�
}



//=============================================================================
//
//								�ÓI�֐�
//
//=============================================================================



//��������
CMaw* CMaw::Create(Position Pos)
{
	CMaw* pEnemy = new CMaw;			//�C���X�^���X�𐶐�����

	if (FAILED(pEnemy->Init()))
	{//����������
		return nullptr;
	}

	pEnemy->SetSize(D3DXVECTOR2(150.0f, 20.0f));			//�T�C�Y�̐ݒ�
	pEnemy->SetTexture(CObject::TextureGluttonyMaw);		//�e�N�X�`���̐ݒ�
	pEnemy->SetTextureParameter(1, 1, 5, INT_MAX);			//�e�N�X�`���p�����[�^�̐ݒ�
															
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		
	float fStartingAngle = 0.0f;							
	D3DXVECTOR2 size = D3DXVECTOR2(0.0f, 0.0f);				

	//=======================================================================================================================
	//�ʒu�ɂ���Ĉʒu�A�����ƃT�C�Y�̐ݒ�
	switch (Pos)
	{
	case CMaw::left:

	{
		pos = D3DXVECTOR3(85.0f, (float)SCREEN_HEIGHT * 0.5f, 0.0f);
		fStartingAngle = -D3DX_PI * 0.5f;
		size = D3DXVECTOR2(15.0f, 90.0f);
	}

		break;

	case CMaw::up:

	{
		pos = D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, 85.0f, 0.0f);
		fStartingAngle = D3DX_PI;
		size = D3DXVECTOR2(90.0f, 15.0f);
	}

		break;

	case CMaw::right:

	{
		pos = D3DXVECTOR3((float)SCREEN_WIDTH - 85.0f, (float)SCREEN_HEIGHT * 0.5f, 0.0f);
		fStartingAngle = D3DX_PI * 0.5f;
		size = D3DXVECTOR2(15.0f, 90.0f);
	}

		break;

	case CMaw::down:

	{
		pos = D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT - 85.0f, 0.0f);
		fStartingAngle = 0.0f;
		size = D3DXVECTOR2(90.0f, 15.0f);
	}

		break;

	default:
		break;
	}
	//=======================================================================================================================

	pEnemy->SetPos(pos);															//�ʒu�̐ݒ�
	pEnemy->SetStartingRot(D3DX_PI * 0.5f + fStartingAngle);						//�����̏����l�̐ݒ�
	pEnemy->m_pHitbox = CSquareHitbox::Create(pos, size, CHitbox::Type_Enemy);		//�q�b�g�{�b�N�X�̐���

	return pEnemy;				//���������C���X�^���X��Ԃ�
}



//=============================================================================
//
//							�v���C�x�[�g�֐�
//
//=============================================================================



//��Ԃɂ���Ă̍X�V����
void CMaw::UpdateState(void)
{
	switch (m_state)
	{
	case CMaw::state_normal:

	{//���ʂ̏��

	}

		break;

	case CMaw::state_open:

	{//�J�����

		m_nPhase++;			//�J�E���^�[���C���N�������g����

		if (m_nPhase % 8 == 7)
		{//8�t���[�����ƃA�j���[�V�����p�^�[�����X�V����

			int anim = GetPresentAnimPattern();

			if (anim >= 4)
			{//�A�j���[�V�������I�������A�����_���Ŏ��̍U����ݒ肷��

				switch (int a = random(0, 3))
				{
				case 0:

					m_state = state_SingleShoot;			//�U��(�P��)

					break;

				case 1:

					m_state = state_TripleShoot;			//�U��(�R��)

					break;

				case 2:

					m_state = state_RandomShoot;			//�����_���ȍU��

					break;

				case 3:

					m_state = state_Spawn;					//����

				default:
					break;
				}
				
				m_nPhase = 0;								//�J�E���^�[��0�ɖ߂�
			}
			else
			{
				anim++;						//�A�j���[�V�����J�E���^�[���C���N�������g����
				SetAnimPattern(anim);		//�A�j���[�V�����p�^�[����ݒ肷��
			}
		}
	}

		break;

	case CMaw::state_SingleShoot:

	{//�U��(�P��)

		m_nShootDelay++;				//�U���J�E���^�[���C���N�������g����

		if (m_nShootDelay % 50 == 5)
		{//50�t���[�����ƂP�̒e�𐶐�����

			D3DXVECTOR3 pos, PlayerPos, target;

			//�v���C���[�܂ł̃x�N�g�����v�Z���āA���K�����āA�e�̑��x�Ƃ��Ďg��
			pos = GetPos();
			PlayerPos = CPlayer::GetPlayer()->GetPos();
			target = PlayerPos - pos;
			D3DXVec3Normalize(&target, &target);
			target.x *= 3.0f;
			target.y *= 3.0f;

			CBone::Create(pos, target);				//�e�̐���
		}

		if (m_nShootDelay >= 410)
		{//410�t���[�����o������
			m_nShootDelay = 0;			//�U���J�E���^�[��0�ɖ߂�
			m_state = state_close;		//�����Ԃɂ���
		}
	}

		break;

	case CMaw::state_TripleShoot:

	{//�U��(�R��)

		m_nShootDelay++;				//�U���J�E���^�[���C���N�������g����

		if (m_nShootDelay % 100 == 5)
		{//50�t���[�����ƂP�̒e�𐶐�����
			D3DXVECTOR3 pos, PlayerPos, target;

			//�v���C���[�܂ł̃x�N�g�����v�Z���āA���K�����āA�e�̑��x�Ƃ��Ďg���B����Ɂ}30�������̒e�𐶐�����
			pos = GetPos();
			PlayerPos = CPlayer::GetPlayer()->GetPos();
			target = PlayerPos - pos;
			D3DXVec3Normalize(&target, &target);

			D3DXVECTOR3 unit = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

			float fAngle = acosf(D3DXVec3Dot(&target, &unit));

			if (PlayerPos.y < pos.y)
			{
				fAngle *= -1.0f;
			}

			//�e�̐���
			CBone::Create(pos, D3DXVECTOR3(3.0f * target.x, 3.0f * target.y, 0.0f));

			D3DXVECTOR3 NewMove = D3DXVECTOR3(cosf(fAngle) * cosf(D3DX_PI / 6.0f) - sinf(fAngle) * sinf(D3DX_PI / 6.0f),
				sinf(fAngle) * cosf(D3DX_PI / 6.0f) + cosf(fAngle) * sinf(D3DX_PI / 6.0f), 0.0f);

			CBone::Create(pos, D3DXVECTOR3(3.0f * NewMove.x, 3.0f * NewMove.y, 0.0f));

			NewMove = D3DXVECTOR3(cosf(fAngle) * cosf(-D3DX_PI / 6.0f) - sinf(fAngle) * sinf(-D3DX_PI / 6.0f),
				sinf(fAngle) * cosf(-D3DX_PI / 6.0f) + cosf(fAngle) * sinf(-D3DX_PI / 6.0f), 0.0f);

			CBone::Create(pos, D3DXVECTOR3(3.0f * NewMove.x, 3.0f * NewMove.y, 0.0f));
		}

		if (m_nShootDelay >= 710)
		{//710�t���[�����o������
			m_nShootDelay = 0;			//�U���J�E���^�[��0�ɖ߂�
			m_state = state_close;		//�����Ԃɂ���
		}
	}

	break;

	case CMaw::state_RandomShoot:

	{//�����_���ȍU��

		m_nShootDelay++;				//�U���J�E���^�[���C���N�������g����

		if (m_nShootDelay % 30 == 5)
		{//30�t���[�����ƒe�𐶐�����

			D3DXVECTOR3 pos, PlayerPos, target;

			//�v���C���[�܂ł̃x�N�g�����v�Z���āA���K�����āA�}45�������̒e�𐶐�����
			//�v���C���[�������Ȃ��Ɠ�����Ȃ��\���������B�ł��ǂƓ���������A�܂�Ă��甽�˂���
			pos = GetPos();
			PlayerPos = CPlayer::GetPlayer()->GetPos();
			target = PlayerPos - pos;
			D3DXVec3Normalize(&target, &target);

			D3DXVECTOR3 unit = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

			float fAngle = acosf(D3DXVec3Dot(&target, &unit));

			if (PlayerPos.y < pos.y)
			{
				fAngle *= -1.0f;
			}
			
			float fDiv = random(3000, 8000) * 0.001f;

			//�e�̐���
			D3DXVECTOR3 NewMove = D3DXVECTOR3(cosf(fAngle) * cosf(D3DX_PI / fDiv) - sinf(fAngle) * sinf(D3DX_PI / fDiv),
				sinf(fAngle) * cosf(D3DX_PI / fDiv) + cosf(fAngle) * sinf(D3DX_PI / fDiv), 0.0f);

			CBone::Create(pos, D3DXVECTOR3(4.0f * NewMove.x, 4.0f * NewMove.y, 0.0f));

			NewMove = D3DXVECTOR3(cosf(fAngle) * cosf(-D3DX_PI / fDiv) - sinf(fAngle) * sinf(-D3DX_PI / fDiv),
				sinf(fAngle) * cosf(-D3DX_PI / fDiv) + cosf(fAngle) * sinf(-D3DX_PI / fDiv), 0.0f);

			CBone::Create(pos, D3DXVECTOR3(4.0f * NewMove.x, 4.0f * NewMove.y, 0.0f));
		}

		if (m_nShootDelay >= 410)
		{//410�t���[�����o������
			m_nShootDelay = 0;			//�U���J�E���^�[��0�ɖ߂�
			m_state = state_close;		//�����Ԃɂ���
		}
	}

	break;

	case CMaw::state_Spawn:

	{//����

		m_nShootDelay++;					//�U���J�E���^�[���C���N�������g����

		if (m_nShootDelay % 35 == 5)
		{//35�t���[�����ƓG��C��������
			CSkeleton::Create(GetPos());
		}

		if (m_nShootDelay >= 350)
		{//350�t���[�����o������
			m_nShootDelay = 0;			//�U���J�E���^�[��0�ɖ߂�
			m_state = state_close;		//�����Ԃɂ���
		}
	}

	break;

	case CMaw::state_close:

	{//������

		m_nPhase++;				//�J�E���^�[���C���N�������g����

		if (m_nPhase % 8 == 7)
		{//8�t���[�����ƃe�N�X�`���p�^�[�����X�V����

			int anim = GetPresentAnimPattern();

			if (anim == 0)
			{//���S�ɕ�����A���ʂ̏�Ԃɖ߂�
				m_state = state_normal;
				m_nPhase = 0;
			}
			else
			{
				anim--;						//�A�j���[�V�����p�^�[���̍X�V
				SetAnimPattern(anim);		//�A�j���[�V�����p�^�[���̐ݒ�
			}
		}
	}

		break;

	default:
		break;
	}
}