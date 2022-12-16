//=============================================================================
//
// missile.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef MISSILE_H
#define MISSILE_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "bullet.h"

//=============================================================================
//前方宣言
//=============================================================================
class CSquareHitbox;

class CMissile : public CBullet
{
public:

	//状態の列挙型
	enum state
	{
		state_ascend = 0,		//上におろす
		state_descend,			//落ちる
		state_strike,			//ストライク
		state_max
	};

	CMissile();							//コンストラクタ
	~CMissile() override;				//デストラクタ

	HRESULT Init(void) override;		//初期化処理
	void Uninit(void) override;			//終了処理
	void Update(void) override;			//更新処理


	static CMissile* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move);									//生成処理
	static CMissile* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const D3DXVECTOR3 acc);			//生成処理

private:

	state m_state;						//状態

	CSquareHitbox* m_pHitbox;			//ヒットボックスへのポインタ
};


#endif