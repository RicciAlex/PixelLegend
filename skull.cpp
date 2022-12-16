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
	//ヒットボックスの破棄処理
	if (m_pHitbox != nullptr)
	{//nullチェック
		m_pHitbox->Release();		//メモリを解放する
		m_pHitbox = nullptr;		//ポインタをnullにする
	}

	//基本クラスの終了処理
	CEnemy::Uninit();
}

//更新処理
void CSkull::Update(void)
{
	//基本クラスの更新処理
	CObject_2D::Update();

	//ヒットボックスの更新処理
	if (m_pHitbox)
	{//nullチェック

		m_pHitbox->SetPos(GetPos());		//位置の設定

		if (m_pHitbox->Hit() || m_pHitbox->GetHitState())
		{//当たった状態だったら

			int nDamage = CPlayer::GetPlayer()->GetAttack();		//プレイヤーの攻撃力の取得
			SetLife(GetLife() - nDamage);							//体力更新との設定
			m_pHitbox->SetHitState(false);							//当っていない状態に戻す
		}
	}

	//死亡アニメーション処理
	if (m_bDead)
	{
		m_nCntDestroy--;			//死亡カウンターをデクリメントする

		if (m_nCntDestroy <= 0)
		{//死亡カウンターが0以下になったら
			Release();				//破棄する
		}
	}
}

//死亡アニメーション処理
void CSkull::Kill(void)
{
	m_bDead = true;			//死んだ状態にする

	//ランダムな方向に移動させて、回転させる
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

	//ヒットボックスの生成
	pSkull->m_pHitbox = CSquareHitbox::Create(pos, D3DXVECTOR2(size.x * 0.5f, size.y * 0.5f), CHitbox::Type_Enemy);

	return pSkull;							//生成したインスタンスを返す
} 