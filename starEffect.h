//=============================================================================
//
// starEffect.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef STAR_EFFECT_H
#define STAR_EFFECT_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "effect.h"

//�O���錾
class CCircleHitbox;

class CStarEffect : public CEffect
{
public:	
	CStarEffect();						//�R���X�g���N�^
	~CStarEffect() override;			//�f�X�g���N�^

	HRESULT Init(void) override;		//����������
	void Uninit(void) override;			//�I������
	void Update(void) override;			//�X�V����
	void Draw(void) override;			//�I������

	void SetCenterPos(const D3DXVECTOR3 center);			//���S�_�̐ݒ菈��
	void SetAngleMove(const float fAngle);					

	bool GetActiveState(void);

	static CStarEffect* Create(const D3DXVECTOR3 center, const float fAngleStart, 
		const float fAngleMove, const D3DXCOLOR col, const D3DXVECTOR2 size, const int Life);			//��������

private:

	D3DXVECTOR3 m_center;										//���S�_
	float m_fAngleStart;										//�A�j���[�V������ړ��p�̃J�E���^�[
	float m_fAngleSpeed;
	bool m_bActive;

	CCircleHitbox* m_pHitbox;
};


#endif