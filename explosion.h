//=============================================================================
//
// explosion.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef EXPLOSION_H
#define EXPLOSION_H

//インクルードファイル
#include "object2D.h"

//爆発のクラス
class CExplosion : public CObject_2D
{
public:
	CExplosion();							//コンストラクタ
	~CExplosion() override;					//デストラクタ
											
	HRESULT Init(void) override;			//初期化処理
	void Uninit(void) override;				//終了処理
	void Update(void) override;				//更新処理

	static CExplosion* Create(void);		//生成処理
											
private:									
	int m_nLastPattern;						//前回のアニメーションパターン
};

#endif // !EXPLOSION_H
