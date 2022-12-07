//=============================================================================
//
// Scylla.h
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "Scylla.h"
#include "ScyllaBody.h"
#include "SkullTentacle.h"
#include "spine.h"
#include "enemyLife.h"
#include "application.h"
#include "sound.h"

#include "inputKeyboard.h"

//コンストラクタ
CScylla::CScylla()
{
	//メンバー変数をクリアする
	m_bEnd = false;
	m_pBody = nullptr;
	for (int nCnt = 0; nCnt < MaxTentacle; nCnt++)
	{
		m_pSpine[nCnt] = nullptr;
		m_pTentacle[nCnt] = nullptr;
		m_aliveHead[nCnt] = false;
		m_state = state_Max;

		m_nCntAttack = 0;
		m_nAliveHeadNum = 0;
		m_Anchor[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_TentacleAnchor[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	m_pLife = nullptr;
}

//デストラクタ
CScylla::~CScylla()
{

}

//初期化処理
HRESULT CScylla::Init(void)
{
	//メンバー変数の初期化
	m_bEnd = false;
	m_pBody = nullptr;
	for (int nCnt = 0; nCnt < MaxTentacle; nCnt++)
	{
		m_pSpine[nCnt] = nullptr;
		m_pTentacle[nCnt] = nullptr;
		m_aliveHead[nCnt] = true;

		m_nCntAttack = 0;
		m_state = state_Spawn;
		m_nAliveHeadNum = MaxTentacle;
		m_Anchor[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_TentacleAnchor[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	m_pLife = nullptr;

	return S_OK;
}

//終了処理
void CScylla::Uninit(void)
{
	for (int nCnt = 0; nCnt < MaxTentacle; nCnt++)
	{
		if (m_pSpine[nCnt] != nullptr)
		{
			m_pSpine[nCnt]->Release();
			m_pSpine[nCnt] = nullptr;
		}

		if (m_pTentacle[nCnt] != nullptr)
		{
			m_pTentacle[nCnt]->Release();
			m_pTentacle[nCnt] = nullptr;
		}
	}

	if (m_pBody != nullptr)
	{	
		m_pBody->Release();
		m_pBody = nullptr;
	}

	if (m_pLife != nullptr)
	{
		m_pLife->Release();
		m_pLife = nullptr;
	}
}

//更新処理
void CScylla::Update(void)
{
	for (int nCnt = 0; nCnt < MaxTentacle; nCnt++)
	{
		if (m_pTentacle[nCnt] != nullptr)
		{
			int nLife = m_pTentacle[nCnt]->GetLife();

			if (nLife <= 0 && m_aliveHead[nCnt])
			{
				m_pTentacle[nCnt]->Kill();
				m_pTentacle[nCnt] = nullptr;
				m_pSpine[nCnt]->Kill();
				m_pSpine[nCnt] = nullptr;
				m_aliveHead[nCnt] = false;
				m_nAliveHeadNum--;

				if (m_pLife != nullptr)
				{
					m_pLife->SubtractLife(1);
				}

				if (m_nAliveHeadNum <= 0)
				{
					m_state = state_Death;
				}
				else
				{
					m_state = state_Damage;
					m_nCntAttack = 30;
				}
			}
		}
	}

	//========================================================================================================
	//										一時的
	if (CInputKeyboard::GetKeyboardTrigger(DIK_R))
	{
		m_pSpine[3]->Kill();
	}
	//========================================================================================================

	switch (m_state)
	{
	case state_normal:

		//普通状態

		if (m_nAliveHeadNum >= MaxTentacle)
		{
			m_nCntAttack++;

			if (m_nCntAttack >= 120)
			{
				int Idx = random(0, 5);
				m_pTentacle[Idx]->SetState(CSkullTentacle::state_Bite);
				m_nCntAttack = 0;
				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_ROAR);
			}
		}
		else if (m_nAliveHeadNum < MaxTentacle && m_nAliveHeadNum >= 4)
		{
			m_nCntAttack++;

			if(m_nCntAttack >= 480)
			{
				CSkullTentacle::State state = CSkullTentacle::state_Max;
				int a = 0;
				int b = 6;
				int c = 6;

				while (a < 2)
				{
					int Idx = random(0, 5);

					if (m_pTentacle[Idx] != nullptr)
					{
						state = m_pTentacle[Idx]->GetState();

						if (m_aliveHead[Idx] == true && state == CSkullTentacle::state_Idle && Idx != b)
						{
							switch (a)
							{
							case 0:
								b = Idx;
								break;
							case 1:
								c = Idx;
								break;
							default:
								break;
							}

							a++;
						}
					}
				}

				m_pTentacle[b]->SetState(CSkullTentacle::state_Pursuit);
				m_pTentacle[c]->SetState(CSkullTentacle::state_Pull);
				m_nCntAttack = 0;
			}
			
		}
		else if (m_nAliveHeadNum < 4 && m_nAliveHeadNum > 0)
		{
			m_nCntAttack++;

			if (m_nCntAttack >= 400)
			{
				CSkullTentacle::State state = CSkullTentacle::state_Max;
				int Idx = 6;

				while (true)
				{
					Idx = random(0, 5);

					if (m_pTentacle[Idx] != nullptr)
					{
						break;
					}
				}

				m_pTentacle[Idx]->SetState(CSkullTentacle::state_Flamethrower);
				m_nCntAttack = 0;
			}
		}
		
		break;

	case state_Spawn:

		m_nCntAttack++;

		if (m_nCntAttack >= 60)
		{
			m_state = state_normal;
			m_nCntAttack = 0;
		}

		break;

	case state_Damage:

		m_nCntAttack--;

		if (m_nCntAttack <= 0)
		{
			m_nCntAttack = 0;
			m_state = state_normal;

			if (m_nAliveHeadNum == 5)
			{
				m_nCntAttack = 360;
			}
			else if (m_nAliveHeadNum == 3)
			{
				m_nCntAttack = 180;
			}
		}

		break;

	case state_Death:

		m_pBody->SetPos(m_pBody->GetPos() + D3DXVECTOR3(0.0f, 2.0f, 0.0f));
		m_pBody->SetAnimPattern(1);

		if (m_pBody->GetPos().y >= 1000.0f)
		{
			m_bEnd = true;
		}

		break;

	default:

		break;
	}
}

//描画処理
void CScylla::Draw(void)
{

}

//位置の設定処理
void CScylla::SetPos(const D3DXVECTOR3 pos)
{

}

//サイズの取得処理
const D3DXVECTOR2 CScylla::GetSize(void)
{
	return D3DXVECTOR2(0.0f, 0.0f);
}


const D3DXVECTOR3 CScylla::GetPos(void)
{
	return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}


const bool CScylla::GetEnd(void)
{
	return m_bEnd;
}


//========================================================================================================
//										静的関数 
//========================================================================================================

//生成処理
CScylla* CScylla::Create(void)
{
	CScylla* pScylla = new CScylla;

	if (FAILED(pScylla->Init()))
	{
		return nullptr;
	}

	D3DXVECTOR3 pos = D3DXVECTOR3((float)SCREEN_WIDTH * 0.8f, (float)SCREEN_HEIGHT * 0.5f, 0.0f);
	pScylla->SetPos(pos);


	pScylla->m_Anchor[0] = D3DXVECTOR3((float)SCREEN_WIDTH * 1.00f, 800.0f, 0.0f);
	pScylla->m_Anchor[1] = D3DXVECTOR3((float)SCREEN_WIDTH * 0.95f, 800.0f, 0.0f);
	pScylla->m_Anchor[2] = D3DXVECTOR3((float)SCREEN_WIDTH * 0.90f, 800.0f, 0.0f);
	pScylla->m_Anchor[3] = D3DXVECTOR3((float)SCREEN_WIDTH * 0.85f, 800.0f, 0.0f);
	pScylla->m_Anchor[4] = D3DXVECTOR3((float)SCREEN_WIDTH * 0.80f, 800.0f, 0.0f);
	pScylla->m_Anchor[5] = D3DXVECTOR3((float)SCREEN_WIDTH * 0.75f, 800.0f, 0.0f);


	pScylla->m_pSpine[0] = CSpine::Create(D3DXVECTOR3((float)SCREEN_WIDTH * 0.950f, 500.0f, 0.0f), pScylla->m_Anchor[0]);
	pScylla->m_pSpine[1] = CSpine::Create(D3DXVECTOR3((float)SCREEN_WIDTH * 0.925f, 500.0f, 0.0f), pScylla->m_Anchor[1]);
	pScylla->m_pSpine[2] = CSpine::Create(D3DXVECTOR3((float)SCREEN_WIDTH * 0.900f, 500.0f, 0.0f), pScylla->m_Anchor[2]);
	pScylla->m_pSpine[3] = CSpine::Create(D3DXVECTOR3((float)SCREEN_WIDTH * 0.875f, 500.0f, 0.0f), pScylla->m_Anchor[3]);
	pScylla->m_pSpine[4] = CSpine::Create(D3DXVECTOR3((float)SCREEN_WIDTH * 0.850f, 500.0f, 0.0f), pScylla->m_Anchor[4]);
	pScylla->m_pSpine[5] = CSpine::Create(D3DXVECTOR3((float)SCREEN_WIDTH * 0.825f, 500.0f, 0.0f), pScylla->m_Anchor[5]);

	pScylla->m_pBody = CScyllaBody::Create();

	pScylla->m_TentacleAnchor[0] = D3DXVECTOR3(50.0f, -10.0f, 0.0f);
	pScylla->m_TentacleAnchor[1] = D3DXVECTOR3(350.0f, -10.0f, 0.0f);
	pScylla->m_TentacleAnchor[2] = D3DXVECTOR3(750.0f, -10.0f, 0.0f);
	pScylla->m_TentacleAnchor[3] = D3DXVECTOR3(50.0f, (float)SCREEN_HEIGHT + 10.0f, 0.0f);
	pScylla->m_TentacleAnchor[4] = D3DXVECTOR3(350.0f, (float)SCREEN_HEIGHT + 10.0f, 0.0f);
	pScylla->m_TentacleAnchor[5] = D3DXVECTOR3(750.0f, (float)SCREEN_HEIGHT + 10.0f, 0.0f);

	pScylla->m_pTentacle[0] = CSkullTentacle::Create(pScylla->m_TentacleAnchor[0], D3DXVECTOR3(pScylla->m_TentacleAnchor[0].x, pScylla->m_TentacleAnchor[0].y + 100.0f, 0.0f));
	pScylla->m_pTentacle[1] = CSkullTentacle::Create(pScylla->m_TentacleAnchor[1], D3DXVECTOR3(pScylla->m_TentacleAnchor[1].x, pScylla->m_TentacleAnchor[1].y + 70.0f, 0.0f));
	pScylla->m_pTentacle[2] = CSkullTentacle::Create(pScylla->m_TentacleAnchor[2], D3DXVECTOR3(pScylla->m_TentacleAnchor[2].x, pScylla->m_TentacleAnchor[2].y + 70.0f, 0.0f));
	pScylla->m_pTentacle[3] = CSkullTentacle::Create(pScylla->m_TentacleAnchor[3], D3DXVECTOR3(pScylla->m_TentacleAnchor[3].x, pScylla->m_TentacleAnchor[3].y - 100.0f, 0.0f));
	pScylla->m_pTentacle[4] = CSkullTentacle::Create(pScylla->m_TentacleAnchor[4], D3DXVECTOR3(pScylla->m_TentacleAnchor[4].x, pScylla->m_TentacleAnchor[4].y - 70.0f, 0.0f));
	pScylla->m_pTentacle[5] = CSkullTentacle::Create(pScylla->m_TentacleAnchor[5], D3DXVECTOR3(pScylla->m_TentacleAnchor[5].x, pScylla->m_TentacleAnchor[5].y - 70.0f, 0.0f));

	pScylla->m_pLife = CEnemyLife::Create(D3DXVECTOR3(900.0f, 40.0f, 0.0f), D3DXCOLOR(1.0f, 0.4f, 0.0f, 0.5f), 6, "scylla");

	return pScylla;
}