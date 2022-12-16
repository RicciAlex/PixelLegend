//=============================================================================
//
// circleHitbox.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "circleHitbox.h"

//�R���X�g���N�^
CCircleHitbox::CCircleHitbox()
{
	//�����o�[�ϐ����N���A����
	m_fRadius = 0.0f;
}

//�f�X�g���N�^
CCircleHitbox::~CCircleHitbox()
{

}

//����������
HRESULT CCircleHitbox::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CHitbox::Init()))
	{
		return -1;
	}

	//�����o�[�ϐ��̏�����
	m_fRadius = 0.0f;
	SetShape(shape_Circle);

	return S_OK;
}

//�I������
void CCircleHitbox::Uninit(void)
{
	//��{�N���X�̏I������
	CHitbox::Uninit();
}

//�����蔻��
bool CCircleHitbox::Hit(void)
{
	CHitbox** pHitbox = GetAllHitbox();			
	//SetHitState(false);

	for (int nCnt = 0; nCnt < CHitbox::MaxHitbox; nCnt++)
	{
		if (pHitbox[nCnt] != nullptr && pHitbox[nCnt] != this)
		{
			CHitbox::Type type = pHitbox[nCnt]->GetType();				//��ނ̎擾����

			if (type == Type_Enemy && this->GetType() == Type_Player || 
				type == Type_Player && this->GetType() == Type_Enemy ||
				type == Type_Enemy && this->GetType() == Type_PlayerBullet ||
				type == Type_Player && this->GetType() == Type_EnemyBullet)
			{//��ނ̊m�F
				Shape shape = pHitbox[nCnt]->GetShape();				//�`�̎擾����

				switch (shape)
				{
				case shape_Square:

				{
					D3DXVECTOR3 pos = pHitbox[nCnt]->GetPos();			//�ʒu�̎擾
					D3DXVECTOR2 size = pHitbox[nCnt]->GetSize();		//�T�C�Y�̎擾

					//�����蔻��
					if (CircleSquareHit(pos, size))
					{
						SetHitState(true);						//����������Ԃɂ���

						if (type == Type_Enemy && this->GetType() == Type_Player)
						{//�v���C���[�͓G�ɓ��������ꍇ�A�G�Ƀ_���[�W��^���Ȃ����Ƃɂ���
							return true;
						}

						pHitbox[nCnt]->SetHitState(true);		//����𓖂�������Ԃɂ���
						return true;
					}

				}

				break;

				case shape_Circle:

				{
					D3DXVECTOR3 pos = pHitbox[nCnt]->GetPos();			//�ʒu�̎擾
					float radius = pHitbox[nCnt]->GetRadius();			//���a�̎擾

					//�����蔻��
					if (CircleCircleHit(pos, radius))
					{
						SetHitState(true);						//����������Ԃɂ���

						if (type == Type_Enemy && this->GetType() == Type_Player)
						{//�v���C���[�͓G�ɓ��������ꍇ�A�G�Ƀ_���[�W��^���Ȃ����Ƃɂ���
							return true;
						}

						pHitbox[nCnt]->SetHitState(true);		//����𓖂�������Ԃɂ���
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
const D3DXVECTOR2 CCircleHitbox::GetSize(void)
{
	return D3DXVECTOR2(0.0f, 0.0f);
}

//���a�̎擾����
const float CCircleHitbox::GetRadius(void)
{
	return m_fRadius;
}

//���a�̐ݒ菈��
void CCircleHitbox::SetRadius(const float radius)
{
	m_fRadius = radius;
}

//�ۂƎl�p�`�̓����蔻��
bool CCircleHitbox::CircleSquareHit(const D3DXVECTOR3 pos, const D3DXVECTOR2 size)
{
	//�ȗ��p�̃��[�J���ϐ�
	float fUp, fDown, fRight, fLeft;
	fUp = pos.y - m_fRadius - size.y;
	fDown = pos.y + m_fRadius + size.y;
	fRight = pos.x + m_fRadius + size.x;
	fLeft = pos.x - m_fRadius - size.x;

	D3DXVECTOR3 center = GetPos();		//���S�_�̎擾

	if (center.x >= fLeft && center.x <= fRight && center.y >= fUp && center.y <= fDown)
	{//����
		return true;
	}

	return false;
}

//�ۂƊۂ̓����蔻��
bool CCircleHitbox::CircleCircleHit(const D3DXVECTOR3 center, const float radius)
{
	D3DXVECTOR3 pos = GetPos();		//�ʒu�̎擾

	float fResult = ((pos.x - center.x) * (pos.x - center.x)) + (pos.y - center.y) * (pos.y - center.y);	//�������v�Z����
	float fRadius = (radius + m_fRadius) * (radius + m_fRadius);			//���a�̑����Z���v�Z����

	if (fResult < fRadius)
	{//����
		return true;
	}

	return false;
}


//=============================================================================
//
//								�ÓI�֐� 
//
//=============================================================================

//��������
CCircleHitbox* CCircleHitbox::Create(const D3DXVECTOR3 pos, const float fRadius, const Type type)
{
	CCircleHitbox* pHitbox = new CCircleHitbox;			//�C���X�^���X�𐶐�����

	//����������
	if (FAILED(pHitbox->Init()))
	{
		return nullptr;
	}

	pHitbox->SetPos(pos);			//�ʒu�̐ݒ�
	pHitbox->m_fRadius = fRadius;	//���a�̐ݒ�
	pHitbox->SetType(type);			//��ނ̐ݒ�

	return pHitbox;					//���������C���X�^���X��Ԃ�							
}	