//=============================================================================
//
// envy.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef ENVY_H
#define ENVY_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "enemy.h"

//=============================================================================
//�O���錾
//=============================================================================
class CSquareHitbox;
class CEnemyLife;


class CEnvy : public CEnemy
{
public:

	//���
	enum state
	{	
		state_spawn = 0,			//�X�|�[�����
		state_normal,				//���ʂ̏��
		state_hide,					//�B�����
		state_strike,				//�U�����
		state_death,				//���S���
		state_max
	};

	CEnvy();									//�R���X�g���N�^
	~CEnvy() override;							//�f�X�g���N�^

	HRESULT Init(void) override;				//����������
	void Uninit(void) override;					//�I������
	void Update(void) override;					//�X�V����
	void Draw(void) override;					//�`�揈��

	const bool GetEnd(void);					//�I��������ǂ����̎擾����

	static CEnvy* Create(void);					//��������

private:
						
	void UpdateState(void);				//��Ԃɂ���Ă̍X�V����
	void UpdatePointers(void);			//�|�C���^�̍X�V����
	void CreateGears(void);				//���Ԃ̐�������



	static const int nGearNum = 6;		//���Ԃ̐�
	static const int nPipeNum = 2;		//�ǂ̐�
	static const D3DXVECTOR2 m_EnvySize;		//�T�C�Y
	static const D3DXVECTOR2 m_HitboxEnvySize;	//�q�b�g�{�b�N�X�T�C�Y
	static const D3DXVECTOR2 m_HitboxHatSize;			//�X�q�̃q�b�g�{�b�N�X�T�C�Y

	
	D3DXVECTOR3 m_gearRelativePos[nGearNum];		//���Ԃ̑��Έʒu
	D3DXVECTOR3 m_hatRelativePos;					//�X�q�̑��Έʒu
	D3DXVECTOR3 m_pipeRelativePos[nPipeNum];		//�ǂ̑��Έʒu
	D3DXVECTOR3 m_cannonRelativePos;				//��C�̑��Έʒu

	int m_nCntState;					//��ԃJ�E���^�[
	state m_state;						//���
	bool m_bEnd;						//�I��������ǂ���
										
	CObject_2D* m_pGear[nGearNum];		//���Ԃւ̃|�C���^
	CObject_2D* m_pHat;					//�X�q�ւ̃|�C���^
	CObject_2D* m_pPipe[nPipeNum];		//�ǂւ̃|�C���^
	CObject_2D* m_pCannon;				//��C�ւ̃|�C���^
	CSquareHitbox* m_pHitbox;			//�q�b�g�{�b�N�X�ւ̃|�C���^
	CSquareHitbox* m_pHatHitbox;		//�X�q�̃q�b�g�{�b�N�X�ւ̃|�C���^
	CEnemyLife* m_pLife;				//�̗�UI�ւ̃|�C���^
};


#endif