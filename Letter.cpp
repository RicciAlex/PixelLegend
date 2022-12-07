//=============================================================================
//
// Letter.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "Letter.h"

//�R���X�g���N�^
CLetter::CLetter()
{

}

//�f�X�g���N�^
CLetter::~CLetter()
{

}

//����������
HRESULT CLetter::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CObject_2D::Init()))
	{
		return -1;
	}

	//��ނ̐ݒ菈��
	SetObjType(CObject::OBJTYPE_LETTER);

	return S_OK;
}

//�I������
void CLetter::Uninit(void)
{
	//��{�N���X�̏I������
	CObject_2D::Uninit();
}

//�X�V����
void CLetter::Update(void)
{
	//��{�N���X�̍X�V����
	CObject_2D::Update();
}

//�I������
void CLetter::Draw(void)
{
	//��{�N���X�̕`�揈��
	CObject_2D::Draw();
}

bool CLetter::ConvertInNumber(const int nNum)
{
	if (nNum >= 0 && nNum <= 9)
	{
		SetTexture(CObject::TextureNumbers);
		SetTextureParameter(1, 5, 3, INT_MAX);
		SetAnimPattern(nNum);
	}
	else
	{
		return false;
	}

	return true;
}

bool CLetter::ConvertInSymbol(const char symbol)
{
	if (symbol != '?' && symbol != '!' && symbol != '%')
	{
		return false;
	}
	else
	{
		SetTexture(CObject::TextureNumbers);
		SetTextureParameter(1, 5, 3, INT_MAX);

		switch (symbol)
		{
		case '?':

			SetAnimPattern(10);

			break;

		case '!':

			SetAnimPattern(11);

			break;

		case '%':

			SetAnimPattern(12);

			break;

		default:

			return false;

			break;
		}
	}
	
	return true;
}


//==================================================================================================================
//
//		�ÓI�֐�
//
//==================================================================================================================

//��������
CLetter* CLetter::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const char letter)
{
	CLetter* pLetter = new CLetter;						//����

	//����������
	if (FAILED(pLetter->Init()))
	{
		return nullptr;
	}
	
	pLetter->SetPos(pos);									//�ʒu�̐ݒ�
	pLetter->SetSize(size);									//�T�C�Y�̐ݒ�
	pLetter->SetStartingRot(D3DX_PI * 0.5f);				//��]�p�x�̐ݒ�
	pLetter->SetTexture(CObject::TextureLetters);			//�e�N�X�`���̐ݒ�
	pLetter->SetTextureParameter(26, 13, 2, INT_MAX);		//�e�N�X�`���p�����[�^�̐ݒ�

	char aLetter = 'a';

	//�A�j���[�V�����p�^�[���̐ݒ�
	int Cell = 27;

	for (int nCnt = 0; nCnt < 26; nCnt++)
	{
		if (letter == aLetter)
		{
			Cell = nCnt;
			break;
		}

		aLetter += 1;
	}

	if (Cell < 0 || Cell > 25)
	{
		if (!pLetter->ConvertInSymbol(letter))
		{
			pLetter->Release();
			return nullptr;
		}
	}
	else
	{
		pLetter->SetAnimPattern(Cell);
	}	

	return pLetter;				
} 

//��������
CLetter* CLetter::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const int nNum)
{
	CLetter* pLetter = new CLetter;						//����

														//����������
	if (FAILED(pLetter->Init()))
	{
		return nullptr;
	}

	pLetter->SetPos(pos);									//�ʒu�̐ݒ�
	pLetter->SetSize(size);									//�T�C�Y�̐ݒ�
	pLetter->SetStartingRot(D3DX_PI * 0.5f);				//��]�p�x�̐ݒ�
	pLetter->SetTexture(CObject::TextureLetters);			//�e�N�X�`���̐ݒ�
	pLetter->SetTextureParameter(26, 13, 2, INT_MAX);		//�e�N�X�`���p�����[�^�̐ݒ�

	if (!pLetter->ConvertInNumber(nNum))
	{
		pLetter->Uninit();
		pLetter->Release();
		return nullptr;
	}
	

	return pLetter;
}