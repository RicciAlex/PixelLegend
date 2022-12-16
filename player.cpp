//=============================================================================
//
// player.cpp
// Author : Ricci Alex
//
//=============================================================================

//�C���N���[�h�t�@�C��
#include "player.h"
#include "inputKeyboard.h"
#include "fireballPlayer.h"
#include "application.h"
#include "inputMouse.h"
#include "squareHitbox.h"
#include "lifeIcon.h"
#include "sound.h"

//�ÓI�ϐ��̏�����
CPlayer* CPlayer::m_pPlayer = nullptr;

//�R���X�g���N�^
CPlayer::CPlayer()
{
	//�����o�[�ϐ����N���A����
	m_nShootDelay = 0;
	m_nStateCnt = 0;
	m_nDir = 0;
	m_nLife = 0;
	m_nDamageCnt = 0;
	m_nAttack = 0;							
	m_nAnimCnt = 0;
	m_bConfused = false;
	m_bDead = false;
	m_bEnd = false;
	m_pHitbox = nullptr;
	m_pIcon = nullptr;
}

//�f�X�g���N�^
CPlayer::~CPlayer()
{

}

//����������
HRESULT CPlayer::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CObject_2D::Init()))
	{
		return -1;
	}

	//�����o�[�ϐ��̏���������
	CObject::SavePlayerIdx(this);
	SetTexture(CObject::TextureDragon);				//�e�N�X�`���̐ݒ�
	SetTextureParameter(2, 2, 3, 16);				//�e�N�X�`���p�����[�^�̐ݒ�
	SetSize(D3DXVECTOR2(50.0f, 50.0f));				//�T�C�Y�̐ݒ�
	SetStartingRot(D3DX_PI * 0.5f);					//��]�p�x�̐ݒ�
	m_nShootDelay = 0;								//�e�𔭐�����p�̃J�E���^�[
	m_nStateCnt = 0;								//��ԃJ�E���^�[
	m_nDamageCnt = 0;								//�_���[�W�J�E���^�[
	int nDifficulty = CApplication::GetDifficulty();//��Փx
	m_nAttack = 100 - (25 * (nDifficulty - 1));		//�U����
	m_nAnimCnt = 0;									//�A�j���[�V�����p�̃J�E���^�[
	m_nLife = 15;									//�̗�
	m_nDir = -1;									//����
	m_bConfused = false;							
	m_bDead = false;								//���S�������ǂ���
	m_bEnd = false;									//�I��������ǂ���
	m_pIcon = nullptr;								//UI�C���X�^���X�ւ̃|�C���^
	m_pPlayer = this;								//���̃C���X�^���X�ւ̃|�C���^
	
	return S_OK;
}

//�I������
void CPlayer::Uninit(void)
{
	//�q�b�g�{�b�N�X�̔j������
	if (m_pHitbox != nullptr)
	{//null�`�F�b�N
		m_pHitbox->Release();			//���������������
		m_pHitbox = nullptr;			//null�ɂ���
	}

	//UI�̔j������
	if (m_pIcon != nullptr)
	{//null�`�F�b�N
		m_pIcon->Release();				//���������������
		m_pIcon = nullptr;				//null�ɂ���
	}

	m_pPlayer = nullptr;				//null�ɂ���

	//��{�N���X�̏I������
	CObject_2D::Uninit();
}

