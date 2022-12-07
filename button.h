//=============================================================================
//
// button.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef BUTTON_H
#define BUTTON_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object.h"

//=============================================================================
//�O���錾
//=============================================================================
class CLetter;
class CObject_2D;

class CButton
{
public:
	CButton();									//�R���X�g���N�^
	~CButton();									//�f�X�g���N�^

	HRESULT Init(void);							//����������
	void Uninit(void);							//�I������
	void Update(void);							//�X�V����
	void Draw(void);							//�`�揈��

	void SetPos(const D3DXVECTOR3 pos);			//�ʒu�̐ݒ菈��
	const D3DXVECTOR2 GetSize(void);			//�T�C�Y�̎擾����
	const D3DXVECTOR3 GetPos(void);				//�ʒu�̐ݒ菈��
	const bool GetTriggerState(void);

	static CButton* Create(const D3DXVECTOR3 pos, const 
		D3DXVECTOR2 size, const D3DXCOLOR BgCol, const char* Word);									//��������
	static CButton* Create(const D3DXVECTOR3 pos, const
		D3DXVECTOR2 size, const D3DXCOLOR BgCol, const D3DXCOLOR LettersCol, const char* Word);		//��������

private:

	static const int MaxWordLenght = 24;			//�����̍ő吔

	D3DXVECTOR3 m_pos;								//�ʒu
	D3DXVECTOR2 m_size;								//�T�C�Y
	D3DXVECTOR2 m_originalSize;						//�������̃T�C�Y
													
	float m_fCntAnim;								//�A�j���V�����J�E���^�[
	bool m_bTriggered;								//�}�E�X�J�[�\���Əd�Ȃ��Ă��邩�ǂ���
													
	CObject_2D* m_pBack;							//�w�i�ւ̃|�C���^
	CLetter* m_pLetter[MaxWordLenght];				//�{�^���̕����ւ̃|�C���^
};


#endif