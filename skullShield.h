//=============================================================================
//
// skullShield.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef SKULL_SHIELD_H
#define SKULL_SHIELD_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "enemy.h"

//=============================================================================
//前方宣言
//=============================================================================
class CCircleHitbox;

class CSkullShield : public CEnemy
{
public:
	CSkullShield();										//コンストラクタ
	~CSkullShield() override;							//デストラクタ

	virtual HRESULT Init(void) override;				//初期化処理
	virtual void Uninit(void) override;					//終了処理
	virtual void Update(void) override;					//更新処理
	virtual void Draw(void) override;					//描画処理

	static CSkullShield* Create(const D3DXVECTOR3 pos, const float fStartAngle);		//生成処理

private:

	CCircleHitbox* m_pHitbox;							//ヒットボックス
};

#endif