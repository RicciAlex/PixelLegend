//=============================================================================
//
// handGun.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef HAND_GUN_H
#define HAND_GUN_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "enemy.h"

//=============================================================================
//前方宣言
//=============================================================================
class CCircleHitbox;
class CWrath;

class CHandGun : public CEnemy
{
public:

	//状態の列挙型
	enum state
	{
		state_spawn = 0,			//スポーン
		state_shoot,				//ショット
		state_return,				//戻る
		state_despawn,				//ディスポーン
		state_death,				//死亡
		state_max
	};

	CHandGun();																		//コンストラクタ
	~CHandGun() override;															//デストラクタ

	HRESULT Init(void) override;													//初期化処理
	void Uninit(void) override;														//終了処理
	void Update(void) override;														//更新処理

	void SetParent(CWrath* pParent);												//親の設定処理

	static CHandGun* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);						//生成処理

private:

	void UpdateState(void);			//状態によっての更新処理
									
	state m_state;					//状態
									
	CCircleHitbox* m_pHitbox;		//ヒットボックス
	CWrath* m_pParent;				//親へのポインタ
};




#endif