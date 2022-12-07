//=============================================================================
//
// boundEnemy.cpp
// Author : Ricci Alex
//
//=============================================================================

//インクルードファイル
#include "enemyClock.h"
#include "clockNeedle.h"
#include "player.h"

//コンストラクタ
CEnemyClock::CEnemyClock()
{
	//メンバー変数をクリアする
	m_pBoundBullet[MAX_BOUND_BULLET] = {};
	m_nCntBoundAnimation = 0;

	for (int nCnt = 0; nCnt < MAX_BOUND_BULLET; nCnt++)
	{
		m_bBound[nCnt] = false;
	}
}

//デストラクタ
CEnemyClock::~CEnemyClock()
{

}

//初期化処理
HRESULT CEnemyClock::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CEnemy::Init()))
	{
		return -1;
	}

	//メンバー変数の初期化
	m_nCntBoundAnimation = 0;

	for (int nCnt = 0; nCnt < MAX_BOUND_BULLET; nCnt++)
	{
		if (m_pBoundBullet[nCnt] != nullptr)
		{//nullチェック
			m_pBoundBullet[MAX_BOUND_BULLET]->Release();
			m_pBoundBullet[MAX_BOUND_BULLET] = nullptr;
			m_bBound[nCnt] = false;
		}
	}

	return S_OK;
}

//終了処理
void CEnemyClock::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_BOUND_BULLET; nCnt++)
	{
		if (m_pBoundBullet[nCnt] != nullptr)
		{//nullチェック
			m_pBoundBullet[MAX_BOUND_BULLET]->Release();
			m_pBoundBullet[MAX_BOUND_BULLET] = nullptr;
		}
	}

	//基本クラスの終了処理
	CEnemy::Uninit();
}

//更新処理
void CEnemyClock::Update(void)
{
	UpdateClock();

	//基本クラスの更新処理
	CObject_2D::Update();
}

//描画処理
void CEnemyClock::Draw(void)
{
	//基本クラスの描画処理
	CEnemy::Draw();
}


//生成処理
CEnemyClock* CEnemyClock::Create(D3DXVECTOR3 pos)
{
	CEnemyClock* pEnemy = new CEnemyClock;			//敵を生成する

	if (pEnemy != nullptr)
	{//nullチェック

	 //初期化処理
		if (FAILED(pEnemy->Init()))
		{//初期化できなかったら
			delete pEnemy;				//メモリを解放する
			return nullptr;				//nullを返す
		}

		pEnemy->SetObjType(CObject::OBJTYPE_ENEMY);					//オブジェクトの種類を設定する
		pEnemy->SetSubtype(CObject::ENEMYTYPE_BOUND_CLOCK);			//敵の種類の設定

		pEnemy->SetPos(pos);											//位置の設定
		pEnemy->SetMaxSpeed(4.0f);										//最大速度の設定
		pEnemy->SetStartingRot(D3DX_PI * 0.5f);							//回転角度の初期値
		pEnemy->m_fAngleMove = 0.0f;									//1フレームの回転角度
		pEnemy->m_nCntMove = 0;											//移動カウンタ
		pEnemy->m_nShootDelay = 0;										//弾の発生カウンター
		pEnemy->SetTextureParameter(1, 1, 1, INT_MAX);					//テクスチャパラメータの設定
		pEnemy->SetSize(D3DXVECTOR2(75.0f, 75.0f));						//サイズの設定

		pEnemy->SetMove(D3DXVECTOR3(-2.0f, 0.0f, 0.0f));				//速度の設定
		pEnemy->SetAcceleration(D3DXVECTOR3(0.0f, 0.0f, 0.0f));			//加速の設定


		pEnemy->SetTexture(TextureClock);								//テクスチャの設定

		//階層構造の弾の生成処理

		pEnemy->m_pBoundBullet[0] = CClockNeedle::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(20.0f, 20.0f));

		pEnemy->m_pBoundBullet[0]->SetStartingRot(-D3DX_PI * 0.5f);						//回転角度の初期値
		pEnemy->m_pBoundBullet[0]->SetRotation(-D3DX_PI * 0.001f);						//1フレームの回転角度
		pEnemy->m_pBoundBullet[0]->SetRevolution(pos, -D3DX_PI * 0.001f, 15.0f);		//1フレームの公転角度
		pEnemy->m_bBound[0] = true;														//リリースされているかどうか

		pEnemy->m_pBoundBullet[1] = CClockNeedle::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(30.0f, 30.0f));

		pEnemy->m_pBoundBullet[1]->SetStartingRot(-D3DX_PI * 0.5f);						//回転角度の初期値
		pEnemy->m_pBoundBullet[1]->SetRotation(-D3DX_PI * 0.03f);						//1フレームの回転角度
		pEnemy->m_pBoundBullet[1]->SetRevolution(pos, -D3DX_PI * 0.03f, 20.0f);			//1フレームの公転角度
		pEnemy->m_bBound[1] = true;														//リリースされているかどうか

	}

	return pEnemy;					//敵を返す
}


