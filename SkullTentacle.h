//=============================================================================
//
// SkullTentacle.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef SKULL_TENTACLE_H
#define SKULL_TENTACLE_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object.h"

//=============================================================================
//�O���錾
//=============================================================================
class CSpine;
class CSkull;

class CSkullTentacle : public CObject
{
public:

	//���
	enum State
	{
		state_Spawn = 0,
		state_Idle,
		state_Bite,
		state_Pursuit,
		state_Aim,
		state_ShootBeam,
		state_Flamethrower,
		state_Pull,
		state_Return,
		state_Max,
	};

	CSkullTentacle();									//�R���X�g���N�^
	~CSkullTentacle() override;							//�f�X�g���N�^

	HRESULT Init(void) override;						//����������
	void Uninit(void) override;							//�I������
	void Update(void) override;							//�X�V����
	void Draw(void) override;							//�`�揈��

	void SetPos(const D3DXVECTOR3 pos) override;				//�ʒu�̐ݒ菈��
	const D3DXVECTOR2 GetSize(void) override;				//�T�C�Y�̎擾����
	const D3DXVECTOR3 GetPos(void) override;

	const State GetState(void);							//��Ԃ̎擾����

	void SetState(const State state);					//��Ԃ̐ݒ菈��

	void SetLife(const int nLife);						//���C�t�̐ݒ菈��

	const int GetLife(void);							//���C�t�̎擾����

	void Kill(void);

	static CSkullTentacle* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 headPos);		//��������		pos = CSpine��anchor



private:

	void UpdateState(void);								//�X�V����
	void ChargeAnimation(const D3DXCOLOR color);		//�A�j���[�V��������

	int m_nLife;										//�̗�
	D3DXVECTOR3 m_SkullPos;								//���̈ʒu
	D3DXVECTOR3 m_SkullDir;								//���̌���
	D3DXVECTOR3 m_target;								//�ړI�̈ʒu
	CSkull* m_pSkull;									
	CSpine* m_pSpine;									
	State m_state;										//���
	int m_nCntAtk;										//�U���p�̃J�E���^�[
	int m_nCntDeath;									//���S�A�j���[�V�����p�̃J�E���^�[
	int m_nCntMove;										//�ړ��p�̃J�E���^�[
	float m_fAngleMove;									//�ړ��p�̃J�E���^�[
	bool m_bDead;										//����ł��邩�ǂ���
};

#endif