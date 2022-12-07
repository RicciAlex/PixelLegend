//=============================================================================
//
// laugh.cpp
// Author : Ricci Alex
//
//=============================================================================

//インクルードファイル
#include "laugh.h"
#include "squareHitbox.h"
#include "Letter.h"

//コンストラクタ
CLaughBullet::CLaughBullet()
{
	m_pHitbox = nullptr;
}

//デストラクタ
CLaughBullet::~CLaughBullet()
{

}

//初期化処理
HRESULT CLaughBullet::Init(void)
{
	if (FAILED(CBullet::Init()))
	{
		return -1;
	}

	m_pHitbox = nullptr;

	return S_OK;
}

//終了処理
void CLaughBullet::Uninit(void)
{
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}

	CBullet::Uninit();
}

//更新処理
void CLaughBullet::Update(void)
{
	D3DXVECTOR3 pos = GetPos() + GetMove();
	D3DXVECTOR2 size = GetSize();
	
	CBullet::Update();

	if (pos.x + size.x > 0.0f && pos.x + size.x < (float)SCREEN_WIDTH &&
		pos.y + size.y > 0.0f && pos.y - size.y < (float)SCREEN_HEIGHT)
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
	}
}




//生成処理
CLaughBullet* CLaughBullet::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move)
{
	CLaughBullet* pBullet = new CLaughBullet;

	if (FAILED(pBullet->Init()))
	{
		return nullptr;
	}

	pBullet->SetPos(pos);
	pBullet->SetSize(D3DXVECTOR2(45.0f, 40.0f));
	pBullet->SetMove(move);
	pBullet->SetLife(300);
	pBullet->SetStartingRot(D3DX_PI * 0.5f);

	pBullet->SetTexture(CObject::TextureLaugh);
	pBullet->SetTextureParameter(1, 1, 1, INT_MAX);

	pBullet->m_pHitbox = CSquareHitbox::Create(pos, D3DXVECTOR2(40.0f, 35.0f), CHitbox::Type_EnemyBullet);

	return pBullet;
}