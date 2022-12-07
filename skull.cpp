//=============================================================================
//
// skull.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "Skull.h"
#include "player.h"
#include "squareHitbox.h"

//コンストラクタ
CSkull::CSkull()
{
	//メンバー変数をクリアする
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCntDestroy = 0;
	m_bDead = false;

	m_pHitbox = nullptr;
}

//デストラクタ
CSkull::~CSkull()
{

}

//初期化処理
HRESULT CSkull::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CEnemy::Init()))
	{
		return -1;
	}

	//メンバー変数の初期化
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCntDestroy = 0;
	m_bDead = false;
	SetLife(5000);

	return S_OK;
}

//終了処理
void CSkull::Uninit(void)
{
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}

	//基本クラスの終了処理
	CEnemy::Uninit();
}

//更新処理
void CSkull::Update(void)
{
	//基本クラスの更新処理
	CObject_2D::Update();

	m_pHitbox->SetPos(GetPos());

	if (m_pHitbox->Hit() || m_pHitbox->GetHitState())
	{
		int nDamage = CPlayer::GetPlayer()->GetAttack();
		SetLife(GetLife() - nDamage);
		m_pHitbox->SetHitState(false);
	}

	//死亡アニメーション処理
	if (m_bDead)
	{
		m_nCntDestroy--;

		if (m_nCntDestroy <= 0)
		{
			Release();
		}
	}
}

//死亡アニメーション処理
void CSkull::Kill(void)
{
	m_bDead = true;

	D3DXVECTOR3 dir = D3DXVECTOR3((float)random(-5000, 5000), (float)random(-5000, 5000), 0.0f);
	D3DXVec3Normalize(&dir, &dir);
	dir.x *= 2.0f;
	dir.y *= 2.0f;

	SetMove(dir);
	SetRotation(((float)random(-100, 100) * 0.01f) * D3DX_PI * 0.1f);
	SetAcceleration(D3DXVECTOR3(0.0f, 0.05f, 0.0f));
	m_nCntDestroy = 120;
}


//========================================================================================================
//										静的関数
//========================================================================================================

//生成処理
CSkull* CSkull::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	CSkull* pSkull = new CSkull;					//メモリを確保する

	//初期化処理
	if (FAILED(pSkull->Init()))
	{
		return nullptr;
	}

	pSkull->SetPos(pos);										//位置の設定
	pSkull->SetSize(size);										//サイズの設定

	pSkull->SetObjType(CObject::OBJTYPE_ENEMY);					//オブジェクトの種類の設定

	pSkull->SetStartingRot(D3DX_PI * 0.5f);						//回転角度の初期値の設定
	pSkull->SetMaxSpeed(12.5f);									//最大速度の設定
	pSkull->SetTextureParameter(1, 3, 1, INT_MAX);				//テクスチャパラメータの設定
	pSkull->SetSize(size);										//サイズの設定

	pSkull->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));				//速度の設定
	pSkull->SetAcceleration(D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//加速の設定
	pSkull->SetSubtype(ENEMYTYPE_SKULL);						//敵の種類の設定

	pSkull->SetTexture(TextureSkull);							//テクスチャの設定

	pSkull->m_pHitbox = CSquareHitbox::Create(pos, D3DXVECTOR2(size.x * 0.5f, size.y * 0.5f), CHitbox::Type_Enemy);

	return pSkull;
} 