//=============================================================================
//
// effect.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef EFFECT_H
#define EFFECT_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "object2D.h"

class CEffect : public CObject_2D
{
public:
	CEffect();									//コンストラクタ
	virtual ~CEffect() override;				//デストラクタ

	virtual HRESULT Init(void) override;		//初期化処理
	virtual void Uninit(void) override;			//終了処理
	virtual void Update(void) override;			//更新処理

	const int GetLife(void);					//ライフの取得処理

	void SetMove(const D3DXVECTOR3 move);							//速度の設定処理
	void SetLife(const int Life);									//ライフの設定処理

	static CEffect* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, 
		const D3DXCOLOR col, const D3DXVECTOR2 size, const int Life);		//生成処理

private:

	D3DXVECTOR3 m_move;							//速度
	int m_nLife;								//寿命
};

#endif