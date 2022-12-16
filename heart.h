//=============================================================================
//
// heart.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef HEART_H
#define HEART_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "enemy.h"

//=============================================================================
//�O���錾
//=============================================================================
class CSquareHitbox;
class CEnemyLife;

class CHeart : public CEnemy
{
public:

	//���
	enum state
	{
		state_spawn = 0,		//�X�|�[�����
		state_awake,			//�N������
		state_sleep,			//�Q����
		state_vulnerable,		//�_���[�W���󂯂���
		state_return,			//�߂���
		state_death,			//���S���
		state_max
	};
		
	CHeart();										//�R���X�g���N�^
	~CHeart() override;								//�f�X�g���N�^

	HRESULT Init(void) override;					//����������
	void Uninit(void) override;						//�I������
	void Update(void) override;						//�X�V����
	void Draw(void) override;						//�`�揈��

	void SetActive(void);							//�N�����Ԃ̐ݒ菈��
	const bool GetEnd(void);						//�I��������ǂ����̏I������

	static CHeart* Create(void);					//��������

private:

	void UpdateState(void);				//��Ԃɂ���Ă̍X�V����

	
	bool m_bEnd;						//�I��������ǂ���
	float m_fAngleShoot;				//�U���p�x
	state m_state;						//���
										
	CSquareHitbox* m_pHitbox;			//�q�b�g�{�b�N�X
	CEnemyLife* m_pLife;				//�̗�UI
};

#endif