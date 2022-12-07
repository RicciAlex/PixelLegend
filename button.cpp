//=============================================================================
//
// button.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "button.h"
#include "object2D.h"
#include "Letter.h"
#include "application.h"
#include "inputMouse.h"

//コンストラクタ
CButton::CButton()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR2(0.0f, 0.0f);
	m_originalSize = D3DXVECTOR2(0.0f, 0.0f);

	m_fCntAnim = 0.0f;
	m_bTriggered = false;

	m_pBack = nullptr;

	for (int nCnt = 0; nCnt < MaxWordLenght; nCnt++)
	{
		m_pLetter[nCnt] = nullptr;
	}
}

//デストラクタ
CButton::~CButton()
{

}

//初期化処理
HRESULT CButton::Init(void)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR2(0.0f, 0.0f);
	m_originalSize = D3DXVECTOR2(0.0f, 0.0f);

	m_fCntAnim = 0.25f;
	m_bTriggered = false;

	m_pBack = nullptr;

	for (int nCnt = 0; nCnt < MaxWordLenght; nCnt++)
	{
		m_pLetter[nCnt] = nullptr;
	}

	return S_OK;
}

//終了処理
void CButton::Uninit(void)
{
	if (m_pBack != nullptr)
	{
		m_pBack->Release();
		m_pBack = nullptr;
	}

	for (int nCnt = 0; nCnt < MaxWordLenght; nCnt++)
	{
		if (m_pLetter[nCnt] != nullptr)
		{
			m_pLetter[nCnt]->Release();
			m_pLetter[nCnt] = nullptr;
		}
	}
}

//更新処理
void CButton::Update(void)
{
	POINT pt;
	GetCursorPos(&pt);
	HWND wnd = CApplication::GetWindow();
	ScreenToClient(wnd, &pt);
	D3DXVECTOR3 MousePos, PlayerPos;
	MousePos.x = (float)pt.x;
	MousePos.y = (float)pt.y;
	MousePos.z = 0.0f;

	float fLeft, fRight, fTop, fBottom;

	fLeft = GetPos().x - GetSize().x;
	fRight = GetPos().x + GetSize().x;
	fTop = GetPos().y - GetSize().y;
	fBottom = GetPos().y + GetSize().y;

	bool bChange = false;
	m_bTriggered = false;

	if (MousePos.x > fLeft && MousePos.x < fRight && MousePos.y > fTop && MousePos.y < fBottom)
	{
		if (CApplication::GetMouse()->GetMouseLeftClick() && !CApplication::GetFade())
		{
			m_bTriggered = true;
		}

		for (int nCnt = 0; nCnt < MaxWordLenght; nCnt++)
		{
			if (m_pLetter[nCnt] != nullptr)
			{
				D3DXVECTOR2 size = m_pLetter[nCnt]->GetSize();
				size.x += m_fCntAnim;
				size.y += m_fCntAnim;

				if (size.x >= m_originalSize.x + 10.0f)
				{
					size.x = m_originalSize.x + 10.0f;
					bChange = true;
				}
				else if (size.x <= m_originalSize.x)
				{
					size.x = m_originalSize.x;
					bChange = true;
				}

				m_pLetter[nCnt]->SetSize(size);

				
			}
		}
	}
	else
	{
		for (int nCnt = 0; nCnt < MaxWordLenght; nCnt++)
		{
			if (m_pLetter[nCnt] != nullptr)
			{
				m_pLetter[nCnt]->SetSize(m_originalSize);
			}
		}
	}

	if (bChange)
	{
		m_fCntAnim *= -1.0f;
	}
}

//描画処理
void CButton::Draw(void)
{
	
}

//位置の設定処理
void CButton::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//サイズの取得処理
const D3DXVECTOR2 CButton::GetSize(void)
{
	return m_size;
}

//位置の設定処理
const D3DXVECTOR3 CButton::GetPos(void)
{
	return m_pos;
}

