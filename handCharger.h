//=============================================================================
//
// handCharger.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef HAND_CHARGER_H
#define HAND_CHARGER_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "enemy.h"

//=============================================================================
//�O���錾
//=============================================================================
class CSquareHitbox;
class CWrath;

class CHandCharger : public CEnemy
{
public:

	enum state
	{
		state_spawn = 0,
		state_attack,
		state_return,
		state_despawn,
		state_death,
		state_max
	};

	CHandCharger();																		//�R���X�g���N�^
	~CHandCharger() override;															//�f�X�g���N�^

	HRESULT Init(void) override;													//����������
	void Uninit(void) override;														//�I������
	void Update(void) override;														//�X�V����

	void SetParent(CWrath* pParent);

	static CHandCharger* Create(D3DXVECTOR3 pos);						//��������

private:

	void UpdateState(void);

	D3DXVECTOR3 m_targetPos;
	state m_state;

	CSquareHitbox* m_pHitbox;
	CWrath* m_pParent;
};




#endif