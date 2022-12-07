//=============================================================================
//
// bullet.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef BULLET_H
#define BULLET_H

//�C���N���[�h�t�@�C��
#include "object2D.h"

//�e�N���X(CObject2D�̔h���N���X)
class CBullet : public CObject_2D
{
public:

	//�e�̎��
	enum BULLET_TYPE
	{
		BULLET_FIREBALL = 0,
		BULLET_PLAYER_FIREBALL,
		BULLET_THUNDER,
		BULLET_BLACKHOLE,
		BULLET_CLOCK_NEEDLE,
		BULLET_BEAM,
		BULLET_HEART,
		BULLET_SKULL_FIREBALL,
		BULLET_TYPE_MAX
	};

	CBullet();																				//�R���X�g���N�^
	virtual ~CBullet();																		//�f�X�g���N�^

	virtual HRESULT Init(void) override;													//����������
	virtual void Uninit(void) override;														//�I������
	virtual void Update(void) override;														//�X�V����

	void DestroyBullet(void);																//�e�̔j������

	int GetLife(void);																		//���C�t�̎擾����
	void SetLife(const int life);															//���C�t�̐ݒ菈��
	BULLET_TYPE GetBulletType(void);														//�e�̎�ނ̎擾����
	void SetBulletType(BULLET_TYPE type);													//�e�̎�ނ̐ݒ菈��

private:
	
	int m_nLife;						//����
	BULLET_TYPE m_BulletType;			//�e�̎��
};

#endif // !BULLET_H