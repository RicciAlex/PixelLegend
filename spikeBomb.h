//=============================================================================
//
// spikeBomb.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef SPIKE_BOMB_H
#define SPIKE_BOMB_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "bullet.h"

//=============================================================================
//前方宣言
//=============================================================================
class CCircleHitbox;

class CSpikeBomb : public CBullet
{
public:
	CSpikeBomb();							//コンストラクタ
	~CSpikeBomb() override;					//デストラクタ

	HRESULT Init(void) override;			//初期化処理
	void Uninit(void) override;				//終了処理
	void Update(void) override;				//更新処理


	static CSpikeBomb* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);						//生成処理

private:

	CCircleHitbox* m_pHitbox;				//ヒットボックスへのポインタ
};


#endif