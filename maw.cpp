//=============================================================================
//
// maw.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "maw.h"
#include "squareHitbox.h"
#include "player.h"
#include "bone.h"
#include "skeleton.h"

#include "inputKeyboard.h"

//コンストラクタ
CMaw::CMaw()
{
	//メンバー変数をクリアする
	m_state = state_normal;

	m_pHitbox = nullptr;
}

//デストラクタ
CMaw::~CMaw()
{

}

//初期化処理
HRESULT CMaw::Init(void)
{
	if (FAILED(CEnemy::Init()))
	{//基本クラスの初期化処理
		return -1;
	}

	//メンバー変数を初期化する
	m_state = state_normal;

	m_pHitbox = nullptr;

	return S_OK;
}

//終了処理
void CMaw::Uninit(void)
{
	//ヒットボックスの破棄処理
	if (m_pHitbox != nullptr)
	{//nullチェック
		m_pHitbox->Release();			//メモリを解放する
		m_pHitbox = nullptr;			//ポインタをnullにする
	}

	//基本クラスの終了処理
	CEnemy::Uninit();
}

//更新処理
void CMaw::Update(void)
{
	//基本クラスの更新処理
	CObject_2D::Update();

	//ヒットボックスの更新処理
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Hit();	//衝突を判定する(無敵な敵なので、ダメージを受けない)
	}

	UpdateState();			//状態によっての更新処理
}

//描画処理
void CMaw::Draw(void)
{
	//基本クラスの描画処理
	CObject_2D::Draw();
}

//開く処理
void CMaw::Open(void)
{
	m_state = state_open;		//開く状態にする

	m_nPhase = 0;				//カウンターを0に戻す
	m_nShootDelay = 0;			//攻撃カウンターを0に戻す
}



//=============================================================================
//
//								静的関数
//
//=============================================================================



//生成処理
CMaw* CMaw::Create(Position Pos)
{
	CMaw* pEnemy = new CMaw;			//インスタンスを生成する

	if (FAILED(pEnemy->Init()))
	{//初期化処理
		return nullptr;
	}

	pEnemy->SetSize(D3DXVECTOR2(150.0f, 20.0f));			//サイズの設定
	pEnemy->SetTexture(CObject::TextureGluttonyMaw);		//テクスチャの設定
	pEnemy->SetTextureParameter(1, 1, 5, INT_MAX);			//テクスチャパラメータの設定
															
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		
	float fStartingAngle = 0.0f;							
	D3DXVECTOR2 size = D3DXVECTOR2(0.0f, 0.0f);				

	//=======================================================================================================================
	//位置によって位置、向きとサイズの設定
	switch (Pos)
	{
	case CMaw::left:

	{
		pos = D3DXVECTOR3(85.0f, (float)SCREEN_HEIGHT * 0.5f, 0.0f);
		fStartingAngle = -D3DX_PI * 0.5f;
		size = D3DXVECTOR2(15.0f, 90.0f);
	}

		break;

	case CMaw::up:

	{
		pos = D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, 85.0f, 0.0f);
		fStartingAngle = D3DX_PI;
		size = D3DXVECTOR2(90.0f, 15.0f);
	}

		break;

	case CMaw::right:

	{
		pos = D3DXVECTOR3((float)SCREEN_WIDTH - 85.0f, (float)SCREEN_HEIGHT * 0.5f, 0.0f);
		fStartingAngle = D3DX_PI * 0.5f;
		size = D3DXVECTOR2(15.0f, 90.0f);
	}

		break;

	case CMaw::down:

	{
		pos = D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT - 85.0f, 0.0f);
		fStartingAngle = 0.0f;
		size = D3DXVECTOR2(90.0f, 15.0f);
	}

		break;

	default:
		break;
	}
	//=======================================================================================================================

	pEnemy->SetPos(pos);															//位置の設定
	pEnemy->SetStartingRot(D3DX_PI * 0.5f + fStartingAngle);						//向きの初期値の設定
	pEnemy->m_pHitbox = CSquareHitbox::Create(pos, size, CHitbox::Type_Enemy);		//ヒットボックスの生成

	return pEnemy;				//生成したインスタンスを返す
}



