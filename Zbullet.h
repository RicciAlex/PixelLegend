//=============================================================================
//
// Zbullet.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef ZBULLET_H
#define ZBULLET_H

//�C���N���[�h�t�@�C��
#include "bullet.h"

//=============================================================================
//�O���錾
//=============================================================================
class CSquareHitbox;

class CZBullet : public CBullet
{
public:
	CZBullet();																		//�R���X�g���N�^
	~CZBullet() override;															//�f�X�g���N�^

	HRESULT Init(void) override;													//����������
	void Uninit(void) override;														//�I������
	void Update(void) override;														//�X�V����


	static CZBullet* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);						//��������

private:

	int m_nCntSize;
	float m_fGrowth;

	CSquareHitbox* m_pHitbox;
};

#endif
