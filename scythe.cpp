//=============================================================================
//
// scythe.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "Scythe.h"
#include "circleHitbox.h"

//コンストラクタ
CScythe::CScythe()
{
	fCntSize = 0.0f;

	m_pHitbox = nullptr;
}

//デストラクタ
CScythe::~CScythe()
{

}

//初期化処理
HRESULT CScythe::Init(void)
{
	if (FAILED(CBullet::Init()))
	{
		return -1;
	}

	fCntSize = 0.0f;

	m_pHitbox = nullptr;

	return S_OK;
}

//終了処理
void CScythe::Uninit(void)
{
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}

	CBullet::Uninit();
}

//更新処理
void CScythe::Update(void)
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
	
	CBullet::Update();
}




//生成処理
CScythe* CScythe::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CScythe* pBullet = new CScythe;

	if (FAILED(pBullet->Init()))
	{
		return nullptr;
	}

	pBullet->SetPos(pos);
	pBullet->SetMove(move);
	pBullet->SetSize(D3DXVECTOR2(45.0f, 45.0f));
	pBullet->SetTexture(CObject::TextureScythe);
	pBullet->SetTextureParameter(1, 1, 1, INT_MAX);
	pBullet->SetRotation(D3DX_PI * 0.05f);
	pBullet->FlipX();

	pBullet->m_pHitbox = CCircleHitbox::Create(pos, 25.0f, CHitbox::Type_EnemyBullet);

	return pBullet;
}