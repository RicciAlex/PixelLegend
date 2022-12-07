//=============================================================================
//
// bouncingBullet.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "bouncingBullet.h"
#include "circleHitbox.h"

//コンストラクタ
CBouncingBullet::CBouncingBullet()
{
	m_pHitbox = nullptr;
}

//デストラクタ
CBouncingBullet::~CBouncingBullet()
{

}

//初期化処理
HRESULT CBouncingBullet::Init(void)
{
	if (FAILED(CBullet::Init()))
	{
		return -1;
	}

	m_pHitbox = nullptr;

	return S_OK;
}

//終了処理
void CBouncingBullet::Uninit(void)
{
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}

	CBullet::Uninit();
}

//更新処理
void CBouncingBullet::Update(void)
{
	int nLife = GetLife();
	nLife--;

	if (nLife <= 0)
	{
		Release();
		return;
	}
	else
	{
		SetLife(nLife);
	}

	if (m_pHitbox != nullptr)
	{
		m_pHitbox->SetPos(GetPos());

		if (m_pHitbox->Hit())
		{
			Release();
			return;
		}
	}

	D3DXVECTOR3 pos, move;

	pos = GetPos();
	move = GetMove();
	pos += move;

	if (pos.x + GetSize().x <= 0.0f || pos.x + GetSize().x >= (float)SCREEN_WIDTH)
	{
		move.x *= -1.0f;
		SetMove(move);
	}

	if (pos.y + GetSize().y <= 0.0f || pos.y - GetSize().y >= (float)SCREEN_HEIGHT)
	{
		move.y *= -1.0f;
		SetMove(move);
	}

	CBullet::Update();
}



//生成処理
CBouncingBullet* CBouncingBullet::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move)
{
	CBouncingBullet* pBullet = new CBouncingBullet;

	if (FAILED(pBullet->Init()))
	{
		return nullptr;
	}

	pBullet->SetPos(pos);
	pBullet->SetMove(move);
	pBullet->SetSize(D3DXVECTOR2(15.0f, 15.0f));
	pBullet->SetTexture(CObject::TextureNormalEffect);
	pBullet->SetTextureParameter(1, 1, 1, INT_MAX);
	pBullet->SetLife(300);

	int nColor = random(0, 5);
	D3DXCOLOR col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	switch (nColor)
	{
	case 0:
		col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		break;
	case 1:
		col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		break;
	case 2:
		col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
		break;
	case 3:
		col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		break;
	case 4:
		col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		break;
	case 5:
		col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
		break;
	default:
		break;
	}

	pBullet->SetColor(col);

	pBullet->m_pHitbox = CCircleHitbox::Create(pos, 15.0f, CHitbox::Type_EnemyBullet);

	return pBullet;
}