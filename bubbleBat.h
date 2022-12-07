//=============================================================================
//
// bubbleBat.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef BUBBLE_BAT_H
#define BUBBLE_BAT_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "enemy.h"

//=============================================================================
//前方宣言
//=============================================================================
class CCircleHitbox;
class CLetter;

class CBubbleBat : public CEnemy
{
public:

	enum state
	{
		state_spawn = 0,
		state_looking,
		state_charge,
		state_max
	};

	CBubbleBat();
	~CBubbleBat() override;							//デストラクタ

	HRESULT Init(void) override;				//初期化処理
	void Uninit(void) override;					//終了処理
	void Update(void) override;					//更新処理
	void Draw(void) override;					//描画処理

	static CBubbleBat* Create(const D3DXVECTOR3 pos);			//生成処理

private:

	D3DXVECTOR3 m_letterRelativePos;
	state m_state;

	CCircleHitbox* m_pHitbox;
	CLetter* m_pLetter;

};


#endif