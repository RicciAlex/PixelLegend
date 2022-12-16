//=============================================================================
//
// bg.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "bg.h"

//�R���X�g���N�^
CBg::CBg()
{
	//�����o�[�ϐ����N���A����
	m_textMove = D3DXVECTOR2(0.0f, 0.0f);
}

//�f�X�g���N�^
CBg::~CBg()
{

}

//����������
HRESULT CBg::Init(void)
{
	if (FAILED(CObject_2D::Init()))
	{//��{�N���X�̏���������
		return -1;
	}

	SetTexture(CObject::TextureSeaBG);			//�e�N�X�`���̐ݒ�
	SetTextureParameter(2, 1, 2, 30);			//�e�N�X�`���p�����[�^�̐ݒ�
	m_textMove = D3DXVECTOR2(0.0f, 0.0f);		//�e�N�X�`���̈ړ��ʂ̐ݒ�

	SetPos(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f));	//�ʒu�̐ݒ�
	SetSize(D3DXVECTOR2((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f));		//�T�C�Y�̐ݒ�
	SetPriority(1);																		//�v���C�I���e�B�̐ݒ�

	return S_OK;
}

//�I������
void CBg::Uninit(void)
{
	//��{�N���X�̏I������
	CObject_2D::Uninit();
}

//�X�V����
void CBg::Update(void)
{
	//�A�j���[�V����
	MoveTexCoordinates(m_textMove);		

	//��{�N���X�̍X�V����
	CObject_2D::Update();
}

//�F�̐ݒ菈��
void CBg::SetColor(const D3DXCOLOR col)
{
	VERTEX_2D* pVtx = nullptr;		//���_���ւ̃|�C���^

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxbuff();		//���_�o�b�t�@�̏I��

	//���_�o�b�t�@�̃��b�N
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�̐F�̐ݒ�
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}


//��������
CBg* CBg::Create(const D3DXCOLOR col, const D3DXVECTOR2 textMove)
{
	CBg* pBg = new CBg;				//�C���X�^�𐶐�����

	if (FAILED(pBg->Init()))
	{//����������
		return nullptr;
	}

	pBg->SetStartingRot(D3DX_PI * 0.5f);			//�����̏����l�̐ݒ�
	pBg->SetColor(col);								//�F�̐ݒ�
	pBg->m_textMove = textMove;						//�A�j���V�������x�̐ݒ�

	return pBg;				//���������C���X�^���X��Ԃ�
}