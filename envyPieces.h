//=============================================================================
//
// envyPieces.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef ENVY_PIECES_H
#define ENVY_PIECES_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "bullet.h"

//=============================================================================
//前方宣言
//=============================================================================
class CCircleHitbox;

class CEnvyPieces : public CBullet
{
public:
	CEnvyPieces();						//コンストラクタ
	~CEnvyPieces() override;			//デストラクタ

	HRESULT Init(void) override;		//初期化処理
	void Uninit(void) override;			//終了処理
	void Update(void) override;			//更新処理


	static CEnvyPieces* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move);		//生成処理
	static CEnvyPieces* Create(const D3DXVECTOR3 pos, const float radius);			//生成処理

private:

	CCircleHitbox* m_pHitbox;			//ヒットボックスへのポインタ
};

#endif