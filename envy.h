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

	//状態
	enum state
	{	
		state_spawn = 0,			//スポーン状態
		state_normal,				//普通の状態
		state_hide,					//隠す状態
		state_strike,				//攻撃状態
		state_death,				//死亡状態
		state_max
	};

	CEnvy();									//コンストラクタ
	~CEnvy() override;							//デストラクタ

	HRESULT Init(void) override;				//初期化処理
	void Uninit(void) override;					//終了処理
	void Update(void) override;					//更新処理
	void Draw(void) override;					//描画処理

	const bool GetEnd(void);					//終わったかどうかの取得処理

	static CEnvy* Create(void);					//生成処理

private:
						
	void UpdateState(void);				//状態によっての更新処理
	void UpdatePointers(void);			//ポインタの更新処理
	void CreateGears(void);				//歯車の生成処理



	static const int nGearNum = 6;		//歯車の数
	static const int nPipeNum = 2;		//管の数
	static const D3DXVECTOR2 m_EnvySize;		//サイズ
	static const D3DXVECTOR2 m_HitboxEnvySize;	//ヒットボックスサイズ
	static const D3DXVECTOR2 m_HitboxHatSize;			//帽子のヒットボックスサイズ

	
	D3DXVECTOR3 m_gearRelativePos[nGearNum];		//歯車の相対位置
	D3DXVECTOR3 m_hatRelativePos;					//帽子の相対位置
	D3DXVECTOR3 m_pipeRelativePos[nPipeNum];		//管の相対位置
	D3DXVECTOR3 m_cannonRelativePos;				//大砲の相対位置

	int m_nCntState;					//状態カウンター
	state m_state;						//状態
	bool m_bEnd;						//終わったかどうか
										
	CObject_2D* m_pGear[nGearNum];		//歯車へのポインタ
	CObject_2D* m_pHat;					//帽子へのポインタ
	CObject_2D* m_pPipe[nPipeNum];		//管へのポインタ
	CObject_2D* m_pCannon;				//大砲へのポインタ
	CSquareHitbox* m_pHitbox;			//ヒットボックスへのポインタ
	CSquareHitbox* m_pHatHitbox;		//帽子のヒットボックスへのポインタ
	CEnemyLife* m_pLife;				//体力UIへのポインタ
};


#endif