//=============================================================================
//
// gameGluttony.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "gameGluttony.h"
#include "application.h"
#include "gluttony.h"
#include "player.h"
#include "inputKeyboard.h"
#include "bg.h"
#include "button.h"
#include "object2D.h"
#include "sound.h"
#include "backMaw.h"
#include "target.h"

#include "maw.h"
#include "heart.h"

//�R���X�g���N�^
CGameGluttony::CGameGluttony()
{
	//�����o�[�ϐ����N���A����

	m_bPause = false;

	m_pBg = nullptr;
	m_pPlayer = nullptr;
	m_pEnemy = nullptr;

	m_pMenuBg = nullptr;

	for (int nCnt = 0; nCnt < button_max; nCnt++)
	{
		m_pButton[nCnt] = nullptr;
	}
}

//�f�X�g���N�^
CGameGluttony::~CGameGluttony()
{

}

//����������
HRESULT CGameGluttony::Init(void)
{
	//�����o�[�ϐ��̏�����
	
	m_bPause = false;

	m_pBg = nullptr;
	m_pPlayer = nullptr;
	m_pEnemy = nullptr;
	//m_pMenu = nullptr;

	m_pMenuBg = nullptr;

	for (int nCnt = 0; nCnt < button_max; nCnt++)
	{
		m_pButton[nCnt] = nullptr;
	}

	//CMaw::Create(CMaw::left);
	//CMaw* pEnemy = CMaw::Create(CMaw::up);
	//pEnemy->SetAnimPattern(4);
	///*CMaw::Create(CMaw::right);
	//CMaw::Create(CMaw::down);*/
	//CObject_2D* pObj = CObject_2D::Create();
	//pObj->SetPos(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, 24.0f, 0.0f));
	//pObj->SetSize(D3DXVECTOR2(300.0f, 85.0f * 0.5f));
	//pObj->SetStartingRot(D3DX_PI * 0.5f);
	//pObj->SetTexture(CObject::TextureNull);
	//pObj->SetTextureParameter(1, 1, 1, INT_MAX);
	//pObj->SetColor(D3DCOLOR_ARGB(255, 255, 45, 45));
	//pObj->SetPriority(4);

	//CHeart::Create();

	//CTarget::Create();

	///*pObj = CObject_2D::Create();
	//pObj->SetPos(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, 150.0f, 0.0f));
	//pObj->SetSize(D3DXVECTOR2(70.0f, 103.6f));
	//pObj->SetStartingRot(D3DX_PI * 0.5f);
	//pObj->SetTexture(CObject::TextureGluttonyHeart);
	//pObj->SetTextureParameter(2, 2, 1, 10);
	//pObj->SetPriority(2);*/

	//CBackMaw::Create();

	//CGluttony::Create();

	CMaw* pMaw = CMaw::Create(CMaw::up);
	pMaw->SetAnimPattern(4);

	CObject_2D* pObj = CObject_2D::Create();
	pObj->SetPos(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, 24.0f, 0.0f));
	pObj->SetSize(D3DXVECTOR2(300.0f, 85.0f * 0.5f));
	pObj->SetStartingRot(D3DX_PI * 0.5f);
	pObj->SetTexture(CObject::TextureNull);
	pObj->SetTextureParameter(1, 1, 1, INT_MAX);
	pObj->SetColor(D3DCOLOR_ARGB(255, 255, 45, 45));
	pObj->SetPriority(4);

	return S_OK;
}

//�I������
void CGameGluttony::Uninit(void)
{
	//�|�C���^�̔j��
	if (m_pBg != nullptr)
	{
		m_pBg->Release();
		m_pBg = nullptr;
	}

	if (m_pPlayer != nullptr)
	{
		m_pPlayer->Release();
		m_pPlayer = nullptr;
	}

	if (m_pEnemy != nullptr)
	{
		m_pEnemy->Uninit();
		m_pEnemy = nullptr;
	}

	if (m_pMenuBg != nullptr)
	{
		m_pMenuBg->Release();
		m_pMenuBg = nullptr;
	}


	for (int nCnt = 0; nCnt < button_max; nCnt++)
	{
		if (m_pButton[nCnt] != nullptr)
		{
			m_pButton[nCnt]->Uninit();
			m_pButton[nCnt] = nullptr;
		}
	}
}

