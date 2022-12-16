//=============================================================================
//
// laugh.cpp
// Author : Ricci Alex
//
//=============================================================================

//インクルードファイル
#include "laugh.h"
#include "squareHitbox.h"
#include "Letter.h"

//コンストラクタ
CLaughBullet::CLaughBullet()
{
	//メンバー変数をクリアする
	m_pHitbox = nullptr;
}

//デストラクタ
CLaughBullet::~CLaughBullet()
{

}

//初期化処理
HRESULT CLaughBullet::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CBullet::Init()))
	{
		return -1;
	}

	//メンバー変数を初期化する
	m_pHitbox = nullptr;

	return S_OK;
}

//終了処理
void CLaughBullet::Uninit(void)
{
	//ヒットボックスの破棄
	if (m_pHitbox != nullptr)
	{//nullチェック
		m_pHitbox->Release();		//メモリを解放する
		m_pHitbox = nullptr;		//ポインタをnullにする
	}

	//基本クラスの終了処理
	CBullet::Uninit();
}

//更新処理
void CLaughBullet::Update(void)
{
	D3DXVECTOR3 pos = GetPos() + GetMove();		//位置の更新
	D3DXVECTOR2 size = GetSize();				//サイズの取得
	
	//基本クラスの更新
	CBullet::Update();

	if (pos.x + size.x > 0.0f && pos.x + size.x < (float)SCREEN_WIDTH &&
		pos.y + size.y > 0.0f && pos.y - size.y < (float)SCREEN_HEIGHT)
	{//画面内だったら

		//ヒットボックスの更新処理
		if (m_pHitbox != nullptr)
		{//nullチェック

			m_pHitbox->SetPos(GetPos());		//ヒットボックスの位置の更新

			if (m_pHitbox->Hit())
			{//何かと当たったら、消す
				Release();
				return;
			}
		}
	}
}



//=============================================================================
//
//								静的関数
//
//=============================================================================



//生成処理
CLaughBullet* CLaughBullet::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move)
{
	CLaughBullet* pBullet = new CLaughBullet;		//インスタンスを生成する

	if (FAILED(pBullet->Init()))
	{//初期化処理
		return nullptr;
	}

	pBullet->SetPos(pos);								//位置の設定
	pBullet->SetSize(D3DXVECTOR2(45.0f, 40.0f));		//サイズの設定
	pBullet->SetMove(move);								//速度の設定
	pBullet->SetLife(300);								//体力の設定
	pBullet->SetStartingRot(D3DX_PI * 0.5f);			//向きの初期値の設定
														
	pBullet->SetTexture(CObject::TextureLaugh);			//テクスチャの設定
	pBullet->SetTextureParameter(1, 1, 1, INT_MAX);		//テクスチャパラメータの設定

	//ヒットボックスの生成
	pBullet->m_pHitbox = CSquareHitbox::Create(pos, D3DXVECTOR2(40.0f, 35.0f), CHitbox::Type_EnemyBullet);

	return pBullet;				//生成したインスタンスを返す
}