//�X�V����
void CPlayer::Update(void)
{
	D3DXVECTOR3 pos = CObject_2D::GetPos();					//�ʒu�̎擾����
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���

	if (!m_bDead)
	{
		//�ʒu�̍X�V����
		if (CInputKeyboard::GetKeyboardPress(DIK_D))
		{//D�{�^�����������ꍇ
			if (!m_bConfused)
			{
				move += D3DXVECTOR3(1.0f, 0.0f, 0.0f);
			}
			else
			{
				move += D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			}
		}
		if (CInputKeyboard::GetKeyboardPress(DIK_A))
		{//A�{�^�����������ꍇ
			if (!m_bConfused)
			{
				move += D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
			}
			else
			{
				move += D3DXVECTOR3(0.0f, -1.0f, 0.0f);
			}
		}
		if (CInputKeyboard::GetKeyboardPress(DIK_W))
		{//W�{�^�����������ꍇ
			if (!m_bConfused)
			{
				move += D3DXVECTOR3(0.0f, -1.0f, 0.0f);
			}
			else
			{
				move += D3DXVECTOR3(1.0f, 0.0f, 0.0f);
			}
		}
		if (CInputKeyboard::GetKeyboardPress(DIK_S))
		{//S�{�^�����������ꍇ
			if (!m_bConfused)
			{
				move += D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			}
			else
			{
				move += D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
			}
		}

		//���x�̐ݒ�
		D3DXVec3Normalize(&move, &move);
		move.x *= 5.0f;
		move.y *= 5.0f;

		//�����̐ݒ�
		if (move.x > 0.0f)
		{
			m_nDir = 1;
		}
		else if (move.x < 0.0f)
		{
			m_nDir = -1;
		}

		//�ʒu�̍X�V
		pos += move;

		if (m_nShootDelay >= 0)
		{//�e�̔����J�E���^�[��0�ȏゾ������
			m_nShootDelay--;			//�J�E���^�[���f�N�������g����
		}

		if (!CApplication::GetMouse()->GetMouseLeftClick() && GetPresentAnimPattern() > 1)
		{
			SetTextureParameter(2, 2, 3, 16);
			SetAnimPattern(CObject_2D::GetPresentAnimPattern() - 2);
		}

		if (CApplication::GetMouse()->GetMouseLeftClick())
		{//�X�y�[�X�L�[����������A�e�𐶐�����

			if (m_nShootDelay <= 0)
			{//�e�̔�������

				//�}�E�X�J�[�\���̈ʒu�̎擾�ƕϊ�
				POINT pt;
				GetCursorPos(&pt);
				HWND wnd = CApplication::GetWindow();
				ScreenToClient(wnd, &pt);
				D3DXVECTOR3 MousePos, Target;
				MousePos.x = (float)pt.x;
				MousePos.y = (float)pt.y;
				MousePos.z = 0.0f;

				//�����̈ʒu���v�Z����
				Target = MousePos - pos;
				D3DXVec3Normalize(&Target, &Target);
				D3DXVECTOR3 spawnPos = pos;
				spawnPos.x += m_nDir * 35.0f;
				spawnPos.y -= 3.0f;

				m_nShootDelay = 20;													//�J�E���^�[��ݒ肷��
				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_FIRE);		//�V���b�g�̃T�E���h�G�t�F�N�g

				//�e2�������āA�K�v�ȏ���ݒ肷��
				CFireballPlayer* pBullet = CFireballPlayer::Create(spawnPos, D3DXVECTOR3(10.0f * Target.x, 10.0f * Target.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(16.0f, 16.0f));
				pBullet = CFireballPlayer::Create(spawnPos, D3DXVECTOR3(10.0f * Target.x, 10.0f * Target.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(16.0f, 16.0f));
				pBullet->SetStartingAngle(D3DX_PI);
			}

			m_nAnimCnt++;			//�A�j���[�V�����p�̃J�E���^�[���C���N�������g����

			//�e�N�X�`���A�j���V�����̏���
			int nCell = 2;

			if (m_nAnimCnt >= 16)
			{
				nCell++;

				if (m_nAnimCnt >= 32)
				{
					m_nAnimCnt = 0;
				}
			}

			SetTextureParameter(1, 2, 3, INT_MAX);
			SetAnimPattern(nCell);
		}
		else
		{
			m_nAnimCnt = 0;				//�J�E���^�[��0�ɖ߂�
		}

		//��ԃJ�E���^�[�̍X�V
		if (m_nStateCnt > 0)
		{
			m_nStateCnt--;

			if (m_nStateCnt <= 0)
			{
				m_nStateCnt = 0;
				m_bConfused = false;
			}
		}

		//�_���[�W�J�E���^�[�̍X�V
		if (m_nDamageCnt > 0)
		{
			m_nDamageCnt--;			//�J�E���^�[���C���N�������g����

			if (m_nDamageCnt % 5 == 4)
			{//5�t���[�����o������A�F��ς���

				D3DXCOLOR col = GetColor();			//�F�̎擾

				if (col.g < 1.0f)
				{//�Ԃ�������
					SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				}
				else
				{//���ʂ�������
					SetColor(D3DXCOLOR(1.0f, 0.4f, 0.4f, 1.0f));
				}

			}

			if (m_nDamageCnt <= 0)
			{//�J�E���^�[��0�ȉ��ɂȂ�����
				m_nDamageCnt = 0;
				SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
		}

		//��ʊO�o���Ȃ����鏈��
		//X���W
		if (pos.x <= GetSize().x)
		{
			pos.x = GetSize().x;			//�ʒu�̐ݒ�
		}
		else if (pos.x >= (float)SCREEN_WIDTH - GetSize().x)
		{
			pos.x = (float)SCREEN_WIDTH - GetSize().x;			//�ʒu�̐ݒ�
		}
		//Y���W
		if (pos.y <= GetSize().y)
		{
			pos.y = GetSize().y;			//�ʒu�̐ݒ�
		}
		else if (pos.y >= (float)SCREEN_HEIGHT - GetSize().y)
		{
			pos.y = (float)SCREEN_HEIGHT - GetSize().y;			//�ʒu�̐ݒ�
		}

		//�ʒu�̐ݒ�
		CObject_2D::SetPos(pos);

		//�����蔻��
		if (m_pHitbox != nullptr)
		{//null�`�F�b�N
			m_pHitbox->SetPos(pos);				//�ʒu�̐ݒ�

			if (m_pHitbox->GetHitState() || m_pHitbox->Hit())
			{//���������ꍇ
				m_pHitbox->SetHitState(false);			//���ʂ̏�Ԃɂ���

				if (m_nDamageCnt <= 0)
				{//�_���[�W�J�E���^�[��0�ȉ���������

					int nDiff = CApplication::GetDifficulty();			//��Փx�̎擾

					//�̗͂̍X�V
					for (int nCnt = 0; nCnt < nDiff; nCnt++)
					{
						m_nLife--;				//�̗͂��f�N�������g����
						m_pIcon->Update();		//UI�̍X�V
					}

					//���G��ԃJ�E���^�[�̐ݒ�
					m_nDamageCnt = 60 - (10 * CApplication::GetDifficulty());

					//�F�̐ݒ�
					SetColor(D3DXCOLOR(1.0f, 0.4f, 0.4f, 1.0f));
				}
			}
		}

		if (m_nLife <= 0)
		{//�̗͂�0�ȉ��ɂȂ�����

			m_bDead = true;												//���S������Ԃɂ���
			SetMove(D3DXVECTOR3((float)random(-2, 2), -10.0f, 0.0f));	//�ړ��ʂ̐ݒ�
			SetAcceleration(D3DXVECTOR3(0.0f, 0.5f, 0.0f));				//�����̐ݒ�
			SetAnimPattern(4);											//�A�j���V�����p�^�[���̐ݒ�
			SetTextureParameter(1, 2, 3, INT_MAX);						//�e�N�X�`���p�����[�^�̐ݒ�
			SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));				//�F�̐ݒ�
			SetPriority(5);												//�v���C�I���e�B�̐ݒ�
		}

		if (!GetFlipX() && m_nDir == -1 || GetFlipX() && m_nDir == 1)
		{//�����ɂ���ăe�N�X�`���𔽓]����
			FlipX();
		}
	}
	else
	{//���S�����ꍇ
		if (pos.y >= 1350.0f)
		{//��ʂ��o����A�����҂��āA���S�t���O��true�ɂ���
			m_bEnd = true;
		}
	}

	//��{�N���X�̍X�V
	CObject_2D::Update();
}

