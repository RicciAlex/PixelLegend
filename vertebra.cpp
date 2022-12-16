//=============================================================================
//
// vertebra.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "vertebra.h"
#include "circleHitbox.h"

//コンストラクタ
CVertebra::CVertebra()
{
	//メンバー変数をクリアする
	m_pHitbox = nullptr;
}

//デストラクタ
CVertebra::~CVertebra()
{

}

//初期化処理
HRESULT CVertebra::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CEnemy::Init()))
	{
		return -1;
	}

	return S_OK;
}

//終了処理
void CVertebra::Uninit(void)
{
	//ヒットボックスの破棄処理
	if (m_pHitbox != nullptr)
	{//nullチェック
		m_pHitbox->Release();		//メモリを解放する
		m_pHitbox = nullptr;		//ポインタをnullにする
	}

	//基本クラスの終了処理
	CEnemy::Uninit();
}

//更新処理
void CVertebra::Update(void)
{
	//基本クラスの更新処理
	CObject_2D::Update();

	//ヒットボックスの更新処理
	if (m_pHitbox)
	{//nullチェック
		//位置を取得して、ヒットボックスの位置を設定する
		D3DXVECTOR3 pos = GetPos();
		m_pHitbox->SetPos(pos);
	}
}


//==================================================================================================
//										静的関数
//==================================================================================================

//生成処理
CVertebra* CVertebra::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	CVertebra* pVertebra = new CVertebra;			//新しい敵を生成する

	if (pVertebra != nullptr)
	{
		//初期化処理
		if (FAILED(pVertebra->Init()))
		{
			return nullptr;						//生成できなかったら、nullを返す
		}

		pVertebra->SetObjType(CObject::OBJTYPE_ENEMY);					//オブジェクトの種類の設定

		pVertebra->SetPos(pos);											//位置の設定
		pVertebra->SetStartingRot(D3DX_PI * 0.5f);						//回転角度の初期値の設定
		pVertebra->SetTextureParameter(1, 1, 1, INT_MAX);				//テクスチャパラメータの設定
		pVertebra->SetSize(size);										//サイズの設定

		pVertebra->SetMove(D3DXVECTOR3(-1.5f, 0.0f, 0.0f));				//速度の設定
		pVertebra->SetAcceleration(D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//加速の設定
		pVertebra->SetSubtype(CObject::ENEMYTYPE_VERTEBRA);				//敵の種類の設定

		pVertebra->SetTexture(TextureVertebra);							//テクスチャの設定

		//ヒットボックスの生成処理
		pVertebra->m_pHitbox = CCircleHitbox::Create(pos, size.x * 0.3f, CHitbox::Type_Enemy);
	}

	return pVertebra;				//生成したインスタンスを返す
} 