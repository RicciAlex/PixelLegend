////=============================================================================
////
//// boundEnemy.h
//// Author : Ricci Alex
////
////=============================================================================
//
////インクルードファイル
//#include "enemy.h"
//
////階層構造アニメーションの敵クラス(敵クラスの派生クラス)
//class CBoundEnemy : public CEnemy
//{
//public:
//
//	static const int MAX_BOUND_OBJECT = 5;										//階層構造のメンバーの最大数
//
//	CBoundEnemy();																//コンストラクタ		
//	~CBoundEnemy();																//デストラクタ
//																				
//	HRESULT Init(void) override;												//初期化処理
//	void Uninit(void) override;													//終了処理
//	void Update(void) override;													//更新処理
//	void Draw(void) override;													//描画処理
//																				
//	static CBoundEnemy* Create(CObject::EnemyType type, D3DXVECTOR3 pos);		//生成処理
//
//
//private:
//
//	void UpdateClock(void);										//時計型敵の更新処理
//	void RespawnNeedle(void);									//時計型敵の弾のリスポーン処理
//																
//	CObject_2D* m_pBoundObject[MAX_BOUND_OBJECT];				//階層構造のオブジェクトへのポインタ
//	bool m_bBound[MAX_BOUND_OBJECT];							//階層構造のオブジェクトはリリースされたかどうか
//	int m_nCntBoundAnimation;									//階層構造アニメーション用のカウンター
//
//};
//
