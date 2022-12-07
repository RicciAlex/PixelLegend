//=============================================================================
//
// beam.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "beam.h"
#include "application.h"
#include "rendering.h"
#include "squareHitbox.h"

//�R���X�g���N�^
CBeam::CBeam()
{
	//�����o�[�ϐ����N���A����
	m_pHitbox = nullptr;
}

//�f�X�g���N�^
CBeam::~CBeam()
{

}

//����������
HRESULT CBeam::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CBullet::Init()))
	{
		return -1;
	}

	return S_OK;
}

//�I������
void CBeam::Uninit(void)
{
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}

	//��{�N���X�̏I������
	CBullet::Uninit();
}

//�X�V����
void CBeam::Update(void)
{
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->SetPos(GetPos());

		m_pHitbox->Hit();
	}

	//��{�N���X�̍X�V����
	CBullet::Update();
}

//�`�揈��
void CBeam::Draw(void)
{
	//�f�o�C�X�̎擾����
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->CRenderer::GetDevice();

	//���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//��{�N���X�̕`�揈��
	CObject_2D::Draw();

	// �ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}


//=============================================================================
//�ÓI�֐�
//=============================================================================


//��������
CBeam* CBeam::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const D3DXVECTOR2 size, D3DXCOLOR col)
{
	CBeam* pBullet = new CBeam;				//�V�����e�̐���

	//����������
	if (FAILED(pBullet->Init()))
	{
		return nullptr;
	}

	pBullet->SetPos(pos);					//�ʒu�̐ݒ�
	pBullet->SetMove(move);					//���x�̐ݒ�
	pBullet->SetSize(size);					//�T�C�Y�̐ݒ�
	pBullet->SetTexture(TextureNull);
	pBullet->SetTextureParameter(1, 1, 1, INT_MAX);

	pBullet->m_pHitbox = CSquareHitbox::Create(pos, size, CHitbox::Type_EnemyBullet);
	
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = pBullet->GetVtxbuff();			//���_�o�b�t�@�̎擾����
	VERTEX_2D* pVtx = nullptr;											//���_���ւ̃|�C���^

	//���_�o�b�t�@�̃��b�N
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J�[���[�̐ݒ�
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();

	return pBullet;				//�e��Ԃ�
} 