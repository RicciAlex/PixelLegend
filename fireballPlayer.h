//=============================================================================
//
// fireballPlayer.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef PLAYER_FIREBALL_H
#define PLAYER_FIREBALL_H

//�C���N���[�h�t�@�C��
#include "bullet.h"

//�O���錾
class CCircleHitbox;

//�e�N���X(CObject2D�̔h���N���X)
class CFireballPlayer : public CBullet
{
public:

	CFireballPlayer();				//�R���X�g���N�^
	~CFireballPlayer() override;	//�f�X�g���N�^

	HRESULT Init(void) override;	//����������
	void Uninit(void) override;		//�I������
	void Update(void) override;		//�X�V����

	bool Hit(void);					//�e�̓����蔻��

	void SetStartingAngle(const float fAngle);		//�����̏����l�̐ݒ菈��

	static CFireballPlayer* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move,
		const D3DXVECTOR3 acc, const D3DXVECTOR2 dim);								//��������

private:

	float m_fBulletAngle;			//�ړ��p�̊p�x											
	float m_fBulletInclination;		//���x�̌����Ƃ̊p�x								
	D3DXVECTOR3 m_BulletVector;		//���[�J�����W�̈ʒu					
	D3DXVECTOR3 m_origin;			//�X�|�[���̈ʒu						
									
	CCircleHitbox* m_pHitbox;		//�q�b�g�{�b�N�X
};

#endif // !PLAYER_FIREBALL_H