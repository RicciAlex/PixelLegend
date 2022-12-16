//=============================================================================
//
// tear.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef TEAR_H
#define TEAR_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "bullet.h"

//=============================================================================
//�O���錾
//=============================================================================
class CCircleHitbox;

class CTearBullet : public CBullet
{
public:
	CTearBullet();						//�R���X�g���N�^
	~CTearBullet() override;			//�f�X�g���N�^

	HRESULT Init(void) override;		//����������
	void Uninit(void) override;			//�I������
	void Update(void) override;			//�X�V����

	static CTearBullet* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move);		//��������

private:

	CCircleHitbox* m_pHitbox;			//�q�b�g�{�b�N�X
};


#endif