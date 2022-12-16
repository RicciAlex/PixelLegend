//=============================================================================
//
// greed.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "greed.h"
#include "circleHitbox.h"
#include "squareHitbox.h"
#include "greedBullet.h"
#include "player.h"
#include "towerJewel.h"
#include "enemyLife.h"
#include "application.h"
#include "sound.h"

//=============================================================================
//							�ÓI�ϐ��̏�����
//=============================================================================

//�ړI�̈ʒu�̏���������
const D3DXVECTOR3 CGreed::TargetPos[nTargetNum] = 
{
	D3DXVECTOR3(150.0f, 150.0f, 0.0f),
	D3DXVECTOR3((float)SCREEN_WIDTH - 150.0f, 150.0f, 0.0f),
	D3DXVECTOR3(150.0f, (float)SCREEN_HEIGHT - 150.0f, 0.0f),
	D3DXVECTOR3((float)SCREEN_WIDTH - 150.0f, (float)SCREEN_HEIGHT - 150.0f, 0.0f),
	D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f)
};

//�R���X�g���N�^
CGreed::CGreed()
{
	//�����o�[�ϐ����N���A����
	m_bEnd = false;
	m_fSumAngle = 0.0f;
	m_fShotAngle = 0.0f;
	m_targetIdx = 0;
	m_nAnimCnt = 0;
	m_nTowerDelay = 0;
	m_state = state_spawn;

	m_HitboxUpRelativePos   = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_HitboxDownRelativePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_pHitboxUp = nullptr;
	m_pHitboxDown = nullptr;
	m_pLife = nullptr;

	for (int nCnt = 0; nCnt < MaxTower; nCnt++)
	{
		m_pTower[nCnt] = nullptr;
	}
}

//�f�X�g���N�^
CGreed::~CGreed()
{

}

//����������
HRESULT CGreed::Init(void)
{
	if (FAILED(CEnemy::Init()))
	{//��{�N���X�̏���������
		return -1;
	}

	//�����o�[�ϐ�������������
	m_bEnd = false;
	m_fSumAngle = 0.22f;
	m_fShotAngle = 0.0f;
	m_targetIdx = 0;
	m_nAnimCnt = 0;
	m_nTowerDelay = 0;
	m_state = state_spawn;

	m_HitboxUpRelativePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_HitboxDownRelativePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_pHitboxUp = nullptr;
	m_pHitboxDown = nullptr;
	m_pLife = nullptr;

	for (int nCnt = 0; nCnt < MaxTower; nCnt++)
	{
		m_pTower[nCnt] = nullptr;
	}

	return S_OK;
}

//�I������
void CGreed::Uninit(void)
{
	//�̂̏㑤�̃q�b�g�{�b�N�X�̔j������
	if (m_pHitboxUp != nullptr)
	{//null�`�F�b�N
		m_pHitboxUp->Release();				//���������������
		m_pHitboxUp = nullptr;				//�|�C���^��null�ɂ���
	}

	//�̂̉����̃q�b�g�{�b�N�X�̔j������
	if (m_pHitboxDown != nullptr)
	{//null�`�F�b�N	 
		m_pHitboxDown->Release();			//���������������
		m_pHitboxDown = nullptr;			//�|�C���^��null�ɂ���
	}

	//���E�̓G�̔j������
	for (int nCnt = 0; nCnt < MaxTower; nCnt++)
	{
		if (m_pTower[nCnt])
		{//null�`�F�b�N
			m_pTower[nCnt]->Release();		//���������������
			m_pTower[nCnt] = nullptr;		//�|�C���^��null�ɂ���
		}
	}

	//�̗�UI�̔j������
	if (m_pLife != nullptr)
	{//null�`�F�b�N
		m_pLife->Release();					//���������������
		m_pLife = nullptr;					//�|�C���^��null�ɂ���
	}

	//��{�N���X�̏I������
	CEnemy::Uninit();
}

