//=============================================================================
//
// spikeBomb.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "spikeBomb.h"
#include "circleHitbox.h"
#include "spike.h"

CSpikeBomb::CSpikeBomb()
{
	m_pHitbox = nullptr;
}

CSpikeBomb::~CSpikeBomb()
{

}

//初期化処理
HRESULT CSpikeBomb::Init(void)
{
	if (FAILED(CBullet::Init()))
	{
		return -1;
	}

	m_pHitbox = nullptr;

	return S_OK;
}

//終了処理
void CSpikeBomb::Uninit(void)
{
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}

	CBullet::Uninit();
}

//更新処理
void CSpikeBomb::Update(void)
{
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->SetPos(GetPos());

		if (m_pHitbox->Hit())
		{
			CSpike* pBullet = CSpike::Create(GetPos(), D3DXVECTOR3(0.0f, -1.0f, 0.0f));
			pBullet = CSpike::Create(GetPos(), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
			pBullet->SetStartingRot(-D3DX_PI * 0.5f);
			pBullet = CSpike::Create(GetPos(), D3DXVECTOR3(-1.0f, 0.0f, 0.0f));
			pBullet->SetStartingRot(D3DX_PI);
			pBullet = CSpike::Create(GetPos(), D3DXVECTOR3(1.0f, 0.0f, 0.0f));
			pBullet->SetStartingRot(0.0f);
			Release();
			return;
		}
	}

	int nLife = GetLife();
	nLife--;

	if (nLife <= 0)
	{
		CSpike* pBullet = CSpike::Create(GetPos(), D3DXVECTOR3(0.0f, -1.0f, 0.0f));
		pBullet = CSpike::Create(GetPos(), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
		pBullet->SetStartingRot(-D3DX_PI * 0.5f);
		pBullet = CSpike::Create(GetPos(), D3DXVECTOR3(-1.0f, 0.0f, 0.0f));
		pBullet->SetStartingRot(D3DX_PI);
		pBullet = CSpike::Create(GetPos(), D3DXVECTOR3(1.0f, 0.0f, 0.0f));
		pBullet->SetStartingRot(0.0f);
		Release();
		return;
	}
	else
	{
		SetLife(nLife);
	}

	CBullet::Update();
}




//生成処理
CSpikeBomb* CSpikeBomb::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CSpikeBomb* pBullet = new CSpikeBomb;

	if (FAILED(pBullet->Init()))
	{
		return nullptr;
	}

	pBullet->SetPos(pos);
	pBullet->SetSize(D3DXVECTOR2(20.0f, 20.0f));
	pBullet->SetMove(move);
	pBullet->SetRotation(-D3DX_PI * 0.05f);
	pBullet->SetTexture(CObject::TextureSpikeBomb);
	pBullet->SetTextureParameter(1, 1, 1, INT_MAX);
	pBullet->SetLife(90);

	pBullet->m_pHitbox = CCircleHitbox::Create(pos, 10.0f, CHitbox::Type_EnemyBullet);

	return pBullet;
}