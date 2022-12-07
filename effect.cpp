//=============================================================================
//
// effect.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "effect.h"

//�R���X�g���N�^
CEffect::CEffect()
{
	//�����o�[�ϐ����N���A����
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
}

//�f�X�g���N�^
CEffect::~CEffect()
{

}

//����������
HRESULT CEffect::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CObject_2D::Init()))
	{
		return -1;
	}

	//�����o�[�ϐ��̏�����
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	SetObjType(CObject::OBJTYPE_EFFECT);

	return S_OK;
}

//�I������
void CEffect::Uninit(void)
{
	//��{�N���X�̏I��
	CObject_2D::Uninit();
}

//�X�V����
void CEffect::Update(void)
{
	//��{�N���X�̍X�V����
	CObject_2D::Update();

	//���C�t�̍X�V
	m_nLife--;

	if (m_nLife <= 0)
	{//���C�t��0�ɂȂ�����A����
		Release();
	}
}

////�I������
//void CEffect::Draw(void)
//{
//	//��{�N���X�̕`�揈��
//	CObject_2D::Draw();
//}

//���C�t�̎擾����
const int CEffect::GetLife(void)
{
	return m_nLife;
}

//���x�̐ݒ菈��
void CEffect::SetMove(const D3DXVECTOR3 move)
{
	m_move = move;
}

//���C�t�̐ݒ菈��
void CEffect::SetLife(const int Life)
{
	m_nLife = Life;
} 


//=============================================================================
//�ÓI�֐�
//=============================================================================

//��������
CEffect* CEffect::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const D3DXCOLOR col, const D3DXVECTOR2 size, const int Life)
{
	CEffect* pEffect = new CEffect;					//�V�����G�t�F�N�g�𐶐�����

	//����������
	if (FAILED(pEffect->Init()))
	{
		return nullptr;
	}

	pEffect->SetPos(pos);							//�ʒu�̐ݒ�
	pEffect->m_move = move;							//���x�̐ݒ�
	pEffect->SetColor(col);							//�J�[���[�̐ݒ�
	pEffect->m_nLife = Life;						//���C�t�̐ݒ�
	pEffect->SetSize(size);							//�T�C�Y�̐ݒ�

	return pEffect;									//�G�t�F�N�g��Ԃ�
}