//=============================================================================
//
// ScyllaBody.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef SCYLLABODY_H
#define SCYLLABODY_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "enemy.h"

//=============================================================================
//�O���錾
//=============================================================================
class CSquareHitbox;

class CScyllaBody : public CEnemy
{
public:
	CScyllaBody();								//�R���X�g���N�^
	~CScyllaBody() override;					//�f�X�g���N�^

	HRESULT Init(void) override;				//����������
	void Uninit(void) override;					//�I������
	void Update(void) override;					//�X�V����
	void Draw(void) override;					//�`�揈��


	static CScyllaBody* Create(void);			//��������

private:

	CSquareHitbox* m_pHitbox;					//�q�b�g�{�b�N�X�ւ̃|�C���^
};

#endif // !SCYLLABODY_H
