//=============================================================================
//
// skullCursor.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "skullCursor.h"
#include "application.h"
#include "skull.h"
#include "spine.h"

//コンストラクタ
CSkullCursor::CSkullCursor()
{
	m_skullPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_pSpine = nullptr;
	m_pSkull = nullptr;
}

//デストラクタ
CSkullCursor::~CSkullCursor()
{

}

//初期化処理
HRESULT CSkullCursor::Init(void)
{
	m_skullPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_pSpine = nullptr;
	m_pSkull = nullptr;

	return S_OK;
}

//終了処理
void CSkullCursor::Uninit(void)
{
	if (m_pSkull != nullptr)
	{
		m_pSkull->Release();
		m_pSkull = nullptr;
	}

	if (m_pSpine != nullptr)
	{
		m_pSpine->Release();
		m_pSpine = nullptr;
	}
}

//更新処理
void CSkullCursor::Update(void)
{
	POINT pt;
	GetCursorPos(&pt);
	HWND wnd = CApplication::GetWindow();
	ScreenToClient(wnd, &pt);

	m_skullPos.y = (float)pt.y;

	if (m_pSkull != nullptr)
	{
		m_pSkull->SetPos(m_skullPos);
	}
	
	if (m_pSpine != nullptr)
	{
		m_pSpine->SetHeadPos(m_skullPos);
	}
}





//生成処理
CSkullCursor* CSkullCursor::Create(const D3DXVECTOR3 pos)
{
	CSkullCursor* pCursor = new CSkullCursor;

	if (FAILED(pCursor->Init()))
	{
		return nullptr;
	}

	POINT pt;
	GetCursorPos(&pt);
	HWND wnd = CApplication::GetWindow();
	ScreenToClient(wnd, &pt);

	float fNum = 350.0f;

	if (pos.x < (float)SCREEN_WIDTH * 0.5f)
	{
		fNum *= -1.0f;
	}

	pCursor->m_skullPos = D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f + fNum, (float)pt.y, 0.0f);
	pCursor->m_pSkull = CSkull::Create(pCursor->m_skullPos, D3DXVECTOR2(60.0f, 60.0f));	
	pCursor->m_pSpine = CSpine::Create(pos, pCursor->m_skullPos);

	if (pCursor->m_pSkull != nullptr && pCursor->m_pSpine != nullptr)
	{
		pCursor->m_pSkull->SetPriority(4);

		if (pos.x < (float)SCREEN_WIDTH * 0.5f)
		{
			pCursor->m_pSkull->FlipX();
			pCursor->m_pSpine->Flip();
		}
	}

	return pCursor;
}