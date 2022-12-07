//=============================================================================
//
// object.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef OBJECT_H
#define OBJECT_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
class CPlayer;

//=============================================================================
// オブジェクトクラス
//=============================================================================
class CObject
{
public:

	// 頂点データ
	struct VERTEX_2D
	{
		D3DXVECTOR3 pos;			//xyz座標
		float rhw;					//rhw
		D3DCOLOR col;				//カーラー
		D3DXVECTOR2 tex;			//テクスチャ座標
	};

	//オブジェクトの種類
	enum EObjType
	{
		OBJECT2D = 0,						//2Dポリゴン
		OBJTYPE_PLAYER,						//プレイヤー
		OBJTYPE_BULLET,						//弾
		OBJTYPE_EXPLOSION,					//爆発
		OBJTYPE_ENEMY,						//敵
		OBJTYPE_EFFECT,						//エフェクト
		OBJTYPE_LETTER,						//文字
		OBJTYPE_MENU,						
		OBJECT_MAX
	};

	//テクスチャの種類
	enum TextType
	{
		TextureBalloon = 0,
		TextureBalloonEnemy,
		TextureBlackHole,
		TextureBone,
		TextureBubbleBat,

		TextureCandle,
		TextureClock,
		TextureClockNeedle,
		TextureCloud,
		TextureCoin,

		TextureDifficultyIcon,
		TextureDifficultyLogo,
		TextureDragon,

		TextureExplosion,
		TextureEnvyBg,

		TextureFace,
		TextureFireball,

		TextureGear,
		TextureGluttonyBackMaw,
		TextureGluttonyBg,
		TextureGluttonyHeart,
		TextureGluttonyMaw,
		TextureGluttonyMinion,
		TextureGreed,
		TextureGreedBg,

		TextureHand,
		TextureHandBlade,
		TextureHandFireball,

		TextureIconA,
		TextureIconD,
		TextureIconMouse,
		TextureIconS,
		TextureIconW,

		TextureJewel,

		TextureLateralEIcon,
		TextureLateralQIcon,
		TextureLaugh,
		TextureLetters,
		TextureLifeIcon,

		TextureMenuBg,
		TextureMissile,

		TextureNormalEffect,
		TextureNull,
		TextureNumbers,

		TexturePipe,
		TexturePressSpaceIcon,
		TexturePride,
		TexturePrideBg,

		TextureRoundEffect,

		TextureScyllaBody,		
		TextureScythe,			
		TextureSeaBG,			
		TextureSkull,			
		TextureSkullFireball,	
		TextureSkullShield,		
		TextureSloth,
		TextureSlothBg,
		TextureSpike,			
		TextureSpikeBomb,		
		TextureSpringAndScrew,

		TextureTarget,
		TextureTeardrop,  	
		TextureThanatos,	
		TextureThanatosBG,	
		TextureThunder,		
		TextureTopHat,	

		TextureVertebra,

		TextureWing,
		TextureWrath,
		TextureWrathArm,
		TextureWrathBg,
		TextureWrathBody,	

		TextTypeMax
	};

	//敵の種類
	enum EnemyType
	{
		ENEMYTYPE_CLOCK = 0,
		ENEMYTYPE_CLOUD,
		ENEMYTYPE_BOUND_CLOCK,
		ENEMYTYPE_WRATH_ARM,
		ENEMYTYPE_WRATH_BODY,
		ENEMYTYPE_VERTEBRA,
		ENEMYTYPE_SKULL,
		ENEMYTYPE_SCYLLA_BODY,
		ENEMYTYPE_MAX
	};

	static const int MaxObject = 2048;					//オブジェクトの最大数

	CObject();											//コンストラクタ
	virtual~CObject();									//デストラクタ
														
	virtual HRESULT Init(void) = 0;						//初期化処理
	virtual void Uninit(void) = 0;						//終了処理
	virtual void Update(void) = 0;						//更新処理
	virtual void Draw(void) = 0;						//描画処理
														
	virtual void SetPos(const D3DXVECTOR3 pos) = 0;		//位置の設定処理
	
	void Release(void);									//インスタンス一つの終了処理
	const EObjType GetObjType(void);					//種類の取得処理
	void SetObjType(const EObjType type);
	virtual const D3DXVECTOR2 GetSize(void) = 0;		//サイズの取得処理
	virtual const D3DXVECTOR3 GetPos(void) = 0;			//位置の取得処理
	void SetPriority(int nPriority);					//プライオリティの設定処理
														
	//静的関数
	static void ReleaseAll(void);						//全部の終了処理
	static void UpdateAll(void);						//全部の更新処理
	static void DrawAll(void);							//全部の描画処理
	//static CPlayer* GetPlayer(void);					//プレイヤー情報の取得処理
	static CObject** GetObj(void);						//オブジェクトの取得処理
	static void SavePlayerIdx(CPlayer* ptr);			//
	static void SetPause(const bool bPause);			//ポーズの設定処理

	//当たり判定関数
	static bool CircleHit(D3DXVECTOR3* pos1, 
		D3DXVECTOR3* pos2, float fRadius1, float fRadius2);
	static bool CircleHit(D3DXVECTOR3* pos1,
		D3DXVECTOR3* pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2);
	static bool HitBox(D3DXVECTOR3* pos1,
		D3DXVECTOR3* pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2);

	static D3DXVECTOR3 GetPerpendicularVersor(D3DXVECTOR3 V);			//垂直ベクトルを返す
	static int random(const int low, const int high);					//乱数を返す
														
private:								

	static const int Max_Priority = 5;					//最大プライオリティ

	static int m_nNumAll;								//存在するポリゴン数
	static CObject* m_pObject[MaxObject];				//オブジェクトへのポンタ
	static int m_nPriorityObjNum[Max_Priority];			//存在しているプライオリティのオブジェクト数
	static int m_PlayerIdx;								//プレイヤーのインデックス
	static bool m_bPause;								//ポーズ中であるかどうか
	int m_nIdx;											//このインスタンスの配列のインデックス
	int m_nPriority;									//描画順
	EObjType m_type;									//種類
};



#endif