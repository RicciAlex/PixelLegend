//=============================================================================
//
// enemy.cpp
// Author : Ricci Alex
//
//=============================================================================

//インクルードファイル
#include "enemy.h"
#include "bullet.h"
#include "player.h"
#include <stdlib.h>

//コンストラクタ
CEnemy::CEnemy()
{
	//メンバー変数をクリアする
	m_maxSpeed = 0.0f;
	m_fAngleMove = 0.0f;
	m_nCntMove = 0;
	m_nShootDelay = 0;
	m_bDamageable = false;
	m_subType = ENEMYTYPE_MAX;
}

//デストラクタ
CEnemy::~CEnemy()
{

}

//初期化処理
HRESULT CEnemy::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CObject_2D::Init()))
	{
		return -1;
	}

	m_bDamageable = false;
	SetObjType(OBJTYPE_ENEMY);

	return S_OK;
}

//終了処理
void CEnemy::Uninit(void)
{
	//基本クラスの終了処理
	CObject_2D::Uninit();
}

//更新処理 
void CEnemy::Update(void)
{
	
}

//描画処理
void CEnemy::Draw(void)
{
	CObject_2D::Draw();
}

const int CEnemy::GetLife(void)
{
	return m_nLife;
}

void CEnemy::SetLife(const int nLife)
{
	m_nLife = nLife;
}

//最大速度の設定処理
void CEnemy::SetMaxSpeed(const float maxSpeed)
{
	m_maxSpeed = maxSpeed;
}

const float CEnemy::GetMaxSpeed(void)
{
	return m_maxSpeed;
}

//敵の種類の設定
void CEnemy::SetSubtype(const EnemyType subType)
{
	m_subType = subType;
}

const bool CEnemy::GetDamageableState(void)
{
	return m_bDamageable;
}

void CEnemy::SetDamageableState(const bool bDamageable)
{
	m_bDamageable = bDamageable;
}

//敵の種類の取得処理
const CEnemy::EnemyType CEnemy::GetSubtype(void)
{
	return m_subType;
}

////敵の生成処理(種類によって)
//CEnemy* CEnemy::Create(CEnemy::EnemyType type)
//{
//	CEnemy* pEnemy = new CEnemy;			//新しい敵を生成する
//
//	if (pEnemy != nullptr)
//	{
//		//初期化処理
//		if (FAILED(pEnemy->Init()))
//		{
//			delete pEnemy;					//メモリを解放する
//			return nullptr;					//nullを返す
//		}
//
//		pEnemy->SetObjType(CObject::OBJTYPE_ENEMY);		//オブジェクトの種類の設定
//
//		switch (type)
//		{
//		case CObject::ENEMYTYPE_CLOCK:
//
//			pEnemy->SetStartingRot(D3DX_PI * 0.5f);						//回転角度の初期値の設定
//			pEnemy->m_maxSpeed = 2.0f;									//最大速度の設定
//			pEnemy->m_fAngleMove = 0.0f;								//カウンタの設定
//			pEnemy->m_nCntMove = 0;										//カウンタの設定
//			pEnemy->m_nShootDelay = 0;									//カウンタの設定
//			pEnemy->SetTextureParameter(1, 1, 1, INT_MAX);				//テクスチャパラメータの設定
//			pEnemy->SetSize(D3DXVECTOR2(40.0f, 40.0f));					//サイズの設定
//																		
//			pEnemy->SetMove(D3DXVECTOR3(-1.5f, 0.0f, 0.0f));			//速度の設定
//			pEnemy->SetAcceleration(D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//加速の設定
//			pEnemy->SetSubtype(type);									//敵の種類の設定
//																		
//			pEnemy->SetTexture(TextureClock);							//テクスチャの設定
//
//			break;
//
//		case CObject::ENEMYTYPE_CLOUD:
//
//			pEnemy->m_maxSpeed = 10.0f;									//最大速度の設定
//			pEnemy->m_fAngleMove = 0.0f;								//回転角度の初期値の設定
//			pEnemy->m_nCntMove = 0;										//カウンターの設定
//			pEnemy->m_nShootDelay = 0;									//カウンターの設定
//			pEnemy->SetTextureParameter(2, 2, 3, 15);					//テクスチャパラメータの設定
//			pEnemy->SetSize(D3DXVECTOR2(50.0f, 40.0f));					//サイズの設定
//																		
//			pEnemy->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));				//速度の設定
//			pEnemy->SetAcceleration(D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//加速の設定
//			pEnemy->SetSubtype(type);									//敵の種類の設定
//																		
//			pEnemy->SetTexture(TextureCloud);							//テクスチャの設定
//
//			break;
//
//		case CObject::ENEMYTYPE_BOUND_CLOCK:
//
//			pEnemy->m_maxSpeed = 2.0f;									//最大速度の設定
//			pEnemy->m_fAngleMove = 0.0f;								//回転角度の初期値の設定
//			pEnemy->m_nCntMove = 0;										//カウンターの設定
//			pEnemy->m_nShootDelay = 0;									//カウンターの設定
//			pEnemy->SetTextureParameter(1, 1, 1, INT_MAX);				//テクスチャパラメータの設定
//			pEnemy->SetSize(D3DXVECTOR2(40.0f, 40.0f));					//サイズの設定
//
//			pEnemy->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));				//速度の設定
//			pEnemy->SetAcceleration(D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//加速の設定
//			pEnemy->SetSubtype(type);									//敵の種類の設定
//
//			pEnemy->SetTexture(TextureClock);							//テクスチャの設定
//
//			break;
//
//		default:
//			break;
//		}
//	}
//
//	return pEnemy;				//生成されたインスタンスへのポンタを返す
//}

