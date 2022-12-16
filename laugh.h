//=============================================================================
//
// laugh.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef LAUGH_H
#define LAUGH_H

//インクルードファイル
#include "bullet.h"

//前方宣言
class CSquareHitbox;
class CLetter;

class CLaughBullet : public CBullet
{
public:
	CLaughBullet();						//コンストラクタ
	~CLaughBullet() override;			//デストラクタ

	HRESULT Init(void) override;		//初期化処理
	void Uninit(void) override;			//終了処理
	void Update(void) override;			//更新処理

	static CLaughBullet* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move);	//生成処理



private:

	CSquareHitbox* m_pHitbox;			//ヒットボックスへのポインタ

};

#endif