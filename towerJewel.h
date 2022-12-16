//=============================================================================
//
// towerJewel.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef TOWER_JEWEL_H
#define TOWER_JEWEL_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "enemy.h"

//=============================================================================
//前方宣言
//=============================================================================
class CCircleHitbox;

class CTowerJewel : public CEnemy
{
public:
	enum state
	{
		state_spawn = 0,			//スポーン状態
		state_shoot,				//ショットの状態
		state_despawn,				//ディスポーンの状態
		state_wait,					//待機状態
		state_max
	};

	CTowerJewel();								//コンストラクタ
	~CTowerJewel() override;					//デストラクタ

	HRESULT Init(void) override;				//初期化処理
	void Uninit(void) override;					//終了処理
	void Update(void) override;					//更新処理

	void SetState(CTowerJewel::state state);	//状態の設定処理

	static CTowerJewel* Create(const D3DXVECTOR3 pos);		//生成処理

private:

	state m_state;								//状態

	CCircleHitbox* m_pHitBox;					//ヒットボックス

};

#endif