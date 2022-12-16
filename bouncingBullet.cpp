//=============================================================================
//
// bouncingBullet.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "bouncingBullet.h"
#include "circleHitbox.h"

//�R���X�g���N�^
CBouncingBullet::CBouncingBullet()
{
	//�����o�[�ϐ����N���A����
	m_pHitbox = nullptr;
}

//�f�X�g���N�^
CBouncingBullet::~CBouncingBullet()
{

}

//����������
HRESULT CBouncingBullet::Init(void)
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
void CBouncingBullet::Uninit(void)
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
void CBouncingBullet::Update(void)
{
	//�����̎擾�ƍX�V
	int nLife = GetLife();
	nLife--;

	if (nLife <= 0)
	{//������0�ȉ��ɂȂ�����A����
		Release();
		return;
	}
	else
	{//������0�ȏゾ������A������ݒ肷��
		SetLife(nLife);
	}

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

	//��ʂ��o��O�A���˂�����
	D3DXVECTOR3 pos, move;

	pos = GetPos();
	move = GetMove();
	pos += move;

	if (pos.x + GetSize().x <= 0.0f || pos.x + GetSize().x >= (float)SCREEN_WIDTH)
	{
		move.x *= -1.0f;
		SetMove(move);
	}

	if (pos.y + GetSize().y <= 0.0f || pos.y - GetSize().y >= (float)SCREEN_HEIGHT)
	{
		move.y *= -1.0f;
		SetMove(move);
	}

	//��{�N���X�̍X�V����
	CBullet::Update();
}


//=============================================================================
//
//								�ÓI�֐�
//
//=============================================================================



//��������
CBouncingBullet* CBouncingBullet::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move)
{
	CBouncingBullet* pBullet = new CBouncingBullet;		//�C���X�^���X�𐶐�����

	if (FAILED(pBullet->Init()))
	{//����������
		return nullptr;
	}

	pBullet->SetPos(pos);								//�ʒu�̐ݒ�
	pBullet->SetMove(move);								//���x�̐ݒ�
	pBullet->SetSize(D3DXVECTOR2(15.0f, 15.0f));		//�T�C�Y�̐ݒ�
	pBullet->SetTexture(CObject::TextureNormalEffect);	//�e�N�X�`���̐ݒ�
	pBullet->SetTextureParameter(1, 1, 1, INT_MAX);		//�e�N�X�`���p�����[�^�̐ݒ�
	pBullet->SetLife(300);								//�����̐ݒ�

	//�����_���ŐF��ݒ肷��
	int nColor = random(0, 5);
	D3DXCOLOR col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	switch (nColor)
	{
	case 0:
		col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		break;
	case 1:
		col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		break;
	case 2:
		col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
		break;
	case 3:
		col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		break;
	case 4:
		col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		break;
	case 5:
		col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
		break;
	default:
		break;
	}

	pBullet->SetColor(col);			//�F�̐ݒ�

	//�q�b�g�{�b�N�X�̐���
	pBullet->m_pHitbox = CCircleHitbox::Create(pos, 15.0f, CHitbox::Type_EnemyBullet);

	return pBullet;					//���������C���X�^���X��Ԃ�
}