//=============================================================================
//
// rankingMode.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "rankingMode.h"
#include "Letter.h"
#include "button.h"
#include "inputKeyboard.h"
#include "application.h"
#include "bg.h"
#include "ranking.h"
#include "sound.h"

//�R���X�g���N�^
CRankingMode::CRankingMode()
{
	//�����o�[�ϐ����N���A����
	m_nSelectedStage = 0;
	m_nCntDelay = 0;

	for (int nCnt = 0; nCnt < 24; nCnt++)
	{
		m_pStageName[nCnt] = nullptr;
	}

	for (int nCnt2 = 0; nCnt2 < MaxRank; nCnt2++)
	{
		for (int nCnt = 0; nCnt < MaxDigit; nCnt++)
		{
			m_pRank[nCnt2][nCnt] = nullptr;
		}
	}

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_pLateralIcon[nCnt] = nullptr;
		m_pLateralButton[nCnt] = nullptr;
	}

	m_pBg = nullptr;
}

//�f�X�g���N�^
CRankingMode::~CRankingMode()
{

}

//����������
HRESULT CRankingMode::Init(void)
{
	//�����o�[�ϐ�������������
	m_nSelectedStage = 0;
	m_nCntDelay = 0;

	for (int nCnt = 0; nCnt < 24; nCnt++)
	{
		m_pStageName[nCnt] = nullptr;
	}

	for (int nCnt2 = 0; nCnt2 < MaxRank; nCnt2++)
	{
		for (int nCnt = 0; nCnt < MaxDigit; nCnt++)
		{
			m_pRank[nCnt2][nCnt] = nullptr;
		}
	}

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		m_pLateralIcon[nCnt] = nullptr;
		m_pLateralButton[nCnt] = nullptr;
	}

	m_pBg = nullptr;

	//UI�̐���
	CObject_2D* pObj = CObject_2D::Create();

	//�����o������A�K�v�ȃp�����[�^��ݒ肷��
	if (pObj)
	{
		pObj->SetPos(D3DXVECTOR3(1000.0f, 600.0f, 0.0f));
		pObj->SetSize(D3DXVECTOR2(100.0f, 65.4f));
		pObj->SetTexture(CObject::TexturePressSpaceIcon);
		pObj->SetTextureParameter(2, 2, 1, 30);
		pObj->SetStartingRot(D3DX_PI * 0.5f);
	}

	return S_OK;
}

//�I������
void CRankingMode::Uninit(void)
{
	//�X�e�[�W�̖��O�̔j��
	for (int nCnt = 0; nCnt < 24; nCnt++)
	{
		if (m_pStageName[nCnt] != nullptr)
		{//null�`�F�b�N
			m_pStageName[nCnt]->Release();			//���������������
			m_pStageName[nCnt] = nullptr;			//�|�C���^��null�ɂ���
		}
	}

	//�X�R�A�̔j��
	for (int nCnt2 = 0; nCnt2 < MaxRank; nCnt2++)
	{
		for (int nCnt = 0; nCnt < MaxDigit; nCnt++)
		{
			if (m_pRank[nCnt2][nCnt] != nullptr)
			{//null�`�F�b�N
				m_pRank[nCnt2][nCnt]->Release();	//���������������
				m_pRank[nCnt2][nCnt] = nullptr;		//�|�C���^��null�ɂ���
			}
		}
	}

	//�{�^����UI�̔j��
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pLateralIcon[nCnt] != nullptr)
		{//null�`�F�b�N
			m_pLateralIcon[nCnt]->Release();		//���������������	
			m_pLateralIcon[nCnt] = nullptr;			//�|�C���^��null�ɂ���
		}

		if (m_pLateralButton[nCnt] != nullptr)
		{//null�`�F�b�N
			m_pLateralButton[nCnt]->Uninit();		//���������������
			m_pLateralButton[nCnt] = nullptr;		//�|�C���^��null�ɂ���
		}
	}

	//�w�i�̔j��
	if (m_pBg != nullptr)
	{//null�`�F�b�N
		m_pBg->Release();			//���������������
		m_pBg = nullptr;			//�|�C���^��null�ɂ���
	}

}

