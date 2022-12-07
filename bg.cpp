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

CBg::CBg()
{
	m_textMove = D3DXVECTOR2(0.0f, 0.0f);
}

CBg::~CBg()
{

}

//初期化処理
HRESULT CBg::Init(void)
{
	if (FAILED(CObject_2D::Init()))
	{
		return -1;
	}

	SetTexture(CObject::TextureSeaBG);
	SetTextureParameter(2, 1, 2, 30);
	m_textMove = D3DXVECTOR2(0.0f, 0.0f);

	SetPos(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f));
	SetSize(D3DXVECTOR2((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f));
	SetPriority(1);

	return S_OK;
}

//終了処理
void CBg::Uninit(void)
{
	CObject_2D::Uninit();
}

//更新処理
void CBg::Update(void)
{
	MoveTexCoordinates(m_textMove);

	CObject_2D::Update();
}

////終了処理
//void CBg::Draw(void)
//{
//	CObject_2D::Draw();
//} 

void CBg::SetColor(const D3DXCOLOR col)
{
	VERTEX_2D* pVtx = nullptr;

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxbuff();

	//頂点バッファのロック
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

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
	CBg* pBg = new CBg;

	if (FAILED(pBg->Init()))
	{
		return nullptr;
	}

	pBg->SetStartingRot(D3DX_PI * 0.5f);
	pBg->SetColor(col);
	pBg->m_textMove = textMove;

	return pBg;
}