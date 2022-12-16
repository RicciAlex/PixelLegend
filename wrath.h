//=============================================================================
//
// wrath.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef WRATH_H
#define WRATH_H

//インクルードファイル
#include "enemy.h"

//前方宣言
class CWrathBody;
class CEnemyLife;


class CWrath : public CEnemy
{
public:

	CWrath();									//コンストラクタ
	~CWrath() override;							//デストラクタ

	HRESULT Init(void) override;				//初期化処理
	void Uninit(void) override;					//終了処理
	void Update(void) override;					//更新処理
	void Draw(void) override;

	const bool GetEnd(void);					//終わったかどうかの取得処理
	const bool GetDeath(void);					//死亡したかどうかの取得処理
	void Damage(const int nDamage);				//ダメージを受ける処理

	static CWrath* Create(void);				//生成処理

private:

	bool m_bEnd;								//終わったかどうか
	bool m_bDeath;								//死亡したかどうか
												
	CWrathBody* m_pBody;						//体インスタンスへのポインタ
	CEnemyLife* m_pLife;						//体力UIへのポインタ
};



#endif