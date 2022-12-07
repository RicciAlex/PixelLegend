//=============================================================================
//
// wrath.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef WRATH_H
#define WRATH_H

//�C���N���[�h�t�@�C��
#include "enemy.h"

//�O���錾
class CWrathBody;
class CEnemyLife;


class CWrath : public CEnemy
{
public:

	CWrath();									//�R���X�g���N�^
	~CWrath() override;							//�f�X�g���N�^

	HRESULT Init(void) override;				//����������
	void Uninit(void) override;					//�I������
	void Update(void) override;					//�X�V����
	void Draw(void) override;

	const bool GetEnd(void);
	const bool GetDeath(void);
	void Damage(const int nDamage);

	static CWrath* Create(void);				//��������

private:

	//void WrathBehavior(void);					//�X�V����

	bool m_bEnd;
	bool m_bDeath;

	CWrathBody* m_pBody;
	CEnemyLife* m_pLife;
};



#endif