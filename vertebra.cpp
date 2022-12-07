//=============================================================================
//
// vertebra.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "vertebra.h"
#include "circleHitbox.h"

//�R���X�g���N�^
CVertebra::CVertebra()
{
	m_pHitbox = nullptr;
}

//�f�X�g���N�^
CVertebra::~CVertebra()
{

}

//����������
HRESULT CVertebra::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CEnemy::Init()))
	{
		return -1;
	}

	return S_OK;
}

//�I������
void CVertebra::Uninit(void)
{
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}

	//��{�N���X�̏I������
	CEnemy::Uninit();
}

//�X�V����
void CVertebra::Update(void)
{
	//��{�N���X�̍X�V����
	CObject_2D::Update();

	D3DXVECTOR3 pos = GetPos();
	m_pHitbox->SetPos(pos);
}


//==================================================================================================
//										�ÓI�֐�
//==================================================================================================

//��������
CVertebra* CVertebra::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	CVertebra* pVertebra = new CVertebra;			//�V�����G�𐶐�����

	if (pVertebra != nullptr)
	{
		//����������
		if (FAILED(pVertebra->Init()))
		{
			return nullptr;						//null��Ԃ�
		}

		pVertebra->SetObjType(CObject::OBJTYPE_ENEMY);					//�I�u�W�F�N�g�̎�ނ̐ݒ�

		pVertebra->SetPos(pos);											//�ʒu�̐ݒ�
		pVertebra->SetStartingRot(D3DX_PI * 0.5f);						//��]�p�x�̏����l�̐ݒ�
		pVertebra->SetTextureParameter(1, 1, 1, INT_MAX);				//�e�N�X�`���p�����[�^�̐ݒ�
		pVertebra->SetSize(size);										//�T�C�Y�̐ݒ�

		pVertebra->SetMove(D3DXVECTOR3(-1.5f, 0.0f, 0.0f));				//���x�̐ݒ�
		pVertebra->SetAcceleration(D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//�����̐ݒ�
		pVertebra->SetSubtype(CObject::ENEMYTYPE_VERTEBRA);				//�G�̎�ނ̐ݒ�

		pVertebra->SetTexture(TextureVertebra);							//�e�N�X�`���̐ݒ�

		pVertebra->m_pHitbox = CCircleHitbox::Create(pos, size.x * 0.3f, CHitbox::Type_Enemy);
	}

	return pVertebra;
} 