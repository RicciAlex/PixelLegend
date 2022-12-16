//=============================================================================
//
// laugh.cpp
// Author : Ricci Alex
//
//=============================================================================

//�C���N���[�h�t�@�C��
#include "laugh.h"
#include "squareHitbox.h"
#include "Letter.h"

//�R���X�g���N�^
CLaughBullet::CLaughBullet()
{
	//�����o�[�ϐ����N���A����
	m_pHitbox = nullptr;
}

//�f�X�g���N�^
CLaughBullet::~CLaughBullet()
{

}

//����������
HRESULT CLaughBullet::Init(void)
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
void CLaughBullet::Uninit(void)
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
void CLaughBullet::Update(void)
{
	D3DXVECTOR3 pos = GetPos() + GetMove();		//�ʒu�̍X�V
	D3DXVECTOR2 size = GetSize();				//�T�C�Y�̎擾
	
	//��{�N���X�̍X�V
	CBullet::Update();

	if (pos.x + size.x > 0.0f && pos.x + size.x < (float)SCREEN_WIDTH &&
		pos.y + size.y > 0.0f && pos.y - size.y < (float)SCREEN_HEIGHT)
	{//��ʓ���������

		//�q�b�g�{�b�N�X�̍X�V����
		if (m_pHitbox != nullptr)
		{//null�`�F�b�N

			m_pHitbox->SetPos(GetPos());		//�q�b�g�{�b�N�X�̈ʒu�̍X�V

			if (m_pHitbox->Hit())
			{//�����Ɠ���������A����
				Release();
				return;
			}
		}
	}
}



//=============================================================================
//
//								�ÓI�֐�
//
//=============================================================================



//��������
CLaughBullet* CLaughBullet::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move)
{
	CLaughBullet* pBullet = new CLaughBullet;		//�C���X�^���X�𐶐�����

	if (FAILED(pBullet->Init()))
	{//����������
		return nullptr;
	}

	pBullet->SetPos(pos);								//�ʒu�̐ݒ�
	pBullet->SetSize(D3DXVECTOR2(45.0f, 40.0f));		//�T�C�Y�̐ݒ�
	pBullet->SetMove(move);								//���x�̐ݒ�
	pBullet->SetLife(300);								//�̗͂̐ݒ�
	pBullet->SetStartingRot(D3DX_PI * 0.5f);			//�����̏����l�̐ݒ�
														
	pBullet->SetTexture(CObject::TextureLaugh);			//�e�N�X�`���̐ݒ�
	pBullet->SetTextureParameter(1, 1, 1, INT_MAX);		//�e�N�X�`���p�����[�^�̐ݒ�

	//�q�b�g�{�b�N�X�̐���
	pBullet->m_pHitbox = CSquareHitbox::Create(pos, D3DXVECTOR2(40.0f, 35.0f), CHitbox::Type_EnemyBullet);

	return pBullet;				//���������C���X�^���X��Ԃ�
}