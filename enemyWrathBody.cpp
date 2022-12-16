//=============================================================================
//
// enemyWrathBody.cpp
// Author : Ricci Alex
//
//=============================================================================

//�C���N���[�h�t�@�C��
#include "enemyWrathBody.h"
#include "circleHitbox.h"
#include "squareHitbox.h"
#include "application.h"
#include "sound.h"
#include "skullFireball.h"
#include "player.h"
#include "wrath.h"


//�R���X�g���N�^
CWrathBody::CWrathBody()
{
	//�����o�[�ϐ����N���A����
	m_nCntShoot = 0;
	m_nCntState = 0;
	m_state = state_spawn;

	m_pHitbox = nullptr;
	m_pHeadHitbox = nullptr;
	m_bDead = false;
	m_bBound = false;
	m_pArm = nullptr;
	m_pParent = nullptr;

	m_posArm =D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posBodyHitbox = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posHeadHitbox = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_targetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//�f�X�g���N�^
CWrathBody::~CWrathBody()
{

}

//����������
HRESULT CWrathBody::Init(void)
{
	//�����o�[�ϐ�������������

	//��{�N���X�̏���������
	if (FAILED(CEnemy::Init()))
	{
		return -1;
	}

	m_nCntShoot = 0;
	m_nCntState = 0;
	m_state = state_spawn;

	m_pHitbox = nullptr;
	m_pHeadHitbox = nullptr;
	m_bDead = false;
	m_bBound = true;
	m_pArm = nullptr;
	m_pParent = nullptr;

	m_posArm = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posBodyHitbox = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posHeadHitbox = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_targetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return S_OK;
}

//�I������
void CWrathBody::Uninit(void)
{
	//�̂̃q�b�g�{�b�N�X�̔j������
	if (m_pHitbox != nullptr)
	{//null�`�F�b�N
		m_pHitbox->Release();			//���������������
		m_pHitbox = nullptr;			//null�ɂ���
	}
	//���̃q�b�g�{�b�N�X�̔j������
	if (m_pHeadHitbox != nullptr)
	{//null�`�F�b�N
		m_pHeadHitbox->Release();		//���������������
		m_pHeadHitbox = nullptr;		//null�ɂ���
	}
	//�r�̔j������
	if (m_pArm != nullptr)
	{//null�`�F�b�N
		m_pArm->Release();				//���������������
		m_pArm = nullptr;				//null�ɂ���
	}
	//�e�ւ̃|�C���^��null�ł͂Ȃ�������Anull�ɂ���
	if (m_pParent != nullptr)
	{//null�`�F�b�N
		m_pParent = nullptr;			//null�ɂ���
	}

	//��{�N���X�̏I������
	CEnemy::Uninit();
}
//�X�V����
void CWrathBody::Update(void)
{
	//��Ԃɂ���Ă̍X�V����
	UpdateState();

	//��{�N���X�̍X�V����
	CObject_2D::Update();

	D3DXVECTOR3 pos = GetPos();				//�ʒu�̎擾

	//�̂̃q�b�g�{�b�N�X�̍X�V
	if (m_pHitbox != nullptr)
	{//null�`�F�b�N

		m_pHitbox->SetPos(pos + m_posBodyHitbox);			//�̂̃q�b�g�{�b�N�X�̈ʒu�̐ݒ�

		if (m_pHitbox->GetHitState())
		{//����������Ԃ�������

			m_pHitbox->SetHitState(false);				//�����Ă��Ȃ���Ԃɖ߂�

			int nDamage = CPlayer::GetPlayer()->GetAttack();	//�v���C���[�̍U���͂̎擾

			int nLife = GetLife() - nDamage;			//�̗͂̍X�V

			//�e�ւ̃|�C���^��null�ł͂Ȃ�������A�_���[�W��^����
			if (m_pParent != nullptr)
			{//null�`�F�b�N
				m_pParent->Damage(nDamage);
			}

			if (nLife <= 0)
			{//�̗͂�0�ȉ��ɂȂ�����

				m_pHitbox->Release();			//�q�b�g�{�b�N�X��j������
				m_pHitbox = nullptr;			//�|�C���^��null�ɂ���

				if (m_pHeadHitbox != nullptr)
				{//���̃q�b�g�{�b�N�X��null�ł͂Ȃ�������A

					m_pHeadHitbox->Release();	//�q�b�g�{�b�N�X��j������
					m_pHeadHitbox = nullptr;	//�|�C���^��null�ɂ���
				}

				SetMove(D3DXVECTOR3(4.0f, -10.0f, 0.0f));			//���x�̐ݒ�
				SetAcceleration(D3DXVECTOR3(0.0f, 0.5f, 0.0f));		//�����̐ݒ�
				SetAnimPattern(4);									//�A�j���V�����p�^�[���̐ݒ�
				m_nPhase = 0;										//�J�E���^�[��0�ɖ߂�
				m_bBound = false;									//�e�Ɍ���ł��Ȃ���Ԃɂ���
				m_state = state_death;								//��Ԃ̍X�V
				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_WRATH_DEATH);			//�T�E���h���Đ�����

				return;
			}
			
			SetLife(nLife);				//�̗͂̍X�V
		}
	}

	//���̃q�b�g�{�b�N�X�̍X�V
	if (m_pHeadHitbox != nullptr)
	{//null�`�F�b�N

		m_pHeadHitbox->SetPos(pos + m_posHeadHitbox);			//���̃q�b�g�{�b�N�X�̈ʒu�̐ݒ�

		if (m_pHeadHitbox->GetHitState())
		{//����������Ԃ�������

			m_pHeadHitbox->SetHitState(false);					//�����Ă��Ȃ���Ԃɖ߂�

			int nDamage = CPlayer::GetPlayer()->GetAttack();	//�v���C���[�̍U���͂̎擾

			int nLife = GetLife() - nDamage;					//�̗͂̍X�V

			//�e�ւ̃|�C���^��null�ł͂Ȃ�������
			if (m_pParent != nullptr)
			{
				m_pParent->Damage(nDamage);		//�e�Ƀ_���[�W��^����
			}

			if (nLife <= 0)
			{//�̗͂�0�ȉ��ɂȂ�����
				m_pHeadHitbox->Release();			//�q�b�g�{�b�N�X��j������
				m_pHeadHitbox = nullptr;			//�|�C���^��null�ɂ���

				if (m_pHitbox != nullptr)
				{//�̂ւ̃|�C���^��null�ł͂Ȃ�������
					m_pHitbox->Release();			//�q�b�g�{�b�N�X��j������
					m_pHitbox = nullptr;			//�|�C���^��null�ɂ���
				}

				SetMove(D3DXVECTOR3(4.0f, -13.0f, 0.0f));				//���x�̐ݒ�
				SetAcceleration(D3DXVECTOR3(0.0f, 0.5f, 0.0f));			//�����̐ݒ�
				SetAnimPattern(4);										//�A�j���V�����p�^�[���̐ݒ�
				m_nPhase = 0;											//�J�E���^�[��0�ɖ߂�
				m_bBound = false;										//�e�Ɍ���ł��Ȃ���Ԃɂ���
				m_state = state_death;									//��Ԃ̍X�V
				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_WRATH_DEATH);			//�T�E���h���Đ�����

				return;
			}

			SetLife(nLife);				//�̗͂̐ݒ�
		}
	}
	//�r�̍X�V
	if (m_pArm != nullptr && m_bBound)
	{//�r�ւ̃|�C���^��null�ł͂Ȃ��āA�e�Ɍ���ł����Ԃ�������

		m_pArm->SetPos(pos + m_posArm);			//�ʒu�̐ݒ�
	}
}

