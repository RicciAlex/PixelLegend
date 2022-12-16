//=============================================================================
//
// candle.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef CANDLE_H
#define CANDLE_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "enemy.h"

//=============================================================================
//前方宣言
//=============================================================================
class CSquareHitbox;
class CBg;
class CThanatos;
class CSkullShield;


class CCandle : public CEnemy
{
public:

	//状態の列挙型
	enum state
	{
		state_spawn = 0,		//スポーン
		state_off,				//消えた
		state_on,				//つけた
		state_max
	};

	CCandle();											//コンストラクタ
	~CCandle() override;								//デストラクタ
														
	virtual HRESULT Init(void) override;				//初期化処理
	virtual void Uninit(void) override;					//終了処理
	virtual void Update(void) override;					//更新処理
	virtual void Draw(void) override;					//描画処理

	void SetParent(CThanatos* pParent);					//親の設定処理
	void SetBgPointer(CBg* pointer);					//背景へのポインタの設定処理
														
	state GetCandleState(void);							//状態の取得処理
														
	void Unlit(void);									//火を消す処理
	void Despawn(void);									//破棄処理

	static CCandle* Create(const D3DXVECTOR3 pos);						//生成処理
	static CCandle* Create(const D3DXVECTOR3 pos, CBg* pointer);		//生成処理

private:

	int m_nCntState;						//状態カウンター
	int m_nIdx;								//インデックス
	state m_state;							//状態
											
	CThanatos* m_pParent;					//親へのポインタ
	CSquareHitbox* m_pHitbox;				//ヒットボックスへのポインタ
	CBg* m_pBg;								//背景へのポインタ
	CSkullShield* m_pShield[2];				

};

#endif