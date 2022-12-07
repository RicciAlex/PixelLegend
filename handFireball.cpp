//=============================================================================
//
// handFireball.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "handFireball.h"
#include "circleHitbox.h"

//コンストラクタ
CHandFireball::CHandFireball()
{
	m_fChange = 0.0f;
	m_Rot = false;

	m_pHitbox = nullptr;
}

//デストラクタ
CHandFireball::~CHandFireball()
{

}

//初期化処理
HRESULT CHandFireball::Init(void)
{
	if (FAILED(CBullet::Init()))
	{
		return -1;
	}

	m_fChange = 0.0f;
	m_Rot = false;

	m_pHitbox = nullptr;

	return S_OK;
}

//終了処理
void CHandFireball::Uninit(void)
{
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}

	CBullet::Uninit();
}

//更新処理
void CHandFireball::Update(void)
{
	CObject_2D::Update();

	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 move = GetMove();

	if (pos.x >= m_fChange && move.x >= 0.0f || pos.x <= m_fChange && move.x <= 0.0f)
	{
		if (move.x >= 0.0f)
		{
			m_fChange += 100.0f;
		}
		else
		{
			m_fChange -= 100.0f;
		}
		
		move.y *= -1.0f;

		SetMove(move);

		if (!m_Rot)
		{
			float fRot = GetRot() + D3DX_PI * 0.5f;
			SetStartingRot(fRot);
			m_Rot = true;
		}
		else
		{
			float fRot = GetRot() - D3DX_PI * 0.5f;
			SetStartingRot(fRot);
			m_Rot = false;
		}
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

	if (pos.x <= -100.0f || pos.x >= 1380.0f)
	{
		Release();
		return;
	}
}





//生成処理
CHandFireball* CHandFireball::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CHandFireball* pBullet = new CHandFireball;

	if (FAILED(pBullet->Init()))
	{
		return nullptr;
	}

	pBullet->SetPos(pos);
	pBullet->SetSize(D3DXVECTOR2(25.0f, 25.0f));
	pBullet->SetMove(move);
	//pBullet->SetStartingRot(D3DX_PI * 0.25f);
	pBullet->SetTexture(CObject::TextureHandFireball);
	pBullet->SetTextureParameter(1, 1, 1, INT_MAX);
	pBullet->m_fChange = 100.0f;

	if (move.x < 0.0)
	{
		pBullet->FlipX();

		pBullet->m_Rot = true;
		pBullet->m_fChange = (float)SCREEN_WIDTH - 100.0f;

		pBullet->SetStartingRot(D3DX_PI);
	}

	pBullet->m_pHitbox = CCircleHitbox::Create(pos, 20.0f, CHitbox::Type_EnemyBullet);

	return pBullet;
}