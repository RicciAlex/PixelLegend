//=============================================================================
//
// Scylla.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef SCYLLA_H
#define SCYLLA_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "enemy.h"

//=============================================================================
//前方宣言
//=============================================================================
class CSkullTentacle;
class CSpine;
class CScyllaBody;
class CEnemyLife;

class CScylla : public CObject
{
public:

	//状態
	enum State
	{
		state_Spawn = 0,			//スポーン状態
		state_Damage,				//ダメージを受ける状態
		state_Death,				//死亡状態
		state_normal,				//普通の状態
		state_Max
	};

	CScylla();											//コンストラクタ
	~CScylla() override;								//デストラクタ

	HRESULT Init(void) override;						//初期化処理
	void Uninit(void) override;							//終了処理
	void Update(void) override;							//更新処理
	void Draw(void) override;							//描画処理

	void SetPos(const D3DXVECTOR3 pos) override;		//位置の設定処理
	const D3DXVECTOR2 GetSize(void) override;			//サイズの取得処理
	const D3DXVECTOR3 GetPos(void) override;			//位置の取得処理
	const bool GetEnd(void);							//終わったかどうかの取得処理

	static CScylla* Create(void);						//生成処理

private:

	void UpdateState(void);								//状態によっての更新処理

	static const int MaxTentacle = 6;					

	D3DXVECTOR3 m_Anchor[MaxTentacle];					
	D3DXVECTOR3 m_TentacleAnchor[MaxTentacle];
	bool m_aliveHead[MaxTentacle];						//頭が生きているかどうか
	int m_nAliveHeadNum;								//残っている頭の数
	int m_nCntAttack;									//攻撃用のカウンター
	State m_state;										//状態
	bool m_bEnd;										//終わったかどうか

	CSkullTentacle* m_pTentacle[MaxTentacle];
	CSpine* m_pSpine[MaxTentacle];						//骨へのポインタ
	CScyllaBody* m_pBody;								//体へのポインタ
	CEnemyLife* m_pLife;								//体力UIへのポインタ
};



#endif