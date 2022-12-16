//=============================================================================
//
// starBullet.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef STAR_BULLET_H
#define STAR_BULLET_H

//インクルードファイル
#include "bullet.h"

//前方宣言
class CStarEffect;

class CStarBullet : public CBullet
{
public:
	CStarBullet();						//コンストラクタ
	~CStarBullet() override;			//デストラクタ

	HRESULT Init(void) override;		//初期化処理
	void Uninit(void) override;			//終了処理
	void Update(void) override;			//更新処理

	static CStarBullet* Create(const D3DXVECTOR3 CenterPos, const D3DXVECTOR3 move);				//生成処理

private:

	static const int MaxEffect = 120;			//エフェクトの最大数

	CStarEffect* m_pEffect[MaxEffect];			//エフェクトへのポインタ
};



#endif