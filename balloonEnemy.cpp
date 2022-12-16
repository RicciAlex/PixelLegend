//=============================================================================
//
// enemy.cpp
// Author : Ricci Alex
//
//=============================================================================

//インクルードファイル
#include "balloonEnemy.h"
#include "circleHitbox.h"
#include "player.h"
#include "explosion.h"
#include "application.h"
#include "sound.h"

//コンストラクタ
CBalloonEnemy::CBalloonEnemy()
{
	//メンバー変数をクリアする
	m_pHitbox = nullptr;
}

CBalloonEnemy::~CBalloonEnemy()
{

}

//初期化処理
HRESULT CBalloonEnemy::Init(void)
{
	//メンバー変数を初期化する
	if (FAILED(CEnemy::Init()))
	{
		return -1;
	}

	m_pHitbox = nullptr;

	return S_OK;
}

//終了処理
void CBalloonEnemy::Uninit(void)
{
	//ヒットボックスの破棄処理
	if (m_pHitbox != nullptr)
	{//nullチェック
		m_pHitbox->Release();			//メモリを解放する
		m_pHitbox = nullptr;			//nullにする
	}

	//基本クラスの終了処理
	CEnemy::Uninit();
}

//更新処理
void CBalloonEnemy::Update(void)
{
	//速度の計算
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 playerPos = CPlayer::GetPlayer()->GetPos();
	D3DXVECTOR3 target = playerPos - pos;
	D3DXVec3Normalize(&target, &target);
	target.x *= 2.5f;
	target.y *= 2.5f;
	target += GetMove();
	D3DXVec3Normalize(&target, &target);
	target.x *= 2.5f;
	target.y *= 2.5f;

	//速度の設定
	SetMove(target);

	//ヒットボックス更新
	if (m_pHitbox)
	{//nullチェック
		m_pHitbox->SetPos(pos);			//位置の設定
	}	

	int nLife = GetLife();				//体力の取得
	nLife--;							//体力の更新

	if (nLife <= 0)
	{//体力が0以下になったら
		CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_EXPLOSION);		//爆発のサウンドエフェクト
		CExplosion* pExplosion = CExplosion::Create();							//爆発を生成する
		pExplosion->SetPos(pos);												//爆発の位置の設定
		pExplosion->SetSize(D3DXVECTOR2(30.0f, 30.0f));							//爆発のサイズの設定

		Release();				//インスタンスを破棄する
		return;
	}
	else
	{
		SetLife(nLife);			//体力の設定
	}

	//基本クラスの更新処理
	CObject_2D::Update();
}

//描画処理
void CBalloonEnemy::Draw(void)
{
	CEnemy::Draw();
}


//生成処理
CBalloonEnemy* CBalloonEnemy::Create(D3DXVECTOR3 pos)
{
	CBalloonEnemy* pEnemy = new CBalloonEnemy;				//インスタンスを生成する

	if (FAILED(pEnemy->Init()))
	{//初期化処理
		return nullptr;
	}

	pEnemy->SetPos(pos);								//位置の設定
	pEnemy->SetStartingRot(D3DX_PI * 0.5f);				//向きの初期値の設定
	pEnemy->SetSize(D3DXVECTOR2(25.0f, 25.0f));			//サイズの設定
	pEnemy->SetTexture(CObject::TextureBalloonEnemy);	//テクスチャの設定
	pEnemy->SetTextureParameter(1, 1, 1, INT_MAX);		//テクスチャパラメータの設定
	pEnemy->SetLife(random(120, 360));					//体力の設定

	//速度の計算
	D3DXVECTOR3 playerPos = CPlayer::GetPlayer()->GetPos();
	D3DXVECTOR3 target = playerPos - pos;
	D3DXVec3Normalize(&target, &target);
	target.x *= 2.5f;
	target.y *= 2.5f;

	pEnemy->SetMove(target);				//速度の設定
		

	//ヒットボックスを生成する
	pEnemy->m_pHitbox = CCircleHitbox::Create(pos, 25.0f, CHitbox::Type_Enemy);

	//色の設定処理
	int nColor = random(0, 5);
	D3DXCOLOR col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	switch (nColor)
	{
	case 0:
		col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		break;
	case 1:
		col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		break;
	case 2:
		col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
		break;
	case 3:
		col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		break;
	case 4:
		col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		break;
	case 5:
		col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
		break;
	default:
		break;
	}

	pEnemy->SetColor(col);

	return pEnemy;					//生成したインスタンスを返す
}