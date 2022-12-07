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

	for (int nCnt = 0; nCnt < MaxNameLenght; nCnt++)
	{
		if (m_pName[nCnt] != nullptr)
		{
			m_pName[nCnt]->Release();
			m_pName[nCnt] = nullptr;
		}
	}

	for (int nCnt = 0; nCnt < MaxDigit; nCnt++)
	{
		if (m_pLife[nCnt] != nullptr)
		{
			m_pLife[nCnt]->Release();
			m_pLife[nCnt] = nullptr;
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

void CEnemyLife::SetLife(const int nLife)
{
	m_nMaxLife = nLife;
	m_nLife = nLife;
}

void CEnemyLife::SubtractLife(const int nLife)
{
	m_nLife -= nLife;

	float life = ((float)m_nLife / (float)m_nMaxLife) * 100;

	if (m_pLife[0] != nullptr)
	{
		m_pLife[0]->SetAnimPattern((int)life / 100);
	}
	if (m_pLife[1] != nullptr)
	{
		m_pLife[1]->SetAnimPattern(((int)life % 100) / 10);
	}
	if (m_pLife[2] != nullptr)
	{
		m_pLife[2]->SetAnimPattern(((int)life % 10));
	}
}




CEnemyLife* CEnemyLife::Create(const D3DXVECTOR3 pos, const D3DXCOLOR NameCol, const int MaxLife, const char* pName)
{
	CEnemyLife* pIcon = new CEnemyLife;

	if (FAILED(pIcon->Init()))
	{
		return nullptr;
	}

	char aName[MaxNameLenght] = {};

	strcpy(aName, pName);

	int nNameLenght = strlen(aName);

	char aLife[4] = {};

	pIcon->m_pos = pos;
	pIcon->m_nMaxLife = MaxLife;
	pIcon->m_nLife = MaxLife;

	for (int nCnt = 0; nCnt < MaxNameLenght; nCnt++)
	{
		if (pIcon->m_pName[nCnt] == nullptr)
		{
			pIcon->m_pName[nCnt] = CLetter::Create(D3DXVECTOR3(pos.x + 35.0f * (nCnt), pos.y, 0.0f), D3DXVECTOR2(25.0f, 25.0f), aName[nCnt]);

			if (pIcon->m_pName[nCnt] != nullptr)
			{
				pIcon->m_pName[nCnt]->SetPriority(5);
				pIcon->m_pName[nCnt]->SetColor(D3DXCOLOR(NameCol.r, NameCol.g, NameCol.b, 0.75f));
			}
		}
	}

	pIcon->m_pLife[0] = CLetter::Create(D3DXVECTOR3(pos.x + 25.0f * (nNameLenght + 4), pos.y, 0.0f), D3DXVECTOR2(25.0f, 25.0f), 1);

	if (pIcon->m_pLife[0] != nullptr)
	{
		pIcon->m_pLife[0]->SetPriority(5);
		pIcon->m_pLife[0]->SetColor(D3DXCOLOR(NameCol.r, NameCol.g, NameCol.b, 0.75f));
	}

	pIcon->m_pLife[1] = CLetter::Create(D3DXVECTOR3(pos.x + 25.0f * (nNameLenght + 5), pos.y, 0.0f), D3DXVECTOR2(25.0f, 25.0f), 0);

	if (pIcon->m_pLife[1] != nullptr)
	{
		pIcon->m_pLife[1]->SetPriority(5);
		pIcon->m_pLife[1]->SetColor(D3DXCOLOR(NameCol.r, NameCol.g, NameCol.b, 0.75f));
	}

	pIcon->m_pLife[2] = CLetter::Create(D3DXVECTOR3(pos.x + 25.0f * (nNameLenght + 6), pos.y, 0.0f), D3DXVECTOR2(25.0f, 25.0f), 0);

	if (pIcon->m_pLife[2] != nullptr)
	{
		pIcon->m_pLife[2]->SetPriority(5);
		pIcon->m_pLife[2]->SetColor(D3DXCOLOR(NameCol.r, NameCol.g, NameCol.b, 0.75f));
	}

	pIcon->m_pLife[3] = CLetter::Create(D3DXVECTOR3(pos.x + 25.0f * (nNameLenght + 7), pos.y, 0.0f), D3DXVECTOR2(25.0f, 25.0f), '%');

	if (pIcon->m_pLife[3] != nullptr)
	{
		pIcon->m_pLife[3]->SetPriority(5);
		pIcon->m_pLife[3]->SetColor(D3DXCOLOR(NameCol.r, NameCol.g, NameCol.b, 0.75f));
	}

	//pIcon->m_size = D3DXVECTOR2(40.0f * MaxHeart, 30.0f);



	return pIcon;
}