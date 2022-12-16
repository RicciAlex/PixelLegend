//=============================================================================
//
// handFireball.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef HAND_FIREBALL_H
#define HAND_FIREBALL_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "bullet.h"

//=============================================================================
//�O���錾
//=============================================================================
class CCircleHitbox;

class CHandFireball : public CBullet
{
public:
	CHandFireball();					//�R���X�g���N�^
	~CHandFireball() override;			//�f�X�g���N�^

	HRESULT Init(void) override;		//����������
	void Uninit(void) override;			//�I������
	void Update(void) override;			//�X�V����


	static CHandFireball* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);						//��������

private:

	float m_fChange;					//��������ς�����W
	bool  m_Rot;						//����
										
	CCircleHitbox* m_pHitbox;			//�q�b�g�{�b�N�X�ւ̃|�C���^
};




#endif