//=============================================================================
//
// skullCursor.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "skullCursor.h"
#include "application.h"
#include "skull.h"
#include "spine.h"

//�R���X�g���N�^
CSkullCursor::CSkullCursor()
{
	//�����o�[�ϐ����N���A����
	m_skullPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_pSpine = nullptr;
	m_pSkull = nullptr;
}

//�f�X�g���N�^
CSkullCursor::~CSkullCursor()
{

}

//����������
HRESULT CSkullCursor::Init(void)
{
	//�����o�[�ϐ�������������
	m_skullPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_pSpine = nullptr;
	m_pSkull = nullptr;

	return S_OK;
}

//�I������
void CSkullCursor::Uninit(void)
{
	if (m_pSkull != nullptr)
	{//null�`�F�b�N
		m_pSkull->Release();		//���������������
		m_pSkull = nullptr;			//null�ɂ���
	}

	if (m_pSpine != nullptr)
	{//null�`�F�b�N	
		m_pSpine->Release();		//���������������
		m_pSpine = nullptr;			//null�ɂ���
	}
}

//�X�V����
void CSkullCursor::Update(void)
{
	//�}�E�X�J�[�\���̈ʒu�̎擾�ƕϊ�
	POINT pt;
	GetCursorPos(&pt);
	HWND wnd = CApplication::GetWindow();
	ScreenToClient(wnd, &pt);

	m_skullPos.y = (float)pt.y;			//�ʒu��Y���W�̐ݒ�

	if (m_pSkull != nullptr)
	{//null�`�F�b�N
		m_pSkull->SetPos(m_skullPos);		//�ʒu�̐ݒ�
	}
	
	if (m_pSpine != nullptr)
	{//null�`�F�b�N
		m_pSpine->SetHeadPos(m_skullPos);	//�ʒu�̐ݒ�
	}
}





//��������
CSkullCursor* CSkullCursor::Create(const D3DXVECTOR3 pos)
{
	CSkullCursor* pCursor = new CSkullCursor;			//�C���X�^���X�̐���

	if (FAILED(pCursor->Init()))
	{//����������
		return nullptr;
	}

	//�}�E�X�J�[�\���̈ʒu�̎擾�ƕϊ�
	POINT pt;
	GetCursorPos(&pt);
	HWND wnd = CApplication::GetWindow();
	ScreenToClient(wnd, &pt);

	//�ʒu�̌v�Z�Ɛݒ�
	float fNum = 350.0f;

	if (pos.x < (float)SCREEN_WIDTH * 0.5f)
	{
		fNum *= -1.0f;
	}

	pCursor->m_skullPos = D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f + fNum, (float)pt.y, 0.0f);	
	pCursor->m_pSkull = CSkull::Create(pCursor->m_skullPos, D3DXVECTOR2(60.0f, 60.0f));	
	pCursor->m_pSpine = CSpine::Create(pos, pCursor->m_skullPos);

	if (pCursor->m_pSkull != nullptr && pCursor->m_pSpine != nullptr)
	{//null�`�F�b�N
		pCursor->m_pSkull->SetPriority(4);			//�v���C�I���e�B�̐ݒ�

		if (pos.x < (float)SCREEN_WIDTH * 0.5f)
		{//�ʒu�ɂ���ăe�N�X�`���𔽓]����
			pCursor->m_pSkull->FlipX();
			pCursor->m_pSpine->Flip();
		}
	}

	return pCursor;				//���������C���X�^���X��Ԃ�
}