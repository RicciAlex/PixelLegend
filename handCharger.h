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

	//���
	enum state
	{
		state_spawn = 0,			//�X�|�[�����
		state_attack,				//�U�����
		state_return,				//�߂���
		state_despawn,				//�f�B�X�|�[�����
		state_death,				//���S���
		state_max
	};

	CHandCharger();										//�R���X�g���N�^
	~CHandCharger() override;							//�f�X�g���N�^

	HRESULT Init(void) override;						//����������
	void Uninit(void) override;							//�I������
	void Update(void) override;							//�X�V����

	void SetParent(CWrath* pParent);					//�e�ւ̃|�C���^�̐ݒ菈��

	static CHandCharger* Create(D3DXVECTOR3 pos);		//��������

private:

	void UpdateState(void);					//��Ԃɂ���Ă̍X�V����
											
	D3DXVECTOR3 m_targetPos;				//�ړI�̈ʒu
	state m_state;							//���݂̏��
											
	CSquareHitbox* m_pHitbox;				//�q�b�g�{�b�N�X
	CWrath* m_pParent;						//�e�ւ̃|�C���^
};




#endif