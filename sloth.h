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
		state_Spawn = 0,			//スポーン状態
		state_Normal,				//普通の状態
		state_Return,				//戻る状態
		state_Charge,				//体当たり
		state_Snore,				//いびき攻撃
		state_Weep,					//泣く攻撃(1)
		state_Cry,					//泣く攻撃(2)
		state_Summon,				//召喚
		state_Death,				//死亡状態
		state_Max
	};

	CSloth();									//コンストラクタ
	~CSloth() override;							//デストラクタ

	HRESULT Init(void) override;				//初期化処理
	void Uninit(void) override;					//終了処理
	void Update(void) override;					//更新処理
	void Draw(void) override;					//描画処理

	const bool GetEnd(void);					//終わったかどうかの取得処理

	static CSloth* Create(void);				//生成処理

private:

	void SlothBehavior(void);					//更新処理

	bool m_bEnd;
	float m_fYCoord;							//Y座標
	int m_nCntState;							//状態カウンター
	int m_nCntDmg;								//ダメージ用のカウンター
	int m_nCntSpawn;							//スポーンカウンター
	int m_nChange;								//
	int m_nCntSound;							//サウンドのカウンター
	int m_nSoundDelay;							//サウンドのディレイ
	int m_nCntAnim;								//アニメーションカウンター
	D3DXVECTOR3 m_HitboxRelativePos;			//ヒットボックスの相対位置
	State m_state;								//状態

	CSquareHitbox* m_pHitbox;					//ヒットボックス
	CEnemyLife* m_pLife;						//体力UIへのポインタ
};



#endif