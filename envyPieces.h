//=============================================================================
//
// envyPieces.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef ENVY_PIECES_H
#define ENVY_PIECES_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "bullet.h"

//=============================================================================
//�O���錾
//=============================================================================
class CCircleHitbox;

class CEnvyPieces : public CBullet
{
public:
	CEnvyPieces();																	//�R���X�g���N�^
	~CEnvyPieces() override;														//�f�X�g���N�^

	HRESULT Init(void) override;													//����������
	void Uninit(void) override;														//�I������
	void Update(void) override;														//�X�V����


	static CEnvyPieces* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move);		//��������
	static CEnvyPieces* Create(const D3DXVECTOR3 pos, const float radius);			//��������

private:

	CCircleHitbox* m_pHitbox;
};

#endif