//曇型敵の更新処理
//void CEnemy::UpdateCloud(void)
//{
//	LPDIRECT3DVERTEXBUFFER9 pBuffer = CObject_2D::GetVtxbuff();									//バッファの取得処理
//	D3DXVECTOR3 pos = GetPos();																	//位置の取得処理
//	CPlayer* pPlayer = CObject::GetPlayer();													//プレイヤー情報の取得処理
//	D3DXVECTOR3 PosPlayer = pPlayer->GetPos();													//プレイヤーの位置の取得処理
//	D3DXVECTOR3 move = GetMove();																//速度の取得処理
//	D3DXVECTOR3 acc = GetAcceleration();														//加速の取得処理
//	D3DXVECTOR2 Size = pPlayer->GetSize();														//サイズの取得処理
//	D3DXVECTOR3 target = D3DXVECTOR3(PosPlayer.x, PosPlayer.y - (1.5f * Size.y), 0.0f);			//目的の位置の座標を計算する
//	int nColumn = 0;
//
//	VERTEX_2D* pVtx = nullptr;					//頂点情報へのポインタ
//
//	switch (m_nPhase)
//	{
//	case 0:
//
//	{//プレイヤーの上に向かう
//
//		D3DXVECTOR3 move = target - pos;			//速度の向きを計算する
//		D3DXVec3Normalize(&move, &move);			//向きを正規化する
//		move.x *= m_maxSpeed;
//		move.y *= m_maxSpeed;
//
//		pos += move;								//位置の更新
//
//													//プレイヤーとの距離を計算する
//		float fDistance = sqrtf(((target.x - pos.x) * (target.x - pos.x)) + ((target.y - pos.y) * (target.y - pos.y)));
//
//		if (fDistance <= 5.0f)
//		{//次へ進む
//			m_nPhase++;
//		}
//
//	}
//	break;
//
//	case 1:
//
//		//1.5秒間プレイヤーの上に設定する
//
//		m_nShootDelay++;
//
//		pos = target;				//位置の設定
//
//		if (m_nShootDelay >= 90)
//		{//1.5秒間後次へ進む
//			m_nShootDelay = 0;
//			m_nPhase++;
//		}
//
//		break;
//
//	case 2:
//
//		//動かなくなったら、テクスチャアニメーションと弾の発生
//
//		m_nShootDelay++;
//
//		if (m_nShootDelay < 30 || m_nShootDelay >= 110)
//		{//白い雲
//			nColumn = 0;
//		}
//		else if (m_nShootDelay >= 30 && m_nShootDelay < 60 || m_nShootDelay >= 100 && m_nShootDelay < 110)
//		{//灰色の雲
//			nColumn = 1;
//		}
//		else if (m_nShootDelay >= 60 && m_nShootDelay < 100)
//		{//黒い雲
//			nColumn = 2;
//		}
//
//		if (m_nShootDelay == 90)
//		{//弾を生成する
//			CBullet* pBullet = CBullet::Create(D3DXVECTOR3(pos.x, pos.y + 75.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(30.0f, 100.0f), CBullet::BULLET_THUNDER);
//		}
//		if (m_nShootDelay == 120)
//		{//次へ進む
//			move = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);		//速度の設定
//			acc = D3DXVECTOR3(0.0f, -0.3f, 0.0f);		//加速の設定
//			m_nShootDelay = 0;							//カウンターの設定
//			m_nPhase++;
//		}
//
//		break;
//
//	case 3:
//
//		//画面を出る
//
//		pos += move;			//位置の更新
//		move += acc;			//速度の更新
//
//		if (pos.x <= -GetSize().x || pos.y <= -GetSize().y)
//		{//画面を出たら、弾を消す
//			Release();
//			return;
//		}
//
//		break;
//
//	default:
//		break;
//	}
//
//	SetPos(pos);				//位置の設定
//	SetMove(move);				//速度の設定
//	SetAcceleration(acc);		//加速の設定
//
//								//アニメーション処理
//	m_fAngleMove += 1.0f;		//カウンターの更新
//
//	if (m_fAngleMove >= 15.0f)
//	{
//		m_fAngleMove = 0.0f;
//		m_nCntMove ^= 1;
//	}
//
//	//頂点バッファをロックする
//	pBuffer->Lock(0, 0, (void**)&pVtx, 0);
//
//	//頂点座標の更新
//	pVtx[0].pos = D3DXVECTOR3(pos.x - (Size.x * 0.5f), pos.y - (Size.y * 0.5f), 0.0f);
//	pVtx[1].pos = D3DXVECTOR3(pos.x + (Size.x * 0.5f), pos.y - (Size.y * 0.5f), 0.0f);
//	pVtx[2].pos = D3DXVECTOR3(pos.x - (Size.x * 0.5f), pos.y + (Size.y * 0.5f), 0.0f);
//	pVtx[3].pos = D3DXVECTOR3(pos.x + (Size.x * 0.5f), pos.y + (Size.y * 0.5f), 0.0f);
//
//	//テクスチャ座標の更新
//	pVtx[0].tex = D3DXVECTOR2(0.0f + 0.5f * (m_nCntMove), 0.0f + 0.3334f * (nColumn));
//	pVtx[1].tex = D3DXVECTOR2(0.5f + 0.5f * (m_nCntMove), 0.0f + 0.3334f * (nColumn));
//	pVtx[2].tex = D3DXVECTOR2(0.0f + 0.5f * (m_nCntMove), 0.3334f + 0.3334f * (nColumn));
//	pVtx[3].tex = D3DXVECTOR2(0.5f + 0.5f * (m_nCntMove), 0.3334f + 0.3334f * (nColumn));
//
//	//頂点バッファをアンロックする
//	pBuffer->Unlock();
//}