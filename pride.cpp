//=============================================================================
//
// pride.cpp
// Author : Ricci Alex
//
//=============================================================================

//�C���N���[�h�t�@�C��
#include "pride.h"
#include "circleHitbox.h"
#include "balloon.h"
#include "player.h"
#include "laugh.h"
#include "balloonEnemy.h"
#include "starBullet.h"
#include "bouncingBullet.h"
#include "enemyLife.h"
#include "application.h"
#include "sound.h"

//�R���X�g���N�^
CPride::CPride()
{
	//�����o�[�ϐ����N���A����
	m_state = state_Spawn;
	m_nSpawnFrame = 0;
	m_bEnd = false;

	m_pHitbox = nullptr;
	m_pLife = nullptr;
}

//�f�X�g���N�^
CPride::~CPride()
{

}

//����������
HRESULT CPride::Init(void)
{
	if (FAILED(CEnemy::Init()))
	{//��{�N���X�̏���������
		return -1;
	}

	//�����o�[�ϐ�������������
	m_state = state_Spawn;
	m_nSpawnFrame = 0;
	m_bEnd = false;

	SetTexture(CObject::TexturePride);
	SetTextureParameter(1, 3, 2, INT_MAX);

	m_pLife = nullptr;

	return S_OK;
}

//�I������
void CPride::Uninit(void)
{
	//�q�b�g�{�b�N�X�̔j������
	if (m_pHitbox != nullptr)
	{//null�`�F�b�N
		m_pHitbox->Release();			//���������������
		m_pHitbox = nullptr;			//�|�C���^��null�ɂ���
	}

	//�̗�UI�̔j������
	if (m_pLife != nullptr)
	{//null�`�F�b�N
		m_pLife->Release();				//���������������
		m_pLife = nullptr;				//�|�C���^��null�ɂ���
	}

	//��{�N���X�̏I������
	CEnemy::Uninit();
}

//�X�V����
void CPride::Update(void)
{
	//��{�N���X�̍X�V����
	CObject_2D::Update();

	//�q�b�g�{�b�N�X�̍X�V����
	if (m_pHitbox != nullptr)
	{//null�`�F�b�N

		m_pHitbox->SetPos(GetPos());		//�ʒu�̍X�V

		if (m_pHitbox->GetHitState())
		{//����������Ԃ�������

			m_pHitbox->SetHitState(false);	//�����Ă��Ȃ���Ԃɖ߂�

			int nLife = GetLife();								//�̗͂̎擾
			int nDamage = CPlayer::GetPlayer()->GetAttack();	//�v���C���[�̍U���͂̎擾
			nLife -= nDamage;									//�̗͂̍X�V

			if (nLife <= 0)
			{//�̗͂�0�ȉ��ɂȂ�����

				m_state = state_Death;							//���S��Ԃɂ���
				SetAnimPattern(4);								//�A�j���V�����p�^�[���̍X�V
				m_nCntMove = 0;									//�ړ��J�E���^�[��0�ɖ߂�
				m_nPhase = 0;									//�J�E���^�[��0�ɖ߂�
				m_fAngleMove = 0;								//�ړ��p�x��0�ɖ߂�
				SetMove(D3DXVECTOR3(0.0f, 3.0f, 0.0f));			//���x�̐ݒ�
				m_pHitbox->Release();							//�q�b�g�{�b�N�X�̔j��
				m_pHitbox = nullptr;							//�|�C���^��null�ɂ���
				SetLife(0);										//�̗͂�0�ɐݒ肷��
			}
			else
			{//�̗͂�0�ȉ��ł͂Ȃ�������

				SetLife(nLife);				//�̗͂̐ݒ�

				//�̗͂�UI�̍X�V
				if (m_pLife != nullptr)
				{//null�`�F�b�N

					m_pLife->SubtractLife(nDamage);			//UI�̍X�V
				}
			}
		}
	}

	UpdateState();					//��Ԃɂ���Ă̍X�V����
}

//�`�揈��
void CPride::Draw(void)
{
	//��{�N���X�̕`�揈��
	CEnemy::Draw();
}

