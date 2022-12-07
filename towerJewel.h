//=============================================================================
//
// towerJewel.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef TOWER_JEWEL_H
#define TOWER_JEWEL_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "enemy.h"

//=============================================================================
//�O���錾
//=============================================================================
class CCircleHitbox;

class CTowerJewel : public CEnemy
{
public:
	enum state
	{
		state_spawn = 0,
		state_shoot,
		state_despawn,
		state_wait,
		state_max
	};

	CTowerJewel();											//�R���X�g���N�^
	~CTowerJewel() override;								//�f�X�g���N�^

	HRESULT Init(void) override;				//����������
	void Uninit(void) override;					//�I������
	void Update(void) override;					//�X�V����

	void SetState(CTowerJewel::state state);

	static CTowerJewel* Create(const D3DXVECTOR3 pos);		//��������

private:

	state m_state;

	CCircleHitbox* m_pHitBox;

};

#endif