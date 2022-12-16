//=============================================================================
//
// balloon.cpp
// Author : Ricci Alex
//
//=============================================================================

//�C���N���[�h�t�@�C��
#include "balloon.h"
#include "circleHitbox.h"
#include "application.h"
#include "sound.h"

//�R���X�g���N�^
CBalloonBullet::CBalloonBullet()
{
	//�����o�[�ϐ����N���A����
	m_pHitbox = nullptr;
}

//�f�X�g���N�^
CBalloonBullet::~CBalloonBullet()
{

}

//����������
HRESULT CBalloonBullet::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CBullet::Init()))
	{
		return -1;
	}

	//�����o�[�ϐ�������������
	m_pHitbox = nullptr;

	return S_OK;
}

//�I������
void CBalloonBullet::Uninit(void)
{
	//�q�b�g�{�b�N�X�̔j��
	if (m_pHitbox != nullptr)
	{//null�`�F�b�N
		m_pHitbox->Release();		//���������������
		m_pHitbox = nullptr;		//�|�C���^��null�ɂ���
	}

	//��{�N���X�̏I������
	CBullet::Uninit();
}

//�X�V����
void CBalloonBullet::Update(void)
{
	//�q�b�g�{�b�N�X�̍X�V����
	if (m_pHitbox)
	{
		m_pHitbox->SetPos(GetPos());			//�q�b�g�{�b�N�X�̈ʒu�̍X�V

		if (m_pHitbox->Hit())
		{//�����Ɠ���������A

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_EXPLOSION);		//�����̃T�E���h�G�t�F�N�g
			Release();				//�j������
			return;
		}
	}

	//��{�N���X�̍X�V����
	CBullet::Update();
}


//=============================================================================
//
//								�ÓI�֐�
//
//=============================================================================



//��������
CBalloonBullet* CBalloonBullet::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, D3DXCOLOR col)
{
	CBalloonBullet* pBullet = new CBalloonBullet;		//�C���X�^���X�𐶐�����

	if (FAILED(pBullet->Init()))
	{//����������
		return nullptr;
	}

	pBullet->SetPos(pos);								//�ʒu�̐ݒ�
	pBullet->SetMove(move);								//���x�̐ݒ�
	pBullet->SetSize(D3DXVECTOR2(25.0f, 45.0f));		//�T�C�Y�̐ݒ�
	pBullet->SetLife(random(120, 300));					//�����̐ݒ�
	pBullet->SetColor(col);								//�F�̐ݒ�
	pBullet->SetTexture(CObject::TextureBalloon);		//�e�N�X�`���̐ݒ�
	pBullet->SetTextureParameter(1, 1, 1, INT_MAX);		//�e�N�X�`���p�����[�^�̐ݒ�
	pBullet->SetStartingRot(D3DX_PI * 0.5f);			//�����̏����l�̐ݒ�

	pBullet->m_pHitbox = CCircleHitbox::Create(pos, 25.0f, CHitbox::Type_EnemyBullet);		//�q�b�g�{�b�N�X�̐���

	return pBullet;			//���������C���X�^���X��Ԃ�
}