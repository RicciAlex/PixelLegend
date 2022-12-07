//=============================================================================
//
// sloth.cpp
// Author : Ricci Alex
//
//=============================================================================

//インクルードファイル
#include "sloth.h"
#include "application.h"
#include "sound.h"
#include "tear.h"
#include "enemyCloud.h"
#include "Zbullet.h"
#include "player.h"
#include "squareHitbox.h"
#include "enemyLife.h"

//コンストラクタ
CSloth::CSloth()
{
	//メンバー変数をクリアする
	m_bEnd = false;
	m_nCntState = 0;
	m_fYCoord = 0.0f;
	m_state = state_Spawn;
	m_nCntDmg = 0;
	m_nCntSpawn = 0;
	m_nCntSound = 0;
	m_nSoundDelay = 0;
	m_nChange = 0;
	m_nCntAnim = 0;
	m_HitboxRelativePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pHitbox = nullptr;
	m_pLife = nullptr;
}

//デストラクタ
CSloth::~CSloth()
{

}

//初期化処理
HRESULT CSloth::Init(void)
{
	//基本クラスの初期化
	if (FAILED(CEnemy::Init()))
	{
		return -1;
	}

	//メンバー変数の初期化
	m_bEnd = false;
	SetLife(20000);
	m_state = state_Spawn;
	m_nCntState = 30;
	m_nCntDmg = 0;
	m_nCntSpawn = 0;
	m_nCntSound = 0;
	m_nSoundDelay = 0;
	m_nChange = 0;
	m_nCntAnim = 0;
	m_HitboxRelativePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pHitbox = nullptr;
	m_pLife = nullptr;

	return S_OK;
}

//終了処理
void CSloth::Uninit(void)
{
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}
	if (m_pLife != nullptr)
	{
		m_pLife->Release();
		m_pLife = nullptr;
	}

	//基本クラスの終了処理
	CEnemy::Uninit();
}

//更新処理
void CSloth::Update(void)
{
	SlothBehavior();					//更新処理

	if (m_pHitbox != nullptr)
	{
		m_pHitbox->SetPos(GetPos() + m_HitboxRelativePos);

		if (m_nCntDmg <= 0)
		{
			if (m_pHitbox->GetHitState())
			{
				m_pHitbox->SetHitState(false);
				int nLife = GetLife();
				int nDamage = CPlayer::GetPlayer()->GetAttack();
				nLife -= nDamage;
				m_nCntDmg = 20;

				if (nLife <= 0)
				{
					SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
					m_nSoundDelay = 45;
					m_state = state_Death;
					m_pHitbox->Release();
					m_pHitbox = nullptr;
					m_nChange++;
					SetAnimPattern(14);
					return;
				}

				if (nLife <= 15000 && m_nChange == 0)
				{
					SetTextureParameter(1, 6, 3, INT_MAX);
					SetAnimPattern(6);
					m_nChange++;

					CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_THUNDER);
				}
				else if (nLife <= 7500 && m_nChange == 1)
				{
					SetAnimPattern(12);
					m_nChange++;

					CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_THUNDER);
				}

				if (m_pLife != nullptr)
				{
					m_pLife->SubtractLife(nDamage);
				}

				SetLife(nLife);
			}
		}
		else
		{
			m_nCntDmg--;
		}
	}

	if (m_nChange == 1)
	{
		m_nCntAnim++;

		if (m_nCntAnim >= 30)
		{
			m_nCntAnim = 0;
			
			if (GetPresentAnimPattern() == 6)
			{
				SetAnimPattern(7);
			}
			else
			{
				SetAnimPattern(6);
			}
		}
	}
	else if (m_nChange == 2)
	{
		m_nCntAnim++;

		if (m_nCntAnim >= 30)
		{
			m_nCntAnim = 0;

			if (GetPresentAnimPattern() == 12)
			{
				SetAnimPattern(13);
			}
			else
			{
				SetAnimPattern(12);
			}
		}
	}
	else if (m_nChange == 3)
	{
		m_nCntAnim++;

		if (m_nCntAnim >= 30)
		{
			m_nCntAnim = 0;

			if (GetPresentAnimPattern() == 14)
			{
				SetAnimPattern(15);
			}
			else
			{
				SetAnimPattern(14);
			}
		}
	}

	CObject_2D::Update();				//基本クラスの更新処理
}

//描画処理
void CSloth::Draw(void)
{
	//基本クラスの描画処理
	CEnemy::Draw();
}

const bool CSloth::GetEnd(void)
{
	return m_bEnd;
}