//�X�V����
void CGreed::Update(void)
{
	D3DXVECTOR3 pos = GetPos();			//�ʒu�̎擾

	//�̂̏㑤�̃q�b�g�{�b�N�X�̍X�V
	if (m_pHitboxUp != nullptr)
	{//null�`�F�b�N

		m_pHitboxUp->SetPos(GetPos() + m_HitboxUpRelativePos);		//�q�b�g�{�b�N�X�̈ʒu�̍X�V

		if (m_pHitboxUp->GetHitState())
		{//����������Ԃ�������

			m_pHitboxUp->SetHitState(false);		//�̂̏㑤�̃q�b�g�{�b�N�X�𓖂��Ă��Ȃ���Ԃɖ߂�
			m_pHitboxDown->SetHitState(false);		//�̂̉����̃q�b�g�{�b�N�X�𓖂��Ă��Ȃ���Ԃɖ߂�

			int nLife = GetLife();								//�̗͂̎擾
			int nDamage = CPlayer::GetPlayer()->GetAttack();	//�v���C���[�̍U���͂̎擾
			nLife -= nDamage;									//�̗͂��X�V����

			if (nLife <= 0)
			{//�̗͂�0�ȉ��ɂȂ�����
				m_state = state_death;			//���S��Ԃɂ���
				nLife = 0;
				SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

				//�q�b�g�{�b�N�X��j������
				m_pHitboxUp->Release();
				m_pHitboxUp = nullptr;

				if (m_pHitboxDown)
				{
					m_pHitboxDown->Release();
					m_pHitboxDown = nullptr;
				}
			}
			else
			{//�̗͂�0�ȉ��ł͂Ȃ�������

				SetLife(nLife);					//�̗͂̐ݒ�

				//1�`2�̒e�̐���
				for (int nCnt = 0; nCnt < random(1, 2); nCnt++)
				{
					//�������̎��̑��x�͏�����ŁA�������̑��x������
					D3DXVECTOR3 move = D3DXVECTOR3((float)random(-500, 500) * 0.01f, (float)random(400, 800) * -0.01f, 0.0f);

					//�e�̐���
					CGreedBullet::Create(pos, move, D3DXVECTOR3(0.0f, 0.05f, 0.0f));

					//�T�E���h���Đ�����
					CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_COIN);
				}
			}

			//�̗͂�UI�̍X�V
			if (m_pLife != nullptr)
			{//null�`�F�b�N
				m_pLife->SubtractLife(nDamage);
			}
		}
	}
	//�̂̉����̃q�b�g�{�b�N�X�̍X�V
	if (m_pHitboxDown != nullptr)
	{//null�`�F�b�N
		m_pHitboxDown->SetPos(GetPos() + m_HitboxDownRelativePos);	//�q�b�g�{�b�N�X�̈ʒu�̍X�V

		if (m_pHitboxDown->GetHitState())
		{//����������Ԃ�������
			m_pHitboxDown->SetHitState(false);				//�̂̉����̃q�b�g�{�b�N�X�𓖂��Ă��Ȃ���Ԃɖ߂�

			int nLife = GetLife();								//�̗͂̎擾
			int nDamage = CPlayer::GetPlayer()->GetAttack();	//�v���C���[�̍U���͂̎擾
			nLife -= nDamage;									//�̗͂��X�V����

			if (nLife <= 0)
			{//�̗͂�0�ȉ��ɂȂ�����
				m_state = state_death;
				nLife = 0;
				SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

				//�q�b�g�{�b�N�X��j������
				m_pHitboxDown->Release();
				m_pHitboxDown = nullptr;

				if (m_pHitboxUp)
				{
					m_pHitboxUp->Release();
					m_pHitboxUp = nullptr;
				}
			}
			else
			{//�̗͂�0�ȉ��ł͂Ȃ�������

				SetLife(nLife);			//�̗͂̐ݒ�

				//1�`3�̒e�̐���
				for (int nCnt = 0; nCnt < random(1, 3); nCnt++)
				{
					//�������̎��̑��x�͏�����ŁA�������̑��x������
					D3DXVECTOR3 move = D3DXVECTOR3((float)random(-500, 500) * 0.01f, (float)random(400, 800) * -0.01f, 0.0f);

					//�e�̐���
					CGreedBullet::Create(pos, move, D3DXVECTOR3(0.0f, 0.05f, 0.0f));

					//�T�E���h���Đ�����
					CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_COIN);
				}
			}

			//�̗͂�UI�̍X�V
			if (m_pLife != nullptr)
			{//null�`�F�b�N
				m_pLife->SubtractLife(nDamage);
			}
		}
	}

	UpdateState();

	if (m_state != state_spawn && m_state != state_death && GetLife() < 15000)
	{
		m_nTowerDelay++;

		if (m_nTowerDelay >= 600)
		{
			m_nTowerDelay = 0;

			int nIdx = random(0, 1);

			if (m_pTower[nIdx] != nullptr)
			{
				D3DXVECTOR3 Tpos = m_pTower[nIdx]->GetPos();
				Tpos.y = CPlayer::GetPlayer()->GetPos().y;

				m_pTower[nIdx]->SetPos(Tpos);
				m_pTower[nIdx]->SetState(CTowerJewel::state_spawn);
			}
		}
	}

	//��{�N���X�̍X�V����
	CObject_2D::Update();
}