//=============================================================================
//
//							プライベート関数
//
//=============================================================================



//状態によっての更新処理
void CMaw::UpdateState(void)
{
	switch (m_state)
	{
	case CMaw::state_normal:

	{//普通の状態

	}

		break;

	case CMaw::state_open:

	{//開く状態

		m_nPhase++;			//カウンターをインクリメントする

		if (m_nPhase % 8 == 7)
		{//8フレームごとアニメーションパターンを更新する

			int anim = GetPresentAnimPattern();

			if (anim >= 4)
			{//アニメーションが終わったら、ランダムで次の攻撃を設定する

				switch (int a = random(0, 3))
				{
				case 0:

					m_state = state_SingleShoot;			//攻撃(１つ)

					break;

				case 1:

					m_state = state_TripleShoot;			//攻撃(３つ)

					break;

				case 2:

					m_state = state_RandomShoot;			//ランダムな攻撃

					break;

				case 3:

					m_state = state_Spawn;					//召喚

				default:
					break;
				}
				
				m_nPhase = 0;								//カウンターを0に戻す
			}
			else
			{
				anim++;						//アニメーションカウンターをインクリメントする
				SetAnimPattern(anim);		//アニメーションパターンを設定する
			}
		}
	}

		break;

	case CMaw::state_SingleShoot:

	{//攻撃(１つ)

		m_nShootDelay++;				//攻撃カウンターをインクリメントする

		if (m_nShootDelay % 50 == 5)
		{//50フレームごと１つの弾を生成する

			D3DXVECTOR3 pos, PlayerPos, target;

			//プレイヤーまでのベクトルを計算して、正規化して、弾の速度として使う
			pos = GetPos();
			PlayerPos = CPlayer::GetPlayer()->GetPos();
			target = PlayerPos - pos;
			D3DXVec3Normalize(&target, &target);
			target.x *= 3.0f;
			target.y *= 3.0f;

			CBone::Create(pos, target);				//弾の生成
		}

		if (m_nShootDelay >= 410)
		{//410フレームが経ったら
			m_nShootDelay = 0;			//攻撃カウンターを0に戻す
			m_state = state_close;		//閉じる状態にする
		}
	}

		break;

	case CMaw::state_TripleShoot:

	{//攻撃(３つ)

		m_nShootDelay++;				//攻撃カウンターをインクリメントする

		if (m_nShootDelay % 100 == 5)
		{//50フレームごと１つの弾を生成する
			D3DXVECTOR3 pos, PlayerPos, target;

			//プレイヤーまでのベクトルを計算して、正規化して、弾の速度として使う。それに±30°向きの弾を生成する
			pos = GetPos();
			PlayerPos = CPlayer::GetPlayer()->GetPos();
			target = PlayerPos - pos;
			D3DXVec3Normalize(&target, &target);

			D3DXVECTOR3 unit = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

			float fAngle = acosf(D3DXVec3Dot(&target, &unit));

			if (PlayerPos.y < pos.y)
			{
				fAngle *= -1.0f;
			}

			//弾の生成
			CBone::Create(pos, D3DXVECTOR3(3.0f * target.x, 3.0f * target.y, 0.0f));

			D3DXVECTOR3 NewMove = D3DXVECTOR3(cosf(fAngle) * cosf(D3DX_PI / 6.0f) - sinf(fAngle) * sinf(D3DX_PI / 6.0f),
				sinf(fAngle) * cosf(D3DX_PI / 6.0f) + cosf(fAngle) * sinf(D3DX_PI / 6.0f), 0.0f);

			CBone::Create(pos, D3DXVECTOR3(3.0f * NewMove.x, 3.0f * NewMove.y, 0.0f));

			NewMove = D3DXVECTOR3(cosf(fAngle) * cosf(-D3DX_PI / 6.0f) - sinf(fAngle) * sinf(-D3DX_PI / 6.0f),
				sinf(fAngle) * cosf(-D3DX_PI / 6.0f) + cosf(fAngle) * sinf(-D3DX_PI / 6.0f), 0.0f);

			CBone::Create(pos, D3DXVECTOR3(3.0f * NewMove.x, 3.0f * NewMove.y, 0.0f));
		}

		if (m_nShootDelay >= 710)
		{//710フレームが経ったら
			m_nShootDelay = 0;			//攻撃カウンターを0に戻す
			m_state = state_close;		//閉じる状態にする
		}
	}

	break;

	case CMaw::state_RandomShoot:

	{//ランダムな攻撃

		m_nShootDelay++;				//攻撃カウンターをインクリメントする

		if (m_nShootDelay % 30 == 5)
		{//30フレームごと弾を生成する

			D3DXVECTOR3 pos, PlayerPos, target;

			//プレイヤーまでのベクトルを計算して、正規化して、±45°向きの弾を生成する
			//プレイヤーが動かないと当たらない可能性が高い。でも壁と当たったら、折れてから反射する
			pos = GetPos();
			PlayerPos = CPlayer::GetPlayer()->GetPos();
			target = PlayerPos - pos;
			D3DXVec3Normalize(&target, &target);

			D3DXVECTOR3 unit = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

			float fAngle = acosf(D3DXVec3Dot(&target, &unit));

			if (PlayerPos.y < pos.y)
			{
				fAngle *= -1.0f;
			}
			
			float fDiv = random(3000, 8000) * 0.001f;

			//弾の生成
			D3DXVECTOR3 NewMove = D3DXVECTOR3(cosf(fAngle) * cosf(D3DX_PI / fDiv) - sinf(fAngle) * sinf(D3DX_PI / fDiv),
				sinf(fAngle) * cosf(D3DX_PI / fDiv) + cosf(fAngle) * sinf(D3DX_PI / fDiv), 0.0f);

			CBone::Create(pos, D3DXVECTOR3(4.0f * NewMove.x, 4.0f * NewMove.y, 0.0f));

			NewMove = D3DXVECTOR3(cosf(fAngle) * cosf(-D3DX_PI / fDiv) - sinf(fAngle) * sinf(-D3DX_PI / fDiv),
				sinf(fAngle) * cosf(-D3DX_PI / fDiv) + cosf(fAngle) * sinf(-D3DX_PI / fDiv), 0.0f);

			CBone::Create(pos, D3DXVECTOR3(4.0f * NewMove.x, 4.0f * NewMove.y, 0.0f));
		}

		if (m_nShootDelay >= 410)
		{//410フレームが経ったら
			m_nShootDelay = 0;			//攻撃カウンターを0に戻す
			m_state = state_close;		//閉じる状態にする
		}
	}

	break;

	case CMaw::state_Spawn:

	{//召喚

		m_nShootDelay++;					//攻撃カウンターをインクリメントする

		if (m_nShootDelay % 35 == 5)
		{//35フレームごと敵一匹生成する
			CSkeleton::Create(GetPos());
		}

		if (m_nShootDelay >= 350)
		{//350フレームが経ったら
			m_nShootDelay = 0;			//攻撃カウンターを0に戻す
			m_state = state_close;		//閉じる状態にする
		}
	}

	break;

	case CMaw::state_close:

	{//閉じる状態

		m_nPhase++;				//カウンターをインクリメントする

		if (m_nPhase % 8 == 7)
		{//8フレームごとテクスチャパターンを更新する

			int anim = GetPresentAnimPattern();

			if (anim == 0)
			{//完全に閉じたら、普通の状態に戻す
				m_state = state_normal;
				m_nPhase = 0;
			}
			else
			{
				anim--;						//アニメーションパターンの更新
				SetAnimPattern(anim);		//アニメーションパターンの設定
			}
		}
	}

		break;

	default:
		break;
	}
}