//=============================================================================
//
// handGun.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef HAND_GUN_H
#define HAND_GUN_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "enemy.h"

//=============================================================================
//�O���錾
//=============================================================================
class CCircleHitbox;
class CWrath;

class CHandGun : public CEnemy
{
public:

	enum state
	{
		state_spawn = 0,
		state_shoot,
		state_return,
		state_despawn,
		state_death,
		state_max
	};

	CHandGun();																		//�R���X�g���N�^
	~CHandGun() override;															//�f�X�g���N�^

	HRESULT Init(void) override;													//����������
	void Uninit(void) override;														//�I������
	void Update(void) override;														//�X�V����

	void SetParent(CWrath* pParent);

	static CHandGun* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);						//��������

private:

	void UpdateState(void);

	state m_state;

	CCircleHitbox* m_pHitbox;
	CWrath* m_pParent;
};




#endif