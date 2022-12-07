//=============================================================================
//
// skeleton.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef SKELETON_H
#define SKELETON_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "enemy.h"

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
class CSquareHitbox;

class CSkeleton : public CEnemy
{
public:

	enum type
	{
		type_legs = 0,
		type_body,
		type_full
	};

	enum state
	{
		state_spawn = 0,
		state_wait,
		state_pursuit
	};

	CSkeleton();
	~CSkeleton() override;

	HRESULT Init(void) override;				//����������
	void Uninit(void) override;					//�I������
	void Update(void) override;					//�X�V����
	void Draw(void) override;					//�`�揈��

	static CSkeleton* Create(const D3DXVECTOR3 pos);					//��������

private:

	void UpdateMove(void);

	type m_type;
	state m_state;
	float m_fTaget;

	CSquareHitbox* m_pHitbox;
};



#endif