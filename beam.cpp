//=============================================================================
//
// beam.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "beam.h"
#include "application.h"
#include "rendering.h"
#include "squareHitbox.h"

//コンストラクタ
CBeam::CBeam()
{
	//メンバー変数をクリアする
	m_pHitbox = nullptr;
}

//デストラクタ
CBeam::~CBeam()
{

}

//初期化処理
HRESULT CBeam::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CBullet::Init()))
	{
		return -1;
	}

	return S_OK;
}

//終了処理
void CBeam::Uninit(void)
{
	//ヒットボックスの破棄
	if (m_pHitbox != nullptr)
	{//nullチェック
		m_pHitbox->Release();			//メモリを解放する
		m_pHitbox = nullptr;			//ポインタをnullにする
	}

	//基本クラスの終了処理
	CBullet::Uninit();
}

//更新処理
void CBeam::Update(void)
{
	//ヒットボックスの更新処理
	if (m_pHitbox != nullptr)
	{//nullチェック

		m_pHitbox->SetPos(GetPos());			//ヒットボックスの位置の更新

		m_pHitbox->Hit();						//何かと当たったかどうかを確認する
	}

	//基本クラスの更新処理
	CBullet::Update();
}

//描画処理
void CBeam::Draw(void)
{
	//デバイスの取得処理
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->CRenderer::GetDevice();

	//加算合成の設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//基本クラスの描画処理
	CObject_2D::Draw();

	// 設定を元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}


//=============================================================================
//
//									静的関数
//
//=============================================================================


//生成処理
CBeam* CBeam::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const D3DXVECTOR2 size, D3DXCOLOR col)
{
	CBeam* pBullet = new CBeam;				//新しい弾の生成

	//初期化処理
	if (FAILED(pBullet->Init()))
	{
		return nullptr;
	}

	pBullet->SetPos(pos);								//位置の設定
	pBullet->SetMove(move);								//速度の設定
	pBullet->SetSize(size);								//サイズの設定
	pBullet->SetTexture(TextureNull);					//テクスチャの設定
	pBullet->SetTextureParameter(1, 1, 1, INT_MAX);		//テクスチャパラメータの設定

	pBullet->m_pHitbox = CSquareHitbox::Create(pos, size, CHitbox::Type_EnemyBullet);			//ヒットボックスの生成
	
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = pBullet->GetVtxbuff();			//頂点バッファの取得処理
	VERTEX_2D* pVtx = nullptr;											//頂点情報へのポインタ

	//頂点バッファのロック
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カーラーの設定
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//頂点バッファをアンロックする
	pVtxBuff->Unlock();

	return pBullet;				//弾を返す
} 