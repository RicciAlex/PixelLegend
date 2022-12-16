//=============================================================================
//
// bg.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "bg.h"

//コンストラクタ
CBg::CBg()
{
	//メンバー変数をクリアする
	m_textMove = D3DXVECTOR2(0.0f, 0.0f);
}

//デストラクタ
CBg::~CBg()
{

}

//初期化処理
HRESULT CBg::Init(void)
{
	if (FAILED(CObject_2D::Init()))
	{//基本クラスの初期化処理
		return -1;
	}

	SetTexture(CObject::TextureSeaBG);			//テクスチャの設定
	SetTextureParameter(2, 1, 2, 30);			//テクスチャパラメータの設定
	m_textMove = D3DXVECTOR2(0.0f, 0.0f);		//テクスチャの移動量の設定

	SetPos(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f));	//位置の設定
	SetSize(D3DXVECTOR2((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f));		//サイズの設定
	SetPriority(1);																		//プライオリティの設定

	return S_OK;
}

//終了処理
void CBg::Uninit(void)
{
	//基本クラスの終了処理
	CObject_2D::Uninit();
}

//更新処理
void CBg::Update(void)
{
	//アニメーション
	MoveTexCoordinates(m_textMove);		

	//基本クラスの更新処理
	CObject_2D::Update();
}

//色の設定処理
void CBg::SetColor(const D3DXCOLOR col)
{
	VERTEX_2D* pVtx = nullptr;		//頂点情報へのポインタ

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxbuff();		//頂点バッファの終了

	//頂点バッファのロック
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点の色の設定
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//頂点バッファをアンロックする
	pVtxBuff->Unlock();
}


//生成処理
CBg* CBg::Create(const D3DXCOLOR col, const D3DXVECTOR2 textMove)
{
	CBg* pBg = new CBg;				//インスタを生成する

	if (FAILED(pBg->Init()))
	{//初期化処理
		return nullptr;
	}

	pBg->SetStartingRot(D3DX_PI * 0.5f);			//向きの初期値の設定
	pBg->SetColor(col);								//色の設定
	pBg->m_textMove = textMove;						//アニメション速度の設定

	return pBg;				//生成したインスタンスを返す
}