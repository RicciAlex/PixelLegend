//=============================================================================
//
// maw.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef MAW_H
#define MAW_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "enemy.h"

//=============================================================================
//前方宣言
//=============================================================================
class CSquareHitbox;

class CMaw : public CEnemy
{
public:

	enum Position
	{
		left = 0,
		up,
		right,
		down
	};

	enum state
	{
		state_normal = 0,
		state_open,
		state_SingleShoot,
		state_TripleShoot,
		state_RandomShoot,
		state_Spawn,
		state_close
	};

	CMaw();
	~CMaw() override;								//デストラクタ

	HRESULT Init(void) override;					//初期化処理
	void Uninit(void) override;						//終了処理
	void Update(void) override;						//更新処理
	void Draw(void) override;						//描画処理

	void Open(void);

	static CMaw* Create(Position Pos);					//生成処理

private:

	void UpdateState(void);

	state m_state;								//状態
	Position m_Pos;

	CSquareHitbox* m_pHitbox;
};

#endif