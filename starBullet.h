//=============================================================================
//
// starBullet.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef STAR_BULLET_H
#define STAR_BULLET_H

//�C���N���[�h�t�@�C��
#include "bullet.h"

//�O���錾
class CStarEffect;

class CStarBullet : public CBullet
{
public:
	CStarBullet();						//�R���X�g���N�^
	~CStarBullet() override;			//�f�X�g���N�^

	HRESULT Init(void) override;		//����������
	void Uninit(void) override;			//�I������
	void Update(void) override;			//�X�V����

	static CStarBullet* Create(const D3DXVECTOR3 CenterPos, const D3DXVECTOR3 move);				//��������

private:

	static const int MaxEffect = 120;			//�G�t�F�N�g�̍ő吔

	CStarEffect* m_pEffect[MaxEffect];			//�G�t�F�N�g�ւ̃|�C���^
};



#endif