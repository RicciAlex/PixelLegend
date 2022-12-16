//=============================================================================
//
// title.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "title.h"
#include "bg.h"
#include "inputKeyboard.h"
#include "inputMouse.h"
#include "application.h"
#include "button.h"
#include "sound.h"
#include "skullCursor.h"
#include "Letter.h"

//=============================================================================
//							�ÓI�ϐ��̏�����
//=============================================================================
D3DXCOLOR CTitle::targetColors[CTitle::TargetCol_Max] =				//�^�C�g���A�j���[�V�����̐F
{
	{1.0f, 0.0f, 0.0f, 1.0f},			//��
	{0.0f, 1.0f, 0.0f, 1.0f},			//��
	{0.0f, 0.0f, 1.0f, 1.0f},			//��
	{1.0f, 1.0f, 0.0f, 1.0f},			//��
	{1.0f, 0.0f, 1.0f, 1.0f},			//�}�[���^
	{0.0f, 1.0f, 1.0f, 1.0f}			//�V�A��
};

//�R���X�g���N�^
CTitle::CTitle()
{
	//�����o�[�ϐ����N���A����
	m_pBg = nullptr;

	for (int nCnt = 0; nCnt < button_max; nCnt++)
	{
		m_pButton[nCnt] = nullptr;
	}
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_pCursor[nCnt] = nullptr;
	}
	for (int nCnt = 0; nCnt < 16; nCnt++)
	{
		m_pTitle[nCnt] = nullptr;
	}

	m_TargetCol = TargetCol_Red;
	m_changeCol = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_nChangeFrame = 0;


	//m_pTitleMenu = nullptr;
}

//�f�X�g���N�^
CTitle::~CTitle()
{

}

//����������
HRESULT CTitle::Init(void)
{
	//�����o�[�ϐ�������������
	m_pBg = nullptr;

	for (int nCnt = 0; nCnt < button_max; nCnt++)
	{
		m_pButton[nCnt] = nullptr;
	}
	for (int nCnt = 0; nCnt < 16; nCnt++)
	{
		m_pTitle[nCnt] = nullptr;
	}

	m_TargetCol = TargetCol_Red;
	m_changeCol = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_nChangeFrame = 0;

	return S_OK;
}

//�I������
void CTitle::Uninit(void)
{
	//�w�i�̔j��
	if (m_pBg != nullptr)
	{//null�`�F�b�N
		m_pBg->Release();					//���������������
		m_pBg = nullptr;					//�|�C���^��null�ɂ���
	}

	//�{�^���̔j��
	for (int nCnt = 0; nCnt < button_max; nCnt++)
	{
		if (m_pButton[nCnt] != nullptr)
		{//null�`�F�b�N
			m_pButton[nCnt]->Uninit();		//���������������
			m_pButton[nCnt] = nullptr;		//�|�C���^��null�ɂ���
		}
	}

	//�J�[�\���̔j��
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pCursor[nCnt] != nullptr)
		{//null�`�F�b�N
			m_pCursor[nCnt]->Uninit();		//���������������
			m_pCursor[nCnt] = nullptr;		//�|�C���^��null�ɂ���
		}
	}

	//�^�C�g���̕����̔j��
	for (int nCnt = 0; nCnt < 16; nCnt++)
	{
		if (m_pTitle[nCnt] != nullptr)
		{//null�`�F�b�N
			m_pTitle[nCnt]->Release();		//���������������
			m_pTitle[nCnt] = nullptr;		//�|�C���^��null�ɂ���
		}
	}
}

//�X�V����
void CTitle::Update(void)
{
	UpdateTitleColor();						//�^�C�g���̐F�̍X�V����

	//�J�[�\���̍X�V����
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pCursor[nCnt] != nullptr)
		{//null�`�F�b�N
			m_pCursor[nCnt]->Update();
		}
	}

	//�{�^���̍X�V����
	if (m_pButton[button_play] != nullptr)
	{//�v���C�{�^����null�`�F�b�N

		m_pButton[button_play]->Update();			//�v���C�{�^���̍X�V����

		if (m_pButton[button_play]->GetTriggerState())
		{//�����ꂽ��

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_CLICK);		//�N���b�N�̃T�E���h���Đ�����

			CApplication::SetFade(CApplication::Mode_StageSelection);			//�X�e�[�W�I����ʂɈړ�
			return;		
		}
	}
	if (m_pButton[button_tutorial] != nullptr)
	{//�`���[�g���A���{�^����null�`�F�b�N

		m_pButton[button_tutorial]->Update();		//�`���[�g���A���{�^���̍X�V����

		if (m_pButton[button_tutorial]->GetTriggerState())
		{//�����ꂽ��

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_CLICK);		//�N���b�N�̃T�E���h���Đ�����

			CApplication::SetFade(CApplication::Mode_Tutorial);					//�`���[�g���A����ʂɈړ�
			return;
		}
	}
	if (m_pButton[button_leaderboard] != nullptr)
	{//�����L���O�{�^����null�`�F�b�N

		m_pButton[button_leaderboard]->Update();	//�����L���O�{�^���̍X�V����

		if (m_pButton[button_leaderboard]->GetTriggerState())
		{//�����ꂽ��

			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_CLICK);		//�N���b�N�̃T�E���h���Đ�����

			CApplication::SetFade(CApplication::Mode_Ranking);					//�����L���O��ʂɈړ�
			return;
		}
	}
}



