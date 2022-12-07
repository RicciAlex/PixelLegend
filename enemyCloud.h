//=============================================================================
//
// enemyCloud.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef ENEMY_CLOUD_H
#define ENEMY_CLOUD_H

//�C���N���[�h�t�@�C��
#include "enemy.h"

class CEnemyCloud : public CEnemy
{
public:
	
	enum state
	{
		state_pursuit = 0,
		state_aim,
		state_fire,
		state_flee,
		state_max
	};

	CEnemyCloud();
	~CEnemyCloud() override;

	HRESULT Init(void) override;
	void Uninit(void) override;					//�I������
	void Update(void) override;					//�X�V����
	void Draw(void) override;					//�`�揈��

	static CEnemyCloud* Create(D3DXVECTOR3 pos);

private:

	int m_nCntMove;										//�A�j���[�V������ړ��p�̃J�E���^�[
	float m_fAngleMove;									//�A�j���[�V������ړ��p�̃J�E���^�[
	state m_nPhase;										//�A�j���[�V������ړ��p�̃J�E���^�[
	int m_nShootDelay;									//�A�j���[�V������ړ��p�̃J�E���^�[
};

#endif // !ENEMY_CLOUD_H