//=============================================================================
//
// ringEffect.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef RING_EFFECT_H
#define RING_EFFECT_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "effect.h"

class CRingEffect : public CEffect
{
public:
	CRingEffect();								//�R���X�g���N�^
	~CRingEffect() override;					//�f�X�g���N�^

	virtual HRESULT Init(void) override;		//����������
	virtual void Uninit(void) override;			//�I������
	virtual void Update(void) override;			//�X�V����
	virtual void Draw(void) override;			//�I������

	static CRingEffect* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, 
		const D3DXVECTOR2 size, const D3DXVECTOR2 deltaSize, const D3DXCOLOR col, const D3DXCOLOR deltaCol);			//��������

private:
	D3DXCOLOR m_deltaCol;						//�F�̌���
	D3DXVECTOR2 m_deltaSize;					//�T�C�Y�̌���
};

#endif
