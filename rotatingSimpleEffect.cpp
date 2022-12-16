//=============================================================================
//
// rotatinfSimpleEffect.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "rotatingSimpleEffect.h"

//コンストラクタ
CRotSimpleEff::CRotSimpleEff()
{
	//メンバー変数をクリアする
	m_target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_deltaCol = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//デストラクタ
CRotSimpleEff::~CRotSimpleEff()
{

}

//初期化処理
HRESULT CRotSimpleEff::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CEffect::Init()))
	{
		return -1;
	}

	//メンバー変数の初期化
	m_target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_deltaCol = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

	return S_OK;
}

//終了処理
void CRotSimpleEff::Uninit(void)
{
	//基本クラスの終了処理
	CEffect::Uninit();
}

//更新処理
void CRotSimpleEff::Update(void)
{
	//基本クラスの更新処理
	CEffect::Update();

	D3DXVECTOR3 pos = GetPos();					//位置の取得
	D3DXCOLOR col = GetColor();					//カーラーの取得
												
	pos += GetMove();							//位置の更新
	col += m_deltaCol;							//カーラーの更新

	if (sqrtf((((pos.x - m_target.x) * (pos.x - m_target.x))) + ((pos.y - m_target.y) * (pos.y - m_target.y))) <= 5.0f)
	{//目的の位置に着いたら、消す
		Release();
		return;
	}

	SetPos(pos);								//位置の設定
	SetColor(col);								//カーラーの設定
}

//終了処理
void CRotSimpleEff::Draw(void)
{
	//基本クラスの描画処理
	CEffect::Draw();
}

//==================================================================================================================
//
//		静的関数
//
//==================================================================================================================


//生成処理
CRotSimpleEff* CRotSimpleEff::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 target, const D3DXVECTOR3 move, const D3DXCOLOR col, const int Life, const D3DXCOLOR deltaCol, const D3DXVECTOR2 size, const float fFrameRot)
{
	CRotSimpleEff* pEffect = new CRotSimpleEff;			//新しいエフェクトを生成する

	//初期化処理
	if (FAILED(pEffect->Init()))
	{
		return nullptr;
	}

	pEffect->SetPos(pos);								//位置の設定
	pEffect->m_target = target;							//目的の位置の設定
	pEffect->SetMove(move);								//速度の設定
	pEffect->SetColor(col);								//カーラーの設定
	pEffect->SetLife(Life);								//ライフの設定
	pEffect->m_deltaCol = deltaCol;						//色の減数の設定
	pEffect->SetRotation(fFrameRot);					//回転速度の設定
	pEffect->SetSize(size);								//サイズの設定
	pEffect->SetTexture(CObject::TextureRoundEffect);	//テクスチャの設定
	pEffect->SetTextureParameter(1, 1, 1, INT_MAX);		//テクスチャパラメータの設定

	return pEffect;										//エフェクトを返す
} 