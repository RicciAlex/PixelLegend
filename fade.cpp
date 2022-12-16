//=============================================================================
//
// fade.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "fade.h"
#include "object2D.h"

//�R���X�g���N�^
CFade::CFade()
{
	//�����o�[�ϐ����N���A����
	m_fade = FADE_NONE;
	m_pFade = nullptr;
	m_mode = CApplication::Mode_Title;
}

//�f�X�g���N�^
CFade::~CFade()
{

}

//����������
HRESULT CFade::Init(void)
{
	//�����o�[�ϐ�������������
	m_pFade = nullptr;

	m_mode = CApplication::Mode_Title;

	m_fade = FADE_NONE;

	return S_OK;
}

//�I������
void CFade::Uninit(void)
{
	//�t�F�[�h�p�̃|���S����j������
	if (m_pFade != nullptr)
	{//null�`�F�b�N
		m_pFade->Release();			//���������������
		m_pFade = nullptr;			//null�ɂ���
	}
}

//�X�V����
void CFade::Update(void)
{
	switch (m_fade)
	{
	case CFade::FADE_NONE:

		break;

	case CFade::FADE_IN:

	{//�t�F�[�h�C����������
		if (m_pFade != nullptr)
		{//�t�F�[�h�p�̃|���S����null�ł͂Ȃ�������

			D3DXCOLOR col = m_pFade->GetColor();			//�F�̎擾

			col.a -= 0.025f;			//���l���X�V����

			if (col.a <= 0.0f)
			{//���l��0�ȉ��ɂȂ�����
				m_pFade->Release();					//�t�F�[�h�p�̃|���S����j������
				m_pFade = nullptr;					//�|�C���^��null�ɂ���
				m_fade = FADE_NONE;					//�t�F�[�h��Ԃ̐ݒ�
				CApplication::SetFade(false);		//�t�F�[�h���I��������Ƃ�ݒ肷��
			}
			else
			{
				m_pFade->SetColor(col);				//�F�̐ݒ�
			}
		}
		
	}

		break;

	case CFade::FADE_OUT:

	{//�t�F�[�h�A�E�g��������
		if (m_pFade != nullptr)
		{//null�`�F�b�N

			D3DXCOLOR col = m_pFade->GetColor();			//�F�̎擾

			col.a += 0.025f;			//���l�̍X�V

			if (col.a >= 1.0f)
			{//���l��
				m_pFade->Release();
				m_pFade = nullptr;
				m_fade = FADE_IN;

				CApplication::SetMode(m_mode);

				SetFadeIn();
			}
			else
			{
				m_pFade->SetColor(col);
			}
		}
	}

		break;

	default:
		break;
	}
}

//�`�揈��
void CFade::Draw(void)
{
	if (m_pFade != nullptr)
	{
		m_pFade->Draw();
	}
}




//�t�F�[�h�C���̐ݒ菈��
void CFade::SetFadeIn(void)
{
	m_fade = FADE_IN;

	CApplication::SetFade(true);

	if (m_pFade == nullptr)
	{
		m_pFade = CObject_2D::Create();

		if (m_pFade != nullptr)
		{
			m_pFade->SetTexture(CObject::TextureNull);
			m_pFade->SetTextureParameter(1, 1, 1, INT_MAX);
			m_pFade->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
			m_pFade->SetPos(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f));
			m_pFade->SetSize(D3DXVECTOR2((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f));
			m_pFade->SetStartingRot(D3DX_PI * 0.5f);
			m_pFade->SetPriority(5);
		}
	}
}

//�t�F�[�h�A�E�g�̐ݒ菈��
void CFade::SetFadeOut(CApplication::Mode mode)
{
	m_fade = FADE_OUT;

	CApplication::SetFade(true);

	if (m_pFade == nullptr)
	{
		m_pFade = CObject_2D::Create();

		if (m_pFade != nullptr)
		{
			m_pFade->SetTexture(CObject::TextureNull);
			m_pFade->SetTextureParameter(1, 1, 1, INT_MAX);
			m_pFade->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
			m_pFade->SetPos(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f));
			m_pFade->SetSize(D3DXVECTOR2((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f));
			m_pFade->SetStartingRot(D3DX_PI * 0.5f);
			m_pFade->SetPriority(5);

			m_mode = mode;
		}
	}
}

//��������
CFade* CFade::Create(void)
{
	CFade* pFade = new CFade;

	if (FAILED(pFade->Init()))
	{
		return nullptr;
	}

	pFade->SetFadeIn();

	return pFade;
}