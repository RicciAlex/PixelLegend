//=============================================================================
//
// vertebra.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef VERTEBRA_H
#define VERTEBRA_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "enemy.h"

//=============================================================================
//前方宣言
//=============================================================================
class CCircleHitbox;

class CVertebra : public CEnemy
{
public:
	CVertebra();								//コンストラクタ
	~CVertebra() override;						//デストラクタ

	HRESULT Init(void) override;				//初期化処理
	void Uninit(void) override;					//終了処理
	void Update(void) override;					//更新処理

	static CVertebra* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);			//生成処理

private:

	CCircleHitbox* m_pHitbox;					//ヒットボックスへのポインタ
};

#endif