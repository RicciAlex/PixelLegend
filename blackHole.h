//=============================================================================
//
// blackHole.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef BLACK_HOLE_H
#define BLACK_HOLE_H

//�C���N���[�h�t�@�C��
#include "bullet.h"

//�e�N���X(CObject2D�̔h���N���X)
class CBlackHole : public CBullet
{
public:

	CBlackHole();																	//�R���X�g���N�^
	~CBlackHole() override;															//�f�X�g���N�^

	HRESULT Init(void) override;													//����������
	void Uninit(void) override;														//�I������
	void Update(void) override;														//�X�V����

	static CBlackHole* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move,
		const D3DXVECTOR3 acc, const D3DXVECTOR2 dim, const int nLife);				//��������

private:

};

#endif // !BLACK_HOLE_H