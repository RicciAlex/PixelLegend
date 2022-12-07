//=============================================================================
//
// bone.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef BONE_H
#define BONE_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "bullet.h"

//=============================================================================
//前方宣言
//=============================================================================
class CSquareHitbox;

class CBone : public CBullet
{
public:
	CBone();									//コンストラクタ
	~CBone() override;							//デストラクタ

	HRESULT Init(void) override;				//初期化処理
	void Uninit(void) override;					//終了処理
	void Update(void) override;					//更新処理

	static CBone* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move);

private:

	void Split(void);

	bool m_bBroken;

	CSquareHitbox* m_pHitbox;

};

#endif