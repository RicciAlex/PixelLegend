//=============================================================================
//
// enemyLife.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef ENEMY_LIFE_H
#define ENEMY_LIFE_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object.h"

//=============================================================================
//�O���錾
//=============================================================================
class CLetter;

class CEnemyLife : public CObject
{
public:

	CEnemyLife();										//�R���X�g���N�^
	~CEnemyLife() override;								//�f�X�g���N�^

	HRESULT Init(void) override;						//����������
	void Uninit(void) override;							//�I������
	void Update(void) override;							//�X�V����
	void Draw(void) override;							//�`�揈��

	void SetPos(const D3DXVECTOR3 pos) override;		//�ʒu�̐ݒ菈��

	const D3DXVECTOR2 GetSize(void) override;			//�T�C�Y�̎擾����
	const D3DXVECTOR3 GetPos(void) override;			//�ʒu�̎擾����

	void SetLife(const int nLife);						//�̗͂̐ݒ菈��
	void SubtractLife(const int nLife);					//�̗͂̈����Z����

	static CEnemyLife* Create(const D3DXVECTOR3 pos, const D3DXCOLOR NameCol, const int MaxLife , const char* pName);		//��������

private:

	static const int MaxNameLenght = 24;				//�����̍ő吔
	static const int MaxDigit = 24;						//���l�̍ő吔

	D3DXVECTOR3 m_pos;									//�ʒu
	D3DXVECTOR2 m_size;									//�T�C�Y
														
	int m_nMaxLife;										//�ő�̗̑�
	int m_nLife;										//���݂̗̑�
														
	CLetter* m_pName[MaxNameLenght];					//�����ւ̃|�C���^
	CLetter* m_pLife[MaxDigit];							//���l�ւ̃|�C���^

};

#endif