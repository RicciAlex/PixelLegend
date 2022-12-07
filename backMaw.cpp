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

#include "inputKeyboard.h"

//コンストラクタ
CBackMaw::CBackMaw()
{
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
	{
		return -1;
	}

	m_target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_state = state_sleep;

	m_pHitbox = nullptr;

	return S_OK;
}

//終了処理
void CBackMaw::Uninit(void)
{
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}

	CEnemy::Uninit();
}

//更新処理
void CBackMaw::Update(void)
{
	CObject_2D::Update();

	UpdateState();

	if (CInputKeyboard::GetKeyboardTrigger(DIK_U))
	{
		m_state = state_awake;
	}
}

//描画処理
void CBackMaw::Draw(void)
{
	CObject_2D::Draw();
}

//状態の設定処理
void CBackMaw::SetState(CBackMaw::state state)
{
	if (m_state == state_sleep)
	{
		m_fAngleMove = 0;

		m_state = state;
	}
}




//生成処理
CBackMaw* CBackMaw::Create(void)
{
	CBackMaw* pEnemy = new CBackMaw;

	if (FAILED(pEnemy->Init()))
	{
		return nullptr;
	}

	pEnemy->SetPos(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f));
	pEnemy->SetSize(D3DXVECTOR2(100.0f, 90.0f));
	pEnemy->SetStartingRot(D3DX_PI * 0.5f);
	pEnemy->SetTexture(CObject::TextureGluttonyBackMaw);
	pEnemy->SetTextureParameter(1, 2, 2, INT_MAX);
	pEnemy->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
	pEnemy->SetPriority(2);

	return pEnemy;
}




//状態の更新処理
void CBackMaw::UpdateState(void)
{
	D3DXVECTOR3 pos = GetPos();

	switch (m_state)
	{
	case CBackMaw::state_sleep:

	{
		m_fAngleMove += D3DX_PI * 0.01f;

		pos.y += sinf(m_fAngleMove) * -0.1f;
		SetPos(pos);
	}

		break;

	case CBackMaw::state_roar:

	{
		m_nCntMove++;

		if (m_nPhase == 0)
		{
			if (m_nCntMove >= 4)
			{
				int anim = GetPresentAnimPattern();
				anim++;
				m_nCntMove = 0;

				if (anim >= 4)
				{
					m_nPhase++;
					CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_GLUTTONY_ROAR);
				}
				else
				{
					SetAnimPattern(anim);
				}
			}
		}
		else if (m_nPhase == 1)
		{
			if (m_nCntMove >= 180)
			{
				m_nPhase++;
				m_nCntMove = 0;
			}
		}
		else if (m_nPhase == 2)
		{
			if (m_nCntMove >= 4)
			{
				int anim = GetPresentAnimPattern();
				anim--;
				m_nCntMove = 0;

				if (anim <= 0)
				{
					anim = 0;
					m_nPhase = 0;

					switch (random(0, 1))
					{
					case 0:

					{
						m_state = state_shoot;
					}

						break;

					case 1:

					{
						m_state = state_bite;
					}

						break;

					default:
						break;
					}
				}
				else
				{
					SetAnimPattern(anim);
				}
			}
		}
	}
	

		break;

	case CBackMaw::state_shoot:

	{
		if (m_nPhase == 0)
		{
			m_nCntMove++; 

			if (m_nCntMove >= 3)
			{
				int anim = GetPresentAnimPattern();
				anim++;
				m_nCntMove = 0;

				if (anim >= 4)
				{
					m_nPhase++;
				}
				else
				{
					SetAnimPattern(anim);
				}
			}
		}
		else if (m_nPhase == 1)
		{
			m_nShootDelay++;

			if (m_nShootDelay % 120 == 5)
			{
				int nRand = random(4, 10);

				for (int nCnt = 0; nCnt < nRand; nCnt++)
				{
					CBone::Create(GetPos(), D3DXVECTOR3(2.0f * cosf((2.0f * D3DX_PI * nCnt) / nRand), 2.0f * sinf((2.0f * D3DX_PI * nCnt) / nRand), 0.0f));
				}

				if (m_nShootDelay >= 500)
				{
					m_nShootDelay = 0;
					m_nPhase++;
				}
			}
		}
		else if (m_nPhase == 2)
		{
			m_nCntMove++;

			if (m_nCntMove >= 3)
			{
				int anim = GetPresentAnimPattern();
				anim--;
				m_nCntMove = 0;

				if (anim <= 0)
				{
					anim = 0;
					m_nPhase = 0;
					m_state = state_return;
				}
				else
				{
					SetAnimPattern(anim);
				}
			}
		}
		else
		{
			m_nPhase = 0;
		}
	}

		break;

	case CBackMaw::state_bite:

	{
		if (m_nPhase == 0)
		{
			m_nCntMove++;

			if (m_nCntMove >= 3)
			{
				int anim = GetPresentAnimPattern();
				anim++;
				m_nCntMove = 0;

				if (anim >= 4)
				{
					m_nPhase++;
				}
				else
				{
					SetAnimPattern(anim);
				}
			}
		}
		else if (m_nPhase == 1)
		{
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
		{
			D3DXVECTOR3 distance = m_target - pos;
			float lenght = D3DXVec3Length(&distance);

			if (lenght <= 8.0f)
			{
				SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				m_nPhase++;

				if (m_pHitbox == nullptr)
				{
					m_pHitbox = CSquareHitbox::Create(pos, D3DXVECTOR2(85.0f, 40.0f), CHitbox::Type_Enemy);
				}
			}
		}
		else if (m_nPhase == 3)
		{
			m_nCntMove++;

			if (m_nCntMove >= 3)
			{
				int anim = GetPresentAnimPattern();
				anim--;
				m_nCntMove = 0;

				if (anim <= 0)
				{
					CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_BITE);
					anim = 0;
					m_pHitbox->Release();
					m_pHitbox = nullptr;
					m_nShootDelay++;

					if (m_nShootDelay >= 6)
					{
						m_nShootDelay = 0;
						m_nPhase++;
					}
					else
					{
						m_nPhase = 0;
					}
				}
				else
				{
					SetAnimPattern(anim);
				}
			}
		}
		else if (m_nPhase == 4)
		{
			D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			m_target = D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f);
			move = m_target - pos;
			D3DXVec3Normalize(&move, &move);
			move.x *= 8.0f;
			move.y *= 8.0f;
			SetMove(move);
			m_nPhase++;
		}
		else if (m_nPhase == 5)
		{
			D3DXVECTOR3 distance = m_target - pos;
			float lenght = D3DXVec3Length(&distance);

			if (lenght <= 8.0f)
			{
				SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				m_nPhase = 0;
				m_state = state_return;
			}
		}
		

	}

		break;

	case CBackMaw::state_awake:

	{
		D3DXCOLOR col = GetColor();

		col.r += 0.01f;
		col.g += 0.01f;
		col.b += 0.01f;

		if (col.r >= 1.0f)
		{
			m_state = state_roar;
		}
		else
		{
			SetColor(col);
		}
	}

		break;

	case CBackMaw::state_return:

	{
		D3DXCOLOR col = GetColor();

		col.r -= 0.01f;
		col.g -= 0.01f;
		col.b -= 0.01f;

		if (col.r <= 0.5f)
		{
			m_state = state_sleep;
		}
		else
		{
			SetColor(col);
		}
	}

		break;


	case CBackMaw::state_wait:

	{
		m_nCntMove++;

		if (m_nCntMove >= 600)
		{
			m_nCntMove = 0;
			m_state = state_awake;
		}
	}

	break;

	default:
		break;
	}
}