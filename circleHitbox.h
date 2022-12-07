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
	CCircleHitbox();
	~CCircleHitbox() override;

	HRESULT Init(void) override;
	void Uninit(void) override;
	bool Hit(void) override;

	const D3DXVECTOR2 GetSize(void);
	const float GetRadius(void);

	void SetRadius(const float radius);

	bool CircleSquareHit(const D3DXVECTOR3 pos, const D3DXVECTOR2 size);
	bool CircleCircleHit(const D3DXVECTOR3 center, const float radius);

	static CCircleHitbox* Create(const D3DXVECTOR3 pos, const float fRadius, const Type type);

private:

	float m_fRadius;

};



#endif