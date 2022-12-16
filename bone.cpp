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
	//メンバー変数をクリアする
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
	{//基本クラスの初期化処理
		return -1;
	}

	//メンバー変数を初期化する
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
	//基本クラスの更新処理
	CObject_2D::Update();

	D3DXVECTOR3 pos = GetPos();		//位置の取得

	//ヒットボックスの更新処理
	if (m_pHitbox != nullptr)
	{//nullチェック

		m_pHitbox->SetPos(pos);		//ヒットボックスの位置の更新

		if (m_pHitbox->Hit())
		{//何かと当たったら、消す
			Release();
			return;
		}
	}

	//画面を出ないようにする
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
	{//壁と当たったら
		if (!m_bBroken)
		{//まだ折れていなかったら、折れる
			m_bBroken = true;
			Split();
			Release();
			return;
		}
		else
		{//もう折れた場合、消す
			Release();
			return;
		}
	}
}



//=============================================================================
//
//								静的関数
//
//=============================================================================



//生成処理
CBone* CBone::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move)
{
	CBone* pBullet = new CBone;			//インスタンスを生成する

	if (FAILED(pBullet->Init()))
	{//初期化処理
		return nullptr;
	}

	pBullet->SetPos(pos);												//位置の設定
	pBullet->SetSize(D3DXVECTOR2(35.0f, 10.7f));						//サイズの設定
	pBullet->SetMove(move);												//速度の設定
	pBullet->SetTexture(CObject_2D::TextureBone);						//テクスチャの設定
	pBullet->SetTextureParameter(1, 1, 2, INT_MAX);						//テクスチャパラメータの設定
	pBullet->SetRotation((float)random(-10, 10) * 0.0025f * D3DX_PI);	//回転させる
	pBullet->SetStartingRot(D3DX_PI * 0.5f);							//向きの初期値の設定
	pBullet->m_bBroken = false;											//折れていない状態にする

	//ヒットボックスの生成
	pBullet->m_pHitbox = CSquareHitbox::Create(D3DXVECTOR3(pos), D3DXVECTOR2(49.0f, 15.0f), CHitbox::Type_EnemyBullet);

	return pBullet;			//生成したインスタンスを返す
}


//=============================================================================
//
//							プライベート関数
//
//=============================================================================


//折れる処理
void CBone::Split(void)
{
	D3DXVECTOR3 pos = GetPos();								
	D3DXVECTOR3 move1 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		
	D3DXVECTOR3 move2 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		
	D3DXVECTOR3 V = GetMove();								
	float fSpeed = D3DXVec3Length(&V);						

	//位置によって新しい弾の速度を設定する
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

	//サイズを調整する
	D3DXVECTOR2 size = GetSize();
	size.x *= 0.5f;

	//新しい弾を生成して、必要なパラメータを設定する
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