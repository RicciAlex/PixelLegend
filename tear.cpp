//=============================================================================
//
// tear.cpp
// Author : Ricci Alex
//
//=============================================================================

//インクルードファイル
#include "tear.h"
#include "circleHitbox.h"

//コンストラクタ
CTearBullet::CTearBullet()
{
	//メンバー変数をクリアする
	m_pHitbox = nullptr;
}

//デストラクタ
CTearBullet::~CTearBullet()
{

}

//初期化処理
HRESULT CTearBullet::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CBullet::Init()))
	{
		return -1;
	}

	return S_OK;
}

//終了処理
void CTearBullet::Uninit(void)
{
	//ヒットボックスの破棄
	if (m_pHitbox != nullptr)
	{//nullチェック
		m_pHitbox->Release();			//メモリを解放する
		m_pHitbox = nullptr;			//ポインタをnullにする
	}

	//基本クラスの終了処理
	CBullet::Uninit();
}

//更新処理
void CTearBullet::Update(void)
{
	D3DXVECTOR3 move = GetMove();								//速度の取得
	D3DXVECTOR3 Vec, unit;
	unit = D3DXVECTOR3(0.0f, -1.0f, 0.0f);						//単位ヴェクトルを宣言する
	D3DXVec3Normalize(&Vec, &move);								//速度を正規化する
	float fAngle = (float)acos(D3DXVec3Dot(&Vec, &unit));		//単位ヴェクトルと速度のヴェクトルの間の角度を計算する

	//角度の正規化
	if (Vec.y < unit.y)
	{
		fAngle *= -1.0f;
	}

	//弾の角度の更新処理
	if (move.x <= 0.0f)
	{
		SetStartingRot(fAngle + (-D3DX_PI * 0.5f));
	}
	else
	{
		SetStartingRot(-fAngle + (-D3DX_PI * 0.5f));
	}	

	//速度の更新
	move.y += 0.08f;			
	SetMove(move);

	//基本クラスの更新処理
	CObject_2D::Update();

	m_pHitbox->SetPos(GetPos());

	if (m_pHitbox->Hit())
	{//プレイヤーと当たった場合、弾を消す
		Release();
		return;
	}

	D3DXVECTOR3 pos = GetPos();				//位置の取得
	D3DXVECTOR2 size = GetSize();			//サイズの取得

	if (pos.x + size.x <= 0.0f || pos.x + size.x >= (float)SCREEN_WIDTH || pos.y - size.y >= (float)SCREEN_HEIGHT)
	{//画面を出たら、消す
		Release();
		return;
	}
}

//=============================================================================
//静的関数
//=============================================================================

//生成処理
CTearBullet* CTearBullet::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move)
{
	CTearBullet* pBullet = new CTearBullet;				//新しい弾を生成する

	//初期化処理
	if (FAILED(pBullet->Init()))
	{
		return nullptr;
	}
		
	pBullet->SetPos(pos);								//位置の設定
	pBullet->SetMove(move);								//速度の設定

	pBullet->SetTexture(CObject::TextureTeardrop);		//テクスチャの設定
	pBullet->SetTextureParameter(1, 1, 1, INT_MAX);		//テクスチャパラメータの設定処理
	pBullet->SetSize(D3DXVECTOR2(15.0f, 15.0f));		//サイズの設定

	//弾の回転角度の計算と設定
	D3DXVECTOR3 Vec, unit;
	unit = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	D3DXVec3Normalize(&Vec, &move);
	float fAngle = (float)acos(D3DXVec3Dot(&Vec, &unit));

	if (Vec.y < unit.y)
	{
		fAngle *= -1.0f;
	}

	pBullet->SetStartingRot(fAngle + (D3DX_PI * 0.25f));		//向きの初期値の設定

	pBullet->m_pHitbox = CCircleHitbox::Create(pos, 13.0f, CHitbox::Type_EnemyBullet);		//ヒットボックスの生成

	return pBullet;									//弾を返す
} 
