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

	//��Ԃ̗񋓌^
	enum state
	{
		state_spawn = 0,			//�X�|�[��
		state_shoot,				//�V���b�g
		state_return,				//�߂�
		state_despawn,				//�f�B�X�|�[��
		state_death,				//���S
		state_max
	};

	CHandGun();																		//�R���X�g���N�^
	~CHandGun() override;															//�f�X�g���N�^

	HRESULT Init(void) override;													//����������
	void Uninit(void) override;														//�I������
	void Update(void) override;														//�X�V����

	void SetParent(CWrath* pParent);												//�e�̐ݒ菈��

	static CHandGun* Create(D3DXVECTOR3 pos, D3DXVECTOR3 move);						//��������

private:

	void UpdateState(void);			//��Ԃɂ���Ă̍X�V����
									
	state m_state;					//���
									
	CCircleHitbox* m_pHitbox;		//�q�b�g�{�b�N�X
	CWrath* m_pParent;				//�e�ւ̃|�C���^
};




#endif