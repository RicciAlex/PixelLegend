//=============================================================================
//
// skullShield.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef SKULL_SHIELD_H
#define SKULL_SHIELD_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "enemy.h"

//=============================================================================
//�O���錾
//=============================================================================
class CCircleHitbox;

class CSkullShield : public CEnemy
{
public:
	CSkullShield();
	~CSkullShield() override;								//�f�X�g���N�^

	virtual HRESULT Init(void) override;				//����������
	virtual void Uninit(void) override;					//�I������
	virtual void Update(void) override;					//�X�V����
	virtual void Draw(void) override;					//�`�揈��

	static CSkullShield* Create(const D3DXVECTOR3 pos, const float fStartAngle);		//��������

private:

	CCircleHitbox* m_pHitbox;
};

#endif