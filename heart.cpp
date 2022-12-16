//=============================================================================
//
// heart.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "heart.h"
#include "squareHitbox.h"
#include "heartBullet.h"
#include "player.h"
#include "enemyLife.h"

//�R���X�g���N�^
CHeart::CHeart()
{
	//�����o�[�ϐ����N���A����
	m_fAngleShoot = 0.0f;
	m_state = state_spawn;

	m_bEnd = false;

	m_pLife = nullptr;
	m_pHitbox = nullptr;
}

//�f�X�g���N�^
CHeart::~CHeart()
{

}

//����������
HRESULT CHeart::Init(void)
{
	if (FAILED(CEnemy::Init()))
	{//��{�N���X�̏���������
		return -1;
	}

	//�����o�[�ϐ�������������
	m_fAngleShoot = 0.0f;
	m_state = state_spawn;
	m_bEnd = false;

	m_pLife = nullptr;
	m_pHitbox = nullptr;

	return S_OK;
}

//�I������
void CHeart::Uninit(void)
{
	//�q�b�g�{�b�N�X�̔j������
	if (m_pHitbox != nullptr)
	{//null�`�F�b�N
		m_pHitbox->Release();		//���������������
		m_pHitbox = nullptr;		//�|�C���^��null�ɂ���
	}

	//�̗�UI�̔j������
	if (m_pLife != nullptr)
	{//null�`�F�b�N
		m_pLife->Release();			//���������������
		m_pLife = nullptr;			//�|�C���^��null�ɂ���
	}

	//��{�N���X�̏I������
	CEnemy::Uninit();
}

//�X�V����
void CHeart::Update(void)
{
	//��Ԃɂ���Ă̍X�V����
	UpdateState();

	//��{�N���X�̍X�V����
	CObject_2D::Update();

	//�q�b�g�{�b�N�X�̍X�V����
	if (m_pHitbox != nullptr)
	{//null�`�F�b�N

		if (m_pHitbox->GetHitState())
		{//�I�������Ԃ�������A

			m_pHitbox->SetHitState(false);			//�����Ă��Ȃ���Ԃɖ߂�

			int nDamage = CPlayer::GetPlayer()->GetAttack();		//�v���C���[�̍U���͂̎擾

			int nLife = GetLife();					//�̗͂̎擾
				
			nLife -= nDamage;						//�̗͂̍X�V

			//�̗�UI�̍X�V
			if (m_pLife != nullptr)
			{//null�`�F�b�N
				m_pLife->SubtractLife(nDamage);
			}

			if (nLife <= 0)
			{//�̗͂�0�ȉ��ɂȂ�����

				m_state = state_death;	//���S��Ԃɂ���
				m_pHitbox->Release();	//�q�b�g�{�b�N�X��j������
				m_pHitbox = nullptr;	//�q�b�g�{�b�N�X�ւ̃|�C���^��null�ɂ���
				SetLife(0);				//�̗͂̐ݒ�
				m_nCntMove = 0;			//�ړ��J�E���^�[��0�ɂ���
			}
			else
			{//�̗͂�0�ȉ��ł͂Ȃ�������
				SetLife(nLife);			//�̗͂̐ݒ�
			}
		}
	}
}

//�`�揈��
void CHeart::Draw(void)
{
	//��{�N���X�̕`�揈��
	CObject_2D::Draw();
}

//�N�����Ԃ̐ݒ菈��
void CHeart::SetActive(void)
{
	m_state = state_awake;						//��Ԃ̐ݒ�
	SetMove(D3DXVECTOR3(0.0f, 1.0f, 0.0f));		//���x�̐ݒ�
}

//�I��������ǂ����̐ݒ菈��
const bool CHeart::GetEnd(void)
{
	return m_bEnd;
}



//=============================================================================
//
//								�ÓI�֐�
//
//=============================================================================



//��������
CHeart* CHeart::Create(void)
{
	CHeart* pEnemy = new CHeart;			//�C���X�^���X�𐶐�����

	if (FAILED(pEnemy->Init()))
	{//����������
		return nullptr;
	}

	pEnemy->SetPos(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, 150.0f, 0.0f));		//�ʒu�̐ݒ�
	pEnemy->SetSize(D3DXVECTOR2(70.0f, 103.6f));								//�T�C�Y�̐ݒ�
	pEnemy->SetStartingRot(D3DX_PI * 0.5f);										//�����̏����l�̐ݒ�
	pEnemy->SetTexture(CObject::TextureGluttonyHeart);							//�e�N�X�`���̐ݒ�
	pEnemy->SetTextureParameter(2, 2, 1, 20);									//�e�N�X�`���p�����[�^�̐ݒ�
	pEnemy->SetPriority(2);														//�v���C�I���e�B�̐ݒ�
	pEnemy->SetLife(10000);														//�̗͂̐ݒ�

	//�q�b�g�{�b�N�X�̐���
	pEnemy->m_pLife = CEnemyLife::Create(D3DXVECTOR3(850.0f, 40.0f, 0.0f), D3DXCOLOR(0.0f, 1.0f, 0.3f, 0.5f), 10000, "gluttony");

	return pEnemy;					//���������C���X�^���X��Ԃ�
}



