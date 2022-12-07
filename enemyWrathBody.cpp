//=============================================================================
//
// enemyWrathBody.cpp
// Author : Ricci Alex
//
//=============================================================================

//インクルードファイル
#include "enemyWrathBody.h"
#include "circleHitbox.h"
#include "squareHitbox.h"
#include "application.h"
#include "sound.h"
#include "skullFireball.h"
#include "player.h"
#include "wrath.h"


//コンストラクタ
CWrathBody::CWrathBody()
{
	m_nCntShoot = 0;
	m_nCntState = 0;
	m_state = state_spawn;

	m_pHitbox = nullptr;
	m_pHeadHitbox = nullptr;
	m_bDead = false;
	m_bBound = false;
	m_pArm = nullptr;
	m_pParent = nullptr;

	m_posArm =D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posBodyHitbox = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posHeadHitbox = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_targetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//デストラクタ
CWrathBody::~CWrathBody()
{

}

//初期化処理
HRESULT CWrathBody::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CEnemy::Init()))
	{
		return -1;
	}

	m_nCntShoot = 0;
	m_nCntState = 0;
	m_state = state_spawn;

	m_pHitbox = nullptr;
	m_pHeadHitbox = nullptr;
	m_bDead = false;
	m_bBound = true;
	m_pArm = nullptr;
	m_pParent = nullptr;

	m_posArm = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posBodyHitbox = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posHeadHitbox = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_targetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//CHandCharger::Create(D3DXVECTOR3(500.0f, -100.0f, 0.0f));

	/*CHandGun::Create(D3DXVECTOR3(-200.0f, 400.0f, 0.0f), D3DXVECTOR3(2.0f, 0.0f, 0.0f));
	CHandFlamethrower::Create(D3DXVECTOR3((float)SCREEN_WIDTH + 200.0f, 200.0f, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f));*/

	/*CSkullFireball* pBullet = CSkullFireball::Create(D3DXVECTOR3(1000.0f, 310.0f, 0.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f));
	pBullet->SetRevolution(D3DXVECTOR3(1000.0f, 360.0f, 0.0f), D3DX_PI * 0.05f, 40.0f);
	pBullet = CSkullFireball::Create(D3DXVECTOR3(1000.0f, 410.0f, 0.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f));
	pBullet->SetRevolution(D3DXVECTOR3(1000.0f, 360.0f, 0.0f), D3DX_PI * 0.05f, 40.0f);
	pBullet->SetPresentRevolutionAngle(D3DX_PI);

	pBullet = CSkullFireball::Create(D3DXVECTOR3(1000.0f, 260.0f, 0.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f));
	pBullet->SetRevolution(D3DXVECTOR3(1000.0f, 360.0f, 0.0f), D3DX_PI * 0.05f, 90.0f);
	pBullet = CSkullFireball::Create(D3DXVECTOR3(1000.0f, 460.0f, 0.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f));
	pBullet->SetRevolution(D3DXVECTOR3(1000.0f, 360.0f, 0.0f), D3DX_PI * 0.05f, 90.0f);
	pBullet->SetPresentRevolutionAngle(D3DX_PI);*/

	return S_OK;
}

//終了処理
void CWrathBody::Uninit(void)
{
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}
	if (m_pHeadHitbox != nullptr)
	{
		m_pHeadHitbox->Release();
		m_pHeadHitbox = nullptr;
	}

	if (m_pArm != nullptr)
	{
		m_pArm->Release();
		m_pArm = nullptr;
	}

	if (m_pParent != nullptr)
	{
		m_pParent = nullptr;
	}

	//基本クラスの終了処理
	CEnemy::Uninit();
}
//更新処理
void CWrathBody::Update(void)
{
	UpdateState();

	CObject_2D::Update();

	D3DXVECTOR3 pos = GetPos();

	if (m_pHitbox != nullptr)
	{
		m_pHitbox->SetPos(pos + m_posBodyHitbox);

		if (m_pHitbox->GetHitState())
		{
			m_pHitbox->SetHitState(false);

			int nDamage = CPlayer::GetPlayer()->GetAttack();

			int nLife = GetLife() - nDamage;

			if (m_pParent != nullptr)
			{
				m_pParent->Damage(nDamage);
			}

			if (nLife <= 0)
			{
				m_pHitbox->Release();
				m_pHitbox = nullptr;

				if (m_pHeadHitbox != nullptr)
				{
					m_pHeadHitbox->Release();
					m_pHeadHitbox = nullptr;
				}

				SetMove(D3DXVECTOR3(4.0f, -10.0f, 0.0f));
				SetAcceleration(D3DXVECTOR3(0.0f, 0.5f, 0.0f));
				SetAnimPattern(4);
				m_nPhase = 0;
				m_bBound = false;
				m_state = state_death;
				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_WRATH_DEATH);

				return;
			}
			
			SetLife(nLife);
		}
	}
	if (m_pHeadHitbox != nullptr)
	{
		m_pHeadHitbox->SetPos(pos + m_posHeadHitbox);

		if (m_pHeadHitbox->GetHitState())
		{
			m_pHeadHitbox->SetHitState(false);

			int nDamage = CPlayer::GetPlayer()->GetAttack();

			int nLife = GetLife() - nDamage;

			if (m_pParent != nullptr)
			{
				m_pParent->Damage(nDamage);
			}

			if (nLife <= 0)
			{
				m_pHeadHitbox->Release();
				m_pHeadHitbox = nullptr;

				if (m_pHitbox != nullptr)
				{
					m_pHitbox->Release();
					m_pHitbox = nullptr;
				}

				SetMove(D3DXVECTOR3(4.0f, -13.0f, 0.0f));
				SetAcceleration(D3DXVECTOR3(0.0f, 0.5f, 0.0f));
				SetAnimPattern(4);
				m_nPhase = 0;
				m_bBound = false;
				m_state = state_death;
				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_WRATH_DEATH);

				return;
			}

			SetLife(nLife);
		}
	}
	if (m_pArm != nullptr && m_bBound)
	{
		m_pArm->SetPos(pos + m_posArm);
	}
}

