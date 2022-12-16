//=============================================================================
//
// enemyLife.h
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "enemyLife.h"
#include "letter.h"
#include "player.h"

//コンストラクタ
CEnemyLife::CEnemyLife()
{
	//メンバー変数をクリアする
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_nMaxLife =0;
	m_nLife = 0;

	for (int nCnt = 0; nCnt < MaxNameLenght; nCnt++)
	{
		m_pName[nCnt] = nullptr;
	}

	for (int nCnt = 0; nCnt < MaxDigit; nCnt++)
	{
		m_pLife[nCnt] = nullptr;
	}
}

//デストラクタ
CEnemyLife::~CEnemyLife()
{

}

//初期化処理
HRESULT CEnemyLife::Init(void)
{
	//メンバー変数を初期化する
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_nMaxLife = 0;
	m_nLife = 0;

	for (int nCnt = 0; nCnt < MaxNameLenght; nCnt++)
	{
		m_pName[nCnt] = nullptr;
	}

	for (int nCnt = 0; nCnt < MaxDigit; nCnt++)
	{
		m_pLife[nCnt] = nullptr;
	}

	return S_OK;
}

//終了処理
void CEnemyLife::Uninit(void)
{
	//敵の名前のUIの破棄処理
	for (int nCnt = 0; nCnt < MaxNameLenght; nCnt++)
	{//nullチェック
		if (m_pName[nCnt] != nullptr)
		{
			m_pName[nCnt]->Release();			//メモリを解放する
			m_pName[nCnt] = nullptr;			//nullにする
		}
	}

	//敵の体力のUIの破棄処理
	for (int nCnt = 0; nCnt < MaxDigit; nCnt++)
	{
		if (m_pLife[nCnt] != nullptr)
		{//nullチェック
			m_pLife[nCnt]->Release();			//メモリを解放する
			m_pLife[nCnt] = nullptr;			//nullにする
		}
	}
}

//更新処理
void CEnemyLife::Update(void)
{
	
}

//描画処理
void CEnemyLife::Draw(void)
{

}

//位置の設定処理
void CEnemyLife::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//サイズの取得処理
const D3DXVECTOR2 CEnemyLife::GetSize(void)
{
	return m_size;
}

//位置の取得処理
const D3DXVECTOR3  CEnemyLife::GetPos(void)
{
	return m_pos;
}

//体力の設定処理
void CEnemyLife::SetLife(const int nLife)
{
	m_nMaxLife = nLife;
	m_nLife = nLife;
}

//体力の減算処理
void CEnemyLife::SubtractLife(const int nLife)
{
	m_nLife -= nLife;		//体力を更新する

	float life = ((float)m_nLife / (float)m_nMaxLife) * 100;			//体力の％を計算する

	if (m_pLife[0] != nullptr)
	{//nullチェック
		m_pLife[0]->SetAnimPattern((int)life / 100);			//テクスチャパターンの設定
	}
	if (m_pLife[1] != nullptr)
	{//nullチェック
		m_pLife[1]->SetAnimPattern(((int)life % 100) / 10);		//テクスチャパターンの設定
	}
	if (m_pLife[2] != nullptr)
	{//nullチェック
		m_pLife[2]->SetAnimPattern(((int)life % 10));			//テクスチャパターンの設定
	}
}



//生成処理
CEnemyLife* CEnemyLife::Create(const D3DXVECTOR3 pos, const D3DXCOLOR NameCol, const int MaxLife, const char* pName)
{
	CEnemyLife* pIcon = new CEnemyLife;				//インスタンスを生成する

	if (FAILED(pIcon->Init()))
	{//初期化処理
		return nullptr;
	}

	//名前のUIの生成処理
	char aName[MaxNameLenght] = {};			

	strcpy(aName, pName);				//配列をコーピする

	int nNameLenght = strlen(aName);	//配列の長さ

	char aLife[4] = {};

	pIcon->m_pos = pos;					//位置の設定
	pIcon->m_nMaxLife = MaxLife;		//体力の最大値の設定
	pIcon->m_nLife = MaxLife;			//現在の体力の設定

	for (int nCnt = 0; nCnt < MaxNameLenght; nCnt++)
	{
		if (pIcon->m_pName[nCnt] == nullptr)
		{//nullチェック

			//文字を生成する
			pIcon->m_pName[nCnt] = CLetter::Create(D3DXVECTOR3(pos.x + 35.0f * (nCnt), pos.y, 0.0f), D3DXVECTOR2(25.0f, 25.0f), aName[nCnt]);

			if (pIcon->m_pName[nCnt] != nullptr)
			{//生成できたら
				pIcon->m_pName[nCnt]->SetPriority(5);													//プライオリティの設定
				pIcon->m_pName[nCnt]->SetColor(D3DXCOLOR(NameCol.r, NameCol.g, NameCol.b, 0.75f));		//色の設定
			}
		}
	}

	//体力の最初の文字の生成
	pIcon->m_pLife[0] = CLetter::Create(D3DXVECTOR3(pos.x + 25.0f * (nNameLenght + 4), pos.y, 0.0f), D3DXVECTOR2(25.0f, 25.0f), 1);

	if (pIcon->m_pLife[0] != nullptr)
	{//生成できたら
		pIcon->m_pLife[0]->SetPriority(5);														//プライオリティの設定
		pIcon->m_pLife[0]->SetColor(D3DXCOLOR(NameCol.r, NameCol.g, NameCol.b, 0.75f));			//色の設定
	}

	//体力の2番目の文字の生成
	pIcon->m_pLife[1] = CLetter::Create(D3DXVECTOR3(pos.x + 25.0f * (nNameLenght + 5), pos.y, 0.0f), D3DXVECTOR2(25.0f, 25.0f), 0);

	if (pIcon->m_pLife[1] != nullptr)
	{//生成できたら
		pIcon->m_pLife[1]->SetPriority(5);														//プライオリティの設定
		pIcon->m_pLife[1]->SetColor(D3DXCOLOR(NameCol.r, NameCol.g, NameCol.b, 0.75f));			//色の設定
	}

	//体力の3番目の文字の生成
	pIcon->m_pLife[2] = CLetter::Create(D3DXVECTOR3(pos.x + 25.0f * (nNameLenght + 6), pos.y, 0.0f), D3DXVECTOR2(25.0f, 25.0f), 0);

	if (pIcon->m_pLife[2] != nullptr)
	{//生成できたら
		pIcon->m_pLife[2]->SetPriority(5);														//プライオリティの設定
		pIcon->m_pLife[2]->SetColor(D3DXCOLOR(NameCol.r, NameCol.g, NameCol.b, 0.75f));			//色の設定
	}

	//体力の4番目の文字の生成(%)
	pIcon->m_pLife[3] = CLetter::Create(D3DXVECTOR3(pos.x + 25.0f * (nNameLenght + 7), pos.y, 0.0f), D3DXVECTOR2(25.0f, 25.0f), '%');

	if (pIcon->m_pLife[3] != nullptr)
	{//生成できたら
		pIcon->m_pLife[3]->SetPriority(5);														//プライオリティの設定
		pIcon->m_pLife[3]->SetColor(D3DXCOLOR(NameCol.r, NameCol.g, NameCol.b, 0.75f));			//色の設定
	}

	return pIcon;					//生成したインスタンスを返す
}