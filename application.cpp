//=============================================================================
//
// application.cpp
// Author : Ricci Alex
//
//=============================================================================

//�C���N���[�h�t�@�C��
#include "application.h"
#include "rendering.h"
#include "object.h"
#include "object2D.h"
#include "input.h"
#include "inputKeyboard.h"
#include "inputMouse.h"
#include"player.h"
#include "mode.h"
#include "title.h"
#include "gameScylla.h"
#include "gameThanatos.h"
#include "stageSelection.h"
#include "gamePride.h"
#include "gameEnvy.h"
#include "gameGreed.h"
#include "score.h"
#include "result.h"
#include "sound.h"
#include "ranking.h"
#include "rankingMode.h"
#include "gameGluttony.h"
#include "gameSloth.h"
#include "modeWrath.h"
#include "fade.h"
#include "hitbox.h"
#include "tutorial.h"

//�ÓI�����o�[�ϐ��̐錾
HWND CApplication::m_hWnd;
CRenderer* CApplication::m_pRenderer = nullptr;			//�����f�B���O�C���X�^���X�ւ̃|�C���^
CInput* CApplication::m_pInput[2] = {};					//�C���v�b�g�C���X�^���X�ւ̃|�C���^
CInputMouse* CApplication::m_pMouse = nullptr;			//�}�E�X�C���X�^���X�ւ̃|�C���^
CApplication::Mode CApplication::m_mode = CApplication::Mode_Title;
CMode* CApplication::m_pMode = nullptr;
CScore* CApplication::m_pScore = nullptr;
CSound* CApplication::m_pSound = nullptr;
CRanking* CApplication::m_pRanking = nullptr;
CFade* CApplication::m_pFade = nullptr;
bool CApplication::m_bFade = false;
int CApplication::m_nDifficulty = 1;

//�R���X�g���N�^
CApplication::CApplication()
{
	
}

//�f�X�g���N�^
CApplication::~CApplication()
{
	
}

//����������
HRESULT CApplication::Init(HINSTANCE hInstance, HWND hWnd)
{
	m_hWnd = hWnd;

	//�����f�B���O�C���X�^���X�̐�������
	if (m_pRenderer == nullptr)
	{//�|�C���^��null�ł͂Ȃ�������
		m_pRenderer = new CRenderer;
	}

	//�����f�B���O�C���X�^���X�̏���������
	if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
	{
		return -1;
	}

	//�e�N�X�`���S�������[�h����
	CObject_2D::LoadTextures();

	//���[�h�̐���
	m_pMode = CTitle::Create();

	//�L�[�{�[�h�C���X�^���X�̐�������
	m_pInput[0] = new CInputKeyboard;

	//�L�[�{�[�h�̏���������
	if (FAILED(m_pInput[0]->Init(hInstance, hWnd, GUID_SysKeyboard)))
	{
		return -1;
	}

	//�}�E�X�C���v�b�g�̐���
	m_pMouse = new CInputMouse;

	//�L�[�{�[�h�̏���������
	if (FAILED(m_pMouse->Init(hInstance, hWnd, GUID_SysMouse)))
	{
		return -1;
	}

	//�X�R�A�̐���
	m_pScore = CScore::Create();

	//�����L���O�̐���
	m_pRanking = CRanking::Create();

	//�T�E���h�̐���
	m_pSound = CSound::Create(hWnd);

	if (m_pSound != nullptr)
	{//�����o������ABGM���Đ�����

		m_pSound->Play(CSound::SOUND_LABEL_BGM_TITLE);
	}

	//�t�F�[�h�𐶐�����
	m_pFade = CFade::Create();		
	m_bFade = true;

	return S_OK;
}

