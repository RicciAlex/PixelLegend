//=============================================================================
//
// ScyllaBody.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef SCYLLABODY_H
#define SCYLLABODY_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "enemy.h"

//=============================================================================
//前方宣言
//=============================================================================
class CSquareHitbox;

class CScyllaBody : public CEnemy
{
public:
	CScyllaBody();								//コンストラクタ
	~CScyllaBody() override;					//デストラクタ

	HRESULT Init(void) override;				//初期化処理
	void Uninit(void) override;					//終了処理
	void Update(void) override;					//更新処理
	void Draw(void) override;					//描画処理


	static CScyllaBody* Create(void);			//生成処理

private:

	CSquareHitbox* m_pHitbox;					//ヒットボックスへのポインタ
};

#endif // !SCYLLABODY_H
