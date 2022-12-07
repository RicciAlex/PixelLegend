//=============================================================================
//
// enemyLife.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef ENEMY_LIFE_H
#define ENEMY_LIFE_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "object.h"

//=============================================================================
//前方宣言
//=============================================================================
class CLetter;

class CEnemyLife : public CObject
{
public:

	CEnemyLife();										//コンストラクタ
	~CEnemyLife() override;								//デストラクタ

	HRESULT Init(void) override;						//初期化処理
	void Uninit(void) override;							//終了処理
	void Update(void) override;							//更新処理
	void Draw(void) override;							//描画処理

	void SetPos(const D3DXVECTOR3 pos) override;		//位置の設定処理

	const D3DXVECTOR2 GetSize(void) override;			//サイズの取得処理
	const D3DXVECTOR3 GetPos(void) override;			//位置の取得処理

	void SetLife(const int nLife);						//体力の設定処理
	void SubtractLife(const int nLife);					//体力の引き算処理

	static CEnemyLife* Create(const D3DXVECTOR3 pos, const D3DXCOLOR NameCol, const int MaxLife , const char* pName);		//生成処理

private:

	static const int MaxNameLenght = 24;				//文字の最大数
	static const int MaxDigit = 24;						//数値の最大数

	D3DXVECTOR3 m_pos;									//位置
	D3DXVECTOR2 m_size;									//サイズ
														
	int m_nMaxLife;										//最大の体力
	int m_nLife;										//現在の体力
														
	CLetter* m_pName[MaxNameLenght];					//文字へのポインタ
	CLetter* m_pLife[MaxDigit];							//数値へのポインタ

};

#endif