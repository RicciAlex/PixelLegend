//=============================================================================
//
// bone.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "bone.h"
#include "squareHitbox.h"

//�R���X�g���N�^
CBone::CBone()
{
	//�����o�[�ϐ����N���A����
	m_bBroken = false;

	m_pHitbox = nullptr;
}

//�f�X�g���N�^
CBone::~CBone()
{

}

//����������
HRESULT CBone::Init(void)
{
	if (FAILED(CBullet::Init()))
	{//��{�N���X�̏���������
		return -1;
	}

	//�����o�[�ϐ�������������
	m_bBroken = false;

	m_pHitbox = nullptr;

	return S_OK;
}

//�I������
void CBone::Uninit(void)
{
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}

	CBullet::Uninit();
}

//�X�V����
void CBone::Update(void)
{
	//��{�N���X�̍X�V����
	CObject_2D::Update();

	D3DXVECTOR3 pos = GetPos();		//�ʒu�̎擾

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

	//��ʂ��o�Ȃ��悤�ɂ���
	if (pos.x <= 60.0f)
	{
		pos.x = 60.0f;
	}
	else if (pos.x >= (float)SCREEN_WIDTH - 60)
	{
		pos.x = (float)SCREEN_WIDTH - 60;
	}

	if (pos.y <= 60.0f)
	{
		pos.y = 60.0f;
	}
	else if(pos.y >= (float)SCREEN_HEIGHT - 60)
	{
		pos.y = (float)SCREEN_HEIGHT - 60;
	}
	
	if (pos.x <= 60.0f || pos.x >= (float)SCREEN_WIDTH - 60 || pos.y <= 60.0f || pos.y >= (float)SCREEN_HEIGHT - 60)
	{//�ǂƓ���������
		if (!m_bBroken)
		{//�܂��܂�Ă��Ȃ�������A�܂��
			m_bBroken = true;
			Split();
			Release();
			return;
		}
		else
		{//�����܂ꂽ�ꍇ�A����
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
CBone* CBone::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move)
{
	CBone* pBullet = new CBone;			//�C���X�^���X�𐶐�����

	if (FAILED(pBullet->Init()))
	{//����������
		return nullptr;
	}

	pBullet->SetPos(pos);												//�ʒu�̐ݒ�
	pBullet->SetSize(D3DXVECTOR2(35.0f, 10.7f));						//�T�C�Y�̐ݒ�
	pBullet->SetMove(move);												//���x�̐ݒ�
	pBullet->SetTexture(CObject_2D::TextureBone);						//�e�N�X�`���̐ݒ�
	pBullet->SetTextureParameter(1, 1, 2, INT_MAX);						//�e�N�X�`���p�����[�^�̐ݒ�
	pBullet->SetRotation((float)random(-10, 10) * 0.0025f * D3DX_PI);	//��]������
	pBullet->SetStartingRot(D3DX_PI * 0.5f);							//�����̏����l�̐ݒ�
	pBullet->m_bBroken = false;											//�܂�Ă��Ȃ���Ԃɂ���

	//�q�b�g�{�b�N�X�̐���
	pBullet->m_pHitbox = CSquareHitbox::Create(D3DXVECTOR3(pos), D3DXVECTOR2(49.0f, 15.0f), CHitbox::Type_EnemyBullet);

	return pBullet;			//���������C���X�^���X��Ԃ�
}


//=============================================================================
//
//							�v���C�x�[�g�֐�
//
//=============================================================================


//�܂�鏈��
void CBone::Split(void)
{
	D3DXVECTOR3 pos = GetPos();								
	D3DXVECTOR3 move1 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		
	D3DXVECTOR3 move2 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		
	D3DXVECTOR3 V = GetMove();								
	float fSpeed = D3DXVec3Length(&V);						

	//�ʒu�ɂ���ĐV�����e�̑��x��ݒ肷��
	if (pos.x <= 61.0f || pos.x >= (float)SCREEN_WIDTH - 61.0f)
	{
		move1.x = GetMove().x * -1.0f;
		move2.x = GetMove().x * -1.0f;

		move1.y = random(-10, 10) * 0.1f;
		move2.y = -move1.y;
	}
	else if (pos.y <= 61.0f || pos.y >= (float)SCREEN_HEIGHT - 61.0f)
	{
		move1.y = GetMove().y * -1.0f;
		move2.y = GetMove().y * -1.0f;

		move1.x = random(5, 10) * 0.1f;
		move2.x = -move1.x;
	}

	D3DXVec3Normalize(&move1, &move1);
	D3DXVec3Normalize(&move2, &move2);

	move1.x *= fSpeed;
	move1.y *= fSpeed;
	move2.x *= fSpeed;
	move2.y *= fSpeed;

	//�T�C�Y�𒲐�����
	D3DXVECTOR2 size = GetSize();
	size.x *= 0.5f;

	//�V�����e�𐶐����āA�K�v�ȃp�����[�^��ݒ肷��
	CBone* pBullet = CBone::Create(pos, move1);
	pBullet->SetTextureParameter(1, 2, 2, INT_MAX);
	pBullet->SetAnimPattern(1);
	pBullet->m_bBroken = true;
	pBullet->SetSize(size);
	pBullet->m_pHitbox->SetSize(size);

	pBullet = CBone::Create(pos, move2);
	pBullet->SetTextureParameter(1, 2, 2, INT_MAX);
	pBullet->SetAnimPattern(2);
	pBullet->m_bBroken = true;
	pBullet->SetSize(size);
	pBullet->m_pHitbox->SetSize(size);
}