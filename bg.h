//=============================================================================
//
// bg.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef BG_H
#define BG_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "object2D.h"

class CBg : public CObject_2D
{
public:
	CBg();															//コンストラクタ
	~CBg() override;												//デストラクタ

	HRESULT Init(void) override;									//初期化処理
	virtual void Uninit(void) override;								//終了処理
	virtual void Update(void) override;								//更新処理
	//virtual void Draw(void) override;								//終了処理

	void SetColor(const D3DXCOLOR col);								//カーラーの設定処理

	static CBg* Create(const D3DXCOLOR col, const D3DXVECTOR2 textMove);										//生成処理

private:
	
	D3DXVECTOR2 m_textMove;											//テクスチャのUV座標の移動量
};

#endif