//=============================================================================
//
// ringEffect.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef RING_EFFECT_H
#define RING_EFFECT_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "effect.h"

class CRingEffect : public CEffect
{
public:
	CRingEffect();								//コンストラクタ
	~CRingEffect() override;					//デストラクタ

	virtual HRESULT Init(void) override;		//初期化処理
	virtual void Uninit(void) override;			//終了処理
	virtual void Update(void) override;			//更新処理
	virtual void Draw(void) override;			//終了処理

	static CRingEffect* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, 
		const D3DXVECTOR2 size, const D3DXVECTOR2 deltaSize, const D3DXCOLOR col, const D3DXCOLOR deltaCol);			//生成処理

private:
	D3DXCOLOR m_deltaCol;						//色の減数
	D3DXVECTOR2 m_deltaSize;					//サイズの減数
};

#endif
