//=============================================================================
//
// thunderEnemy.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef ENEMY_THUNDER_H
#define ENEMY_THUNDER_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "bullet.h"

//=============================================================================
//�O���錾
//=============================================================================
class CSquareHitbox;

class CThunderEnemy : public CBullet
{
public:
	CThunderEnemy();																//�R���X�g���N�^
	~CThunderEnemy();																//�f�X�g���N�^

	HRESULT Init(void) override;													//����������
	void Uninit(void) override;														//�I������
	void Update(void) override;														//�X�V����

	static CThunderEnemy* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move,
		const D3DXVECTOR3 acc, const D3DXVECTOR2 dim);								//��������

private:

	CSquareHitbox* m_pHitbox;				//�q�b�g�{�b�N�X
};

#endif // !ENEMY_THUNDER_H