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
	void SetAngleMove(const float fAngle);					//角度の初期値の設定処理	

	bool GetActiveState(void);								//まだあるかどうかの取得処理

	static CStarEffect* Create(const D3DXVECTOR3 center, const float fAngleStart, 
		const float fAngleMove, const D3DXCOLOR col, const D3DXVECTOR2 size, const int Life);			//生成処理

private:

	D3DXVECTOR3 m_center;										//中心点
	float m_fAngleStart;										//移動用のカウンター
	float m_fAngleSpeed;										//移動の角度
	bool m_bActive;												//まだあるかどうか

	CCircleHitbox* m_pHitbox;									//ヒットボックス
};


#endif