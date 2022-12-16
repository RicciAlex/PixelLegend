//=============================================================================
//
// sloth.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef SLOTH_H
#define SLOTH_H

//�C���N���[�h�t�@�C��
#include "enemy.h"

//�O���錾
class CSquareHitbox;
class CEnemyLife;

class CSloth : public CEnemy
{
public:

	//���
	enum State
	{
		state_Spawn = 0,			//�X�|�[�����
		state_Normal,				//���ʂ̏��
		state_Return,				//�߂���
		state_Charge,				//�̓�����
		state_Snore,				//���т��U��
		state_Weep,					//�����U��(1)
		state_Cry,					//�����U��(2)
		state_Summon,				//����
		state_Death,				//���S���
		state_Max
	};

	CSloth();									//�R���X�g���N�^
	~CSloth() override;							//�f�X�g���N�^

	HRESULT Init(void) override;				//����������
	void Uninit(void) override;					//�I������
	void Update(void) override;					//�X�V����
	void Draw(void) override;					//�`�揈��

	const bool GetEnd(void);					//�I��������ǂ����̎擾����

	static CSloth* Create(void);				//��������

private:

	void SlothBehavior(void);					//�X�V����

	bool m_bEnd;
	float m_fYCoord;							//Y���W
	int m_nCntState;							//��ԃJ�E���^�[
	int m_nCntDmg;								//�_���[�W�p�̃J�E���^�[
	int m_nCntSpawn;							//�X�|�[���J�E���^�[
	int m_nChange;								//
	int m_nCntSound;							//�T�E���h�̃J�E���^�[
	int m_nSoundDelay;							//�T�E���h�̃f�B���C
	int m_nCntAnim;								//�A�j���[�V�����J�E���^�[
	D3DXVECTOR3 m_HitboxRelativePos;			//�q�b�g�{�b�N�X�̑��Έʒu
	State m_state;								//���

	CSquareHitbox* m_pHitbox;					//�q�b�g�{�b�N�X
	CEnemyLife* m_pLife;						//�̗�UI�ւ̃|�C���^
};



#endif