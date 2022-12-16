//=============================================================================
//
// effect.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "effect.h"

//コンストラクタ
CEffect::CEffect()
{
	//メンバー変数をクリアする
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
}

//デストラクタ
CEffect::~CEffect()
{

}

//初期化処理
HRESULT CEffect::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CObject_2D::Init()))
	{
		return -1;
	}

	//メンバー変数の初期化
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	SetObjType(CObject::OBJTYPE_EFFECT);

	return S_OK;
}

//終了処理
void CEffect::Uninit(void)
{
	//基本クラスの終了
	CObject_2D::Uninit();
}

//更新処理
void CEffect::Update(void)
{
	//基本クラスの更新処理
	CObject_2D::Update();

	//ライフの更新
	m_nLife--;

	if (m_nLife <= 0)
	{//ライフが0になったら、消す
		Release();
	}
}

//ライフの取得処理
const int CEffect::GetLife(void)
{
	return m_nLife;
}

//速度の設定処理
void CEffect::SetMove(const D3DXVECTOR3 move)
{
	m_move = move;
}

//ライフの設定処理
void CEffect::SetLife(const int Life)
{
	m_nLife = Life;
} 


//=============================================================================
//静的関数
//=============================================================================

//生成処理
CEffect* CEffect::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const D3DXCOLOR col, const D3DXVECTOR2 size, const int Life)
{
	CEffect* pEffect = new CEffect;					//新しいエフェクトを生成する

	//初期化処理
	if (FAILED(pEffect->Init()))
	{
		return nullptr;
	}

	pEffect->SetPos(pos);							//位置の設定
	pEffect->m_move = move;							//速度の設定
	pEffect->SetColor(col);							//カーラーの設定
	pEffect->m_nLife = Life;						//ライフの設定
	pEffect->SetSize(size);							//サイズの設定

	return pEffect;									//エフェクトを返す
}