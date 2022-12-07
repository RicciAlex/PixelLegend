//=============================================================================
//
// target.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef TARGET_H
#define TARGET_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "object2D.h"

class CTarget : public CObject_2D
{
public:
	CTarget();												//コンストラクタ
	~CTarget() override;									//デストラクタ

	HRESULT Init(void) override;							//初期化処理
	void Uninit(void) override;								//終了処理
	void Update(void) override;								//更新処理

	static CTarget* Create(void);							//生成処理

private:

};


#endif