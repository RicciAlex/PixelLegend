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
		state_Spawn = 0,
		state_Normal,
		state_Hide,
		state_BouncingBall,
		state_Star,
		state_LaughAttack,
		state_CreateEnemy,
		state_Balloon,
		state_LaughAnim,
		state_Death,
		state_Max
	};

	CPride();									//�R���X�g���N�^
	~CPride() override;							//�f�X�g���N�^

	HRESULT Init(void) override;				//����������
	void Uninit(void) override;					//�I������
	void Update(void) override;					//�X�V����
	void Draw(void) override;					//�`�揈��

	const bool GetEnd(void);

	static CPride* Create(void);				//��������

private:

	State m_state;								//���
	int m_nSpawnFrame;
	bool m_bEnd;

	CCircleHitbox* m_pHitbox;
	CEnemyLife* m_pLife;
};

#endif