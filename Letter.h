//=============================================================================
//
// Letter.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef LETTER_H
#define LETTER_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object2D.h"

class CLetter : public CObject_2D
{
public:
	CLetter();																//�R���X�g���N�^
	~CLetter() override;													//�f�X�g���N�^

	HRESULT Init(void) override;											//����������
	void Uninit(void) override;												//�I������
	void Update(void) override;												//�X�V����
	void Draw(void) override;												//�I������

	bool ConvertInNumber(const int nNum);									//���l�ɕϊ����鏈��
	bool ConvertInSymbol(const char symbol);								//�����ɕϊ����鏈��

	static CLetter* Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const char letter);			//��������
	static CLetter* CLetter::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const int nNum);		

private:

};

#endif
