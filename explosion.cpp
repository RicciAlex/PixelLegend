//=============================================================================
//
// explosion.cpp
// Author : Ricci Alex
//
//=============================================================================

//�C���N���[�h�t�@�C��
#include "explosion.h"

//�R���X�g���N�^
CExplosion::CExplosion()
{
	//�����o�[�ϐ����N���A����
	m_nLastPattern = 0;
}

//�f�X�g���N�^
CExplosion::~CExplosion()
{

}

//����������
HRESULT CExplosion::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CObject_2D::Init()))
	{
		return -1;
	}

	SetTexture(CObject::TextureExplosion);				//�e�N�X�`���̐ݒ�
	SetTextureParameter(24, 5, 5, 2);			//�e�N�X�`���p�����[�^�̐ݒ菈��
	SetSize(D3DXVECTOR2(20.0f, 20.0f));			//�T�C�Y�̏�����
												
	m_nLastPattern = 0;							//�O��̃A�j���[�V�����p�^�[���̏�����

	return S_OK;
} 

//�I������
void CExplosion::Uninit(void)
{
	//��{�N���X�̏I������
	CObject_2D::Uninit();
}

//�X�V����
void CExplosion::Update(void)
{
	//��{�N���X�̍X�V����
	CObject_2D::Update();

	//�A�j���[�V�������I���������ǂ����𔻒肷��
	if (GetPresentAnimPattern() < m_nLastPattern)
	{//�I�������ꍇ
		//�����̃C���X�^���X������
		Release();
		return;
	}

	m_nLastPattern = GetPresentAnimPattern();		//�O��̃A�j���[�V�����p�^�[���̍X�V
}

//��������
CExplosion* CExplosion::Create(void)
{
	CExplosion* pExplosion = nullptr;

	pExplosion = new CExplosion;								//�V���������𐶐�����
		
	//����������
	if (FAILED(pExplosion->Init()))
	{//�ł��Ȃ�������
		return nullptr;
	}

	pExplosion->SetObjType(CObject::OBJTYPE_EXPLOSION);			//�I�u�W�F�N�g�̎�ނ̐ݒ�

	return pExplosion;											//�|�C���^��Ԃ�
}