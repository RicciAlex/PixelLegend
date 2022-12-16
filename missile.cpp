//=============================================================================
//
// missile.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "missile.h"
#include "squareHitbox.h"
#include "player.h"
#include "application.h"
#include "sound.h"

//�R���X�g���N�^
CMissile::CMissile()
{
	//�����o�[�ϐ����N���A����
	m_state = state_max;
	m_pHitbox = nullptr;
}

//�f�X�g���N�^
CMissile::~CMissile()
{

}

//����������
HRESULT CMissile::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CBullet::Init()))
	{
		return -1;
	}

	//�����o�[�ϐ�������������
	m_state = state_ascend;
	m_pHitbox = nullptr;

	return S_OK;
}

//�I������
void CMissile::Uninit(void)
{
	//�q�b�g�{�b�N�X�̔j������
	if (m_pHitbox != nullptr)
	{//null�`�F�b�N
		m_pHitbox->Release();		//���������������
		m_pHitbox = nullptr;		//�|�C���^��null�ɂ���
	}

	//��{�N���X�̏I������
	CBullet::Uninit();
}

//�X�V����
void CMissile::Update(void)
{
	CObject_2D::Update();				//��{�N���X�̍X�V����
			
	D3DXVECTOR3 pos = GetPos();			//�ʒu�̎擾
	D3DXVECTOR2 size = GetSize();		//�T�C�Y�̎擾

	switch (m_state)
	{
	case CMissile::state_ascend:

		if (pos.y <= -150.0f)
		{//��ʂ��o����

			SetStartingRot(D3DX_PI);						//�������t�ɂ���
			pos.x = CPlayer::GetPlayer()->GetPos().x;		//�v���C���[�̓���X���W�ɐݒ肷��

			//���x��0�ɂ���
			D3DXVECTOR3 move = GetMove();
			move.x = 0.0f;
			move.y = 0.0f;

			SetAcceleration(D3DXVECTOR3(0.0f, 0.2f, 0.0f));		//�����̐ݒ�
			SetPos(pos);										//�ʒu�̐ݒ�
			SetMove(move);										//���x�̐ݒ�
			
			m_state = state_descend;							//�������Ԃɂ���
		}

		break;

	case CMissile::state_descend:

		if (pos.y - 200.0f >= (float)SCREEN_HEIGHT)
		{//��ʂ��o����A����
			Release();
			return;
		}

		break;

	case state_strike:



		break;

	default:
		break;
	}

	//�q�b�g�{�b�N�X�̍X�V����
	if (m_pHitbox != nullptr)
	{//null�`�F�b�N

		m_pHitbox->SetPos(GetPos());		//�q�b�g�{�b�N�X�̈ʒu�̍X�V

		if (m_pHitbox->Hit())
		{//�����Ɠ���������

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_BIG_EXPLOSION);	//�����̃T�E���h���Đ�����
			Release();																//�j������
			return;
		}
	}
}


//=============================================================================
//
//								�ÓI�֐�
//
//=============================================================================


//��������
CMissile* CMissile::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move)
{
	CMissile* pBullet = new CMissile;		//�C���X�^���X�𐶐�����

	if (FAILED(pBullet->Init()))
	{//����������
		return nullptr;
	}

	pBullet->SetPos(pos);							//�ʒu�̐ݒ�
	pBullet->SetMove(move);							//���x�̐ݒ�
	pBullet->SetSize(D3DXVECTOR2(67.5f, 16.5f));	//�T�C�Y�̐ݒ�
	pBullet->SetTexture(CObject::TextureMissile);	//�e�N�X�`���̐ݒ�
	pBullet->SetTextureParameter(2, 1, 2, 15);		//�e�N�X�`���p�����[�^�̐ݒ�
	pBullet->SetPriority(2);						//�v���C�I���e�B�̐ݒ�

	//�q�b�g�{�b�N�X�̐���
	pBullet->m_pHitbox = CSquareHitbox::Create(pos ,D3DXVECTOR2(30.0f, 8.0f), CHitbox::Type_EnemyBullet);

	return pBullet;					//���������C���X�^���X��Ԃ�
}

//��������
CMissile* CMissile::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const D3DXVECTOR3 acc)
{
	CMissile* pBullet = new CMissile;			//�C���X�^���X�𐶐�����

	if (FAILED(pBullet->Init()))
	{//����������
		return nullptr;
	}

	pBullet->SetPos(pos);								//�ʒu�̐ݒ�
	pBullet->SetMove(move);								//���x�̐ݒ�
	pBullet->SetSize(D3DXVECTOR2(67.5f, 16.5f));		//�T�C�Y�̐ݒ�
	pBullet->SetTexture(CObject::TextureMissile);		//�e�N�X�`���̐ݒ�
	pBullet->SetTextureParameter(2, 1, 2, 15);			//�e�N�X�`���p�����[�^�̐ݒ�
	pBullet->SetPriority(2);							//�v���C�I���e�B�̐ݒ�
	pBullet->SetAcceleration(acc);						//�����̐ݒ�
	pBullet->m_state = state_strike;					//��Ԃ̐ݒ�
	pBullet->SetStartingRot(D3DX_PI * 0.5f);			//�����̏����l�̐ݒ�

														//�q�b�g�{�b�N�X�̐���
	pBullet->m_pHitbox = CSquareHitbox::Create(pos, D3DXVECTOR2(30.0f, 8.0f), CHitbox::Type_EnemyBullet);

	return pBullet;				//���������C���X�^���X��Ԃ�
}