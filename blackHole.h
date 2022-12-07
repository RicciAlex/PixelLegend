//=============================================================================
//
// blackHole.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef BLACK_HOLE_H
#define BLACK_HOLE_H

//インクルードファイル
#include "bullet.h"

//弾クラス(CObject2Dの派生クラス)
class CBlackHole : public CBullet
{
public:

	CBlackHole();																	//コンストラクタ
	~CBlackHole() override;															//デストラクタ

	HRESULT Init(void) override;													//初期化処理
	void Uninit(void) override;														//終了処理
	void Update(void) override;														//更新処理

	static CBlackHole* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move,
		const D3DXVECTOR3 acc, const D3DXVECTOR2 dim, const int nLife);				//生成処理

private:

};

#endif // !BLACK_HOLE_H