//=============================================================================
//
// Thanatos.h
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "Thanatos.h"
#include "squareHitbox.h"
#include "candle.h"
#include "player.h"
#include "scythe.h"
#include "enemyLife.h"
#include "application.h"
#include "sound.h"

//�R���X�g���N�^
CThanatos::CThanatos()
{
	//�����o�[�ϐ����N���A����
	m_nTargetLife = 0;
	m_nLitCandle = 0;
	m_nCntState = 0;
	m_state = state_Spawn;
	m_bEnd = false;

	for (int nCnt = 0; nCnt < Max_Candle; nCnt++)
	{
		m_pCandle[nCnt] = nullptr;
	}

	m_pLife = nullptr;

	m_pHitbox = nullptr;
}

//�f�X�g���N�^
CThanatos::~CThanatos()
{

}

//����������
HRESULT CThanatos::Init(void)
{
	//�����o�[�ϐ�������������
	if (FAILED(CEnemy::Init()))
	{//��{�N���X�̏���������
		return -1;
	}

	m_nTargetLife = 4000;
	m_nLitCandle = 0;
	m_nCntState = 0;
	m_state = state_Spawn;
	m_bEnd = false;

	for (int nCnt = 0; nCnt < Max_Candle; nCnt++)
	{
		m_pCandle[nCnt] = nullptr;
	}

	m_pLife = nullptr;

	m_pHitbox = nullptr;

	return S_OK;
}

//�I������
void CThanatos::Uninit(void)
{
	//���E�\�N�̔j������
	for (int nCnt = 0; nCnt < Max_Candle; nCnt++)
	{
		if (m_pCandle[nCnt] != nullptr)
		{//null�`�F�b�N
			m_pCandle[nCnt]->Release();			//���������������
			m_pCandle[nCnt] = nullptr;			//null�ɂ���
		}
	}

	//�q�b�g�{�b�N�X�̔j������
	if (m_pHitbox != nullptr)
	{//null�`�F�b�N
		m_pHitbox->Release();					//���������������			
		m_pHitbox = nullptr;					//null�ɂ���
	}

	//�̗�UI�̔j������
	if (m_pLife != nullptr)
	{//null�`�F�b�N
		m_pLife->Release();						//���������������
		m_pLife = nullptr;						//null�ɂ���
	}

	//��{�N���X�̏I������
	CEnemy::Uninit();
}

