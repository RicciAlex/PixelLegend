//=============================================================================
//
// tutorial.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "tutorial.h"
#include "bg.h"
#include "object2D.h"
#include "fireballPlayer.h"
#include "application.h"
#include "inputKeyboard.h"
#include "Letter.h"

//�R���X�g���N�^
CTutorial::CTutorial()
{
	//�����o�[�ϐ����N���A����
	m_nCntAnim = 0;
	
	m_pBg = nullptr;
	m_pPlayer = nullptr;
	m_pButton = nullptr;
	m_pTarget = nullptr;
}

//�f�X�g���N�^
CTutorial::~CTutorial()
{

}

//����������
HRESULT CTutorial::Init(void)
{
	//�����o�[�ϐ�������������
	m_nCntAnim = 0;

	m_pBg = nullptr;
	m_pPlayer = nullptr;
	m_pButton = nullptr;
	m_pTarget = nullptr;

	return S_OK;
}

//�I������
void CTutorial::Uninit(void)
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
	//�{�^���̔j��
	if (m_pButton != nullptr)
	{//null�`�F�b�N
		m_pButton->Release();		//���������������
		m_pButton = nullptr;		//�|�C���^��null�ɂ���
	}
	//�^�[�Q�b�g�̔j��
	if (m_pTarget != nullptr)
	{//null�`�F�b�N
		m_pTarget->Release();		//���������������
		m_pTarget = nullptr;		//�|�C���^��null�ɂ���
	}
}

//�X�V����
void CTutorial::Update(void)
{
	//�A�j���[�V��������
	if (m_pPlayer != nullptr)
	{//�v���C���[��null�`�F�b�N

		D3DXVECTOR3 pos = m_pPlayer->GetPos() + D3DXVECTOR3(-150.0f, 0.0f, 0.0f);

		m_nCntAnim++;				//�A�j���[�V�����J�E���^�[���C���N�������g����

		if (m_nCntAnim == 120)
		{//120�t���[�����o������

			m_pPlayer->SetMove(D3DXVECTOR3(2.0f, 0.0f, 0.0f));		//�v���C���[�𓮂���(�E��)
			
			//D�{�^����UI�摜�𐶐�����
			if (m_pButton == nullptr)
			{
				m_pButton = CObject_2D::Create();

				if (m_pButton != nullptr)
				{
					m_pButton->SetPos(pos);
					m_pButton->SetSize(D3DXVECTOR2(20.0f, 53.0f));
					m_pButton->SetStartingRot(D3DX_PI * 0.5f);
					m_pButton->SetTexture(CObject::TextureIconD);
					m_pButton->SetTextureParameter(2, 2, 1, 30);
				}
			}
		}
		else if (m_nCntAnim == 240)
		{//240�t���[�����o������
			m_pPlayer->SetMove(D3DXVECTOR3(-2.0f, 0.0f, 0.0f));

			//A�{�^���̉摜�ɕς���
			if (m_pButton != nullptr)
			{
				m_pButton->SetTexture(CObject::TextureIconA);
			}
		}
		else if (m_nCntAnim == 360)
		{//360�t���[�����o������
			m_pPlayer->SetMove(D3DXVECTOR3(0.0f, -2.0f, 0.0f));

			//W�{�^���̉摜�ɕς���
			if (m_pButton != nullptr)
			{
				m_pButton->SetTexture(CObject::TextureIconW);
			}
		}
		else if (m_nCntAnim == 480)
		{//480�t���[�����o������
			m_pPlayer->SetMove(D3DXVECTOR3(.0f, 2.0f, 0.0f));

			//S�{�^���̉摜�ɕς���
			if (m_pButton != nullptr)
			{
				m_pButton->SetTexture(CObject::TextureIconS);
			}
		}
		else if (m_nCntAnim == 600)
		{//600�t���[�����o������
			m_pPlayer->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

			//�}�E�X�̉摜�ɕς��āA�}�E�X�J�[�\���̉摜����������
			if (m_pButton != nullptr)
			{
				m_pButton->SetTexture(CObject::TextureIconMouse);
				m_pButton->SetSize(D3DXVECTOR2(20.0f, 28.7f));
				m_pButton->SetTextureParameter(1, 2, 1, INT_MAX);
				m_pButton->SetAnimPattern(1);

				if (m_pTarget != nullptr)
				{
					m_pButton->SetPos(m_pTarget->GetPos() + D3DXVECTOR3(-50.0f, -20.0f, 0.0f));
					m_pButton->SetRevolution(m_pPlayer->GetPos(), D3DX_PI * 0.01f, 140.0f);
					m_pTarget->SetRevolution(m_pPlayer->GetPos(), D3DX_PI * 0.01f, 200.0f);
					m_pTarget->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				}
			}
		}
		else if (m_nCntAnim >= 720 && m_nCntAnim <= 1020 && m_nCntAnim % 20 == 0)
		{//720��1020�t���[���̊�20�t���[�����ƒe�𔭐�����

			//�}�E�X�̉摜�̃A�j���[�V�����p�^�[�����X�V����
			if (m_pButton != nullptr)
			{
				m_pButton->SetAnimPattern(0);
			}

			//�v���C���[����}�E�X�J�[�\���̕����ɒe�𔭐�����(2��)
			if (m_pTarget != nullptr)
			{
				D3DXVECTOR3 target = m_pTarget->GetPos();

				target -= m_pPlayer->GetPos();
				D3DXVec3Normalize(&target, &target);

				D3DXVECTOR3 P = m_pPlayer->GetPos();

				CFireballPlayer::Create(P + D3DXVECTOR3(35.0f, -3.0f, 0.0f), D3DXVECTOR3(10.0f * target.x, 10.0f * target.y, 0.0f),
					D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(16.0f, 16.0f));
				CFireballPlayer* pBullet = CFireballPlayer::Create(P + D3DXVECTOR3(35.0f, -3.0f, 0.0f), D3DXVECTOR3(10.0f * target.x, 10.0f * target.y, 0.0f),
					D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR2(16.0f, 16.0f));
				pBullet->SetStartingAngle(D3DX_PI);
			}
		}
		else if (m_nCntAnim > 1020 && m_nCntAnim < 1200)
		{//1020��1200�t���[���̊�

			//�v���C���[�̎���Ƀ}�E�X�{�^���ƃJ�[�\������]����
			if (m_pButton != nullptr)
			{
				m_pButton->SetRevolution(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f);
				m_pButton->SetAnimPattern(1);
			}
			if (m_pTarget != nullptr)
			{
				m_pTarget->SetRevolution(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f);
			}
		}
		else if (m_nCntAnim >= 1200)
		{//1200�t���[������������A�^�C�g����ʂɖ߂�
			CApplication::SetFade(CApplication::Mode_Title);
		}

		if (CInputKeyboard::GetKeyboardTrigger(DIK_SPACE))
		{//�X�y�[�X�L�[����������A�^�C�g����ʂɖ߂�
			CApplication::SetFade(CApplication::Mode_Title);
		}

		if (m_pButton != nullptr)
		{//�{�^����null�ł͂Ȃ�������A�ʒu��ݒ肷��
			m_pButton->SetPos(pos);
		}
	}
}