//時計型の敵の更新処理
void CEnemyClock::UpdateClock(void)
{
	D3DXVECTOR3 pos = GetPos();						//位置の取得処理
	D3DXVECTOR3 dir;								//向き

	if (m_nCntMove <= 0)
	{
		DWORD dwExecLastTime = timeGetTime();		//現在の時間を取得

		srand(dwExecLastTime);

		m_nCntMove = (rand() % 91) + 30;			//速度の向きが変わるまでのフレーム数を計算する
		float fX, fY;

		fX = (float)((rand() % 24001) - 12000);		//速度のXコンポネント

		fY = (float)((rand() % 15001) - 7500);		//速度のYコンポネント

		dir.x = fX;
		dir.y = fY;
		dir.z = 0.0f;

		D3DXVec3Normalize(&dir, &dir);				//正規化処理

		dir.x *= 3.0f;								//速度を計算する
		dir.y *= 3.0f;								//速度を計算する
	}
	else
	{
		dir = GetMove();							//速度の取得
	}

	//=========================================================================================
	//								画面を出ないように
	if (pos.x >= SCREEN_WIDTH * 0.9f)
	{
		pos.x = SCREEN_WIDTH * 0.9f;
		dir.x *= -1.0f;
	}
	if (pos.x <= SCREEN_WIDTH * 0.1f)
	{
		pos.x = SCREEN_WIDTH * 0.1f;
		dir.x *= -1.0f;
	}
	if (pos.y >= SCREEN_HEIGHT * 0.9f)
	{
		pos.y = SCREEN_HEIGHT * 0.9f;
		dir.y *= -1.0f;
	}
	if (pos.y <= SCREEN_HEIGHT * 0.1f)
	{
		pos.y = SCREEN_HEIGHT * 0.1f;
		dir.y *= -1.0f;
	}
	//
	//=========================================================================================

	SetMove(dir);				//速度の設定
	pos += dir;					//位置の更新処理
	SetPos(pos);				//位置の設定

	m_nCntMove--;				//移動カウンターの更新

								//==========================================================================================
								//								弾を撃った後
	if (m_nShootDelay > 0)
	{
		m_nShootDelay--;								//カウンターの更新

		if (m_nShootDelay == 60)
		{
			RespawnNeedle();							//新しい弾を生成する
		}
		else if (m_nShootDelay < 60 && m_nShootDelay > 0)
		{
			//サイズの更新処理
			D3DXVECTOR2 NeedleSize = m_pBoundBullet[0]->GetSize();
			float fD = 20.0f / 60.0f;
			m_pBoundBullet[0]->SetSize(D3DXVECTOR2(NeedleSize.x + fD, NeedleSize.y + fD));
			NeedleSize = m_pBoundBullet[1]->GetSize();
			fD = 30.0f / 60.0f;
			m_pBoundBullet[1]->SetSize(D3DXVECTOR2(NeedleSize.x + fD, NeedleSize.y + fD));
		}
		if (m_nShootDelay <= 0)
		{
			m_nShootDelay = 0;
		}
	}
	//
	//==========================================================================================
	//==========================================================================================
	//
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pBoundBullet[nCnt] != nullptr)
		{
			float fAngSpeed = m_pBoundBullet[nCnt]->GetAngularSpeed();				//回転速度の取得
			D3DXVECTOR2 size = m_pBoundBullet[nCnt]->GetSize();						//サイズの取得

			if (m_bBound[nCnt] == true)
			{
				//回転速度の更新
				m_pBoundBullet[nCnt]->AddAngularSpeed(-D3DX_PI * 0.001f);

				if (fAngSpeed <= -D3DX_PI * 0.25f)
				{
					m_pBoundBullet[nCnt]->SetRotation(0.0f);				//回転を止まる
					CPlayer* pPlayer = CPlayer::GetPlayer();				//プレイヤー情報を取得する
					D3DXVECTOR3 PlayerPos = pPlayer->GetPos();				//プレイヤーの位置を取得する
					D3DXVECTOR3 unit = D3DXVECTOR3(1.0f, 0.0f, 0.0f);		//計算用のヴェクトル
					float dot = 0.0f;										//内積を計算用の変数

					dir = PlayerPos - pos;									//弾の向きの計算
					D3DXVec3Normalize(&dir, &dir);							//向きの正規化
					dot = D3DXVec3Dot(&dir, &unit);							//内積を計算する
					float fAngle = acosf(dot);								//プレイヤーと敵の中の角度

					if (PlayerPos.y > pos.y)
					{
						fAngle *= -1.0f;
					}

					m_pBoundBullet[nCnt]->SetStartingRot(fAngle);									//弾の回転角度の設定
					m_pBoundBullet[nCnt]->SetMove(D3DXVECTOR3(dir.x * 10.0f, dir.y * 10.0f, 0.0f));	//弾の速度の設定
					m_pBoundBullet[nCnt]->SetRevolution(pos, 0.0f, 0.0f);							//公転を止める
					m_bBound[nCnt] = false;															//弾をリリースする
					m_pBoundBullet[nCnt] = nullptr;													//ポインタをnullにする
					m_nShootDelay = 240;															//カウンターの設定
				}
				else
				{
					fAngSpeed = m_pBoundBullet[nCnt]->GetAngularSpeed();							//回転速度の更新
					m_pBoundBullet[nCnt]->SetRevolution(pos, fAngSpeed, size.x * 0.5f);				//公転パラメータの更新
				}
			}
			else
			{
				D3DXVECTOR3 BulletPos = m_pBoundBullet[nCnt]->GetPos();					 //弾の位置の取得
				D3DXVECTOR3 BulletMove = m_pBoundBullet[nCnt]->GetMove();				 //弾の速度の取得

				m_pBoundBullet[nCnt]->SetPos(BulletPos + BulletMove);					 //弾の位置の設定
			}
		}
	}
	//
	//==========================================================================================
}