//==================================================================================================
//										静的関数
//==================================================================================================

//生成処理
CSloth* CSloth::Create(void)
{
	CSloth* pBoss = new CSloth;					//メモリを確保する

	//初期化処理
	if (FAILED(pBoss->Init()))
	{
		return nullptr;
	}

	pBoss->SetPos(D3DXVECTOR3((float)SCREEN_WIDTH * 0.75f, (float)SCREEN_HEIGHT * 0.25f, 0.0f));		//位置の設定
	pBoss->SetSize(D3DXVECTOR2(180.0f, 104.0f));													//サイズの設定
	pBoss->SetStartingRot(D3DX_PI * 0.5f);															//回転角度の設定
	pBoss->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));													//速度の設定
	pBoss->m_fYCoord = pBoss->GetPos().y;															//Y座標を保存する
	pBoss->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
																									
	pBoss->SetTexture(CObject::TextureSloth);														//テクスチャの設定
	pBoss->SetTextureParameter(2, 6, 3, 30);														//テクスチャパラメータの設定

	D3DXVECTOR3 pos = pBoss->GetPos();

	pBoss->m_HitboxRelativePos = D3DXVECTOR3(30.0f, 0.0f, 0.0f);

	pBoss->m_pHitbox = CSquareHitbox::Create(D3DXVECTOR3(pos.x + pBoss->m_HitboxRelativePos.x, pos.y, 0.0f), D3DXVECTOR2(100.0f, 80.0f), CHitbox::Type_Enemy);

	pBoss->m_pLife = CEnemyLife::Create(D3DXVECTOR3(900.0f, 40.0f, 0.0f), D3DXCOLOR(0.0f, 0.4f, 1.0f, 0.5f), 20000, "sloth");

	return pBoss;								//敵を返す
}



//==================================================================================================
//										プライベート関数 
//==================================================================================================

