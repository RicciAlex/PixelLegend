//=============================================================================
//
// sloth.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef SLOTH_H
#define SLOTH_H

//インクルードファイル
#include "enemy.h"

//前方宣言
class CSquareHitbox;
class CEnemyLife;

class CSloth : public CEnemy
{
public:

	//状態
	enum State
	{
		state_Spawn = 0,
		state_Normal,
		state_Return,
		state_Charge,
		state_Snore,
		state_Weep,
		state_Cry,
		state_Summon,
		state_Death,
		state_Max
	};

	CSloth();									//コンストラクタ
	~CSloth() override;							//デストラクタ

	HRESULT Init(void) override;				//初期化処理
	void Uninit(void) override;					//終了処理
	void Update(void) override;					//更新処理
	void Draw(void) override;					//描画処理

	const bool GetEnd(void);

	static CSloth* Create(void);				//生成処理

private:

	void SlothBehavior(void);					//更新処理

	bool m_bEnd;
	float m_fYCoord;							//Y座標
	int m_nCntState;							//状態カウンター
	int m_nCntDmg;								//ダメージ用のカウンター
	int m_nCntSpawn;
	int m_nChange;
	int m_nCntSound;
	int m_nSoundDelay;
	int m_nCntAnim;
	D3DXVECTOR3 m_HitboxRelativePos;
	State m_state;								//状態

	CSquareHitbox* m_pHitbox;
	CEnemyLife* m_pLife;
};



#endif