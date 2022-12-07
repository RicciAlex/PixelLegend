//=============================================================================
//
// maw.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef MAW_H
#define MAW_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "enemy.h"

//=============================================================================
//�O���錾
//=============================================================================
class CSquareHitbox;

class CMaw : public CEnemy
{
public:

	enum Position
	{
		left = 0,
		up,
		right,
		down
	};

	enum state
	{
		state_normal = 0,
		state_open,
		state_SingleShoot,
		state_TripleShoot,
		state_RandomShoot,
		state_Spawn,
		state_close
	};

	CMaw();
	~CMaw() override;								//�f�X�g���N�^

	HRESULT Init(void) override;					//����������
	void Uninit(void) override;						//�I������
	void Update(void) override;						//�X�V����
	void Draw(void) override;						//�`�揈��

	void Open(void);

	static CMaw* Create(Position Pos);					//��������

private:

	void UpdateState(void);

	state m_state;								//���
	Position m_Pos;

	CSquareHitbox* m_pHitbox;
};

#endif