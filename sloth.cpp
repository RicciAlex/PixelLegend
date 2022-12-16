//=============================================================================
//
// sloth.cpp
// Author : Ricci Alex
//
//=============================================================================

//�C���N���[�h�t�@�C��
#include "sloth.h"
#include "application.h"
#include "sound.h"
#include "tear.h"
#include "enemyCloud.h"
#include "Zbullet.h"
#include "player.h"
#include "squareHitbox.h"
#include "enemyLife.h"

//�R���X�g���N�^
CSloth::CSloth()
{
	//�����o�[�ϐ����N���A����
	m_bEnd = false;
	m_nCntState = 0;
	m_fYCoord = 0.0f;
	m_state = state_Spawn;
	m_nCntDmg = 0;
	m_nCntSpawn = 0;
	m_nCntSound = 0;
	m_nSoundDelay = 0;
	m_nChange = 0;
	m_nCntAnim = 0;
	m_HitboxRelativePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pHitbox = nullptr;
	m_pLife = nullptr;
}

//�f�X�g���N�^
CSloth::~CSloth()
{

}

//����������
HRESULT CSloth::Init(void)
{
	//��{�N���X�̏�����
	if (FAILED(CEnemy::Init()))
	{
		return -1;
	}

	//�����o�[�ϐ��̏�����
	m_bEnd = false;
	SetLife(20000);
	m_state = state_Spawn;
	m_nCntState = 30;
	m_nCntDmg = 0;
	m_nCntSpawn = 0;
	m_nCntSound = 0;
	m_nSoundDelay = 0;
	m_nChange = 0;
	m_nCntAnim = 0;
	m_HitboxRelativePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pHitbox = nullptr;
	m_pLife = nullptr;

	return S_OK;
}

//�I������
void CSloth::Uninit(void)
{
	//�q�b�g�{�b�N�X�̔j������
	if (m_pHitbox != nullptr)
	{//null�`�F�b�N
		m_pHitbox->Release();			//���������������
		m_pHitbox = nullptr;			//null�ɂ���
	}

	//�̗�UI�̔j������
	if (m_pLife != nullptr)
	{//null�`�F�b�N
		m_pLife->Release();				//���������������
		m_pLife = nullptr;				//null�ɂ���
	}

	//��{�N���X�̏I������
	CEnemy::Uninit();
}