//描画処理
void CWrathBody::Draw(void)
{
	//基本クラスの描画処理
	CEnemy::Draw();
}

void CWrathBody::SetParent(CWrath* pParent)
{
	m_pParent = pParent;
}

const bool CWrathBody::GetDeath(void)
{
	return m_bDead;
}

//==========================================================================================================
//
//											静的関数
//
//==========================================================================================================


//生成処理
CWrathBody* CWrathBody::Create(D3DXVECTOR3 pos)
{
	CWrathBody* pEnemy = new CWrathBody;			//新しい敵を生成する

		//初期化処理
	if (FAILED(pEnemy->Init()))
	{
		return nullptr;					//nullを返す
	}

	pEnemy->SetPos(pos);
	pEnemy->SetObjType(CObject::OBJTYPE_ENEMY);					//オブジェクトの種類の設定
	pEnemy->SetStartingRot(D3DX_PI * 0.5f);							//回転角度の初期値の設定
	pEnemy->m_nCntMove = 0;										//カウンタの設定
	pEnemy->m_nShootDelay = 0;									//カウンタの設定
	pEnemy->SetTextureParameter(1, 2, 3, INT_MAX);				//テクスチャパラメータの設定
	pEnemy->SetSize(D3DXVECTOR2(120.0f, 241.0f));				//サイズの設定

	pEnemy->SetMove(D3DXVECTOR3(-2.0f, 0.0f, 0.0f));				//速度の設定
	pEnemy->SetAcceleration(D3DXVECTOR3(0.0f, 0.0f, 0.0f));		//加速の設定
	pEnemy->SetSubtype(ENEMYTYPE_WRATH_BODY);					//敵の種類の設定
	pEnemy->SetLife(15000);

	pEnemy->SetTexture(TextureWrath);						//テクスチャの設定

	pEnemy->m_posBodyHitbox = D3DXVECTOR3(0.0f, 135.0f, 0.0f);
	pEnemy->m_posHeadHitbox = D3DXVECTOR3(5.0f, -85.0f, 0.0f);

	pEnemy->m_pHitbox = CSquareHitbox::Create(pos + pEnemy->m_posBodyHitbox, D3DXVECTOR2(60.0f, 85.0f), CHitbox::Type_Enemy);
	pEnemy->m_pHeadHitbox = CCircleHitbox::Create(pos + pEnemy->m_posHeadHitbox, 100.0f, CHitbox::Type_Enemy);

	pEnemy->m_posArm = D3DXVECTOR3(0.0f, 250.0f, 0.0f);

	pEnemy->m_pArm = CObject_2D::Create();
	pEnemy->m_pArm->SetPos(pos + pEnemy->m_posArm);
	pEnemy->m_pArm->SetSize(D3DXVECTOR2(126.0f, 193.5));
	pEnemy->m_pArm->SetTexture(CObject::TextureHand);
	pEnemy->m_pArm->SetTextureParameter(1, 4, 1, INT_MAX);
	pEnemy->m_pArm->SetPriority(2);
	pEnemy->m_pArm->SetStartingRot(D3DX_PI * 0.5f);

	return pEnemy;				//生成されたインスタンスへのポンタを返す
}



