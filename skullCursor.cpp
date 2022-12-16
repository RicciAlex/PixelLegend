//=============================================================================
//
// skullCursor.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "skullCursor.h"
#include "application.h"
#include "skull.h"
#include "spine.h"

//コンストラクタ
CSkullCursor::CSkullCursor()
{
	//メンバー変数をクリアする
	m_skullPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_pSpine = nullptr;
	m_pSkull = nullptr;
}

//デストラクタ
CSkullCursor::~CSkullCursor()
{

}

//初期化処理
HRESULT CSkullCursor::Init(void)
{
	//メンバー変数を初期化する
	m_skullPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_pSpine = nullptr;
	m_pSkull = nullptr;

	return S_OK;
}

//終了処理
void CSkullCursor::Uninit(void)
{
	if (m_pSkull != nullptr)
	{//nullチェック
		m_pSkull->Release();		//メモリを解放する
		m_pSkull = nullptr;			//nullにする
	}

	if (m_pSpine != nullptr)
	{//nullチェック	
		m_pSpine->Release();		//メモリを解放する
		m_pSpine = nullptr;			//nullにする
	}
}

//更新処理
void CSkullCursor::Update(void)
{
	//マウスカーソルの位置の取得と変換
	POINT pt;
	GetCursorPos(&pt);
	HWND wnd = CApplication::GetWindow();
	ScreenToClient(wnd, &pt);

	m_skullPos.y = (float)pt.y;			//位置のY座標の設定

	if (m_pSkull != nullptr)
	{//nullチェック
		m_pSkull->SetPos(m_skullPos);		//位置の設定
	}
	
	if (m_pSpine != nullptr)
	{//nullチェック
		m_pSpine->SetHeadPos(m_skullPos);	//位置の設定
	}
}





//生成処理
CSkullCursor* CSkullCursor::Create(const D3DXVECTOR3 pos)
{
	CSkullCursor* pCursor = new CSkullCursor;			//インスタンスの生成

	if (FAILED(pCursor->Init()))
	{//初期化処理
		return nullptr;
	}

	//マウスカーソルの位置の取得と変換
	POINT pt;
	GetCursorPos(&pt);
	HWND wnd = CApplication::GetWindow();
	ScreenToClient(wnd, &pt);

	//位置の計算と設定
	float fNum = 350.0f;

	if (pos.x < (float)SCREEN_WIDTH * 0.5f)
	{
		fNum *= -1.0f;
	}

	pCursor->m_skullPos = D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f + fNum, (float)pt.y, 0.0f);	
	pCursor->m_pSkull = CSkull::Create(pCursor->m_skullPos, D3DXVECTOR2(60.0f, 60.0f));	
	pCursor->m_pSpine = CSpine::Create(pos, pCursor->m_skullPos);

	if (pCursor->m_pSkull != nullptr && pCursor->m_pSpine != nullptr)
	{//nullチェック
		pCursor->m_pSkull->SetPriority(4);			//プライオリティの設定

		if (pos.x < (float)SCREEN_WIDTH * 0.5f)
		{//位置によってテクスチャを反転する
			pCursor->m_pSkull->FlipX();
			pCursor->m_pSpine->Flip();
		}
	}

	return pCursor;				//生成したインスタンスを返す
}