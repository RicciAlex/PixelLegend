//=============================================================================
//
// hitbox.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef HITBOX_H
#define HITBOX_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"

class CHitbox
{
public:

	static const int MaxHitbox = 1024;		//ヒットボックスの最大数
	
	//種類の列挙型
	enum Type
	{
		Type_Enemy = 0,			//敵
		Type_Player,			//プレイヤー
		Type_EnemyBullet,		//敵の弾
		Type_PlayerBullet,		//プレイヤーの弾
		Type_Max
	};

	//形の列挙型
	enum Shape
	{
		shape_Circle = 0,		//円形
		shape_Square,			//四角形
		shape_Capsule,			
		shape_Max
	};

	CHitbox();								//コンストラクタ
	virtual ~CHitbox();						//デストラクタ
											
	virtual HRESULT Init(void);				//初期化処理
	virtual void Uninit(void);				//終了処理
	virtual bool Hit(void) = 0;				//当たり判定の処理
											
	void Release(void);						//破棄処理
											
	const D3DXVECTOR3 GetPos(void);			//位置の取得処理
	const Shape GetShape(void);				//形の取得処理
	const Type GetType(void);				//種類の取得処理
	virtual const D3DXVECTOR2 GetSize(void) = 0;	//サイズの取得処理
	virtual const float GetRadius(void) = 0;		//半径の取得処理
	const bool GetHitState(void);			//当たったかどうかの取得処理
	

	
	void SetPos(const D3DXVECTOR3 pos);		//位置の設定処理
	void SetType(const Type type);			//種類の設定処理
	void SetShape(const Shape shape);		//形の設定処理
	void SetHitState(const bool bHit);		//当たったかどうかの設定処理
											
	static void ReleaseAll(void);			//全部のインスタンスの破棄処理
	static CHitbox** GetAllHitbox(void);	//全部のインスタンスの取得処理

private:

	Type m_Type;				//種類
	Shape m_Shape;				//形
	D3DXVECTOR3 m_pos;			//位置
	int m_nIdx;					//インデックス
	bool m_bHit;				//当たったかどうか

	static CHitbox* m_pHitbox[MaxHitbox];		//全部のインスタンスへのポインタを持っている配列

};



#endif // !HITBOX_H
