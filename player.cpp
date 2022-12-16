//=============================================================================
//
// player.cpp
// Author : Ricci Alex
//
//=============================================================================

//インクルードファイル
#include "player.h"
#include "inputKeyboard.h"
#include "fireballPlayer.h"
#include "application.h"
#include "inputMouse.h"
#include "squareHitbox.h"
#include "lifeIcon.h"
#include "sound.h"

//静的変数の初期化
CPlayer* CPlayer::m_pPlayer = nullptr;

//コンストラクタ
CPlayer::CPlayer()
{
	//メンバー変数をクリアする
	m_nShootDelay = 0;
	m_nStateCnt = 0;
	m_nDir = 0;
	m_nLife = 0;
	m_nDamageCnt = 0;
	m_nAttack = 0;							
	m_nAnimCnt = 0;
	m_bConfused = false;
	m_bDead = false;
	m_bEnd = false;
	m_pHitbox = nullptr;
	m_pIcon = nullptr;
}

//デストラクタ
CPlayer::~CPlayer()
{

}

//初期化処理
HRESULT CPlayer::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CObject_2D::Init()))
	{
		return -1;
	}

	//メンバー変数の初期化処理
	CObject::SavePlayerIdx(this);
	SetTexture(CObject::TextureDragon);				//テクスチャの設定
	SetTextureParameter(2, 2, 3, 16);				//テクスチャパラメータの設定
	SetSize(D3DXVECTOR2(50.0f, 50.0f));				//サイズの設定
	SetStartingRot(D3DX_PI * 0.5f);					//回転角度の設定
	m_nShootDelay = 0;								//弾を発生する用のカウンター
	m_nStateCnt = 0;								//状態カウンター
	m_nDamageCnt = 0;								//ダメージカウンター
	int nDifficulty = CApplication::GetDifficulty();//難易度
	m_nAttack = 100 - (25 * (nDifficulty - 1));		//攻撃力
	m_nAnimCnt = 0;									//アニメーション用のカウンター
	m_nLife = 15;									//体力
	m_nDir = -1;									//向き
	m_bConfused = false;							
	m_bDead = false;								//死亡したかどうか
	m_bEnd = false;									//終わったかどうか
	m_pIcon = nullptr;								//UIインスタンスへのポインタ
	m_pPlayer = this;								//このインスタンスへのポインタ
	
	return S_OK;
}

//終了処理
void CPlayer::Uninit(void)
{
	//ヒットボックスの破棄処理
	if (m_pHitbox != nullptr)
	{//nullチェック
		m_pHitbox->Release();			//メモリを解放する
		m_pHitbox = nullptr;			//nullにする
	}

	//UIの破棄処理
	if (m_pIcon != nullptr)
	{//nullチェック
		m_pIcon->Release();				//メモリを解放する
		m_pIcon = nullptr;				//nullにする
	}

	m_pPlayer = nullptr;				//nullにする

	//基本クラスの終了処理
	CObject_2D::Uninit();
}