void CWrathBody::UpdateState(void)
{
	D3DXVECTOR3 pos = GetPos();

	switch (m_state)
	{
	case CWrathBody::state_spawn:

	{
		pos.y += 0.5f * sinf(m_fAngleMove);
		m_fAngleMove += D3DX_PI * 0.01f;

		if (pos.x <= 950.0f)
		{
			m_state = state_normal;
			SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}

		SetPos(pos);
	}

		break;
	case CWrathBody::state_normal:

	{
		pos.y += 0.5f * sinf(m_fAngleMove);
		m_fAngleMove += D3DX_PI * 0.01f;

		SetPos(pos);

		m_nCntState++;

		if (m_nCntState >= 90)
		{
			m_nCntState = 0;

			int nSelect = CObject::random(CWrathBody::state_flamethrower, CWrathBody::state_swirl);

			switch (nSelect)
			{
			case state_flamethrower:

			{
				m_state = state_flamethrower;
				SetAnimPattern(1);
			}

				break;

			case state_rage:

			{
				m_state = state_rage;
				SetAnimPattern(1);
				SetMove(D3DXVECTOR3(2.0f, 0.0f, 0.0f));
			}

				break;

			case state_swirl:

			{
				m_state = state_swirl;
			}

				break;

			default:
				break;
			}

			/*m_state = state_flamethrower;
			SetAnimPattern(1);*/

			/*m_state = state_rage;
			SetAnimPattern(1);
			SetMove(D3DXVECTOR3(2.0f, 0.0f, 0.0f));*/

			//m_state = state_charge;

			//m_state = (CWrathBody::state)CObject::random(CWrathBody::state_flamethrower, CWrathBody::state_charge);
		}
	}

		break;

	case CWrathBody::state_flamethrower:

	{
		m_nShootDelay++;

		if (m_nShootDelay >= 50)
		{
			if (m_nShootDelay % 20 == 19)
			{
				if (GetPresentAnimPattern() == 2)
				{
					SetAnimPattern(3);
				}
				else
				{
					SetAnimPattern(2);
				}
			}

			if (m_nShootDelay % 20 == 19)
			{
				D3DXVECTOR3 playerPos = CPlayer::GetPlayer()->GetPos();
				D3DXVECTOR3 move = playerPos - pos;
				D3DXVec3Normalize(&move, &move);

				CSkullFireball::Create(pos, D3DXVECTOR3(move.x * 3.0f, move.y * 3.0f, 0.0f));


				D3DXVECTOR3 unit = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

				float fAngle = acosf(D3DXVec3Dot(&move, &unit));

				if (playerPos.y < pos.y)
				{
					fAngle *= -1.0f;
				}

				if (m_nPhase > 0)
				{
					D3DXVECTOR3 NewMove = D3DXVECTOR3(cosf(fAngle) * cosf(D3DX_PI / 12.0f) - sinf(fAngle) * sinf(D3DX_PI / 12.0f),
						sinf(fAngle) * cosf(D3DX_PI / 12.0f) + cosf(fAngle) * sinf(D3DX_PI / 12.0f), 0.0f);

					CSkullFireball::Create(pos, D3DXVECTOR3(NewMove.x * 3.0f, NewMove.y * 3.0f, 0.0f));

					NewMove = D3DXVECTOR3(cosf(fAngle) * cosf(-D3DX_PI / 12.0f) - sinf(fAngle) * sinf(-D3DX_PI / 12.0f),
						sinf(fAngle) * cosf(-D3DX_PI / 12.0f) + cosf(fAngle) * sinf(-D3DX_PI / 12.0f), 0.0f);

					CSkullFireball::Create(pos, D3DXVECTOR3(NewMove.x * 3.0f, NewMove.y * 3.0f, 0.0f));
				}
				if (m_nPhase == 2)
				{
					D3DXVECTOR3 NewMove = D3DXVECTOR3(cosf(fAngle) * cosf(D3DX_PI / 6.0f) - sinf(fAngle) * sinf(D3DX_PI / 6.0f),
						sinf(fAngle) * cosf(D3DX_PI / 6.0f) + cosf(fAngle) * sinf(D3DX_PI / 6.0f), 0.0f);

					CSkullFireball::Create(pos, D3DXVECTOR3(NewMove.x * 3.0f, NewMove.y * 3.0f, 0.0f));

					NewMove = D3DXVECTOR3(cosf(fAngle) * cosf(-D3DX_PI / 6.0f) - sinf(fAngle) * sinf(-D3DX_PI / 6.0f),
						sinf(fAngle) * cosf(-D3DX_PI / 6.0f) + cosf(fAngle) * sinf(-D3DX_PI / 6.0f), 0.0f);

					CSkullFireball::Create(pos, D3DXVECTOR3(NewMove.x * 3.0f, NewMove.y * 3.0f, 0.0f));
				}

				if (m_nShootDelay == 99 || m_nShootDelay == 159)
				{
					m_nPhase++;
				}
				else if(m_nShootDelay == 240 || m_nShootDelay == 300)
				{
					m_nPhase--;
				}
				
				if (m_nShootDelay >= 360)
				{
					if (m_nCntShoot >= 2)
					{
						SetAnimPattern(1);
						m_state = state_normal;
						m_nPhase = 0;
						m_nShootDelay = 0;
						m_nCntShoot = 0;
					}
					else
					{
						m_nPhase = 0;
						m_nShootDelay = -70;
						m_nCntShoot++;
					}
				}

				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_FIRE);
			}
		}
	}

		break;

	case CWrathBody::state_rage:

	{
		switch (m_nPhase)
		{
		case 0:

		{
			if (pos.x >= 1400.0f)
			{
				SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				m_nPhase++;
			}
		}

			break;

		case 1:

		{
			m_nShootDelay++;

			if (m_nShootDelay == 5)
			{
				m_targetPos = CPlayer::GetPlayer()->GetPos();
			}

			if (m_nShootDelay % 10 == 9 && m_nShootDelay >= 60)
			{
				CSkullFireball::Create(D3DXVECTOR3(m_targetPos.x, (float)SCREEN_HEIGHT - 1.0f, 0.0f), D3DXVECTOR3(0.0f, -5.0f, 0.0f));
				CSkullFireball::Create(D3DXVECTOR3(m_targetPos.x - 20.0f, 1.0f, 0.0f), D3DXVECTOR3(0.0f, 5.0f, 0.0f));
				CSkullFireball::Create(D3DXVECTOR3(m_targetPos.x + 20.0f, 1.0f, 0.0f), D3DXVECTOR3(0.0f, 5.0f, 0.0f));

				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_FIRE);
			}

			if (m_nShootDelay >= 180)
			{
				m_nShootDelay = 0;
				m_nCntShoot++;
			}

			if (m_nCntShoot >= 5)
			{
				m_nShootDelay = 0;
				m_nCntShoot = 0;
				m_nPhase++;
				SetMove(D3DXVECTOR3(-2.0f, 0.0f, 0.0f));
			}
		}

			break;

		case 2:

		{
			{
				pos.y += 0.5f * sinf(m_fAngleMove);
				m_fAngleMove += D3DX_PI * 0.01f;

				if (pos.x <= 950.0f)
				{
					m_nPhase = 0;
					m_state = state_normal;
					SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				}

				SetPos(pos);
			}
		}

		default:
			break;
		}
	}

		break;

	case CWrathBody::state_swirl:

	{
		m_nShootDelay++;

		{
			pos.y += 0.5f * sinf(m_fAngleMove);
			m_fAngleMove += D3DX_PI * 0.01f;

			SetPos(pos);
		}

		if (m_nShootDelay % 20 == 19)
		{
			if (GetPresentAnimPattern() == 2)
			{
				SetAnimPattern(3);
			}
			else
			{
				SetAnimPattern(2);
			}
		}

		if (m_nShootDelay % 40 == 39)
		{
			float fStart = D3DX_PI * random(-500, 500) * 0.01f;

			

			for (int nCnt = 0; nCnt < 10; nCnt++)
			{
				D3DXVECTOR3 move = D3DXVECTOR3(5.0f * cosf(fStart + D3DX_PI * 2.0f * nCnt / 10.0f), 5.0f * sinf(fStart + D3DX_PI * 2.0f * nCnt / 10.0f), 0.0f);

				CSkullFireball::Create(pos, move);
			}

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_FIRE);
		}

		if (m_nShootDelay % 40 == 19)
		{
			D3DXVECTOR3 move = D3DXVECTOR3(CPlayer::GetPlayer()->GetPos() - pos);
			D3DXVec3Normalize(&move, &move);
			move.x *= 5.0f;
			move.y *= 5.0f;

			CSkullFireball::Create(pos, move);
		}

		if (m_nShootDelay >= 600)
		{
			m_nShootDelay = 0;
			m_state = state_normal;
		}
	}

		break;

	case CWrathBody::state_death:

	{
		if (m_nPhase == 0)
		{
			if (pos.y >= (float)SCREEN_HEIGHT + GetSize().y * 0.5f)
			{
				if (m_pArm != nullptr)
				{
					m_pArm->SetMove(D3DXVECTOR3(0.0f, 2.0f, 0.0f));
					m_nPhase++;
				}
			}
		}
		else if (m_nPhase == 1)
		{
			if (m_pArm->GetPos().y >= (float)SCREEN_HEIGHT + m_pArm->GetSize().y)
			{
				m_bDead = true;
			}
		}
	}

		break;

	default:
		break;
	}
}