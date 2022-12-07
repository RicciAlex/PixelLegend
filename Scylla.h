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
		state_Spawn = 0,
		state_Damage,
		state_Death,
		state_normal,
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
	const bool GetEnd(void);

	static CScylla* Create(void);						//生成処理

private:

	static const int MaxTentacle = 6;					

	D3DXVECTOR3 m_Anchor[MaxTentacle];					
	D3DXVECTOR3 m_TentacleAnchor[MaxTentacle];
	bool m_aliveHead[MaxTentacle];						//頭が生きているかどうか
	int m_nAliveHeadNum;								//残っている頭の数
	int m_nCntAttack;									//攻撃用のカウンター
	State m_state;										//状態
	bool m_bEnd;

	CSkullTentacle* m_pTentacle[MaxTentacle];
	CSpine* m_pSpine[MaxTentacle];
	CScyllaBody* m_pBody;
	CEnemyLife* m_pLife;
};



#endif