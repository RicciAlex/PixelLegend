//=============================================================================
//
// beam.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef BEAM_H
#define BEAM_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "bullet.h"

//=============================================================================
//�O���錾
//=============================================================================
class CSquareHitbox;

class CBeam : public CBullet
{
public:
	CBeam();							//�R���X�g���N�^
	~CBeam() override;					//�f�X�g���N�^

	HRESULT Init(void) override;		//����������
	void Uninit(void) override;			//�I������
	void Update(void) override;			//�X�V����
	void Draw(void) override;

	static CBeam* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const D3DXVECTOR2 size, D3DXCOLOR col);		//��������

private:

	CSquareHitbox* m_pHitbox;			//�q�b�g�{�b�N�X�ւ̃|�C���^
};

#endif