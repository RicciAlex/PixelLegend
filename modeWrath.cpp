//=============================================================================
//
// gameWrath.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "modeWrath.h"
#include "application.h"
#include "wrath.h"
#include "player.h"
#include "inputKeyboard.h"
#include "bg.h"
#include "button.h"
#include "object2D.h"
#include "sound.h"
#include "target.h"
#include "enemyWrathBody.h"

//�R���X�g���N�^
CGameWrath::CGameWrath()
{
	//�����o�[�ϐ����N���A����
	m_nCntBg = 0;
	m_fColAnim = 0.0f;

	m_bPause = false;

	m_pBg = nullptr;
	m_pBackBg = nullptr;
	m_pPlayer = nullptr;
	m_pEnemy = nullptr;

	m_pMenuBg = nullptr;

	for (int nCnt = 0; nCnt < button_max; nCnt++)
	{
		m_pButton[nCnt] = nullptr;
	}

	m_pObj = nullptr;
	m_nAnim = 0;
}

//�f�X�g���N�^
CGameWrath::~CGameWrath()
{

}

//����������
HRESULT CGameWrath::Init(void)
{
	//�����o�[�ϐ��̏�����
	m_nCntBg = 0;
	m_fColAnim = -0.001f;

	m_bPause = false;

	m_pBg = nullptr;
	m_pBackBg = nullptr;
	m_pPlayer = nullptr;
	m_pEnemy = nullptr;
	//m_pMenu = nullptr;

	m_pMenuBg = nullptr;
	m_pObj = nullptr;
	m_nAnim = 0;

	for (int nCnt = 0; nCnt < button_max; nCnt++)
	{
		m_pButton[nCnt] = nullptr;
	}

	return S_OK;
}

//�I������
void CGameWrath::Uninit(void)
{
	//�|�C���^�̔j��
	if (m_pBg != nullptr)
	{
		m_pBg->Release();
		m_pBg = nullptr;
	}
	if (m_pBackBg != nullptr)
	{
		m_pBackBg->Release();
		m_pBackBg = nullptr;
	}
	if (m_pPlayer != nullptr)
	{
		m_pPlayer->Release();
		m_pPlayer = nullptr;
	}

	if (m_pEnemy != nullptr)
	{
		m_pEnemy->Release();
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

	if (m_pObj != nullptr)
	{
		m_pObj->Release();
		m_pObj = nullptr;
	}
}

//�X�V����
void CGameWrath::Update(void)
{
	if (m_pEnemy != nullptr)
	{
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
			if (m_pBackBg != nullptr)
			{
				m_nCntBg++;

				D3DXCOLOR col = m_pBackBg->GetColor();

				col.r += m_fColAnim;
				col.g += m_fColAnim;

				if (col.r >= 1.0f || col.r <= 0.7f)
				{
					m_fColAnim *= -1.0f;
				}

				m_pBackBg->SetColor(col);
			}

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
CGameWrath* CGameWrath::Create(void)
{
	CGameWrath* pGame = new CGameWrath;				//�X�e�[�W��ʂ̐���

	if (FAILED(pGame->Init()))
	{//����������
		return nullptr;
	}

	pGame->m_pBackBg = CObject_2D::Create();			

	if (pGame->m_pBackBg != nullptr)
	{//�����o�����ꍇ�A�e�N�X�`����ݒ肷��
		pGame->m_pBackBg->SetPos(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f));
		pGame->m_pBackBg->SetSize(D3DXVECTOR2((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT));
		pGame->m_pBackBg->SetTexture(CObject::TextureNull);
		pGame->m_pBackBg->SetTextureParameter(1, 1, 1, INT_MAX);
		pGame->m_pBackBg->SetColor(D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f));
		pGame->m_pBackBg->SetPriority(1);
	}

	pGame->m_pBg = CBg::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));			//�w�i�̐���

	if (pGame->m_pBg != nullptr)
	{//�����o�����ꍇ�A�e�N�X�`����ݒ肷��
		pGame->m_pBg->SetTexture(CObject::TextureWrathBg);
		pGame->m_pBg->SetTextureParameter(1, 1, 2, INT_MAX);
		pGame->m_pBg->SetPriority(1);
	}

	pGame->m_pPlayer = CPlayer::Create();		//�v���C���[�̐���

	if (pGame->m_pPlayer != nullptr)
	{//�����ł����ꍇ�A�ʒu��ݒ肷��
		pGame->m_pPlayer->SetPos(D3DXVECTOR3(300.0f, (float)SCREEN_HEIGHT * 0.5f, 0.0f));
	}

	pGame->m_pEnemy = CWrath::Create();			//�G�̐���

	return pGame;
}



//���j���[�̍X�V����
void CGameWrath::UpdateMenu(void)
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