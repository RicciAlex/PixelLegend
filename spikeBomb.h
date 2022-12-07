//=============================================================================
//
// spikeBomb.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef SPIKE_BOMB_H
#define SPIKE_BOMB_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "bullet.h"

//=============================================================================
//�O���錾
//=============================================================================
class CCircleHitbox;

class CSpikeBomb : public CBullet
{
public:
	CSpikeBomb();																	//�R���X�g���N�^
	~CSpikeBomb() override;															//�f�X�g���N�^

	HRESULT Init(void) override;													//����������
	void Uninit(void) override;														//�I������
	void Update(void) override;														//�X�V����


	static CSpikeBomb* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);						//��������

private:

	CCircleHitbox* m_pHitbox;
};


#endif