//=============================================================================
//
// gameEnvy.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "gameEnvy.h"
#include "application.h"
#include "envy.h"
#include "player.h"
#include "inputKeyboard.h"
#include "bg.h"
#include "button.h"
#include "object2D.h"
#include "sound.h"
#include "target.h"

//�R���X�g���N�^
CGameEnvy::CGameEnvy()
{
	//�����o�[�ϐ����N���A����
	m_nCntAnim = 0;

	m_bPause = false;

	m_pBg = nullptr;
	m_pPlayer = nullptr;
	m_pEnemy = nullptr;

	m_pMenuBg = nullptr;
	m_pThunderBg = nullptr;

	for (int nCnt = 0; nCnt < button_max; nCnt++)
	{
		m_pButton[nCnt] = nullptr;
	}
}

//�f�X�g���N�^
CGameEnvy::~CGameEnvy()
{

}

//����������
HRESULT CGameEnvy::Init(void)
{
	//�����o�[�ϐ��̏�����
	m_nCntAnim = 0;

	m_bPause = false;

	m_pBg = nullptr;
	m_pPlayer = nullptr;
	m_pEnemy = nullptr;
	//m_pMenu = nullptr;

	m_pMenuBg = nullptr;
	m_pThunderBg = nullptr;

	CTarget::Create();

	for (int nCnt = 0; nCnt < button_max; nCnt++)
	{
		m_pButton[nCnt] = nullptr;
	}

	return S_OK;
}

//�I������
void CGameEnvy::Uninit(void)
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
		m_pEnemy->Release();
		m_pEnemy = nullptr;
	}

	if (m_pMenuBg != nullptr)
	{
		m_pMenuBg->Release();
		m_pMenuBg = nullptr;
	}

	if (m_pThunderBg != nullptr)
	{
		m_pThunderBg->Release();
		m_pThunderBg = nullptr;
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
void CGameEnvy::Update(void)
{
	m_nCntAnim++;

	if (m_nCntAnim % 400 == 60)
	{//�w�i�̗��A�j���[�V����
		if (m_pThunderBg == nullptr)
		{
			m_pThunderBg = CObject_2D::Create();				//���𐶐�����

			if (m_pThunderBg != nullptr)
			{
				m_pThunderBg->SetPos(D3DXVECTOR3((float)CObject::random(200, 1080), 250.0f, 0.0f));		//�ʒu�̐ݒ�
				m_pThunderBg->SetTexture(CObject::TextureThunder);										//�e�N�X�`���̐ݒ�
				m_pThunderBg->SetTextureParameter(8, 4, 2, 4);											//�e�N�X�`���p�����[�^�̐ݒ菈��
				m_pThunderBg->SetSize(D3DXVECTOR2(40.0f, 133.0f));										//�T�C�Y�̐ݒ�
				m_pThunderBg->SetStartingRot(D3DX_PI * 0.5f);											//��]�p�x�̐ݒ�
				m_pThunderBg->SetPriority(1);															//�v���C�I���e�B�̐ݒ�

				CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_THUNDER);		//���̃T�E���h�G�t�F�N�g

				if (m_pBg != nullptr)
				{//�w�i�𖾂邭����
					m_pBg->SetVtxColor(0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					m_pBg->SetVtxColor(1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				}
			}
		}
	}

	if (m_pThunderBg != nullptr)
	{//���̃e�N�X�`���A�j���[�V����
		int anim = m_pThunderBg->GetPresentAnimPattern();

		if (anim >= 7)
		{
			m_pThunderBg->Release();											//���̔j��
			m_pThunderBg = nullptr;												//�|�C���^��null�ɂ���
			m_pBg->SetVtxColor(0, D3DXCOLOR(0.25f, 0.25f, 0.25f, 1.0f));		//�w�i�J���[�����ɖ߂�
			m_pBg->SetVtxColor(1, D3DXCOLOR(0.25f, 0.25f, 0.25f, 1.0f));		//�w�i�J���[�����ɖ߂�
		}
	}

	if (m_pEnemy != nullptr)
	{
		if (m_pEnemy->GetEnd())
		{//�G������ł��邩�ǂ����m�F����
			if (m_pPlayer != nullptr)
			{
				CApplication::SetRemainingLife(m_pPlayer->GetLife());
			}

			//CApplication::SetMode(CApplication::Mode_Result);					//���[�h��؂�ւ���
			CApplication::SetFade(CApplication::Mode_Result);					//�t�F�[�h�̐ݒ菈��
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
CGameEnvy* CGameEnvy::Create(void)
{
	CGameEnvy* pGame = new CGameEnvy;				//�X�e�[�W��ʂ̐���

	if (FAILED(pGame->Init()))
	{//����������
		return nullptr;
	}

	pGame->m_pBg = CBg::Create(D3DXCOLOR(0.25f, 0.25f, 0.25f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));			//�w�i�̐���

	if (pGame->m_pBg != nullptr)
	{//�����o�����ꍇ�A�e�N�X�`����ݒ肷��
		pGame->m_pBg->SetTexture(CObject::TextureEnvyBg);
		pGame->m_pBg->SetTextureParameter(1, 1, 1, INT_MAX);
	}
		
	pGame->m_pPlayer = CPlayer::Create();		//�v���C���[�̐���

	if (pGame->m_pPlayer != nullptr)
	{//�����ł����ꍇ�A�ʒu��ݒ肷��
		pGame->m_pPlayer->SetPos(D3DXVECTOR3(300.0f, (float)SCREEN_HEIGHT * 0.5f, 0.0f));
	}

	pGame->m_pEnemy = CEnvy::Create();			//�G�̐���

	return pGame;
}



//���j���[�̍X�V����
void CGameEnvy::UpdateMenu(void)
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