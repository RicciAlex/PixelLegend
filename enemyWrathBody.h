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


	CWrathBody();
	~CWrathBody() override;

	HRESULT Init(void) override;				//初期化処理
	void Uninit(void) override;					//終了処理
	void Update(void) override;					//更新処理
	void Draw(void) override;					//描画処理

	void SetParent(CWrath* pParent);

	const bool GetDeath(void);

	//==========================================================================================================
	//											静的関数
	static CWrathBody* Create(D3DXVECTOR3 pos);		//生成処理

private:

	void UpdateState(void);

	bool m_bDead;
	bool m_bBound;

	int m_nCntShoot;
	int m_nCntState;
	D3DXVECTOR3 m_targetPos;
	state m_state;

	D3DXVECTOR3 m_posArm;

	CObject_2D* m_pArm;

	D3DXVECTOR3 m_posBodyHitbox;
	D3DXVECTOR3 m_posHeadHitbox;

	CSquareHitbox* m_pHitbox;
	CCircleHitbox* m_pHeadHitbox;

	CWrath* m_pParent;
};

