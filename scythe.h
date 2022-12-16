//=============================================================================
//
// scythe.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef SCYTHE_H
#define SCYTHE_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "bullet.h"

//=============================================================================
//�O���錾
//=============================================================================
class CCircleHitbox;

class CScythe : public CBullet
{
public:
	CScythe();							//�R���X�g���N�^
	~CScythe() override;				//�f�X�g���N�^

	HRESULT Init(void) override;		//����������
	void Uninit(void) override;			//�I������
	void Update(void) override;			//�X�V����


	static CScythe* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);		//��������

private:

	float fCntSize;						//�T�C�Y�̃J�E���^�[

	CCircleHitbox* m_pHitbox;			//�q�b�g�{�b�N�X�ւ̃|�C���^
};




#endif