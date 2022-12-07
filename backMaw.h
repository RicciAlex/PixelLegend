//=============================================================================
//
// backMaw.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef BACK_MAW_H
#define BACK_MAW_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "enemy.h"

//=============================================================================
//�O���錾
//=============================================================================
class CSquareHitbox;

class CBackMaw : public CEnemy
{
public:

	enum state
	{
		state_sleep = 0,
		state_roar,
		state_shoot,
		state_bite,
		state_awake,
		state_wait,
		state_return
	};

	CBackMaw();
	~CBackMaw() override;

	HRESULT Init(void) override;					//����������
	void Uninit(void) override;						//�I������
	void Update(void) override;						//�X�V����
	void Draw(void) override;						//�`�揈��

	void SetState(CBackMaw::state state);			//��Ԃ̐ݒ菈��

	static CBackMaw* Create(void);					//��������

private:

	void UpdateState(void);							//��Ԃ̍X�V����

	D3DXVECTOR3 m_target;
	state m_state;

	CSquareHitbox* m_pHitbox;
};



#endif