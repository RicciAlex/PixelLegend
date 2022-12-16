//=============================================================================
//
// SkullTentacle.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef SKULL_TENTACLE_H
#define SKULL_TENTACLE_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "object.h"

//=============================================================================
//前方宣言
//=============================================================================
class CSpine;
class CSkull;

class CSkullTentacle : public CObject
{
public:

	//状態
	enum State
	{
		state_Spawn = 0,		//スポーン状態
		state_Idle,				//待機状態
		state_Bite,				//嚙む攻撃
		state_Pursuit,			//追いかける状態
		state_Aim,				//狙う
		state_ShootBeam,		//ビーム攻撃
		state_Flamethrower,		//炎攻撃
		state_Pull,				//引く攻撃
		state_Return,			//戻る状態
		state_Max,
	};

	CSkullTentacle();									//コンストラクタ
	~CSkullTentacle() override;							//デストラクタ

	HRESULT Init(void) override;						//初期化処理
	void Uninit(void) override;							//終了処理
	void Update(void) override;							//更新処理
	void Draw(void) override;							//描画処理

	void SetPos(const D3DXVECTOR3 pos) override;		//位置の設定処理
	const D3DXVECTOR2 GetSize(void) override;			//サイズの取得処理
	const D3DXVECTOR3 GetPos(void) override;			//位置の取得処理

	const State GetState(void);							//状態の取得処理

	void SetState(const State state);					//状態の設定処理

	void SetLife(const int nLife);						//ライフの設定処理

	const int GetLife(void);							//ライフの取得処理

	void Kill(void);									//死亡アニメーションの設定処理

	static CSkullTentacle* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 headPos);		//生成処理		pos = CSpineのanchor



private:

	void UpdateState(void);								//更新処理
	void ChargeAnimation(const D3DXCOLOR color);		//アニメーション処理

	int m_nLife;										//体力
	D3DXVECTOR3 m_SkullPos;								//頭の位置
	D3DXVECTOR3 m_SkullDir;								//頭の向き
	D3DXVECTOR3 m_target;								//目的の位置
	CSkull* m_pSkull;									//頭へのポインタ
	CSpine* m_pSpine;									//骨へのポインタ
	State m_state;										//状態
	int m_nCntAtk;										//攻撃用のカウンター
	int m_nCntDeath;									//死亡アニメーション用のカウンター
	int m_nCntMove;										//移動用のカウンター
	float m_fAngleMove;									//移動用のカウンター
	bool m_bDead;										//死んでいるかどうか
};

#endif