//更新処理
void CPlayer::Update(void)
{
	D3DXVECTOR3 pos = CObject_2D::GetPos();					//位置の取得処理
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//移動量

	if (!m_bDead)
	{
		//位置の更新処理
		if (CInputKeyboard::GetKeyboardPress(DIK_D))
		{//Dボタンを押した場合
			if (!m_bConfused)
			{
				move += D3DXVECTOR3(1.0f, 0.0f, 0.0f);
			}
			else
			{
				move += D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			}
		}
		if (CInputKeyboard::GetKeyboardPress(DIK_A))
		{//Aボタンを押した場合
			if (!m_bConfused)
			{
				move += D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
			}
			else
			{
				move += D3DXVECTOR3(0.0f, -1.0f, 0.0f);
			}
		}
		if (CInputKeyboard::GetKeyboardPress(DIK_W))
		{//Wボタンを押した場合
			if (!m_bConfused)
			{
				move += D3DXVECTOR3(0.0f, -1.0f, 0.0f);
			}
			else
			{
				move += D3DXVECTOR3(1.0f, 0.0f, 0.0f);
			}
		}
		if (CInputKeyboard::GetKeyboardPress(DIK_S))
		{//Sボタンを押した場合
			if (!m_bConfused)
			{
				move += D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			}
			else
			{
				move += D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
			}
		}

		//速度の設定
		D3DXVec3Normalize(&move, &move);
		move.x *= 5.0f;
		move.y *= 5.0f;

		//向きの設定
		if (move.x > 0.0f)
		{
			m_nDir = 1;
		}
		else if (move.x < 0.0f)
		{
			m_nDir = -1;
		}

		//位置の更新
		pos += move;

		if (m_nShootDelay >= 0)
		{//弾の発生カウンターが0以上だったら
			m_nShootDelay--;			//カウンターをデクリメントする
		}

		if (!CApplication::GetMouse()->GetMouseLeftClick() && GetPresentAnimPattern() > 1)
		{
			SetTextureParameter(2, 2, 3, 16);
			SetAnimPattern(CObject_2D::GetPresentAnimPattern() - 2);
		}

		if (CApplication::GetMouse()->GetMouseLeftClick())
		{//スペースキーを押したら、弾を生成する

			if (m_nShootDelay <= 0)
			{//弾の発生処理

				//マウスカーソルの位置の取得と変換
				POINT pt;
				GetCursorPos(&pt);
				HWND wnd = CApplication::GetWindow();
				ScreenToClient(wnd, &pt);
				D3DXVECTOR3 MousePos, Target;
				MousePos.x = (float)pt.x;
				MousePos.y = (float)pt.y;
				MousePos.z = 0.0f;

				//発生の位置を計算する
				Target = MousePos - pos;
				D3DXVec3Normalize(&Target, &Target);
				D3DXVECTOR3 spawnPos = pos;
				spawnPos.x += m_nDir * 35.0f;
				spawnPos.y -= 3.0f;

				m_nShootDelay = 20;													//カウンターを設定する
				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_FIRE);		//ショットのサウンドエフェクト

				//弾2つ生成して、必要な情報を設定する
				CFireballPlayer* pBullet = CFireballPlayer::Create(spawnPos, D3DXVECTOR3(10.0f * Target.x, 10.0f * Target.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(16.0f, 16.0f));
				pBullet = CFireballPlayer::Create(spawnPos, D3DXVECTOR3(10.0f * Target.x, 10.0f * Target.y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(16.0f, 16.0f));
				pBullet->SetStartingAngle(D3DX_PI);
			}

			m_nAnimCnt++;			//アニメーション用のカウンターをインクリメントする

			//テクスチャアニメションの処理
			int nCell = 2;

			if (m_nAnimCnt >= 16)
			{
				nCell++;

				if (m_nAnimCnt >= 32)
				{
					m_nAnimCnt = 0;
				}
			}

			SetTextureParameter(1, 2, 3, INT_MAX);
			SetAnimPattern(nCell);
		}
		else
		{
			m_nAnimCnt = 0;				//カウンターを0に戻す
		}

		//状態カウンターの更新
		if (m_nStateCnt > 0)
		{
			m_nStateCnt--;

			if (m_nStateCnt <= 0)
			{
				m_nStateCnt = 0;
				m_bConfused = false;
			}
		}

		//ダメージカウンターの更新
		if (m_nDamageCnt > 0)
		{
			m_nDamageCnt--;			//カウンターをインクリメントする

			if (m_nDamageCnt % 5 == 4)
			{//5フレームが経ったら、色を変える

				D3DXCOLOR col = GetColor();			//色の取得

				if (col.g < 1.0f)
				{//赤かったら
					SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				}
				else
				{//普通だったら
					SetColor(D3DXCOLOR(1.0f, 0.4f, 0.4f, 1.0f));
				}

			}

			if (m_nDamageCnt <= 0)
			{//カウンターが0以下になったら
				m_nDamageCnt = 0;
				SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
		}

		//画面外出られないする処理
		//X座標
		if (pos.x <= GetSize().x)
		{
			pos.x = GetSize().x;			//位置の設定
		}
		else if (pos.x >= (float)SCREEN_WIDTH - GetSize().x)
		{
			pos.x = (float)SCREEN_WIDTH - GetSize().x;			//位置の設定
		}
		//Y座標
		if (pos.y <= GetSize().y)
		{
			pos.y = GetSize().y;			//位置の設定
		}
		else if (pos.y >= (float)SCREEN_HEIGHT - GetSize().y)
		{
			pos.y = (float)SCREEN_HEIGHT - GetSize().y;			//位置の設定
		}

		//位置の設定
		CObject_2D::SetPos(pos);

		//当たり判定
		if (m_pHitbox != nullptr)
		{//nullチェック
			m_pHitbox->SetPos(pos);				//位置の設定

			if (m_pHitbox->GetHitState() || m_pHitbox->Hit())
			{//当たった場合
				m_pHitbox->SetHitState(false);			//普通の状態にする

				if (m_nDamageCnt <= 0)
				{//ダメージカウンターが0以下だったら

					int nDiff = CApplication::GetDifficulty();			//難易度の取得

					//体力の更新
					for (int nCnt = 0; nCnt < nDiff; nCnt++)
					{
						m_nLife--;				//体力をデクリメントする
						m_pIcon->Update();		//UIの更新
					}

					//無敵状態カウンターの設定
					m_nDamageCnt = 60 - (10 * CApplication::GetDifficulty());

					//色の設定
					SetColor(D3DXCOLOR(1.0f, 0.4f, 0.4f, 1.0f));
				}
			}
		}

		if (m_nLife <= 0)
		{//体力が0以下になったら

			m_bDead = true;												//死亡した状態にする
			SetMove(D3DXVECTOR3((float)random(-2, 2), -10.0f, 0.0f));	//移動量の設定
			SetAcceleration(D3DXVECTOR3(0.0f, 0.5f, 0.0f));				//加速の設定
			SetAnimPattern(4);											//アニメションパターンの設定
			SetTextureParameter(1, 2, 3, INT_MAX);						//テクスチャパラメータの設定
			SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));				//色の設定
			SetPriority(5);												//プライオリティの設定
		}

		if (!GetFlipX() && m_nDir == -1 || GetFlipX() && m_nDir == 1)
		{//向きによってテクスチャを反転する
			FlipX();
		}
	}
	else
	{//死亡した場合
		if (pos.y >= 1350.0f)
		{//画面を出たら、少し待って、死亡フラグをtrueにする
			m_bEnd = true;
		}
	}

	//基本クラスの更新
	CObject_2D::Update();
}

