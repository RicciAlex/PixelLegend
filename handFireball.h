//=============================================================================
//
// handFireball.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef HAND_FIREBALL_H
#define HAND_FIREBALL_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "bullet.h"

//=============================================================================
//前方宣言
//=============================================================================
class CCircleHitbox;

class CHandFireball : public CBullet
{
public:
	CHandFireball();					//コンストラクタ
	~CHandFireball() override;			//デストラクタ

	HRESULT Init(void) override;		//初期化処理
	void Uninit(void) override;			//終了処理
	void Update(void) override;			//更新処理


	static CHandFireball* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);						//生成処理

private:

	float m_fChange;					//次向きを変える座標
	bool  m_Rot;						//向き
										
	CCircleHitbox* m_pHitbox;			//ヒットボックスへのポインタ
};




#endif