//=============================================================================
//
// skullFireball.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef SKULL_FIREBALL_H
#define SKULL_FIREBALL_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "bullet.h"

//=============================================================================
//�O���錾
//=============================================================================
class CCircleHitbox;

class CSkullFireball : public CBullet
{
public:
	CSkullFireball();																//�R���X�g���N�^
	~CSkullFireball() override;														//�f�X�g���N�^

	HRESULT Init(void) override;													//����������
	void Uninit(void) override;														//�I������
	void Update(void) override;														//�X�V����

	static CSkullFireball* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);				//��������

private:

	CCircleHitbox* m_pHitbox;
};

#endif