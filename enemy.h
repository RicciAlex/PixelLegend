//=============================================================================
//
// enemy.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef ENEMY_H
#define ENEMY_H

//�C���N���[�h�t�@�C��
#include "main.h"
#include "object2D.h"

//�G�̊�{�N���X
class CEnemy : public CObject_2D
{
public:
	CEnemy();											//�R���X�g���N�^
	virtual ~CEnemy() override;							//�f�X�g���N�^
														
	virtual HRESULT Init(void) override;				//����������
	virtual void Uninit(void) override;					//�I������
	virtual void Update(void) override;					//�X�V����
	virtual void Draw(void) override;					//�`�揈��
														
	const int GetLife(void);							//�̗͂̎擾����
	void SetLife(const int nLife);						//�̗͂̐ݒ菈��
	void SetMaxSpeed(const float maxSpeed);				//�ő呬�x�̐ݒ菈��
	const float GetMaxSpeed(void);						//�ő呬�x�̎擾����
	void SetSubtype(const EnemyType subType);			//�G�̎�ނ̐ݒ菈��
	const bool GetDamageableState(void);				//�_���[�W���󂯂邩�ǂ����̎擾����
	void SetDamageableState(const bool bDamageable);	//�_���[�W���󂯂邩�ǂ����̐ݒ菈��
	const EnemyType GetSubtype(void);					//�G�̎�ނ̎擾����

protected:

	int m_nCntMove;										//�A�j���[�V������ړ��p�̃J�E���^�[
	float m_fAngleMove;									//�A�j���[�V������ړ��p�̃J�E���^�[
	int m_nPhase;										//�A�j���[�V������ړ��p�̃J�E���^�[
	int m_nShootDelay;									//�A�j���[�V������ړ��p�̃J�E���^�[

private:

	//void UpdateCloud(void);							//�_�^�G�̍X�V����
														
	int m_nLife;										//�G�̗̑�
	float m_maxSpeed;									//�G�̍ő呬�x
	bool m_bDamageable;
	EnemyType m_subType;								//�G�̎��
	

};




#endif