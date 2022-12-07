//=============================================================================
//
// handBlade.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "handBlade.h"
#include "circleHitbox.h"

//コンストラクタ
CHandBlade::CHandBlade()
{
	m_pHitbox = nullptr;
}

//デストラクタ
CHandBlade::~CHandBlade()
{

}

//初期化処理
HRESULT CHandBlade::Init(void)
{
	if (FAILED(CBullet::Init()))
	{
		return -1;
	}

	m_pHitbox = nullptr;

	return S_OK;
}

//終了処理
void CHandBlade::Uninit(void)
{
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}

	CBullet::Uninit();
}

//更新処理
void CHandBlade::Update(void)
{
	CObject_2D::Update();

	D3DXVECTOR3 pos, move;
	pos = GetPos();
	move = GetMove();

	if (pos.y + move.y <= 0.0f || pos.y + move.y >= (float)SCREEN_HEIGHT)
	{
		move.y *= -1.0f;
		SetMove(move);
	}
	if (pos.x <= 0.0f || pos.x >= (float)SCREEN_WIDTH)
	{
		Release();
		return;
	}

	int nLife = GetLife() - 1;

	if (nLife <= 0)
	{
		Release();
		return;
	}
	
	SetLife(nLife);

	if (m_pHitbox != nullptr)
	{
		m_pHitbox->SetPos(pos);

		if (m_pHitbox->Hit())
		{
			Release();
			return;
		}
	}
}







//生成処理
CHandBlade* CHandBlade::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CHandBlade* pBullet = new CHandBlade;

	if (FAILED(pBullet->Init()))
	{
		return nullptr;
	}

	pBullet->SetPos(pos);
	pBullet->SetMove(move);
	pBullet->SetSize(D3DXVECTOR2(20.0f, 20.0f));
	pBullet->SetRotation(-D3DX_PI * 0.025f);
	pBullet->SetTexture(CObject::TextureHandBlade);
	pBullet->SetTextureParameter(1, 1, 1, INT_MAX);
	pBullet->SetLife(300);

	pBullet->m_pHitbox = CCircleHitbox::Create(pos, 20.0f, CHitbox::Type_EnemyBullet);

	return pBullet;
}