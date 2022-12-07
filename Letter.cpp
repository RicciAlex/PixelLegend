//=============================================================================
//
// Letter.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "Letter.h"

//コンストラクタ
CLetter::CLetter()
{

}

//デストラクタ
CLetter::~CLetter()
{

}

//初期化処理
HRESULT CLetter::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CObject_2D::Init()))
	{
		return -1;
	}

	//種類の設定処理
	SetObjType(CObject::OBJTYPE_LETTER);

	return S_OK;
}

//終了処理
void CLetter::Uninit(void)
{
	//基本クラスの終了処理
	CObject_2D::Uninit();
}

//更新処理
void CLetter::Update(void)
{
	//基本クラスの更新処理
	CObject_2D::Update();
}

//終了処理
void CLetter::Draw(void)
{
	//基本クラスの描画処理
	CObject_2D::Draw();
}

bool CLetter::ConvertInNumber(const int nNum)
{
	if (nNum >= 0 && nNum <= 9)
	{
		SetTexture(CObject::TextureNumbers);
		SetTextureParameter(1, 5, 3, INT_MAX);
		SetAnimPattern(nNum);
	}
	else
	{
		return false;
	}

	return true;
}

bool CLetter::ConvertInSymbol(const char symbol)
{
	if (symbol != '?' && symbol != '!' && symbol != '%')
	{
		return false;
	}
	else
	{
		SetTexture(CObject::TextureNumbers);
		SetTextureParameter(1, 5, 3, INT_MAX);

		switch (symbol)
		{
		case '?':

			SetAnimPattern(10);

			break;

		case '!':

			SetAnimPattern(11);

			break;

		case '%':

			SetAnimPattern(12);

			break;

		default:

			return false;

			break;
		}
	}
	
	return true;
}


//==================================================================================================================
//
//		静的関数
//
//==================================================================================================================

//生成処理
CLetter* CLetter::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const char letter)
{
	CLetter* pLetter = new CLetter;						//生成

	//初期化処理
	if (FAILED(pLetter->Init()))
	{
		return nullptr;
	}
	
	pLetter->SetPos(pos);									//位置の設定
	pLetter->SetSize(size);									//サイズの設定
	pLetter->SetStartingRot(D3DX_PI * 0.5f);				//回転角度の設定
	pLetter->SetTexture(CObject::TextureLetters);			//テクスチャの設定
	pLetter->SetTextureParameter(26, 13, 2, INT_MAX);		//テクスチャパラメータの設定

	char aLetter = 'a';

	//アニメーションパターンの設定
	int Cell = 27;

	for (int nCnt = 0; nCnt < 26; nCnt++)
	{
		if (letter == aLetter)
		{
			Cell = nCnt;
			break;
		}

		aLetter += 1;
	}

	if (Cell < 0 || Cell > 25)
	{
		if (!pLetter->ConvertInSymbol(letter))
		{
			pLetter->Release();
			return nullptr;
		}
	}
	else
	{
		pLetter->SetAnimPattern(Cell);
	}	

	return pLetter;				
} 

//生成処理
CLetter* CLetter::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const int nNum)
{
	CLetter* pLetter = new CLetter;						//生成

														//初期化処理
	if (FAILED(pLetter->Init()))
	{
		return nullptr;
	}

	pLetter->SetPos(pos);									//位置の設定
	pLetter->SetSize(size);									//サイズの設定
	pLetter->SetStartingRot(D3DX_PI * 0.5f);				//回転角度の設定
	pLetter->SetTexture(CObject::TextureLetters);			//テクスチャの設定
	pLetter->SetTextureParameter(26, 13, 2, INT_MAX);		//テクスチャパラメータの設定

	if (!pLetter->ConvertInNumber(nNum))
	{
		pLetter->Uninit();
		pLetter->Release();
		return nullptr;
	}
	

	return pLetter;
}