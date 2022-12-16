//=============================================================================
//
// lifeIcon.h
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "lifeIcon.h"
#include "object2D.h"
#include "player.h"

//コンストラクタ
CLifeIcon::CLifeIcon()
{
	//メンバー変数をクリアする
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	for (int nCnt = 0; nCnt < MaxHeart; nCnt++)
	{
		m_pHeart[nCnt] = nullptr;
	}
}

//デストラクタ
CLifeIcon::~CLifeIcon()
{

}

//初期化処理
HRESULT CLifeIcon::Init(void)
{
	//メンバー変数を初期化する
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	for (int nCnt = 0; nCnt < MaxHeart; nCnt++)
	{
		m_pHeart[nCnt] = nullptr;
	}

	return S_OK;
}

//終了処理
void CLifeIcon::Uninit(void)
{
	//UIイメージの破棄処理
	for (int nCnt = 0; nCnt < MaxHeart; nCnt++)
	{
		if (m_pHeart[nCnt] != nullptr)
		{//nullチェック
			m_pHeart[nCnt]->Release();			//メモリを解放する
			m_pHeart[nCnt] = nullptr;			//nullにする
		}
	}
}

//更新処理
void CLifeIcon::Update(void)
{
	int nLife = CPlayer::GetPlayer()->GetLife();			//プレイヤーの体力の取得

	if (nLife <= 0)
	{//体力が0以下になったら
		m_pHeart[0]->SetAnimPattern(3);			//テクスチャを設定する
	}
	else if (nLife < 15)
	{//体力が最大値以下になったら
		m_pHeart[nLife / 3]->SetAnimPattern(3 - (nLife % 3));			//テクスチャを設定する
	}
}

//描画処理
void CLifeIcon::Draw(void)
{

}

//位置の設定処理
void CLifeIcon::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//サイズの取得処理
const D3DXVECTOR2 CLifeIcon::GetSize(void)
{
	return m_size;
}

//位置の取得処理
const D3DXVECTOR3  CLifeIcon::GetPos(void)
{
	return m_pos;
}



//生成処理
CLifeIcon* CLifeIcon::Create(const D3DXVECTOR3 pos)
{
	CLifeIcon* pIcon = new CLifeIcon;			//インスタンスを生成する

	if (FAILED(pIcon->Init()))
	{//初期化処理
		return nullptr;
	}

	pIcon->m_pos = pos;											//位置の設定
	pIcon->m_size = D3DXVECTOR2(40.0f * MaxHeart, 30.0f);		//サイズの設定

	for (int nCnt = 0; nCnt < MaxHeart; nCnt++)
	{//画像のインスタンスの生成
		pIcon->m_pHeart[nCnt] = CObject_2D::Create();

		//位置の計算
		D3DXVECTOR3 heartPos = pos;			
		heartPos.x += 42.5f * nCnt;

		pIcon->m_pHeart[nCnt]->SetPos(heartPos);								//位置の設定
		pIcon->m_pHeart[nCnt]->SetSize(D3DXVECTOR2(22.5f, 22.5f));				//サイズの設定
		pIcon->m_pHeart[nCnt]->SetStartingRot(D3DX_PI * 0.5f);					//向きの初期値の設定
		pIcon->m_pHeart[nCnt]->SetTexture(CObject::TextureLifeIcon);			//テクスチャの設定
		pIcon->m_pHeart[nCnt]->SetTextureParameter(1, 4, 1, INT_MAX);			//テクスチャパラメータの設定
		pIcon->m_pHeart[nCnt]->SetPriority(2);									//プライオリティの設定
		pIcon->m_pHeart[nCnt]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));		//色の設定
	}

	return pIcon;					//生成したインスタンスを返す
}