//�I��������ǂ����̎擾����
const bool CPride::GetEnd(void)
{
	return m_bEnd;
}



//=============================================================================
//
//								�ÓI�֐�
//
//=============================================================================



//��������
CPride* CPride::Create(void)
{
	CPride* pEnemy = new CPride;				//�C���X�^���X�̐���

	if (FAILED(pEnemy->Init()))
	{//����������
		return nullptr;
	}

	pEnemy->SetPos(D3DXVECTOR3(1000.0f, -180.0f, 0.0f));		//�ʒu�̐ݒ�
	pEnemy->SetMove(D3DXVECTOR3(0.0f, 1.5f, 0.0f));				//���x�̐ݒ�
	pEnemy->SetSize(D3DXVECTOR2(140.0f, 140.0f));				//�T�C�Y�̐ݒ�
	pEnemy->SetStartingRot(D3DX_PI * 0.5f);						//�����̏����l�̐ݒ�
	pEnemy->SetLife(25000);										//�̗͂̐ݒ�

	//�q�b�g�{�b�N�X�̐���
	pEnemy->m_pHitbox = CCircleHitbox::Create(D3DXVECTOR3(500.0f, 300.0f, 0.0f), 125.0f, CHitbox::Type_Enemy);

	//�̗͂�UI�̐���
	pEnemy->m_pLife = CEnemyLife::Create(D3DXVECTOR3(900.0f, 40.0f, 0.0f), D3DXCOLOR(1.0f, 0.0f, 0.75f, 0.4f), 25000, "pride");

	return pEnemy;							//���������C���X�^���X��Ԃ�
}





//=============================================================================
//
//							�v���C�x�[�g�֐�
//
//=============================================================================




