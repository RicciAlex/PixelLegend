//=============================================================================
//
// ringEffect.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "ringEffect.h"
#include "application.h"
#include "rendering.h"

//�R���X�g���N�^
CRingEffect::CRingEffect()
{
	//�����o�[�ϐ����N���A����
	m_deltaCol = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_deltaSize = D3DXVECTOR2(0.0f, 0.0f);
}

//�f�X�g���N�^
CRingEffect::~CRingEffect()
{

}

//����������
HRESULT CRingEffect::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CEffect::Init()))
	{
		return -1;
	}

	//�����o�[�ϐ��̏�����
	m_deltaCol = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_deltaSize = D3DXVECTOR2(0.0f, 0.0f);

	return S_OK;
}

//�I������
void CRingEffect::Uninit(void)
{
	//��{�N���X�̏I������
	CEffect::Uninit();
}

//�X�V����
void CRingEffect::Update(void)
{
	//��{�N���X�̍X�V
	CEffect::Update();

	D3DXCOLOR col = GetColor();							//�J�[���[�̎擾
	D3DXVECTOR2 size = D3DXVECTOR2(0.0f, 0.0f);	
	size = CObject_2D::GetSize();						//�T�C�Y�̎擾

	col += m_deltaCol;									//�J�[���[�̍X�V
	size += m_deltaSize;								//�T�C�Y�̂̍X�V

	if (size.x <= 0.0f || size.y <= 0.0f)
	{//�T�C�Y���O�ȉ��ɂȂ�����A����
		Release();
		return;
	}

	SetColor(col);										//�J�[���[�̐ݒ�
	SetSize(size);										//�T�C�Y�̂̐ݒ�
}

//�I������
void CRingEffect::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->CRenderer::GetDevice();

	//���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//��{�N���X�̕`�揈��
	CEffect::Draw();

	// �ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}


//==================================================================================================================
//
//		�ÓI�֐�
//
//==================================================================================================================

//��������
CRingEffect* CRingEffect::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move,
	const D3DXVECTOR2 size, const D3DXVECTOR2 deltaSize, const D3DXCOLOR col, const D3DXCOLOR deltaCol)
{
	CRingEffect* pEffect = new CRingEffect;						//�V�����G�t�F�N�g�𐶐�����

	//����������
	if (FAILED(pEffect->Init()))
	{
		return nullptr;
	}

	pEffect->SetPos(pos);										//�ʒu�̐ݒ�
	pEffect->SetMove(move);										//���x�̐ݒ�
	pEffect->SetSize(size);										//�T�C�Y�̐ݒ�
	pEffect->m_deltaSize = deltaSize;							
	pEffect->SetColor(col);										//�J�[���[�̐ݒ�
	pEffect->m_deltaCol = deltaCol;								
	pEffect->SetLife(600);										//���C�t�̐ݒ�

	pEffect->SetTexture(CObject::TextureRoundEffect);			//�e�N�X�`���̐ݒ�
	pEffect->SetTextureParameter(1, 1, 1, INT_MAX);				//�e�N�X�`���p�����[�^�̐ݒ�

	return pEffect;												//�G�t�F�N�g��Ԃ�
} 