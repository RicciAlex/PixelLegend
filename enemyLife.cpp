//=============================================================================
//
// enemyLife.h
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "enemyLife.h"
#include "letter.h"
#include "player.h"

//�R���X�g���N�^
CEnemyLife::CEnemyLife()
{
	//�����o�[�ϐ����N���A����
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_nMaxLife =0;
	m_nLife = 0;

	for (int nCnt = 0; nCnt < MaxNameLenght; nCnt++)
	{
		m_pName[nCnt] = nullptr;
	}

	for (int nCnt = 0; nCnt < MaxDigit; nCnt++)
	{
		m_pLife[nCnt] = nullptr;
	}
}

//�f�X�g���N�^
CEnemyLife::~CEnemyLife()
{

}

//����������
HRESULT CEnemyLife::Init(void)
{
	//�����o�[�ϐ�������������
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_nMaxLife = 0;
	m_nLife = 0;

	for (int nCnt = 0; nCnt < MaxNameLenght; nCnt++)
	{
		m_pName[nCnt] = nullptr;
	}

	for (int nCnt = 0; nCnt < MaxDigit; nCnt++)
	{
		m_pLife[nCnt] = nullptr;
	}

	return S_OK;
}

//�I������
void CEnemyLife::Uninit(void)
{
	//�G�̖��O��UI�̔j������
	for (int nCnt = 0; nCnt < MaxNameLenght; nCnt++)
	{//null�`�F�b�N
		if (m_pName[nCnt] != nullptr)
		{
			m_pName[nCnt]->Release();			//���������������
			m_pName[nCnt] = nullptr;			//null�ɂ���
		}
	}

	//�G�̗̑͂�UI�̔j������
	for (int nCnt = 0; nCnt < MaxDigit; nCnt++)
	{
		if (m_pLife[nCnt] != nullptr)
		{//null�`�F�b�N
			m_pLife[nCnt]->Release();			//���������������
			m_pLife[nCnt] = nullptr;			//null�ɂ���
		}
	}
}

//�X�V����
void CEnemyLife::Update(void)
{
	
}

//�`�揈��
void CEnemyLife::Draw(void)
{

}

