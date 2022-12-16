//=============================================================================
//
// envyPieces.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "envyPieces.h"
#include "circleHitbox.h"

//�R���X�g���N�^
CEnvyPieces::CEnvyPieces()
{
	//�����o�[�ϐ����N���A����
	m_pHitbox = nullptr;
}

//�f�X�g���N�^
CEnvyPieces::~CEnvyPieces()
{

}

//����������
HRESULT CEnvyPieces::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CBullet::Init()))
	{
		return -1;
	}

	//�����o�[�ϐ�������������
	m_pHitbox = nullptr;

	return S_OK;
}

//�I������
void CEnvyPieces::Uninit(void)
{
	//�q�b�g�{�b�N�X�̔j��
	if (m_pHitbox != nullptr)
	{//null�`�F�b�N
		m_pHitbox->Release();		//���������������
		m_pHitbox = nullptr;		//�|�C���^��null�ɂ���
	}

	//��{�N���X�̏I������
	CBullet::Uninit();
}

//�X�V����
void CEnvyPieces::Update(void)
{
	//��{�N���X�̍X�V����
	CObject_2D::Update();

	//�q�b�g�{�b�N�X�̍X�V����
	if (m_pHitbox != nullptr)
	{//null�`�F�b�N

		m_pHitbox->SetPos(GetPos());		//�q�b�g�{�b�N�X�̈ʒu�̍X�V

		if (m_pHitbox->Hit())
		{//�����Ɠ���������A����
			Release();
			return;
		}
	}

	//��ʂ��o����A����
	if (GetPos().y >= 900.0f)
	{
		Release();
		return;
	}
}


//=============================================================================
//
//								�ÓI�֐�
//
//=============================================================================



//��������
CEnvyPieces* CEnvyPieces::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move)
{
	CEnvyPieces* pBullet = new CEnvyPieces;		//�C���X�^���X�𐶐�����

	if (FAILED(pBullet->Init()))
	{//����������
		return nullptr;
	}

	pBullet->SetPos(pos);													//�ʒu�̐ݒ�
	pBullet->SetMove(move);													//���x�̐ݒ�
	pBullet->SetAcceleration(D3DXVECTOR3(0.0f, 0.05f, 0.0f));				//�����̐ݒ�
	pBullet->SetSize(D3DXVECTOR2(15.0f, 15.0f));							//�T�C�Y�̐ݒ�
	pBullet->SetRotation(D3DX_PI * ((float)random(-50, 50) * 0.002f));		//��]������

	//�����_���Ńe�N�X�`����ݒ肷��
	int randomizer = random(0, 2);

	switch (randomizer)
	{
	case 0:

		pBullet->SetTexture(CObject::TextureGear);
		pBullet->SetTextureParameter(1, 3, 2, INT_MAX);
		pBullet->SetAnimPattern(random(0, 5));

		break;

	case 1:

		pBullet->SetTexture(CObject::TextureSpringAndScrew);
		pBullet->SetTextureParameter(1, 2, 1, INT_MAX);
		pBullet->SetAnimPattern(1);

		break;

	case 2:

		pBullet->SetTexture(CObject::TextureSpringAndScrew);
		pBullet->SetTextureParameter(1, 2, 1, INT_MAX);
		pBullet->SetAnimPattern(2);

		break;

	default:
		break;
	}

	//�q�b�g�{�b�N�X�̐���
	pBullet->m_pHitbox = CCircleHitbox::Create(pos, 14.0f, CHitbox::Type_EnemyBullet);

	return pBullet;			//���������C���X�^���X��Ԃ�
	
}

//��������
CEnvyPieces* CEnvyPieces::Create(const D3DXVECTOR3 pos, const float radius)
{
	CEnvyPieces* pBullet = new CEnvyPieces;		//�C���X�^���X�𐶐�����

	if (FAILED(pBullet->Init()))
	{//����������
		return nullptr;
	}

	//�����_���ő��x�̐ݒ肷��
	D3DXVECTOR3 P = pos;
	P.x += (float)random((int)-radius, (int)radius);
	P.y += (float)random((int)-radius, (int)radius);

	D3DXVECTOR3 move = D3DXVECTOR3((float)random(-1000, 1000), (float)random(-1000, 1000), 0.0f);
	D3DXVec3Normalize(&move, &move);
	int K = random(2, 7);
	move.x *= (float)K;
	move.y *= (float)K;

	pBullet->SetPos(P);														//�ʒu�̐ݒ�
	pBullet->SetMove(move);													//���x�̐ݒ�
	pBullet->SetAcceleration(D3DXVECTOR3(0.0f, 0.05f, 0.0f));				//�����̐ݒ�
	pBullet->SetSize(D3DXVECTOR2(15.0f, 15.0f));							//�T�C�Y�̐ݒ�
	pBullet->SetRotation(D3DX_PI * ((float)random(-50, 50) * 0.002f));		//��]������


	//�����_���Ńe�N�X�`����ݒ肷��
	int randomizer = random(0, 2);

	switch (randomizer)
	{
	case 0:

		pBullet->SetTexture(CObject::TextureGear);
		pBullet->SetTextureParameter(1, 3, 2, INT_MAX);
		pBullet->SetAnimPattern(random(0, 5));

		break;

	case 1:

		pBullet->SetTexture(CObject::TextureSpringAndScrew);
		pBullet->SetTextureParameter(1, 2, 1, INT_MAX);
		pBullet->SetAnimPattern(1);

		break;

	case 2:

		pBullet->SetTexture(CObject::TextureSpringAndScrew);
		pBullet->SetTextureParameter(1, 2, 1, INT_MAX);
		pBullet->SetAnimPattern(2);

		break;

	default:
		break;
	}

	return pBullet;				//���������C���X�^���X��Ԃ�
}
