//=============================================================================
//
// target.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef TARGET_H
#define TARGET_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object2D.h"

class CTarget : public CObject_2D
{
public:
	CTarget();												//�R���X�g���N�^
	~CTarget() override;									//�f�X�g���N�^

	HRESULT Init(void) override;							//����������
	void Uninit(void) override;								//�I������
	void Update(void) override;								//�X�V����

	static CTarget* Create(void);							//��������

private:

};


#endif