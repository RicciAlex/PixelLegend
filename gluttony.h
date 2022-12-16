//=============================================================================
//
// gluttony.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef GLUTTONY_H
#define GLUTTONY_H

//�C���N���[�h�t�@�C��
#include "enemy.h"

//�O���錾
class CSquareHitbox;
class CMaw;
class CBackMaw;
class CHeart;

class CGluttony
{
public:
	CGluttony();						//�R���X�g���N�^
	~CGluttony();						//�f�X�g���N�^

	HRESULT Init(void);					//����������
	void Uninit(void);					//�I������
	void Update(void);					//�X�V����

	const bool GetEnd(void);			//�I��������ǂ����̐ݒ菈��

	static CGluttony* Create(void);				//��������

private:

	static const int MaxMaw = 3;		//����̓G�̐�

	int m_nTargetFrame;					//�ړI�̃t���[��
	int m_nCntState;					//��ԃJ�E���^�[
	int m_nPhase;						//�J�E���^�[
										
	CSquareHitbox* m_pHitbox;			//�q�b�g�{�b�N�X�ւ̃|�C���^
	CMaw*     m_pMaw[MaxMaw];			//����̓G�ւ̃|�C���^
	CBackMaw* m_pBackMaw;				//�w�i�̓G�ւ̃|�C���^
	CHeart*   m_pHeart;					//�S�ւ̃|�C���^
};

#endif