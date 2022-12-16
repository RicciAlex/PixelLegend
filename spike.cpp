//=============================================================================
//
// spike.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "spike.h"
#include "squareHitbox.h"

//�R���X�g���N�^
CSpike::CSpike()
{
	//�����o�[�ϐ����N���A����
	m_pHitbox = nullptr;
}

//�f�X�g���N�^
CSpike::~CSpike()
{

}

//����������
HRESULT CSpike::Init(void)
{
	if (FAILED(CBullet::Init()))
	{//��{�N���X�̏���������
		return -1;
	}

	//�����o�[�ϐ�������������
	m_pHitbox = nullptr;

	return S_OK;
}

//�I������
void CSpike::Uninit(void)
{
	//�q�b�g�{�b�N�X�̔j������
	if (m_pHitbox != nullptr)
	{//null�`�F�b�N
		m_pHitbox->Release();			//���������������
		m_pHitbox = nullptr;			//�|�C���^��null�ɂ���
	}

	//��{�N���X�̏I������
	CBullet::Uninit();
}

//�X�V����
void CSpike::Update(void)
{
	//�q�b�g�{�b�N�X�̍X�V����
	if (m_pHitbox != nullptr)
	{//null�`�F�b�N

		m_pHitbox->SetPos(GetPos());		//�q�b�g�{�b�N�X�̈ʒu�̍X�V
		
		if (m_pHitbox->Hit())
		{//�����Ɠ���������

			Release();			//�j������
			return;				
		}
	}

	//���x�Ɖ������擾���āA��ׂāA���x�̌������t�ɂȂ�����A����
	D3DXVECTOR3 move, acc;
	move = GetMove();
	acc = GetAcceleration();

	if (move.x * acc.x > 0 || move.y * acc.y > 0)
	{
		Release();
		return;
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
CSpike* CSpike::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move)
{
	CSpike* pBullet = new CSpike;			//�C���X�^���X�𐶐�����

	if (FAILED(pBullet->Init()))
	{//����������
		return nullptr;
	}

	pBullet->SetPos(pos);								//�ʒu�̐ݒ�
	pBullet->SetMove(move);								//���x�̐ݒ�
	pBullet->SetSize(D3DXVECTOR2(10.0f, 13.7f));		//�T�C�Y�̐ݒ�
	pBullet->SetTexture(CObject::TextureSpike);			//�e�N�X�`���̐ݒ�
	pBullet->SetTextureParameter(1, 1, 1, INT_MAX);		//�e�N�X�`���p�����[�^�̐ݒ�
	pBullet->SetStartingRot(D3DX_PI * 0.5f);			//�����̏����l�̐ݒ�
	
	//�������v�Z���āA�ݒ肷��
	D3DXVECTOR3 acc;

	D3DXVec3Normalize(&acc, &move);

	float fLenght = D3DXVec3Length(&move);
	fLenght *= -0.01f;

	acc.x *= fLenght;
	acc.y *= fLenght;

	pBullet->SetAcceleration(acc);

	//�q�b�g�{�b�N�X�̐���
	pBullet->m_pHitbox = CSquareHitbox::Create(pos, D3DXVECTOR2(9.0f, 12.0f), CHitbox::Type_EnemyBullet);

	return pBullet;					//���������C���X�^���X��Ԃ�
}