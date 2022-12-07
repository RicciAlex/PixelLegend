//=============================================================================
//
// bone.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "bone.h"
#include "squareHitbox.h"

//コンストラクタ
CBone::CBone()
{
	m_bBroken = false;

	m_pHitbox = nullptr;
}

//デストラクタ
CBone::~CBone()
{

}

//初期化処理
HRESULT CBone::Init(void)
{
	if (FAILED(CBullet::Init()))
	{
		return -1;
	}

	m_bBroken = false;

	m_pHitbox = nullptr;

	return S_OK;
}

//終了処理
void CBone::Uninit(void)
{
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}

	CBullet::Uninit();
}

//更新処理
void CBone::Update(void)
{
	CObject_2D::Update();

	D3DXVECTOR3 pos = GetPos();

	if (m_pHitbox != nullptr)
	{
		m_pHitbox->SetPos(pos);

		if (m_pHitbox->Hit())
		{
			Release();
			return;
		}
	}

	if (pos.x <= 60.0f)
	{
		pos.x = 60.0f;
	}
	else if (pos.x >= (float)SCREEN_WIDTH - 60)
	{
		pos.x = (float)SCREEN_WIDTH - 60;
	}

	if (pos.y <= 60.0f)
	{
		pos.y = 60.0f;
	}
	else if(pos.y >= (float)SCREEN_HEIGHT - 60)
	{
		pos.y = (float)SCREEN_HEIGHT - 60;
	}
	
	if (pos.x <= 60.0f || pos.x >= (float)SCREEN_WIDTH - 60 || pos.y <= 60.0f || pos.y >= (float)SCREEN_HEIGHT - 60)
	{
		if (!m_bBroken)
		{
			m_bBroken = true;
			Split();
			Release();
			return;
		}
		else
		{
			Release();
			return;
		}
	}
}



//生成処理
CBone* CBone::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move)
{
	CBone* pBullet = new CBone;

	if (FAILED(pBullet->Init()))
	{
		return nullptr;
	}

	pBullet->SetPos(pos);
	pBullet->SetSize(D3DXVECTOR2(35.0f, 10.7f));
	pBullet->SetMove(move);
	pBullet->SetTexture(CObject_2D::TextureBone);
	pBullet->SetTextureParameter(1, 1, 2, INT_MAX);
	pBullet->SetRotation((float)random(-10, 10) * 0.0025f * D3DX_PI);
	pBullet->SetStartingRot(D3DX_PI * 0.5f);
	pBullet->m_bBroken = false;

	pBullet->m_pHitbox = CSquareHitbox::Create(D3DXVECTOR3(pos), D3DXVECTOR2(49.0f, 15.0f), CHitbox::Type_EnemyBullet);


	return pBullet;
}



void CBone::Split(void)
{
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 move1 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 move2 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 V = GetMove();
	float fSpeed = D3DXVec3Length(&V);

	if (pos.x <= 61.0f || pos.x >= (float)SCREEN_WIDTH - 61.0f)
	{
		move1.x = GetMove().x * -1.0f;
		move2.x = GetMove().x * -1.0f;

		move1.y = random(-10, 10) * 0.1f;
		move2.y = -move1.y;
	}
	else if (pos.y <= 61.0f || pos.y >= (float)SCREEN_HEIGHT - 61.0f)
	{
		move1.y = GetMove().y * -1.0f;
		move2.y = GetMove().y * -1.0f;

		move1.x = random(5, 10) * 0.1f;
		move2.x = -move1.x;
	}

	D3DXVec3Normalize(&move1, &move1);
	D3DXVec3Normalize(&move2, &move2);

	move1.x *= fSpeed;
	move1.y *= fSpeed;
	move2.x *= fSpeed;
	move2.y *= fSpeed;

	D3DXVECTOR2 size = GetSize();
	size.x *= 0.5f;

	CBone* pBullet = CBone::Create(pos, move1);
	pBullet->SetTextureParameter(1, 2, 2, INT_MAX);
	pBullet->SetAnimPattern(1);
	pBullet->m_bBroken = true;
	pBullet->SetSize(size);
	pBullet->m_pHitbox->SetSize(size);

	pBullet = CBone::Create(pos, move2);
	pBullet->SetTextureParameter(1, 2, 2, INT_MAX);
	pBullet->SetAnimPattern(2);
	pBullet->m_bBroken = true;
	pBullet->SetSize(size);
	pBullet->m_pHitbox->SetSize(size);
}