//=============================================================================
//
// boundEnemy.cpp
// Author : Ricci Alex
//
//=============================================================================

//�C���N���[�h�t�@�C��
#include "enemyClock.h"
#include "clockNeedle.h"
#include "player.h"

//�R���X�g���N�^
CEnemyClock::CEnemyClock()
{
	//�����o�[�ϐ����N���A����
	m_pBoundBullet[MAX_BOUND_BULLET] = {};
	m_nCntBoundAnimation = 0;

	for (int nCnt = 0; nCnt < MAX_BOUND_BULLET; nCnt++)
	{
		m_bBound[nCnt] = false;
	}
}

//�f�X�g���N�^
CEnemyClock::~CEnemyClock()
{

}

//����������
HRESULT CEnemyClock::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CEnemy::Init()))
	{
		return -1;
	}

	//�����o�[�ϐ��̏�����
	m_nCntBoundAnimation = 0;

	for (int nCnt = 0; nCnt < MAX_BOUND_BULLET; nCnt++)
	{
		if (m_pBoundBullet[nCnt] != nullptr)
		{//null�`�F�b�N
			m_pBoundBullet[MAX_BOUND_BULLET]->Release();
			m_pBoundBullet[MAX_BOUND_BULLET] = nullptr;
			m_bBound[nCnt] = false;
		}
	}

	return S_OK;
}

//�I������
void CEnemyClock::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_BOUND_BULLET; nCnt++)
	{
		if (m_pBoundBullet[nCnt] != nullptr)
		{//null�`�F�b�N
			m_pBoundBullet[MAX_BOUND_BULLET]->Release();
			m_pBoundBullet[MAX_BOUND_BULLET] = nullptr;
		}
	}

	//��{�N���X�̏I������
	CEnemy::Uninit();
}

//�X�V����
void CEnemyClock::Update(void)
{
	UpdateClock();

	//��{�N���X�̍X�V����
	CObject_2D::Update();
}

//�`�揈��
void CEnemyClock::Draw(void)
{
	//��{�N���X�̕`�揈��
	CEnemy::Draw();
}


//��������
CEnemyClock* CEnemyClock::Create(D3DXVECTOR3 pos)
{
	CEnemyClock* pEnemy = new CEnemyClock;			//�G�𐶐�����

	if (pEnemy != nullptr)
	{//null�`�F�b�N

	 //����������
		if (FAILED(pEnemy->Init()))
		{//�������ł��Ȃ�������
			delete pEnemy;				//���������������
			return nullptr;				//null��Ԃ�
		}

		pEnemy->SetObjType(CObject::OBJTYPE_ENEMY);					//�I�u�W�F�N�g�̎�ނ�ݒ肷��
		pEnemy->SetSubtype(CObject::ENEMYTYPE_BOUND_CLOCK);			//�G�̎�ނ̐ݒ�

		pEnemy->SetPos(pos);											//�ʒu�̐ݒ�
		pEnemy->SetMaxSpeed(4.0f);										//�ő呬�x�̐ݒ�
		pEnemy->SetStartingRot(D3DX_PI * 0.5f);							//��]�p�x�̏����l
		pEnemy->m_fAngleMove = 0.0f;									//1�t���[���̉�]�p�x
		pEnemy->m_nCntMove = 0;											//�ړ��J�E���^
		pEnemy->m_nShootDelay = 0;										//�e�̔����J�E���^�[
		pEnemy->SetTextureParameter(1, 1, 1, INT_MAX);					//�e�N�X�`���p�����[�^�̐ݒ�
		pEnemy->SetSize(D3DXVECTOR2(75.0f, 75.0f));						//�T�C�Y�̐ݒ�

		pEnemy->SetMove(D3DXVECTOR3(-2.0f, 0.0f, 0.0f));				//���x�̐ݒ�
		pEnemy->SetAcceleration(D3DXVECTOR3(0.0f, 0.0f, 0.0f));			//�����̐ݒ�


		pEnemy->SetTexture(TextureClock);								//�e�N�X�`���̐ݒ�

		//�K�w�\���̒e�̐�������

		pEnemy->m_pBoundBullet[0] = CClockNeedle::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(20.0f, 20.0f));

		pEnemy->m_pBoundBullet[0]->SetStartingRot(-D3DX_PI * 0.5f);						//��]�p�x�̏����l
		pEnemy->m_pBoundBullet[0]->SetRotation(-D3DX_PI * 0.001f);						//1�t���[���̉�]�p�x
		pEnemy->m_pBoundBullet[0]->SetRevolution(pos, -D3DX_PI * 0.001f, 15.0f);		//1�t���[���̌��]�p�x
		pEnemy->m_bBound[0] = true;														//�����[�X����Ă��邩�ǂ���

		pEnemy->m_pBoundBullet[1] = CClockNeedle::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(30.0f, 30.0f));

		pEnemy->m_pBoundBullet[1]->SetStartingRot(-D3DX_PI * 0.5f);						//��]�p�x�̏����l
		pEnemy->m_pBoundBullet[1]->SetRotation(-D3DX_PI * 0.03f);						//1�t���[���̉�]�p�x
		pEnemy->m_pBoundBullet[1]->SetRevolution(pos, -D3DX_PI * 0.03f, 20.0f);			//1�t���[���̌��]�p�x
		pEnemy->m_bBound[1] = true;														//�����[�X����Ă��邩�ǂ���

	}

	return pEnemy;					//�G��Ԃ�
}


