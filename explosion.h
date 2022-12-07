//=============================================================================
//
// explosion.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef EXPLOSION_H
#define EXPLOSION_H

//�C���N���[�h�t�@�C��
#include "object2D.h"

//�����̃N���X
class CExplosion : public CObject_2D
{
public:
	CExplosion();							//�R���X�g���N�^
	~CExplosion() override;					//�f�X�g���N�^
											
	HRESULT Init(void) override;			//����������
	void Uninit(void) override;				//�I������
	void Update(void) override;				//�X�V����

	static CExplosion* Create(void);		//��������
											
private:									
	int m_nLastPattern;						//�O��̃A�j���[�V�����p�^�[��
};

#endif // !EXPLOSION_H
