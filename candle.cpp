//=============================================================================
//
// candle.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "candle.h"
#include "squareHitbox.h"
#include "bg.h"
#include "skullShield.h"
#include "Thanatos.h"

//コンストラクタ
CCandle::CCandle()
{
	//メンバー変数をクリアする
	m_state = state_spawn;
	m_nCntState = 0;
	m_nIdx = 0;

	m_pParent = nullptr;
	m_pHitbox = nullptr;
	m_pBg = nullptr;
	m_pShield[0] = nullptr;
	m_pShield[1] = nullptr;
}

//デストラクタ
CCandle::~CCandle()
{

}

//初期化処理
HRESULT CCandle::Init(void)
{
	//メンバー変数を初期化する
	if (FAILED(CEnemy::Init()))
	{
		return -1;
	}

	m_nCntState = 0;
	m_nIdx = -1;
	m_state = state_spawn;
	SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	m_pParent = nullptr;
	m_pHitbox = nullptr;
	m_pBg = nullptr;
	m_pShield[0] = nullptr;
	m_pShield[1] = nullptr;

	return S_OK;
}

//終了処理
void CCandle::Uninit(void)
{
	//ヒットボックスの破棄処理
	if (m_pHitbox != nullptr)
	{//nullチェック
		m_pHitbox->Release();		//メモリを解放する
		m_pHitbox = nullptr;		//nullにする
	}
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pShield[nCnt] != nullptr)
		{//nullチェック
			m_pShield[nCnt]->Release();			//メモリを解放する
			m_pShield[nCnt] = nullptr;			//nullにする
		}
	}

	//背景へのポインタと親へのポインタをnullにする
	if (m_pBg != nullptr)
	{
		m_pBg = nullptr;
	}
	if (m_pParent != nullptr)
	{
		m_pParent = nullptr;
	}

	//基本クラスの終了処理
	CEnemy::Uninit();
}

//更新処理
void CCandle::Update(void)
{
	switch (m_state)
	{//状態によって更新する
	case CCandle::state_spawn:

	{//スポーン状態

		D3DXCOLOR col = GetColor();		//色の取得

		col.a += 0.01f;					//α値の更新

		SetColor(col);					//色の設定

		if (col.a >= 0.9f)
		{//α値が0.9fを超えたら
			m_state = state_off;		//状態を更新する
		}
	}

		break;

	case CCandle::state_off:

	{//火が消えた状態

		if (m_pHitbox)
		{//nullチェック
			m_pHitbox->SetPos(GetPos());			//位置の設定

			if (m_pHitbox->GetHitState())
			{//当たったら
				m_pHitbox->SetHitState(false);		//当っていない状態に戻す
				int nLife = GetLife();				//体力の取得
				nLife += 100;						//体力の更新
				SetLife(nLife);						//体力の設定

				if (nLife >= 1500)
				{//体力が1500を超えたら

					m_state = state_on;					//状態を更新する
					SetAnimPattern(0);					//アニメションパターンの設定
					SetTextureParameter(4, 5, 1, 10);	//アニメーションパラメータの設定

					if (m_pParent != nullptr)
					{//nullチェック
						m_pParent->AddLitCandle();		//親のつけたロウソクの数を更新する
					}

					if (m_pBg != nullptr)
					{//nullチェック
						m_pBg->SetVtxColor(m_nIdx, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));			//背景の色を更新する
					}
				}
			}
		}
	}

		break;

	case CCandle::state_on:
		break;

	default:
		break;
	}

	//基本クラスの更新処理
	CObject_2D::Update();
}

//描画処理
void CCandle::Draw(void)
{
	//基本クラスの描画処理
	CObject_2D::Draw();
}

//親へのポインタの設定
void CCandle::SetParent(CThanatos* pParent)
{
	m_pParent = pParent;
}

//背景へのポインタの設定処理
void CCandle::SetBgPointer(CBg* pointer)
{
	m_pBg = pointer;
}

//状態の取得処理
CCandle::state CCandle::GetCandleState(void)
{
	return m_state;
}

//火を消す処理
void CCandle::Unlit(void)
{
	m_state = state_off;												//状態の更新
	SetTextureParameter(1, 5, 1, INT_MAX);								//テクスチャパラメータの設定
	SetAnimPattern(4);													//アニメションパターンの設定
	m_pBg->SetVtxColor(m_nIdx, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));		//背景の頂点の色の設定
	SetLife(0);															//体力の設定

	m_pShield[0]->AddRevolutionSpeed(D3DX_PI * 0.01f);					
	m_pShield[1]->AddRevolutionSpeed(D3DX_PI * 0.01f);					
}

