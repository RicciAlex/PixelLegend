//=============================================================================
//
// handBlade.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef HAND_BLADE_H
#define HAND_BLADE_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "bullet.h"

//=============================================================================
//�O���錾
//=============================================================================
class CCircleHitbox;

class CHandBlade : public CBullet
{
public:
	CHandBlade();							//�R���X�g���N�^
	~CHandBlade() override;					//�f�X�g���N�^

	HRESULT Init(void) override;			//����������
	void Uninit(void) override;				//�I������
	void Update(void) override;				//�X�V����


	static CHandBlade* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);	//��������

private:

	CCircleHitbox* m_pHitbox;				//�q�b�g�{�b�N�X�ւ̃|�C���^
};




#endif