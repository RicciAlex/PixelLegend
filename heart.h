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

	enum state
	{
		state_spawn = 0,
		state_awake,
		state_sleep,
		state_vulnerable,
		state_return,
		state_death,
		state_max
	};

	CHeart();
	~CHeart() override;								//�f�X�g���N�^

	HRESULT Init(void) override;					//����������
	void Uninit(void) override;						//�I������
	void Update(void) override;						//�X�V����
	void Draw(void) override;						//�`�揈��

	void SetActive(void);
	const bool GetEnd(void);

	static CHeart* Create(void);					//��������



private:

	void UpdateState(void);

	
	bool m_bEnd;
	float m_fAngleShoot;
	state m_state;

	CSquareHitbox* m_pHitbox;
	CEnemyLife* m_pLife;
};

#endif