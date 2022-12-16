//=============================================================================
//
// vertebra.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef VERTEBRA_H
#define VERTEBRA_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "enemy.h"

//=============================================================================
//�O���錾
//=============================================================================
class CCircleHitbox;

class CVertebra : public CEnemy
{
public:
	CVertebra();								//�R���X�g���N�^
	~CVertebra() override;						//�f�X�g���N�^

	HRESULT Init(void) override;				//����������
	void Uninit(void) override;					//�I������
	void Update(void) override;					//�X�V����

	static CVertebra* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);			//��������

private:

	CCircleHitbox* m_pHitbox;					//�q�b�g�{�b�N�X�ւ̃|�C���^
};

#endif