//描画処理
void CPlayer::Draw(void)
{
	//基本クラスの描画処理
	CObject_2D::Draw();
}

void CPlayer::SetConfusion(const int nTime)
{
	m_bConfused = true;
	m_nStateCnt = nTime;
}

//攻撃力の設定処理
void CPlayer::SetAttack(const int nAttack)
{
	m_nAttack = nAttack;
}

//ライフの設定処理
const int CPlayer::GetLife(void)
{
	return m_nLife;
}

//攻撃力の取得処理
const int CPlayer::GetAttack(void)
{
	return m_nAttack;
}

//終わったかどうかの取得処理
const bool CPlayer::GetEnd(void)
{
	return m_bEnd;
}


//プレイヤーの生成処理
CPlayer* CPlayer::Create(void)
{
	CPlayer* pPlayer = nullptr;

	pPlayer = new CPlayer;									//新しいプレイヤーを生成する

	//初期化処理
	if (FAILED(pPlayer->Init()))
	{//できなかったら

		return nullptr;
	}

	pPlayer->m_nLife = 15;									//体力の設定処理

	pPlayer->SetObjType(CObject::OBJTYPE_PLAYER);			//オブジェクト種類の設定

	//ヒットボックスの生成処理
	pPlayer->m_pHitbox = CSquareHitbox::Create(pPlayer->GetPos(), D3DXVECTOR2(20.0f, 20.0f), CHitbox::Type_Player);

	//UIの生成処理
	pPlayer->m_pIcon = CLifeIcon::Create(D3DXVECTOR3(50.0f, 50.0f, 0.0f));

	return pPlayer;											//生成したポインタを返す
} 

//プレイヤー情報の取得処理
CPlayer* CPlayer::GetPlayer(void)
{
	return m_pPlayer;
}