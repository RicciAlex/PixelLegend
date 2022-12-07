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

	enum state
	{
		state_spawn = 0,
		state_off,
		state_on,
		state_max
	};

	CCandle();
	~CCandle() override;								//デストラクタ
														
	virtual HRESULT Init(void) override;				//初期化処理
	virtual void Uninit(void) override;					//終了処理
	virtual void Update(void) override;					//更新処理
	virtual void Draw(void) override;					//描画処理

	void SetParent(CThanatos* pParent);
	void SetBgPointer(CBg* pointer);

	state GetCandleState(void);

	void Unlit(void);
	void Despawn(void);

	static CCandle* Create(const D3DXVECTOR3 pos);		//生成処理
	static CCandle* Create(const D3DXVECTOR3 pos, CBg* pointer);		//生成処理

private:

	int m_nCntState;
	int m_nIdx;
	state m_state;

	CThanatos* m_pParent;
	CSquareHitbox* m_pHitbox;
	CBg* m_pBg;
	CSkullShield* m_pShield[2];

};

#endif