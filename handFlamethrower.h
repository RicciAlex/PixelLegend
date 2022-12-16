//=============================================================================
//
// handFlamethrower.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef HAND_FLAMETHROWER_H
#define HAND_FLAMETHROWER_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "enemy.h"

//=============================================================================
//�O���錾
//=============================================================================
class CCircleHitbox;
class CWrath;

class CHandFlamethrower : public CEnemy
{
public:

	//���
	enum state
	{
		state_spawn = 0,				//�X�|�[�����
		state_shoot,					//�U�����
		state_return,					//�߂���
		state_despawn,					//�f�B�X�|�[�����
		state_death,					//���S���
		state_max
	};

	CHandFlamethrower();															//�R���X�g���N�^
	~CHandFlamethrower() override;													//�f�X�g���N�^

	HRESULT Init(void) override;													//����������
	void Uninit(void) override;														//�I������
	void Update(void) override;														//�X�V����

	void SetParent(CWrath* pParent);												//�e�ւ̃|�C���^�̐ݒ菈��

	static CHandFlamethrower* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);						//��������

private:

	void updateState(void);					//��Ԃɂ���Ă̍X�V����
											
	state m_state;							//���݂̏��
											
	CCircleHitbox* m_pHitbox;				//�q�b�g�{�b�N�X
	CWrath* m_pParent;						//�e�ւ̃|�C���^
};




#endif