//�X�V����
void CRankingMode::Update(void)
{
	if (m_nCntDelay >= 30)
	{//�t�F�[�h���ł͂Ȃ�������

		bool bDx = false;
		bool bSx = false;

		//=========================================================================================================================
		//								�{�^�����X�V���āA�����ꂽ���ǂ������擾����
		if (m_pLateralButton[0] != nullptr)
		{
			m_pLateralButton[0]->Update();
			bSx = m_pLateralButton[0]->GetTriggerState();
		}
		if (m_pLateralButton[1] != nullptr)
		{
			m_pLateralButton[1]->Update();
			bDx = m_pLateralButton[1]->GetTriggerState();
		}
		//=========================================================================================================================
		//=========================================================================================================================
		//				�E/���A���[�{�^���AA/D�{�^���A���͍��E�̃{�^���������ꂽ��A�I������Ă����ʂ�ς���
		if (CInputKeyboard::GetKeyboardTrigger(DIK_RIGHT) || CInputKeyboard::GetKeyboardTrigger(DIK_D) || bDx)
		{
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_CLICK);

			m_nSelectedStage++;
			m_nCntDelay = 0;

			if (m_nSelectedStage >= CStageSelection::stage_Max)
			{
				m_nSelectedStage = 0;
			}

			UpdateMenu();

		}
		else if (CInputKeyboard::GetKeyboardTrigger(DIK_LEFT) || CInputKeyboard::GetKeyboardTrigger(DIK_A) || bSx)
		{
			CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_CLICK);

			m_nSelectedStage--;
			m_nCntDelay = 0;

			if (m_nSelectedStage < 0)
			{
				m_nSelectedStage = CStageSelection::stage_Max - 1;
			}

			UpdateMenu();
		}
		//=========================================================================================================================
	}
	else
	{//�t�F�[�h����������A�J�E���^�[���C���N�������g����
		m_nCntDelay++;
	}

	//�X�y�[�X�L�[�A���̓G���^�[�L�[�������ꂽ��A�^�C�g����ʂɐ؂�ւ���
	if (CInputKeyboard::GetKeyboardTrigger(DIK_SPACE) || CInputKeyboard::GetKeyboardTrigger(DIK_RETURN))
	{
		CApplication::SetFade(CApplication::Mode_Title);
	}
}



//=============================================================================
//
//								�ÓI�֐�
//
//=============================================================================



