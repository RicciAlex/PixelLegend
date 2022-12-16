//=============================================================================
//
// heartEffect.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "starEffect.h"
#include "circleHitbox.h"

//コンストラクタ
CStarEffect::CStarEffect()
{
	//メンバー変数をクリアする
	m_fAngleStart = 0.0f;
	m_fAngleSpeed = 0.0f;
	m_bActive = false;
	m_pHitbox = nullptr;
}

//デストラクタ
CStarEffect::~CStarEffect()
{

}

//初期化処理
HRESULT CStarEffect::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CEffect::Init()))
	{
		return -1;
	}

	//メンバー変数の初期化
	m_fAngleStart = 0.0f;
	m_fAngleSpeed = 0.0f;
	m_bActive = true;
	m_pHitbox = nullptr;

	return S_OK;
}

//終了処理
void CStarEffect::Uninit(void)
{
	//ヒットボックスの破棄処理
	if (m_pHitbox != nullptr)
	{//nullチェック
		m_pHitbox->Release();			//メモリを解放する
		m_pHitbox = nullptr;			//ポインタをnullにする
	}

	//基本クラスの終了処理
	CEffect::Uninit();
}

//更新処理
void CStarEffect::Update(void)
{
	//位置の計算と設定
	float fX, fY, x, y;

	m_fAngleStart += m_fAngleSpeed;				//移動の角度の更新

	//パラメトリック方程式を使って、現在の位置を計算する
	float a = 5.0f;
	float b = 3.0f;
	x = sinf(m_fAngleStart + m_fAngleSpeed);
	y = cosf(m_fAngleStart + m_fAngleSpeed);
	fX = m_center.x + 20.0f * ((a - b) * y + b * (cosf(((a - b) / b) * m_fAngleStart + m_fAngleSpeed)));
	fY = m_center.y + 20.0f * ((a - b) * x - b * (sinf(((a - b) / b) * m_fAngleStart + m_fAngleSpeed)));

	SetPos(D3DXVECTOR3(fX, fY, 0.0f));				//位置の設定

	//基本クラスの更新
	CObject_2D::Update();

	int life = GetLife();				//ライフの取得

	life--;								//ライフの更新

	if (life <= 0)
	{//ライフが0以下になったら、消す
		m_bActive = false;
	}
	else
	{
		SetLife(life);					//ライフの設定
	}
	
	//ヒットボックスの更新処理
	if (m_pHitbox)
	{//nullチェック

		m_pHitbox->SetPos(GetPos());			//ヒットボックスの位置の更新

		if (m_pHitbox->Hit())
		{//プレイヤーと当たった場合、消す
			m_bActive = false;
		}
	}
}

//終了処理
void CStarEffect::Draw(void)
{
	//基本クラスの描画処理
	CEffect::Draw();
}

//中心点の設定処理
void CStarEffect::SetCenterPos(const D3DXVECTOR3 center)
{
	m_center = center;
}

//角度の初期値の設定処理	
void CStarEffect::SetAngleMove(const float fAngle)
{
	m_fAngleStart = fAngle;
}

//まだあるかどうかの取得処理
bool CStarEffect::GetActiveState(void)
{
	return m_bActive;
}


//==================================================================================================================
//
//		静的関数
//
//==================================================================================================================

//生成処理
CStarEffect* CStarEffect::Create(const D3DXVECTOR3 center, const float fAngleStart, const float fAngleMove, const D3DXCOLOR col, const D3DXVECTOR2 size, const int Life)
{
	CStarEffect* pEffect = new CStarEffect;				//新しいエフェクトを生成する

	//初期化処理
	if (FAILED(pEffect->Init()))
	{
		return nullptr;
	}

	pEffect->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));							//速度の設定
	pEffect->SetColor(col);														//カーラーの設定
	pEffect->SetLife(Life);														//ライフの設定
	pEffect->SetSize(size);														//サイズの設定
	pEffect->m_center = center;													//中心点の設定
	pEffect->m_fAngleStart = fAngleStart;										//角度の初期値の設定
	pEffect->m_fAngleSpeed = fAngleMove * 0.02f;								//回転速度の設定

	//位置の計算と設定
	float fX, fY, x, y, a, b;

	//パラメトリック方程式を使って、位置を計算する
	a = 5.0f;
	b = 3.0f;
	x = sinf(pEffect->m_fAngleStart + pEffect->m_fAngleSpeed);
	y = cosf(pEffect->m_fAngleStart + pEffect->m_fAngleSpeed);
	fX = center.x + 20.0f * ((a - b) * y + b * (cosf(((a - b) / b) * pEffect->m_fAngleStart + pEffect->m_fAngleSpeed)));
	fY = center.y + 20.0f * ((a - b) * x - b * (sinf(((a - b) / b) * pEffect->m_fAngleStart + pEffect->m_fAngleSpeed)));

	pEffect->SetPos(D3DXVECTOR3(fX, fY, 0.0f));									//位置の設定

	pEffect->SetTexture(CObject::TextureNormalEffect);							//テクスチャの設定
	pEffect->SetTextureParameter(1, 1, 1, INT_MAX);								//テクスチャパラメータの設定

	//ヒットボックスの生成
	pEffect->m_pHitbox = CCircleHitbox::Create(pEffect->GetPos(), size.x * 0.5f, CHitbox::Type_EnemyBullet);

	return pEffect;							//エフェクトを返す
}	 