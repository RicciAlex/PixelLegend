//=============================================================================
//
// maw.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef MAW_H
#define MAW_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "enemy.h"

//=============================================================================
//前方宣言
//=============================================================================
class CSquareHitbox;

class CMaw : public CEnemy
{
public:

	//位置
	enum Position
	{
		left = 0,		//左
		up,				//上
		right,			//右
		down			//下
	};

	//状態
	enum state
	{
		state_normal = 0,		//普通の状態
		state_open,				//開く
		state_SingleShoot,		//攻撃(1つ)
		state_TripleShoot,		//攻撃(3つ)
		state_RandomShoot,		//ランダムな攻撃
		state_Spawn,			//召喚
		state_close				//閉じる
	};

	CMaw();											//コンストラクタ
	~CMaw() override;								//デストラクタ

	HRESULT Init(void) override;					//初期化処理
	void Uninit(void) override;						//終了処理
	void Update(void) override;						//更新処理
	void Draw(void) override;						//描画処理

	void Open(void);								//開く処理

	static CMaw* Create(Position Pos);				//生成処理

private:

	void UpdateState(void);						//状態によっての更新処理

	state m_state;								//状態
	Position m_Pos;								//位置

	CSquareHitbox* m_pHitbox;					//ヒットボックス
};

#endif