//=============================================================================
//
//								�ÓI�֐�
//
//=============================================================================


//��������
CTutorial* CTutorial::Create(void)
{
	CTutorial* pMode = new CTutorial;			//�C���X�^���X�𐶐�����

	if (FAILED(pMode->Init()))
	{//����������
		return nullptr;
	}

	//�w�i�̐���
	pMode->m_pBg = CBg::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));

	if (pMode->m_pBg != nullptr)
	{//�w�i�𐶐��o������A�K�v�ȃp�����[�^��ݒ肷��
		pMode->m_pBg->SetTexture(CObject::TextureSlothBg);
		pMode->m_pBg->SetTextureParameter(1, 1, 1, INT_MAX);
		pMode->m_pBg->SetPriority(1);
	}

	//�v���C���[�̐���
	pMode->m_pPlayer = CObject_2D::Create();

	if (pMode->m_pPlayer != nullptr)
	{//�v���C���[�������o������A�K�v�ȃp�����[�^��ݒ肷��
		pMode->m_pPlayer->SetPos(D3DXVECTOR3(650.0f, 360.0f, 0.0f));
		pMode->m_pPlayer->SetSize(D3DXVECTOR2(50.0f, 50.0f));
		pMode->m_pPlayer->SetStartingRot(D3DX_PI * 0.5f);
		pMode->m_pPlayer->SetTexture(CObject::TextureDragon);
		pMode->m_pPlayer->SetTextureParameter(2, 2, 3, 16);
	}

	//�^�[�Q�b�g�̐���
	pMode->m_pTarget = CObject_2D::Create();

	if (pMode->m_pTarget != nullptr)
	{//�^�[�Q�b�g�������o������A�K�v�ȃp�����[�^��ݒ肷��
		pMode->m_pTarget->SetPos(D3DXVECTOR3(850.0f, 360.0f, 0.0f));
		pMode->m_pTarget->SetSize(D3DXVECTOR2(40.0f, 40.0f));
		pMode->m_pTarget->SetTexture(CObject::TextureTarget);
		pMode->m_pTarget->SetTextureParameter(1, 1, 1, INT_MAX);
		pMode->m_pTarget->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}

	//UI�摜�̐���
	CObject_2D* pObj = CObject_2D::Create();

	if (pObj != nullptr)
	{//UI�摜�������o������A�K�v�ȃp�����[�^��ݒ肷��
		pObj->SetPos(D3DXVECTOR3(250.0f, 600.0f, 0.0f));
		pObj->SetSize(D3DXVECTOR2(50.0f, 42.0f));
		pObj->SetStartingRot(D3DX_PI * 0.5f);
		pObj->SetTexture(CObject::TexturePressSpaceIcon);
		pObj->SetTextureParameter(2, 2, 1, 30);
	}

	//"End Tutorial"�Ƃ���������𐶐�����
	char* aStr = "end tutorial";
	int nLenght = strlen(aStr);

	for (int nCnt = 0; nCnt < nLenght; nCnt++)
	{
		//�����̐���
		CLetter* pLetter = CLetter::Create(D3DXVECTOR3(250.0f + 100.0f + 20.0f * nCnt, 600.0f + 35.0f, 0.0f), D3DXVECTOR2(10.0f, 10.0f), aStr[nCnt]);

		if (pLetter != nullptr)
		{//�����������o������
			pLetter->SetColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		}
	}


	return pMode;			//���������C���X�^���X��Ԃ�
}