//更新処理
void CSloth::SlothBehavior(void)
{
	switch (m_state)
	{
	case CSloth::state_Spawn:

	{
		D3DXCOLOR col = GetColor();

		col.a += 0.005f;

		if (col.a >= 1.0f)
		{
			col.a = 1.0f;
			m_state = state_Normal;
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_GOAT);
		}

		SetColor(col);
	}

	break;

	case CSloth::state_Normal:

		if (m_nCntState > 0)
		{
			m_nCntState--;

			if (m_nCntState <= 0)
			{
				m_nCntState = 0;
			}

			int nState = random(300, 799);

			nState /= 100;

			switch (nState)
			{
			case state_Charge:

				m_state = state_Charge;

				m_nSoundDelay = 120;

				SetMove(D3DXVECTOR3(-5.0f, 0.0f, 0.0f));

				break;

			case state_Snore:

				m_state = state_Snore;

				SetMove(D3DXVECTOR3(-2.0f, 0.0f, 0.0f));

				m_nSoundDelay = 150;

				break;

			case state_Weep:

				m_state = state_Weep;

				SetMove(D3DXVECTOR3(-4.0f, 0.0f, 0.0f));

				m_nSoundDelay = 60;

				break;

			case state_Cry:

				m_state = state_Cry;

				SetMove(D3DXVECTOR3(-4.0f, 0.0f, 0.0f));

				m_nSoundDelay = 60;

				break;

			case state_Summon:

				m_state = state_Summon;

				SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

				m_nSoundDelay = 240;

				break;


			default:
				break;
			}
		}

		break;

	case state_Return:

	{
		D3DXVECTOR3 pos = GetPos();

		if (pos.x <= (float)SCREEN_WIDTH * 0.75f)
		{
			m_nCntState = 30;
			m_state = state_Normal;
			m_fYCoord = GetPos().y;
			m_nCntMove = 0;
			m_fAngleMove = 0.0f;
		}
	}

	break;


	case CSloth::state_Charge:

	{
		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 move = GetMove();
		m_fAngleMove += D3DX_PI * 0.0125f;

		pos.x += move.x;
		pos.y = m_fYCoord + 130.0f * sqrtf(cosf(m_fAngleMove) * cosf(m_fAngleMove));

		if (pos.x <= -1.0f * GetSize().x)
		{
			pos.x = -1.0f * GetSize().x;
			pos.y = (float)random(150, 570);
			m_fYCoord = pos.y;
			move.x *= -1.0f;
			FlipX();
			m_HitboxRelativePos.x *= -1.0f;
			m_nPhase++;
		}
		else if (pos.x >= (float)SCREEN_WIDTH + GetSize().x)
		{
			pos.x = (float)SCREEN_WIDTH + GetSize().x;
			pos.y = (float)random(150, 570);
			m_fYCoord = pos.y;
			move.x *= -1.0f;
			FlipX();
			m_HitboxRelativePos.x *= -1.0f;
			m_nPhase++;
		}

		if (m_nPhase >= 4)
		{
			pos = D3DXVECTOR3((float)SCREEN_WIDTH * 1.25f, (float)SCREEN_HEIGHT * 0.25f, 0.0f);
			move = D3DXVECTOR3(-2.0f, 0.0f, 0.0f);
			m_state = state_Return;
			m_nPhase = 0;
		}

		SetPos(pos);
		SetMove(move);
		m_nCntSound++;
	}

	break;

	case CSloth::state_Snore:

	{
		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 move = GetMove();

		pos += move;

		if (pos.x <= -1.0f * GetSize().x)
		{
			pos.x = -1.0f * GetSize().x;
			move.x *= -1.0f;
			FlipX();
			m_HitboxRelativePos.x *= -1.0f;
			m_nPhase++;
		}
		else if (pos.x >= (float)SCREEN_WIDTH + GetSize().x)
		{
			pos.x = (float)SCREEN_WIDTH + GetSize().x;
			move.x *= -1.0f;
			FlipX();
			m_HitboxRelativePos.x *= -1.0f;
			m_nPhase++;
		}

		if (pos.x >= 10.0f && pos.x <= (float)SCREEN_WIDTH - 10.0f)
		{
			m_nShootDelay++;

			if (m_nShootDelay >= 60)
			{
				D3DXVECTOR3 PlayerPos = CPlayer::GetPlayer()->GetPos();
				D3DXVECTOR3 BulletMove = PlayerPos - pos;
				D3DXVec3Normalize(&BulletMove, &BulletMove);

				{
					CZBullet* pBullet = CZBullet::Create(pos, D3DXVECTOR3(BulletMove.x * 5.0f, BulletMove.y * 5.0f, 0.0f));
				}

				for (int nCnt = 0; nCnt < 2; nCnt++)
				{
					D3DXVECTOR3 dir = D3DXVECTOR3((float)random(-1000, 1000) * 0.001f, (float)random(-1000, 1000) * 0.001f, 0.0f);
					dir += BulletMove;
					D3DXVec3Normalize(&dir, &dir);
					CZBullet* pBullet = CZBullet::Create(pos, D3DXVECTOR3(dir.x * 5.0f, dir.y * 5.0f, 0.0f));
				}

				m_nShootDelay = 0;
			}
		}

		if (m_nPhase >= 4)
		{
			pos = D3DXVECTOR3((float)SCREEN_WIDTH * 1.25f, (float)SCREEN_HEIGHT * 0.25f, 0.0f);
			move = D3DXVECTOR3(-2.0f, 0.0f, 0.0f);
			m_state = state_Return;
			m_nPhase = 0;
		}

		SetPos(pos);
		SetMove(move);
		m_nCntSound++;
	}

	break;

	case CSloth::state_Weep:

	{
		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 move = GetMove();

		pos.x += move.x;

		if (pos.x <= -1.0f * GetSize().x)
		{
			pos.x = -1.0f * GetSize().x;
			move.x *= -1.0f;
			FlipX();
			m_HitboxRelativePos.x *= -1.0f;
			m_nPhase++;
		}
		else if (pos.x >= (float)SCREEN_WIDTH + GetSize().x)
		{
			pos.x = (float)SCREEN_WIDTH + GetSize().x;
			move.x *= -1.0f;
			FlipX();
			m_HitboxRelativePos.x *= -1.0f;
			m_nPhase++;
		}

		if (pos.x >= 50.0f && pos.x <= (float)SCREEN_WIDTH - 50.0f)
		{
			m_nShootDelay++;

			if (m_nShootDelay >= 10)
			{
				for (int nCnt = 0; nCnt < 2; nCnt++)
				{
					int rand = random(0, 1);

					D3DXVECTOR3 dir = D3DXVECTOR3((float)random(5, 30) * 0.1f, (float)random(40, 70) * -0.1f, 0.0f);

					if (rand == 0)
					{
						dir.x *= -1.0f;
					}

					CTearBullet* pBullet = CTearBullet::Create(D3DXVECTOR3(pos.x + ((float)abs((int)move.x) / move.x) * 150.0f, pos.y - 50.0f, 0.0f), dir);
				}

				m_nShootDelay = 0;
			}
		}

		if (m_nPhase >= 4)
		{
			pos = D3DXVECTOR3((float)SCREEN_WIDTH * 1.25f, (float)SCREEN_HEIGHT * 0.25f, 0.0f);
			move = D3DXVECTOR3(-2.0f, 0.0f, 0.0f);
			m_state = state_Return;
			m_nPhase = 0;
		}

		SetPos(pos);
		SetMove(move);
		m_nCntSound++;
	}

	break;

	case CSloth::state_Cry:

	{
		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 move = GetMove();

		pos.x += move.x;

		if (pos.x <= -1.0f * GetSize().x)
		{
			pos.x = -1.0f * GetSize().x;
			move.x *= -1.0f;
			FlipX();
			m_HitboxRelativePos.x *= -1.0f;
			m_nPhase++;
		}
		else if (pos.x >= (float)SCREEN_WIDTH + GetSize().x)
		{
			pos.x = (float)SCREEN_WIDTH + GetSize().x;
			move.x *= -1.0f;
			FlipX();
			m_HitboxRelativePos.x *= -1.0f;
			m_nPhase++;
		}

		if (pos.x >= 50.0f && pos.x <= (float)SCREEN_WIDTH - 50.0f)
		{
			m_nShootDelay++;

			if (m_nShootDelay >= 30)
			{
				for (int nCnt = 0; nCnt < 6; nCnt++)
				{
					int rand = random(0, 1);

					D3DXVECTOR3 dir = D3DXVECTOR3((float)random(5, 30) * 0.1f, (float)random(40, 70) * -0.1f, 0.0f);

					if (rand == 0)
					{
						dir.x *= -1.0f;
					}

					CTearBullet* pBullet = CTearBullet::Create(D3DXVECTOR3(pos.x + ((float)abs((int)move.x) / move.x) * 150.0f, pos.y - 50.0f, 0.0f), dir);
				}

				m_nShootDelay = 0;
			}
		}

		if (m_nPhase >= 4)
		{
			pos = D3DXVECTOR3((float)SCREEN_WIDTH * 1.25f, (float)SCREEN_HEIGHT * 0.25f, 0.0f);
			move = D3DXVECTOR3(-2.0f, 0.0f, 0.0f);
			m_state = state_Return;
			m_nPhase = 0;
		}

		SetPos(pos);
		SetMove(move);
		m_nCntSound++;
	}

	break;

	case CSloth::state_Summon:

	{
		SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		D3DXVECTOR3 pos = GetPos();
		m_fAngleMove += D3DX_PI * 0.025f;
		pos.y = m_fYCoord + cosf(m_fAngleMove) * 50.0f;

		m_nShootDelay++;

		if (m_nShootDelay % 30 == 29)
		{
			CEnemyCloud* pEnemy = CEnemyCloud::Create(pos);
		}

		if (m_nShootDelay >= 610)
		{
			m_state = state_Normal;
		}
		m_nCntSound++;
	}

	break;


	case CSloth::state_Death:

	{
		D3DXCOLOR col = GetColor();
		D3DXVECTOR3 pos = GetPos();

		if (col.a > 0.0f)
		{
			m_nCntSound++;
			col.a -= 0.005f;
			SetColor(col);
			m_nShootDelay++;

			if (m_nShootDelay >= 15)
			{
				for (int nCnt = 0; nCnt < 6; nCnt++)
				{
					int rand = random(0, 1);

					D3DXVECTOR3 dir = D3DXVECTOR3((float)random(5, 30) * 0.1f, (float)random(40, 70) * -0.1f, 0.0f);

					if (rand == 0)
					{
						dir.x *= -1.0f;
					}

					float fDir = 1.0f;

					if (!GetFlipX())
					{
						fDir = -1.0f;
					}

					CTearBullet* pBullet = CTearBullet::Create(D3DXVECTOR3(pos.x + (115.0f * fDir), pos.y - 50.0f, 0.0f), dir);
				}

				m_nShootDelay = 0;
			}
		}
		else
		{
			m_bEnd = true;
		}
	}

	break;

	default:
		break;
	}

	switch (m_nChange)
	{
	case 1:

	{
		m_nCntSpawn++;

		if (m_nCntSpawn >= 120)
		{
			m_nCntSpawn = 0;

			CEnemyCloud::Create(GetPos());
		}
	}

		break;

	case 2:

	{
		m_nCntSpawn++;

		if (m_nCntSpawn >= 60)
		{
			m_nCntSpawn = 0;

			CEnemyCloud::Create(GetPos());
		}
	}

		break;

	default:
		break;
	}

	if (m_nCntSound >= m_nSoundDelay)
	{
		CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_GOAT);
		m_nCntSound = 0;
	}
}