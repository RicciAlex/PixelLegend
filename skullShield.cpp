//=============================================================================
//
// skullShield.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "skullShield.h"
#include "circleHitbox.h"

//コンストラクタ
CSkullShield::CSkullShield()
{
	//メンバー変数をクリアする
	m_pHitbox = nullptr;
}

//デストラクタ
CSkullShield::~CSkullShield()
{

}

//初期化処理
HRESULT CSkullShield::Init(void)
{
	//メンバー変数を初期化する
	if (FAILED(CEnemy::Init()))
	{
		return -1;
	}

	m_pHitbox = nullptr;

	return S_OK;
}

//終了処理
void CSkullShield::Uninit(void)
{
	//ヒットボックスの破棄処理
	if (m_pHitbox != nullptr)
	{//nullチェック
		m_pHitbox->Release();			//メモリを解放する
		m_pHitbox = nullptr;			//nullにする
	}

	//基本クラスの終了処理
	CEnemy::Uninit();
}

//更新処理
void CSkullShield::Update(void)
{
	//ヒットボックスの更新
	if (m_pHitbox != nullptr)
	{//nullチェック
		m_pHitbox->SetPos(GetPos());			//位置の設定

		if (m_pHitbox->GetHitState())
		{//当たったら
			m_pHitbox->SetHitState(false);		//元に戻す
			int nLife = GetLife();				//体力の取得

			nLife -= 100;						//体力の更新

			if (nLife <= 0)
			{//体力が0以下になったら
				Release();						//メモリを解放する
				return;
			}
			else
			{
				SetLife(nLife);					//体力の設定
			}
		}
	}

	//基本クラスの更新処理
	CObject_2D::Update();
}

//描画処理
void CSkullShield::Draw(void)
{
	//基本クラスの描画処理
	CObject_2D::Draw();
}




//生成処理
CSkullShield* CSkullShield::Create(const D3DXVECTOR3 pos, const float fStartAngle)
{
	CSkullShield* pEnemy = new CSkullShield;				//インスタンスを生成する

	if (FAILED(pEnemy->Init()))
	{//初期化処理
		return nullptr;
	}

	pEnemy->SetPos(pos);									//位置の設定
	pEnemy->SetStartingRot(D3DX_PI * 0.5f);					//向きの初期値の設定
	pEnemy->SetPresentRevolutionAngle(fStartAngle);			//現在の公転角度の設定
	pEnemy->SetTexture(CObject::TextureSkullShield);		//テクスチャの設定
	pEnemy->SetTextureParameter(1, 1, 1, INT_MAX);			//テクスチャパラメータの設定
	pEnemy->SetRevolution(pos, D3DX_PI * 0.01f, 60.0f);		//公転の設定
	pEnemy->SetSize(D3DXVECTOR2(22.5f, 22.5f));				//サイズの設定
	pEnemy->SetLife(30000);									//体力の設定

	//ヒットボックスの生成
	pEnemy->m_pHitbox = CCircleHitbox::Create(pEnemy->GetPos(), 18.0f, CHitbox::Type_Enemy);

	return pEnemy;					//生成したインスタンスを返す
}