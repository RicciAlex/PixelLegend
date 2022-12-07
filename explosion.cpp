//=============================================================================
//
// explosion.cpp
// Author : Ricci Alex
//
//=============================================================================

//インクルードファイル
#include "explosion.h"

//コンストラクタ
CExplosion::CExplosion()
{
	//メンバー変数をクリアする
	m_nLastPattern = 0;
}

//デストラクタ
CExplosion::~CExplosion()
{

}

//初期化処理
HRESULT CExplosion::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CObject_2D::Init()))
	{
		return -1;
	}

	SetTexture(CObject::TextureExplosion);				//テクスチャの設定
	SetTextureParameter(24, 5, 5, 2);			//テクスチャパラメータの設定処理
	SetSize(D3DXVECTOR2(20.0f, 20.0f));			//サイズの初期化
												
	m_nLastPattern = 0;							//前回のアニメーションパターンの初期化

	return S_OK;
} 

//終了処理
void CExplosion::Uninit(void)
{
	//基本クラスの終了処理
	CObject_2D::Uninit();
}

//更新処理
void CExplosion::Update(void)
{
	//基本クラスの更新処理
	CObject_2D::Update();

	//アニメーションが終了したかどうかを判定する
	if (GetPresentAnimPattern() < m_nLastPattern)
	{//終了した場合
		//爆発のインスタンスを消す
		Release();
		return;
	}

	m_nLastPattern = GetPresentAnimPattern();		//前回のアニメーションパターンの更新
}

//生成処理
CExplosion* CExplosion::Create(void)
{
	CExplosion* pExplosion = nullptr;

	pExplosion = new CExplosion;								//新しい爆発を生成する
		
	//初期化処理
	if (FAILED(pExplosion->Init()))
	{//できなかったら
		return nullptr;
	}

	pExplosion->SetObjType(CObject::OBJTYPE_EXPLOSION);			//オブジェクトの種類の設定

	return pExplosion;											//ポインタを返す
}