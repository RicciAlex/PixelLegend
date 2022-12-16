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

	//�ʒu
	enum Position
	{
		left = 0,		//��
		up,				//��
		right,			//�E
		down			//��
	};

	//���
	enum state
	{
		state_normal = 0,		//���ʂ̏��
		state_open,				//�J��
		state_SingleShoot,		//�U��(1��)
		state_TripleShoot,		//�U��(3��)
		state_RandomShoot,		//�����_���ȍU��
		state_Spawn,			//����
		state_close				//����
	};

	CMaw();											//�R���X�g���N�^
	~CMaw() override;								//�f�X�g���N�^

	HRESULT Init(void) override;					//����������
	void Uninit(void) override;						//�I������
	void Update(void) override;						//�X�V����
	void Draw(void) override;						//�`�揈��

	void Open(void);								//�J������

	static CMaw* Create(Position Pos);				//��������

private:

	void UpdateState(void);						//��Ԃɂ���Ă̍X�V����

	state m_state;								//���
	Position m_Pos;								//�ʒu

	CSquareHitbox* m_pHitbox;					//�q�b�g�{�b�N�X
};

#endif