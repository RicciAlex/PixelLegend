//=============================================================================
//
// wrath.cpp
// Author : Ricci Alex
//
//=============================================================================

//インクルードファイル
#include "wrath.h"
#include "enemyWrathBody.h"
#include "handFlamethrower.h"
#include "handGun.h"
#include "handCharger.h"
#include "player.h"
#include "enemyLife.h"

//コンストラクタ
CWrath::CWrath()
{
	//メンバー変数をクリアする
	m_bEnd = false;
	m_bDeath = false;
	m_pBody = nullptr;
	m_pLife = nullptr;
}

//デストラクタ
CWrath::~CWrath()
{

}

//初期化処理
HRESULT CWrath::Init(void)
{
	//メンバー変数を初期化する
	if (FAILED(CEnemy::Init()))
	{//基本クラスの初期化処理
		return -1;
	}

	m_bEnd = false;
	m_bDeath = false;
	m_pBody = nullptr;
	m_pLife = nullptr;

	return S_OK;
}

//終了処理
void CWrath::Uninit(void)
{
	//体インスタンスの破棄処理
	if (m_pBody != nullptr)
	{//nullチェック
		m_pBody->Release();				//メモリを解放する
		m_pBody = nullptr;				//nullにする
	}

	//体力UIの破棄処理
	if (m_pLife != nullptr)
	{//nullチェック
		m_pLife->Release();				//メモリを解放する
		m_pLife = nullptr;				//nullにする
	}

	//基本クラスの終了処理
	CEnemy::Uninit();
}

//更新処理
void CWrath::Update(void)
{
	int nLife = GetLife();										//体力の取得
	D3DXVECTOR3 playerPos = CPlayer::GetPlayer()->GetPos();		//プレイヤーの位置の取得
	
	if (nLife <= 0)
	{//体力が0以下になったら、死亡した状態にする
		m_bDeath = true;
	}

	//体インスタンスの更新処理
	if (m_pBody != nullptr)
	{//nullチェック
		if (m_pBody->GetDeath())
		{//死んだかどうかを確認する
			m_pBody->Release();					//体インスタンスを破棄する
			m_pBody = nullptr;					//ポインタをnullにする
		}
	}
	else
	{//体インスタンスが死んだら

		m_nShootDelay++;			//攻撃カウンターを更新する

		if (m_nShootDelay >= 500)
		{//一定時間が経ったら
			if (nLife >= 12500)
			{//体力が決まった値以上だったら

				int nSelect = random(0, 200);				//攻撃の種類をランダムで決める(25%ごとの確率)

				if (nSelect < 50)
				{
					//左から火の手をスポーンする
					CHandFlamethrower* pEnemy = CHandFlamethrower::Create(D3DXVECTOR3(-100.0f, playerPos.y, 0.0f), D3DXVECTOR3(2.0f, 0.0f, 0.0f));
					pEnemy->SetParent(this);
				}
				else if (nSelect >= 50 && nSelect < 100)
				{
					//右から火の手をスポーンする
					CHandFlamethrower* pEnemy = CHandFlamethrower::Create(D3DXVECTOR3((float)SCREEN_WIDTH + 100.0f, playerPos.y, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f));
					pEnemy->SetParent(this);
				}
				else if (nSelect >= 100 && nSelect < 150)
				{
					//左から他の手をスポーンする
					CHandGun* pEnemy = CHandGun::Create(D3DXVECTOR3(-100.0f, playerPos.y, 0.0f), D3DXVECTOR3(2.0f, 0.0f, 0.0f));
					pEnemy->SetParent(this);
				}
				else
				{
					//右から他の手をスポーンする
					CHandGun* pEnemy = CHandGun::Create(D3DXVECTOR3((float)SCREEN_WIDTH + 100.0f, playerPos.y, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f));
					pEnemy->SetParent(this);
				}
			}
			else if (nLife < 12500 && nLife >= 10000)
			{//体力が12500未満、10000以上だったら、ランダムで2つのパターンの中ランダムで選ぶ
				int nSelect = random(0, 100);

				//右からも左からも上の手型の敵が現れて、攻撃する
				if (nSelect < 50)
				{
					CHandFlamethrower* pEnemy = CHandFlamethrower::Create(D3DXVECTOR3(-100.0f, playerPos.y, 0.0f), D3DXVECTOR3(2.0f, 0.0f, 0.0f));
					pEnemy->SetParent(this);
					CHandGun* pEnemy2 = CHandGun::Create(D3DXVECTOR3((float)SCREEN_WIDTH + 100.0f, playerPos.y, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f));
					pEnemy2->SetParent(this);
				}
				else
				{
					CHandFlamethrower* pEnemy = CHandFlamethrower::Create(D3DXVECTOR3((float)SCREEN_WIDTH + 100.0f, playerPos.y, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f));
					pEnemy->SetParent(this);
					CHandGun* pEnemy2 = CHandGun::Create(D3DXVECTOR3(-100.0f, playerPos.y, 0.0f), D3DXVECTOR3(2.0f, 0.0f, 0.0f));
					pEnemy2->SetParent(this);
				}
			}
			else
			{//体力が10000未満だったら、手型の敵3種類現れて、攻撃する

				int nSelect = random(0, 100);

				if (nSelect < 50)
				{
					CHandFlamethrower* pEnemy = CHandFlamethrower::Create(D3DXVECTOR3(-100.0f, playerPos.y, 0.0f), D3DXVECTOR3(2.0f, 0.0f, 0.0f));
					pEnemy->SetParent(this);
					CHandGun* pEnemy2 = CHandGun::Create(D3DXVECTOR3((float)SCREEN_WIDTH + 100.0f, playerPos.y, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f));
					pEnemy2->SetParent(this);
				}
				else
				{
					CHandFlamethrower* pEnemy = CHandFlamethrower::Create(D3DXVECTOR3((float)SCREEN_WIDTH + 100.0f, playerPos.y, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f));
					pEnemy->SetParent(this);
					CHandGun* pEnemy2 = CHandGun::Create(D3DXVECTOR3(-100.0f, playerPos.y, 0.0f), D3DXVECTOR3(2.0f, 0.0f, 0.0f));
					pEnemy2->SetParent(this);
				}

				CHandCharger* pEnemy = CHandCharger::Create(D3DXVECTOR3(playerPos.x, -100.0f, 0.0f));
				pEnemy->SetParent(this);
			}

			m_nShootDelay = 0;				//攻撃カウンターを0に戻す
		}
	}

	if (m_bDeath)
	{//死亡した場合
		m_nCntMove++;			//移動カウンターを更新する

		if (m_nCntMove >= 60)
		{//1秒が経ったら
			m_bEnd = true;		//終わった状態にする
		}
	}
}

