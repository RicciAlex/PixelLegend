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

	const bool GetEnd(void);					//�I��������ǂ����̎擾����
	const bool GetDeath(void);					//���S�������ǂ����̎擾����
	void Damage(const int nDamage);				//�_���[�W���󂯂鏈��

	static CWrath* Create(void);				//��������

private:

	bool m_bEnd;								//�I��������ǂ���
	bool m_bDeath;								//���S�������ǂ���
												
	CWrathBody* m_pBody;						//�̃C���X�^���X�ւ̃|�C���^
	CEnemyLife* m_pLife;						//�̗�UI�ւ̃|�C���^
};



#endif