//�`�揈��
void CPlayer::Draw(void)
{
	//��{�N���X�̕`�揈��
	CObject_2D::Draw();
}

void CPlayer::SetConfusion(const int nTime)
{
	m_bConfused = true;
	m_nStateCnt = nTime;
}

//�U���͂̐ݒ菈��
void CPlayer::SetAttack(const int nAttack)
{
	m_nAttack = nAttack;
}

//���C�t�̐ݒ菈��
const int CPlayer::GetLife(void)
{
	return m_nLife;
}

//�U���͂̎擾����
const int CPlayer::GetAttack(void)
{
	return m_nAttack;
}

//�I��������ǂ����̎擾����
const bool CPlayer::GetEnd(void)
{
	return m_bEnd;
}


//�v���C���[�̐�������
CPlayer* CPlayer::Create(void)
{
	CPlayer* pPlayer = nullptr;

	pPlayer = new CPlayer;									//�V�����v���C���[�𐶐�����

	//����������
	if (FAILED(pPlayer->Init()))
	{//�ł��Ȃ�������

		return nullptr;
	}

	pPlayer->m_nLife = 15;									//�̗͂̐ݒ菈��

	pPlayer->SetObjType(CObject::OBJTYPE_PLAYER);			//�I�u�W�F�N�g��ނ̐ݒ�

	//�q�b�g�{�b�N�X�̐�������
	pPlayer->m_pHitbox = CSquareHitbox::Create(pPlayer->GetPos(), D3DXVECTOR2(20.0f, 20.0f), CHitbox::Type_Player);

	//UI�̐�������
	pPlayer->m_pIcon = CLifeIcon::Create(D3DXVECTOR3(50.0f, 50.0f, 0.0f));

	return pPlayer;											//���������|�C���^��Ԃ�
} 

//�v���C���[���̎擾����
CPlayer* CPlayer::GetPlayer(void)
{
	return m_pPlayer;
}