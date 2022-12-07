//=============================================================================
//
// spike.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef SPIKE_H
#define SPIKE_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "bullet.h"

//=============================================================================
//�O���錾
//=============================================================================
class CSquareHitbox;

class CSpike : public CBullet
{
public:
	CSpike();																		//�R���X�g���N�^
	~CSpike() override;																//�f�X�g���N�^

	HRESULT Init(void) override;													//����������
	void Uninit(void) override;														//�I������
	void Update(void) override;														//�X�V����


	static CSpike* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move);			//��������

private:

	CSquareHitbox* m_pHitbox;

};

#endif