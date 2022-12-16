//=============================================================================
//
// squareHitbox.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef SQUARE_HITBOX_H
#define SQUARE_HITBOX_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "hitbox.h"

class CSquareHitbox : public CHitbox
{
public:
	CSquareHitbox();							//�R���X�g���N�^
	~CSquareHitbox() override;					//�f�X�g���N�^
												
	HRESULT Init(void) override;				//����������
	void Uninit(void) override;					//�I������
	bool Hit(void) override;					//�����蔻��̏���
												
	const D3DXVECTOR2 GetSize(void);			//�T�C�Y�̎擾����
	const float GetRadius(void);				//���a�̎擾����
												
	void SetSize(const D3DXVECTOR2 size);		//�T�C�Y�̐ݒ菈��

	bool SquareSquareHit(const D3DXVECTOR3 pos, const D3DXVECTOR2 size);	//�~�`���m�̓����蔻��
	bool SquareCircleHit(const D3DXVECTOR3 center, const float radius);		//�l�p�`�Ɖ~�`�̓����蔻��

	static CSquareHitbox* Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const Type type);		//��������

private:

	D3DXVECTOR2 m_size;				//�T�C�Y

};



#endif