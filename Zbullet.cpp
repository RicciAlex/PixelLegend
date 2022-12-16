//=============================================================================
//
// Zbullet.cpp
// Author : Ricci Alex
//
//=============================================================================

//インクルードファイル
#include "Zbullet.h"
#include "squareHitbox.h"

//コンストラクタ
CZBullet::CZBullet()
{
	//メンバー変数をクリアする
	m_nCntSize = 0;
	m_fGrowth = 0.0f;
	m_pHitbox = nullptr;
}

//デストラクタ
CZBullet::~CZBullet()
{

}

//初期化処理
HRESULT CZBullet::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CBullet::Init()))
	{
		return -1;
	}

	//メンバー変数の初期化
	m_nCntSize = 0;
	m_fGrowth = 1.0f;

	return S_OK;
}

//終了処理
void CZBullet::Uninit(void)
{
	//ヒットボックスの破棄処理
	if (m_pHitbox != nullptr)
	{//nullチェック
		m_pHitbox->Release();			//メモリを解放する
		m_pHitbox = nullptr;			//ポインタをnullにする
	}

	//基本クラスの終了処理
	CBullet::Uninit();
}

//更新処理
void CZBullet::Update(void)
{
	//サイズの変更
	m_nCntSize++;

	if (m_nCntSize >= 30)
	{//30フレームごと減数の符号を逆にする

		m_nCntSize = 0;
		m_fGrowth *= -1.0f;
	}

	//サイズの更新
	D3DXVECTOR2 size = GetSize();
	size += D3DXVECTOR2(m_fGrowth, m_fGrowth);
	SetSize(size);

	//ヒットボックスの更新処理
	if (m_pHitbox)
	{
		m_pHitbox->SetPos(GetPos());				//位置の取得
		m_pHitbox->SetSize(size);					//サイズの取得

		if (m_pHitbox->Hit())
		{//プレイヤーと当たった場合、消す
			Release();
			return;
		}
	}

	//基本クラスの更新処理
	CBullet::Update();
}


//=============================================================================
//静的関数
//=============================================================================

//生成処理
CZBullet* CZBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	CZBullet* pBullet = new CZBullet;					//新しい弾を生成する

	//初期化処理
	if (FAILED(pBullet->Init()))
	{
		return nullptr;
	}

	pBullet->SetPos(pos);									//位置の設定
	pBullet->SetMove(move);									//速度の設定

	pBullet->SetTexture(CObject::TextureLetters);			//テクスチャの設定
	pBullet->SetTextureParameter(26, 13, 2, INT_MAX);		//テクスチャパラメータの設定処理
	pBullet->SetAnimPattern(25);							//アニメーションパターンの設定
	pBullet->SetSize(D3DXVECTOR2(35.0f, 35.0f));			//サイズの設定

	pBullet->SetStartingRot((D3DX_PI * 0.5f));				//回転角度の設定

	//ヒットボックスの生成
	pBullet->m_pHitbox = CSquareHitbox::Create(pos, D3DXVECTOR2(31.0f, 31.0f), CHitbox::Type_EnemyBullet);

	return pBullet;											//弾を返す
} 