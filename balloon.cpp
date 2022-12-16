//=============================================================================
//
// balloon.cpp
// Author : Ricci Alex
//
//=============================================================================

//インクルードファイル
#include "balloon.h"
#include "circleHitbox.h"
#include "application.h"
#include "sound.h"

//コンストラクタ
CBalloonBullet::CBalloonBullet()
{
	//メンバー変数をクリアする
	m_pHitbox = nullptr;
}

//デストラクタ
CBalloonBullet::~CBalloonBullet()
{

}

//初期化処理
HRESULT CBalloonBullet::Init(void)
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
void CBalloonBullet::Uninit(void)
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
void CBalloonBullet::Update(void)
{
	//ヒットボックスの更新処理
	if (m_pHitbox)
	{
		m_pHitbox->SetPos(GetPos());			//ヒットボックスの位置の更新

		if (m_pHitbox->Hit())
		{//何かと当たったら、

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_EXPLOSION);		//爆発のサウンドエフェクト
			Release();				//破棄する
			return;
		}
	}

	//基本クラスの更新処理
	CBullet::Update();
}


//=============================================================================
//
//								静的関数
//
//=============================================================================



//生成処理
CBalloonBullet* CBalloonBullet::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, D3DXCOLOR col)
{
	CBalloonBullet* pBullet = new CBalloonBullet;		//インスタンスを生成する

	if (FAILED(pBullet->Init()))
	{//初期化処理
		return nullptr;
	}

	pBullet->SetPos(pos);								//位置の設定
	pBullet->SetMove(move);								//速度の設定
	pBullet->SetSize(D3DXVECTOR2(25.0f, 45.0f));		//サイズの設定
	pBullet->SetLife(random(120, 300));					//寿命の設定
	pBullet->SetColor(col);								//色の設定
	pBullet->SetTexture(CObject::TextureBalloon);		//テクスチャの設定
	pBullet->SetTextureParameter(1, 1, 1, INT_MAX);		//テクスチャパラメータの設定
	pBullet->SetStartingRot(D3DX_PI * 0.5f);			//向きの初期値の設定

	pBullet->m_pHitbox = CCircleHitbox::Create(pos, 25.0f, CHitbox::Type_EnemyBullet);		//ヒットボックスの生成

	return pBullet;			//生成したインスタンスを返す
}