//=============================================================================
//
// pride.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef PRIDE_H
#define PRIDE_H

//�C���N���[�h�t�@�C��
#include "enemy.h"

//�O���錾
class CCircleHitbox;
class CEnemyLife;

class CPride : public CEnemy
{
public:

	//���
	enum State
	{
		state_Spawn = 0,			//�X�|�[��
		state_Normal,				//����
		state_Hide,					//�B��
		state_BouncingBall,			//�ʒe
		state_Star,					//���e
		state_LaughAttack,			//�΂�
		state_CreateEnemy,			//����
		state_Balloon,				//���D
		state_LaughAnim,			//�΂��A�j���[�V����
		state_Death,				//���S
		state_Max
	};

	CPride();									//�R���X�g���N�^
	~CPride() override;							//�f�X�g���N�^

	HRESULT Init(void) override;				//����������
	void Uninit(void) override;					//�I������
	void Update(void) override;					//�X�V����
	void Draw(void) override;					//�`�揈��

	const bool GetEnd(void);					//�I��������ǂ����̎擾����

	static CPride* Create(void);				//��������

private:

	void UpdateState(void);						//��Ԃɂ���Ă̍X�V����

	State m_state;								//���
	int m_nSpawnFrame;							//�����t���[��
	bool m_bEnd;								//�I��������ǂ���

	CCircleHitbox* m_pHitbox;					//�q�b�g�{�b�N�X�ւ̃|�C���^
	CEnemyLife* m_pLife;						//�̗�UI�ւ̃|�C���^
};

#endif