//���v�^�̓G�̍X�V����
void CEnemyClock::UpdateClock(void)
{
	D3DXVECTOR3 pos = GetPos();						//�ʒu�̎擾����
	D3DXVECTOR3 dir;								//����

	if (m_nCntMove <= 0)
	{
		DWORD dwExecLastTime = timeGetTime();		//���݂̎��Ԃ��擾

		srand(dwExecLastTime);

		m_nCntMove = (rand() % 91) + 30;			//���x�̌������ς��܂ł̃t���[�������v�Z����
		float fX, fY;

		fX = (float)((rand() % 24001) - 12000);		//���x��X�R���|�l���g

		fY = (float)((rand() % 15001) - 7500);		//���x��Y�R���|�l���g

		dir.x = fX;
		dir.y = fY;
		dir.z = 0.0f;

		D3DXVec3Normalize(&dir, &dir);				//���K������

		dir.x *= 3.0f;								//���x���v�Z����
		dir.y *= 3.0f;								//���x���v�Z����
	}
	else
	{
		dir = GetMove();							//���x�̎擾
	}

	//=========================================================================================
	//								��ʂ��o�Ȃ��悤��
	if (pos.x >= SCREEN_WIDTH * 0.9f)
	{
		pos.x = SCREEN_WIDTH * 0.9f;
		dir.x *= -1.0f;
	}
	if (pos.x <= SCREEN_WIDTH * 0.1f)
	{
		pos.x = SCREEN_WIDTH * 0.1f;
		dir.x *= -1.0f;
	}
	if (pos.y >= SCREEN_HEIGHT * 0.9f)
	{
		pos.y = SCREEN_HEIGHT * 0.9f;
		dir.y *= -1.0f;
	}
	if (pos.y <= SCREEN_HEIGHT * 0.1f)
	{
		pos.y = SCREEN_HEIGHT * 0.1f;
		dir.y *= -1.0f;
	}
	//
	//=========================================================================================

	SetMove(dir);				//���x�̐ݒ�
	pos += dir;					//�ʒu�̍X�V����
	SetPos(pos);				//�ʒu�̐ݒ�

	m_nCntMove--;				//�ړ��J�E���^�[�̍X�V

								//==========================================================================================
								//								�e����������
	if (m_nShootDelay > 0)
	{
		m_nShootDelay--;								//�J�E���^�[�̍X�V

		if (m_nShootDelay == 60)
		{
			RespawnNeedle();							//�V�����e�𐶐�����
		}
		else if (m_nShootDelay < 60 && m_nShootDelay > 0)
		{
			//�T�C�Y�̍X�V����
			D3DXVECTOR2 NeedleSize = m_pBoundBullet[0]->GetSize();
			float fD = 20.0f / 60.0f;
			m_pBoundBullet[0]->SetSize(D3DXVECTOR2(NeedleSize.x + fD, NeedleSize.y + fD));
			NeedleSize = m_pBoundBullet[1]->GetSize();
			fD = 30.0f / 60.0f;
			m_pBoundBullet[1]->SetSize(D3DXVECTOR2(NeedleSize.x + fD, NeedleSize.y + fD));
		}
		if (m_nShootDelay <= 0)
		{
			m_nShootDelay = 0;
		}
	}
	//
	//==========================================================================================
	//==========================================================================================
	//
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pBoundBullet[nCnt] != nullptr)
		{
			float fAngSpeed = m_pBoundBullet[nCnt]->GetAngularSpeed();				//��]���x�̎擾
			D3DXVECTOR2 size = m_pBoundBullet[nCnt]->GetSize();						//�T�C�Y�̎擾

			if (m_bBound[nCnt] == true)
			{
				//��]���x�̍X�V
				m_pBoundBullet[nCnt]->AddAngularSpeed(-D3DX_PI * 0.001f);

				if (fAngSpeed <= -D3DX_PI * 0.25f)
				{
					m_pBoundBullet[nCnt]->SetRotation(0.0f);				//��]���~�܂�
					CPlayer* pPlayer = CPlayer::GetPlayer();				//�v���C���[�����擾����
					D3DXVECTOR3 PlayerPos = pPlayer->GetPos();				//�v���C���[�̈ʒu���擾����
					D3DXVECTOR3 unit = D3DXVECTOR3(1.0f, 0.0f, 0.0f);		//�v�Z�p�̃��F�N�g��
					float dot = 0.0f;										//���ς��v�Z�p�̕ϐ�

					dir = PlayerPos - pos;									//�e�̌����̌v�Z
					D3DXVec3Normalize(&dir, &dir);							//�����̐��K��
					dot = D3DXVec3Dot(&dir, &unit);							//���ς��v�Z����
					float fAngle = acosf(dot);								//�v���C���[�ƓG�̒��̊p�x

					if (PlayerPos.y > pos.y)
					{
						fAngle *= -1.0f;
					}

					m_pBoundBullet[nCnt]->SetStartingRot(fAngle);									//�e�̉�]�p�x�̐ݒ�
					m_pBoundBullet[nCnt]->SetMove(D3DXVECTOR3(dir.x * 10.0f, dir.y * 10.0f, 0.0f));	//�e�̑��x�̐ݒ�
					m_pBoundBullet[nCnt]->SetRevolution(pos, 0.0f, 0.0f);							//���]���~�߂�
					m_bBound[nCnt] = false;															//�e�������[�X����
					m_pBoundBullet[nCnt] = nullptr;													//�|�C���^��null�ɂ���
					m_nShootDelay = 240;															//�J�E���^�[�̐ݒ�
				}
				else
				{
					fAngSpeed = m_pBoundBullet[nCnt]->GetAngularSpeed();							//��]���x�̍X�V
					m_pBoundBullet[nCnt]->SetRevolution(pos, fAngSpeed, size.x * 0.5f);				//���]�p�����[�^�̍X�V
				}
			}
			else
			{
				D3DXVECTOR3 BulletPos = m_pBoundBullet[nCnt]->GetPos();					 //�e�̈ʒu�̎擾
				D3DXVECTOR3 BulletMove = m_pBoundBullet[nCnt]->GetMove();				 //�e�̑��x�̎擾

				m_pBoundBullet[nCnt]->SetPos(BulletPos + BulletMove);					 //�e�̈ʒu�̐ݒ�
			}
		}
	}
	//
	//==========================================================================================
}