//�X�V����
void CSloth::Update(void)
{
	SlothBehavior();					//�X�V����

	//�q�b�g�{�b�N�X�̍X�V����
	if (m_pHitbox != nullptr)
	{//null�`�F�b�N

		m_pHitbox->SetPos(GetPos() + m_HitboxRelativePos);		//�q�b�g�{�b�N�X�̈ʒu�̐ݒ�

		if (m_nCntDmg <= 0)
		{//���G��Ԃł͂Ȃ�������

			if (m_pHitbox->GetHitState())
			{//����������Ԃ�������

				m_pHitbox->SetHitState(false);						//�����Ă��Ȃ���Ԃɖ߂�
				int nLife = GetLife();								//�̗͂̎擾
				int nDamage = CPlayer::GetPlayer()->GetAttack();	//�v���C���[�̍U���͂̎擾
				nLife -= nDamage;									//�̗͂̍X�V
				m_nCntDmg = 20;										//���G��ԃJ�E���^�[��ݒ肷��

				if (nLife <= 0)
				{//�̗͂�0�ȉ��ɂȂ�����

					SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));	//���x�̐ݒ�
					m_nSoundDelay = 45;						//�T�E���h�f�B���C�̍X�V
					m_state = state_Death;					//��Ԃ̍X�V
					m_pHitbox->Release();					//�q�b�g�{�b�N�X�̔j��
					m_pHitbox = nullptr;					//�q�b�g�{�b�N�X�ւ̃|�C���^��null�ɂ���
					m_nChange++;							//�J�E���^�[���C���N�������g����
					SetAnimPattern(14);						//�A�j���V�����p�^�[���̐ݒ�
					return;
				}

				if (nLife <= 15000 && m_nChange == 0)
				{//�̗͂�15000�ȉ�7500��菬����������A�D�F�e�N�X�`���̃A�j���V�����p�^�[���ɐݒ肷��

					SetTextureParameter(1, 6, 3, INT_MAX);		//�e�N�X�`���p�����[�^�̐ݒ�
					SetAnimPattern(6);							//�A�j���V�����p�^�[���̐ݒ�
					m_nChange++;								//�J�E���^�[���C���N�������g����

					CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_THUNDER);			//���̃T�E���h���Đ�����
				}
				else if (nLife <= 7500 && m_nChange == 1)
				{//�̗͂�7500�ȉ���������A�����e�N�X�`���̃A�j���V�����p�^�[���ɐݒ肷��

					SetAnimPattern(12);				//�A�j���V�����p�^�[���̐ݒ�
					m_nChange++;					//�J�E���^�[���C���N�������g����

					CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_THUNDER);			//���̃T�E���h���Đ�����
				}

				//�̗�UI�̍X�V
				if (m_pLife != nullptr)
				{//null�`�F�b�N
					m_pLife->SubtractLife(nDamage);			//UI�̍X�V
				}

				SetLife(nLife);				//�̗͂̍X�V
			}
		}
		else
		{
			m_nCntDmg--;					//���G��ԃJ�E���^�[���f�N�������g����
		}
	}

	if (m_nChange == 1)
	{
		m_nCntAnim++;			//�A�j���[�V�����J�E���^�[�̍X�V

		if (m_nCntAnim >= 30)
		{//30�t���[�����ƃe�N�X�`�����X�V����

			m_nCntAnim = 0;		//�A�j���[�V�����J�E���^�[��0�ɖ߂�
			
			if (GetPresentAnimPattern() == 6)
			{
				SetAnimPattern(7);
			}
			else
			{
				SetAnimPattern(6);
			}
		}
	}
	else if (m_nChange == 2)
	{
		m_nCntAnim++;			//�A�j���[�V�����J�E���^�[�̍X�V

		if (m_nCntAnim >= 30)
		{//30�t���[�����ƃe�N�X�`�����X�V����

			m_nCntAnim = 0;		//�A�j���[�V�����J�E���^�[��0�ɖ߂�

			if (GetPresentAnimPattern() == 12)
			{
				SetAnimPattern(13);
			}
			else
			{
				SetAnimPattern(12);
			}
		}
	}
	else if (m_nChange == 3)
	{
		m_nCntAnim++;			//�A�j���[�V�����J�E���^�[�̍X�V

		if (m_nCntAnim >= 30)
		{//30�t���[�����ƃe�N�X�`�����X�V����

			m_nCntAnim = 0;		//�A�j���[�V�����J�E���^�[��0�ɖ߂�

			if (GetPresentAnimPattern() == 14)
			{
				SetAnimPattern(15);
			}
			else
			{
				SetAnimPattern(14);
			}
		}
	}

	CObject_2D::Update();				//��{�N���X�̍X�V����
}

//�`�揈��
void CSloth::Draw(void)
{
	//��{�N���X�̕`�揈��
	CEnemy::Draw();
}

//�I��������ǂ����̎擾����
const bool CSloth::GetEnd(void)
{
	return m_bEnd;
}


//==================================================================================================
//										�ÓI�֐�
//==================================================================================================