//描画処理
void CWrath::Draw(void)
{
	//基本クラスの描画処理
	CObject_2D::Draw();
}


//終わったかどうかの取得処理
const bool CWrath::GetEnd(void)
{
	return m_bEnd;
}

//死亡したかどうかの取得処理
const bool CWrath::GetDeath(void)
{
	return m_bDeath;
}

//ダメージを受ける処理
void CWrath::Damage(const int nDamage)
{
	int nLife = GetLife();		//体力の取得処理

	if (nLife > 0)
	{//体力が0以上だったら

		SetLife(nLife - nDamage);			//体力の設定処理

		//体力のUIの更新
		if (m_pLife != nullptr)
		{//nullチェック
			m_pLife->SubtractLife(nDamage);	//UIを更新する
		}
	}
}






//生成処理
CWrath* CWrath::Create(void)
{
	CWrath* pEnemy = new CWrath;

	if (FAILED(pEnemy->Init()))
	{
		return nullptr;
	}

	pEnemy->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pEnemy->SetSize(D3DXVECTOR2(0.0f, 0.0f));
	pEnemy->SetLife(30000);
	pEnemy->SetTexture(CObject::TextureNull);
	pEnemy->SetTextureParameter(1, 1, 1, INT_MAX);

	pEnemy->m_pBody = CWrathBody::Create(D3DXVECTOR3(1400.0f, 350.0f, 0.0f));
	
	if (pEnemy->m_pBody != nullptr)
	{
		pEnemy->m_pBody->SetParent(pEnemy);
	}

	pEnemy->m_nShootDelay = 440;

	pEnemy->m_pLife = CEnemyLife::Create(D3DXVECTOR3(900.0f, 40.0f, 0.0f), D3DXCOLOR(0.0f, 1.0f, 0.5f, 0.4f), 30000, "wrath");

	return pEnemy;
}

