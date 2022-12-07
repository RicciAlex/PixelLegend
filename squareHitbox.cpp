//=============================================================================
//
// squareHitbox.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "squareHitbox.h"

//�R���X�g���N�^
CSquareHitbox::CSquareHitbox()
{
	//�����o�[�ϐ����N���A����
	m_size = D3DXVECTOR2(0.0f, 0.0f);
}

//�f�X�g���N�^
CSquareHitbox::~CSquareHitbox()
{

}

//����������
HRESULT CSquareHitbox::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CHitbox::Init()))
	{
		return -1;
	}

	//�����o�[�ϐ��̏�����
	m_size = D3DXVECTOR2(0.0f, 0.0f);
	SetShape(shape_Square);

	return S_OK;
}

//�I������
void CSquareHitbox::Uninit(void)
{
	//��{�N���X�̏I������
	CHitbox::Uninit();
}

//�����蔻��
bool CSquareHitbox::Hit(void)
{
	CHitbox** pHitbox = GetAllHitbox();

	//if (GetType() != Type_Player && GetType() != Type_Enemy)
	//{
	//	SetHitState(false);
	//}

	for (int nCnt = 0; nCnt < CHitbox::MaxHitbox; nCnt++)
	{
		if (pHitbox[nCnt] != nullptr)
		{
			CHitbox::Type type = pHitbox[nCnt]->GetType();					//��ނ̎擾����

			if (type == Type_Enemy && this->GetType() == Type_Player ||
				type == Type_Player && this->GetType() == Type_Enemy ||
				type == Type_Enemy && this->GetType() == Type_PlayerBullet ||
				type == Type_Player && this->GetType() == Type_EnemyBullet)
			{
				Shape shape = pHitbox[nCnt]->GetShape();					//�`�̎擾����

				switch (shape)
				{
				case shape_Square:

				{
					D3DXVECTOR3 pos = pHitbox[nCnt]->GetPos();				//�ʒu�̎擾
					D3DXVECTOR2 size = pHitbox[nCnt]->GetSize();			//�T�C�Y�̎擾

					if (SquareSquareHit(pos, size))
					{
						SetHitState(true);

						if (type == Type_Enemy && this->GetType() == Type_Player)
						{
							return true;
						}

						pHitbox[nCnt]->SetHitState(true);
						return true;
					}

				}

				break;

				case shape_Circle:

				{
					D3DXVECTOR3 pos = pHitbox[nCnt]->GetPos();				//�ʒu�̎擾
					float radius = pHitbox[nCnt]->GetRadius();				//���a�̎擾

					if (SquareCircleHit(pos, radius))
					{
						SetHitState(true);

						if (type == Type_Enemy && this->GetType() == Type_Player)
						{
							return true;
						}

						pHitbox[nCnt]->SetHitState(true);
						return true;
					}
				}
				break;

				default:
					break;
				}
			}
		}
	}

	return false;
}

//�T�C�Y�̎擾����
const D3DXVECTOR2 CSquareHitbox::GetSize(void)
{
	return m_size;
}

const float CSquareHitbox::GetRadius(void)
{
	return 0.0f;
}

//�T�C�Y�̐ݒ菈��
void CSquareHitbox::SetSize(const D3DXVECTOR2 size)
{
	m_size = size;
}

//�l�p�`�Ǝl�p�`�̓����蔻��
bool CSquareHitbox::SquareSquareHit(const D3DXVECTOR3 pos, const D3DXVECTOR2 size)
{
	D3DXVECTOR2 Size = GetSize();
	float fUp, fDown, fRight, fLeft;
	fUp = GetPos().y - size.y - Size.y;
	fDown = GetPos().y + size.y + Size.y;
	fRight = GetPos().x + size.x + Size.x;
	fLeft = GetPos().x - size.x - Size.x;

	if (pos.x >= fLeft && pos.x <= fRight && pos.y >= fUp && pos.y <= fDown)
	{
		return true;
	}

	return false;
}

//�l�p�`�Ɗۂ̓����蔻��
bool CSquareHitbox::SquareCircleHit(const D3DXVECTOR3 center, const float radius)
{
	float fUp, fDown, fRight, fLeft;
	D3DXVECTOR2 size = GetSize();
	fUp = GetPos().y - radius - size.y;
	fDown = GetPos().y + radius + size.y;
	fRight = GetPos().x + radius + size.x;
	fLeft = GetPos().x - radius - size.x;

	if (center.x >= fLeft && center.x <= fRight && center.y >= fUp && center.y <= fDown)
	{
		return true;
	}

	return false;
}


//=============================================================================
//�ÓI�֐� 
//=============================================================================


//��������
CSquareHitbox* CSquareHitbox::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const Type type)
{
	CSquareHitbox* pHitbox = new CSquareHitbox;			//����

	//����������
	if (FAILED(pHitbox->Init()))
	{
		return nullptr;
	}

	pHitbox->SetPos(pos);								//�ʒu�̐ݒ�
	pHitbox->SetSize(size);								//�T�C�Y�̐ݒ�
	pHitbox->SetType(type);								//��ނ̎擾

	return pHitbox;
}