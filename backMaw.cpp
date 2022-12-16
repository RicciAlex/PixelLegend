//=============================================================================
//
// backMaw.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "backMaw.h"
#include "squareHitbox.h"
#include "application.h"
#include "sound.h"
#include "bone.h"
#include "player.h"

//=============================================================================
//							静的変数の初期化
//=============================================================================
const D3DXVECTOR2 CBackMaw::m_BackMawSize = D3DXVECTOR2(100.0f, 90.0f);			//ヒットボックスのサイズ

//コンストラクタ
CBackMaw::CBackMaw()
{
	//メンバー変数をクリアする
	m_target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_state = state_sleep;

	m_pHitbox = nullptr;
}

//デストラクタ
CBackMaw::~CBackMaw()
{

}

//初期化処理
HRESULT CBackMaw::Init(void)
{
	if (FAILED(CEnemy::Init()))
	{//基本クラスの初期化処理
		return -1;
	}

	//メンバー変数を初期化する
	m_target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_state = state_sleep;

	m_pHitbox = nullptr;

	return S_OK;
}

//終了処理
void CBackMaw::Uninit(void)
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
void CBackMaw::Update(void)
{
	//基本クラスの更新処理
	CObject_2D::Update();

	//状態によっての更新処理
	UpdateState();		
}

//描画処理
void CBackMaw::Draw(void)
{
	//基本クラスの描画処理
	CObject_2D::Draw();
}

//状態の設定処理
void CBackMaw::SetState(CBackMaw::state state)
{
	if (m_state == state_sleep)
	{//現在の状態は寝る状態だったら

		m_fAngleMove = 0;				//移動用の角度を0に戻す

		m_state = state;				//状態の設定
	}
}



//=============================================================================
//
//								静的関数
//
//=============================================================================



//生成処理
CBackMaw* CBackMaw::Create(void)
{
	CBackMaw* pEnemy = new CBackMaw;			//インスタンスを生成する

	if (FAILED(pEnemy->Init()))
	{//初期化処理
		return nullptr;
	}

	pEnemy->SetPos(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f));	//位置の設定
	pEnemy->SetSize(m_BackMawSize);																//サイズの設定
	pEnemy->SetStartingRot(D3DX_PI * 0.5f);														//向きの初期値の設定
	pEnemy->SetTexture(CObject::TextureGluttonyBackMaw);										//テクスチャの設定
	pEnemy->SetTextureParameter(1, 2, 2, INT_MAX);												//テクスチャパラメータの設定
	pEnemy->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));										//色の設定
	pEnemy->SetPriority(2);																		//プライオリティの設定
																								
	return pEnemy;							//生成したインスタンスを返す
}



//=============================================================================
//
//							プライベート関数
//
//=============================================================================



