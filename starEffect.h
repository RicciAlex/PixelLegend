//=============================================================================
//
// starEffect.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef STAR_EFFECT_H
#define STAR_EFFECT_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "effect.h"

//前方宣言
class CCircleHitbox;

class CStarEffect : public CEffect
{
public:	
	CStarEffect();						//コンストラクタ
	~CStarEffect() override;			//デストラクタ

	HRESULT Init(void) override;		//初期化処理
	void Uninit(void) override;			//終了処理
	void Update(void) override;			//更新処理
	void Draw(void) override;			//終了処理

	void SetCenterPos(const D3DXVECTOR3 center);			//中心点の設定処理
	void SetAngleMove(const float fAngle);					

	bool GetActiveState(void);

	static CStarEffect* Create(const D3DXVECTOR3 center, const float fAngleStart, 
		const float fAngleMove, const D3DXCOLOR col, const D3DXVECTOR2 size, const int Life);			//生成処理

private:

	D3DXVECTOR3 m_center;										//中心点
	float m_fAngleStart;										//アニメーションや移動用のカウンター
	float m_fAngleSpeed;
	bool m_bActive;

	CCircleHitbox* m_pHitbox;
};


#endif