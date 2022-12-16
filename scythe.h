//=============================================================================
//
// scythe.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef SCYTHE_H
#define SCYTHE_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "bullet.h"

//=============================================================================
//前方宣言
//=============================================================================
class CCircleHitbox;

class CScythe : public CBullet
{
public:
	CScythe();							//コンストラクタ
	~CScythe() override;				//デストラクタ

	HRESULT Init(void) override;		//初期化処理
	void Uninit(void) override;			//終了処理
	void Update(void) override;			//更新処理


	static CScythe* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);		//生成処理

private:

	float fCntSize;						//サイズのカウンター

	CCircleHitbox* m_pHitbox;			//ヒットボックスへのポインタ
};




#endif