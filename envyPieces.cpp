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
	//メンバー変数をクリアする
	m_pHitbox = nullptr;
}

//デストラクタ
CEnvyPieces::~CEnvyPieces()
{

}

//初期化処理
HRESULT CEnvyPieces::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CBullet::Init()))
	{
		return -1;
	}

	//メンバー変数を初期化する
	m_pHitbox = nullptr;

	return S_OK;
}

//終了処理
void CEnvyPieces::Uninit(void)
{
	//ヒットボックスの破棄
	if (m_pHitbox != nullptr)
	{//nullチェック
		m_pHitbox->Release();		//メモリを解放する
		m_pHitbox = nullptr;		//ポインタをnullにする
	}

	//基本クラスの終了処理
	CBullet::Uninit();
}

//更新処理
void CEnvyPieces::Update(void)
{
	//基本クラスの更新処理
	CObject_2D::Update();

	//ヒットボックスの更新処理
	if (m_pHitbox != nullptr)
	{//nullチェック

		m_pHitbox->SetPos(GetPos());		//ヒットボックスの位置の更新

		if (m_pHitbox->Hit())
		{//何かと当たったら、消す
			Release();
			return;
		}
	}

	//画面を出たら、消す
	if (GetPos().y >= 900.0f)
	{
		Release();
		return;
	}
}


//=============================================================================
//
//								静的関数
//
//=============================================================================



//生成処理
CEnvyPieces* CEnvyPieces::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move)
{
	CEnvyPieces* pBullet = new CEnvyPieces;		//インスタンスを生成する

	if (FAILED(pBullet->Init()))
	{//初期化処理
		return nullptr;
	}

	pBullet->SetPos(pos);													//位置の設定
	pBullet->SetMove(move);													//速度の設定
	pBullet->SetAcceleration(D3DXVECTOR3(0.0f, 0.05f, 0.0f));				//加速の設定
	pBullet->SetSize(D3DXVECTOR2(15.0f, 15.0f));							//サイズの設定
	pBullet->SetRotation(D3DX_PI * ((float)random(-50, 50) * 0.002f));		//回転させる

	//ランダムでテクスチャを設定する
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

	//ヒットボックスの生成
	pBullet->m_pHitbox = CCircleHitbox::Create(pos, 14.0f, CHitbox::Type_EnemyBullet);

	return pBullet;			//生成したインスタンスを返す
	
}

//生成処理
CEnvyPieces* CEnvyPieces::Create(const D3DXVECTOR3 pos, const float radius)
{
	CEnvyPieces* pBullet = new CEnvyPieces;		//インスタンスを生成する

	if (FAILED(pBullet->Init()))
	{//初期化処理
		return nullptr;
	}

	//ランダムで速度の設定する
	D3DXVECTOR3 P = pos;
	P.x += (float)random((int)-radius, (int)radius);
	P.y += (float)random((int)-radius, (int)radius);

	D3DXVECTOR3 move = D3DXVECTOR3((float)random(-1000, 1000), (float)random(-1000, 1000), 0.0f);
	D3DXVec3Normalize(&move, &move);
	int K = random(2, 7);
	move.x *= (float)K;
	move.y *= (float)K;

	pBullet->SetPos(P);														//位置の設定
	pBullet->SetMove(move);													//速度の設定
	pBullet->SetAcceleration(D3DXVECTOR3(0.0f, 0.05f, 0.0f));				//加速の設定
	pBullet->SetSize(D3DXVECTOR2(15.0f, 15.0f));							//サイズの設定
	pBullet->SetRotation(D3DX_PI * ((float)random(-50, 50) * 0.002f));		//回転させる


	//ランダムでテクスチャを設定する
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

	return pBullet;				//生成したインスタンスを返す
}
