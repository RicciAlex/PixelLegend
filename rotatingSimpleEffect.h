//=============================================================================
//
// rotatinfSimpleEffect.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef ROT_SIMPLE_EFFECT_H
#define ROT_SIMPLE_EFFECT_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "effect.h"

class CRotSimpleEff : public CEffect
{
public:
	CRotSimpleEff();					//�R���X�g���N�^
	~CRotSimpleEff() override;			//�f�X�g���N�^

	HRESULT Init(void) override;		//����������
	void Uninit(void) override;			//�I������
	void Update(void) override;			//�X�V����
	void Draw(void) override;			//�I������

	//��������
	static CRotSimpleEff* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 target, const D3DXVECTOR3 move, const D3DXCOLOR col,
		const int Life, const D3DXCOLOR deltaCol, const D3DXVECTOR2 size, const float fFrameRot);										//��������

private:

	D3DXVECTOR3 m_target;				//�ړI�̈ʒu
	D3DXCOLOR m_deltaCol;				//�F�̌���

};

#endif