//���v�^�G�̒e�����X�|�[�����鏈��
void CEnemyClock::RespawnNeedle(void)
{
	D3DXVECTOR3 pos = GetPos();			//�ʒu�̎擾

	if (m_pBoundBullet[0] == nullptr && m_pBoundBullet[1] == nullptr)
	{//�e�̃|�C���^��null��������

	 //�e�𐶐�����
		m_pBoundBullet[0] = CClockNeedle::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(20.0f, 20.0f));

		m_pBoundBullet[0]->SetStartingRot(-D3DX_PI * 0.5f);							//��]�p�x�̏����l
		m_pBoundBullet[0]->SetRotation(-D3DX_PI * 0.001f);							//1�t���[���̉�]�p�x
		m_pBoundBullet[0]->SetRevolution(pos, -D3DX_PI * 0.001f, 15.0f);			//1�t���[���̌��]�p�x
		m_pBoundBullet[0]->SetSize(D3DXVECTOR2(1.0f, 1.0f));						//�����[�X����Ă��邩�ǂ���
		m_bBound[0] = true;

		m_pBoundBullet[1] = CClockNeedle::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(30.0f, 30.0f));

		m_pBoundBullet[1]->SetStartingRot(-D3DX_PI * 0.5f);							//��]�p�x�̏����l
		m_pBoundBullet[1]->SetRotation(-D3DX_PI * 0.03f);							//1�t���[���̉�]�p�x
		m_pBoundBullet[1]->SetRevolution(pos, -D3DX_PI * 0.03f, 20.0f);				//1�t���[���̌��]�p�x
		m_pBoundBullet[1]->SetSize(D3DXVECTOR2(2.0f, 2.0f));						//�����[�X����Ă��邩�ǂ���
		m_bBound[1] = true;
	}
}