//状態の更新処理
void CBackMaw::UpdateState(void)
{
	D3DXVECTOR3 pos = GetPos();				//位置の取得

	switch (m_state)
	{
	case CBackMaw::state_sleep:

	{//寝る状態

		//上下に移動させる
		m_fAngleMove += D3DX_PI * 0.01f;

		pos.y += sinf(m_fAngleMove) * -0.1f;
		SetPos(pos);
	}

		break;

	case CBackMaw::state_roar:

	{//鳴き声を出す

		m_nCntMove++;				//移動カウンターをインクリメントする

		if (m_nPhase == 0)
		{//口を開く

			if (m_nCntMove >= 4)
			{//4フレームごと

				//アニメーションパターンを取得して、更新する。
				int anim = GetPresentAnimPattern();
				anim++;
				m_nCntMove = 0;							//アニメーションカウンターを元に戻す

				if (anim >= 4)
				{//完全に開いたら

					m_nPhase++;
					CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_GLUTTONY_ROAR);		//鳴き声のサウンドを再生する
				}
				else
				{//まだ完全に開いていない場合

					SetAnimPattern(anim);				//アニメーションパラメータの設定
				}
			}
		}
		else if (m_nPhase == 1)
		{//しばらく動かない

			if (m_nCntMove >= 180)
			{//180フレームが経ったら
				m_nPhase++;
				m_nCntMove = 0;
			}
		}
		else if (m_nPhase == 2)
		{//閉じるアニメーションをする

			if (m_nCntMove >= 4)
			{//4フレームごと

			 //アニメーションパターンを取得して、更新する。
				int anim = GetPresentAnimPattern();
				anim--;
				m_nCntMove = 0;					//アニメーションカウンターを元に戻す

				if (anim <= 0)
				{//完全に閉じたら、次の攻撃を設定する
					anim = 0;
					m_nPhase = 0;

					switch (random(0, 1))
					{
					case 0:

					{
						m_state = state_shoot;			//弾を発生する
					}

						break;

					case 1:

					{
						m_state = state_bite;			//プレイヤーを追いついて、嚙んでみる
					}

						break;

					default:
						break;
					}
				}
				else
				{//まだ閉じていない場合
					SetAnimPattern(anim);				//アニメーションパラメータの設定
				}
			}
		}
	}
	

		break;

	case CBackMaw::state_shoot:

	{//弾の発生攻撃

		if (m_nPhase == 0)
		{//開くアニメーション

			m_nCntMove++;		//カウンターをインクリメントする

			if (m_nCntMove >= 3)
			{//3フレームごと

			 //アニメーションパターンを取得して、更新する。
				int anim = GetPresentAnimPattern();
				anim++;
				m_nCntMove = 0;					//アニメーションカウンターを元に戻す

				if (anim >= 4)
				{//完全に開いたら
					m_nPhase++;					//弾の発生に進む
				}
				else
				{//まだ完全に開いていない場合
					SetAnimPattern(anim);				//アニメーションパラメータの設定
				}
			}
		}
		else if (m_nPhase == 1)
		{//弾の発生

			m_nShootDelay++;				//攻撃カウンターをインクリメントする

			if (m_nShootDelay % 120 == 5)
			{//120フレームごと弾を発生する

				int nRand = random(4, 10);				//4～10の間ランダムで弾の個数を設定する

				for (int nCnt = 0; nCnt < nRand; nCnt++)
				{
					//弾の生成
					CBone::Create(GetPos(), D3DXVECTOR3(2.0f * cosf((2.0f * D3DX_PI * nCnt) / nRand), 2.0f * sinf((2.0f * D3DX_PI * nCnt) / nRand), 0.0f));
				}

				if (m_nShootDelay >= 500)
				{//500フレームが経ったら
					m_nShootDelay = 0;			//攻撃カウンターを0に戻す
					m_nPhase++;					//閉じるアニメーションに進む
				}
			}
		}
		else if (m_nPhase == 2)
		{//閉じるアニメーション

			m_nCntMove++;				//移動カウンターをインクリメントする

			if (m_nCntMove >= 3)
			{//3フレームごと

				//アニメーションパターンを取得して、更新する。
				int anim = GetPresentAnimPattern();
				anim--;
				m_nCntMove = 0;				//アニメーションカウンターを元に戻す

				if (anim <= 0)
				{//完全に閉じたら
					anim = 0;					//アニメーションパターンの設定
					m_nPhase = 0;				//カウンターを0に戻す
					m_state = state_return;		//戻る状態にする
				}
				else
				{//まだ完全に閉じていない場合
					SetAnimPattern(anim);		//アニメーションパターンの設定
				}
			}
		}
		else
		{//エラーが起きたら、カウンターを0に戻す
			m_nPhase = 0;
		}
	}

		break;

	case CBackMaw::state_bite:

	{//嚙む攻撃

		if (m_nPhase == 0)
		{//開くアニメーション

			m_nCntMove++;				//移動カウンターをインクリメントする

			if (m_nCntMove >= 3)
			{//3フレームごと

			 //アニメーションパターンを取得して、更新する。
				int anim = GetPresentAnimPattern();
				anim++;
				m_nCntMove = 0;			//アニメーションカウンターを元に戻す

				if (anim >= 4)
				{//完全に開いたら
					m_nPhase++;			//攻撃開始に進む
				}
				else
				{//まだ完全に開いていない場合
					SetAnimPattern(anim);			//アニメーションパターンの設定
				}
			}
		}
		else if (m_nPhase == 1)
		{//攻撃開始

			//目的の位置をプレイヤーの位置に設定して、計算してから速度を設定する
			D3DXVECTOR3 PlayerPos = CPlayer::GetPlayer()->GetPos();
			D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			move = PlayerPos - pos;
			D3DXVec3Normalize(&move, &move);
			move.x *= 7.0f;
			move.y *= 7.0f;
			SetMove(move);
			m_target = PlayerPos;
			m_nPhase++;
		}
		else if (m_nPhase == 2)
		{//移動

			//目的の位置までのベクトルを計算して、距離を計算する
			D3DXVECTOR3 distance = m_target - pos;
			float lenght = D3DXVec3Length(&distance);

			if (lenght <= 8.0f)
			{//目的の位置までの距離が8.0以下だったら

				SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//速度の設定
				m_nPhase++;									//ダメージを与える状態に進む

				//ヒットボックスの生成
				if (m_pHitbox == nullptr)
				{//ポインタはnullだったら
					m_pHitbox = CSquareHitbox::Create(pos, D3DXVECTOR2(85.0f, 40.0f), CHitbox::Type_Enemy);
				}
			}
		}
		else if (m_nPhase == 3)
		{//ダメージを与える状態

			m_nCntMove++;				//移動カウンターをインクリメントする

			if (m_nCntMove >= 3)
			{//3フレームごと

			 //アニメーションパターンを取得して、更新する
				int anim = GetPresentAnimPattern();
				anim--;
				m_nCntMove = 0;				//アニメーションカウンターを元に戻す

				if (anim <= 0)
				{//完全に閉じたら

					CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_BITE);	//サウンドを再生する
					anim = 0;						//アニメーションパターンの設定
					m_pHitbox->Release();			//ヒットボックスの破棄
					m_pHitbox = nullptr;			//ヒットボックスへのポインタをnullにする
					m_nShootDelay++;				//攻撃カウンターをインクリメントする

					if (m_nShootDelay >= 6)
					{//6フレームが経ったら
						m_nShootDelay = 0;			//攻撃カウンターを0に戻す
						m_nPhase++;					//カウンターを0に戻す
					}
					else
					{
						m_nPhase = 0;
					}
				}
				else
				{//まだ閉じていない場合
					SetAnimPattern(anim);			//アニメーションパターンの設定
				}
			}
		}
		else if (m_nPhase == 4)
		{//元に戻す

			D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//速度の設定
			m_target = D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f);			//目的の位置として画面の真ん中を設定する

			//速度を設定して、設定する
			move = m_target - pos;						
			D3DXVec3Normalize(&move, &move);			
			move.x *= 8.0f;								
			move.y *= 8.0f;								
			SetMove(move);								
			m_nPhase++;									
		}
		else if (m_nPhase == 5)
		{//元の位置に着いたら

			//目的の位置までの距離を計算する
			D3DXVECTOR3 distance = m_target - pos;
			float lenght = D3DXVec3Length(&distance);

			if (lenght <= 8.0f)
			{//元の位置に着いたら、戻る状態にする
				SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				m_nPhase = 0;
				m_state = state_return;
			}
		}
		

	}

		break;

	case CBackMaw::state_awake:

	{//起きる状態

		D3DXCOLOR col = GetColor();		//色の取得

		//明るくする
		col.r += 0.01f;
		col.g += 0.01f;
		col.b += 0.01f;

		if (col.r >= 1.0f)
		{//色がホワイトになったら、
			m_state = state_roar;		//鳴き声を出す状態にする
		}
		else
		{//まだ終わっていなかったら
			SetColor(col);				//色の設定処理
		}
	}

		break;

	case CBackMaw::state_return:

	{//戻る状態

		D3DXCOLOR col = GetColor();		//色の取得

		//暗くする
		col.r -= 0.01f;
		col.g -= 0.01f;
		col.b -= 0.01f;

		if (col.r <= 0.5f)
		{//暗くなったら
			m_state = state_sleep;		//寝る状態にする
		}
		else
		{//まだ途中だったら
			SetColor(col);				//色の設定
		}
	}

		break;


	case CBackMaw::state_wait:

	{//待機状態

		m_nCntMove++;			//移動カウンターをインクリメントする

		if (m_nCntMove >= 600)
		{//600フレームが経ったら

			m_nCntMove = 0;			//移動カウンターを0に戻す
			m_state = state_awake;	//起きる状態にする
		}
	}

	break;

	default:
		break;
	}
}