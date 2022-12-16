//=============================================================================
//
// hitbox.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef HITBOX_H
#define HITBOX_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

class CHitbox
{
public:

	static const int MaxHitbox = 1024;		//�q�b�g�{�b�N�X�̍ő吔
	
	//��ނ̗񋓌^
	enum Type
	{
		Type_Enemy = 0,			//�G
		Type_Player,			//�v���C���[
		Type_EnemyBullet,		//�G�̒e
		Type_PlayerBullet,		//�v���C���[�̒e
		Type_Max
	};

	//�`�̗񋓌^
	enum Shape
	{
		shape_Circle = 0,		//�~�`
		shape_Square,			//�l�p�`
		shape_Capsule,			
		shape_Max
	};

	CHitbox();								//�R���X�g���N�^
	virtual ~CHitbox();						//�f�X�g���N�^
											
	virtual HRESULT Init(void);				//����������
	virtual void Uninit(void);				//�I������
	virtual bool Hit(void) = 0;				//�����蔻��̏���
											
	void Release(void);						//�j������
											
	const D3DXVECTOR3 GetPos(void);			//�ʒu�̎擾����
	const Shape GetShape(void);				//�`�̎擾����
	const Type GetType(void);				//��ނ̎擾����
	virtual const D3DXVECTOR2 GetSize(void) = 0;	//�T�C�Y�̎擾����
	virtual const float GetRadius(void) = 0;		//���a�̎擾����
	const bool GetHitState(void);			//�����������ǂ����̎擾����
	

	
	void SetPos(const D3DXVECTOR3 pos);		//�ʒu�̐ݒ菈��
	void SetType(const Type type);			//��ނ̐ݒ菈��
	void SetShape(const Shape shape);		//�`�̐ݒ菈��
	void SetHitState(const bool bHit);		//�����������ǂ����̐ݒ菈��
											
	static void ReleaseAll(void);			//�S���̃C���X�^���X�̔j������
	static CHitbox** GetAllHitbox(void);	//�S���̃C���X�^���X�̎擾����

private:

	Type m_Type;				//���
	Shape m_Shape;				//�`
	D3DXVECTOR3 m_pos;			//�ʒu
	int m_nIdx;					//�C���f�b�N�X
	bool m_bHit;				//�����������ǂ���

	static CHitbox* m_pHitbox[MaxHitbox];		//�S���̃C���X�^���X�ւ̃|�C���^�������Ă���z��

};



#endif // !HITBOX_H
