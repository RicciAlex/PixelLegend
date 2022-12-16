//=============================================================================
//
// balloon.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef BALLOON_H
#define BALLOON_H

//インクルードファイル
#include "bullet.h"

//前方宣言
class CCircleHitbox;

class CBalloonBullet : public CBullet
{
public:
	CBalloonBullet();					//コンストラクタ
	~CBalloonBullet() override;			//デストラクタ

	HRESULT Init(void) override;		//初期化処理
	void Uninit(void) override;			//終了処理
	void Update(void) override;			//更新処理

	static CBalloonBullet* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, D3DXCOLOR col);	//生成処理



private:

	CCircleHitbox* m_pHitbox;			//ヒットボックスへのポインタ

};




#endif