//�ʒu�̐ݒ菈��
void CEnemyLife::SetPos(const D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//�T�C�Y�̎擾����
const D3DXVECTOR2 CEnemyLife::GetSize(void)
{
	return m_size;
}

//�ʒu�̎擾����
const D3DXVECTOR3  CEnemyLife::GetPos(void)
{
	return m_pos;
}

//�̗͂̐ݒ菈��
void CEnemyLife::SetLife(const int nLife)
{
	m_nMaxLife = nLife;
	m_nLife = nLife;
}

//�̗͂̌��Z����
void CEnemyLife::SubtractLife(const int nLife)
{
	m_nLife -= nLife;		//�̗͂��X�V����

	float life = ((float)m_nLife / (float)m_nMaxLife) * 100;			//�̗͂́����v�Z����

	if (m_pLife[0] != nullptr)
	{//null�`�F�b�N
		m_pLife[0]->SetAnimPattern((int)life / 100);			//�e�N�X�`���p�^�[���̐ݒ�
	}
	if (m_pLife[1] != nullptr)
	{//null�`�F�b�N
		m_pLife[1]->SetAnimPattern(((int)life % 100) / 10);		//�e�N�X�`���p�^�[���̐ݒ�
	}
	if (m_pLife[2] != nullptr)
	{//null�`�F�b�N
		m_pLife[2]->SetAnimPattern(((int)life % 10));			//�e�N�X�`���p�^�[���̐ݒ�
	}
}



//��������
CEnemyLife* CEnemyLife::Create(const D3DXVECTOR3 pos, const D3DXCOLOR NameCol, const int MaxLife, const char* pName)
{
	CEnemyLife* pIcon = new CEnemyLife;				//�C���X�^���X�𐶐�����

	if (FAILED(pIcon->Init()))
	{//����������
		return nullptr;
	}

	//���O��UI�̐�������
	char aName[MaxNameLenght] = {};			

	strcpy(aName, pName);				//�z����R�[�s����

	int nNameLenght = strlen(aName);	//�z��̒���

	char aLife[4] = {};

	pIcon->m_pos = pos;					//�ʒu�̐ݒ�
	pIcon->m_nMaxLife = MaxLife;		//�̗͂̍ő�l�̐ݒ�
	pIcon->m_nLife = MaxLife;			//���݂̗̑͂̐ݒ�

	for (int nCnt = 0; nCnt < MaxNameLenght; nCnt++)
	{
		if (pIcon->m_pName[nCnt] == nullptr)
		{//null�`�F�b�N

			//�����𐶐�����
			pIcon->m_pName[nCnt] = CLetter::Create(D3DXVECTOR3(pos.x + 35.0f * (nCnt), pos.y, 0.0f), D3DXVECTOR2(25.0f, 25.0f), aName[nCnt]);

			if (pIcon->m_pName[nCnt] != nullptr)
			{//�����ł�����
				pIcon->m_pName[nCnt]->SetPriority(5);													//�v���C�I���e�B�̐ݒ�
				pIcon->m_pName[nCnt]->SetColor(D3DXCOLOR(NameCol.r, NameCol.g, NameCol.b, 0.75f));		//�F�̐ݒ�
			}
		}
	}

	//�̗͂̍ŏ��̕����̐���
	pIcon->m_pLife[0] = CLetter::Create(D3DXVECTOR3(pos.x + 25.0f * (nNameLenght + 4), pos.y, 0.0f), D3DXVECTOR2(25.0f, 25.0f), 1);

	if (pIcon->m_pLife[0] != nullptr)
	{//�����ł�����
		pIcon->m_pLife[0]->SetPriority(5);														//�v���C�I���e�B�̐ݒ�
		pIcon->m_pLife[0]->SetColor(D3DXCOLOR(NameCol.r, NameCol.g, NameCol.b, 0.75f));			//�F�̐ݒ�
	}

	//�̗͂�2�Ԗڂ̕����̐���
	pIcon->m_pLife[1] = CLetter::Create(D3DXVECTOR3(pos.x + 25.0f * (nNameLenght + 5), pos.y, 0.0f), D3DXVECTOR2(25.0f, 25.0f), 0);

	if (pIcon->m_pLife[1] != nullptr)
	{//�����ł�����
		pIcon->m_pLife[1]->SetPriority(5);														//�v���C�I���e�B�̐ݒ�
		pIcon->m_pLife[1]->SetColor(D3DXCOLOR(NameCol.r, NameCol.g, NameCol.b, 0.75f));			//�F�̐ݒ�
	}

	//�̗͂�3�Ԗڂ̕����̐���
	pIcon->m_pLife[2] = CLetter::Create(D3DXVECTOR3(pos.x + 25.0f * (nNameLenght + 6), pos.y, 0.0f), D3DXVECTOR2(25.0f, 25.0f), 0);

	if (pIcon->m_pLife[2] != nullptr)
	{//�����ł�����
		pIcon->m_pLife[2]->SetPriority(5);														//�v���C�I���e�B�̐ݒ�
		pIcon->m_pLife[2]->SetColor(D3DXCOLOR(NameCol.r, NameCol.g, NameCol.b, 0.75f));			//�F�̐ݒ�
	}

	//�̗͂�4�Ԗڂ̕����̐���(%)
	pIcon->m_pLife[3] = CLetter::Create(D3DXVECTOR3(pos.x + 25.0f * (nNameLenght + 7), pos.y, 0.0f), D3DXVECTOR2(25.0f, 25.0f), '%');

	if (pIcon->m_pLife[3] != nullptr)
	{//�����ł�����
		pIcon->m_pLife[3]->SetPriority(5);														//�v���C�I���e�B�̐ݒ�
		pIcon->m_pLife[3]->SetColor(D3DXCOLOR(NameCol.r, NameCol.g, NameCol.b, 0.75f));			//�F�̐ݒ�
	}

	return pIcon;					//���������C���X�^���X��Ԃ�
}