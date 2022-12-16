//=============================================================================
//
// spikeBomb.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "spikeBomb.h"
#include "circleHitbox.h"
#include "spike.h"

//�R���X�g���N�^
CSpikeBomb::CSpikeBomb()
{
	//�����o�[�ϐ����N���A����
	m_pHitbox = nullptr;
}

//�f�X�g���N�^
CSpikeBomb::~CSpikeBomb()
{

}

//����������
HRESULT CSpikeBomb::Init(void)
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
void CSpikeBomb::Uninit(void)
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
void CSpikeBomb::Update(void)
{
	//�q�b�g�{�b�N�X�̍X�V����
	if (m_pHitbox != nullptr)
	{//null�`�F�b�N

		m_pHitbox->SetPos(GetPos());			//�q�b�g�{�b�N�X�̈ʒu�̐ݒ�

		if (m_pHitbox->Hit())
		{//����������Ԃ�������

			//�g�Q�^�̒e��4�������āA�����̏����l��ݒ肷��
			CSpike* pBullet = CSpike::Create(GetPos(), D3DXVECTOR3(0.0f, -1.0f, 0.0f));
			pBullet = CSpike::Create(GetPos(), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
			pBullet->SetStartingRot(-D3DX_PI * 0.5f);
			pBullet = CSpike::Create(GetPos(), D3DXVECTOR3(-1.0f, 0.0f, 0.0f));
			pBullet->SetStartingRot(D3DX_PI);
			pBullet = CSpike::Create(GetPos(), D3DXVECTOR3(1.0f, 0.0f, 0.0f));
			pBullet->SetStartingRot(0.0f);

			Release();							//�j������
			return;
		}
	}

	int nLife = GetLife();		//�̗͂̎擾
	nLife--;					//�̗͂̍X�V

	if (nLife <= 0)
	{//�̗͂�0�ȉ��ɂȂ�����

		//�g�Q�^�̒e��4�������āA�����̏����l��ݒ肷��
		CSpike* pBullet = CSpike::Create(GetPos(), D3DXVECTOR3(0.0f, -1.0f, 0.0f));
		pBullet = CSpike::Create(GetPos(), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
		pBullet->SetStartingRot(-D3DX_PI * 0.5f);
		pBullet = CSpike::Create(GetPos(), D3DXVECTOR3(-1.0f, 0.0f, 0.0f));
		pBullet->SetStartingRot(D3DX_PI);
		pBullet = CSpike::Create(GetPos(), D3DXVECTOR3(1.0f, 0.0f, 0.0f));
		pBullet->SetStartingRot(0.0f);

		Release();				//�j������
		return;
	}
	else
	{//�̗͂�0�ȏゾ������

		SetLife(nLife);			//�̗͂̐ݒ�
	}

	CBullet::Update();			//��{�N���X�̍X�V����
}


//=============================================================================
//
//								�ÓI�֐�
//
//=============================================================================


//��������
CSpikeBomb* CSpikeBomb::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CSpikeBomb* pBullet = new CSpikeBomb;		//�C���X�^���X�𐶐�����

	if (FAILED(pBullet->Init()))
	{//����������
		return nullptr;
	}

	pBullet->SetPos(pos);									//�ʒu�̐ݒ�
	pBullet->SetSize(D3DXVECTOR2(20.0f, 20.0f));			//�T�C�Y�̐ݒ�
	pBullet->SetMove(move);									//���x�̐ݒ�
	pBullet->SetRotation(-D3DX_PI * 0.05f);					//�����̏����l�̐ݒ�
	pBullet->SetTexture(CObject::TextureSpikeBomb);			//�e�N�X�`���̐ݒ�
	pBullet->SetTextureParameter(1, 1, 1, INT_MAX);			//�e�N�X�`���p�����[�^�̐ݒ�
	pBullet->SetLife(90);									//�̗͂̐ݒ�

	//�q�b�g�{�b�N�X�̐ݒ�
	pBullet->m_pHitbox = CCircleHitbox::Create(pos, 10.0f, CHitbox::Type_EnemyBullet);

	return pBullet;				//���������C���X�^���X��Ԃ�
}