//��Ԃɂ���Ă̍X�V����
void CPride::UpdateState(void)
{
	switch (m_state)
	{

	case state_Spawn:

	{//�X�|�[�����

		D3DXVECTOR3 pos = GetPos();				//�ʒu�̎擾

		if (pos.y >= 180.0f)
		{//���܂����ʒu�ɒ�������

			SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));							//���x�̐ݒ�
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_LAUGH);	//�΂��T�E���h���Đ�����
			m_state = state_LaughAnim;										//�΂���Ԃɐ؂�ւ���
			SetAnimPattern(1);												//�e�N�X�`���p�����[�^�̐ݒ�
		}
	}

	break;

	case state_Normal:

	{//���ʂ̏��

		m_state = state_BouncingBall;
	}

	break;

	case state_Hide:

	{//�B�����

		D3DXVECTOR3 pos = GetPos();							//�ʒu�̎擾
		D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//���x

		//�����̈ʒu�ɂ���đ��x��ݒ肷��
		if (pos.x >= (float)SCREEN_WIDTH * 0.5f)
		{//��ʂ̉E���ɂ�����

			move.x += 5.0f;			//�E�����������悤�ɐݒ肷��
		}
		else
		{//��ʂ̍����ɂ�����
			move.x += -5.0f;		//�������������悤�ɐݒ肷��
		}
		if (pos.y >= (float)SCREEN_HEIGHT * 0.5f)
		{//��ʂ̏㑤�ɂ�����
			move.y += 5.0f;			//�㑤���������悤�ɐݒ肷��
		}
		else
		{//��ʂ̉����ɂ�����
			move.y += -5.0f;		//�������������悤�ɐݒ肷��
		}

		if (pos.x >= (float)SCREEN_WIDTH + 200.0f || pos.x <= -200.0f || pos.y >= (float)SCREEN_HEIGHT + 200.0f || pos.y <= -200.0f)
		{//��ʂ��o����

			//���x��ݒ肷��
			move.x = 0.0f;
			move.y = 3.0f;
			m_state = state_Spawn;							//��Ԃ̍X�V
			SetPos(D3DXVECTOR3(1000.0f, -180.0f, 0.0f));	//�ʒu��ݒ肷��
		}

		SetMove(move);				//���x�̐ݒ�

	}

	break;

	case state_BouncingBall:

	{//�ʒe

		m_nShootDelay++;				//�U���J�E���^�[���C���N�������g����

		//�A�j���[�V��������
		if (m_nShootDelay == 10)
		{
			SetAnimPattern(3);
		}
		else if (m_nShootDelay == 55)
		{
			SetAnimPattern(4);
		}

		//�e�𔭐�����
		if (m_nShootDelay >= 60)
		{//60�t���[�����ƒe�𔭐�����

			m_nShootDelay = 0;				//�U���J�E���^�[��0�ɖ߂�

			for (int nCnt = 0; nCnt < 3; nCnt++)
			{//�e�𔭐�����(�R��)

				//�����_���ȕ����ɒe�𔭐�����
				D3DXVECTOR3 PlayerPos = CPlayer::GetPlayer()->GetPos();
				D3DXVECTOR3 Target = PlayerPos - D3DXVECTOR3(GetPos().x, GetPos().y + 90.0f, 0.0f);
				D3DXVec3Normalize(&Target, &Target);
				D3DXVECTOR3 V = D3DXVECTOR3((float)random(-5000, 5000), (float)random(-5000, 5000), 0.0f);
				D3DXVec3Normalize(&V, &V);
				Target += V;
				D3DXVec3Normalize(&Target, &Target);
				Target.x *= 6.0f;
				Target.y *= 6.0f;

				//�e�̐���
				CBouncingBullet* pBullet = CBouncingBullet::Create(D3DXVECTOR3(GetPos().x, GetPos().y + 90.0f, 0.0f), Target);
			}

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_SHOT);			//�e�̔����̃T�E���h���Đ�����

			m_nPhase++;				//�U�����̃J�E���^�[���C���N�������g����
		}

		if (m_nPhase >= 10)
		{//10��U��������

			m_nShootDelay = 0;			//�U���J�E���^�[��0�ɖ߂�
			m_nPhase = 0;				//�U�����̃J�E���^�[��0�ɖ߂�
			SetAnimPattern(0);			//�e�N�X�`���p�����[�^��0�ɖ߂�
			m_state = state_Hide;		//�B����Ԃɖ߂�
		}
	}

	break;

	case state_Star:

	{//���U���̏��

		m_nCntMove++;			//�ړ��J�E���^�[�̍X�V

		if (m_nCntMove >= m_nSpawnFrame)
		{//�ړ��J�E���^�[���X�|�[���t���[���ȏ�ɂȂ�����

			m_nSpawnFrame = random(40, 150);			//���̃X�|�[���t���[����ݒ肷��

			//���^�̒e�̐���
			CStarBullet* pBullet = CStarBullet::Create(GetPos(), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_STAR_BULLET);			//�T�E���h���Đ�����

			m_nCntMove = 0;				//�ړ��J�E���^�[��0�ɖ߂�
		}

		if (GetPos().x < -201.0f || GetPos().x > 1481.0f)
		{//��ʂ��o����

			D3DXVECTOR3 move = GetMove();			//���x�̎擾
			move.x *= -1.0f;						//X���W���t�ɂ���
			SetMove(move);							//���x�̐ݒ�
			D3DXVECTOR3 pos = D3DXVECTOR3(GetPos().x, CPlayer::GetPlayer()->GetPos().y, 0.0f);			//�ʒu��Y���W���v���C���[�̓��������ɐݒ肷��
			SetPos(pos);							//�ʒu�̐ݒ�
			m_nPhase++;								//�J�E���^�[���C���N�������g����

			if (m_nPhase >= 5)
			{//5�񂱂̍U����������A

				m_nPhase = 0;			//�J�E���^�[��0�ɖ߂�
				m_state = state_Hide;	//�B����Ԃɂ���
			}
		}
	}

	break;

	case state_CreateEnemy:

	{//�����U��

		m_nCntMove++;				//�ړ��J�E���^�[���C���N�������g����

		if (m_nCntMove % 80 == 79)
		{//�e�N�X�`���p�����[�^�̐ݒ�
			SetAnimPattern(4);
		}

		if (m_nCntMove >= 100)
		{//100�t���[���𒴂�����A�G�𐶐�����

			//�G�̐���
			CBalloonEnemy* pEnemy = CBalloonEnemy::Create(D3DXVECTOR3(GetPos().x, GetPos().y + 90.0f, 0.0f));

			SetAnimPattern(0);			//�e�N�X�`���p�����[�^�̐ݒ�

			m_nCntMove = 0;				//�ړ��J�E���^�[��0�ɖ߂�

			m_nPhase++;					//�U�����̃J�E���^�[���C���N�������g����

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_BALLOON_POP);			//�T�E���h���Đ�����

			if (m_nPhase >= 7)
			{//7�񂱂̍U����������

				m_nPhase = 0;				//�U�����̃J�E���^�[��0�ɖ߂�
				m_state = state_Hide;		//�B����Ԃɖ߂�
			}
		}
	}

	break;

	case state_LaughAttack:

	{//�΂��U��

		m_nCntMove++;			//�ړ��J�E���^�[���C���N�������g����

		if (m_nCntMove % 20 == 19)
		{//20�t���[�����ƃA�j���V�����p�^�[�����X�V����
			if (GetPresentAnimPattern() == 1)
			{
				SetAnimPattern(2);
			}
			else if (GetPresentAnimPattern() == 2)
			{
				SetAnimPattern(1);
			}
		}

		if (m_nCntMove >= 40)
		{//40�t���[�����ƒe�𔭐�����

			m_nCntMove = 0;			//�ړ��J�E���^�[��0�ɖ߂�

			//���̓G����v���C���[�܂ł̃x�N�g�����v�Z���āA���K��������A�e�̑��x�̂Ƃ��Ďg��
			D3DXVECTOR3 PlayerPos = CPlayer::GetPlayer()->GetPos();	
			D3DXVECTOR3 Target = PlayerPos - D3DXVECTOR3(GetPos().x, GetPos().y + 90.0f, 0.0f);
			D3DXVec3Normalize(&Target, &Target);
			Target.x *= 5.0f;
			Target.y *= 5.0f;

			//�e�̐���
			CLaughBullet* pBullet = CLaughBullet::Create(D3DXVECTOR3(GetPos().x, GetPos().y + 90.0f, 0.0f), Target);

			m_nPhase++;			//�U�����̃J�E���^�[���C���N�������g����

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_LAUGH);			//�T�E���h���Đ�����

			if (m_nPhase >= 15)
			{//15�񂱂̍U����������

				m_nPhase = 0;				//�U�����̃J�E���^�[��0�ɖ߂�
				SetAnimPattern(0);			//�e�N�X�`���p�����[�^�̐ݒ�
				m_state = state_Hide;		//�B����Ԃɖ߂�
			}
		}
	}

	break;

	case state_Balloon:

	{
		D3DXVECTOR3 pos = GetPos();			//�ʒu�̎擾

		if (pos.y <= -150.0f)
		{//��ʂ��o����

			SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));			//���x�̐ݒ�

			m_nCntMove++;				//�ړ��J�E���^�[���C���N�������g����

			if (m_nCntMove >= 20)
			{//20�t���[�����ƒe�𔭐�����

				m_nCntMove = 0;			//�ړ��J�E���^�[��0�ɖ߂�

				D3DXVECTOR3 PlayerPos = CPlayer::GetPlayer()->GetPos();		//�v���C���[�̈ʒu�̎擾
					
				//��������e�̐��̐ݒ�
				////�v���C���[�͉�ʂ̏㑤�ɂ�����
				int nMax = 1;

				if (PlayerPos.y >= (float)SCREEN_HEIGHT * 0.34f && PlayerPos.y < (float)SCREEN_HEIGHT * 0.67f)
				{//�v���C���[�͉�ʂ̐^�񒆂ɂ�����
					nMax = 2;
				}
				else if (PlayerPos.y >= (float)SCREEN_HEIGHT * 0.67f)
				{//�v���C���[�͉�ʂ̉����ɂ�����
					nMax = 3;
				}

				for (int nCnt = 0; nCnt < nMax; nCnt++)
				{
					//�����_���ȑ��x�̐ݒ�
					D3DXVECTOR3 move = D3DXVECTOR3(random(-100, 100) * 0.05f, random(50, 100) * 0.05f, 0.0f);
					int nColor = random(0, 5);
					D3DXCOLOR col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

					//�F�̐ݒ�(�ԁA�΁A�A���A�}�[���^�A�V�A��)
					switch (nColor)
					{
					case 0:
						col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
						break;
					case 1:
						col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
						break;
					case 2:
						col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
						break;
					case 3:
						col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
						break;
					case 4:
						col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
						break;
					case 5:
						col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
						break;
					default:
						break;
					}

					//�e�̐���
					CBalloonBullet* pBullet = CBalloonBullet::Create(D3DXVECTOR3(PlayerPos.x, -15.0f, 0.0f), move, col);
				}

				m_nPhase++;				//�U�����̃J�E���^�[���C���N�������g����

				if (m_nPhase >= 15)
				{//15�񂱂̍U����������

					m_nPhase = 0;				//�U���J�E���^�[��0�ɖ߂�
					m_state = state_Hide;		//�B����Ԃɖ߂�
				}
			}
		}
	}

	break;

	case state_LaughAnim:

	{//�΂��A�j���[�V����

		m_nCntMove++;			//�ړ��J�E���^�[���C���N�������g����

		if (m_nCntMove % 8 == 0)
		{//8�t���[�����ƃe�N�X�`���p�^�[�����X�V����

			if (GetPresentAnimPattern() == 1)
			{
				SetAnimPattern(2);
			}
			else if (GetPresentAnimPattern() == 2)
			{
				SetAnimPattern(1);
			}
		}

		if (m_nCntMove >= 91)
		{//90�t���[�����o������

			SetAnimPattern(0);			//�A�j���V�����p�^�[����0�ɖ߂�
			m_nCntMove = 0;				//�ړ��J�E���^�[��0�ɖ߂�

			int nSelect = random(3, 7);	//�����_���Ŏ��̍U����ݒ肷��

			switch (nSelect)
			{
			case state_BouncingBall:

				//�e�^�̍U��
				SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				m_state = state_BouncingBall;

				break;

			case state_Star:

				//���^�̍U��
				SetMove(D3DXVECTOR3(-8.0f, 0.0f, 0.0f));
				m_state = state_Star;

				break;

			case state_LaughAttack:

				//�΂��U��
				SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				SetAnimPattern(1);
				m_state = state_LaughAttack;

				break;

			case state_CreateEnemy:

				//�G�̏���
				SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				m_state = state_CreateEnemy;

				break;

			case state_Balloon:

				//���D�U��
				SetMove(D3DXVECTOR3(0.0f, -2.0f, 0.0f));
				m_state = state_Balloon;

				break;
			}
		}
	}

	break;

	case state_Death:

	{//���S���

		if (m_nPhase == 0)
		{//���������������Ȃ���A��ʂ̉����Ɉړ�������

			m_nCntMove++;			//�ړ��J�E���^�[���C���N�������g����

			if (m_nCntMove % 30 < 20)
			{
				//�T�C�Y������������
				D3DXVECTOR2 size = GetSize();
				size.x -= 0.5f;
				size.y -= 0.5f;
				SetSize(size);
			}
			if (m_nCntMove >= 92)
			{
				//��]�����āA�㑤�����̉�����ݒ肷��
				m_nPhase++;
				m_nCntMove = 0;
				SetAcceleration(D3DXVECTOR3(0.0f, -0.5f, 0.0f));
				SetRotation(D3DX_PI * 0.2f);
			}
		}
		else
		{
			D3DXVECTOR3 pos = GetPos();				//�ʒu�̎擾
			pos.x += 3.0f * sinf(m_fAngleMove);		//���E�ړ���ǉ�����
			SetPos(pos);							//�ʒu��ݒ肷��
			m_fAngleMove += D3DX_PI * 0.05f;		//���E�ړ��p�̊p�x���X�V����

			if (pos.y <= -200.0f)
			{//��ʂ��o����A�I��������Ƃɂ���

				m_bEnd = true;
			}
		}
	}

	break;

	default:

		break;
	}
}
