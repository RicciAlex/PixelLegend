//=============================================================================
//
// skull.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef SKULL_H
#define SKULL_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "enemy.h"

//=============================================================================
//�O���錾
//=============================================================================
class CSquareHitbox;

class CSkull : public CEnemy
{
public:
	CSkull();									//�R���X�g���N�^
	~CSkull() override;							//�f�X�g���N�^

	HRESULT Init(void) override;				//����������
	void Uninit(void) override;					//�I������
	void Update(void) override;					//�X�V����

	void Kill(void);							//���S�A�j���[�V�����̐ݒ菈��

	static CSkull* Create(D3DXVECTOR3 pos, D3DXVECTOR2 size);			//��������

private:

	D3DXVECTOR3 m_move;							//���x
	int m_nCntDestroy;							//���S�A�j���[�V�����p�̃J�E���^�[
	bool m_bDead;								//����ł��邩�ǂ���

	CSquareHitbox* m_pHitbox;
};

#endif