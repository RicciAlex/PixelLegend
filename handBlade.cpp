//=============================================================================
//
// handBlade.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "handBlade.h"
#include "circleHitbox.h"

//�R���X�g���N�^
CHandBlade::CHandBlade()
{
	//�����o�[�ϐ����N���A����
	m_pHitbox = nullptr;
}

//�f�X�g���N�^
CHandBlade::~CHandBlade()
{

}

//����������
HRESULT CHandBlade::Init(void)
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
void CHandBlade::Uninit(void)
{
	//�q�b�g�{�b�N�X�̔j��
	if (m_pHitbox != nullptr)
	{//null�`�F�b�N
		m_pHitbox->Release();			//���������������
		m_pHitbox = nullptr;			//�|�C���^��null�ɂ���
	}

	//��{�N���X�̏I������
	CBullet::Uninit();
}

//�X�V����
void CHandBlade::Update(void)
{
	//��{�N���X�̍X�V����
	CObject_2D::Update();

	D3DXVECTOR3 pos, move;
	pos = GetPos();				//�ʒu�̎擾
	move = GetMove();			//���x�̎擾

	//�O�ʂ��o��O�A���˂�����
	if (pos.y + move.y <= 0.0f || pos.y + move.y >= (float)SCREEN_HEIGHT)
	{
		move.y *= -1.0f;
		SetMove(move);
	}
	if (pos.x <= 0.0f || pos.x >= (float)SCREEN_WIDTH)
	{
		Release();
		return;
	}

	//�ʒu�̍X�V
	int nLife = GetLife() - 1;

	if (nLife <= 0)
	{//�̗͂�0�ȉ��ɂȂ�����A����
		Release();
		return;
	}
	
	SetLife(nLife);			//�̗͂̐ݒ�

	//�q�b�g�{�b�N�X�̍X�V����
	if (m_pHitbox != nullptr)
	{//null�`�F�b�N

		m_pHitbox->SetPos(pos);		//�q�b�g�{�b�N�X�̈ʒu�̍X�V

		if (m_pHitbox->Hit())
		{//�����Ɠ���������A����
			Release();
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
CHandBlade* CHandBlade::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CHandBlade* pBullet = new CHandBlade;		//�C���X�^���X�𐶐�����

	if (FAILED(pBullet->Init()))
	{//����������
		return nullptr;
	}

	pBullet->SetPos(pos);							//�ʒu�̐ݒ�
	pBullet->SetMove(move);							//���x�̐ݒ�
	pBullet->SetSize(D3DXVECTOR2(20.0f, 20.0f));	//�T�C�Y�̐ݒ�
	pBullet->SetRotation(-D3DX_PI * 0.025f);		//�����̏����l�̐ݒ�
	pBullet->SetTexture(CObject::TextureHandBlade);	//�e�N�X�`���̐ݒ�
	pBullet->SetTextureParameter(1, 1, 1, INT_MAX);	//�e�N�X�`���p�����[�^�̐ݒ�
	pBullet->SetLife(300);							//�̗͂̐ݒ�

	//�q�b�g�{�b�N�X�̐���
	pBullet->m_pHitbox = CCircleHitbox::Create(pos, 20.0f, CHitbox::Type_EnemyBullet);

	return pBullet;					//���������C���X�^���X��Ԃ�
}