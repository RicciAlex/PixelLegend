//=============================================================================
//
// squareHitbox.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef SQUARE_HITBOX_H
#define SQUARE_HITBOX_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "hitbox.h"

class CSquareHitbox : public CHitbox
{
public:
	CSquareHitbox();							//コンストラクタ
	~CSquareHitbox() override;					//デストラクタ
												
	HRESULT Init(void) override;				//初期化処理
	void Uninit(void) override;					//終了処理
	bool Hit(void) override;					//当たり判定の処理
												
	const D3DXVECTOR2 GetSize(void);			//サイズの取得処理
	const float GetRadius(void);				//半径の取得処理
												
	void SetSize(const D3DXVECTOR2 size);		//サイズの設定処理

	bool SquareSquareHit(const D3DXVECTOR3 pos, const D3DXVECTOR2 size);	//円形同士の当たり判定
	bool SquareCircleHit(const D3DXVECTOR3 center, const float radius);		//四角形と円形の当たり判定

	static CSquareHitbox* Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const Type type);		//生成処理

private:

	D3DXVECTOR2 m_size;				//サイズ

};



#endif