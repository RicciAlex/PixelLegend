//=============================================================================
//
// bouncingBullet.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "bouncingBullet.h"
#include "circleHitbox.h"

//コンストラクタ
CBouncingBullet::CBouncingBullet()
{
	//メンバー変数をクリアする
	m_pHitbox = nullptr;
}

//デストラクタ
CBouncingBullet::~CBouncingBullet()
{

}

//初期化処理
HRESULT CBouncingBullet::Init(void)
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
void CBouncingBullet::Uninit(void)
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
void CBouncingBullet::Update(void)
{
	//寿命の取得と更新
	int nLife = GetLife();
	nLife--;

	if (nLife <= 0)
	{//寿命が0以下になったら、消す
		Release();
		return;
	}
	else
	{//寿命が0以上だったら、寿命を設定する
		SetLife(nLife);
	}

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

	//画面を出る前、反射させる
	D3DXVECTOR3 pos, move;

	pos = GetPos();
	move = GetMove();
	pos += move;

	if (pos.x + GetSize().x <= 0.0f || pos.x + GetSize().x >= (float)SCREEN_WIDTH)
	{
		move.x *= -1.0f;
		SetMove(move);
	}

	if (pos.y + GetSize().y <= 0.0f || pos.y - GetSize().y >= (float)SCREEN_HEIGHT)
	{
		move.y *= -1.0f;
		SetMove(move);
	}

	//基本クラスの更新処理
	CBullet::Update();
}


//=============================================================================
//
//								静的関数
//
//=============================================================================



//生成処理
CBouncingBullet* CBouncingBullet::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move)
{
	CBouncingBullet* pBullet = new CBouncingBullet;		//インスタンスを生成する

	if (FAILED(pBullet->Init()))
	{//初期化処理
		return nullptr;
	}

	pBullet->SetPos(pos);								//位置の設定
	pBullet->SetMove(move);								//速度の設定
	pBullet->SetSize(D3DXVECTOR2(15.0f, 15.0f));		//サイズの設定
	pBullet->SetTexture(CObject::TextureNormalEffect);	//テクスチャの設定
	pBullet->SetTextureParameter(1, 1, 1, INT_MAX);		//テクスチャパラメータの設定
	pBullet->SetLife(300);								//寿命の設定

	//ランダムで色を設定する
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

	pBullet->SetColor(col);			//色の設定

	//ヒットボックスの生成
	pBullet->m_pHitbox = CCircleHitbox::Create(pos, 15.0f, CHitbox::Type_EnemyBullet);

	return pBullet;					//生成したインスタンスを返す
}