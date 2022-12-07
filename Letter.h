//=============================================================================
//
// Letter.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef LETTER_H
#define LETTER_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "object2D.h"

class CLetter : public CObject_2D
{
public:
	CLetter();																//コンストラクタ
	~CLetter() override;													//デストラクタ

	HRESULT Init(void) override;											//初期化処理
	void Uninit(void) override;												//終了処理
	void Update(void) override;												//更新処理
	void Draw(void) override;												//終了処理

	bool ConvertInNumber(const int nNum);									//数値に変換する処理
	bool ConvertInSymbol(const char symbol);								//文字に変換する処理

	static CLetter* Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const char letter);			//生成処理
	static CLetter* CLetter::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const int nNum);		

private:

};

#endif
