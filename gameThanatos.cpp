//=============================================================================
//
// gameThanatos.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "gameThanatos.h"
#include "Thanatos.h"
#include "player.h"
#include "inputKeyboard.h"
#include "inputMouse.h"
#include "bg.h"
#include "button.h"
#include "application.h"
#include "sound.h"
#include "target.h"

//�R���X�g���N�^
CGameThanatos::CGameThanatos()
{
	//�����o�[�ϐ����N���b�N����
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
CGameThanatos::~CGameThanatos()
{

}

//����������
HRESULT CGameThanatos::Init(void)
{
	//�����o�[�ϐ�������������
	m_bPause = false;

	m_pBg = nullptr;
	m_pPlayer = nullptr;
	m_pEnemy = nullptr;

	m_pMenuBg = nullptr;

	CTarget::Create();

	for (int nCnt = 0; nCnt < button_max; nCnt++)
	{
		m_pButton[nCnt] = nullptr;
	}

	return S_OK;
}

//�I������
void CGameThanatos::Uninit(void)
{
	//�w�i�̔j��
	if (m_pBg != nullptr)
	{//null�`�F�b�N
		m_pBg->Release();			//���������������
		m_pBg = nullptr;			//�|�C���^��null�ɂ���
	}
	//�v���C���[�̔j��
	if (m_pPlayer != nullptr)
	{//null�`�F�b�N
		m_pPlayer->Release();		//���������������
		m_pPlayer = nullptr;		//�|�C���^��null�ɂ���
	}
	//�G�̔j��
	if (m_pEnemy != nullptr)
	{//null�`�F�b�N
		m_pEnemy->Release();		//���������������
		m_pEnemy = nullptr;			//�|�C���^��null�ɂ���
	}
	//���j���[�̔w�i�̔j��
	if (m_pMenuBg != nullptr)
	{//null�`�F�b�N
		m_pMenuBg->Release();		//���������������
		m_pMenuBg = nullptr;		//�|�C���^��null�ɂ���
	}
	//�{�^���̔j��
	for (int nCnt = 0; nCnt < button_max; nCnt++)
	{
		if (m_pButton[nCnt] != nullptr)
		{//null�`�F�b�N
			m_pButton[nCnt]->Uninit();			//���������������
			m_pButton[nCnt] = nullptr;			//�|�C���^��null�ɂ���
		}
	}
}

//�X�V����
void CGameThanatos::Update(void)
{
	if (m_pEnemy != nullptr)
	{//�G��null�`�F�b�N

		if (m_pEnemy->GetEnd())
		{//�G�����񂾂�

			if (m_pPlayer != nullptr)
			{//�v���C���[��null�`�F�b�N

				CApplication::SetRemainingLife(m_pPlayer->GetLife());		//�v���C���[�̎c�����̗͂̎擾
			}

			CApplication::SetFade(CApplication::Mode_Result);				//���U���g��ʂɐ؂�ւ���
		}
		else
		{//�܂�����ł��Ȃ�������

			UpdateMenu();			//���j���[���X�V����
		}
	}

	if (m_pPlayer != nullptr)
	{//�v���C���[��null�`�F�b�N

		if (m_pPlayer->GetEnd())
		{//�v���C���[�����񂾂�

			CApplication::SetFade(CApplication::Mode_Result);		//���U���g��ʂɐ؂�ւ���
		}
	}
}



//=============================================================================
//
//								�ÓI�֐�
//
//=============================================================================



//��������
CGameThanatos* CGameThanatos::Create(void)
{
	CGameThanatos* pGame = new CGameThanatos;		//�C���X�^���X�𐶐�����

	if (FAILED(pGame->Init()))
	{//����������
		return nullptr;
	}

	//�w�i�𐶐�����
	pGame->m_pBg = CBg::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, -0.0f));		

	if (pGame->m_pBg != nullptr)
	{//�����o������A�K�v�ȃp�����[�^�̐ݒ�
		pGame->m_pBg->SetTexture(CObject::TextureThanatosBG);
		pGame->m_pBg->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
		pGame->m_pBg->SetTextureParameter(1, 1, 1, INT_MAX);
	}

	//�v���C���[�̐���
	pGame->m_pPlayer = CPlayer::Create();

	if (pGame->m_pPlayer != nullptr)
	{//�����o������A�ʒu��ݒ肷��
		pGame->m_pPlayer->SetPos(D3DXVECTOR3(300.0f, (float)SCREEN_HEIGHT * 0.5f, 0.0f));
	}

	//�G�̐���
	pGame->m_pEnemy = CThanatos::Create();

	if (pGame->m_pEnemy)
	{//�����o������A�w�i�ւ̃|�C���^��ݒ肷��
		pGame->m_pEnemy->SetBgPointer(pGame->m_pBg);
	}

	return pGame;			//���������C���X�^���X��Ԃ�
}


//=============================================================================
//
//							�v���C�x�[�g�֐�
//
//=============================================================================


//���j���[�̍X�V����
void CGameThanatos::UpdateMenu(void)
{
	if (CInputKeyboard::GetKeyboardTrigger(DIK_RETURN))
	{//�G���^�[�L�[����������
		if (m_bPause)
		{//�|�[�Y��Ԃ�������
			m_bPause = false;			//���ʏ�Ԃɂ���

										//�{�^����j������
			for (int nCnt = 0; nCnt < button_max; nCnt++)
			{
				if (m_pButton[nCnt] != nullptr)
				{
					m_pButton[nCnt]->Uninit();
					m_pButton[nCnt] = nullptr;
				}
			}
			//���j���[�̔w�i��j������
			if (m_pMenuBg != nullptr)
			{
				m_pMenuBg->Release();
				m_pMenuBg = nullptr;
			}

			CObject::SetPause(false);			//�|�[�Y���ł͂Ȃ���Ԃɂ���
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
			{//null�`�F�b�N
				m_pButton[nCnt]->Update();

				if (m_pButton[nCnt]->GetTriggerState())
				{//�����ꂽ��

					CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_CLICK);		//�N���b�N�T�E���h���Đ�����

																						//�ǂ�ȃ{�^���������ꂽ�ɂ���čX�V����
					switch (nCnt)
					{
					case button_continue:

					{//�R���e�B�j���[�{�^����������A�|�[�Y���j���[��j������
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

					{//�^�C�g���ɖ߂�{�^����������A�^�C�g����ʂɐ؂�ւ���

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