//�X�V����
void CThanatos::Update(void)
{
	switch (m_state)
	{//��Ԃɂ���čX�V����
	case CThanatos::state_Spawn:

	{//�X�|�[�����
		D3DXCOLOR col = GetColor();		//�F�̎擾	

		col.a += 0.005f;				//���l�̍X�V

		if (col.a >= 1.0f)
		{//���l��1�ȏ�ɂȂ�����
			col.a = 1.0f;				//1.0f�ɖ߂�
			m_state = state_Hide;		//��Ԃ��X�V����
		}

		SetColor(col);					//�F�̐ݒ�
	}

		break;

	case CThanatos::state_Normal:
		//���ʏ��
		break;

	case CThanatos::state_Hide:

	{//�B�����
		D3DXCOLOR col = GetColor();		//�F�̎擾

		col.a -= 0.005f;				//���l�̍X�V

		if (col.a <= 0.0f)
		{//���l��0�ȉ��ɂȂ�����
			col.a = 0.0f;				//0.0f�ɖ߂�
			m_state = state_ShowEyes;	//��Ԃ��X�V����
			SetAnimPattern(1);			//�A�j���V�����p�^�[���̐ݒ�
		}

		SetColor(col);					//�F�̐ݒ�
	}

		break;

	case CThanatos::state_ShowEyes:

	{//�ڂ���������
		D3DXCOLOR col = GetColor();		//�F�̎擾

		col.a += 0.005f;				//���l���X�V����

		if (col.a >= 1.0f)
		{//���l��1.0f�ȏ�ɂȂ�����
			col.a = 1.0f;				//1.0f�ɖ߂�
			m_state = state_Hidden;		//��Ԃ��X�V����
			m_nShootDelay = 30;			//�J�E���^�[�̐ݒ�
		}

		SetColor(col);					//�F�̐ݒ�
	}

	break;

	case CThanatos::state_Hidden:

	{//�B�������
		m_nShootDelay--;				//�J�E���^�[�̍X�V

		//�ړI�̍��W���v�Z����
		D3DXVECTOR3 target = CPlayer::GetPlayer()->GetPos();		
		target -= GetPos();
		D3DXVec3Normalize(&target, &target);
		target.x *= 0.25f;
		target.y *= 0.25f;

		SetMove(target);				//���x�̐ݒ�


		if (m_nShootDelay <= 0)
		{//�J�E���^�[��0�ȉ��ɂȂ�����
			m_nShootDelay = 90;				//�J�E���^�[�̐ݒ�

			//�e�̈ړ��ʂ̌v�Z
			D3DXVec3Normalize(&target, &target);		
			target.x *= 4.0f;
			target.y *= 4.0f;

			//�e�̐���
			CScythe* pBullet = CScythe::Create(GetPos(), target);

			if (GetLife() <= 4000)
			{//�̗͂�4000�ȉ���������	
				int nMax = 1;			//��񂾂��J��Ԃ�

				if (GetLife() <= 2000)
				{//�̗͂�2000�ȉ���������
					nMax = 2;			//���J��Ԃ�
				}

				for (int nCnt = 0; nCnt < nMax; nCnt++)
				{
					//�V�����e�̑��x�̌v�Z
					D3DXVec3Normalize(&target, &target);

					D3DXVECTOR3 speed = target;
					speed.x *= (float)random(2000, 5000) * 0.001f;
					speed.y = (float)random(2000, 4000) * -0.001f;

					//�e�̐���
					pBullet = CScythe::Create(GetPos(), speed);

					pBullet->SetAcceleration(D3DXVECTOR3(0.0f, 0.05f, 0.0f));		//�����̐ݒ�
					pBullet->AddAngularSpeed(D3DX_PI * 0.05f);						//��]������

					//�V�����e�̈ړ��ʂ̌v�Z
					if (target.x >= target.y)
					{
						target.x += target.x;
					}
					else
					{
						target.y += target.y;
					}

					D3DXVec3Normalize(&target, &target);
					target.x *= 4.0f;
					target.y *= 4.0f;

					//�e�̐���
					pBullet = CScythe::Create(GetPos(), target);
				}
			}

			//�T�E���h���Đ�����
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_SCYTHE);
		}
		
		if (m_nLitCandle >= 4)
		{//�S���̃��E�\�N��������

			m_state = state_Vulnerable;			//��Ԃ̍X�V
			SetAnimPattern(0);					//�A�j���V�����p�^�[���̐ݒ�

			//�q�b�g�{�b�N�X�̐���
			if (m_pHitbox == nullptr)
			{//null��������
				//�q�b�g�{�b�N�X�̃T�C�Y���v�Z����
				D3DXVECTOR2 size = GetSize();
				size.x *= 0.7f;
				size.y *= 0.9f;

				//�q�b�g�{�b�N�X�𐶐�����
				m_pHitbox = CSquareHitbox::Create(GetPos(), size, CHitbox::Type_Enemy);
			}
		}
	}

	break;

	case CThanatos::state_Vulnerable:

	{//�_���[�W���󂯂���

		m_nShootDelay -= 2;				//���ʂ��2�{�����e������

		SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));			//�ړ���

		if (m_nShootDelay <= 0)
		{//�J�E���^�[��0�ȉ��ɂȂ�����
			m_nShootDelay = 90;				//�J�E���^�̐ݒ�

			//�ړI�̈ʒu���v�Z����
			D3DXVECTOR3 target = CPlayer::GetPlayer()->GetPos();
			target -= GetPos();
			D3DXVec3Normalize(&target, &target);
			target.x *= 4.0f;
			target.y *= 4.0f;

			//�e�̐���
			CScythe* pBullet = CScythe::Create(GetPos(), target);

			if (GetLife() <= 4000)
			{//�̗͂�4000�ȉ���������
				int nMax = 1;

				if (GetLife() <= 2000)
				{//�̗͂�2000�ȉ���������
					nMax = 2;
				}

				for (int nCnt = 0; nCnt < nMax; nCnt++)
				{
					//�V�����e�̈ړ��ʂ̌v�Z
					D3DXVec3Normalize(&target, &target);

					D3DXVECTOR3 speed = target;
					speed.x *= (float)random(2000, 5000) * 0.001f;
					speed.y = (float)random(2000, 4000) * -0.001f;

					//�e�̐���
					pBullet = CScythe::Create(GetPos(), speed);

					pBullet->SetAcceleration(D3DXVECTOR3(0.0f, 0.05f, 0.0f));			//�����̐ݒ�
					pBullet->AddAngularSpeed(D3DX_PI * 0.05f);							//��]������

					//�V�����e�̑��x�̌v�Z
					if (target.x >= target.y)
					{
						target.x += target.x;
					}
					else
					{
						target.y += target.y;
					}

					D3DXVec3Normalize(&target, &target);
					target.x *= 4.0f;
					target.y *= 4.0f;

					//�e�̐���
					pBullet = CScythe::Create(GetPos(), target);
				}
			}

			//�T�E���h���Đ�����
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_SCYTHE);
		}

		if (m_pHitbox->GetHitState())
		{//����������
			m_pHitbox->SetHitState(false);						//�����Ă��Ȃ���Ԃɂ���
			int nLife = GetLife();								//�̗͂̎擾
			int nDamage = CPlayer::GetPlayer()->GetAttack();	//�󂯂��_���[�W�̎擾

			nLife -= nDamage;			//�̗͂̍X�V

			//UI�̍X�V
			if (m_pLife != nullptr)
			{//null�`�F�b�N
				m_pLife->SubtractLife(nDamage);				//�̗�UI�̍X�V
			}

			if (nLife <= 0)
			{//�̗͂�0�ȉ��ɂȂ�����
				m_state = state_Death;			//���S��Ԃɂ���
				m_pHitbox->Release();			//�q�b�g�{�b�N�X��j������
				m_pHitbox = nullptr;			//null�ɂ���
			}
			else if(nLife <= m_nTargetLife)
			{//�ړI�̗͈̑ȉ��ɂȂ�����
				nLife = m_nTargetLife;		//�̗͂̐ݒ�
				m_nTargetLife -= 2000;		//���̖ړI�̗̑͂��v�Z����
				SetLife(nLife);				//�̗͂̐ݒ�

				for (int nCnt = 0; nCnt < Max_Candle; nCnt++)
				{//���E�\�N������
					if (m_pCandle[nCnt])
					{//null�`�F�b�N
						m_pCandle[nCnt]->Unlit();
					}
				}

				m_pHitbox->Release();			//�q�b�g�{�b�N�X��j������
				m_pHitbox = nullptr;			//null�ɂ���
				m_nLitCandle = 0;				//�������E�\�N�̐���0�ɖ߂�
				m_state = state_Hide;			//��Ԃ̍X�V
			}
			else
			{
				SetLife(nLife);					//�̗͂̐ݒ�
			}
		}
	}

	break;

	case CThanatos::state_Death:

	{//���S���
		D3DXCOLOR col = GetColor();			//�F�̎擾

		col.a -= 0.005f;					//���l�̍X�V

		if (col.a <= 0.0f)
		{//���l��0�ȉ��ɂȂ�����
			col.a = 0.0f;					//���l��0�ȉ��ɖ߂�

			m_bEnd = true;					//�I�������Ԃɂ���
		}

		SetColor(col);						//�F�̐ݒ�

		for (int nCnt = 0; nCnt < Max_Candle; nCnt++)
		{//���E�\�N�̔j������
			m_pCandle[nCnt]->Despawn();
		}
	}

	break;
	
	default:
		break;
	}

	
	if (m_state != state_Spawn && m_state != state_Death)
	{//�X�|�[���Ǝ��S��ԈȊO

		//�v���C���[�̈ʒu�ɂ���ăe�N�X�`���𔽓]���܂�
		D3DXVECTOR3 PlayerPos = CPlayer::GetPlayer()->GetPos();
		D3DXVECTOR3 pos = GetPos();

		if (PlayerPos.x < pos.x && GetFlipX() || PlayerPos.x > pos.x && !GetFlipX())
		{
			FlipX();
		}

		//�㉺�̈ړ�������
		pos.y += 0.20f * sinf(m_fAngleMove);
		m_fAngleMove += D3DX_PI * 0.015f;

		SetPos(pos);				//�ʒu�̐ݒ�
	}
	
	//�q�b�g�{�b�N�X�̍X�V����
	if (m_pHitbox != nullptr)
	{//null�`�F�b�N
		m_pHitbox->SetPos(GetPos());		//�ʒu�̐ݒ�
	}

	//��{�N���X�̍X�V����
	CObject_2D::Update();
}

