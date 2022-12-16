//=============================================================================
//
// enemyCloud.cpp
// Author : Ricci Alex
//
//=============================================================================

//インクルードファイル
#include "enemyCloud.h"
#include "player.h"
#include "thunderEnemy.h"

//コンストラクタ
CEnemyCloud::CEnemyCloud()
{
	//メンバー変数をクリアする
	m_nCntMove = 0;
	m_fAngleMove = 0.0f;
	m_nPhase = state_max;
	m_nShootDelay = 0;
}

//デストラクタ 
CEnemyCloud::~CEnemyCloud()
{

}

//初期化処理
HRESULT CEnemyCloud::Init(void)
{
	//メンバー変数を初期化する

	//基本クラスの初期化処理
	if (FAILED(CEnemy::Init()))
	{
		return -1;
	}

	//メンバー変数の初期化
	m_nCntMove = 0;
	m_fAngleMove = 0.0f;
	m_nPhase = state_max;
	m_nShootDelay = 0;

	return S_OK;
}

//終了処理
void CEnemyCloud::Uninit(void)
{
	//基本クラスの終了処理
	CEnemy::Uninit();
}

//更新処理
void CEnemyCloud::Update(void)
{
	float maxSpeed = GetMaxSpeed();
	LPDIRECT3DVERTEXBUFFER9 pBuffer = CObject_2D::GetVtxbuff();									//バッファの取得処理
	D3DXVECTOR3 pos = GetPos();																	//位置の取得処理
	CPlayer* pPlayer = CPlayer::GetPlayer();													//プレイヤー情報の取得処理
	D3DXVECTOR3 PosPlayer = pPlayer->GetPos();													//プレイヤーの位置の取得処理
	D3DXVECTOR3 move = GetMove();																//速度の取得処理
	D3DXVECTOR3 acc = GetAcceleration();														//加速の取得処理
	D3DXVECTOR2 Size = pPlayer->GetSize();														//サイズの取得処理
	D3DXVECTOR3 target = D3DXVECTOR3(PosPlayer.x, PosPlayer.y - (1.5f * Size.y), 0.0f);			//目的の位置の座標を計算する
	int nColumn = 0;

	VERTEX_2D* pVtx = nullptr;					//頂点情報へのポインタ

	switch (m_nPhase)
	{
	case state_pursuit:

	{//プレイヤーの上に向かう

		move = target - pos;			//速度の向きを計算する
		D3DXVec3Normalize(&move, &move);			//向きを正規化する
		move.x *= maxSpeed;
		move.y *= maxSpeed;

		pos += move;								//位置の更新

													//プレイヤーとの距離を計算する
		float fDistance = sqrtf(((target.x - pos.x) * (target.x - pos.x)) + ((target.y - pos.y) * (target.y - pos.y)));

		if (fDistance <= 5.0f)
		{//次へ進む
			m_nPhase = state_aim;
		}

	}
	break;

	case state_aim:

		//1.5秒間プレイヤーの上に設定する

		m_nShootDelay++;

		pos = target;				//位置の設定

		if (m_nShootDelay >= 90)
		{//1.5秒間後次へ進む
			m_nShootDelay = 0;
			m_nPhase = state_fire;
		}

		break;

	case state_fire:

		//動かなくなったら、テクスチャアニメーションと弾の発生

		m_nShootDelay++;

		if (m_nShootDelay < 30 || m_nShootDelay >= 110)
		{//白い雲
			nColumn = 0;
		}
		else if (m_nShootDelay >= 30 && m_nShootDelay < 60 || m_nShootDelay >= 100 && m_nShootDelay < 110)
		{//灰色の雲
			nColumn = 1;
		}
		else if (m_nShootDelay >= 60 && m_nShootDelay < 100)
		{//黒い雲
			nColumn = 2;
		}

		if (m_nShootDelay == 90)
		{//弾を生成する
			CThunderEnemy* pBullet = CThunderEnemy::Create(D3DXVECTOR3(pos.x, pos.y + 75.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(20.0f, 66.0f));
		}
		if (m_nShootDelay == 120)
		{//次へ進む
			move = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);		//速度の設定
			acc = D3DXVECTOR3(0.0f, -0.3f, 0.0f);		//加速の設定
			m_nShootDelay = 0;							//カウンターの設定
			m_nPhase = state_flee;
		}

		break;

	case state_flee:

		//画面を出る

		pos += move;			//位置の更新
		move += acc;			//速度の更新

		if (pos.x <= -GetSize().x || pos.y <= -GetSize().y)
		{//画面を出たら、弾を消す
			Release();
			return;
		}

		break;

	default:
		break;
	}

	SetPos(pos);				//位置の設定
	SetMove(move);				//速度の設定
	SetAcceleration(acc);		//加速の設定

								//アニメーション処理
	m_fAngleMove += 1.0f;		//カウンターの更新

	if (m_fAngleMove >= 15.0f)
	{
		m_fAngleMove = 0.0f;
		m_nCntMove ^= 1;
	}

	//頂点バッファをロックする
	pBuffer->Lock(0, 0, (void**)&pVtx, 0);

	Size = GetSize();

	//頂点座標の更新
	pVtx[0].pos = D3DXVECTOR3(pos.x - (Size.x * 0.5f), pos.y - (Size.y * 0.5f), 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + (Size.x * 0.5f), pos.y - (Size.y * 0.5f), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - (Size.x * 0.5f), pos.y + (Size.y * 0.5f), 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + (Size.x * 0.5f), pos.y + (Size.y * 0.5f), 0.0f);

	//テクスチャ座標の更新
	pVtx[0].tex = D3DXVECTOR2(0.0f + 0.5f * (m_nCntMove), 0.0f + 0.3334f * (nColumn));
	pVtx[1].tex = D3DXVECTOR2(0.5f + 0.5f * (m_nCntMove), 0.0f + 0.3334f * (nColumn));
	pVtx[2].tex = D3DXVECTOR2(0.0f + 0.5f * (m_nCntMove), 0.3334f + 0.3334f * (nColumn));
	pVtx[3].tex = D3DXVECTOR2(0.5f + 0.5f * (m_nCntMove), 0.3334f + 0.3334f * (nColumn));

	//頂点バッファをアンロックする
	pBuffer->Unlock();
}

