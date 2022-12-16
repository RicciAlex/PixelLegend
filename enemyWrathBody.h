//=============================================================================
//
// enemyWrathBody.h
// Author : Ricci Alex
//
//=============================================================================

//�C���N���[�h�t�@�C��
#include "enemy.h"

//�O���錾
class CSquareHitbox;
class CCircleHitbox;
class CObject_2D;
class CWrath;

class CWrathBody : public CEnemy
{
public:

	enum state
	{
		state_spawn = 0,
		state_normal,
		state_flamethrower,
		state_rage,
		state_swirl,
		state_death,
		state_max
	};


	CWrathBody();								//�R���X�g���N�^
	~CWrathBody() override;						//�f�X�g���N�^

	HRESULT Init(void) override;				//����������
	void Uninit(void) override;					//�I������
	void Update(void) override;					//�X�V����
	void Draw(void) override;					//�`�揈��

	void SetParent(CWrath* pParent);			//�e�ւ̃|�C���^�̐ݒ菈��
												
	const bool GetDeath(void);					//���S��Ԃ̎擾����

	//==========================================================================================================
	//											�ÓI�֐�
	static CWrathBody* Create(D3DXVECTOR3 pos);		//��������

private:

	void UpdateState(void);				//��Ԃɂ���Ă̍X�V����
										
	bool m_bDead;						//���S�������ǂ���
	bool m_bBound;						//�e�Ɍ���ł��邩�ǂ���
										
	int m_nCntShoot;					//�U���J�E���^�[
	int m_nCntState;					//��ԃJ�E���^�[
	D3DXVECTOR3 m_targetPos;			//�ړI�̈ʒu
	state m_state;						//���݂̏��
										
	D3DXVECTOR3 m_posArm;				//�r�̈ʒu
										
	CObject_2D* m_pArm;					//�r�ւ̃|�C���^
										
	D3DXVECTOR3 m_posBodyHitbox;		//�̂̃q�b�g�{�b�N�X
	D3DXVECTOR3 m_posHeadHitbox;		//���̃q�b�g�{�b�N�X
										
	CSquareHitbox* m_pHitbox;			//�̂̃q�b�g�{�b�N�X
	CCircleHitbox* m_pHeadHitbox;		//���̃q�b�g�{�b�N�X
										
	CWrath* m_pParent;					//�e�ւ̃|�C���^
};

