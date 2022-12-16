//=============================================================================
//
// greed.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef GREED_H
#define GREED_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "enemy.h"

//=============================================================================
//�O���錾
//=============================================================================
class CSquareHitbox;
class CCircleHitbox;
class CTowerJewel;
class CEnemyLife;

class CGreed : public CEnemy
{
public:

	//���
	enum state
	{
		state_spawn = 0,		//�X�|�[�����
		state_normal,			//���ʂ̏��
		state_walk,				//�ړ����
		state_shot,				//�U�����
		state_rage,				//�{��U��
		state_death,			//���S���
		state_max
	};

	CGreed();												//�R���X�g���N�^
	~CGreed();												//�f�X�g���N�^

	HRESULT Init(void) override;							//����������
	void Uninit(void) override;								//�I������
	void Update(void) override;								//�X�V����
	void Draw(void) override;								//�`�揈��

	const bool GetEnd(void);								//�I��������ǂ����̎擾����

	static CGreed* Create(void);							//��������

private:

	void UpdateState(void);									//��Ԃɂ���Ă̍X�V����

	static const int nTargetNum = 5;						//�ړI�̈ʒu�̐�
	static const int MaxTower = 2;							//���E����U������G�̐�
	static const D3DXVECTOR3 TargetPos[nTargetNum];			//�ړI�̈ʒu

	bool m_bEnd;								//�I��������ǂ���
	float m_fSumAngle;							//�U���p�̊p�x
	float m_fShotAngle;							//�U���̊Ԃ̊p�x
	int m_targetIdx;							//�ړI�̈ʒu�̃C���f�b�N�X
	int m_nAnimCnt;								//�A�j���[�V�����p�̃J�E���^�[
	int m_nTowerDelay;							//���E�̓G�̂̍U���̃f�B���C
	state m_state;								//���
												
	D3DXVECTOR3 m_HitboxUpRelativePos;			//�̂̏㑤�̃q�b�g�{�b�N�X�̑��Έʒu
	D3DXVECTOR3 m_HitboxDownRelativePos;		//�̂̉����̃q�b�g�{�b�N�X�̑��Έʒu
												
	CCircleHitbox* m_pHitboxUp;					//�̂̏㑤�̃q�b�g�{�b�N�X�ւ̃|�C���^
	CSquareHitbox* m_pHitboxDown;				//�̂̉����̃q�b�g�{�b�N�X�ւ̃|�C���^
	CTowerJewel* m_pTower[MaxTower];			//���E�̓G�ւ̃|�C���^
	CEnemyLife* m_pLife;						//�̗�UI�ւ̃|�C���^
};






#endif