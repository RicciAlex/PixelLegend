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
	{//null�`�F�b�N
		m_pBg->Release();					//���������������
		m_pBg = nullptr;					//�|�C���^��null�ɂ���
	}
	if (m_pBackBg != nullptr)
	{//null�`�F�b�N
		m_pBackBg->Release();				//���������������
		m_pBackBg = nullptr;				//�|�C���^��null�ɂ���
	}
	if (m_pPlayer != nullptr)
	{//null�`�F�b�N
		m_pPlayer->Release();				//���������������
		m_pPlayer = nullptr;				//�|�C���^��null�ɂ���
	}

	if (m_pEnemy != nullptr)
	{//null�`�F�b�N
		m_pEnemy->Release();				//���������������
		m_pEnemy = nullptr;					//�|�C���^��null�ɂ���
	}

	if (m_pMenuBg != nullptr)
	{//null�`�F�b�N
		m_pMenuBg->Release();				//���������������
		m_pMenuBg = nullptr;				//�|�C���^��null�ɂ���
	}
	for (int nCnt = 0; nCnt < button_max; nCnt++)
	{
		if (m_pButton[nCnt] != nullptr)
		{//null�`�F�b�N
			m_pButton[nCnt]->Uninit();		//���������������
			m_pButton[nCnt] = nullptr;		//�|�C���^��null�ɂ���
		}
	}
	if (m_pObj != nullptr)
	{//null�`�F�b�N
		m_pObj->Release();		//���������������
		m_pObj = nullptr;		//�|�C���^��null�ɂ���
	}
}

//�X�V����
void CGameWrath::Update(void)
{
	//�{�X�̍X�V����
	if (m_pEnemy != nullptr)
	{//null�`�F�b�N

		if (m_pEnemy->GetEnd())
		{//�G������ł��邩�ǂ����m�F����

			if (m_pPlayer != nullptr)
			{//�v���C���[��null�ł͂Ȃ�������

				CApplication::SetRemainingLife(m_pPlayer->GetLife());		//�v���C���[�̎c�����̗͂̎擾
			}

			CApplication::SetFade(CApplication::Mode_Result);				//���[�h��؂�ւ���
		}
		else
		{//�G���܂�����ł��Ȃ�������

			//�w�i�̍X�V����
			if (m_pBackBg != nullptr)
			{//null�`�F�b�N

				m_nCntBg++;			//�A�j���[�V�����J�E���^�[���C���N�������g����

				D3DXCOLOR col = m_pBackBg->GetColor();		//���݂̐F�̎擾

				//�F�̍X�V
				col.r += m_fColAnim;
				col.g += m_fColAnim;

				if (col.r >= 1.0f || col.r <= 0.7f)
				{//�͈͂��o����A�A�j���[�V�����p�̕ϐ����t�ɂ���

					m_fColAnim *= -1.0f;
				}

				m_pBackBg->SetColor(col);			//�F�̐ݒ�
			}

			UpdateMenu();		//���j���[�̍X�V����
		}
	}

	//�v���C���[�̍X�V
	if (m_pPlayer != nullptr)
	{//null�`�F�b�N

		if (m_pPlayer->GetEnd())
		{//�v���C���[�����񂾂�

			CApplication::SetFade(CApplication::Mode_Result);		//�t�F�[�h�̐ݒ菈��
		}
	}
}



//=============================================================================
//
//									�ÓI�֐�
//
//=============================================================================



//��������
CGameWrath* CGameWrath::Create(void)
{
	CGameWrath* pGame = new CGameWrath;				//�X�e�[�W��ʂ̐���

	if (FAILED(pGame->Init()))
	{//����������
		return nullptr;
	}

	//�w�i�̐���
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

	return pGame;				//���������C���X�^���X��Ԃ�
}


//=============================================================================
//
//							�v���C�x�[�g�֐�
//
//=============================================================================



//���j���[�̍X�V����
void CGameWrath::UpdateMenu(void)
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