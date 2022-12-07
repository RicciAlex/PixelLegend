//=============================================================================
//
// envyPieces.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "envyPieces.h"
#include "circleHitbox.h"

//コンストラクタ
CEnvyPieces::CEnvyPieces()
{
	m_pHitbox = nullptr;
}

//デストラクタ
CEnvyPieces::~CEnvyPieces()
{

}

//初期化処理
HRESULT CEnvyPieces::Init(void)
{
	if (FAILED(CBullet::Init()))
	{
		return -1;
	}

	m_pHitbox = nullptr;

	return S_OK;
}

//終了処理
void CEnvyPieces::Uninit(void)
{
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}

	CBullet::Uninit();
}

//更新処理
void CEnvyPieces::Update(void)
{
	CObject_2D::Update();

	if (m_pHitbox != nullptr)
	{
		m_pHitbox->SetPos(GetPos());

		if (m_pHitbox->Hit())
		{
			Release();
			return;
		}
	}

	if (GetPos().y >= 900.0f)
	{
		Release();
		return;
	}
}




//生成処理
CEnvyPieces* CEnvyPieces::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move)
{
	CEnvyPieces* pBullet = new CEnvyPieces;

	if (FAILED(pBullet->Init()))
	{
		return nullptr;
	}

	pBullet->SetPos(pos);
	pBullet->SetMove(move);
	pBullet->SetAcceleration(D3DXVECTOR3(0.0f, 0.05f, 0.0f));
	pBullet->SetSize(D3DXVECTOR2(15.0f, 15.0f));
	pBullet->SetRotation(D3DX_PI * ((float)random(-50, 50) * 0.002f));

	int randomizer = random(0, 2);

	switch (randomizer)
	{
	case 0:

		pBullet->SetTexture(CObject::TextureGear);
		pBullet->SetTextureParameter(1, 3, 2, INT_MAX);
		pBullet->SetAnimPattern(random(0, 5));

		break;

	case 1:

		pBullet->SetTexture(CObject::TextureSpringAndScrew);
		pBullet->SetTextureParameter(1, 2, 1, INT_MAX);
		pBullet->SetAnimPattern(1);

		break;

	case 2:

		pBullet->SetTexture(CObject::TextureSpringAndScrew);
		pBullet->SetTextureParameter(1, 2, 1, INT_MAX);
		pBullet->SetAnimPattern(2);

		break;

	default:
		break;
	}

	pBullet->m_pHitbox = CCircleHitbox::Create(pos, 14.0f, CHitbox::Type_EnemyBullet);

	return pBullet;
	
}

CEnvyPieces* CEnvyPieces::Create(const D3DXVECTOR3 pos, const float radius)
{
	CEnvyPieces* pBullet = new CEnvyPieces;

	if (FAILED(pBullet->Init()))
	{
		return nullptr;
	}

	D3DXVECTOR3 P = pos;
	P.x += (float)random((int)-radius, (int)radius);
	P.y += (float)random((int)-radius, (int)radius);

	D3DXVECTOR3 move = D3DXVECTOR3((float)random(-1000, 1000), (float)random(-1000, 1000), 0.0f);
	D3DXVec3Normalize(&move, &move);
	int K = random(2, 7);
	move.x *= (float)K;
	move.y *= (float)K;

	pBullet->SetPos(P);
	pBullet->SetMove(move);
	pBullet->SetAcceleration(D3DXVECTOR3(0.0f, 0.05f, 0.0f));
	pBullet->SetSize(D3DXVECTOR2(15.0f, 15.0f));
	pBullet->SetRotation(D3DX_PI * ((float)random(-50, 50) * 0.002f));

	int randomizer = random(0, 2);

	switch (randomizer)
	{
	case 0:

		pBullet->SetTexture(CObject::TextureGear);
		pBullet->SetTextureParameter(1, 3, 2, INT_MAX);
		pBullet->SetAnimPattern(random(0, 5));

		break;

	case 1:

		pBullet->SetTexture(CObject::TextureSpringAndScrew);
		pBullet->SetTextureParameter(1, 2, 1, INT_MAX);
		pBullet->SetAnimPattern(1);

		break;

	case 2:

		pBullet->SetTexture(CObject::TextureSpringAndScrew);
		pBullet->SetTextureParameter(1, 2, 1, INT_MAX);
		pBullet->SetAnimPattern(2);

		break;

	default:
		break;
	}

	return pBullet;
}
