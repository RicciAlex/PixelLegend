//=============================================================================
//
// gluttony.cpp
// Author : Ricci Alex
//
//=============================================================================

//�C���N���[�h�t�@�C��
#include "gluttony.h"
#include "squareHitbox.h"
#include "maw.h"
#include "backMaw.h"
#include "heart.h"
#include "application.h"

//�R���X�g���N�^
CGluttony::CGluttony()
{
	//�����o�[�ϐ����N���A����
	m_pHitbox = nullptr;

	for (int nCnt = 0; nCnt < MaxMaw; nCnt++)
	{
		m_pMaw[nCnt] = nullptr;
	}

	m_nCntState = 0;
	m_nTargetFrame = 0;
	m_nPhase = 0;

	m_pBackMaw = nullptr;
	m_pHeart = nullptr;
}

//�f�X�g���N�^
CGluttony::~CGluttony()
{

}

//����������
HRESULT CGluttony::Init(void)
{
	//�����o�[�ϐ�������������
	m_pHitbox = nullptr;

	for (int nCnt = 0; nCnt < MaxMaw; nCnt++)
	{
		m_pMaw[nCnt] = nullptr;
	}

	m_nCntState = 0;
	m_nTargetFrame = 0;
	m_nPhase = 0;

	m_pBackMaw = nullptr;
	m_pHeart = nullptr;

	return S_OK;
}

//�I������
void CGluttony::Uninit(void)
{
	//�q�b�g�{�b�N�X�̔j������
	if (m_pHitbox != nullptr)
	{//null�`�F�b�N
		m_pHitbox->Release();			//���������������
		m_pHitbox = nullptr;			//�|�C���^��null�ɂ���
	}

	//����̓G�̔j������
	for (int nCnt = 0; nCnt < MaxMaw; nCnt++)
	{
		if (m_pMaw[nCnt] != nullptr)
		{//null�`�F�b�N
			m_pMaw[nCnt]->Release();	//���������������
			m_pMaw[nCnt] = nullptr;		//�|�C���^��null�ɂ���
		}
	}

	//�w�i�̓G�̔j������
	if (m_pBackMaw != nullptr)
	{//null�`�F�b�N
		m_pBackMaw->Release();			//���������������
		m_pBackMaw = nullptr;			//�|�C���^��null�ɂ���
	}

	//�S�̔j������
	if (m_pHeart != nullptr)
	{//null�`�F�b�N
		m_pHeart->Release();			//���������������
		m_pHeart = nullptr;				//�|�C���^��null�ɂ���
	}
}

//�X�V����
void CGluttony::Update(void)
{
	m_nCntState++;				//�U���J�E���^�[���C���N�������g����

	//�S�̍X�V����
	if (m_pHeart != nullptr)
	{//null�`�F�b�N

		if (m_pHeart->GetLife() <= 6250 && m_nPhase == 0)
		{
			m_nPhase++;
		}
		
		if (m_pHeart->GetEnd())
		{//�I�������A���U���g��ʂɐ؂�ւ���
			CApplication::SetFade(CApplication::Mode_Result);
		}
	}

	if (m_nCntState % 1000 == 999)
	{//1000�t���[�����Ǝ���̓G�A���͔w�i�̓G�̏�Ԃ�ݒ肷��

		if (m_nPhase == 0)
		{//�̗͂�6250�ȏゾ������
			int nIdx = CObject::random(0, 2);

			if (m_pMaw[nIdx] != nullptr)
			{//�����_���Ŏ���̓G��1�C�I�����āA�U��������
				m_pMaw[nIdx]->Open();
			}
		}
		else
		{//�̗͂�6250������������
			if (m_pBackMaw != nullptr)
			{//�w�i�̓G���U��������
				m_pBackMaw->SetState(CBackMaw::state_awake);
			}
		}

		if (m_nCntState >= m_nTargetFrame)
		{//�ړI�̃t���[���𒴂�����A

			m_nCntState = 0;										//��ԃJ�E���^�[��0�ɖ߂�
			m_nTargetFrame = CObject::random(3, 5) * 1000;			//���̖ړI�̃t���[���������_���Őݒ肷��

			//�S��null�ł͂Ȃ�������A�N����悤�ɐݒ肷��
			if (m_pHeart != nullptr)
			{
				m_pHeart->SetActive();
			}
		}
	}
}

//�I��������ǂ����̎擾����
const bool CGluttony::GetEnd(void)
{
	if (m_pHeart != nullptr)
	{//�S��null�ł͂Ȃ�������

		return m_pHeart->GetEnd();
	}

	return false;
}


//=============================================================================
//
//									�ÓI�֐�
//
//=============================================================================


//��������
CGluttony* CGluttony::Create(void)
{
	CGluttony* pEnemy = new CGluttony;				//�C���X�^���X�𐶐�����

	if (pEnemy == nullptr)
	{//����������
		return nullptr;
	}

	pEnemy->m_pBackMaw = CBackMaw::Create();				//�w�i�̓G�̐���
	pEnemy->m_pMaw[0] = CMaw::Create(CMaw::left);			//���̓G�̐���
	pEnemy->m_pMaw[1] = CMaw::Create(CMaw::down);			//���̓G�̐���
	pEnemy->m_pMaw[2] = CMaw::Create(CMaw::right);			//�E�̓G�̐���
	pEnemy->m_pHeart = CHeart::Create();					//�S�̐���
	pEnemy->m_nCntState = 700;								//��ԃJ�E���^�[��ݒ肷��
	pEnemy->m_nTargetFrame = CObject::random(1, 3) * 1000;	//�ړI�̃t���[����ݒ肷��

	return pEnemy;					//���������C���X�^���X��Ԃ�
}