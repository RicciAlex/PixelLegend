//=============================================================================
//
// enemy.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef BALLOON_ENEMY_H
#define BALLOON_ENEMY_H

//�C���N���[�h�t�@�C��
#include "enemy.h"

//�O���錾
class CCircleHitbox;

class CBalloonEnemy : public CEnemy
{
public:
	CBalloonEnemy();
	~CBalloonEnemy() override;

	HRESULT Init(void) override;
	void Uninit(void) override;					//�I������
	void Update(void) override;					//�X�V����
	void Draw(void) override;					//�`�揈��

	static CBalloonEnemy* Create(D3DXVECTOR3 pos);

private:

	CCircleHitbox* m_pHitbox;
};

#endif