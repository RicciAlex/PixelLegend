//=============================================================================
//
// spine.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef SPINE_H
#define SPINE_H

//=============================================================================
//�C���N���[�h�t�@�C���ƑO���錾
//=============================================================================
#include "object.h"
class CVertebra;

class CSpine : public CObject
{
public:

	static const int VertebraNumber = 8;					//���̐�


	CSpine();												//�R���X�g���N�^
	~CSpine() override;										//�f�X�g���N�^
															
	HRESULT Init(void) override;							//����������
	void Uninit(void) override;								//�I������
	void Update(void) override;								//�X�V����
	void Draw(void) override;								//�`�揈��

	void SetPos(const D3DXVECTOR3 pos);						//�ʒu�̐ݒ菈��
	void SetHeadPos(const D3DXVECTOR3 pos);					//���̈ʒu�̐ݒ菈��

	const D3DXVECTOR2 GetSize(void) override;				//�T�C�Y�̎擾����
	const D3DXVECTOR3 GetPos(void) override;				//�ʒu�̐ݒ菈��

	void Kill(void);										//���S�A�j���[�V�����̐ݒ菈��
	void Flip(void);

	static CSpine* Create(D3DXVECTOR3 anchor, D3DXVECTOR3 head);		//��������

private:

	CVertebra* m_pVertebra[VertebraNumber];
	D3DXVECTOR3 m_anchor;									//�ʒu�̐ݒ菈��
	D3DXVECTOR3 m_head;										//���̈ʒu�̐ݒ菈��
	int m_nCntDestroy;										//���S�A�j���[�V�����p�̃J�E���^�[
	bool m_bDead;											//����ł��邩�ǂ���
};															



#endif