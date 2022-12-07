//=============================================================================
//
// balloon.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef BALLOON_H
#define BALLOON_H

//�C���N���[�h�t�@�C��
#include "bullet.h"

//�O���錾
class CCircleHitbox;

class CBalloonBullet : public CBullet
{
public:
	CBalloonBullet();																//�R���X�g���N�^
	~CBalloonBullet() override;														//�f�X�g���N�^

	HRESULT Init(void) override;													//����������
	void Uninit(void) override;														//�I������
	void Update(void) override;														//�X�V����

	static CBalloonBullet* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, D3DXCOLOR col);	//��������



private:

	CCircleHitbox* m_pHitbox;

};




#endif