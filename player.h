//=============================================================================
//
// player.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef PLAYER_H
#define PLAYER_H

//インクルードファイル
#include "object2D.h"

//前方宣言
class CSquareHitbox;
class CLifeIcon;

//プレイヤークラス(CObject_2Dの派生クラス)
class CPlayer : public CObject_2D
{
public:
	CPlayer();								//コンストラクタ
	~CPlayer() override;					//デストラクタ
											
	HRESULT Init(void) override;			//初期化処理
	void Uninit(void) override;				//終了処理
	void Update(void) override;				//更新処理
	void Draw(void) override;				//描画処理

	void SetConfusion(const int nTime);		//

	void SetAttack(const int nAttack);		//攻撃力の設定処理

	const int GetLife(void);				//ライフの取得処理
	const int GetAttack(void);				//攻撃力の取得処理
	const bool GetEnd(void);				//死んでいるかどうかの取得処理

	static CPlayer* Create(void);			//生成処理

	static CPlayer* GetPlayer(void);		//プレイヤー情報の取得処理

private:

	int m_nAnimCnt;							//アニメションカウンター
	int m_nShootDelay;						//弾の発生カウンター
	int m_nStateCnt;						//状態カウンター
	int m_nDamageCnt;						//ダメージカウンター
	int m_nAttack;							//攻撃力
	bool m_bConfused;						
	int m_nDir;								//向き
	int m_nLife;							//体力
	bool m_bDead;							//死んでいるかどうか
	bool m_bEnd;							//ゲームオーバーのフラグ

	CSquareHitbox* m_pHitbox;				//ヒットボックス
	static CPlayer* m_pPlayer;				//プレイヤーのアドレス
	CLifeIcon* m_pIcon;						//体力のUIへのポインタ
};

#endif // !PLAYER_H