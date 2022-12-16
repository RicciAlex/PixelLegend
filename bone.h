//=============================================================================
//
// bone.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef BONE_H
#define BONE_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "bullet.h"

//=============================================================================
//�O���錾
//=============================================================================
class CSquareHitbox;

class CBone : public CBullet
{
public:
	CBone();									//�R���X�g���N�^
	~CBone() override;							//�f�X�g���N�^

	HRESULT Init(void) override;				//����������
	void Uninit(void) override;					//�I������
	void Update(void) override;					//�X�V����

	static CBone* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move);			//��������

private:

	void Split(void);				//�܂�鏈��

	bool m_bBroken;					//�܂ꂽ���ǂ���

	CSquareHitbox* m_pHitbox;		//�q�b�g�{�b�N�X�ւ̃|�C���^

};

#endif