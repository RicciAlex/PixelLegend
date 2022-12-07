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
		state_Spawn = 0,
		state_Normal,
		state_Return,
		state_Charge,
		state_Snore,
		state_Weep,
		state_Cry,
		state_Summon,
		state_Death,
		state_Max
	};

	CSloth();									//�R���X�g���N�^
	~CSloth() override;							//�f�X�g���N�^

	HRESULT Init(void) override;				//����������
	void Uninit(void) override;					//�I������
	void Update(void) override;					//�X�V����
	void Draw(void) override;					//�`�揈��

	const bool GetEnd(void);

	static CSloth* Create(void);				//��������

private:

	void SlothBehavior(void);					//�X�V����

	bool m_bEnd;
	float m_fYCoord;							//Y���W
	int m_nCntState;							//��ԃJ�E���^�[
	int m_nCntDmg;								//�_���[�W�p�̃J�E���^�[
	int m_nCntSpawn;
	int m_nChange;
	int m_nCntSound;
	int m_nSoundDelay;
	int m_nCntAnim;
	D3DXVECTOR3 m_HitboxRelativePos;
	State m_state;								//���

	CSquareHitbox* m_pHitbox;
	CEnemyLife* m_pLife;
};



#endif