//��������
CSloth* CSloth::Create(void)
{
	CSloth* pBoss = new CSloth;					//���������m�ۂ���

	//����������
	if (FAILED(pBoss->Init()))
	{
		return nullptr;
	}

	pBoss->SetPos(D3DXVECTOR3((float)SCREEN_WIDTH * 0.75f, (float)SCREEN_HEIGHT * 0.25f, 0.0f));	//�ʒu�̐ݒ�
	pBoss->SetSize(D3DXVECTOR2(180.0f, 104.0f));													//�T�C�Y�̐ݒ�
	pBoss->SetStartingRot(D3DX_PI * 0.5f);															//��]�p�x�̐ݒ�
	pBoss->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));													//���x�̐ݒ�
	pBoss->m_fYCoord = pBoss->GetPos().y;															//Y���W��ۑ�����
	pBoss->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));												//�F�̐ݒ�
																									
	pBoss->SetTexture(CObject::TextureSloth);														//�e�N�X�`���̐ݒ�
	pBoss->SetTextureParameter(2, 6, 3, 30);														//�e�N�X�`���p�����[�^�̐ݒ�

	D3DXVECTOR3 pos = pBoss->GetPos();

	pBoss->m_HitboxRelativePos = D3DXVECTOR3(30.0f, 0.0f, 0.0f);			//���Έʒu�̐ݒ�

	//�q�b�g�{�b�N�X�̐���
	pBoss->m_pHitbox = CSquareHitbox::Create(D3DXVECTOR3(pos.x + pBoss->m_HitboxRelativePos.x, pos.y, 0.0f), D3DXVECTOR2(100.0f, 80.0f), CHitbox::Type_Enemy);

	//�̗�UI�̐���
	pBoss->m_pLife = CEnemyLife::Create(D3DXVECTOR3(900.0f, 40.0f, 0.0f), D3DXCOLOR(0.0f, 0.4f, 1.0f, 0.5f), 20000, "sloth");

	return pBoss;								//�G��Ԃ�
}



//==================================================================================================
//										�v���C�x�[�g�֐� 
//==================================================================================================

