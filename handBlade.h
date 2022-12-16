//=============================================================================
//
// handBlade.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef HAND_BLADE_H
#define HAND_BLADE_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "bullet.h"

//=============================================================================
//前方宣言
//=============================================================================
class CCircleHitbox;

class CHandBlade : public CBullet
{
public:
	CHandBlade();							//コンストラクタ
	~CHandBlade() override;					//デストラクタ

	HRESULT Init(void) override;			//初期化処理
	void Uninit(void) override;				//終了処理
	void Update(void) override;				//更新処理


	static CHandBlade* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);	//生成処理

private:

	CCircleHitbox* m_pHitbox;				//ヒットボックスへのポインタ
};




#endif