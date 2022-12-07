//=============================================================================
//
// thunderEnemy.cpp
// Author : Ricci Alex
//
//=============================================================================

//�C���N���[�h�t�@�C��
#include "thunderEnemy.h"
#include "player.h"
#include "squareHitbox.h"
#include "application.h"
#include "sound.h"


CThunderEnemy::CThunderEnemy()
{
	m_pHitbox = nullptr;
}

CThunderEnemy::~CThunderEnemy()
{

}

//����������
HRESULT CThunderEnemy::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CObject_2D::Init()))
	{
		return -1;
	}

	SetLife(24);
	CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_THUNDER);		//���̃T�E���h�G�t�F�N�g

	return S_OK;
}

//�I������
void CThunderEnemy::Uninit(void)
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
void CThunderEnemy::Update(void)
{
	CObject_2D::Update();								//��{�N���X�̍X�V����

	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Hit();
	}

	int nLife = GetLife();

	nLife--;											//�����̍X�V

	if (nLife <= 0)
	{//������0�ɂȂ�����

		DestroyBullet();

		return;
	}
	else
	{
		SetLife(nLife);
	}
}

//==================================================================================================================
//
//		�ÓI�֐� 
//
//==================================================================================================================

//��������
CThunderEnemy* CThunderEnemy::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const D3DXVECTOR3 acc, const D3DXVECTOR2 Size)
{
	CThunderEnemy* pBullet = new CThunderEnemy;				//�e�𐶐�����

	if (pBullet != nullptr)
	{
		//����������
		if (FAILED(pBullet->Init()))
		{
			delete pBullet;			//���������������
			return nullptr;			//null��Ԃ�
		}

		pBullet->SetBulletType(CBullet::BULLET_THUNDER);
		pBullet->SetPos(pos);									//�ʒu�̐ݒ�
		pBullet->SetMove(move);									//�ړ��ʂ̐ݒ�
		pBullet->SetAcceleration(acc);							//�����̐ݒ�

		pBullet->SetTexture(CObject::TextureThunder);		//�e�N�X�`���̐ݒ�
		pBullet->SetTextureParameter(8, 4, 2, 3);			//�e�N�X�`���p�����[�^�̐ݒ菈��
		pBullet->SetSize(Size);								//�T�C�Y�̐ݒ�
		pBullet->SetStartingRot(D3DX_PI * 0.5f);			//��]�p�x�̐ݒ�

		pBullet->m_pHitbox = CSquareHitbox::Create(pos, Size, CHitbox::Type_EnemyBullet);

	}

	return pBullet;						//�e��Ԃ�
}