const bool CButton::GetTriggerState(void)
{
	return m_bTriggered;
}


CButton* CButton::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const D3DXCOLOR BgCol, const char* Word)
{
	CButton* pButton = new CButton;

	if (FAILED(pButton->Init()))
	{
		return nullptr;
	}

	pButton->m_pos = pos;
	pButton->m_size = size;

	pButton->m_pBack = CObject_2D::Create();
	int nIdx = 0;

	if (pButton->m_pBack != nullptr)
	{
		pButton->m_pBack->SetStartingRot(D3DX_PI * 0.5f);
		pButton->m_pBack->SetPos(pos);
		pButton->m_pBack->SetSize(size);
		pButton->m_pBack->SetColor(BgCol);
		pButton->m_pBack->SetPriority(5);
		pButton->m_pBack->SetObjType(CObject::OBJTYPE_MENU);
	}
	
	char aStrg[MaxWordLenght] = {};
	strcpy(aStrg, Word);

	int Lenght = strlen(aStrg);
	float fLetterLenght = size.x / (Lenght - 1);

	for (int nCnt = 0; nCnt < Lenght; nCnt++)
	{
		if (aStrg[nCnt] != ' ' && pButton->m_pLetter[nCnt] == nullptr)
		{
			pButton->m_pLetter[nCnt] = CLetter::Create(D3DXVECTOR3((pos.x - 50.0f * (Lenght - 1) * 0.5f) + 50.0f * nCnt, pos.y, 0.0f), D3DXVECTOR2(25.0f, 31.8f), aStrg[nCnt]);

			if (pButton->m_pLetter[nCnt] != nullptr)
			{
				pButton->m_pLetter[nCnt]->SetPriority(5);
				pButton->m_originalSize = pButton->m_pLetter[nCnt]->GetSize();
				pButton->m_pLetter[nCnt]->SetObjType(CObject::OBJTYPE_MENU);
			}
		}
	}

	int a = 0;

	return pButton;
}

CButton* CButton::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const D3DXCOLOR BgCol, const D3DXCOLOR LettersCol, const char* Word)
{
	CButton* pButton = new CButton;

	if (FAILED(pButton->Init()))
	{
		return nullptr;
	}

	pButton->m_pos = pos;
	pButton->m_size = size;

	pButton->m_pBack = CObject_2D::Create();

	if (pButton->m_pBack != nullptr)
	{
		pButton->m_pBack->SetStartingRot(D3DX_PI * 0.5f);
		pButton->m_pBack->SetPos(pos);
		pButton->m_pBack->SetSize(size);
		pButton->m_pBack->SetColor(BgCol);
		pButton->m_pBack->SetPriority(5);
		pButton->m_pBack->SetObjType(CObject::OBJTYPE_MENU);
	}

	char aStrg[MaxWordLenght] = {};
	strcpy(aStrg, Word);

	int Lenght = strlen(aStrg);
	float fLetterLenght = size.x / (Lenght - 1);

	for (int nCnt = 0; nCnt < Lenght; nCnt++)
	{
		if (aStrg[nCnt] != ' ' && pButton->m_pLetter[nCnt] == nullptr)
		{
			pButton->m_pLetter[nCnt] = CLetter::Create(D3DXVECTOR3((pos.x - fLetterLenght * (Lenght - 1) * 0.5f) + fLetterLenght * nCnt, pos.y, 0.0f), D3DXVECTOR2(fLetterLenght * 0.5f, fLetterLenght * 0.5f), aStrg[nCnt]);

			if (pButton->m_pLetter[nCnt] != nullptr)
			{
				pButton->m_pLetter[nCnt]->SetPriority(5);
				pButton->m_originalSize = pButton->m_pLetter[nCnt]->GetSize();
				pButton->m_pLetter[nCnt]->SetColor(LettersCol);
				pButton->m_pLetter[nCnt]->SetObjType(CObject::OBJTYPE_MENU);
			}
		}
	}

	int a = 0;

	return pButton;
}