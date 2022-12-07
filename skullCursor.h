//=============================================================================
//
// skullCursor.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef SKULL_CURSOR_H
#define SKULL_CURSOR_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
//前方宣言
//=============================================================================
class CSpine;
class CSkull;

class CSkullCursor
{
public:
	CSkullCursor();						//コンストラクタ
	~CSkullCursor();					//デストラクタ
										
	HRESULT Init(void);					//初期化処理
	void Uninit(void);					//終了処理
	void Update(void);					//更新処理

	static CSkullCursor* Create(const D3DXVECTOR3 pos);		//生成処理

private:

	D3DXVECTOR3 m_skullPos;				//頭の位置
	
	CSpine* m_pSpine;					//脊椎へのポインタ
	CSkull* m_pSkull;					//頭へのポインタ
};




#endif