//��������
CRankingMode* CRankingMode::Create(const int nStage)
{
	CRankingMode* pStage = new CRankingMode;			//�C���X�^���X�𐶐�����

	if (FAILED(pStage->Init()))
	{//����������
		return nullptr;
	}

	pStage->m_nSelectedStage = nStage;		//�I������Ă���X�e�[�W�̐ݒ�

	//�w�i�̐���
	pStage->m_pBg = CBg::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));

	CObject::TextType aText[CStageSelection::stage_Max] = { CObject::TextureSeaBG, CObject::TextureThanatosBG , CObject::TexturePrideBg,  CObject::TextureEnvyBg, CObject::TextureWrathBg, CObject::TextureSlothBg, CObject::TextureGreedBg, CObject::TextureGluttonyBg };

	if (pStage->m_pBg != nullptr)
	{//�����o������A�K�v�ȃp�����[�^�̐ݒ肷��
		pStage->m_pBg->SetTexture(aText[pStage->m_nSelectedStage]);

		if (pStage->m_nSelectedStage == CStageSelection::stage_Scylla)
		{
			pStage->m_pBg->SetTextureParameter(2, 1, 2, 30);
			pStage->m_pBg->SetAnimPattern(0);
		}
		else if (pStage->m_nSelectedStage == CStageSelection::stage_Wrath)
		{
			pStage->m_pBg->SetTextureParameter(1, 1, 2, INT_MAX);
			pStage->m_pBg->SetAnimPattern(0);
		}
		else
		{
			pStage->m_pBg->SetTextureParameter(1, 1, 1, INT_MAX);
			pStage->m_pBg->SetAnimPattern(0);
		}
	}

	//�X�e�[�W�̖��O�̐ݒ�
	char aStrg[24] = {};
	strcpy(aStrg, CStageSelection::m_aStage[pStage->m_nSelectedStage]);

	for (int nCnt = 0; nCnt < 24; nCnt++)
	{
		if (aStrg[nCnt] != ' ' && pStage->m_pStageName[nCnt] == nullptr)
		{
			//�X�e�[�W�̖��O�̐���
			pStage->m_pStageName[nCnt] = CLetter::Create(D3DXVECTOR3(((float)SCREEN_WIDTH * 0.35f) + 60.0f * nCnt, (float)SCREEN_HEIGHT * 0.1f, 0.0f), D3DXVECTOR2(50.0f * 0.5f, 50.0f * 0.5f), aStrg[nCnt]);

			if (pStage->m_pStageName[nCnt] != nullptr)
			{//�����������o������A�K�v�ȃp�����[�^��ݒ肷��

				pStage->m_pStageName[nCnt]->SetPriority(5);
				pStage->m_pStageName[nCnt]->SetColor(D3DXCOLOR(1.0f, 8.0f, 0.0f, 1.0f));
				pStage->m_pStageName[nCnt]->SetObjType(CObject::OBJTYPE_MENU);
			}
		}
	}

	//�ۑ����ꂽ�����L���O���擾����
	int* pRanking = CApplication::GetRanking()->GetRanking((CStageSelection::stage)nStage);

	//�X�R�A��z��ɕϊ�����
	for (int i = 0; i < MaxRank; i++)
	{

		int aDigit[MaxDigit] = {};

		int nR = pRanking[i];

		if (pRanking[i] > 0)
		{
			for (int nCnt = 0; nCnt < MaxDigit; nCnt++)
			{
				int nDiv = 1;

				for (int nCnt2 = nCnt; nCnt2 < MaxDigit - 1; nCnt2++)
				{
					nDiv *= 10;
				}

				aDigit[nCnt] = (nR / nDiv);
				nR = nR % nDiv;
			}
		}
		else
		{
			for (int nCnt = 0; nCnt < MaxDigit; nCnt++)
			{
				aDigit[nCnt] = 0;
			}
		}


		for (int nCnt = 0; nCnt < MaxDigit; nCnt++)
		{
			//�X�R�A�̌��𐶐�����
			pStage->m_pRank[i][nCnt] = CLetter::Create(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f - 45.0f * (MaxDigit * 0.5f) + 45.0f * nCnt, (float)SCREEN_HEIGHT * 0.25f + (float)SCREEN_HEIGHT * 0.15f * i, 0.0f), D3DXVECTOR2(40.0f, 40.0f), aDigit[nCnt]);

			if (pStage->m_pRank[i][nCnt] != nullptr)
			{//�����o������A�K�v�ȃp�����[�^��ݒ肷��

				pStage->m_pRank[i][nCnt]->SetPriority(4);
				pStage->m_pRank[i][nCnt]->SetColor(D3DXCOLOR(0.0f, 1.0f, 0.75f, 1.0f));
			}
		}
	}


	//�{�^���̐���
	pStage->m_pLateralButton[0] = CButton::Create(D3DXVECTOR3(150.0f, (float)SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR2(100.0f, 100.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), " ");
	
	if (pStage->m_pLateralButton[0])
	{//�����o������A�K�v�ȃp�����[�^��ݒ肷��
		pStage->m_pLateralIcon[0] = CLetter::Create(D3DXVECTOR3(150.0f, (float)SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR2(100.0f, 100.0f), 0);
		pStage->m_pLateralIcon[0]->SetAnimPattern(13);
	}

	pStage->m_pLateralButton[1] = CButton::Create(D3DXVECTOR3((float)SCREEN_WIDTH - 150.0f, (float)SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR2(100.0f, 100.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), " ");
	
	if (pStage->m_pLateralButton[1])
	{//�����o������A�K�v�ȃp�����[�^��ݒ肷��
		pStage->m_pLateralIcon[1] = CLetter::Create(D3DXVECTOR3((float)SCREEN_WIDTH - 150.0f, (float)SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR2(100.0f, 100.0f), 0);
		pStage->m_pLateralIcon[1]->SetAnimPattern(14);
	}

	CApplication::GetSound()->Play(CSound::SOUND_LABEL_BGM_RESULTS);			//BGM�̐ݒ�

	return pStage;				//���������C���X�^���X��Ԃ�
}



//=============================================================================
//
//								�v���C�x�[�g�֐�
//
//=============================================================================



//���j���[�̍X�V����
void CRankingMode::UpdateMenu(void)
{
	char aStrg[24] = {};
	strcpy(aStrg, CStageSelection::m_aStage[m_nSelectedStage]);		//�X�e�[�W�̖��O���R�s�[����
	D3DXCOLOR col = m_pStageName[0]->GetColor();					//�F�̎擾

	for (int nCnt = 0; nCnt < 24; nCnt++)
	{
		//�X�e�[�W�̖��O��j������
		if (m_pStageName[nCnt] != nullptr)
		{
			m_pStageName[nCnt]->Release();
			m_pStageName[nCnt] = nullptr;
		}

		if (aStrg[nCnt] != ' ' && m_pStageName[nCnt] == nullptr)
		{
			//���݂̃X�e�[�W�̖��O�𐶐�����
			m_pStageName[nCnt] = CLetter::Create(D3DXVECTOR3(((float)SCREEN_WIDTH * 0.35f) + 60.0f * nCnt, (float)SCREEN_HEIGHT * 0.1f, 0.0f), D3DXVECTOR2(50.0f * 0.5f, 50.0f * 0.5f), aStrg[nCnt]);

			if (m_pStageName[nCnt] != nullptr)
			{//�����o������A�K�v�ȃp�����[�^��ݒ肷��
				m_pStageName[nCnt]->SetPriority(5);
				m_pStageName[nCnt]->SetColor(col);
				m_pStageName[nCnt]->SetObjType(CObject::OBJTYPE_MENU);
			}
		}
	}

	//�w�i�̃e�N�X�`��
	CObject::TextType aText[CStageSelection::stage_Max] = { CObject::TextureSeaBG, CObject::TextureThanatosBG , CObject::TexturePrideBg,  CObject::TextureEnvyBg, CObject::TextureWrathBg, CObject::TextureSlothBg, CObject::TextureGreedBg, CObject::TextureGluttonyBg };

	if (m_pBg != nullptr)
	{//null�`�F�b�N

		//�I������Ă���X�e�[�W�ɂ���āA�e�N�X�`���ƃe�N�X�`���p�����[�^�̐ݒ�
		m_pBg->SetTexture(aText[m_nSelectedStage]);				

		if (m_nSelectedStage == CStageSelection::stage_Scylla)
		{
			m_pBg->SetTextureParameter(2, 1, 2, 30);
			m_pBg->SetAnimPattern(0);
		}
		else if (m_nSelectedStage == CStageSelection::stage_Wrath)
		{
			m_pBg->SetTextureParameter(1, 1, 2, INT_MAX);
			m_pBg->SetAnimPattern(1);
		}
		else
		{
			m_pBg->SetTextureParameter(1, 1, 1, INT_MAX);
			m_pBg->SetAnimPattern(0);
		}
	}

	//�����L���O�̎擾
	int* pRanking = CApplication::GetRanking()->GetRanking((CStageSelection::stage)m_nSelectedStage);

	//�擾�����X�R�A��z��ɕϊ�����
	for (int nCnt = 0; nCnt < MaxRank; nCnt++)
	{

		int aDigit[MaxDigit] = {};

		int nR = pRanking[nCnt];

		if (pRanking[nCnt] > 0)
		{
			for (int nCnt = 0; nCnt < MaxDigit; nCnt++)
			{
				int nDiv = 1;

				for (int nCnt2 = nCnt; nCnt2 < MaxDigit - 1; nCnt2++)
				{
					nDiv *= 10;
				}

				aDigit[nCnt] = (nR / nDiv);
				nR = nR % nDiv;
			}
		}
		else
		{
			for (int nCnt = 0; nCnt < MaxDigit; nCnt++)
			{
				aDigit[nCnt] = 0;
			}
		}

		for (int i = 0; i < MaxDigit; i++)
		{//�X�R�A�̃A�j���V�����p�^�[����ݒ肷��
			m_pRank[nCnt][i]->SetAnimPattern(aDigit[i]);
		}
	}
}