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
	CSquareHitbox();
	~CSquareHitbox() override;

	HRESULT Init(void) override;
	void Uninit(void) override;
	bool Hit(void) override;

	const D3DXVECTOR2 GetSize(void);
	const float GetRadius(void);

	void SetSize(const D3DXVECTOR2 size);

	bool SquareSquareHit(const D3DXVECTOR3 pos, const D3DXVECTOR2 size);
	bool SquareCircleHit(const D3DXVECTOR3 center, const float radius);

	static CSquareHitbox* Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const Type type);

private:

	D3DXVECTOR2 m_size;

};



#endif