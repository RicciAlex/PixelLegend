//=============================================================================
//
// ScyllaBody.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "ScyllaBody.h"
#include "squareHitbox.h"

//�R���X�g���N�^
CScyllaBody::CScyllaBody()
{
	//�����o�[�ϐ����N���A����
	m_pHitbox = nullptr;
}

//�f�X�g���N�^
CScyllaBody::~CScyllaBody()
{

}

//����������
HRESULT CScyllaBody::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CEnemy::Init()))
	{
		return -1;
	}

	//�����o�[�ϐ��̏�����
	SetTexture(CObject::TextureScyllaBody);
	SetTextureParameter(2, 2, 1, INT_MAX);

	return S_OK;
}

//�I������
void CScyllaBody::Uninit(void)
{
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}

	//��{�N���X�̏I������
	CEnemy::Uninit();
}

//�X�V����
void CScyllaBody::Update(void)
{
	//��{�N���X�̍X�V����
	CObject_2D::Update();

	m_pHitbox->SetPos(GetPos());
}

//�`�揈��
void CScyllaBody::Draw(void)
{
	//��{�N���X�̕`�揈��
	CEnemy::Draw();
}


//========================================================================================================
//										�ÓI�֐� 
//========================================================================================================


//��������
CScyllaBody* CScyllaBody::Create(void)
{
	CScyllaBody* pEnemy = new CScyllaBody;			//���������m�ۂ���

	//����������
	if (FAILED(pEnemy->Init()))
	{
		return nullptr;
	}

	D3DXVECTOR3 pos = D3DXVECTOR3((float)SCREEN_WIDTH * 0.9f, (float)SCREEN_HEIGHT * 0.450f, 0.0f);

	pEnemy->SetPos(pos);												//�ʒu�̐ݒ�
	pEnemy->SetSize(D3DXVECTOR2(140.0f, 250.0f));						//�T�C�Y�̐ݒ�
	pEnemy->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));						//���x�̐ݒ�
	pEnemy->SetStartingRot(D3DX_PI * 0.5f);								//��]�p�x�̐ݒ�
	pEnemy->SetSubtype(ENEMYTYPE_SCYLLA_BODY);							//�G�̎�ނ̐ݒ�

	pEnemy->m_pHitbox = CSquareHitbox::Create(pos, D3DXVECTOR2(70.0f, 250.0f), CHitbox::Type_Enemy);

	return pEnemy;
}