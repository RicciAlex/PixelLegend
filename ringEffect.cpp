//=============================================================================
//
// ringEffect.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "ringEffect.h"
#include "application.h"
#include "rendering.h"

//コンストラクタ
CRingEffect::CRingEffect()
{
	//メンバー変数をクリアする
	m_deltaCol = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_deltaSize = D3DXVECTOR2(0.0f, 0.0f);
}

//デストラクタ
CRingEffect::~CRingEffect()
{

}

//初期化処理
HRESULT CRingEffect::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CEffect::Init()))
	{
		return -1;
	}

	//メンバー変数の初期化
	m_deltaCol = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_deltaSize = D3DXVECTOR2(0.0f, 0.0f);

	return S_OK;
}

//終了処理
void CRingEffect::Uninit(void)
{
	//基本クラスの終了処理
	CEffect::Uninit();
}

//更新処理
void CRingEffect::Update(void)
{
	//基本クラスの更新
	CEffect::Update();

	D3DXCOLOR col = GetColor();							//カーラーの取得
	D3DXVECTOR2 size = D3DXVECTOR2(0.0f, 0.0f);	
	size = CObject_2D::GetSize();						//サイズの取得

	col += m_deltaCol;									//カーラーの更新
	size += m_deltaSize;								//サイズのの更新

	if (size.x <= 0.0f || size.y <= 0.0f)
	{//サイズが0以下になったら、消す
		Release();
		return;
	}

	SetColor(col);										//カーラーの設定
	SetSize(size);										//サイズのの設定
}

//終了処理
void CRingEffect::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->CRenderer::GetDevice();

	//加算合成の設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//基本クラスの描画処理
	CEffect::Draw();

	// 設定を元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}


//==================================================================================================================
//
//		静的関数
//
//==================================================================================================================

//生成処理
CRingEffect* CRingEffect::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move,
	const D3DXVECTOR2 size, const D3DXVECTOR2 deltaSize, const D3DXCOLOR col, const D3DXCOLOR deltaCol)
{
	CRingEffect* pEffect = new CRingEffect;						//新しいエフェクトを生成する

	//初期化処理
	if (FAILED(pEffect->Init()))
	{
		return nullptr;
	}

	pEffect->SetPos(pos);										//位置の設定
	pEffect->SetMove(move);										//速度の設定
	pEffect->SetSize(size);										//サイズの設定
	pEffect->m_deltaSize = deltaSize;							//サイズの減数の設定	
	pEffect->SetColor(col);										//カーラーの設定
	pEffect->m_deltaCol = deltaCol;								//色の減数の設定
	pEffect->SetLife(600);										//ライフの設定

	pEffect->SetTexture(CObject::TextureRoundEffect);			//テクスチャの設定
	pEffect->SetTextureParameter(1, 1, 1, INT_MAX);				//テクスチャパラメータの設定

	return pEffect;												//エフェクトを返す
} 