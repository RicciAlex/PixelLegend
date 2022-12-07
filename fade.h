//=============================================================================
//
// fade.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef FADE_H
#define FADE_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "application.h"

//=============================================================================
//�O���錾
//=============================================================================
class CObject_2D;

class CFade
{
public:

	enum FADE
	{
		FADE_NONE = 0,			//�t�F�[�h���Ă��Ȃ�
		FADE_IN,				//�t�F�[�h�C��
		FADE_OUT,				//�t�F�[�h�A�E�g
		FADE_MAX
	};

	CFade();										//�R���X�g���N�^
	~CFade();										//�f�X�g���N�^
													
	HRESULT Init(void);								//����������
	void Uninit(void);								//�I������
	void Update(void);								//�X�V����
	void Draw(void);								//�`�揈��

	void SetFadeIn(void);							//�t�F�[�h�C���̐ݒ菈��
	void SetFadeOut(CApplication::Mode mode);		//�t�F�[�h�A�E�g�̐ݒ菈��


	static CFade* Create(void);						//��������

private:

	CObject_2D* m_pFade;							//�t�F�[�h�p�̃|���S��
	FADE m_fade;									//�t�F�[�h
	CApplication::Mode m_mode;						//���[�h

};

#endif