//�I������
void CApplication::Uninit(void)
{
	//�e�N�X�`���S���̔j��
	CObject_2D::DestroyLoadedTextures();

	//�����f�B���O�C���X�^���X�̔j��
	if (m_pRenderer != nullptr)
	{//null�`�F�b�N

		m_pRenderer->Uninit();		//�I������
		delete m_pRenderer;			//���������������
		m_pRenderer = nullptr;		//�|�C���^��null�ɂ���
	}

	//�C���v�b�g�f�o�C�X�̔j��
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pInput[nCnt] != nullptr)
		{//null�`�F�b�N

			m_pInput[nCnt]->Uninit();	//�I������
			delete m_pInput[nCnt];		//���������������
			m_pInput[nCnt] = nullptr;	//�|�C���^��null�ɂ���
		}
	}

	//�}�E�X�̔j������
	if (m_pMouse != nullptr)
	{//null�`�F�b�N

		m_pMouse->Uninit();			//�I������
		delete m_pMouse;			//���������������
		m_pMouse = nullptr;			//�|�C���^��null�ɂ���
	}

	//�X�R�A�̔j������
	if (m_pScore != nullptr)
	{//null�`�F�b�N

		m_pScore->Uninit();			//�I������
		delete m_pScore;			//���������������
		m_pScore = nullptr;			//�|�C���^��null�ɂ���
	}

	//�����L���O�̔j������
	if (m_pRanking != nullptr)
	{//null�`�F�b�N

		m_pRanking->Uninit();		//�I������
		delete m_pRanking;			//���������������
		m_pRanking = nullptr;		//�|�C���^��null�ɂ���
	}

	//�T�E���h�̔j������
	if (m_pSound != nullptr)
	{//null�`�F�b�N

		m_pSound->Uninit();			//�I������
		delete m_pSound;			//���������������
		m_pSound = nullptr;			//�|�C���^��null�ɂ���
	}

	//�t�F�[�h�̔j������
	if (m_pFade != nullptr)
	{//null�`�F�b�N

		m_pFade->Uninit();			//�I������
		delete m_pFade;				//���������������
		m_pFade = nullptr;			//�|�C���^��null�ɂ���
	}

	//�I�u�W�F�N�g�S�̂̏I������
	CObject::ReleaseAll();
}

//�X�V����
void CApplication::Update(void)
{
	//�C���v�b�g�f�o�C�X�̍X�V����
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pInput[nCnt] != nullptr)
		{//null�`�F�b�N
			m_pInput[nCnt]->Update();
		}
	}

	//�����f�B���O�̍X�V����
	if (m_pRenderer != nullptr)
	{//null�`�F�b�N
		m_pRenderer->Update();
	}

	//�t�F�[�h�̍X�V����
	if (m_pFade != nullptr)
	{//null�`�F�b�N
		m_pFade->Update();
	}

	//���[�h�̍X�V����
	if (m_pMode != nullptr)
	{//null�`�F�b�N
		m_pMode->Update();
	}
}

//�`�揈��
void CApplication::Draw(void)
{
	//�����f�B���O�̕`�揈��
	if (m_pRenderer != nullptr)
	{//null�`�F�b�N

		m_pRenderer->Draw();
	}
}

//�����f�B���O�ւ̃|�C���^�̎擾����
CRenderer* CApplication::GetRenderer(void)
{
	return m_pRenderer;
}

//�}�E�X�̎擾����
CInputMouse* CApplication::GetMouse(void)
{
	return m_pMouse;
}

//�E�C���h�E�̎擾����
HWND CApplication::GetWindow(void)
{
	return m_hWnd;
}

//��Փx�̐ݒ菈��
void CApplication::SetDifficulty(const int difficulty)
{
	m_pScore->SetDifficulty(difficulty);
	m_nDifficulty = difficulty;
}

//��Փx�̎擾����
const int CApplication::GetDifficulty(void)
{
	return m_nDifficulty;
}

//�v���C���[�̎c�����̗͂̐ݒ菈��
void CApplication::SetRemainingLife(const int nLife)
{
	m_pScore->SetLife(nLife);
}

//���[�h�̎擾����
CApplication::Mode CApplication::GetMode(void)
{
	return m_mode;
}

