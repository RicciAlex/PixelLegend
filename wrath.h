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

	const bool GetEnd(void);
	const bool GetDeath(void);
	void Damage(const int nDamage);

	static CWrath* Create(void);				//生成処理

private:

	//void WrathBehavior(void);					//更新処理

	bool m_bEnd;
	bool m_bDeath;

	CWrathBody* m_pBody;
	CEnemyLife* m_pLife;
};



#endif