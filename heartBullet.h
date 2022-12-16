//=============================================================================
//
// heartBullet.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef HEART_BULLET_H
#define HEART_BULLET_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "bullet.h"

//=============================================================================
//前方宣言
//=============================================================================
class CHeartEffect;

class CHeartBullet : public CBullet
{
public:

	CHeartBullet();						//コンストラクタ
	~CHeartBullet() override;			//デストラクタ

	HRESULT Init(void) override;		//初期化処理
	void Uninit(void) override;			//終了処理
	void Update(void) override;			//更新処理

	static CHeartBullet* Create(const D3DXVECTOR3 CenterPos, const D3DXVECTOR3 move, const D3DXCOLOR col);				//生成処理

private:
	static const int MaxEffect = 40;	//エフェクトの最大数
										
	CHeartEffect* m_pEffect[MaxEffect];	//エフェクトへのポインタ
};


#endif