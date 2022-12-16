//=============================================================================
//
// Thanatos.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef THANATOS_H
#define THANATOS_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "enemy.h"

//=============================================================================
//前方宣言
//=============================================================================
class CSquareHitbox;
class CCandle;
class CBg;
class CEnemyLife;

class CThanatos : public CEnemy
{
public:

	//状態の列挙型
	enum state
	{
		state_Spawn = 0,							//スポーン
		state_Normal,								//普通
		state_Hide,									//隠す
		state_ShowEyes,								//目が見える
		state_Hidden,								//隠した
		state_Vulnerable,							//ダメージを受ける
		state_Death,								//死亡
		state_Max
	};

	CThanatos();									//コンストラクタ
	~CThanatos() override;							//デストラクタ

	virtual HRESULT Init(void) override;			//初期化処理
	virtual void Uninit(void) override;				//終了処理
	virtual void Update(void) override;				//更新処理
	virtual void Draw(void) override;				//描画処理

	const bool GetEnd(void);						//終わったかどうかの取得処理

	void SetBgPointer(CBg* pPointer);				//背景へのポインタの設定処理
	void AddLitCandle(void);						//つけたロウソクの追加処理

	static CThanatos* Create(void);					//生成処理

private:

	const static int Max_Candle = 4;				//ロウソクの最大数

	bool m_bEnd;									//終わったかどうか
	int m_nTargetLife;								//目的の体力
	int m_nLitCandle;								//つけたロウソクの数
	int m_nCntState;								//状態カウンター
	state m_state;									//状態
													
	CBg* m_pBg;										//背景へのポインタ
	CCandle* m_pCandle[Max_Candle];					//ロウソクへのポインタ
	CEnemyLife* m_pLife;							//体力UIへのポインタ
													
	CSquareHitbox* m_pHitbox;						//ヒットボックス
};




#endif