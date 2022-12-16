//=============================================================================
//
// envy.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "envy.h"
#include "squareHitbox.h"
#include "missile.h"
#include "spikeBomb.h"
#include "player.h"
#include "envyPieces.h"
#include "explosion.h"
#include "enemyLife.h"
#include "application.h"
#include "sound.h"

//=============================================================================
//							�ÓI�ϐ��̏�����
//=============================================================================
const D3DXVECTOR2 CEnvy::m_EnvySize = D3DXVECTOR2(140.0f, 118.0f);			//�T�C�Y
const D3DXVECTOR2 CEnvy::m_HitboxEnvySize = D3DXVECTOR2(110.0f, 120.0f);	//�q�b�g�{�b�N�X�T�C�Y
const D3DXVECTOR2 CEnvy::m_HitboxHatSize = D3DXVECTOR2(95.0f, 115.0f);		//�X�q�̃q�b�g�{�b�N�X�T�C�Y

//�R���X�g���N�^
CEnvy::CEnvy()
{
	//�����o�[�ϐ����N���A����
	for (int nCnt = 0; nCnt < nGearNum; nCnt++)
	{
		m_pGear[nCnt] = nullptr;
		m_gearRelativePos[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	for (int nCnt = 0; nCnt < nPipeNum; nCnt++)
	{
		m_pPipe[nCnt] = nullptr;
		m_pipeRelativePos[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	m_hatRelativePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_cannonRelativePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_nCntState = 0;
	m_state = state_spawn;
	m_bEnd = false;

	m_pCannon = nullptr;
	m_pHat = nullptr;
	m_pHitbox = nullptr;
	m_pHatHitbox = nullptr;
	m_pLife = nullptr;
}

CEnvy::~CEnvy()
{

}

//����������
HRESULT CEnvy::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CEnemy::Init()))
	{
		return -1;
	}

	//�����o�[�ϐ�������������
	for (int nCnt = 0; nCnt < nGearNum; nCnt++)
	{
		m_pGear[nCnt] = nullptr;
		m_gearRelativePos[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
	
	for (int nCnt = 0; nCnt < nPipeNum; nCnt++)
	{
		m_pPipe[nCnt] = nullptr;
		m_pipeRelativePos[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	m_hatRelativePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_cannonRelativePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_nCntState = 0;
	m_state = state_spawn;
	m_bEnd = false;

	m_pCannon = nullptr;
	m_pHat = nullptr;
	m_pHitbox = nullptr;
	m_pHatHitbox = nullptr;
	m_pLife = nullptr;

	return S_OK;
}

//�I������
void CEnvy::Uninit(void)
{
	//���Ԃ̔j������
	for (int nCnt = 0; nCnt < nGearNum; nCnt++)
	{
		if (m_pGear[nCnt] != nullptr)
		{//null�`�F�b�N
			m_pGear[nCnt]->Release();			//���������������
			m_pGear[nCnt] = nullptr;			//�|�C���^��null�ɂ���
		}
	}

	//�X�q�̔j������
	if (m_pHat != nullptr)
	{//null�`�F�b�N
		m_pHat->Release();						//���������������
		m_pHat = nullptr;						//�|�C���^��null�ɂ���
	}

	//��C�̔j������
	if (m_pCannon != nullptr)
	{//null�`�F�b�N 
		m_pCannon->Release();					//���������������
		m_pCannon = nullptr;					//�|�C���^��null�ɂ���
	}

	//�ǂ̔j������
	for (int nCnt = 0; nCnt < nPipeNum; nCnt++)
	{
		if (m_pPipe[nCnt] != nullptr)
		{//null�`�F�b�N
			m_pPipe[nCnt]->Release();			//���������������
			m_pPipe[nCnt] = nullptr;			//�|�C���^��null�ɂ���
		}
	}
	
	//�q�b�g�{�b�N�X�̔j������
	if (m_pHitbox != nullptr)
	{//null�`�F�b�N
		m_pHitbox->Release();					//���������������
		m_pHitbox = nullptr;					//�|�C���^��null�ɂ���
	}

	//�X�q�̔j������
	if (m_pHatHitbox != nullptr)
	{//null�`�F�b�N
		m_pHatHitbox->Release();				//���������������
		m_pHatHitbox = nullptr;					//�|�C���^��null�ɂ���
	}

	//�̗�UI�̔j������
	if (m_pLife != nullptr)
	{//null�`�F�b�N
		m_pLife->Release();						//���������������
		m_pLife = nullptr;						//�|�C���^��null�ɂ���
	}
}

//�X�V����
void CEnvy::Update(void)
{
	UpdatePointers();				//�|�C���g�̍X�V����

	//����ł��Ȃ�������A�㉺�Ɉړ�������
	if (m_state != state_death)
	{
		m_fAngleMove += D3DX_PI * 0.02f;
		D3DXVECTOR3 pos = GetPos();
		pos.y += 0.5f * sinf(m_fAngleMove);
		SetPos(pos);
	}

	UpdateState();			//��Ԃɂ���Ă̍X�V����

	if (!m_bEnd)
	{//����ł��Ȃ�������
		CObject_2D::Update();	//��{�N���X�̍X�V����
	}
}

//�`�揈��
void CEnvy::Draw(void)
{
	//��{�N���X�̕`�揈��
	CObject_2D::Draw();
}

//�I��������ǂ����̎擾����
const bool CEnvy::GetEnd(void)
{
	return m_bEnd;
}



//=============================================================================
//
//								�ÓI�֐�
//
//=============================================================================



//��������
CEnvy* CEnvy::Create(void)
{
	CEnvy* pEnemy = new CEnvy;		//�C���X�^���X�𐶐�����

	if (FAILED(pEnemy->Init()))
	{//����������
		return nullptr;
	}

	D3DXVECTOR3 pos = D3DXVECTOR3(1500.0f, 400.0f, 0.0f);

	pEnemy->SetPos(pos);									//�ʒu�̐ݒ�
	pEnemy->SetSize(m_EnvySize);							//�T�C�Y�̐ݒ�
	pEnemy->SetTexture(CObject::TextureFace);				//�e�N�X�`���̐ݒ�
	pEnemy->SetTextureParameter(1, 1, 1, INT_MAX);			//�e�N�X�`���p�����[�^�̐ݒ�
	pEnemy->SetStartingRot(D3DX_PI * 0.5f);					//�����̏����l�̐ݒ�
	pEnemy->SetMove(D3DXVECTOR3(-5.0f, 0.0f, 0.0f));		//���x�̐ݒ�
	pEnemy->SetLife(15000);									//�̗͂̐ݒ�

	pEnemy->CreateGears();			//���Ԃ̐�������

	//�q�b�g�{�b�N�X�̐�������
	pEnemy->m_pHitbox = CSquareHitbox::Create(pos, m_HitboxEnvySize, CHitbox::Type_Enemy);
	pEnemy->m_pHatHitbox = CSquareHitbox::Create(pos + pEnemy->m_hatRelativePos, m_HitboxHatSize, CHitbox::Type_Enemy);

	//�̗͂�UI�̐�������
	pEnemy->m_pLife = CEnemyLife::Create(D3DXVECTOR3(900.0f, 40.0f, 0.0f), D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.4f), 15000, "envy");

	return pEnemy;					//���������C���X�^���X��Ԃ�
}



//=============================================================================
//
//							�v���C�x�[�g�֐�
//
//=============================================================================



//���Ԃ̐�������
void CEnvy::CreateGears(void)
{
	//�ǂ̑��Έʒu�̐ݒ�
	m_pipeRelativePos[0] = D3DXVECTOR3(-25.0f, -125.0f, 0.0f);
	m_pipeRelativePos[1] = D3DXVECTOR3(35.0f, -140.0f, 0.0f);

	for (int nCnt = 0; nCnt < nPipeNum; nCnt++)
	{
		//�ǂ̐����ƕK�v�ȏ��̐ݒ�
		if (m_pPipe[nCnt] == nullptr)
		{
			m_pPipe[nCnt] = CObject_2D::Create();
			m_pPipe[nCnt]->SetPos(GetPos() + m_pipeRelativePos[nCnt]);
			m_pPipe[nCnt]->SetStartingRot(D3DX_PI * 0.5f);
			m_pPipe[nCnt]->SetTexture(CObject::TexturePipe);
			m_pPipe[nCnt]->SetTextureParameter(1, 1, 1, INT_MAX);
			m_pPipe[nCnt]->SetPriority(2);
		}
	}

	if (m_pCannon == nullptr)
	{
		//��C�̐����ƕK�v�ȏ��̐ݒ�
		m_cannonRelativePos = D3DXVECTOR3(0.0f, -75.0f, 0.0f);
		m_pCannon = CObject_2D::Create();
		m_pCannon->SetPos(GetPos() + m_cannonRelativePos);
		m_pCannon->SetTexture(CObject::TexturePipe);
		m_pCannon->SetTextureParameter(1, 1, 1, INT_MAX);
		m_pCannon->SetPriority(2);
		m_pCannon->SetSize(D3DXVECTOR2(15.0f, 48.75f));
		m_pCannon->SetStartingRot(D3DX_PI);
	}

	//�ǂ̃T�C�Y�̐ݒ�
	m_pPipe[0]->SetSize(D3DXVECTOR2(33.75f, 45.0f));
	m_pPipe[1]->SetSize(D3DXVECTOR2(22.5f, 67.5f));

	//���Ԃ̑��Έʒu�̐ݒ�
	m_gearRelativePos[0] = D3DXVECTOR3(10.0f, -110.0f, 0.0f);
	m_gearRelativePos[1] = D3DXVECTOR3(70.0f, -120.0f, 0.0f);
	m_gearRelativePos[2] = D3DXVECTOR3(30.0f, -105.0f, 0.0f);
	m_gearRelativePos[3] = D3DXVECTOR3(100.0f, -110.0f, 0.0f);
	m_gearRelativePos[4] = D3DXVECTOR3(-20.0f, -100.0f, 0.0f);
	m_gearRelativePos[5] = D3DXVECTOR3(-60.0f, -110.0f, 0.0f);

	//���Ԃ̃T�C�Y�Ɖ�]���x�̐ݒ�
	D3DXVECTOR2 size[nGearNum] = { {26.25f, 26.25f },{ 45.0f, 45.0f },{ 26.25f, 26.25f },{ 22.5f, 22.5f },{ 52.5f, 52.5f },{ 30.0f, 30.0f }};
	float fRotSpeed[nGearNum] = { D3DX_PI * 0.01f, -D3DX_PI * 0.01f, D3DX_PI * 0.02f, D3DX_PI * 0.008f, -D3DX_PI * 0.009f, D3DX_PI * 0.025f };

	for (int nCnt = 0; nCnt < nGearNum; nCnt++)
	{
		//���Ԃ̐����ƕK�v�ȏ��̐ݒ�
		if (m_pGear[nCnt] == nullptr)
		{
			m_pGear[nCnt] = CObject_2D::Create();
			m_pGear[nCnt]->SetPos(GetPos() + m_gearRelativePos[nCnt]);
			m_pGear[nCnt]->SetSize(size[nCnt]);
			m_pGear[nCnt]->SetRotation(fRotSpeed[nCnt]);
			m_pGear[nCnt]->SetTexture(CObject::TextureGear);
			m_pGear[nCnt]->SetTextureParameter(1, 3, 2, INT_MAX);
			m_pGear[nCnt]->SetPriority(2);
		}
	}

	//���Ԃ̃A�j���[�V�����p�^�[���̐ݒ�
	m_pGear[0]->SetAnimPattern(5);
	m_pGear[1]->SetAnimPattern(2);
	m_pGear[2]->SetAnimPattern(1);
	m_pGear[3]->SetAnimPattern(3);
	m_pGear[4]->SetAnimPattern(2);
	m_pGear[5]->SetAnimPattern(4);

	//�X�q�̑��Έʒu�̐ݒ�
	m_hatRelativePos = D3DXVECTOR3(20.0f, -230.0f, 0.0f);

	//�X�q�̐����ƕK�v�ȏ��̐ݒ�
	m_pHat = CObject_2D::Create();
	m_pHat->SetPos(GetPos() + m_hatRelativePos);
	m_pHat->SetSize(D3DXVECTOR2(160.0f, 144.0f));
	m_pHat->SetTexture(CObject::TextureTopHat);
	m_pHat->SetTextureParameter(1, 1, 1, INT_MAX);
	m_pHat->SetStartingRot(D3DX_PI * 0.5f);
}

//��Ԃɂ���Ă̍X�V����
void CEnvy::UpdateState(void)
{
	D3DXVECTOR3 pos = GetPos();			//�ʒu�̎擾

	switch (m_state)
	{
	case CEnvy::state_spawn:

	{//�X�|�[�����

		if (pos.x <= 900.0f)
		{//���܂����ʒu�ɒ�������

			SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));	//���x�̐ݒ�
			m_state = state_normal;					//���ʂ̏�Ԃɐݒ肷��
		}
	}

		break;

	case CEnvy::state_normal:

	{//���ʂ̏��

		m_nCntState++;			//��ԃJ�E���^�[���C���N�������g����
		m_nShootDelay++;		//�U���J�E���^�[���C���N�������g����		

		if (m_nShootDelay >= 120)
		{//120�t���[�����ƒe�𔭐�����

			m_nShootDelay = 0;			//�U���J�E���^�[��0�ɖ߂�

			//�e�𔭐�����
			CMissile* pBullet = CMissile::Create(D3DXVECTOR3(pos.x - 23.0f, pos.y - 180.0f, 0.0f), D3DXVECTOR3(0.0f, -3.0f, 0.0f));

			//�T�E���h���Đ�����
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_ROCKET_START);
		}

		//�ʒu�܂ł̋������v�Z����
		D3DXVECTOR3 target = CPlayer::GetPlayer()->GetPos();
		target -= pos + m_cannonRelativePos;
		target.x -= 20.0f;

		if (fabsf(target.x) < 100.0f || m_nCntState >= 1200)
		{//�ʒu�܂ł̋�����100.0f�ȉ���������A���͏�ԃJ�E���^�[��1200�𒴂�����

			m_nCntState = 0;			//��ԃJ�E���^�[��0�ɖ߂�

			SetMove(D3DXVECTOR3(3.0f, 0.0f, 0.0f));		//���x�̐ݒ�(��ʂ̉E������o��)

			m_state = state_hide;						//�B����Ԃɂ���
		}
	}

		break;
	case CEnvy::state_hide:

	{//�B�����

		m_nShootDelay++;			//�U���J�E���^�[���C���N�������g����

		if (pos.x >= 1450.0f)
		{//��ʂ��o����

			SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));			//�~�܂�

			m_state = state_strike;		//�U����Ԃɂ���
			m_nShootDelay = 0;			//�U���J�E���^�[��0�ɖ߂�
		}
	}

		break;

	case CEnvy::state_strike:

	{//�U�����

		m_nCntState++;			//��ԃJ�E���^�[���C���N�������g����
		m_nShootDelay++;		//�U���J�E���^�[���C���N�������g����

		if (m_nShootDelay % 40 == 39)
		{//40�t���[�����o������

			//�e2�𐶐�����
			CMissile* pBullet = CMissile::Create(D3DXVECTOR3(1400.0f, 240.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.5f, 0.0f, 0.0f));
			pBullet = CMissile::Create(D3DXVECTOR3(1400.0f, 480.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.5f, 0.0f, 0.0f));

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_ROCKET_START);		//�T�E���h���Đ�����
		}

		if (m_nShootDelay >= 60)
		{//60�t���[�����o������

			m_nShootDelay = 0;			//�U���J�E���^�[��0�ɖ߂�

			//�e3�𐶐�����
			float fY = (float)random(50, 190);
			CMissile* pBullet = CMissile::Create(D3DXVECTOR3(1400.0f, fY, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.5f, 0.0f, 0.0f));
			pBullet = CMissile::Create(D3DXVECTOR3(1400.0f, fY + 240.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.5f, 0.0f, 0.0f));
			pBullet = CMissile::Create(D3DXVECTOR3(1400.0f, fY + 480.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.5f, 0.0f, 0.0f));

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_ROCKET_START);		//�T�E���h���Đ�����]
		}

		if (m_nCntState >= 310)
		{//310�t���[�����o������

			m_nCntState = 0;							//��ԃJ�E���^�[��0�ɖ߂�
			m_nShootDelay = 0;							//�U���J�E���^�[��0�ɖ߂�
			m_state = state_spawn;						//��Ԃ��X�|�[����Ԃɂ���
			SetMove(D3DXVECTOR3(-5.0f, 0.0f, 0.0f));	//���x��ݒ肷��(�E���������)
		}
	}

		break;

	case state_death:

	{//���S���

		m_nCntState++;			//��ԃJ�E���^�[���C���N�������g����
		m_nShootDelay++;		//�U���J�E���^�[���C���N�������g����

		pos.y -= 50.0f;			//���S�_�̉�����e�𔭐�����(�_���[�W��^���Ȃ��e)

		if (m_nShootDelay % 30 == 0)
		{//30�t���[������

			int nRand = random(1, 3);		//��������e�̐���1�`3�ɂ���

			//============================================================================
			//���a�̒��Ɉʒu��ݒ肵�āA�����𐶐�����
			D3DXVECTOR3 P = pos;
			float radius = GetSize().x * 0.45f;

			P.x += (float)random((int)-radius, (int)radius);
			P.y += (float)random((int)-radius, (int)radius);

			CExplosion* pExplosion = CExplosion::Create();
			pExplosion->SetPos(P);
			pExplosion->SetSize(D3DXVECTOR2(50.0f, 50.0f));
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_BIG_EXPLOSION);
			//============================================================================

			for (int nCnt = 0; nCnt < nRand; nCnt++)
			{//��������e�̐���1�`3�ɂ���
				CEnvyPieces::Create(pos, radius);
			}
		}

		if (GetPos().y >= 1000.0f)
		{//��ʂ��o����A�I�������Ԃɂ���
			m_bEnd = true;
		}
	}

		break;
	
	default:
		break;
	}
}