//���[�h�̐ݒ菈��
void CApplication::SetMode(Mode mode)
{
	//���݂̃��[�h��j������
	if (m_pMode != nullptr)
	{//null�`�F�b�N
		m_pMode->Uninit();		//�I������
		delete m_pMode;			//���������������
		m_pMode = nullptr;		//�|�C���^��null�ɂ���
	}

	CObject::ReleaseAll();		//�S���̃I�u�W�F�N�g�̔j������
	CHitbox::ReleaseAll();		//�S���̃q�b�g�{�b�N�X�̔j������

	//�T�E���h���~����
	if (m_pSound != nullptr)
	{//null�`�F�b�N
		m_pSound->Stop();
	}

	Sleep(150);

	switch (mode)
	{
	case CApplication::Mode_Title:

	{//�^�C�g��

		m_pMode = CTitle::Create();			//�V�������[�h�̐���
		
		if (m_pMode != nullptr)
		{//null�`�F�b�N
			m_mode = mode;
		}

		//�I�����ꂽ�X�e�[�W�̐ݒ�
		if (m_pRanking != nullptr)
		{//null�`�F�b�N
			m_pRanking->SetStage(CStageSelection::stage_Scylla);
		}

		//BGM���Đ�����
		if (m_pSound != nullptr)
		{//null�`�F�b�N
			m_pSound->Play(CSound::SOUND_LABEL_BGM_TITLE);
		}
	}

		break;

	case CApplication::Mode_StageSelection:

	{//�X�e�[�W�I�����

		m_pMode = CStageSelection::Create();			//�V�������[�h�̐���

		if (m_pMode != nullptr)
		{//null�`�F�b�N
			m_mode = mode;
		}

		//�I�����ꂽ�X�e�[�W�̐ݒ�
		if (m_pRanking != nullptr)
		{//null�`�F�b�N
			m_pRanking->SetStage(CStageSelection::stage_Scylla);
		}

		//BGM���Đ�����
		if (m_pSound != nullptr)
		{//null�`�F�b�N
			m_pSound->Play(CSound::SOUND_LABEL_BGM_STAGE_SELECTION);
		}
	}

		break;

	case CApplication::Mode_Tutorial:			

	{//�`���[�g���A��

		m_pMode = CTutorial::Create();				//�V�������[�h�̐���

		if (m_pMode != nullptr)
		{//null�`�F�b�N
			m_mode = mode;
		}

		//�I�����ꂽ�X�e�[�W�̐ݒ�
		if (m_pRanking != nullptr)
		{//null�`�F�b�N
			m_pRanking->SetStage(CStageSelection::stage_Scylla);
		}

		//BGM���Đ�����
		if (m_pSound != nullptr)
		{//null�`�F�b�N
			m_pSound->Play(CSound::SOUND_LABEL_BGM_STAGE_SELECTION);
		}
	}

	break;

	case CApplication::Mode_Game:

	{
		
	}

		break;

	case CApplication::Mode_Game_Scylla:

	{
		m_pMode = CGameScylla::Create();				//�V�������[�h�̐���

		if (m_pMode != nullptr)
		{//null�`�F�b�N
			m_mode = mode;
		}

		//�X�R�A���N���A���Ă���A�x�[�X�X�R�A��ݒ肷��
		if (m_pScore != nullptr)
		{//null�`�F�b�N
			m_pScore->Clear();
			m_pScore->SetBaseScore(200000);
		}

		//�I�����ꂽ�X�e�[�W�̐ݒ�
		if (m_pRanking != nullptr)
		{//null�`�F�b�N
			m_pRanking->SetStage(CStageSelection::stage_Scylla);
		}

		//BGM���Đ�����
		if (m_pSound != nullptr)
		{//null�`�F�b�N
			m_pSound->Play(CSound::SOUND_LABEL_BGM_GAME);
		}
	}

		break;

	case CApplication::Mode_Game_Thanatos:

	{
		m_pMode = CGameThanatos::Create();				//�V�������[�h�̐���

		if (m_pMode != nullptr)
		{//null�`�F�b�N
			m_mode = mode;
		}

		//�X�R�A���N���A���Ă���A�x�[�X�X�R�A��ݒ肷��
		if (m_pScore != nullptr)
		{//null�`�F�b�N
			m_pScore->Clear();
			m_pScore->SetBaseScore(300000);
		}

		//�I�����ꂽ�X�e�[�W�̐ݒ�
		if (m_pRanking != nullptr)
		{//null�`�F�b�N
			m_pRanking->SetStage(CStageSelection::stage_Thanatos);
		}

		//BGM���Đ�����
		if (m_pSound != nullptr)
		{//null�`�F�b�N
			m_pSound->Play(CSound::SOUND_LABEL_BGM_THANATOS);
		}
	}

	break;

	case CApplication::Mode_Game_Pride:

	{
		m_pMode = CGamePride::Create();					//�V�������[�h�̐���

		if (m_pMode != nullptr)
		{//null�`�F�b�N
			m_mode = mode;
		}

		//�X�R�A���N���A���Ă���A�x�[�X�X�R�A��ݒ肷��
		if (m_pScore != nullptr)
		{//null�`�F�b�N
			m_pScore->Clear();
			m_pScore->SetBaseScore(150000);
		}

		//�I�����ꂽ�X�e�[�W�̐ݒ�
		if (m_pRanking != nullptr)
		{//null�`�F�b�N
			m_pRanking->SetStage(CStageSelection::stage_Pride);
		}

		//BGM���Đ�����
		if (m_pSound != nullptr)
		{//null�`�F�b�N
			m_pSound->Play(CSound::SOUND_LABEL_BGM_GAME);
		}
	}

	break;

	case CApplication::Mode_Game_Envy:

	{
		m_pMode = CGameEnvy::Create();					//�V�������[�h�̐���

		if (m_pMode != nullptr)
		{//null�`�F�b�N
			m_mode = mode;
		}

		//�X�R�A���N���A���Ă���A�x�[�X�X�R�A��ݒ肷��
		if (m_pScore != nullptr)
		{//null�`�F�b�N
			m_pScore->Clear();
			m_pScore->SetBaseScore(500000);
		}

		//�I�����ꂽ�X�e�[�W�̐ݒ�
		if (m_pRanking != nullptr)
		{//null�`�F�b�N
			m_pRanking->SetStage(CStageSelection::stage_Envy);
		}

		//BGM���Đ�����
		if (m_pSound != nullptr)
		{//null�`�F�b�N
			m_pSound->Play(CSound::SOUND_LABEL_BGM_GAME);
		}
	}

	break;

	case CApplication::Mode_Game_Wrath:

	{
		m_pMode = CGameWrath::Create();					//�V�������[�h�̐���

		if (m_pMode != nullptr)
		{//null�`�F�b�N
			m_mode = mode;
		}

		//�X�R�A���N���A���Ă���A�x�[�X�X�R�A��ݒ肷��
		if (m_pScore != nullptr)
		{//null�`�F�b�N
			m_pScore->Clear();
			m_pScore->SetBaseScore(500000);
		}

		//�I�����ꂽ�X�e�[�W�̐ݒ�
		if (m_pRanking != nullptr)
		{//null�`�F�b�N
			m_pRanking->SetStage(CStageSelection::stage_Wrath);
		}

		//BGM���Đ�����
		if (m_pSound != nullptr)
		{//null�`�F�b�N
			m_pSound->Play(CSound::SOUND_LABEL_BGM_GAME);
		}
	}

	break;

	case CApplication::Mode_Game_Sloth:

	{
		m_pMode = CGameSloth::Create();					//�V�������[�h�̐���

		if (m_pMode != nullptr)
		{//null�`�F�b�N
			m_mode = mode;
		}

		//�X�R�A���N���A���Ă���A�x�[�X�X�R�A��ݒ肷��
		if (m_pScore != nullptr)
		{//null�`�F�b�N
			m_pScore->Clear();
			m_pScore->SetBaseScore(250000);
		}

		//�I�����ꂽ�X�e�[�W�̐ݒ�
		if (m_pRanking != nullptr)
		{//null�`�F�b�N
			m_pRanking->SetStage(CStageSelection::stage_Sloth);
		}

		//BGM���Đ�����
		if (m_pSound != nullptr)
		{//null�`�F�b�N
			m_pSound->Play(CSound::SOUND_LABEL_BGM_GAME);
		}
	}

	break;

	case CApplication::Mode_Game_Greed:

	{
		m_pMode = CGameGreed::Create();					//�V�������[�h�̐���

		if (m_pMode != nullptr)
		{//null�`�F�b�N
			m_mode = mode;
		}

		//�X�R�A���N���A���Ă���A�x�[�X�X�R�A��ݒ肷��
		if (m_pScore != nullptr)
		{//null�`�F�b�N
			m_pScore->Clear();
			m_pScore->SetBaseScore(350000);
		}

		//�I�����ꂽ�X�e�[�W�̐ݒ�
		if (m_pRanking != nullptr)
		{//null�`�F�b�N
			m_pRanking->SetStage(CStageSelection::stage_Greed);
		}

		//BGM���Đ�����
		if (m_pSound != nullptr)
		{//null�`�F�b�N
			m_pSound->Play(CSound::SOUND_LABEL_BGM_GAME);
		}
	}

	break;

	case CApplication::Mode_Game_Gluttony:

	{
		m_pMode = CGameGluttony::Create();					//�V�������[�h�̐���

		if (m_pMode != nullptr)
		{//null�`�F�b�N
			m_mode = mode;
		}

		//�X�R�A���N���A���Ă���A�x�[�X�X�R�A��ݒ肷��
		if (m_pScore != nullptr)
		{//null�`�F�b�N
			m_pScore->Clear();
			m_pScore->SetBaseScore(250000);
		}

		//�I�����ꂽ�X�e�[�W�̐ݒ�
		if (m_pRanking != nullptr)
		{//null�`�F�b�N
			m_pRanking->SetStage(CStageSelection::stage_Gluttony);
		}

		//BGM���Đ�����
		if (m_pSound != nullptr)
		{//null�`�F�b�N
			m_pSound->Play(CSound::SOUND_LABEL_BGM_GAME);
		}
	}

	break;

	case CApplication::Mode_Result:

	{
		int nScore = m_pScore->GetFinalScore();				//�X�R�A�̎擾����

		//�����L���O�̍X�V
		if (m_pRanking != nullptr)
		{//null�`�F�b�N
			m_pRanking->SetRanking((CStageSelection::stage)m_pRanking->GetStage(), nScore);
		}

		m_pMode = CResult::Create(nScore);					//�V�������[�h�̐���

		if (m_pMode != nullptr)
		{//null�`�F�b�N
			m_mode = mode;
		}
	}

		break;

	case CApplication::Mode_Ranking:

	{
		int stage = 0;

		//�X�e�[�W�̐ݒ�
		if (m_pRanking != nullptr)
		{//null�`�F�b�N
			stage = m_pRanking->GetStage();
		}

		m_pMode = CRankingMode::Create(stage);				//�V�������[�h�̐���

		if (m_pMode != nullptr)
		{//null�`�F�b�N
			m_mode = mode;
		}
	}

		break;

	default:

		break;
	}
}

//�T�E���h�̎擾����
CSound* CApplication::GetSound(void)
{
	return m_pSound;
}

//�����L���O�̎擾����
CRanking* CApplication::GetRanking(void)
{
	return m_pRanking;
}

//�t�F�[�h�̐ݒ菈��
void CApplication::SetFade(CApplication::Mode mode)
{
	if (m_pFade != nullptr)
	{
		m_pFade->SetFadeOut(mode);
	}
}

//�t�F�[�h��Ԃ̐ݒ菈��
void CApplication::SetFade(const bool bFade)
{
	m_bFade = bFade;
}

//�t�F�[�h��Ԃ̐ݒ菈��
const bool CApplication::GetFade(void)
{
	return m_bFade;
}