//�`�揈��
void CThanatos::Draw(void)
{
	CObject_2D::Draw();
}

//�I��������ǂ����̎擾����
const bool CThanatos::GetEnd(void)
{
	return m_bEnd;
}

//�w�i�ւ̃|�C���^�̐ݒ菈��
void CThanatos::SetBgPointer(CBg* pPointer)
{
	m_pBg = pPointer;

	for (int nCnt = 0; nCnt < Max_Candle; nCnt++)
	{
		m_pCandle[nCnt]->SetBgPointer(m_pBg);
	}
}

//�������E�\�N�̒ǉ�����
void CThanatos::AddLitCandle(void)
{
	m_nLitCandle++;
}





//��������
CThanatos* CThanatos::Create(void)
{
	CThanatos* pEnemy = new CThanatos;			//�C���X�^���X�𐶐�����

	if (FAILED(pEnemy->Init()))
	{//����������
		return nullptr;
	}

	pEnemy->SetPos(D3DXVECTOR3(900.0f, 250.0f, 0.0f));				//�ʒu�̐ݒ�
	pEnemy->SetStartingRot(D3DX_PI * 0.5f);							//�����̏����l�̐ݒ�
	pEnemy->SetTexture(CObject::TextureThanatos);					//�e�N�X�`���̐ݒ�
	pEnemy->SetTextureParameter(1, 2, 1, INT_MAX);					//�e�N�X�`���p�����[�^�̐ݒ�
	pEnemy->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));			//�F�̐ݒ�
	pEnemy->SetSize(D3DXVECTOR2(100.0f, 182.4f));					//�T�C�Y�̐ݒ�
	pEnemy->SetLife(6000);											//�̗͂̐ݒ�

	//���E�\�N�̐�������
	pEnemy->m_pCandle[0] = CCandle::Create(D3DXVECTOR3(160.0f, 100.0f, 0.0f));
	pEnemy->m_pCandle[1] = CCandle::Create(D3DXVECTOR3(160.0f, (float)SCREEN_HEIGHT - 100.0f, 0.0f));
	pEnemy->m_pCandle[2] = CCandle::Create(D3DXVECTOR3((float)SCREEN_WIDTH - 152.5f, 100.0f, 0.0f));
	pEnemy->m_pCandle[3] = CCandle::Create(D3DXVECTOR3((float)SCREEN_WIDTH - 152.5f, (float)SCREEN_HEIGHT - 100.0f, 0.0f));

	for (int nCnt = 0; nCnt < CThanatos::Max_Candle; nCnt++)
	{//���E�\�N�̐e�q�֌W�����
		pEnemy->m_pCandle[nCnt]->SetParent(pEnemy);
	}

	//�̗�UI�̐���
	pEnemy->m_pLife = CEnemyLife::Create(D3DXVECTOR3(800.0f, 40.0f, 0.0f), D3DXCOLOR(8.0f, 0.8f, 0.8f, 0.5f), 6000, "thanatos");
	
	return pEnemy;					//���������C���X�^���X��Ԃ�
}