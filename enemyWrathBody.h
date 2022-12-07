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


	CWrathBody();
	~CWrathBody() override;

	HRESULT Init(void) override;				//����������
	void Uninit(void) override;					//�I������
	void Update(void) override;					//�X�V����
	void Draw(void) override;					//�`�揈��

	void SetParent(CWrath* pParent);

	const bool GetDeath(void);

	//==========================================================================================================
	//											�ÓI�֐�
	static CWrathBody* Create(D3DXVECTOR3 pos);		//��������

private:

	void UpdateState(void);

	bool m_bDead;
	bool m_bBound;

	int m_nCntShoot;
	int m_nCntState;
	D3DXVECTOR3 m_targetPos;
	state m_state;

	D3DXVECTOR3 m_posArm;

	CObject_2D* m_pArm;

	D3DXVECTOR3 m_posBodyHitbox;
	D3DXVECTOR3 m_posHeadHitbox;

	CSquareHitbox* m_pHitbox;
	CCircleHitbox* m_pHeadHitbox;

	CWrath* m_pParent;
};