//=============================================================================
//
//							�v���C�x�[�g�֐�
//
//=============================================================================



//��Ԃɂ���Ă̍X�V����
void CHeart::UpdateState(void)
{
	switch (m_state)
	{
	case CHeart::state_spawn:

	{//�X�|�[�����

		m_nCntMove++;		//�ړ��J�E���^�[���X�V����

		if (m_nCntMove == 30)
		{//30�t���[�����o������A�㑤�̂ق��ɓ�����
			SetMove(D3DXVECTOR3(0.0f, -1.0f, 0.0f));
		}

		if (GetPos().y <= -150.0f)
		{//��ʂ��o����

			SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));			//���x�̐ݒ�
			m_nCntMove = 0;									//�ړ��J�E���^�[��ݒ肷��
			m_state = state_sleep;							//�Q���Ԃɐݒ肷��
		}
	}

		break;

	case CHeart::state_awake:

	{//�N������

		if (GetPos().y >= 150.0f)
		{//���܂����ʒu�ɒ�������

			SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//���x�̐ݒ�
			m_state = state_vulnerable;					//�_���[�W���󂯂��Ԃɂ���

			//�q�b�g�{�b�N�X�̐���
			if (m_pHitbox == nullptr)
			{
				m_pHitbox = CSquareHitbox::Create(GetPos(), D3DXVECTOR2(40.0f, 70.0f), CHitbox::Type_Enemy);
			}
		}
	}

		break;

	case CHeart::state_vulnerable:

	{//�_���[�W���󂯂���

		m_nShootDelay++;				//�U���J�E���^�[���C���N�������g����

		if (m_nShootDelay % 90 == 30)
		{//90�t���[�����ƒe�𔭐�����

			CHeartBullet* pBullet = nullptr;

			for (int nCnt = 0; nCnt < 6; nCnt++)
			{//�S�`�̒e��6��������

				D3DXVECTOR3 move = D3DXVECTOR3(5.0f * (cosf(nCnt * (D3DX_PI / 6)) * cosf(m_fAngleShoot) + sinf(nCnt * (D3DX_PI / 6)) * sinf(m_fAngleShoot)),
					5.0f * (sinf((nCnt * (D3DX_PI / 6))) * cosf(m_fAngleShoot) - cosf(nCnt * (D3DX_PI / 6)) * sinf(m_fAngleShoot)), 0.0f);

				pBullet = CHeartBullet::Create(GetPos(), move, D3DXCOLOR(1.0f, 0.51f, 0.5f, 0.75f));
				pBullet->SetLife(90);
			}

			m_fAngleShoot -= D3DX_PI * 0.05f;			//�U���̊p�x�̍X�V

			if (m_fAngleShoot <= -D3DX_PI * 0.17f)
			{//���܂����p�x�𒴂�����A0�ɖ߂�
				m_fAngleShoot = 0.0f;
			}

			if (m_nShootDelay >= 550)
			{//550�t���[�����o������
				m_nShootDelay = 0;							//�U���J�E���^�[��0�ɖ߂�
				m_state = state_return;						//�߂��Ԃɂ���
				SetMove(D3DXVECTOR3(0.0f, -1.0f, 0.0f));	//���x�̐ݒ�
				m_pHitbox->Release();						//�q�b�g�{�b�N�X�̔j��
				m_pHitbox = nullptr;						//�q�b�g�{�b�N�X�ւ̃|�C���^��null�ɂ���
			}
		}
	}

		break;

	case CHeart::state_return:

	{//�߂���

		if (GetPos().y <= -150.0f)
		{//���܂����ʒu�ɒ�������

			SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));			//���x�̐ݒ�
			m_nCntMove = 0;									//�ړ��J�E���^�[��0�ɖ߂�
			m_state = state_sleep;							//�Q���Ԃɖ߂�
		}
	}

		break;

	case CHeart::state_death:

	{//���S���

		m_nCntMove++;			//�J�E���^�[���C���N�������g����

		D3DXCOLOR col = GetColor();		//�F�̎擾

		if (col.r >= 0.25f)
		{//�܂������Ȃ��ꍇ

			//�F���Â�����
			col.r -= 0.0125f;
			col.g -= 0.0125f;
			col.b -= 0.0125f;

			SetColor(col);			//�F�̐ݒ�
		}
		else
		{//�����Ȃ�����A�I�������Ԃɂ���
			m_bEnd = true;
		}
	}


		break;

	case CHeart::state_sleep:


		break;

	default:
		break;
	}
}