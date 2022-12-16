//=============================================================================
//
// spike.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef SPIKE_H
#define SPIKE_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "bullet.h"

//=============================================================================
//前方宣言
//=============================================================================
class CSquareHitbox;

class CSpike : public CBullet
{
public:
	CSpike();							//コンストラクタ
	~CSpike() override;					//デストラクタ

	HRESULT Init(void) override;		//初期化処理
	void Uninit(void) override;			//終了処理
	void Update(void) override;			//更新処理


	static CSpike* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move);			//生成処理

private:

	CSquareHitbox* m_pHitbox;			//ヒットボックスへのポインタ

};

#endif