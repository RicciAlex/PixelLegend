//=============================================================================
//
// heartBullet.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef HEART_BULLET_H
#define HEART_BULLET_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "bullet.h"

//=============================================================================
//�O���錾
//=============================================================================
class CHeartEffect;

class CHeartBullet : public CBullet
{
public:

	CHeartBullet();																	//�R���X�g���N�^
	~CHeartBullet() override;														//�f�X�g���N�^

	HRESULT Init(void) override;													//����������
	void Uninit(void) override;														//�I������
	void Update(void) override;														//�X�V����

	static CHeartBullet* Create(const D3DXVECTOR3 CenterPos, const D3DXVECTOR3 move, const D3DXCOLOR col);				//��������

private:
	static const int MaxEffect = 40;

	CHeartEffect* m_pEffect[MaxEffect];
};


#endif