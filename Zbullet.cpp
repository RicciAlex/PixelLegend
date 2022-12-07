//=============================================================================
//
// Zbullet.cpp
// Author : Ricci Alex
//
//=============================================================================

//�C���N���[�h�t�@�C��
#include "Zbullet.h"
#include "squareHitbox.h"

//�R���X�g���N�^
CZBullet::CZBullet()
{
	//�����o�[�ϐ����N���A����
	m_nCntSize = 0;
	m_fGrowth = 0.0f;
	m_pHitbox = nullptr;
}

//�f�X�g���N�^
CZBullet::~CZBullet()
{

}

//����������
HRESULT CZBullet::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CBullet::Init()))
	{
		return -1;
	}

	//�����o�[�ϐ��̏�����
	m_nCntSize = 0;
	m_fGrowth = 1.0f;

	return S_OK;
}

//�I������
void CZBullet::Uninit(void)
{
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}

	//��{�N���X�̏I������
	CBullet::Uninit();
}

//�X�V����
void CZBullet::Update(void)
{
	//�T�C�Y�̕ύX
	m_nCntSize++;

	if (m_nCntSize >= 30)
	{
		m_nCntSize = 0;

		m_fGrowth *= -1.0f;
	}

	D3DXVECTOR2 size = GetSize();
	size += D3DXVECTOR2(m_fGrowth, m_fGrowth);
	SetSize(size);


	m_pHitbox->SetPos(GetPos());				//�ʒu�̎擾
	m_pHitbox->SetSize(size);					//�T�C�Y�̎擾

	if (m_pHitbox->Hit())
	{//�v���C���[�Ɠ��������ꍇ�A����
		Release();
		return;
	}

	//��{�N���X�̍X�V����
	CBullet::Update();
}


//=============================================================================
//�ÓI�֐�
//=============================================================================

//��������
CZBullet* CZBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CZBullet* pBullet = new CZBullet;					//�V�����e�𐶐�����

	//����������
	if (FAILED(pBullet->Init()))
	{
		return nullptr;
	}

	pBullet->SetPos(pos);									//�ʒu�̐ݒ�
	pBullet->SetMove(move);									//���x�̐ݒ�

	pBullet->SetTexture(CObject::TextureLetters);			//�e�N�X�`���̐ݒ�
	pBullet->SetTextureParameter(26, 13, 2, INT_MAX);		//�e�N�X�`���p�����[�^�̐ݒ菈��
	pBullet->SetAnimPattern(25);							//�A�j���[�V�����p�^�[���̐ݒ�
	pBullet->SetSize(D3DXVECTOR2(35.0f, 35.0f));			//�T�C�Y�̐ݒ�

	pBullet->SetStartingRot((D3DX_PI * 0.5f));				//��]�p�x�̐ݒ�

	pBullet->m_pHitbox = CSquareHitbox::Create(pos, D3DXVECTOR2(31.0f, 31.0f), CHitbox::Type_EnemyBullet);

	return pBullet;											//�e��Ԃ�
} 