//�X�V����
void CGameGluttony::Update(void)
{
	if (m_pEnemy != nullptr)
	{
		m_pEnemy->Update();

		if (m_pEnemy->GetEnd())
		{//�G������ł��邩�ǂ����m�F����
			if (m_pPlayer != nullptr)
			{
				CApplication::SetRemainingLife(m_pPlayer->GetLife());
			}

			CApplication::SetFade(CApplication::Mode_Result);					//���[�h��؂�ւ���
		}
		else
		{
			UpdateMenu();														//���j���[�̍X�V����
		}
	}

	if (m_pPlayer != nullptr)
	{
		if (m_pPlayer->GetEnd())
		{
			CApplication::SetFade(CApplication::Mode_Result);					//�t�F�[�h�̐ݒ菈��
		}
	}
}



//��������
CGameGluttony* CGameGluttony::Create(void)
{
	CGameGluttony* pGame = new CGameGluttony;				//�X�e�[�W��ʂ̐���

	if (FAILED(pGame->Init()))
	{//����������
		return nullptr;
	}

	pGame->m_pBg = CBg::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));			//�w�i�̐���

	if (pGame->m_pBg != nullptr)
	{//�����o�����ꍇ�A�e�N�X�`����ݒ肷��
		pGame->m_pBg->SetTexture(CObject::TextureGluttonyBg);
		pGame->m_pBg->SetTextureParameter(1, 1, 1, INT_MAX);
	}

	pGame->m_pPlayer = CPlayer::Create();		//�v���C���[�̐���

	if (pGame->m_pPlayer != nullptr)
	{//�����ł����ꍇ�A�ʒu��ݒ肷��
		pGame->m_pPlayer->SetPos(D3DXVECTOR3(300.0f, (float)SCREEN_HEIGHT * 0.5f, 0.0f));
	}

	pGame->m_pEnemy = CGluttony::Create();			//�G�̐���

	return pGame;
}



//���j���[�̍X�V����
void CGameGluttony::UpdateMenu(void)
{
	if (CInputKeyboard::GetKeyboardTrigger(DIK_RETURN))
	{//�G���^�[�L�[����������
		if (m_bPause)
		{//�|�[�Y��Ԃ�������
			m_bPause = false;			//���ʏ�Ԃɂ���

			for (int nCnt = 0; nCnt < button_max; nCnt++)
			{
				if (m_pButton[nCnt] != nullptr)
				{
					m_pButton[nCnt]->Uninit();
					m_pButton[nCnt] = nullptr;
				}
			}
			if (m_pMenuBg != nullptr)
			{
				m_pMenuBg->Release();
				m_pMenuBg = nullptr;
			}

			CObject::SetPause(false);
		}
		else
		{//���ʏ�Ԃ�������A�|�[�Y���j���[�𐶐����āA�|�[�Y��Ԃɂ���

			m_pMenuBg = CBg::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
			m_pMenuBg->SetTexture(CObject::TextureMenuBg);
			m_pMenuBg->SetTextureParameter(1, 1, 1, INT_MAX);
			m_pMenuBg->SetSize(D3DXVECTOR2(250.0f, 150.0f));
			m_pMenuBg->SetPos(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, 360.0f, 0.0f));
			m_pMenuBg->SetPriority(5);
			m_pMenuBg->Update();

			char aText[button_max][24] = { { "continue" },{ "quit" } };

			for (int nCnt = 0; nCnt < button_max; nCnt++)
			{
				m_pButton[nCnt] = CButton::Create(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, 300.0f + 60.0f * 2.0f * nCnt, 0.0f), D3DXVECTOR2(55.0f, 55.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), aText[nCnt]);
			}

			CObject::SetPause(true);

			m_bPause = true;
		}
	}

	if (m_bPause)
	{//�|�[�Y��Ԃ�������
		for (int nCnt = 0; nCnt < button_max; nCnt++)
		{//�{�^���̍X�V����
			if (m_pButton[nCnt] != nullptr)
			{
				m_pButton[nCnt]->Update();

				if (m_pButton[nCnt]->GetTriggerState())
				{
					CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_CLICK);

					switch (nCnt)
					{
					case button_continue:

					{
						m_bPause = false;

						for (int nCnt2 = 0; nCnt2 < button_max; nCnt2++)
						{
							if (m_pButton[nCnt2] != nullptr)
							{
								m_pButton[nCnt2]->Uninit();
								m_pButton[nCnt2] = nullptr;
							}
						}

						if (m_pMenuBg != nullptr)
						{
							m_pMenuBg->Release();
							m_pMenuBg = nullptr;
						}

						CObject::SetPause(false);
					}

					break;

					case button_quit:

					{
						m_bPause = false;
						CObject::SetPause(false);
						CApplication::SetFade(CApplication::Mode_Title);
						return;
					}

					break;

					default:
						break;
					}
				}
			}
		}
	}
}