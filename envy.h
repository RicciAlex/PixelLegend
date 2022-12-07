//=============================================================================
//
// envy.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef ENVY_H
#define ENVY_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "enemy.h"

//=============================================================================
//前方宣言
//=============================================================================
class CSquareHitbox;
class CEnemyLife;


class CEnvy : public CEnemy
{
public:

	enum state
	{
		state_spawn = 0,
		state_normal,
		state_hide,
		state_strike,
		state_death,
		state_max
	};

	CEnvy();
	~CEnvy() override;								//デストラクタ

	HRESULT Init(void) override;				//初期化処理
	void Uninit(void) override;					//終了処理
	void Update(void) override;					//更新処理
	void Draw(void) override;					//描画処理

	const bool GetEnd(void);

	static CEnvy* Create(void);								//生成処理

private:

	void UpdateState(void);
	void UpdatePointers(void);

	static const int nGearNum = 6;
	static const int nPipeNum = 2;

	void CreateGears(void);

	D3DXVECTOR3 m_gearRelativePos[nGearNum];
	D3DXVECTOR3 m_hatRelativePos;
	D3DXVECTOR3 m_pipeRelativePos[nPipeNum];
	D3DXVECTOR3 m_cannonRelativePos;

	int m_nCntState;
	state m_state;
	bool m_bEnd;

	CObject_2D* m_pGear[nGearNum];
	CObject_2D* m_pHat;
	CObject_2D* m_pPipe[nPipeNum];
	CObject_2D* m_pCannon;
	CSquareHitbox* m_pHitbox;
	CSquareHitbox* m_pHatHitbox;
	CEnemyLife* m_pLife;
};


#endif