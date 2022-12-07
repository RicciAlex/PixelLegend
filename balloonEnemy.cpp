//=============================================================================
//
// enemy.cpp
// Author : Ricci Alex
//
//=============================================================================

//インクルードファイル
#include "balloonEnemy.h"
#include "circleHitbox.h"
#include "player.h"
#include "explosion.h"
#include "application.h"
#include "sound.h"

CBalloonEnemy::CBalloonEnemy()
{
	m_pHitbox = nullptr;
}

CBalloonEnemy::~CBalloonEnemy()
{

}

//初期化処理
HRESULT CBalloonEnemy::Init(void)
{
	if (FAILED(CEnemy::Init()))
	{
		return -1;
	}

	m_pHitbox = nullptr;

	return S_OK;
}

//終了処理
void CBalloonEnemy::Uninit(void)
{
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}

	CEnemy::Uninit();
}

//更新処理
void CBalloonEnemy::Update(void)
{
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 playerPos = CPlayer::GetPlayer()->GetPos();
	D3DXVECTOR3 target = playerPos - pos;
	D3DXVec3Normalize(&target, &target);
	target.x *= 2.5f;
	target.y *= 2.5f;
	target += GetMove();
	D3DXVec3Normalize(&target, &target);
	target.x *= 2.5f;
	target.y *= 2.5f;

	SetMove(target);

	m_pHitbox->SetPos(pos);

	int nLife = GetLife();
	nLife--;

	if (nLife <= 0)
	{
		CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_EXPLOSION);		//爆発のサウンドエフェクト
		CExplosion* pExplosion = CExplosion::Create();
		pExplosion->SetPos(pos);
		pExplosion->SetSize(D3DXVECTOR2(30.0f, 30.0f));

		Release();
		return;
	}
	else
	{
		SetLife(nLife);
	}

	CObject_2D::Update();
}

//描画処理
void CBalloonEnemy::Draw(void)
{
	CEnemy::Draw();
}



CBalloonEnemy* CBalloonEnemy::Create(D3DXVECTOR3 pos)
{
	CBalloonEnemy* pEnemy = new CBalloonEnemy;

	if (FAILED(pEnemy->Init()))
	{
		return nullptr;
	}

	pEnemy->SetPos(pos);
	pEnemy->SetStartingRot(D3DX_PI * 0.5f);
	pEnemy->SetSize(D3DXVECTOR2(25.0f, 25.0f));
	pEnemy->SetTexture(CObject::TextureBalloonEnemy);
	pEnemy->SetTextureParameter(1, 1, 1, INT_MAX);
	pEnemy->SetLife(random(120, 360));

	D3DXVECTOR3 playerPos = CPlayer::GetPlayer()->GetPos();
	D3DXVECTOR3 target = playerPos - pos;
	D3DXVec3Normalize(&target, &target);
	target.x *= 2.5f;
	target.y *= 2.5f;

	pEnemy->SetMove(target);

	pEnemy->m_pHitbox = CCircleHitbox::Create(pos, 25.0f, CHitbox::Type_Enemy);

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

	pEnemy->SetColor(col);

	return pEnemy;
}