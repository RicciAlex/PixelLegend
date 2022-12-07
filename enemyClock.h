//=============================================================================
//
// enemyClock.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef ENEMY_CLOCK_H
#define ENEMY_CLOCK_H

//�C���N���[�h�t�@�C��
#include "enemy.h"

//�O���錾
class CClockNeedle;

//�K�w�\���A�j���[�V�����̓G�N���X(�G�N���X�̔h���N���X)
class CEnemyClock : public CEnemy
{
public:

	static const int MAX_BOUND_BULLET = 2;										//�K�w�\���̃����o�[�̍ő吔

	CEnemyClock();																//�R���X�g���N�^		
	~CEnemyClock();																//�f�X�g���N�^

	HRESULT Init(void) override;												//����������
	void Uninit(void) override;													//�I������
	void Update(void) override;													//�X�V����
	void Draw(void) override;													//�`�揈��

	static CEnemyClock* Create(D3DXVECTOR3 pos);								//��������


private:

	void UpdateClock(void);										//���v�^�G�̍X�V����
	void RespawnNeedle(void);									//���v�^�G�̒e�̃��X�|�[������

	CClockNeedle* m_pBoundBullet[MAX_BOUND_BULLET];				//�K�w�\���̃I�u�W�F�N�g�ւ̃|�C���^
	bool m_bBound[MAX_BOUND_BULLET];							//�K�w�\���̃I�u�W�F�N�g�̓����[�X���ꂽ���ǂ���
	int m_nCntBoundAnimation;									//�K�w�\���A�j���[�V�����p�̃J�E���^�[

};

#endif // !ENEMY_CLOCK_H