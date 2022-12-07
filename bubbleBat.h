//=============================================================================
//
// bubbleBat.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef BUBBLE_BAT_H
#define BUBBLE_BAT_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "enemy.h"

//=============================================================================
//�O���錾
//=============================================================================
class CCircleHitbox;
class CLetter;

class CBubbleBat : public CEnemy
{
public:

	enum state
	{
		state_spawn = 0,
		state_looking,
		state_charge,
		state_max
	};

	CBubbleBat();
	~CBubbleBat() override;							//�f�X�g���N�^

	HRESULT Init(void) override;				//����������
	void Uninit(void) override;					//�I������
	void Update(void) override;					//�X�V����
	void Draw(void) override;					//�`�揈��

	static CBubbleBat* Create(const D3DXVECTOR3 pos);			//��������

private:

	D3DXVECTOR3 m_letterRelativePos;
	state m_state;

	CCircleHitbox* m_pHitbox;
	CLetter* m_pLetter;

};


#endif