//時計型敵の弾をリスポーンする処理
void CEnemyClock::RespawnNeedle(void)
{
	D3DXVECTOR3 pos = GetPos();			//位置の取得

	if (m_pBoundBullet[0] == nullptr && m_pBoundBullet[1] == nullptr)
	{//弾のポインタはnullだったら

	 //弾を生成する
		m_pBoundBullet[0] = CClockNeedle::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(20.0f, 20.0f));

		m_pBoundBullet[0]->SetStartingRot(-D3DX_PI * 0.5f);							//回転角度の初期値
		m_pBoundBullet[0]->SetRotation(-D3DX_PI * 0.001f);							//1フレームの回転角度
		m_pBoundBullet[0]->SetRevolution(pos, -D3DX_PI * 0.001f, 15.0f);			//1フレームの公転角度
		m_pBoundBullet[0]->SetSize(D3DXVECTOR2(1.0f, 1.0f));						//リリースされているかどうか
		m_bBound[0] = true;

		m_pBoundBullet[1] = CClockNeedle::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(30.0f, 30.0f));

		m_pBoundBullet[1]->SetStartingRot(-D3DX_PI * 0.5f);							//回転角度の初期値
		m_pBoundBullet[1]->SetRotation(-D3DX_PI * 0.03f);							//1フレームの回転角度
		m_pBoundBullet[1]->SetRevolution(pos, -D3DX_PI * 0.03f, 20.0f);				//1フレームの公転角度
		m_pBoundBullet[1]->SetSize(D3DXVECTOR2(2.0f, 2.0f));						//リリースされているかどうか
		m_bBound[1] = true;
	}
}