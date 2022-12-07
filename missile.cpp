//=============================================================================
//
// missile.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "missile.h"
#include "squareHitbox.h"
#include "player.h"
#include "application.h"
#include "sound.h"

CMissile::CMissile()
{
	m_state = state_max;
	m_pHitbox = nullptr;
}

CMissile::~CMissile()
{

}

//初期化処理
HRESULT CMissile::Init(void)
{
	if (FAILED(CBullet::Init()))
	{
		return -1;
	}

	m_state = state_ascend;
	m_pHitbox = nullptr;

	return S_OK;
}

//終了処理
void CMissile::Uninit(void)
{
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}

	CBullet::Uninit();
}

//更新処理
void CMissile::Update(void)
{
	CObject_2D::Update();								//基本クラスの更新処理

	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR2 size = GetSize();

	switch (m_state)
	{
	case CMissile::state_ascend:

		if (pos.y <= -150.0f)
		{
			SetStartingRot(D3DX_PI);
			pos.x = CPlayer::GetPlayer()->GetPos().x;

			D3DXVECTOR3 move = GetMove();
			move.x = 0.0f;
			move.y = 0.0f;

			SetAcceleration(D3DXVECTOR3(0.0f, 0.2f, 0.0f));
			SetPos(pos);
			SetMove(move);
			
			m_state = state_descend;
		}

		break;

	case CMissile::state_descend:

		if (pos.y - 200.0f >= (float)SCREEN_HEIGHT)
		{
			Release();
			return;
		}

		break;

	case state_strike:



		break;

	default:
		break;
	}

	if (m_pHitbox != nullptr)
	{
		m_pHitbox->SetPos(GetPos());

		if (m_pHitbox->Hit())
		{
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_BIG_EXPLOSION);
			Release();
			return;
		}
	}
}





//生成処理
CMissile* CMissile::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move)
{
	CMissile* pBullet = new CMissile;

	if (FAILED(pBullet->Init()))
	{
		return nullptr;
	}

	pBullet->SetPos(pos);
	pBullet->SetMove(move);
	pBullet->SetSize(D3DXVECTOR2(67.5f, 16.5f));
	pBullet->SetTexture(CObject::TextureMissile);
	pBullet->SetTextureParameter(2, 1, 2, 15);
	pBullet->SetPriority(2);

	pBullet->m_pHitbox = CSquareHitbox::Create(pos ,D3DXVECTOR2(30.0f, 8.0f), CHitbox::Type_EnemyBullet);

	return pBullet;
}

//生成処理
CMissile* CMissile::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const D3DXVECTOR3 acc)
{
	CMissile* pBullet = new CMissile;

	if (FAILED(pBullet->Init()))
	{
		return nullptr;
	}

	pBullet->SetPos(pos);
	pBullet->SetMove(move);
	pBullet->SetSize(D3DXVECTOR2(67.5f, 16.5f));
	pBullet->SetTexture(CObject::TextureMissile);
	pBullet->SetTextureParameter(2, 1, 2, 15);
	pBullet->SetPriority(2);
	pBullet->SetAcceleration(acc);
	pBullet->m_state = state_strike;
	pBullet->SetStartingRot(D3DX_PI * 0.5f);

	pBullet->m_pHitbox = CSquareHitbox::Create(pos, D3DXVECTOR2(30.0f, 8.0f), CHitbox::Type_EnemyBullet);

	return pBullet;
}