//�|�C���^�̍X�V����
void CEnvy::UpdatePointers(void)
{
	//�X�q�̍X�V����
	if (m_pHat != nullptr)
	{//null�`�F�b�N

		//�X�q�̃q�b�g�{�b�N�X�̍X�V����
		if (m_pHatHitbox != nullptr)
		{//null�`�F�b�N

			//�ʒu�ƃq�b�g�{�b�N�X�̈ʒu��ݒ肷��
			m_pHat->SetPos(GetPos() + m_hatRelativePos);
			m_pHatHitbox->SetPos(m_pHat->GetPos());

			int life = GetLife();			//�̗͂̎擾

			if (m_pHatHitbox->GetHitState())
			{//����������Ԃ�������

				m_pHatHitbox->SetHitState(false);					//�����Ă��Ȃ���Ԃɖ߂�
				int nDamage = CPlayer::GetPlayer()->GetAttack();	//�v���C���[�̍U���͂̎擾
				life -= nDamage;									//�̗͂̍X�V
				SetLife(life);										//�̗͂̐ݒ�

				//�̗�UI�̍X�V
				if (m_pLife != nullptr)
				{//null�`�F�b�N
					m_pLife->SubtractLife(nDamage);
				}
			}

			if (life < 10000)
			{//�̗͂�10000�ȉ��ɂȂ�����

				//�X�q�̑��x�Ɖ�����ݒ肵�āA��]������B�X�q�̃q�b�g�{�b�N�X��j������
				m_pHat->SetMove(D3DXVECTOR3(4.0f, -8.0f, 0.0f));
				m_pHat->SetAcceleration(D3DXVECTOR3(0.0f, 0.2f, 0.0f));
				m_pHat->SetRotation(-D3DX_PI * 0.025f);
				m_pHatHitbox->Release();
				m_pHatHitbox = nullptr;
			}
		}
		else
		{//�X�q�̃q�b�g�{�b�N�X�ւ̃|�C���^��null��������

			if (m_pHat->GetPos().y > 1000.0f || m_pHat->GetPos().x > 1500.0f)
			{//��ʂ��o����A�X�q��j������
				m_pHat->Release();
				m_pHat = nullptr;
			}
		}
	}

	//===========================================================================================================================================
	//��C�̍X�V����
	if (m_pCannon != nullptr && GetLife() < 12500)
	{//�̗͂�12500�ȉ��ɂȂ�����

		int a = 0;
		if (m_cannonRelativePos.x > -115.0f)
		{//��C��������܂ŁA���ֈړ�������
			m_cannonRelativePos.x += -0.5f;
		}
		else
		{//���܂����ʒu�ɒ�������

			if (m_nShootDelay % 60 == 0 && (m_state == state_normal || m_state == state_hide))
			{//60�t���[�����ƒe�𔭐�����

				//��C����v���C���[�܂ł̃x�N�g�����v�Z����
				D3DXVECTOR3 target = CPlayer::GetPlayer()->GetPos();
				target -= GetPos() + m_cannonRelativePos;
				target.x -= 20.0f;

				if (fabsf(target.x) >= 100.0f)
				{//�߂����Ȃ��ꍇ

					//�e�𔭐�����
					D3DXVec3Normalize(&target, &target);
					target.x *= 5.0f;
					target.y *= 5.0f;

					D3DXVECTOR3 P = GetPos() + m_cannonRelativePos;
					P.x -= 20.0f;

					CSpikeBomb* pBullet = CSpikeBomb::Create(P, target);				//�e�̐���

					CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_CANNON);		//�T�E���h���Đ�����
				}
			}
		}
	}

	//���Ԃ̍X�V����
	for (int nCnt = 0; nCnt < nGearNum; nCnt++)
	{
		if (m_pGear[nCnt] != nullptr)
		{//null�`�F�b�N
			m_pGear[nCnt]->SetPos(GetPos() + m_gearRelativePos[nCnt]);		//�ʒu�̍X�V
		}
	}

	//�ǂ̍X�V����
	for (int nCnt = 0; nCnt < nPipeNum; nCnt++)
	{
		if (m_pPipe[nCnt] != nullptr)
		{//null�`�F�b�N
			m_pPipe[nCnt]->SetPos(GetPos() + m_pipeRelativePos[nCnt]);		//�ʒu�̍X�V
		}
	}

	//��C�̈ʒu�̍X�V
	if (m_pCannon != nullptr)
	{//null�`�F�b�N
		m_pCannon->SetPos(GetPos() + m_cannonRelativePos);
	}

	//�q�b�g�{�b�N�X�̍X�V����
	if (m_pHitbox != nullptr)
	{//null�`�F�b�N

		m_pHitbox->SetPos(GetPos());		//�q�b�g�{�b�N�X�̈ʒu�̍X�V

		if (m_state != state_death)
		{//���S��Ԃł͂Ȃ�������

			if (m_pHitbox->GetHitState())
			{//����������Ԃ�������

				m_pHitbox->SetHitState(false);			//�����Ă��Ȃ���Ԃɖ߂�

				int nLife = GetLife();								//�̗͂̎擾
				int nDamage = CPlayer::GetPlayer()->GetAttack();	//�v���C���[�̍U���͂̎擾
				nLife -= nDamage;									//�̗͂̍X�V

				//�̗͂�UI�̍X�V
				if (m_pLife != nullptr)
				{//null�`�F�b�N
					m_pLife->SubtractLife(nDamage);
				}

				if (nLife <= 0)
				{//�̗͂�0�ȉ��ɂȂ�����

					//���S��Ԃɂ��āA�q�b�g�{�b�N�X��j������
					m_state = state_death;
					SetMove(D3DXVECTOR3(0.0f, 1.0f, 0.0f));
					m_nCntState = 0;
					m_nShootDelay = 0;
					m_pHitbox->Release();
					m_pHitbox = nullptr;
					SetLife(0);
					return;
				}
				else
				{//�̗͂�0�ȏゾ������

					SetLife(nLife);		//�̗͂̐ݒ�
				}

				//�X�q�̃q�b�g�{�b�N�X�ւ̃|�C���^��null��������(�X�q����������)
				if (m_pHatHitbox == nullptr)
				{
					//�ʒu�Ƒ��x��ݒ肷��(�v���C���[�̕����ŏ�ɐݒ肷��B�d�ʂ�����̂ŁA�ォ�痎���Ă���)
					D3DXVECTOR3 pos = GetPos();
					pos.y -= 100.0f;

					D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					move.x = -0.01f * (float)random(100, 500);
					move.y = -0.01f * (float)random(400, 800);

					int nRand = random(1, 3);			//�����_���ŃX�|�[������e�̌���ݒ肷��

					for (int nCnt = 0; nCnt < nRand; nCnt++)
					{
						move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
						move.x = -0.01f * (float)random(100, 500);
						move.y = -0.01f * (float)random(400, 800);

						CEnvyPieces::Create(pos, move);
					}
				}
			}
		}
	}
}