//=============================================================================
//
//								�ÓI�֐�
//
//=============================================================================



//��������
CTitle* CTitle::Create(void)
{
	CTitle* pTitle = new CTitle;			//�C���X�^���X�𐶐�����

	if (FAILED(pTitle->Init()))
	{//����������
		return nullptr;
	}

	pTitle->m_pBg = CBg::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));		//�^�C�g���̐���

	if (pTitle->m_pBg)
	{//�����o������A�K�v�ȃp�����[�^�̐ݒ�

		pTitle->m_pBg->SetTexture(CObject::TextureMenuBg);
		pTitle->m_pBg->SetTextureParameter(1, 1, 1, INT_MAX);
		pTitle->m_pBg->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		pTitle->m_pCursor[0] = CSkullCursor::Create(D3DXVECTOR3(0.0f, (float)SCREEN_HEIGHT * 0.5f, 0.0f));
		pTitle->m_pCursor[1] = CSkullCursor::Create(D3DXVECTOR3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT * 0.5f, 0.0f));
	}

	char aStr[16] = "pixel legend";			//�^�C�g���̕�����

	int Lenght = strlen(aStr);

	for (int nCnt = 0; nCnt < Lenght; nCnt++)
	{
		//�^�C�g���̕����̐���
		pTitle->m_pTitle[nCnt] = CLetter::Create(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f - 75.0f * (Lenght * 0.5f) + (80.0f * nCnt), (float)SCREEN_HEIGHT * 0.25f, 0.0f), D3DXVECTOR2(40.0f, 40.0f), aStr[nCnt]);
		
		if (pTitle->m_pTitle[nCnt] != nullptr)
		{//�����o������A�F�ƃv���C�I���e�B�̐ݒ�

			pTitle->m_pTitle[nCnt]->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			pTitle->m_pTitle[nCnt]->SetPriority(2);
		}
	}

	pTitle->m_TargetCol = TargetCol_Yellow;		//�ړI�̐F�̐ݒ�

	char aText[button_max][24] = { { "play" }, { "tutorial" },{ "leaderboard" } };			//�{�^���̕�����

	for (int nCnt = 0; nCnt < button_max; nCnt++)
	{
		//�{�^���̐���
		pTitle->m_pButton[nCnt] = CButton::Create(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f + 50.0f * 2.5f * nCnt, 0.0f), D3DXVECTOR2(300.0f, 55.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), aText[nCnt]);
	}

	return pTitle;				//���������C���X�^���X��Ԃ�
}



//=============================================================================
//
//							�v���C�x�[�g�֐�
//
//=============================================================================


//�^�C�g���̐F�̍X�V����
void CTitle::UpdateTitleColor(void)
{
	m_nChangeFrame--;				//�A�j���[�V�����J�E���^�[���f�N�������g����

	if (m_nChangeFrame <= 0)
	{//�A�j���[�V�����J�E���^�[��0�ȉ��ɂȂ�����

		m_nChangeFrame = 120;		//120�ɖ߂�

		//���݂̐F�ɂ���āA���̖ړI�̐F��ݒ肷��
		switch (m_TargetCol)
		{
		case CTitle::TargetCol_Red:

			m_TargetCol = TargetCol_Yellow;

			break;

		case CTitle::TargetCol_Green:

			m_TargetCol = TargetCol_Cyan;

			break;

		case CTitle::TargetCol_Blue:

			m_TargetCol = TargetCol_Magenta;

			break;

		case CTitle::TargetCol_Yellow:

			m_TargetCol = TargetCol_Green;

			break;

		case CTitle::TargetCol_Magenta:

			m_TargetCol = TargetCol_Red;

			break;

		case CTitle::TargetCol_Cyan:

			m_TargetCol = TargetCol_Blue;

			break;
		
		default:
			break;
		}

		m_changeCol = targetColors[m_TargetCol] - m_pTitle[0]->GetColor();
		m_changeCol.r /= 120.0f;
		m_changeCol.g /= 120.0f;
		m_changeCol.b /= 120.0f;
		m_changeCol.a = 0.0f;
	}
	else
	{//�A�j���[�V�������܂��r����������

		D3DXCOLOR col = m_pTitle[0]->GetColor();		//���݂̐F���擾����

		col += m_changeCol;			//�F���X�V����

		//�F��ݒ肷��
		for (int nCnt = 0; nCnt < 16; nCnt++)
		{
			if (m_pTitle[nCnt] != nullptr)
			{//null�`�F�b�N

				m_pTitle[nCnt]->SetColor(col);
			}
		}
	}

}