//�`�揈��
void CGreed::Draw(void)
{
	CObject_2D::Draw();
}

const bool CGreed::GetEnd(void)
{
	return m_bEnd;
}




//��������
CGreed* CGreed::Create(void)
{
	CGreed* pEnemy = new CGreed;

	if (FAILED(pEnemy->Init()))
	{
		return nullptr;
	}

	D3DXVECTOR3 pos = D3DXVECTOR3(800.0f, 500.0f, 0.0f);
	pEnemy->m_HitboxUpRelativePos = D3DXVECTOR3(0.0f, -30.0f, 0.0f);
	pEnemy->m_HitboxDownRelativePos = D3DXVECTOR3(0.0f, 75.0f, 0.0f);

	pEnemy->SetPos(D3DXVECTOR3(1400.0f, 350.0f, 0.0f));
	pEnemy->SetMove(D3DXVECTOR3(-1.0f, 0.0f, 0.0f));
	pEnemy->SetSize(D3DXVECTOR2(175.0f, 131.6f));
	pEnemy->SetStartingRot(D3DX_PI * 0.5f);
	pEnemy->SetTexture(CObject::TextureGreed);
	pEnemy->SetTextureParameter(1, 1, 2, INT_MAX);
	pEnemy->SetAnimPattern(1);
	pEnemy->SetLife(20000);

	pEnemy->m_pHitboxUp = CCircleHitbox::Create(pos + pEnemy->m_HitboxUpRelativePos, 95.0f, CHitbox::Type_Enemy);
	pEnemy->m_pHitboxDown = CSquareHitbox::Create(pos + pEnemy->m_HitboxDownRelativePos, D3DXVECTOR2(130.0f, 40.0f), CHitbox::Type_Enemy);
	pEnemy->SetMaxSpeed(2.0f);

	pEnemy->m_pTower[0] = CTowerJewel::Create(D3DXVECTOR3(-100.0f, 0.0f, 0.0f));

	if (pEnemy->m_pTower[0] != nullptr)
	{
		pEnemy->m_pTower[0]->SetStartingRot(0.0f);
	}

	pEnemy->m_pTower[1] = CTowerJewel::Create(D3DXVECTOR3((float)SCREEN_WIDTH + 100.0f, 0.0f, 0.0f));

	if (pEnemy->m_pTower[1])
	{
		pEnemy->m_pTower[1]->SetStartingRot(D3DX_PI);
	}

	pEnemy->m_pLife = CEnemyLife::Create(D3DXVECTOR3(900.0f, 40.0f, 0.0f), D3DXCOLOR(0.0f, 0.4f, 1.0f, 0.5f), 20000, "greed");

	return pEnemy;
}