//破棄処理
void CCandle::Despawn(void)
{
	D3DXCOLOR col = m_pShield[0]->GetColor();		//色の取得

	if (col.a > 0.0f)
	{//色のα値が0.0以上だったら

		col.a -= 0.005f;				//α値を更新する
		m_pShield[0]->SetColor(col);	//色の設定
	}

	col = m_pShield[1]->GetColor();					//色の取得

	if (col.a > 0.0f)
	{//色のα値が0.0以上だったら
		col.a -= 0.005f;				//α値を更新する
		m_pShield[1]->SetColor(col);	//色の設定
	}
}




//生成処理
CCandle* CCandle::Create(const D3DXVECTOR3 pos)
{
	CCandle* pCandle = new CCandle;				//インスタンスを生成する

	if (FAILED(pCandle->Init()))
	{//初期化処理
		return nullptr;
	}

	pCandle->SetPos(pos);										//位置の設定
	pCandle->SetSize(D3DXVECTOR2(22.5f, 28.5f));				//サイズの設定
	pCandle->SetTexture(CObject::TextureCandle);				//テクスチャの設定
	pCandle->SetTextureParameter(1, 5, 1, INT_MAX);				//テクスチャパラメータの設定
	pCandle->SetAnimPattern(4);									//アニメションパターンの設定
	pCandle->SetStartingRot(D3DX_PI * 0.5f);					//向きの初期値の設定

	//ヒットボックスの生成処理
	pCandle->m_pHitbox = CSquareHitbox::Create(pos, D3DXVECTOR2(12.0f, 13.0f), CHitbox::Type_Enemy);

	//ロウソクのインデックスの設定
	if (pos.x < (float)SCREEN_WIDTH * 0.5f && pos.y < (float)SCREEN_HEIGHT * 0.5f)
	{
		pCandle->m_nIdx = 0;
	}
	else if (pos.x > (float)SCREEN_WIDTH * 0.5f && pos.y < (float)SCREEN_HEIGHT * 0.5f)
	{
		pCandle->m_nIdx = 1;
	}
	else if (pos.x < (float)SCREEN_WIDTH * 0.5f && pos.y > (float)SCREEN_HEIGHT * 0.5f)
	{
		pCandle->m_nIdx = 2;
	}
	else if (pos.x > (float)SCREEN_WIDTH * 0.5f && pos.y > (float)SCREEN_HEIGHT * 0.5f)
	{
		pCandle->m_nIdx = 3;
	}

	pCandle->m_pShield[0] = CSkullShield::Create(D3DXVECTOR3(pos.x, pos.y + 5.0f, 0.0f), 0.0f);
	pCandle->m_pShield[1] = CSkullShield::Create(D3DXVECTOR3(pos.x, pos.y + 10.0f, 0.0f), D3DX_PI);

	return pCandle;					//生成したインスタンスを返す
}

CCandle* CCandle::Create(const D3DXVECTOR3 pos, CBg* pointer)
{
	CCandle* pCandle = new CCandle;				//インデックスを生成する

	if (FAILED(pCandle->Init()))
	{//初期化処理
		return nullptr;
	}

	pCandle->SetPos(pos);									//位置の設定
	pCandle->SetSize(D3DXVECTOR2(30.0f, 38.0f));			//サイズの設定
	pCandle->SetTexture(CObject::TextureCandle);			//テクスチャの設定
	pCandle->SetTextureParameter(1, 5, 1, INT_MAX);			//テクスチャパラメータの設定
	pCandle->SetAnimPattern(4);								//アニメションパターンの設定
	pCandle->SetStartingRot(D3DX_PI * 0.5f);				//向きの初期値の設定

															//ヒットボックスの生成処理
	pCandle->m_pHitbox = CSquareHitbox::Create(pos, D3DXVECTOR2(12.0f, 13.0f), CHitbox::Type_Enemy);
	pCandle->m_pBg = pointer;				//ロウソクの背景へのポインタの設定

	//ロウソクのインデックスの設定
	if (pos.x < (float)SCREEN_WIDTH * 0.5f && pos.y < (float)SCREEN_HEIGHT * 0.5f)
	{
		pCandle->m_nIdx = 0;
	}
	else if (pos.x >(float)SCREEN_WIDTH * 0.5f && pos.y < (float)SCREEN_HEIGHT * 0.5f)
	{
		pCandle->m_nIdx = 1;
	}
	else if (pos.x < (float)SCREEN_WIDTH * 0.5f && pos.y >(float)SCREEN_HEIGHT * 0.5f)
	{
		pCandle->m_nIdx = 2;
	}
	else if (pos.x >(float)SCREEN_WIDTH * 0.5f && pos.y > (float)SCREEN_HEIGHT * 0.5f)
	{
		pCandle->m_nIdx = 3;
	}

	pCandle->m_pShield[0] = CSkullShield::Create(D3DXVECTOR3(pos.x, pos.y + 5.0f, 0.0f), 0.0f);
	pCandle->m_pShield[1] = CSkullShield::Create(D3DXVECTOR3(pos.x, pos.y + 10.0f, 0.0f), D3DX_PI);

	return pCandle;						//生成したインスタンスを返す
}