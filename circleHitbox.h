//=============================================================================
//
// circleHitbox.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef CIRCLE_HITBOX_H
#define CIRCLE_HITBOX_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "hitbox.h"

class CCircleHitbox : public CHitbox
{
public:
	CCircleHitbox();						//コンストラクタ
	~CCircleHitbox() override;				//デストラクタ
											
	HRESULT Init(void) override;			//初期化処理
	void Uninit(void) override;				//終了処理
	bool Hit(void) override;				//当たり判定の処理
											
	const D3DXVECTOR2 GetSize(void);		//サイズの取得処理
	const float GetRadius(void);			//半径の取得処理
											
	void SetRadius(const float radius);		//半径の設定処理

	bool CircleSquareHit(const D3DXVECTOR3 pos, const D3DXVECTOR2 size);		//円形と四角形の当たり判定の処理
	bool CircleCircleHit(const D3DXVECTOR3 center, const float radius);			//円形同士の当たり判定の処理

	static CCircleHitbox* Create(const D3DXVECTOR3 pos, const float fRadius, const Type type);			//生成処理
		
private:

	float m_fRadius;			//半径

};



#endif