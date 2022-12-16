//=============================================================================
//
// target.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "target.h"
#include "application.h"

//�R���X�g���N�^
CTarget::CTarget()
{

}

//�f�X�g���N�^
CTarget::~CTarget()
{

}

//����������
HRESULT CTarget::Init(void)
{
	if (FAILED(CObject_2D::Init()))
	{//��{�N���X�̏���������
		return -1;
	}

	return S_OK;
}

//�I������
void CTarget::Uninit(void)
{
	//��{�N���X�̏I������
	CObject_2D::Uninit();
}

//�X�V����
void CTarget::Update(void)
{
	//�}�E�X�J�[�\���̈ʒu�̎擾�ƕϊ�
	POINT pt;
	GetCursorPos(&pt);
	HWND wnd = CApplication::GetWindow();
	ScreenToClient(wnd, &pt);

	D3DXVECTOR3 pos = D3DXVECTOR3((float)pt.x, (float)pt.y, 0.0f);

	SetPos(pos);			//�ʒu�̐ݒ�

	//��{�N���X�̍X�V����
	CObject_2D::Update();
}




//��������
CTarget* CTarget::Create(void)
{
	CTarget* pTarget = new CTarget;			//�C���X�^���X�𐶐�����

	if (FAILED(pTarget->Init()))
	{//����������
		return nullptr;
	}

	//�}�E�X�J�[�\���̈ʒu�̎擾�ƕϊ�
	POINT pt;
	GetCursorPos(&pt);
	HWND wnd = CApplication::GetWindow();
	ScreenToClient(wnd, &pt);

	D3DXVECTOR3 pos = D3DXVECTOR3((float)pt.x, (float)pt.y, 0.0f);

	pTarget->SetPos(pos);										//�ʒu�̐ݒ�
	pTarget->SetTexture(CObject::TextureTarget);				//�e�N�X�`���̐ݒ�
	pTarget->SetSize(D3DXVECTOR2(30.0f, 30.0f));				//�T�C�Y�̐ݒ�
	pTarget->SetTextureParameter(1, 1, 1, INT_MAX);				//�e�N�X�`���p�����[�^�̐ݒ�
	pTarget->SetPriority(5);									//�v���C�I���e�B�̐ݒ�
	pTarget->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));		//�F�̐ݒ�

	return pTarget;					//���������C���X�^���X��Ԃ�
}