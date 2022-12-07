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
	{
		return -1;
	}

	return S_OK;
}

//�I������
void CTarget::Uninit(void)
{
	CObject_2D::Uninit();
}

//�X�V����
void CTarget::Update(void)
{
	POINT pt;
	GetCursorPos(&pt);
	HWND wnd = CApplication::GetWindow();
	ScreenToClient(wnd, &pt);

	D3DXVECTOR3 pos = D3DXVECTOR3((float)pt.x, (float)pt.y, 0.0f);

	SetPos(pos);

	CObject_2D::Update();
}




//��������
CTarget* CTarget::Create(void)
{
	CTarget* pTarget = new CTarget;

	if (FAILED(pTarget->Init()))
	{
		return nullptr;
	}

	POINT pt;
	GetCursorPos(&pt);
	HWND wnd = CApplication::GetWindow();
	ScreenToClient(wnd, &pt);

	D3DXVECTOR3 pos = D3DXVECTOR3((float)pt.x, (float)pt.y, 0.0f);

	pTarget->SetPos(pos);
	pTarget->SetTexture(CObject::TextureTarget);
	pTarget->SetSize(D3DXVECTOR2(30.0f, 30.0f));
	pTarget->SetTextureParameter(1, 1, 1, INT_MAX);
	pTarget->SetPriority(5);
	pTarget->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	return pTarget;
}