//=============================================================================
//
// hitbox.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef HITBOX_H
#define HITBOX_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"

class CHitbox
{
public:

	static const int MaxHitbox = 1024;
	
	enum Type
	{
		Type_Enemy = 0,
		Type_Player,
		Type_EnemyBullet,
		Type_PlayerBullet,
		Type_Max
	};

	enum Shape
	{
		shape_Circle = 0,
		shape_Square,
		shape_Capsule,
		shape_Max
	};

	CHitbox();
	virtual ~CHitbox();

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual bool Hit(void) = 0;

	void Release(void);
	
	const D3DXVECTOR3 GetPos(void);
	const Shape GetShape(void);
	const Type GetType(void);
	virtual const D3DXVECTOR2 GetSize(void) = 0;
	virtual const float GetRadius(void) = 0;
	const bool GetHitState(void);
	

	
	void SetPos(const D3DXVECTOR3 pos);
	void SetType(const Type type);
	void SetShape(const Shape shape);
	void SetHitState(const bool bHit);

	static void ReleaseAll(void);
	static CHitbox** GetAllHitbox(void);

private:

	Type m_Type;
	Shape m_Shape;
	D3DXVECTOR3 m_pos;
	int m_nIdx;
	bool m_bHit;

	static CHitbox* m_pHitbox[MaxHitbox];

};



#endif // !HITBOX_H
