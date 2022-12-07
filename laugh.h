//=============================================================================
//
// laugh.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef LAUGH_H
#define LAUGH_H

//�C���N���[�h�t�@�C��
#include "bullet.h"

//�O���錾
class CSquareHitbox;
class CLetter;

class CLaughBullet : public CBullet
{
public:
	CLaughBullet();																//�R���X�g���N�^
	~CLaughBullet() override;														//�f�X�g���N�^

	HRESULT Init(void) override;													//����������
	void Uninit(void) override;														//�I������
	void Update(void) override;														//�X�V����

	static CLaughBullet* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move);	//��������



private:

	CSquareHitbox* m_pHitbox;

};

#endif