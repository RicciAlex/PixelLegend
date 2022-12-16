//=============================================================================
//
// enemyWrathBody.h
// Author : Ricci Alex
//
//=============================================================================

//インクルードファイル
#include "enemy.h"

//前方宣言
class CSquareHitbox;
class CCircleHitbox;
class CObject_2D;
class CWrath;

class CWrathBody : public CEnemy
{
public:

	enum state
	{
		state_spawn = 0,
		state_normal,
		state_flamethrower,
		state_rage,
		state_swirl,
		state_death,
		state_max
	};


	CWrathBody();								//コンストラクタ
	~CWrathBody() override;						//デストラクタ

	HRESULT Init(void) override;				//初期化処理
	void Uninit(void) override;					//終了処理
	void Update(void) override;					//更新処理
	void Draw(void) override;					//描画処理

	void SetParent(CWrath* pParent);			//親へのポインタの設定処理
												
	const bool GetDeath(void);					//死亡状態の取得処理

	//==========================================================================================================
	//											静的関数
	static CWrathBody* Create(D3DXVECTOR3 pos);		//生成処理

private:

	void UpdateState(void);				//状態によっての更新処理
										
	bool m_bDead;						//死亡したかどうか
	bool m_bBound;						//親に結んでいるかどうか
										
	int m_nCntShoot;					//攻撃カウンター
	int m_nCntState;					//状態カウンター
	D3DXVECTOR3 m_targetPos;			//目的の位置
	state m_state;						//現在の状態
										
	D3DXVECTOR3 m_posArm;				//腕の位置
										
	CObject_2D* m_pArm;					//腕へのポインタ
										
	D3DXVECTOR3 m_posBodyHitbox;		//体のヒットボックス
	D3DXVECTOR3 m_posHeadHitbox;		//頭のヒットボックス
										
	CSquareHitbox* m_pHitbox;			//体のヒットボックス
	CCircleHitbox* m_pHeadHitbox;		//頭のヒットボックス
										
	CWrath* m_pParent;					//親へのポインタ
};

