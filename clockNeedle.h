//=============================================================================
//
// clockNeedle.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef CLOCK_NEEDLE_H
#define CLOCK_NEEDLE_H

//�C���N���[�h�t�@�C��
#include "bullet.h"

class CClockNeedle : public CBullet
{
public:
	CClockNeedle();																	//�R���X�g���N�^
	~CClockNeedle() override;														//�f�X�g���N�^

	HRESULT Init(void) override;													//����������
	void Uninit(void) override;														//�I������
	void Update(void) override;														//�X�V����

	bool Hit(void);																	//�e�̓����蔻��

	static CClockNeedle* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move,
		const D3DXVECTOR3 acc, const D3DXVECTOR2 dim);								//��������

private:

};

#endif // !CLOCK_NEEDLE_H