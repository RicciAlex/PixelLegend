//=============================================================================
//
// fireballPlayer.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef PLAYER_FIREBALL_H
#define PLAYER_FIREBALL_H

//インクルードファイル
#include "bullet.h"

//前方宣言
class CCircleHitbox;

//弾クラス(CObject2Dの派生クラス)
class CFireballPlayer : public CBullet
{
public:

	CFireballPlayer();				//コンストラクタ
	~CFireballPlayer() override;	//デストラクタ

	HRESULT Init(void) override;	//初期化処理
	void Uninit(void) override;		//終了処理
	void Update(void) override;		//更新処理

	bool Hit(void);					//弾の当たり判定

	void SetStartingAngle(const float fAngle);		//向きの初期値の設定処理

	static CFireballPlayer* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move,
		const D3DXVECTOR3 acc, const D3DXVECTOR2 dim);								//生成処理

private:

	float m_fBulletAngle;			//移動用の角度											
	float m_fBulletInclination;		//速度の向きとの角度								
	D3DXVECTOR3 m_BulletVector;		//ローカル座標の位置					
	D3DXVECTOR3 m_origin;			//スポーンの位置						
									
	CCircleHitbox* m_pHitbox;		//ヒットボックス
};

#endif // !PLAYER_FIREBALL_H