//��Ԃɂ���Ă̍X�V����
void CGreed::UpdateState(void)
{
	D3DXVECTOR3 pos = GetPos();			//�ʒu�̎擾

	switch (m_state)
	{
	case CGreed::state_spawn:

	{//�X�|�[�����

		m_nAnimCnt++;				//�A�j���[�V�����p�̃J�E���^�[���C���N�������g����

		if (m_nAnimCnt >= 30)
		{//30�t���[�����o������
			m_nAnimCnt = 0;										//�A�j���[�V�����p�̃J�E���^�[��0�ɖ߂�
			SetAnimPattern(GetPresentAnimPattern() ^ 1);		//�A�j���V�����p�^�[�����X�V����
		}

		if (pos.x <= 1000.0f)
		{//���܂����ʒu�ɒ�������

			m_nAnimCnt = 0;								//�A�j���[�V�����p�̃J�E���^�[��0�ɖ߂�
			SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//���x�̐ݒ�
			SetAnimPattern(0);							//�A�j���V�����p�^�[����0�ɖ߂�
			m_state = state_normal;						//���ʂ̏�Ԃɖ߂�
		}

		//�A�j���V�����p�^�[���ɂ���đ傫�����Ⴄ�̂ŁA�q�b�g�{�b�N�X�̃T�C�Y���X�V����
		if (GetPresentAnimPattern() == 0)
		{
			m_HitboxUpRelativePos = D3DXVECTOR3(0.0f, 5.0f, 0.0f);			//�̂̏㑤�̃q�b�g�{�b�N�X�̑��Έʒu��ݒ肷��
			m_HitboxDownRelativePos = D3DXVECTOR3(0.0f, 85.0f, 0.0f);		//�̂̉����̃q�b�g�{�b�N�X�̑��Έʒu��ݒ肷��
			m_pHitboxUp->SetRadius(100.0f);									//�̂̏㑤�̃q�b�g�{�b�N�X�̔��a��ݒ肷��
			m_pHitboxDown->SetSize(D3DXVECTOR2(170.0f, 30.0f));				//�̂̉����̃q�b�g�{�b�N�X�̃T�C�Y��ݒ肷��
		}
		else
		{
			m_HitboxUpRelativePos = D3DXVECTOR3(0.0f, -30.0f, 0.0f);		//�̂̏㑤�̃q�b�g�{�b�N�X�̑��Έʒu��ݒ肷��
			m_HitboxDownRelativePos = D3DXVECTOR3(0.0f, 75.0f, 0.0f);		//�̂̉����̃q�b�g�{�b�N�X�̑��Έʒu��ݒ肷��
			m_pHitboxUp->SetRadius(95.0f);									//�̂̏㑤�̃q�b�g�{�b�N�X�̔��a��ݒ肷��
			m_pHitboxDown->SetSize(D3DXVECTOR2(130.0f, 40.0f));				//�̂̉����̃q�b�g�{�b�N�X�̃T�C�Y��ݒ肷��
		}
	}

	break;

	case CGreed::state_normal:

	{//���ʂ̏��

		//=========================================================
		//				�{��U�������邩�ǂ���
		//		�̗͂ɂ����0%����20%��40%�ɂȂ�܂�
		int k = 0;

		if (GetLife() < 15000)
		{
			k = 2;
			SetMaxSpeed(4.5f);
		}
		else if (GetLife() < 10000)
		{
			k = 4;
			SetMaxSpeed(7.5f);
		}

		if (random(1, 100) > 100 - (k * 10))
		{
			SetAnimPattern(0);
			m_state = state_rage;
			break;
		}
		//==========================================================

		while (true)
		{//���̖ړI�̈ʒu�̐ݒ�

			int nRand = random(0, 4);

			D3DXVECTOR3 L = TargetPos[nRand] - pos;			//���̓G�ƖړI�̈ʒu�̋������v�Z����

			if (D3DXVec3Length(&L) > 20.0f)
			{//������20.0f�ȏゾ������A�ړI�̈ʒu�ֈړ�������

				D3DXVECTOR3 move;
				D3DXVec3Normalize(&move, &L);
				move.x *= GetMaxSpeed();
				move.y *= GetMaxSpeed();
				SetMove(move);
				m_targetIdx = nRand;
				m_state = state_walk;

				if (move.x > 0 && !GetFlipX() || move.x < 0 && GetFlipX())
				{//�����Ƒ��x�̌������ׂāA�K�v��������A�e�N�X�`���𔽓]����
					FlipX();
				}

				break;
			}
		}
	}

	break;

	case CGreed::state_walk:

	{//�ړ����

		m_nAnimCnt++;				//�A�j���[�V�����p�̃J�E���^�[���C���N�������g����
		
		if (m_nAnimCnt >= 30)
		{//30�t���[�����ƃA�j���V�����p�^�[�����X�V����
			m_nAnimCnt = 0;
			SetAnimPattern(GetPresentAnimPattern() ^ 1);
		}

		D3DXVECTOR3 L = TargetPos[m_targetIdx] - pos;			//�ړI�̈ʒu�܂ł̋������v�Z����

		if (D3DXVec3Length(&L) < 10.0f)
		{//10.0f�ȉ���������
			m_nAnimCnt = 0;								//�A�j���[�V�����p�̃J�E���^�[��0�ɖ߂�
			SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//���x��ݒ肷��
			SetAnimPattern(0);							//�A�j���[�V�����p�^�[���̐ݒ�
			m_state = state_shot;						//�U����Ԃɂ���
		}

		//�A�j���V�����p�^�[���ɂ���đ傫�����Ⴄ�̂ŁA�q�b�g�{�b�N�X�̃T�C�Y���X�V����
		if (GetPresentAnimPattern() == 0)
		{
			m_HitboxUpRelativePos = D3DXVECTOR3(0.0f, 5.0f, 0.0f);			//�̂̏㑤�̃q�b�g�{�b�N�X�̑��Έʒu��ݒ肷��
			m_HitboxDownRelativePos = D3DXVECTOR3(0.0f, 85.0f, 0.0f);		//�̂̉����̃q�b�g�{�b�N�X�̑��Έʒu��ݒ肷��
			m_pHitboxUp->SetRadius(100.0f);									//�̂̏㑤�̃q�b�g�{�b�N�X�̔��a��ݒ肷��
			m_pHitboxDown->SetSize(D3DXVECTOR2(170.0f, 30.0f));				//�̂̉����̃q�b�g�{�b�N�X�̃T�C�Y��ݒ肷��
		}
		else
		{
			m_HitboxUpRelativePos = D3DXVECTOR3(0.0f, -30.0f, 0.0f);		//�̂̏㑤�̃q�b�g�{�b�N�X�̑��Έʒu��ݒ肷��
			m_HitboxDownRelativePos = D3DXVECTOR3(0.0f, 75.0f, 0.0f);		//�̂̉����̃q�b�g�{�b�N�X�̑��Έʒu��ݒ肷��
			m_pHitboxUp->SetRadius(95.0f);									//�̂̏㑤�̃q�b�g�{�b�N�X�̔��a��ݒ肷��
			m_pHitboxDown->SetSize(D3DXVECTOR2(130.0f, 40.0f));				//�̂̉����̃q�b�g�{�b�N�X�̃T�C�Y��ݒ肷��
		}
	}

	break;

	case CGreed::state_shot:

	{//�U�����

		D3DXVECTOR3 PlayerPos = CPlayer::GetPlayer()->GetPos();			//�v���C���[�̈ʒu�̎擾

		if (PlayerPos.x > pos.x && !GetFlipX() || PlayerPos.x < pos.x && GetFlipX())
		{//�v���C���[�̈ʒu�܂ł̃x�N�g���ƌ������ׂāA�K�v��������A�e�N�X�`���𔽓]����
			FlipX();
		}

		int nLife = GetLife();				//�̗͂̎擾

		m_nShootDelay++;					//�U���J�E���^�[���C���N�������g����

		//�A�j���[�V�������Ȃ���A�U������
		if (m_nShootDelay % 30 == 13)
		{
			SetAnimPattern(1);			//�A�j���[�V�����p�^�[���̐ݒ�
		}
		else if (m_nShootDelay % 30 == 28)
		{
			SetAnimPattern(0);			//�A�j���[�V�����p�^�[���̐ݒ�

			//�v���C���[�܂ł̃x�N�g�����v�Z���āA���K������
			D3DXVECTOR3 move = PlayerPos - pos;	
			D3DXVec3Normalize(&move, &move);

			//�e�𐶐�����
			CGreedBullet::Create(pos, D3DXVECTOR3(3.5f * move.x, 3.5f * move.y, 0.0f));

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_COIN);			//�T�E���h���Đ�����

			if (nLife < 15000)
			{//�̗͂�15000�ȉ��ɂȂ�����

				//=================================================================================================================
				//�v���C���[�܂ł̃x�N�g���}30�������̒e�̐���
				D3DXVECTOR3 unit = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

				float fAngle = acosf(D3DXVec3Dot(&move, &unit));

				if (PlayerPos.y < pos.y)
				{
					fAngle *= -1.0f;
				}

				D3DXVECTOR3 NewMove = D3DXVECTOR3(cosf(fAngle) * cosf(D3DX_PI / 6.0f) - sinf(fAngle) * sinf(D3DX_PI / 6.0f),
					sinf(fAngle) * cosf(D3DX_PI / 6.0f) + cosf(fAngle) * sinf(D3DX_PI / 6.0f), 0.0f);

				CGreedBullet::Create(pos, D3DXVECTOR3(3.5f * NewMove.x, 3.5f * NewMove.y, 0.0f));

				NewMove = D3DXVECTOR3(cosf(fAngle) * cosf(-D3DX_PI / 6.0f) - sinf(fAngle) * sinf(-D3DX_PI / 6.0f),
					sinf(fAngle) * cosf(-D3DX_PI / 6.0f) + cosf(fAngle) * sinf(-D3DX_PI / 6.0f), 0.0f);

				CGreedBullet::Create(pos, D3DXVECTOR3(3.5f * NewMove.x, 3.5f * NewMove.y, 0.0f));
				//==================================================================================================================

				if (nLife < 10000)
				{//�̗͂�15000�ȉ��ɂȂ�����

					//=================================================================================================================
					//�v���C���[�܂ł̃x�N�g���}60�������̒e�̐���
					NewMove = D3DXVECTOR3(cosf(fAngle) * cosf(D3DX_PI / 3.0f) - sinf(fAngle) * sinf(D3DX_PI / 3.0f),
						sinf(fAngle) * cosf(D3DX_PI / 3.0f) + cosf(fAngle) * sinf(D3DX_PI / 3.0f), 0.0f);

					CGreedBullet::Create(pos, D3DXVECTOR3(3.5f * NewMove.x, 3.5f * NewMove.y, 0.0f));

					NewMove = D3DXVECTOR3(cosf(fAngle) * cosf(-D3DX_PI / 3.0f) - sinf(fAngle) * sinf(-D3DX_PI / 3.0f),
						sinf(fAngle) * cosf(-D3DX_PI / 3.0f) + cosf(fAngle) * sinf(-D3DX_PI / 3.0f), 0.0f);

					CGreedBullet::Create(pos, D3DXVECTOR3(3.5f * NewMove.x, 3.5f * NewMove.y, 0.0f));
					//==================================================================================================================
				}
			}
		}
		else if (m_nShootDelay > 350)
		{//350�t���[�����o������
			m_nShootDelay = 0;			//�U���J�E���^�[��0�ɖ߂�
			m_state = state_normal;		//���ʂ̏�Ԃɖ߂�
		}
	}

	break;

	case CGreed::state_rage:

	{//�{��U��

		m_nShootDelay++;		//�U���J�E���^�[���C���N�������g����
		m_nCntMove++;			//�ړ��J�E���^�[���C���N�������g����

		if (m_nCntMove < 100)
		{//100�t���[���܂ŐF��ς��邾��

			if (m_nCntMove % 20 == 19)
			{//���ʂ̐F�ɐݒ肷��
				SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else if (m_nCntMove % 10 == 9)
			{//�Ԃ�����
				SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			}
		}
		else
		{//100�t���[�����o������

			SetAnimPattern(1);								//�A�j���[�V�����p�^�[���̐ݒ�
			SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	//���ʂ̐F�̐ݒ�

			if (m_nShootDelay >= 10)
			{//10�t���[������

				m_nShootDelay = 0;			//�U���J�E���^�[��0�ɖ߂�

				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_COIN);		//�T�E���h���Đ�����

				for (int nCnt = 0; nCnt < 8; nCnt++)
				{//���̓G�̎���ɂW�̒e�̐���
					CGreedBullet::Create(pos, D3DXVECTOR3(5.0f * cosf(m_fShotAngle + (nCnt * D3DX_PI / 4.0f)), 5.0f * sinf(m_fShotAngle + (nCnt * D3DX_PI / 4.0f)), 0.0f));
				}

				m_fShotAngle += m_fSumAngle;			//�U���p�̊p�x�̍X�V

				if (m_fShotAngle >= 1.0f || m_fShotAngle <= -1.0f)
				{//���܂����p�x�𒴂�����A�p�x���t�ɂ���
					m_fSumAngle *= -1.0f;
				}
			}
		}

		if (m_nCntMove >= 580)
		{//580�t���[�����o������

			m_nShootDelay = 0;			//�U���J�E���^�[��0�ɖ߂�
			m_nCntMove = 0;				//�ړ��J�E���^�[��0�ɖ߂�
			m_fShotAngle = 0.0f;		//�U���p�x��0�ɖ߂�
			m_state = state_normal;		//���ʂ̏�Ԃɖ߂�
		}
	}

	break;

	case CGreed::state_death:

	{//���S���

		m_nShootDelay++;			//�U���J�E���^�[���C���N�������g����

		if (m_nShootDelay % 20 == 1)
		{//20�t���[�����ƐF���X�V����

			D3DXCOLOR col = GetColor();

			if (col.g <= 0.5f)
			{//���ʂ̐F�ɐݒ肷��
				SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, col.a));
			}
			else
			{//�Ԃ�����
				SetColor(D3DXCOLOR(1.0f, 0.2f, 0.2f, col.a));
			}
		}

		//30�e�̐���
		if (m_nShootDelay == 130)
		{
			for (int nCnt = 0; nCnt < 30; nCnt++)
			{
				//�e�̑��x���v�Z����
				D3DXVECTOR3 move = D3DXVECTOR3((float)random(-500, 500) * 0.01f, (float)random(-500, 500) * -0.01f, 0.0f);

				//�e�̐���
				CGreedBullet::Create(pos, move);

				//�傫�������̃T�E���h���Đ�����
				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_BIG_EXPLOSION);
			}
		}

		if (m_nShootDelay == 300)
		{//300�t���[�����o������A�I�������Ԃɂ���
			m_bEnd = true;
		}
	}

	break;

	default:
		break;
	}
}
