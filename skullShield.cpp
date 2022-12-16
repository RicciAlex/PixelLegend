//=============================================================================
//
// skullShield.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "skullShield.h"
#include "circleHitbox.h"

//�R���X�g���N�^
CSkullShield::CSkullShield()
{
	//�����o�[�ϐ����N���A����
	m_pHitbox = nullptr;
}

//�f�X�g���N�^
CSkullShield::~CSkullShield()
{

}

//����������
HRESULT CSkullShield::Init(void)
{
	//�����o�[�ϐ�������������
	if (FAILED(CEnemy::Init()))
	{
		return -1;
	}

	m_pHitbox = nullptr;

	return S_OK;
}

//�I������
void CSkullShield::Uninit(void)
{
	//�q�b�g�{�b�N�X�̔j������
	if (m_pHitbox != nullptr)
	{//null�`�F�b�N
		m_pHitbox->Release();			//���������������
		m_pHitbox = nullptr;			//null�ɂ���
	}

	//��{�N���X�̏I������
	CEnemy::Uninit();
}

//�X�V����
void CSkullShield::Update(void)
{
	//�q�b�g�{�b�N�X�̍X�V
	if (m_pHitbox != nullptr)
	{//null�`�F�b�N
		m_pHitbox->SetPos(GetPos());			//�ʒu�̐ݒ�

		if (m_pHitbox->GetHitState())
		{//����������
			m_pHitbox->SetHitState(false);		//���ɖ߂�
			int nLife = GetLife();				//�̗͂̎擾

			nLife -= 100;						//�̗͂̍X�V

			if (nLife <= 0)
			{//�̗͂�0�ȉ��ɂȂ�����
				Release();						//���������������
				return;
			}
			else
			{
				SetLife(nLife);					//�̗͂̐ݒ�
			}
		}
	}

	//��{�N���X�̍X�V����
	CObject_2D::Update();
}

//�`�揈��
void CSkullShield::Draw(void)
{
	//��{�N���X�̕`�揈��
	CObject_2D::Draw();
}




//��������
CSkullShield* CSkullShield::Create(const D3DXVECTOR3 pos, const float fStartAngle)
{
	CSkullShield* pEnemy = new CSkullShield;				//�C���X�^���X�𐶐�����

	if (FAILED(pEnemy->Init()))
	{//����������
		return nullptr;
	}

	pEnemy->SetPos(pos);									//�ʒu�̐ݒ�
	pEnemy->SetStartingRot(D3DX_PI * 0.5f);					//�����̏����l�̐ݒ�
	pEnemy->SetPresentRevolutionAngle(fStartAngle);			//���݂̌��]�p�x�̐ݒ�
	pEnemy->SetTexture(CObject::TextureSkullShield);		//�e�N�X�`���̐ݒ�
	pEnemy->SetTextureParameter(1, 1, 1, INT_MAX);			//�e�N�X�`���p�����[�^�̐ݒ�
	pEnemy->SetRevolution(pos, D3DX_PI * 0.01f, 60.0f);		//���]�̐ݒ�
	pEnemy->SetSize(D3DXVECTOR2(22.5f, 22.5f));				//�T�C�Y�̐ݒ�
	pEnemy->SetLife(30000);									//�̗͂̐ݒ�

	//�q�b�g�{�b�N�X�̐���
	pEnemy->m_pHitbox = CCircleHitbox::Create(pEnemy->GetPos(), 18.0f, CHitbox::Type_Enemy);

	return pEnemy;					//���������C���X�^���X��Ԃ�
}