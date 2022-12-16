//=============================================================================
//
// beam.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef BEAM_H
#define BEAM_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "bullet.h"

//=============================================================================
//前方宣言
//=============================================================================
class CSquareHitbox;

class CBeam : public CBullet
{
public:
	CBeam();							//コンストラクタ
	~CBeam() override;					//デストラクタ

	HRESULT Init(void) override;		//初期化処理
	void Uninit(void) override;			//終了処理
	void Update(void) override;			//更新処理
	void Draw(void) override;

	static CBeam* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const D3DXVECTOR2 size, D3DXCOLOR col);		//生成処理

private:

	CSquareHitbox* m_pHitbox;			//ヒットボックスへのポインタ
};

#endif