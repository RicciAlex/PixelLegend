//=============================================================================
//
// target.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "target.h"
#include "application.h"

//コンストラクタ
CTarget::CTarget()
{

}

//デストラクタ
CTarget::~CTarget()
{

}

//初期化処理
HRESULT CTarget::Init(void)
{
	if (FAILED(CObject_2D::Init()))
	{//基本クラスの初期化処理
		return -1;
	}

	return S_OK;
}

//終了処理
void CTarget::Uninit(void)
{
	//基本クラスの終了処理
	CObject_2D::Uninit();
}

//更新処理
void CTarget::Update(void)
{
	//マウスカーソルの位置の取得と変換
	POINT pt;
	GetCursorPos(&pt);
	HWND wnd = CApplication::GetWindow();
	ScreenToClient(wnd, &pt);

	D3DXVECTOR3 pos = D3DXVECTOR3((float)pt.x, (float)pt.y, 0.0f);

	SetPos(pos);			//位置の設定

	//基本クラスの更新処理
	CObject_2D::Update();
}




//生成処理
CTarget* CTarget::Create(void)
{
	CTarget* pTarget = new CTarget;			//インスタンスを生成する

	if (FAILED(pTarget->Init()))
	{//初期化処理
		return nullptr;
	}

	//マウスカーソルの位置の取得と変換
	POINT pt;
	GetCursorPos(&pt);
	HWND wnd = CApplication::GetWindow();
	ScreenToClient(wnd, &pt);

	D3DXVECTOR3 pos = D3DXVECTOR3((float)pt.x, (float)pt.y, 0.0f);

	pTarget->SetPos(pos);										//位置の設定
	pTarget->SetTexture(CObject::TextureTarget);				//テクスチャの設定
	pTarget->SetSize(D3DXVECTOR2(30.0f, 30.0f));				//サイズの設定
	pTarget->SetTextureParameter(1, 1, 1, INT_MAX);				//テクスチャパラメータの設定
	pTarget->SetPriority(5);									//プライオリティの設定
	pTarget->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));		//色の設定

	return pTarget;					//生成したインスタンスを返す
}