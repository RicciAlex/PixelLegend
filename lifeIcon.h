//=============================================================================
//
// lifeIcon.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef LIFE_ICON_H
#define LIFE_ICON_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object.h"

//=============================================================================
//�O���錾
//=============================================================================
class CObject_2D;

class CLifeIcon : public CObject
{
public:

	CLifeIcon();										//�R���X�g���N�^
	~CLifeIcon() override;								//�f�X�g���N�^

	HRESULT Init(void) override;						//����������
	void Uninit(void) override;							//�I������
	void Update(void) override;							//�X�V����
	void Draw(void) override;							//�`�揈��

	void SetPos(const D3DXVECTOR3 pos) override;		//�ʒu�̐ݒ菈��

	const D3DXVECTOR2 GetSize(void) override;			//�T�C�Y�̎擾����
	const D3DXVECTOR3 GetPos(void) override;			//�ʒu�̎擾����

	static CLifeIcon* Create(const D3DXVECTOR3 pos);	//��������

private:

	static const int MaxHeart = 5;						//�A�C�R���̍ő吔
														
	D3DXVECTOR3 m_pos;									//�ʒu
	D3DXVECTOR2 m_size;									//�T�C�Y
														
	CObject_2D* m_pHeart[MaxHeart];						//�A�C�R���ւ̃|�C���^

};

#endif