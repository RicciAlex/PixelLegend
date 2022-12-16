//=============================================================================
//
// greedBullet.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "greedBullet.h"
#include "circleHitbox.h"

//�R���X�g���N�^
CGreedBullet::CGreedBullet()
{
	//�����o�[�ϐ����N���A����
	m_pHitbox = nullptr;
}

//�f�X�g���N�^
CGreedBullet::~CGreedBullet()
{

}

//����������
HRESULT CGreedBullet::Init(void)
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
void CGreedBullet::Uninit(void)
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
void CGreedBullet::Update(void)
{
	//��{�N���X�̍X�V����
	CObject_2D::Update();

	//�̗͂̍X�V
	int nLife = GetLife();
	nLife--;

	if (nLife <= 0)
	{//�̗͂�0�ȉ��ɂȂ�����A����
		Release();
		return;
	}

	D3DXVECTOR3 pos = GetPos();		//�ʒu�̎擾

	if (pos.y >= 850.0f || pos.x <= -400.0f || pos.x >= 1700.0f)
	{//��ʂ��o����A����
		Release();
		return;
	}

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
CGreedBullet* CGreedBullet::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move)
{
	CGreedBullet* pBullet = new CGreedBullet;		//�C���X�^���X�𐶐�����

	if (FAILED(pBullet->Init()))
	{//����������
		return nullptr;
	}

	pBullet->SetPos(pos);							//�ʒu�̐ݒ�
	pBullet->SetMove(move);							//���x�̐ݒ�
	pBullet->SetSize(D3DXVECTOR2(13.0f, 13.0f));	//�T�C�Y�̐ݒ�
	pBullet->SetRotation((float)random(-100, 100) * 0.001f * D3DX_PI);		//��]������
	pBullet->SetLife(800);							//�̗͂̐ݒ�

	//�����_���Ńe�N�X�`����ݒ肷��
	int nRand = random(1, 10);

	if (nRand == 1)
	{//10%�͕��
		pBullet->SetTexture(CObject::TextureJewel);
		pBullet->SetTextureParameter(1, 3, 2, INT_MAX);
		pBullet->SetAnimPattern(random(0, 5));
	}
	else
	{//90%�̓R�C��
		pBullet->SetTexture(CObject::TextureCoin);
		pBullet->SetTextureParameter(1, 3, 2, INT_MAX);
		pBullet->SetAnimPattern(random(0, 5));
	}

	//�q�b�g�{�b�N�X�̐���
	pBullet->m_pHitbox = CCircleHitbox::Create(pos, 17.0f, CHitbox::Type_EnemyBullet);

	return pBullet;				//���������C���X�^���X��Ԃ�
}

//��������
CGreedBullet* CGreedBullet::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const D3DXVECTOR3 acc)
{
	CGreedBullet* pBullet = new CGreedBullet;			//�C���X�^���X�𐶐�����

	if (FAILED(pBullet->Init()))
	{//����������
		return nullptr;
	}

	pBullet->SetPos(pos);							//�ʒu�̐ݒ�
	pBullet->SetMove(move);							//���x�̐ݒ�
	pBullet->SetAcceleration(acc);					//�����̐ݒ�
	pBullet->SetSize(D3DXVECTOR2(13.0f, 13.0f));	//�T�C�Y�̐ݒ�
	pBullet->SetRotation((float)random(-100, 100) * 0.001f * D3DX_PI);		//��]������
	pBullet->SetLife(800);							//�̗͂̐ݒ�

	//�����_���Ńe�N�X�`����ݒ肷��
	int nRand = random(1, 10);

	if (nRand == 1)
	{//10%�͕��
		pBullet->SetTexture(CObject::TextureJewel);
		pBullet->SetTextureParameter(1, 3, 2, INT_MAX);
		pBullet->SetAnimPattern(random(0, 5));
	}
	else
	{//90%�̓R�C��
		pBullet->SetTexture(CObject::TextureCoin);
		pBullet->SetTextureParameter(1, 3, 2, INT_MAX);
		pBullet->SetAnimPattern(random(0, 5));
	}

	//�q�b�g�{�b�N�X�̐���
	pBullet->m_pHitbox = CCircleHitbox::Create(pos, 17.0f, CHitbox::Type_EnemyBullet);

	return pBullet;			//���������C���X�^���X��Ԃ�
}