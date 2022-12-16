//=============================================================================
//
// bouncingBullet.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef BOUNCING_BULLET_H
#define BOUNCING_BULLET_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "bullet.h"

//=============================================================================
//�O���錾
//=============================================================================
class CCircleHitbox;

class CBouncingBullet : public CBullet
{
public:
	CBouncingBullet();						//�R���X�g���N�^
	~CBouncingBullet() override;			//�f�X�g���N�^

	HRESULT Init(void) override;			//����������
	void Uninit(void) override;				//�I������
	void Update(void) override;				//�X�V����

	static CBouncingBullet* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move);	//��������

private:

	CCircleHitbox* m_pHitbox;				//�q�b�g�{�b�N�X
};


#endif