//�`�揈��
void CWrathBody::Draw(void)
{
	//��{�N���X�̕`�揈��
	CEnemy::Draw();
}

//�e�ւ̃|�C���^�̐ݒ菈��
void CWrathBody::SetParent(CWrath* pParent)
{
	m_pParent = pParent;
}

//���S�������ǂ����̎擾����
const bool CWrathBody::GetDeath(void)
{
	return m_bDead;
}

//==========================================================================================================
//
//											�ÓI�֐�
//
//==========================================================================================================


//��������
CWrathBody* CWrathBody::Create(D3DXVECTOR3 pos)
{
	CWrathBody* pEnemy = new CWrathBody;			//�V�����G�𐶐�����

		//����������
	if (FAILED(pEnemy->Init()))
	{
		return nullptr;					//null��Ԃ�
	}

	pEnemy->SetPos(pos);										//�ʒu�̐ݒ�
	pEnemy->SetObjType(CObject::OBJTYPE_ENEMY);					//�I�u�W�F�N�g�̎�ނ̐ݒ�
	pEnemy->SetStartingRot(D3DX_PI * 0.5f);						//��]�p�x�̏����l�̐ݒ�
	pEnemy->m_nCntMove = 0;										//�J�E���^�̐ݒ�
	pEnemy->m_nShootDelay = 0;									//�J�E���^�̐ݒ�
	pEnemy->SetTextureParameter(1, 2, 3, INT_MAX);				//�e�N�X�`���p�����[�^�̐ݒ�
	pEnemy->SetSize(D3DXVECTOR2(120.0f, 241.0f));				//�T�C�Y�̐ݒ�

	pEnemy->SetMove(D3DXVECTOR3(-2.0f, 0.0f, 0.0f));			//���x�̐ݒ�
	pEnemy->SetAcceleration(D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//�����̐ݒ�
	pEnemy->SetSubtype(ENEMYTYPE_WRATH_BODY);					//�G�̎�ނ̐ݒ�
	pEnemy->SetLife(15000);										//�̗͂̐ݒ�

	pEnemy->SetTexture(TextureWrath);						//�e�N�X�`���̐ݒ�

	pEnemy->m_posBodyHitbox = D3DXVECTOR3(0.0f, 135.0f, 0.0f);	//�̂̃q�b�g�{�b�N�X�̈ʒu�̐ݒ�
	pEnemy->m_posHeadHitbox = D3DXVECTOR3(5.0f, -85.0f, 0.0f);	//���̃q�b�g�{�b�N�X�̈ʒu�̐ݒ�

	//�̂̃q�b�g�{�b�N�X�̐���
	pEnemy->m_pHitbox = CSquareHitbox::Create(pos + pEnemy->m_posBodyHitbox, D3DXVECTOR2(60.0f, 85.0f), CHitbox::Type_Enemy);

	//���̃q�b�g�{�b�N�X�̐���
	pEnemy->m_pHeadHitbox = CCircleHitbox::Create(pos + pEnemy->m_posHeadHitbox, 100.0f, CHitbox::Type_Enemy);

	pEnemy->m_posArm = D3DXVECTOR3(0.0f, 250.0f, 0.0f);			//�r�̈ʒu�̐ݒ�

	//�r�̐���
	pEnemy->m_pArm = CObject_2D::Create();						//�C���X�^���X�𐶐�����
	pEnemy->m_pArm->SetPos(pos + pEnemy->m_posArm);				//�ʒu�̐ݒ�
	pEnemy->m_pArm->SetSize(D3DXVECTOR2(126.0f, 193.5));		//�T�C�Y�̐ݒ�
	pEnemy->m_pArm->SetTexture(CObject::TextureHand);			//�e�N�X�`���̐ݒ�
	pEnemy->m_pArm->SetTextureParameter(1, 4, 1, INT_MAX);		//�e�N�X�`���p�����[�^�̐ݒ�
	pEnemy->m_pArm->SetPriority(2);								//�v���C�I���e�B�̐ݒ�
	pEnemy->m_pArm->SetStartingRot(D3DX_PI * 0.5f);				//�����̏����l�̐ݒ�

	return pEnemy;				//�������ꂽ�C���X�^���X�ւ̃|���^��Ԃ�
}



//==========================================================================================================
//
//										�v���C�x�[�g�֐�
//
//==========================================================================================================


//��Ԃɂ���Ă̍X�V����
void CWrathBody::UpdateState(void)
{
	D3DXVECTOR3 pos = GetPos();					//�ʒu�̎擾
		
	switch (m_state)
	{
	case CWrathBody::state_spawn:

	{//�X�|�[�����

		//�㉺�ړ��̐ݒ�
		pos.y += 0.5f * sinf(m_fAngleMove);				
		m_fAngleMove += D3DX_PI * 0.01f;

		if (pos.x <= 950.0f)
		{//���܂����ʒu�ɂ�����
			m_state = state_normal;							//���ʂ̏�Ԃɂ���
			SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));			//���x�̐ݒ�
		}

		SetPos(pos);					//�ʒu�̐ݒ�
	}

		break;

	case CWrathBody::state_normal:

	{//���ʏ��

	 //�㉺�ړ��̐ݒ�
		pos.y += 0.5f * sinf(m_fAngleMove);
		m_fAngleMove += D3DX_PI * 0.01f;

		SetPos(pos);			//�ʒu�̐ݒ�

		m_nCntState++;			//�J�E���^�[���X�V����

		if (m_nCntState >= 90)
		{//90�t���[�����o������

			m_nCntState = 0;				//�J�E���^�[��0�ɖ߂�

			//�����_���Ŏ��̍U�������߂�
			int nSelect = CObject::random(CWrathBody::state_flamethrower, CWrathBody::state_swirl);

			switch (nSelect)
			{
			case state_flamethrower:

			{//���U��

				m_state = state_flamethrower;		//��Ԃ̍X�V
				SetAnimPattern(1);					//�A�j���V�����p�^�[���̐ݒ�
			}

				break;

			case state_rage:

			{//�{��̍U��

				m_state = state_rage;						//��Ԃ̍X�V
				SetAnimPattern(1);							//�A�j���V�����p�^�[���̐ݒ�
				SetMove(D3DXVECTOR3(2.0f, 0.0f, 0.0f));		//���x�̐ݒ�
			}

				break;

			case state_swirl:

			{//�Q���U��
				m_state = state_swirl;				//��Ԃ̍X�V
			}

				break;

			default:
				break;
			}
		}
	}

		break;

	case CWrathBody::state_flamethrower:

	{//���U��

		m_nShootDelay++;				//�U���J�E���^�[���X�V����

		if (m_nShootDelay >= 50)
		{//50�t���[�����o������

			if (m_nShootDelay % 20 == 19)
			{//20�t���[�����ƃA�j���V�����p�^�[�����X�V����

				if (GetPresentAnimPattern() == 2)
				{
					SetAnimPattern(3);		//�A�j���V�����p�^�[�����X�V����
				}
				else
				{
					SetAnimPattern(2);		//�A�j���V�����p�^�[�����X�V����
				}
			}

			if (m_nShootDelay % 20 == 19)
			{//20�t���[�����ƒe�𔭐�����

				D3DXVECTOR3 playerPos = CPlayer::GetPlayer()->GetPos();			//�v���C���[�̈ʒu�̎擾
				D3DXVECTOR3 move = playerPos - pos;								//���x�̌v�Z
				D3DXVec3Normalize(&move, &move);								//���x�𐳋K������

				//�e�𐶐�����
				CSkullFireball::Create(pos, D3DXVECTOR3(move.x * 3.0f, move.y * 3.0f, 0.0f));

				//���S������}15���Ɓ}30���ɂ��e�𔭐�����
				D3DXVECTOR3 unit = D3DXVECTOR3(1.0f, 0.0f, 0.0f);		//�P�ʃx�N�g���̐錾

				float fAngle = acosf(D3DXVec3Dot(&move, &unit));		//�ŏ��̒e�̊p�x���v�Z����

				if (playerPos.y < pos.y)
				{//�K�v��������A���K������
					fAngle *= -1.0f;
				}

				//���Ԃɂ���Ēe�𔭐�����(�ŏ���1�����A���͂R�A�Ō�ɂT��)
				if (m_nPhase > 0)
				{//�}15���̒e�𐶐����邷��
					D3DXVECTOR3 NewMove = D3DXVECTOR3(cosf(fAngle) * cosf(D3DX_PI / 12.0f) - sinf(fAngle) * sinf(D3DX_PI / 12.0f),
						sinf(fAngle) * cosf(D3DX_PI / 12.0f) + cosf(fAngle) * sinf(D3DX_PI / 12.0f), 0.0f);

					CSkullFireball::Create(pos, D3DXVECTOR3(NewMove.x * 3.0f, NewMove.y * 3.0f, 0.0f));

					NewMove = D3DXVECTOR3(cosf(fAngle) * cosf(-D3DX_PI / 12.0f) - sinf(fAngle) * sinf(-D3DX_PI / 12.0f),
						sinf(fAngle) * cosf(-D3DX_PI / 12.0f) + cosf(fAngle) * sinf(-D3DX_PI / 12.0f), 0.0f);

					CSkullFireball::Create(pos, D3DXVECTOR3(NewMove.x * 3.0f, NewMove.y * 3.0f, 0.0f));
				}
				if (m_nPhase == 2)
				{//�}30���̒e�𐶐����邷��
					D3DXVECTOR3 NewMove = D3DXVECTOR3(cosf(fAngle) * cosf(D3DX_PI / 6.0f) - sinf(fAngle) * sinf(D3DX_PI / 6.0f),
						sinf(fAngle) * cosf(D3DX_PI / 6.0f) + cosf(fAngle) * sinf(D3DX_PI / 6.0f), 0.0f);

					CSkullFireball::Create(pos, D3DXVECTOR3(NewMove.x * 3.0f, NewMove.y * 3.0f, 0.0f));

					NewMove = D3DXVECTOR3(cosf(fAngle) * cosf(-D3DX_PI / 6.0f) - sinf(fAngle) * sinf(-D3DX_PI / 6.0f),
						sinf(fAngle) * cosf(-D3DX_PI / 6.0f) + cosf(fAngle) * sinf(-D3DX_PI / 6.0f), 0.0f);

					CSkullFireball::Create(pos, D3DXVECTOR3(NewMove.x * 3.0f, NewMove.y * 3.0f, 0.0f));
				}

				if (m_nShootDelay == 99 || m_nShootDelay == 159)
				{//100�t���[����160�t���[�����o������A�J�E���^�[���C���N�������g����
					m_nPhase++;
				}
				else if(m_nShootDelay == 240 || m_nShootDelay == 300)
				{//240�t���[����300�t���[�����o������A�J�E���^�[���f�N�������g����
					m_nPhase--;
				}
				
				if (m_nShootDelay >= 360)
				{//360�t���[���𒴂�����A���ʂ̏�Ԃɖ߂�

					if (m_nCntShoot >= 2)
					{//3�񂱂̍U����������
						SetAnimPattern(1);			//�A�j���V�����p�^�[���̐ݒ�
						m_state = state_normal;		//��Ԃ̍X�V
						m_nPhase = 0;				//�J�E���^�[��0�ɖ߂�
						m_nShootDelay = 0;			//�U���J�E���^�[��0�ɖ߂�
						m_nCntShoot = 0;			//�U�����̃J�E���^�[��0�ɖ߂�
					}
					else
					{
						m_nPhase = 0;				//�J�E���^�[��0�ɖ߂�
						m_nShootDelay = -70;		//�U���J�E���^�[��-70�ɐݒ肷��(70�t���[����҂��āA������x�U������)
						m_nCntShoot++;				//�U�����̃J�E���^�[���C���N�������g����
					}
				}

				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_FIRE);			//�T�E���h���Đ�����
			}
		}
	}

		break;

	case CWrathBody::state_rage:

	{//�{��U��

		switch (m_nPhase)
		{
		case 0:

		{
			if (pos.x >= 1400.0f)
			{//��ʂ��o����

				SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));			//���x�̐ݒ�
				m_nPhase++;				//�J�E���^�[���C���N�������g����
			}
		}

			break;

		case 1:

		{
			m_nShootDelay++;			//�U���J�E���^�[���C���N�������g����

			if (m_nShootDelay == 5)
			{
				m_targetPos = CPlayer::GetPlayer()->GetPos();			//�ړI�̈ʒu�̐ݒ�
			}

			if (m_nShootDelay % 10 == 9 && m_nShootDelay >= 60)
			{//��ʂ̏㑤�Ɖ�������e�𔭐�����

				CSkullFireball::Create(D3DXVECTOR3(m_targetPos.x, (float)SCREEN_HEIGHT - 1.0f, 0.0f), D3DXVECTOR3(0.0f, -5.0f, 0.0f));
				CSkullFireball::Create(D3DXVECTOR3(m_targetPos.x - 20.0f, 1.0f, 0.0f), D3DXVECTOR3(0.0f, 5.0f, 0.0f));
				CSkullFireball::Create(D3DXVECTOR3(m_targetPos.x + 20.0f, 1.0f, 0.0f), D3DXVECTOR3(0.0f, 5.0f, 0.0f));

				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_FIRE);			//�T�E���h���Đ�����
			}

			if (m_nShootDelay >= 180)
			{//3�b���o������
				m_nShootDelay = 0;		//�U���J�E���^�[��0�ɖ߂�
				m_nCntShoot++;			//�U�����̃J�E���^�[���C���N�������g����
			}

			if (m_nCntShoot >= 5)
			{//���̍U����5�񂵂���

				//�J�E���^�[��0�ɖ߂�
				m_nShootDelay = 0;
				m_nCntShoot = 0;
				m_nPhase++;

				SetMove(D3DXVECTOR3(-2.0f, 0.0f, 0.0f));		//�ړ��ʂ̐ݒ�
			}
		}

			break;

		case 2:

		{
			{
				//�㉺�̈ړ��̐ݒ�
				pos.y += 0.5f * sinf(m_fAngleMove);
				m_fAngleMove += D3DX_PI * 0.01f;

				if (pos.x <= 950.0f)
				{//���܂����ʒu�ɒ�������
					m_nPhase = 0;								//�J�E���^�[��0�ɖ߂�
					m_state = state_normal;						//��Ԃ̍X�V
					SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//���x�̐ݒ�
				}
					
				SetPos(pos);					//�ʒu�̐ݒ�
			}
		}

		default:
			break;
		}
	}

		break;

	case CWrathBody::state_swirl:

	{//�Q���̍U��

		m_nShootDelay++;				//�U���J�E���^�[���C���N�������g����

		{
			//�㉺�̈ړ��̐ݒ�
			pos.y += 0.5f * sinf(m_fAngleMove);
			m_fAngleMove += D3DX_PI * 0.01f;

			SetPos(pos);			//�ʒu�̐ݒ�
		}

		if (m_nShootDelay % 20 == 19)
		{//20�t���[�����ƃA�j���V�����p�^�[�����X�V����
			if (GetPresentAnimPattern() == 2)
			{
				SetAnimPattern(3);
			}
			else
			{
				SetAnimPattern(2);
			}
		}

		if (m_nShootDelay % 40 == 39)
		{//40�t���[�����ƉQ���̒e�𔭐�����

			float fStart = D3DX_PI * random(-500, 500) * 0.01f;

			for (int nCnt = 0; nCnt < 10; nCnt++)
			{
				D3DXVECTOR3 move = D3DXVECTOR3(5.0f * cosf(fStart + D3DX_PI * 2.0f * nCnt / 10.0f), 5.0f * sinf(fStart + D3DX_PI * 2.0f * nCnt / 10.0f), 0.0f);

				CSkullFireball::Create(pos, move);			//�e�̐���
			}

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_FIRE);			//�T�E���h���Đ�����
		}

		if (m_nShootDelay % 40 == 19)
		{//40�t���[�����ƃv���C���[�̈ʒu��_�����e�𔭐�����

			//���x���v�Z����
			D3DXVECTOR3 move = D3DXVECTOR3(CPlayer::GetPlayer()->GetPos() - pos);
			D3DXVec3Normalize(&move, &move);
			move.x *= 5.0f;
			move.y *= 5.0f;

			CSkullFireball::Create(pos, move);			//�e�𔭐�����
		}

		if (m_nShootDelay >= 600)
		{//600�t���[�����o������A���ʂ̏�Ԃɖ߂�
			m_nShootDelay = 0;				//�U���J�E���^�[��0�ɖ߂�
			m_state = state_normal;			//���ʂ̏�Ԃɖ߂�
		}
	}

		break;

	case CWrathBody::state_death:

	{//���S���

		if (m_nPhase == 0)
		{
			if (pos.y >= (float)SCREEN_HEIGHT + GetSize().y * 0.5f)
			{

				//�r��null�ł͂Ȃ�������
				if (m_pArm != nullptr)
				{//null�`�F�b�N
					m_pArm->SetMove(D3DXVECTOR3(0.0f, 2.0f, 0.0f));		//���x�̐ݒ�
					m_nPhase++;											//�J�E���^�[���C���N�������g����
				}
			}
		}
		else if (m_nPhase == 1)
		{
			if (m_pArm->GetPos().y >= (float)SCREEN_HEIGHT + m_pArm->GetSize().y)
			{//���̃C���X�^���X����ʂ��o����A���S��Ԃɂ���
				m_bDead = true;
			}
		}
	}

		break;

	default:
		break;
	}
}