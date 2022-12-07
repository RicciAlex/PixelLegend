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

	CFireballPlayer();																//�R���X�g���N�^
	~CFireballPlayer() override;													//�f�X�g���N�^

	HRESULT Init(void) override;													//����������
	void Uninit(void) override;														//�I������
	void Update(void) override;														//�X�V����

	bool Hit(void);																	//�e�̓����蔻��

	void SetStartingAngle(const float fAngle);

	//static CBullet* Create(void);
	static CFireballPlayer* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move,
		const D3DXVECTOR3 acc, const D3DXVECTOR2 dim);								//��������

private:

	float m_fBulletAngle;															
	float m_fBulletInclination;														
	D3DXVECTOR3 m_BulletVector;														
	D3DXVECTOR3 m_origin;															

	CCircleHitbox* m_pHitbox;
};

#endif // !PLAYER_FIREBALL_H