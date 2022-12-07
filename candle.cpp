//=============================================================================
//
// candle.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "candle.h"
#include "squareHitbox.h"
#include "bg.h"
#include "skullShield.h"
#include "Thanatos.h"

//コンストラクタ
CCandle::CCandle()
{
	m_state = state_spawn;
	m_nCntState = 0;
	m_nIdx = 0;

	m_pParent = nullptr;
	m_pHitbox = nullptr;
	m_pBg = nullptr;
	m_pShield[0] = nullptr;
	m_pShield[1] = nullptr;
}

//デストラクタ
CCandle::~CCandle()
{

}

//初期化処理
HRESULT CCandle::Init(void)
{
	if (FAILED(CEnemy::Init()))
	{
		return -1;
	}

	m_nCntState = 0;
	m_nIdx = -1;
	m_state = state_spawn;
	SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	m_pParent = nullptr;
	m_pHitbox = nullptr;
	m_pBg = nullptr;
	m_pShield[0] = nullptr;
	m_pShield[1] = nullptr;

	return S_OK;
}

//終了処理
void CCandle::Uninit(void)
{
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pShield[nCnt] != nullptr)
		{
			m_pShield[nCnt]->Release();
			m_pShield[nCnt] = nullptr;
		}
	}

	if (m_pBg != nullptr)
	{
		m_pBg = nullptr;
	}
	if (m_pParent != nullptr)
	{
		m_pParent = nullptr;
	}

	CEnemy::Uninit();
}

//更新処理
void CCandle::Update(void)
{
	switch (m_state)
	{
	case CCandle::state_spawn:

	{
		D3DXCOLOR col = GetColor();

		col.a += 0.01f;

		SetColor(col);

		if (col.a >= 0.9f)
		{
			m_state = state_off;
		}
	}

		break;

	case CCandle::state_off:

	{
		m_pHitbox->SetPos(GetPos());

		if (m_pHitbox->GetHitState())
		{
			m_pHitbox->SetHitState(false);
			int nLife = GetLife();
			nLife += 100;
			SetLife(nLife);

			if (nLife >= 1500)
			{
				m_state = state_on;
				SetAnimPattern(0);
				SetTextureParameter(4, 5, 1, 10);

				if (m_pParent != nullptr)
				{
					m_pParent->AddLitCandle();
				}

				if (m_pBg != nullptr)
				{
					m_pBg->SetVtxColor(m_nIdx, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				}
			}
		}
	}

		break;

	case CCandle::state_on:
		break;

	default:
		break;
	}

	CObject_2D::Update();
}

//描画処理
void CCandle::Draw(void)
{
	CObject_2D::Draw();
}

void CCandle::SetParent(CThanatos* pParent)
{
	m_pParent = pParent;
}

void CCandle::SetBgPointer(CBg* pointer)
{
	m_pBg = pointer;
}

CCandle::state CCandle::GetCandleState(void)
{
	return m_state;
}

void CCandle::Unlit(void)
{
	m_state = state_off;
	SetTextureParameter(1, 5, 1, INT_MAX);
	SetAnimPattern(4);
	m_pBg->SetVtxColor(m_nIdx, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	SetLife(0);

	m_pShield[0]->AddRevolutionSpeed(D3DX_PI * 0.01f);
	m_pShield[1]->AddRevolutionSpeed(D3DX_PI * 0.01f);
}

void CCandle::Despawn(void)
{
	D3DXCOLOR col = m_pShield[0]->GetColor();

	if (col.a > 0.0f)
	{
		col.a -= 0.005f;
		m_pShield[0]->SetColor(col);
	}

	col = m_pShield[1]->GetColor();

	if (col.a > 0.0f)
	{
		col.a -= 0.005f;
		m_pShield[1]->SetColor(col);
	}
}




//生成処理
CCandle* CCandle::Create(const D3DXVECTOR3 pos)
{
	CCandle* pCandle = new CCandle;

	if (FAILED(pCandle->Init()))
	{
		return nullptr;
	}

	pCandle->SetPos(pos);
	pCandle->SetSize(D3DXVECTOR2(22.5f, 28.5f));
	pCandle->SetTexture(CObject::TextureCandle);
	pCandle->SetTextureParameter(1, 5, 1, INT_MAX);
	pCandle->SetAnimPattern(4);
	pCandle->SetStartingRot(D3DX_PI * 0.5f);
	pCandle->m_pHitbox = CSquareHitbox::Create(pos, D3DXVECTOR2(12.0f, 13.0f), CHitbox::Type_Enemy);

	if (pos.x < (float)SCREEN_WIDTH * 0.5f && pos.y < (float)SCREEN_HEIGHT * 0.5f)
	{
		pCandle->m_nIdx = 0;
	}
	else if (pos.x > (float)SCREEN_WIDTH * 0.5f && pos.y < (float)SCREEN_HEIGHT * 0.5f)
	{
		pCandle->m_nIdx = 1;
	}
	else if (pos.x < (float)SCREEN_WIDTH * 0.5f && pos.y > (float)SCREEN_HEIGHT * 0.5f)
	{
		pCandle->m_nIdx = 2;
	}
	else if (pos.x > (float)SCREEN_WIDTH * 0.5f && pos.y > (float)SCREEN_HEIGHT * 0.5f)
	{
		pCandle->m_nIdx = 3;
	}

	pCandle->m_pShield[0] = CSkullShield::Create(D3DXVECTOR3(pos.x, pos.y + 5.0f, 0.0f), 0.0f);
	pCandle->m_pShield[1] = CSkullShield::Create(D3DXVECTOR3(pos.x, pos.y + 10.0f, 0.0f), D3DX_PI);

	return pCandle;
}

CCandle* CCandle::Create(const D3DXVECTOR3 pos, CBg* pointer)
{
	CCandle* pCandle = new CCandle;

	if (FAILED(pCandle->Init()))
	{
		return nullptr;
	}

	pCandle->SetPos(pos);
	pCandle->SetSize(D3DXVECTOR2(30.0f, 38.0f));
	pCandle->SetTexture(CObject::TextureCandle);
	pCandle->SetTextureParameter(1, 5, 1, INT_MAX);
	pCandle->SetAnimPattern(4);
	pCandle->SetStartingRot(D3DX_PI * 0.5f);
	pCandle->m_pHitbox = CSquareHitbox::Create(pos, D3DXVECTOR2(12.0f, 13.0f), CHitbox::Type_Enemy);
	pCandle->m_pBg = pointer;

	if (pos.x < (float)SCREEN_WIDTH * 0.5f && pos.y < (float)SCREEN_HEIGHT * 0.5f)
	{
		pCandle->m_nIdx = 0;
	}
	else if (pos.x >(float)SCREEN_WIDTH * 0.5f && pos.y < (float)SCREEN_HEIGHT * 0.5f)
	{
		pCandle->m_nIdx = 1;
	}
	else if (pos.x < (float)SCREEN_WIDTH * 0.5f && pos.y >(float)SCREEN_HEIGHT * 0.5f)
	{
		pCandle->m_nIdx = 2;
	}
	else if (pos.x >(float)SCREEN_WIDTH * 0.5f && pos.y > (float)SCREEN_HEIGHT * 0.5f)
	{
		pCandle->m_nIdx = 3;
	}

	pCandle->m_pShield[0] = CSkullShield::Create(D3DXVECTOR3(pos.x, pos.y + 5.0f, 0.0f), 0.0f);
	pCandle->m_pShield[1] = CSkullShield::Create(D3DXVECTOR3(pos.x, pos.y + 10.0f, 0.0f), D3DX_PI);

	return pCandle;
}