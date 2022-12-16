//=============================================================================
//
// rotatinfSimpleEffect.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef ROT_SIMPLE_EFFECT_H
#define ROT_SIMPLE_EFFECT_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "effect.h"

class CRotSimpleEff : public CEffect
{
public:
	CRotSimpleEff();					//コンストラクタ
	~CRotSimpleEff() override;			//デストラクタ

	HRESULT Init(void) override;		//初期化処理
	void Uninit(void) override;			//終了処理
	void Update(void) override;			//更新処理
	void Draw(void) override;			//終了処理

	//生成処理
	static CRotSimpleEff* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 target, const D3DXVECTOR3 move, const D3DXCOLOR col,
		const int Life, const D3DXCOLOR deltaCol, const D3DXVECTOR2 size, const float fFrameRot);										//生成処理

private:

	D3DXVECTOR3 m_target;				//目的の位置
	D3DXCOLOR m_deltaCol;				//色の減数

};

#endif