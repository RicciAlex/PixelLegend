//=============================================================================
//
// skeleton.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef SKELETON_H
#define SKELETON_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "enemy.h"

//=============================================================================
//インクルードファイル
//=============================================================================
class CSquareHitbox;

class CSkeleton : public CEnemy
{
public:

	enum type
	{
		type_legs = 0,
		type_body,
		type_full
	};

	enum state
	{
		state_spawn = 0,
		state_wait,
		state_pursuit
	};

	CSkeleton();
	~CSkeleton() override;

	HRESULT Init(void) override;				//初期化処理
	void Uninit(void) override;					//終了処理
	void Update(void) override;					//更新処理
	void Draw(void) override;					//描画処理

	static CSkeleton* Create(const D3DXVECTOR3 pos);					//生成処理

private:

	void UpdateMove(void);

	type m_type;
	state m_state;
	float m_fTaget;

	CSquareHitbox* m_pHitbox;
};



#endif