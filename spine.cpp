//=============================================================================
//
// spine.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "spine.h"
#include "vertebra.h"

//コンストラクタ
CSpine::CSpine()
{
	//メンバー変数をクリアする
	for (int nCnt = 0; nCnt < VertebraNumber; nCnt++)
	{
		m_pVertebra[nCnt] = nullptr;
	}
	m_anchor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_head = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCntDestroy = 0;
	m_bDead = false;
}

//デストラクタ
CSpine::~CSpine()
{

}

//初期化処理
HRESULT CSpine::Init(void)
{
	//メンバー変数の初期化処理
	for (int nCnt = 0; nCnt < VertebraNumber; nCnt++)
	{
		if (m_pVertebra[nCnt] != nullptr)
		{
			m_pVertebra[nCnt] = nullptr;
		}
	}

	m_anchor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_head = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCntDestroy = 0;
	m_bDead = false;

	return S_OK;
}

//終了処理
void CSpine::Uninit(void)
{
	//骨の破棄処理
	for (int nCnt = 0; nCnt < VertebraNumber; nCnt++)
	{
		if (m_pVertebra[nCnt] != nullptr)
		{//nullチェック
			m_pVertebra[nCnt]->Release();			//メモリを解放する
			m_pVertebra[nCnt] = nullptr;			//ポインタをnullにする
		}
	}
}

//更新処理
void CSpine::Update(void)
{
	if (!m_bDead)
	{//死んでいない場合
		D3DXVECTOR3 dir = (m_head - m_anchor) * 0.125f;

		for (int nCnt = 0; nCnt < VertebraNumber; nCnt++)
		{
			if (m_pVertebra[nCnt])
			{//nullチェック
				m_pVertebra[nCnt]->SetPos(m_anchor + (dir * (float)(nCnt + 1)));			//位置の更新
			}
		}
	}
	else
	{//死んだ場合

		//死亡アニメーション処理
		m_nCntDestroy--;

		if (m_nCntDestroy <= 0)
		{//死亡アニメーションが終わったら
			Release();			//メモリを解放する
		}
	}
}

//描画処理
void CSpine::Draw(void)
{
	
}

//位置の設定処理
void CSpine::SetPos(const D3DXVECTOR3 pos)
{
	m_anchor = pos;
}

//頭の位置の設定処理
void CSpine::SetHeadPos(const D3DXVECTOR3 pos)
{
	m_head = pos;
}

//サイズの取得処理
const D3DXVECTOR2 CSpine::GetSize(void)
{
	return D3DXVECTOR2(0.0f, 0.0f);
}

//位置の設定処理
const D3DXVECTOR3 CSpine::GetPos(void)
{
	return m_anchor;
}

//死亡アニメーション処理
void CSpine::Kill(void)
{
	m_bDead = true;			//死んだ状態にする
	D3DXVECTOR3 dir;

	for (int nCnt = 0; nCnt < VertebraNumber; nCnt++)
	{
		if (m_pVertebra[nCnt])
		{//nullチェック

			//ランダムな方向に動かせて、下向きの加速を設定して、回転させる
			dir = D3DXVECTOR3((float)random(-5000, 5000), (float)random(-5000, 5000), 0.0f);
			D3DXVec3Normalize(&dir, &dir);
			dir.x *= 2.0f;
			dir.y *= 2.0f;

			m_pVertebra[nCnt]->SetMove(dir);
			m_pVertebra[nCnt]->SetRotation(((float)random(-100, 100) * 0.01f) * D3DX_PI * 0.25f);
			m_pVertebra[nCnt]->SetAcceleration(D3DXVECTOR3(0.0f, 0.05f, 0.0f));
			m_nCntDestroy = 120;
		}
	}
}

//テクスチャの反転処理
void CSpine::Flip(void)
{
	for (int nCnt = 0; nCnt < CSpine::VertebraNumber; nCnt++)
	{
		if (m_pVertebra[nCnt] != nullptr)
		{//nullチェック
			m_pVertebra[nCnt]->FlipX();		//テクスチャを反転する
		}
	}
}


//==================================================================================================
//								静的関数
//==================================================================================================

//生成処理
CSpine* CSpine::Create(D3DXVECTOR3 anchor, D3DXVECTOR3 head)
{
	D3DXVECTOR3 dir = (head - anchor) * 0.125f;

	CSpine* pSpine = new CSpine;			//インスタンスを生成する

	if (FAILED(pSpine->Init()))
	{//初期化処理
		return nullptr;
	}
	
	for (int nCnt = 0; nCnt < VertebraNumber; nCnt++)
	{
		pSpine->m_anchor = anchor;			//生成位置の設定
		pSpine->m_head = head;				//頭の位置の設定
		pSpine->m_pVertebra[nCnt] = CVertebra::Create(anchor + (dir * (float)(nCnt + 1)), D3DXVECTOR2(18.75f, 18.75f));		//骨を生成する
	}

	return pSpine;							//生成したインスタンスを返す
} 