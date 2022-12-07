//=============================================================================
//
// bg.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef BG_H
#define BG_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object2D.h"

class CBg : public CObject_2D
{
public:
	CBg();															//�R���X�g���N�^
	~CBg() override;												//�f�X�g���N�^

	HRESULT Init(void) override;									//����������
	virtual void Uninit(void) override;								//�I������
	virtual void Update(void) override;								//�X�V����
	//virtual void Draw(void) override;								//�I������

	void SetColor(const D3DXCOLOR col);								//�J�[���[�̐ݒ菈��

	static CBg* Create(const D3DXCOLOR col, const D3DXVECTOR2 textMove);										//��������

private:
	
	D3DXVECTOR2 m_textMove;											//�e�N�X�`����UV���W�̈ړ���
};

#endif