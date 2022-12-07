//=============================================================================
//
// greedBullet.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef GREED_BULLET_H
#define GREED_BULLET_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "bullet.h"

//=============================================================================
//�O���錾
//=============================================================================
class CCircleHitbox;

class CGreedBullet : public CBullet
{
public:
	CGreedBullet();																	//�R���X�g���N�^
	~CGreedBullet() override;														//�f�X�g���N�^

	HRESULT Init(void) override;													//����������
	void Uninit(void) override;														//�I������
	void Update(void) override;														//�X�V����


	static CGreedBullet* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move);											//��������
	static CGreedBullet* CGreedBullet::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const D3DXVECTOR3 acc);	//��������

private:

	CCircleHitbox* m_pHitbox;
};

#endif