//=============================================================================
//
// fireballPlayer.h
// Author : Ricci Alex
//
//=============================================================================

//�C���N���[�h�t�@�C��
#include "fireballPlayer.h"
#include "main.h"
#include "explosion.h"
#include "enemy.h"
#include "player.h"
#include "circleHitbox.h"
#include "application.h"
#include "sound.h"

//�R���X�g���N�^
CFireballPlayer::CFireballPlayer()
{
	//�����o�[�ϐ����N���A����
	m_fBulletAngle = 0.0f;
	m_fBulletInclination = 0.0f;
	m_BulletVector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_origin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pHitbox = nullptr;
}

//�f�X�g���N�^
CFireballPlayer::~CFireballPlayer()
{

}

//����������
HRESULT CFireballPlayer::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CObject_2D::Init()))
	{
		return -1;
	}

	//�����o�[�ϐ��̏�����
	SetLife(300);										
	m_fBulletAngle = 0.0f;								
	m_fBulletInclination = 0.0f;						
	m_BulletVector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		
	m_origin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			

	return S_OK;
}

//�I������
void CFireballPlayer::Uninit(void)
{
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}

	//��{�N���X�̏I������
	CObject_2D::Uninit();
}

//�X�V����
void CFireballPlayer::Update(void)
{
	CObject_2D::Update();								//��{�N���X�̍X�V����

	D3DXVECTOR3 move = GetMove();
	D3DXVECTOR3 pos = GetPos() + move;					//�ʒu�̍X�V

	m_fBulletInclination;
	m_BulletVector += D3DXVECTOR3(10.0f, 5.0f * (float)sin(m_fBulletAngle), 0.0f);
	m_fBulletAngle += D3DX_PI * 0.1f;

	pos.x = (m_BulletVector.x - m_origin.x) * cosf(m_fBulletInclination) - (m_BulletVector.y - m_origin.y) * sinf(m_fBulletInclination) + m_origin.x;
	pos.y = (m_BulletVector.x - m_origin.x) * sinf(m_fBulletInclination) + (m_BulletVector.y - m_origin.y) * cosf(m_fBulletInclination) + m_origin.y;

	SetPos(pos);										//�ʒu�̐ݒ�
	m_pHitbox->SetPos(pos);

	//�ړ��ʂ̍X�V
	move += GetAcceleration();							
	SetMove(move);

	int nLife = GetLife();

	nLife--;											//�����̍X�V

	if (nLife <= 0)
	{//������0�ɂȂ�����

		DestroyBullet();

		return;
	}

	if (pos.x > SCREEN_WIDTH || pos.x < 0.0f || pos.y > SCREEN_HEIGHT || pos.y < 0.0f)
	{//��ʂ��o����

		Release();										//�e������
		return;
	}

	if (Hit())
	{
		CExplosion* pExplosion = nullptr;					//�����C���X�^���X�ւ̃|�C���^

		CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_EXPLOSION);		//�����̃T�E���h�G�t�F�N�g

		pExplosion = CExplosion::Create();				//�����̐���

		pExplosion->SetPos(pos);						//�����̈ʒu�̐ݒ�

		Release();										//�e������
		return;
	}
}

//�����蔻��
bool CFireballPlayer::Hit(void)
{
	if (m_pHitbox->Hit())
	{
		return true;
	}

	return false;
}

void CFireballPlayer::SetStartingAngle(const float fAngle)
{
	m_fBulletAngle = fAngle;
}

//==================================================================================================================
//
//		�ÓI�֐�
//
//==================================================================================================================

//��������
CFireballPlayer* CFireballPlayer::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const D3DXVECTOR3 acc, const D3DXVECTOR2 Size)
{
	CFireballPlayer* pBullet = new CFireballPlayer;				//�e�𐶐�����

	if (pBullet != nullptr)
	{
		//����������
		if (FAILED(pBullet->Init()))
		{
			delete pBullet;			//���������������
			return nullptr;			//null��Ԃ�
		}

		pBullet->SetBulletType(CBullet::BULLET_PLAYER_FIREBALL);
		pBullet->SetPos(pos);									//�ʒu�̐ݒ�
		pBullet->SetMove(move);									//�ړ��ʂ̐ݒ�
		pBullet->SetAcceleration(acc);							//�����̐ݒ�
		pBullet->m_BulletVector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pBullet->m_origin = pos;

		D3DXVECTOR3 Vec, unit;
		unit = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		D3DXVec3Normalize(&Vec, &move);
		pBullet->m_fBulletInclination = (float)acos(D3DXVec3Dot(&Vec, &unit));

		if (Vec.y < unit.y)
		{
			pBullet->m_fBulletInclination *= -1.0f;
		}

		pBullet->SetTexture(CObject::TextureFireball);		//�e�N�X�`���̐ݒ�
		pBullet->SetTextureParameter(8, 4, 2, 3);			//�e�N�X�`���p�����[�^�̐ݒ菈��
		pBullet->SetSize(Size);								//�T�C�Y�̐ݒ�
		pBullet->m_BulletVector = pos;

		pBullet->m_pHitbox = CCircleHitbox::Create(pos, Size.x, CHitbox::Type_PlayerBullet);

	}

	return pBullet;						//�e��Ԃ�
} 