//=============================================================================
//
// circleHitbox.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef CIRCLE_HITBOX_H
#define CIRCLE_HITBOX_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "hitbox.h"

class CCircleHitbox : public CHitbox
{
public:
	CCircleHitbox();						//�R���X�g���N�^
	~CCircleHitbox() override;				//�f�X�g���N�^
											
	HRESULT Init(void) override;			//����������
	void Uninit(void) override;				//�I������
	bool Hit(void) override;				//�����蔻��̏���
											
	const D3DXVECTOR2 GetSize(void);		//�T�C�Y�̎擾����
	const float GetRadius(void);			//���a�̎擾����
											
	void SetRadius(const float radius);		//���a�̐ݒ菈��

	bool CircleSquareHit(const D3DXVECTOR3 pos, const D3DXVECTOR2 size);		//�~�`�Ǝl�p�`�̓����蔻��̏���
	bool CircleCircleHit(const D3DXVECTOR3 center, const float radius);			//�~�`���m�̓����蔻��̏���

	static CCircleHitbox* Create(const D3DXVECTOR3 pos, const float fRadius, const Type type);			//��������
		
private:

	float m_fRadius;			//���a

};



#endif