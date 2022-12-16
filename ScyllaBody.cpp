//=============================================================================
//
// ScyllaBody.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "ScyllaBody.h"
#include "squareHitbox.h"

//コンストラクタ
CScyllaBody::CScyllaBody()
{
	//メンバー変数をクリアする
	m_pHitbox = nullptr;
}

//デストラクタ
CScyllaBody::~CScyllaBody()
{

}

//初期化処理
HRESULT CScyllaBody::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CEnemy::Init()))
	{
		return -1;
	}

	//メンバー変数の初期化
	SetTexture(CObject::TextureScyllaBody);
	SetTextureParameter(2, 2, 1, INT_MAX);

	return S_OK;
}

//終了処理
void CScyllaBody::Uninit(void)
{
	//ヒットボックスの破棄処理
	if (m_pHitbox != nullptr)
	{//nullチェック
		m_pHitbox->Release();			//メモリを解放する
		m_pHitbox = nullptr;			//ポインタをnullにする
	}

	//基本クラスの終了処理
	CEnemy::Uninit();
}

//更新処理
void CScyllaBody::Update(void)
{
	//基本クラスの更新処理
	CObject_2D::Update();

	if (m_pHitbox)
	{
		m_pHitbox->SetPos(GetPos());			//ヒットボックスの位置を更新する
	}
}

//描画処理
void CScyllaBody::Draw(void)
{
	//基本クラスの描画処理
	CEnemy::Draw();
}


//========================================================================================================
//										静的関数 
//========================================================================================================


//生成処理
CScyllaBody* CScyllaBody::Create(void)
{
	CScyllaBody* pEnemy = new CScyllaBody;			//メモリを確保する

	//初期化処理
	if (FAILED(pEnemy->Init()))
	{
		return nullptr;
	}

	D3DXVECTOR3 pos = D3DXVECTOR3((float)SCREEN_WIDTH * 0.9f, (float)SCREEN_HEIGHT * 0.450f, 0.0f);

	pEnemy->SetPos(pos);												//位置の設定
	pEnemy->SetSize(D3DXVECTOR2(140.0f, 250.0f));						//サイズの設定
	pEnemy->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));						//速度の設定
	pEnemy->SetStartingRot(D3DX_PI * 0.5f);								//回転角度の設定
	pEnemy->SetSubtype(ENEMYTYPE_SCYLLA_BODY);							//敵の種類の設定

	//ヒットボックスの生成
	pEnemy->m_pHitbox = CSquareHitbox::Create(pos, D3DXVECTOR2(70.0f, 250.0f), CHitbox::Type_Enemy);

	return pEnemy;			//生成したインスタンスを返す
}