//描画処理
void CEnemyCloud::Draw(void)
{
	//基本クラスの描画処理
	CEnemy::Draw();
}

CEnemyCloud* CEnemyCloud::Create(D3DXVECTOR3 pos)
{
	CEnemyCloud* pEnemy = new CEnemyCloud;			//新しい敵を生成する

	if (pEnemy != nullptr)
	{
		//初期化処理
		if (FAILED(pEnemy->Init()))
		{
			delete pEnemy;					//メモリを解放する
			return nullptr;					//nullを返す
		}

		pEnemy->SetObjType(CObject::OBJTYPE_ENEMY);					//オブジェクトの種類の設定
		pEnemy->SetPos(pos);										//位置の設定
		pEnemy->SetMaxSpeed(10.0f);									//最大速度の設定
		pEnemy->SetTextureParameter(2, 2, 3, 15);					//テクスチャパラメータの設定
		pEnemy->SetSize(D3DXVECTOR2(50.0f, 40.0f));					//サイズの設定

		pEnemy->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));				//速度の設定
		pEnemy->SetAcceleration(D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//加速の設定
		pEnemy->SetSubtype(CEnemy::ENEMYTYPE_CLOUD);				//敵の種類の設定
		pEnemy->m_nPhase = state_pursuit;

		pEnemy->SetTexture(TextureCloud);							//テクスチャの設定
	}

	return pEnemy;				//生成されたインスタンスへのポンタを返す
}