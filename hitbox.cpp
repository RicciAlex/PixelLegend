//=============================================================================
//
// hitbox.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "hitbox.h"

//静的変数の初期化
CHitbox* CHitbox::m_pHitbox[MaxHitbox] = {};

//コンストラクタ
CHitbox::CHitbox()
{
	//メンバー変数をクリアする
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Type = Type_Max;
	m_Shape = shape_Max;
	m_bHit = false;

	for (int nCnt = 0; nCnt < MaxHitbox; nCnt++)
	{
		if (m_pHitbox[nCnt] == nullptr)
		{
			m_nIdx = nCnt;
			m_pHitbox[nCnt] = this;
			break;
		}
	}
}

//デストラクタ
CHitbox::~CHitbox()
{

}

//初期化処理
HRESULT CHitbox::Init(void)
{
	//メンバー変数の初期化
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Type = Type_Max;
	m_Shape = shape_Max;
	m_bHit = false;

	return S_OK;
}

//終了処理
void CHitbox::Uninit(void)
{

}

//インスタンス１つを消す処理
void CHitbox::Release(void)
{
	int Idx = m_nIdx;					//配列のインデックスを保存する
	m_pHitbox[Idx]->Uninit();			//オブジェクトの終了処理
	delete m_pHitbox[Idx];				//オブジェクトを消す
	m_pHitbox[Idx] = nullptr;			//ポインタをnullにする
}

//位置の取得処理
const D3DXVECTOR3 CHitbox::GetPos(void)
{
	return m_pos;
}

//形の取得処理
const CHitbox::Shape CHitbox::GetShape(void)
{
	return m_Shape;
}

//種類の取得処理
const CHitbox::Type CHitbox::GetType(void)
{
	return m_Type;
}

//当たったかどうか
const bool CHitbox::GetHitState(void)
{
	return m_bHit;
}

//位置の設定処理
void CHitbox::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//サイズの設定処理
void CHitbox::SetType(const CHitbox::Type type)
{
	m_Type = type;
}

//形の設定処理
void CHitbox::SetShape(const CHitbox::Shape shape)
{
	m_Shape = shape;
}

//当たったかどうか
void CHitbox::SetHitState(const bool bHit)
{
	m_bHit = bHit;
}


//=============================================================================
//静的関数
//=============================================================================

//インスタンス全部の終了処理
void CHitbox::ReleaseAll(void)
{
	for (int nCnt = 0; nCnt < MaxHitbox; nCnt++)
	{
		if (m_pHitbox[nCnt] != nullptr)
		{//nullチェック
			m_pHitbox[nCnt]->Uninit();		//終了処理
			delete m_pHitbox[nCnt];			//メモリを解放する
			m_pHitbox[nCnt] = nullptr;		//nullにする
		}
	}
}

//全部のインスタンスの情報の取得処理
CHitbox** CHitbox::GetAllHitbox(void)
{
	return &m_pHitbox[0];
}