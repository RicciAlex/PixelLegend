//=============================================================================
//
// rotatinfSimpleEffect.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "rotatingSimpleEffect.h"

//�R���X�g���N�^
CRotSimpleEff::CRotSimpleEff()
{
	//�����o�[�ϐ����N���A����
	m_target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_deltaCol = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//�f�X�g���N�^
CRotSimpleEff::~CRotSimpleEff()
{

}

//����������
HRESULT CRotSimpleEff::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CEffect::Init()))
	{
		return -1;
	}

	//�����o�[�ϐ��̏�����
	m_target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_deltaCol = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

	return S_OK;
}

//�I������
void CRotSimpleEff::Uninit(void)
{
	//��{�N���X�̏I������
	CEffect::Uninit();
}

//�X�V����
void CRotSimpleEff::Update(void)
{
	//��{�N���X�̍X�V����
	CEffect::Update();

	D3DXVECTOR3 pos = GetPos();					//�ʒu�̎擾
	D3DXCOLOR col = GetColor();					//�J�[���[�̎擾
												
	pos += GetMove();							//�ʒu�̍X�V
	col += m_deltaCol;							//�J�[���[�̍X�V

	if (sqrtf((((pos.x - m_target.x) * (pos.x - m_target.x))) + ((pos.y - m_target.y) * (pos.y - m_target.y))) <= 5.0f)
	{//�ړI�̈ʒu�ɒ�������A����
		Release();
		return;
	}

	SetPos(pos);								//�ʒu�̐ݒ�
	SetColor(col);								//�J�[���[�̐ݒ�
}

//�I������
void CRotSimpleEff::Draw(void)
{
	//��{�N���X�̕`�揈��
	CEffect::Draw();
}

//==================================================================================================================
//
//		�ÓI�֐�
//
//==================================================================================================================


//��������
CRotSimpleEff* CRotSimpleEff::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 target, const D3DXVECTOR3 move, const D3DXCOLOR col, const int Life, const D3DXCOLOR deltaCol, const D3DXVECTOR2 size, const float fFrameRot)
{
	CRotSimpleEff* pEffect = new CRotSimpleEff;			//�V�����G�t�F�N�g�𐶐�����

	//����������
	if (FAILED(pEffect->Init()))
	{
		return nullptr;
	}

	pEffect->SetPos(pos);								//�ʒu�̐ݒ�
	pEffect->m_target = target;							//�ړI�̈ʒu�̐ݒ�
	pEffect->SetMove(move);								//���x�̐ݒ�
	pEffect->SetColor(col);								//�J�[���[�̐ݒ�
	pEffect->SetLife(Life);								//���C�t�̐ݒ�
	pEffect->m_deltaCol = deltaCol;						//�F�̌����̐ݒ�
	pEffect->SetRotation(fFrameRot);					//��]���x�̐ݒ�
	pEffect->SetSize(size);								//�T�C�Y�̐ݒ�
	pEffect->SetTexture(CObject::TextureRoundEffect);	//�e�N�X�`���̐ݒ�
	pEffect->SetTextureParameter(1, 1, 1, INT_MAX);		//�e�N�X�`���p�����[�^�̐ݒ�

	return pEffect;										//�G�t�F�N�g��Ԃ�
} 