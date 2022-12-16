//=============================================================================
//
// effect.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef EFFECT_H
#define EFFECT_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object2D.h"

class CEffect : public CObject_2D
{
public:
	CEffect();									//�R���X�g���N�^
	virtual ~CEffect() override;				//�f�X�g���N�^

	virtual HRESULT Init(void) override;		//����������
	virtual void Uninit(void) override;			//�I������
	virtual void Update(void) override;			//�X�V����

	const int GetLife(void);					//���C�t�̎擾����

	void SetMove(const D3DXVECTOR3 move);							//���x�̐ݒ菈��
	void SetLife(const int Life);									//���C�t�̐ݒ菈��

	static CEffect* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, 
		const D3DXCOLOR col, const D3DXVECTOR2 size, const int Life);		//��������

private:

	D3DXVECTOR3 m_move;							//���x
	int m_nLife;								//����
};

#endif