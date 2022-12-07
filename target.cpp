//=============================================================================
//
// target.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "target.h"
#include "application.h"

//コンストラクタ
CTarget::CTarget()
{

}

//デストラクタ
CTarget::~CTarget()
{

}

//初期化処理
HRESULT CTarget::Init(void)
{
	if (FAILED(CObject_2D::Init()))
	{
		return -1;
	}

	return S_OK;
}

//終了処理
void CTarget::Uninit(void)
{
	CObject_2D::Uninit();
}

//更新処理
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




//生成処理
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