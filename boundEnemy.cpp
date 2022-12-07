////=============================================================================
////
//// boundEnemy.cpp
//// Author : Ricci Alex
////
////=============================================================================
//
////�C���N���[�h�t�@�C��
//#include "boundEnemy.h"
//#include "clockNeedle.h"
//#include "player.h"
//
////�R���X�g���N�^
//CBoundEnemy::CBoundEnemy()
//{
//	//�����o�[�ϐ����N���A����
//	m_pBoundObject[MAX_BOUND_OBJECT] = {};
//	m_nCntBoundAnimation = 0;
//
//	for (int nCnt = 0; nCnt < MAX_BOUND_OBJECT; nCnt++)
//	{
//		m_bBound[nCnt] = false;
//	}
//}
//
////�f�X�g���N�^
//CBoundEnemy::~CBoundEnemy()
//{
//
//}
//
////����������
//HRESULT CBoundEnemy::Init(void)
//{
//	//��{�N���X�̏���������
//	if (FAILED(CEnemy::Init()))
//	{
//		return -1;
//	}
//
//	//�����o�[�ϐ��̏�����
//	m_nCntBoundAnimation = 0;
//
//	for (int nCnt = 0; nCnt < MAX_BOUND_OBJECT; nCnt++)
//	{
//		if (m_pBoundObject[nCnt] != nullptr)
//		{//null�`�F�b�N
//			m_pBoundObject[MAX_BOUND_OBJECT]->Release();
//			m_pBoundObject[MAX_BOUND_OBJECT] = nullptr;
//			m_bBound[nCnt] = false;
//		}
//	}
//
//	return S_OK;
//}
//
////�I������
//void CBoundEnemy::Uninit(void)
//{
//	for (int nCnt = 0; nCnt < MAX_BOUND_OBJECT; nCnt++)
//	{
//		if (m_pBoundObject[nCnt] != nullptr)
//		{//null�`�F�b�N
//			m_pBoundObject[MAX_BOUND_OBJECT]->Release();
//			m_pBoundObject[MAX_BOUND_OBJECT] = nullptr;
//		}
//	}
//
//	//��{�N���X�̏I������
//	CEnemy::Uninit();
//}
//
////�X�V����
//void CBoundEnemy::Update(void)
//{
//	UpdateClock();
//
//	//��{�N���X�̍X�V����
//	CObject_2D::Update();
//}
//
////�`�揈��
//void CBoundEnemy::Draw(void)
//{
//	//��{�N���X�̕`�揈��
//	CEnemy::Draw();
//}
//
//
////��������
//CBoundEnemy* CBoundEnemy::Create(CObject::EnemyType type, D3DXVECTOR3 pos)
//{
//	CBoundEnemy* pEnemy = new CBoundEnemy;			//�G�𐶐�����
//
//	if (pEnemy != nullptr)
//	{//null�`�F�b�N
//
//		 //����������
//		if (FAILED(pEnemy->Init()))
//		{//�������ł��Ȃ�������
//			delete pEnemy;				//���������������
//			return nullptr;				//null��Ԃ�
//		}
//
//		pEnemy->SetObjType(CObject::OBJTYPE_ENEMY);					//�I�u�W�F�N�g�̎�ނ�ݒ肷��
//		pEnemy->SetSubtype(type);									//�G�̎�ނ̐ݒ�
//
//		switch (type)
//		{
//		case CObject::ENEMYTYPE_BOUND_CLOCK:
//
//			pEnemy->SetPos(pos);											//�ʒu�̐ݒ�
//			pEnemy->SetMaxSpeed(4.0f);										//�ő呬�x�̐ݒ�
//			pEnemy->SetStartingRot(D3DX_PI * 0.5f);							//��]�p�x�̏����l
//			pEnemy->m_fAngleMove = 0.0f;									//1�t���[���̉�]�p�x
//			pEnemy->m_nCntMove = 0;											//�ړ��J�E���^
//			pEnemy->m_nShootDelay = 0;										//�e�̔����J�E���^�[
//			pEnemy->SetTextureParameter(1, 1, 1, INT_MAX);					//�e�N�X�`���p�����[�^�̐ݒ�
//			pEnemy->SetSize(D3DXVECTOR2(75.0f, 75.0f));						//�T�C�Y�̐ݒ�
//																			
//			pEnemy->SetMove(D3DXVECTOR3(-2.0f, 0.0f, 0.0f));				//���x�̐ݒ�
//			pEnemy->SetAcceleration(D3DXVECTOR3(0.0f, 0.0f, 0.0f));			//�����̐ݒ�
//
//
//			pEnemy->SetTexture(TextureClock);								//�e�N�X�`���̐ݒ�
//
//			//�K�w�\���̒e�̐�������
//
//			pEnemy->m_pBoundObject[0] = CClockNeedle::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
//				D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(20.0f, 20.0f));
//
//			pEnemy->m_pBoundObject[0]->SetStartingRot(-D3DX_PI * 0.5f);						//��]�p�x�̏����l
//			pEnemy->m_pBoundObject[0]->SetRotation(-D3DX_PI * 0.001f);						//1�t���[���̉�]�p�x
//			pEnemy->m_pBoundObject[0]->SetRevolution(pos, -D3DX_PI * 0.001f, 15.0f);		//1�t���[���̌��]�p�x
//			pEnemy->m_bBound[0] = true;														//�����[�X����Ă��邩�ǂ���
//
//			pEnemy->m_pBoundObject[1] = CClockNeedle::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
//				D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(30.0f, 30.0f));
//
//			pEnemy->m_pBoundObject[1]->SetStartingRot(-D3DX_PI * 0.5f);						//��]�p�x�̏����l
//			pEnemy->m_pBoundObject[1]->SetRotation(-D3DX_PI * 0.03f);						//1�t���[���̉�]�p�x
//			pEnemy->m_pBoundObject[1]->SetRevolution(pos, -D3DX_PI * 0.03f, 20.0f);			//1�t���[���̌��]�p�x
//			pEnemy->m_bBound[1] = true;														//�����[�X����Ă��邩�ǂ���
//
//			break;
//
//		default:
//			break;
//		}
//	}
//
//	return pEnemy;					//�G��Ԃ�
//}
//
//
////���v�^�̓G�̍X�V����
//void CBoundEnemy::UpdateClock(void)
//{
//	D3DXVECTOR3 pos = GetPos();						//�ʒu�̎擾����
//	D3DXVECTOR3 dir;								//����
//
//	if (m_nCntMove <= 0)
//	{
//		DWORD dwExecLastTime = timeGetTime();		//���݂̎��Ԃ��擾
//
//		srand(dwExecLastTime);						
//
//		m_nCntMove = (rand() % 91) + 30;			//���x�̌������ς��܂ł̃t���[�������v�Z����
//		float fX, fY;
//
//		fX = (float)((rand() % 24001) - 12000);		//���x��X�R���|�l���g
//
//		fY = (float)((rand() % 15001) - 7500);		//���x��Y�R���|�l���g
//
//		dir.x = fX;
//		dir.y = fY;
//		dir.z = 0.0f;
//
//		D3DXVec3Normalize(&dir, &dir);				//���K������
//
//		dir.x *= 3.0f;								//���x���v�Z����
//		dir.y *= 3.0f;								//���x���v�Z����
//	}
//	else
//	{
//		dir = GetMove();							//���x�̎擾
//	}
//
//	//=========================================================================================
//	//								��ʂ��o�Ȃ��悤��
//	if (pos.x >= SCREEN_WIDTH * 0.9f)
//	{
//		pos.x = SCREEN_WIDTH * 0.9f;
//		dir.x *= -1.0f;
//	}
//	if (pos.x <= SCREEN_WIDTH * 0.1f)
//	{
//		pos.x = SCREEN_WIDTH * 0.1f;
//		dir.x *= -1.0f;
//	}
//	if (pos.y >= SCREEN_HEIGHT * 0.9f)
//	{
//		pos.y = SCREEN_HEIGHT * 0.9f;
//		dir.y *= -1.0f;
//	}
//	if (pos.y <= SCREEN_HEIGHT * 0.1f)
//	{
//		pos.y = SCREEN_HEIGHT * 0.1f;
//		dir.y *= -1.0f;
//	}
//	//
//	//=========================================================================================
//
//	SetMove(dir);				//���x�̐ݒ�
//	pos += dir;					//�ʒu�̍X�V����
//	SetPos(pos);				//�ʒu�̐ݒ�
//								
//	m_nCntMove--;				//�ړ��J�E���^�[�̍X�V
//
//	//==========================================================================================
//	//								�e����������
//	if (m_nShootDelay > 0)
//	{
//		m_nShootDelay--;								//�J�E���^�[�̍X�V
//
//		if (m_nShootDelay == 60)
//		{
//			RespawnNeedle();							//�V�����e�𐶐�����
//		}
//		else if (m_nShootDelay < 60 && m_nShootDelay > 0)
//		{
//			//�T�C�Y�̍X�V����
//			D3DXVECTOR2 NeedleSize = m_pBoundObject[0]->GetSize();								
//			float fD = 20.0f / 60.0f;
//			m_pBoundObject[0]->SetSize(D3DXVECTOR2(NeedleSize.x + fD, NeedleSize.y + fD));
//			NeedleSize = m_pBoundObject[1]->GetSize();
//			fD = 30.0f / 60.0f;
//			m_pBoundObject[1]->SetSize(D3DXVECTOR2(NeedleSize.x + fD, NeedleSize.y + fD));
//		}
//		if (m_nShootDelay <= 0)
//		{
//			m_nShootDelay = 0;
//		}
//	}
//	//
//	//==========================================================================================
//	//==========================================================================================
//	//
//	for (int nCnt = 0; nCnt < 2; nCnt++)
//	{
//		if (m_pBoundObject[nCnt] != nullptr)
//		{
//			float fAngSpeed = m_pBoundObject[nCnt]->GetAngularSpeed();				//��]���x�̎擾
//			D3DXVECTOR2 size = m_pBoundObject[nCnt]->GetSize();						//�T�C�Y�̎擾
//
//			if (m_bBound[nCnt] == true)
//			{
//				//��]���x�̍X�V
//				m_pBoundObject[nCnt]->AddAngularSpeed(-D3DX_PI * 0.001f);
//
//				if (fAngSpeed <= -D3DX_PI * 0.25f)
//				{
//					m_pBoundObject[nCnt]->SetRotation(0.0f);				//��]���~�܂�
//					CPlayer* pPlayer = CObject::GetPlayer();				//�v���C���[�����擾����
//					D3DXVECTOR3 PlayerPos = pPlayer->GetPos();				//�v���C���[�̈ʒu���擾����
//					D3DXVECTOR3 unit = D3DXVECTOR3(1.0f, 0.0f, 0.0f);		//�v�Z�p�̃��F�N�g��
//					float dot = 0.0f;										//���ς��v�Z�p�̕ϐ�
//																			
//					dir = PlayerPos - pos;									//�e�̌����̌v�Z
//					D3DXVec3Normalize(&dir, &dir);							//�����̐��K��
//					dot = D3DXVec3Dot(&dir, &unit);							//���ς��v�Z����
//					float fAngle = acosf(dot);								//�v���C���[�ƓG�̒��̊p�x
//
//					if (PlayerPos.y > pos.y)
//					{
//						fAngle *= -1.0f;
//					}
//
//					m_pBoundObject[nCnt]->SetStartingRot(fAngle);									//�e�̉�]�p�x�̐ݒ�
//					m_pBoundObject[nCnt]->SetMove(D3DXVECTOR3(dir.x * 10.0f, dir.y * 10.0f, 0.0f));	//�e�̑��x�̐ݒ�
//					m_pBoundObject[nCnt]->SetRevolution(pos, 0.0f, 0.0f);							//���]���~�߂�
//					m_bBound[nCnt] = false;															//�e�������[�X����
//					m_pBoundObject[nCnt] = nullptr;													//�|�C���^��null�ɂ���
//					m_nShootDelay = 240;															//�J�E���^�[�̐ݒ�
//				}
//				else
//				{
//					fAngSpeed = m_pBoundObject[nCnt]->GetAngularSpeed();							//��]���x�̍X�V
//					m_pBoundObject[nCnt]->SetRevolution(pos, fAngSpeed, size.x * 0.5f);				//���]�p�����[�^�̍X�V
//				}
//			}
//			else
//			{
//				D3DXVECTOR3 BulletPos = m_pBoundObject[nCnt]->GetPos();					 //�e�̈ʒu�̎擾
//				D3DXVECTOR3 BulletMove = m_pBoundObject[nCnt]->GetMove();				 //�e�̑��x�̎擾
//																						 
//				m_pBoundObject[nCnt]->SetPos(BulletPos + BulletMove);					 //�e�̈ʒu�̐ݒ�
//			}
//		}
//	}
//	//
//	//==========================================================================================
//}
//
//
////���v�^�G�̒e�����X�|�[�����鏈��
//void CBoundEnemy::RespawnNeedle(void)
//{
//	D3DXVECTOR3 pos = GetPos();			//�ʒu�̎擾
//
//	if (m_pBoundObject[0] == nullptr && m_pBoundObject[1] == nullptr)
//	{//�e�̃|�C���^��null��������
//
//		//�e�𐶐�����
//		m_pBoundObject[0] = CClockNeedle::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
//			D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(20.0f, 20.0f));
//
//		m_pBoundObject[0]->SetStartingRot(-D3DX_PI * 0.5f);							//��]�p�x�̏����l
//		m_pBoundObject[0]->SetRotation(-D3DX_PI * 0.001f);							//1�t���[���̉�]�p�x
//		m_pBoundObject[0]->SetRevolution(pos, -D3DX_PI * 0.001f, 15.0f);			//1�t���[���̌��]�p�x
//		m_pBoundObject[0]->SetSize(D3DXVECTOR2(1.0f, 1.0f));						//�����[�X����Ă��邩�ǂ���
//		m_bBound[0] = true;
//
//		m_pBoundObject[1] = CClockNeedle::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
//			D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(30.0f, 30.0f));
//
//		m_pBoundObject[1]->SetStartingRot(-D3DX_PI * 0.5f);							//��]�p�x�̏����l
//		m_pBoundObject[1]->SetRotation(-D3DX_PI * 0.03f);							//1�t���[���̉�]�p�x
//		m_pBoundObject[1]->SetRevolution(pos, -D3DX_PI * 0.03f, 20.0f);				//1�t���[���̌��]�p�x
//		m_pBoundObject[1]->SetSize(D3DXVECTOR2(2.0f, 2.0f));						//�����[�X����Ă��邩�ǂ���
//		m_bBound[1] = true;
//	}
//}