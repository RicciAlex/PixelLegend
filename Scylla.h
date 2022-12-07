//=============================================================================
//
// Scylla.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef SCYLLA_H
#define SCYLLA_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "enemy.h"

//=============================================================================
//�O���錾
//=============================================================================
class CSkullTentacle;
class CSpine;
class CScyllaBody;
class CEnemyLife;

class CScylla : public CObject
{
public:

	//���
	enum State
	{
		state_Spawn = 0,
		state_Damage,
		state_Death,
		state_normal,
		state_Max
	};

	CScylla();											//�R���X�g���N�^
	~CScylla() override;								//�f�X�g���N�^

	HRESULT Init(void) override;						//����������
	void Uninit(void) override;							//�I������
	void Update(void) override;							//�X�V����
	void Draw(void) override;							//�`�揈��

	void SetPos(const D3DXVECTOR3 pos) override;		//�ʒu�̐ݒ菈��
	const D3DXVECTOR2 GetSize(void) override;			//�T�C�Y�̎擾����
	const D3DXVECTOR3 GetPos(void) override;			//�ʒu�̎擾����
	const bool GetEnd(void);

	static CScylla* Create(void);						//��������

private:

	static const int MaxTentacle = 6;					

	D3DXVECTOR3 m_Anchor[MaxTentacle];					
	D3DXVECTOR3 m_TentacleAnchor[MaxTentacle];
	bool m_aliveHead[MaxTentacle];						//���������Ă��邩�ǂ���
	int m_nAliveHeadNum;								//�c���Ă��铪�̐�
	int m_nCntAttack;									//�U���p�̃J�E���^�[
	State m_state;										//���
	bool m_bEnd;

	CSkullTentacle* m_pTentacle[MaxTentacle];
	CSpine* m_pSpine[MaxTentacle];
	CScyllaBody* m_pBody;
	CEnemyLife* m_pLife;
};



#endif