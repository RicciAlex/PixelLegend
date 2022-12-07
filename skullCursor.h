//=============================================================================
//
// skullCursor.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef SKULL_CURSOR_H
#define SKULL_CURSOR_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
//�O���錾
//=============================================================================
class CSpine;
class CSkull;

class CSkullCursor
{
public:
	CSkullCursor();						//�R���X�g���N�^
	~CSkullCursor();					//�f�X�g���N�^
										
	HRESULT Init(void);					//����������
	void Uninit(void);					//�I������
	void Update(void);					//�X�V����

	static CSkullCursor* Create(const D3DXVECTOR3 pos);		//��������

private:

	D3DXVECTOR3 m_skullPos;				//���̈ʒu
	
	CSpine* m_pSpine;					//�Ғłւ̃|�C���^
	CSkull* m_pSkull;					//���ւ̃|�C���^
};




#endif