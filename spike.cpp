//=============================================================================
//
// spike.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "spike.h"
#include "squareHitbox.h"

//コンストラクタ
CSpike::CSpike()
{
	m_pHitbox = nullptr;
}

//デストラクタ
CSpike::~CSpike()
{

}

//初期化処理
HRESULT CSpike::Init(void)
{
	if (FAILED(CBullet::Init()))
	{
		return -1;
	}

	m_pHitbox = nullptr;

	return S_OK;
}

//終了処理
void CSpike::Uninit(void)
{
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}

	CBullet::Uninit();
}

//更新処理
void CSpike::Update(void)
{
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->SetPos(GetPos());
		
		if (m_pHitbox->Hit())
		{
			Release();
			return;
		}
	}

	D3DXVECTOR3 move, acc;
	move = GetMove();
	acc = GetAcceleration();

	if (move.x * acc.x > 0 || move.y * acc.y > 0)
	{
		Release();
		return;
	}

	CBullet::Update();
}



//生成処理
CSpike* CSpike::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move)
{
	CSpike* pBullet = new CSpike;

	if (FAILED(pBullet->Init()))
	{
		return nullptr;
	}

	pBullet->SetPos(pos);
	pBullet->SetMove(move);
	pBullet->SetSize(D3DXVECTOR2(10.0f, 13.7f));
	pBullet->SetTexture(CObject::TextureSpike);
	pBullet->SetTextureParameter(1, 1, 1, INT_MAX);
	pBullet->SetStartingRot(D3DX_PI * 0.5f);
	
	D3DXVECTOR3 acc;

	D3DXVec3Normalize(&acc, &move);

	float fLenght = D3DXVec3Length(&move);
	fLenght *= -0.01f;

	acc.x *= fLenght;
	acc.y *= fLenght;

	pBullet->SetAcceleration(acc);

	pBullet->m_pHitbox = CSquareHitbox::Create(pos, D3DXVECTOR2(9.0f, 12.0f), CHitbox::Type_EnemyBullet);

	return pBullet;
}