//�X�V����
void CSloth::SlothBehavior(void)
{
	switch (m_state)
	{//��Ԃɂ���Ă̍X�V����

	case CSloth::state_Spawn:

	{//�X�|�[�����

		D3DXCOLOR col = GetColor();				//�F�̎擾

		col.a += 0.005f;						//���l�̍X�V

		if (col.a >= 1.0f)
		{//���l��1.0f�ȏ�ɂȂ�����

			col.a = 1.0f;						//1.0f�ɖ߂�
			m_state = state_Normal;				//���ʂ̏�Ԃɂ���
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_GOAT);		//�T�E���h���Đ�����
		}

		SetColor(col);				//�F�̐ݒ�
	}

	break;

	case CSloth::state_Normal:
		
		//���ʂ̏��
		
		if (m_nCntState > 0)
		{//�J�E���^�[��0�ȏゾ������

			m_nCntState--;				//��ԃJ�E���^�[���f�N�������g����

			if (m_nCntState <= 0)
			{//��ԃJ�E���^�[��0�ȉ��ɂȂ�����
				m_nCntState = 0;				//0�ɖ߂�
			}

			int nState = random(300, 799);		//�����_���Ő��l��I��

			nState /= 100;			//100�Ŋ���

			switch (nState)
			{//��̌v�Z�̌��ʂɂ���Ď��̍U����I������

			case state_Charge:

				m_state = state_Charge;			//�̓�����U���ɂ���

				m_nSoundDelay = 120;			//�T�E���h�f�B���C�̐ݒ�

				SetMove(D3DXVECTOR3(-5.0f, 0.0f, 0.0f));	//���x�̐ݒ�

				break;

			case state_Snore:

				m_state = state_Snore;			//���т��U���ɂ���

				SetMove(D3DXVECTOR3(-2.0f, 0.0f, 0.0f));	//���x�̐ݒ�

				m_nSoundDelay = 150;			//�T�E���h�f�B���C�̐ݒ�

				break;

			case state_Weep:

				m_state = state_Weep;			//�����U��(1)�U���ɂ���

				SetMove(D3DXVECTOR3(-4.0f, 0.0f, 0.0f));	//���x�̐ݒ�

				m_nSoundDelay = 60;				//�T�E���h�f�B���C�̐ݒ�

				break;

			case state_Cry:

				m_state = state_Cry;			//�����U��(2)�U���ɂ���

				SetMove(D3DXVECTOR3(-4.0f, 0.0f, 0.0f));	//���x�̐ݒ�

				m_nSoundDelay = 60;				//�T�E���h�f�B���C�̐ݒ�

				break;

			case state_Summon:

				m_state = state_Summon;			//������Ԃɂ���

				SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//���x�̐ݒ�

				m_nSoundDelay = 240;			//�T�E���h�f�B���C�̐ݒ�

				break;


			default:
				break;
			}
		}

		break;

	case state_Return:

	{//�߂��Ԃ�������

		D3DXVECTOR3 pos = GetPos();				//�ʒu�̎擾

		if (pos.x <= (float)SCREEN_WIDTH * 0.75f)
		{//���܂����ʒu�ɒ�������

			m_nCntState = 30;					//��ԃJ�E���^�[��ݒ肷��
			m_state = state_Normal;				//���ʂ̏�Ԃɖ߂�
			m_fYCoord = GetPos().y;				//Y���W�̐ݒ�
			m_nCntMove = 0;						//�ړ��J�E���^�[��0�ɖ߂�
			m_fAngleMove = 0.0f;				//���݂̃A�j���[�V�����p�x��0�ɖ߂�
		}										
	}

	break;


	case CSloth::state_Charge:

	{//�̓�����U��

		D3DXVECTOR3 pos = GetPos();					//�ʒu�̎擾
		D3DXVECTOR3 move = GetMove();				//���x�̎擾
		m_fAngleMove += D3DX_PI * 0.0125f;			//�A�j���[�V�����p�x�̍X�V

		//�ʒu�̍X�V
		pos.x += move.x;
		pos.y = m_fYCoord + 130.0f * sqrtf(cosf(m_fAngleMove) * cosf(m_fAngleMove));

		if (pos.x <= -1.0f * GetSize().x)
		{//��ʂ̍�������o����

			pos.x = -1.0f * GetSize().x;				//X���W��ݒ肷��
			pos.y = (float)random(150, 570);			//Y���W��ݒ肷��
			m_fYCoord = pos.y;							//���݂�Y���W�̐ݒ�
			move.x *= -1.0f;							//���x��X���W���t�ɂ���
			FlipX();									//�e�N�X�`���𔽓]����
			m_HitboxRelativePos.x *= -1.0f;				//�q�b�g�{�b�N�X�̈ʒu���X�V����
			m_nPhase++;									//�U�������C���N�������g����
		}
		else if (pos.x >= (float)SCREEN_WIDTH + GetSize().x)
		{//��ʂ̉E������o����
			pos.x = (float)SCREEN_WIDTH + GetSize().x;	//X���W��ݒ肷��
			pos.y = (float)random(150, 570);			//Y���W��ݒ肷��
			m_fYCoord = pos.y;							//���݂�Y���W�̐ݒ�
			move.x *= -1.0f;							//���x��X���W���t�ɂ���
			FlipX();									//�e�N�X�`���𔽓]����
			m_HitboxRelativePos.x *= -1.0f;				//�q�b�g�{�b�N�X�̈ʒu���X�V����
			m_nPhase++;									//�U�������C���N�������g����
		}

		if (m_nPhase >= 4)
		{//4�񂱂̍U����������

			//�ʒu�Ƒ��x��ݒ肵�āA��ʂ̉E��ɖ߂�
			pos = D3DXVECTOR3((float)SCREEN_WIDTH * 1.25f, (float)SCREEN_HEIGHT * 0.25f, 0.0f);
			move = D3DXVECTOR3(-2.0f, 0.0f, 0.0f);
			m_state = state_Return;
			m_nPhase = 0;
		}

		SetPos(pos);			//�ʒu�̐ݒ�
		SetMove(move);			//���x�̐ݒ�
		m_nCntSound++;			//�T�E���h�̃J�E���^�[�̍X�V
	}

	break;

	case CSloth::state_Snore:

	{//���т��U��

		D3DXVECTOR3 pos = GetPos();			//�ʒu�̎擾
		D3DXVECTOR3 move = GetMove();		//���x�̎擾

		pos += move;						//�ʒu�̍X�V

		if (pos.x <= -1.0f * GetSize().x)
		{//��ʂ̍�������o����
			pos.x = -1.0f * GetSize().x;	//X���W��ݒ肷��	
			move.x *= -1.0f;				//Y���W��ݒ肷��
			FlipX();						//�e�N�X�`���𔽓]����
			m_HitboxRelativePos.x *= -1.0f;	//�q�b�g�{�b�N�X�̈ʒu���X�V����
			m_nPhase++;						//�U�������C���N�������g����
		}									
		else if (pos.x >= (float)SCREEN_WIDTH + GetSize().x)
		{//��ʂ̉E������o����
			pos.x = (float)SCREEN_WIDTH + GetSize().x;		//X���W��ݒ肷��	
			move.x *= -1.0f;								//Y���W��ݒ肷��
			FlipX();										//�e�N�X�`���𔽓]����
			m_HitboxRelativePos.x *= -1.0f;					//�q�b�g�{�b�N�X�̈ʒu���X�V����
			m_nPhase++;										//�U�������C���N�������g����
		}

		if (pos.x >= 10.0f && pos.x <= (float)SCREEN_WIDTH - 10.0f)
		{//��ʓ���������

			m_nShootDelay++;				//�U���J�E���^�[���C���N�������g����

			if (m_nShootDelay >= 60)
			{//60�t���[�����ƒe�𔭐�����

				//���x���v�Z����
				D3DXVECTOR3 PlayerPos = CPlayer::GetPlayer()->GetPos();
				D3DXVECTOR3 BulletMove = PlayerPos - pos;
				D3DXVec3Normalize(&BulletMove, &BulletMove);

				{//�v���C���[��_�����e
					CZBullet* pBullet = CZBullet::Create(pos, D3DXVECTOR3(BulletMove.x * 5.0f, BulletMove.y * 5.0f, 0.0f));
				}

				for (int nCnt = 0; nCnt < 2; nCnt++)
				{//��v�Z���������Ƀ����_���ȕ����x�N�g���𑫂��āA��������
					D3DXVECTOR3 dir = D3DXVECTOR3((float)random(-1000, 1000) * 0.001f, (float)random(-1000, 1000) * 0.001f, 0.0f);
					dir += BulletMove;
					D3DXVec3Normalize(&dir, &dir);
					CZBullet* pBullet = CZBullet::Create(pos, D3DXVECTOR3(dir.x * 5.0f, dir.y * 5.0f, 0.0f));
				}

				m_nShootDelay = 0;			//�U���J�E���^�[��0�ɖ߂�
			}
		}

		if (m_nPhase >= 4)
		{//4�񂱂̍U����������A���ʂ̏�Ԃɖ߂�
			pos = D3DXVECTOR3((float)SCREEN_WIDTH * 1.25f, (float)SCREEN_HEIGHT * 0.25f, 0.0f);
			move = D3DXVECTOR3(-2.0f, 0.0f, 0.0f);
			m_state = state_Return;
			m_nPhase = 0;
		}

		SetPos(pos);			//�ʒu�̐ݒ�
		SetMove(move);			//���x�̐ݒ�
		m_nCntSound++;			//�T�E���h�̃J�E���^�[���C���N�������g����
	}

	break;

	case CSloth::state_Weep:

	{//�����U��(1)

		D3DXVECTOR3 pos = GetPos();				//�ʒu�̎擾
		D3DXVECTOR3 move = GetMove();			//���x�̎擾

		pos.x += move.x;						//�ʒu�̍X�V

		if (pos.x <= -1.0f * GetSize().x)
		{//��ʂ̍�������o����
			pos.x = -1.0f * GetSize().x;		//X���W��ݒ肷��	
			move.x *= -1.0f;					//Y���W��ݒ肷��
			FlipX();							//�e�N�X�`���𔽓]����
			m_HitboxRelativePos.x *= -1.0f;		//�q�b�g�{�b�N�X�̈ʒu���X�V����
			m_nPhase++;							//�U�������C���N�������g����
		}
		else if (pos.x >= (float)SCREEN_WIDTH + GetSize().x)
		{//��ʂ̉E������o����
			pos.x = (float)SCREEN_WIDTH + GetSize().x;		//X���W��ݒ肷��	
			move.x *= -1.0f;								//Y���W��ݒ肷��
			FlipX();										//�e�N�X�`���𔽓]����
			m_HitboxRelativePos.x *= -1.0f;					//�q�b�g�{�b�N�X�̈ʒu���X�V����
			m_nPhase++;										//�U�������C���N�������g����
		}

		if (pos.x >= 50.0f && pos.x <= (float)SCREEN_WIDTH - 50.0f)
		{//��ʓ���������

			m_nShootDelay++;					//�U���J�E���^�[���C���N�������g����

			if (m_nShootDelay >= 10)
			{//10�t���[�����ƒe2�𔭐�����

				for (int nCnt = 0; nCnt < 2; nCnt++)
				{
					//���x�̌v�Z
					int rand = random(0, 1);
					D3DXVECTOR3 dir = D3DXVECTOR3((float)random(5, 30) * 0.1f, (float)random(40, 70) * -0.1f, 0.0f);

					if (rand == 0)
					{
						dir.x *= -1.0f;
					}

					//�e�̐���
					CTearBullet* pBullet = CTearBullet::Create(D3DXVECTOR3(pos.x + ((float)abs((int)move.x) / move.x) * 150.0f, pos.y - 50.0f, 0.0f), dir);
				}

				m_nShootDelay = 0;				//�U���J�E���^�[��0�ɖ߂�
			}
		}

		if (m_nPhase >= 4)
		{//4�񂱂̍U���������畁�ʂ̏�Ԃɖ߂�
			pos = D3DXVECTOR3((float)SCREEN_WIDTH * 1.25f, (float)SCREEN_HEIGHT * 0.25f, 0.0f);
			move = D3DXVECTOR3(-2.0f, 0.0f, 0.0f);
			m_state = state_Return;
			m_nPhase = 0;
		}

		SetPos(pos);			//�ʒu�̐ݒ�
		SetMove(move);			//���x�̐ݒ�
		m_nCntSound++;			//�T�E���h�̃J�E���^�[���C���N�������g����
	}

	break;

	case CSloth::state_Cry:

	{
		D3DXVECTOR3 pos = GetPos();			//�ʒu�̎擾
		D3DXVECTOR3 move = GetMove();		//���x�̎擾

		pos.x += move.x;					//�ʒu�̍X�V

		if (pos.x <= -1.0f * GetSize().x)
		{//��ʂ̍�������o����
			pos.x = -1.0f * GetSize().x;		//X���W��ݒ肷��	
			move.x *= -1.0f;					//Y���W��ݒ肷��
			FlipX();							//�e�N�X�`���𔽓]����
			m_HitboxRelativePos.x *= -1.0f;		//�q�b�g�{�b�N�X�̈ʒu���X�V����
			m_nPhase++;							//�U�������C���N�������g����
		}
		else if (pos.x >= (float)SCREEN_WIDTH + GetSize().x)
		{//��ʂ̉E������o����
			pos.x = (float)SCREEN_WIDTH + GetSize().x;		//X���W��ݒ肷��	
			move.x *= -1.0f;								//Y���W��ݒ肷��
			FlipX();										//�e�N�X�`���𔽓]����
			m_HitboxRelativePos.x *= -1.0f;					//�q�b�g�{�b�N�X�̈ʒu���X�V����
			m_nPhase++;										//�U�������C���N�������g����
		}

		if (pos.x >= 50.0f && pos.x <= (float)SCREEN_WIDTH - 50.0f)
		{//��ʓ���������

			m_nShootDelay++;			//�U���J�E���^�[���C���N�������g����

			if (m_nShootDelay >= 30)
			{//30�t���[�����ƒe��6��������

				for (int nCnt = 0; nCnt < 6; nCnt++)
				{
					//�����_���ő��x��ݒ肷��
					int rand = random(0, 1);
					D3DXVECTOR3 dir = D3DXVECTOR3((float)random(5, 30) * 0.1f, (float)random(40, 70) * -0.1f, 0.0f);

					if (rand == 0)
					{
						dir.x *= -1.0f;
					}

					//�e�̐���
					CTearBullet* pBullet = CTearBullet::Create(D3DXVECTOR3(pos.x + ((float)abs((int)move.x) / move.x) * 150.0f, pos.y - 50.0f, 0.0f), dir);
				}

				m_nShootDelay = 0;			//�U���J�E���^�[��0�ɖ߂�
			}
		}

		if (m_nPhase >= 4)
		{//4�񂱂̍U����������A���ʂ̏�Ԃɖ߂�
			pos = D3DXVECTOR3((float)SCREEN_WIDTH * 1.25f, (float)SCREEN_HEIGHT * 0.25f, 0.0f);
			move = D3DXVECTOR3(-2.0f, 0.0f, 0.0f);
			m_state = state_Return;
			m_nPhase = 0;
		}

		SetPos(pos);					//�ʒu�̐ݒ�
		SetMove(move);					//���x�̐ݒ�
		m_nCntSound++;					//�T�E���h�̃J�E���^�[���C���N�������g����
	}

	break;

	case CSloth::state_Summon:

	{//����

		SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));				//���x�̐ݒ�
		D3DXVECTOR3 pos = GetPos();							//�ʒu�̎擾

		//�㉺�̈ړ��̐ݒ�
		m_fAngleMove += D3DX_PI * 0.025f;					
		pos.y = m_fYCoord + cosf(m_fAngleMove) * 50.0f;		
			
		m_nShootDelay++;					//�U���J�E���^�[���C���N�������g����

		if (m_nShootDelay % 30 == 29)
		{//30�t���[�����ƓG����������
			CEnemyCloud* pEnemy = CEnemyCloud::Create(pos);			//�G�̐���
		}

		if (m_nShootDelay >= 610)
		{//610�t���[�����o������A���ʂ̏�Ԃɖ߂�
			m_state = state_Normal;
		}
		m_nCntSound++;				//�T�E���h�̃J�E���^�[���C���N�������g����
	}

	break;


	case CSloth::state_Death:

	{//���S���

		D3DXCOLOR col = GetColor();			//�F�̎擾
		D3DXVECTOR3 pos = GetPos();			//�ʒu�̎擾

		if (col.a > 0.0f)
		{//���l��0.0f�ȏゾ������

			m_nCntSound++;					//�T�E���h�̃J�E���^�[���C���N�������g����
			col.a -= 0.005f;				//���l�̍X�V
			SetColor(col);					//�F�̐ݒ�
			m_nShootDelay++;				//�U���J�E���^�[���C���N�������g����

			if (m_nShootDelay >= 15)
			{//15�t���[�����ƒe6�𐶐�����

				for (int nCnt = 0; nCnt < 6; nCnt++)
				{
					//�����_���ő��x��ݒ肷��
					int rand = random(0, 1);
					D3DXVECTOR3 dir = D3DXVECTOR3((float)random(5, 30) * 0.1f, (float)random(40, 70) * -0.1f, 0.0f);

					if (rand == 0)
					{
						dir.x *= -1.0f;
					}

					float fDir = 1.0f;

					if (!GetFlipX())
					{
						fDir = -1.0f;
					}

					//�e�̐���
					CTearBullet* pBullet = CTearBullet::Create(D3DXVECTOR3(pos.x + (115.0f * fDir), pos.y - 50.0f, 0.0f), dir);
				}

				m_nShootDelay = 0;				//�U���J�E���^�[��0�ɖ߂�
			}
		}
		else
		{//���l��0.0f�ȉ��ɂȂ�����
			m_bEnd = true;			//���񂾏�Ԃɂ���
		}
	}

	break;

	default:
		break;
	}

	//�̗͂ɂ���ď������G�𐶐�����
	switch (m_nChange)
	{
	case 1:

	{//�̗͂�15000�ȉ�7500���傫��������

		m_nCntSpawn++;			//�X�|�[���J�E���^�[���C���N�������g����

		if (m_nCntSpawn >= 120)
		{//120�t���[�����ƓG��̂𐶐�����

			m_nCntSpawn = 0;		//�X�|�[���J�E���^�[��0�ɖ߂�

			CEnemyCloud::Create(GetPos());		//�G�̐���
		}
	}

		break;

	case 2:

	{//�̗͂�7500������������

		m_nCntSpawn++;				//�X�|�[���J�E���^�[���C���N�������g����

		if (m_nCntSpawn >= 60)
		{//60�t���[�����ƓG��̂𐶐�����

			m_nCntSpawn = 0;		//�X�|�[���J�E���^�[��0�ɖ߂�

			CEnemyCloud::Create(GetPos());			//�G�̐���
		}
	}

		break;

	default:
		break;
	}

	if (m_nCntSound >= m_nSoundDelay)
	{//�T�E���h�̃J�E���^�[�����܂����f�B���C�𒴂�����

		CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_GOAT);			//�T�E���h���Đ�����
		m_nCntSound = 0;				//�T�E���h�̃J�E���^�[��0�ɖ߂�
	}
}