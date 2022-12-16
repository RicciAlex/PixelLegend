//=============================================================================
//
// object.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object.h"
#include "object2D.h"
#include "player.h"
#include <random>

//=============================================================================
//�ÓI�����o�[�ϐ��̐錾 
//=============================================================================
int CObject::m_nNumAll = 0;										//���݂���|���S����
CObject* CObject::m_pObject[CObject::MaxObject] = {};			//�I�u�W�F�N�g�ւ̃|���^
int CObject::m_PlayerIdx = -1;
int CObject::m_nPriorityObjNum[CObject::Max_Priority] = {};
bool CObject::m_bPause = false;

//=============================================================================
//�R���X�g���N�^
//=============================================================================
CObject::CObject()
{
	m_nNumAll++;							//�|���S�����̍X�V����
	m_type = OBJECT_MAX;

	for (int nCnt = 0; nCnt < MaxObject; nCnt++)
	{
		if (m_pObject[nCnt] == nullptr)
		{
			m_pObject[nCnt] = this;
			m_pObject[nCnt]->m_nIdx = nCnt;
			break;
		}
	}

	m_nPriority = 3;

	m_nPriorityObjNum[m_nPriority - 1]++;
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CObject::~CObject()
{

}

//�I�u�W�F�N�g����������
void CObject::Release(void)
{
	m_nPriorityObjNum[m_nPriority - 1]--;
	int Idx = m_nIdx;					//�z��̃C���f�b�N�X��ۑ�����
	m_pObject[Idx]->Uninit();			//�I�u�W�F�N�g�̏I������
	delete m_pObject[Idx];				//�I�u�W�F�N�g������
	m_pObject[Idx] = nullptr;			//�|�C���^��null�ɂ���
}

//�I�u�W�F�N�g�̎�ނ̎擾����
const  CObject::EObjType CObject::GetObjType(void)
{
	return m_type;			//��ނ�Ԃ�
}

//�I�u�W�F�N�g�̎�ނ̐ݒ菈��
void CObject::SetObjType(const EObjType type)
{
	m_type = type;
}

//�v���C�I���e�B�̐ݒ菈��
void CObject::SetPriority(int nPriority)
{
	if (nPriority < 1)
	{//�v���C�I���e�B��0�ȉ���������A1�ɐݒ肷��
		nPriority = 1;
	}
	else if(nPriority > 5)
	{//�v���C�I���e�B��6�ȏゾ������A5�ɐݒ肷��
		nPriority = 5;
	}

	int nLastPriority = m_nPriority;

	m_nPriority = nPriority;					//�v���C�I���e�B�̐ݒ�

	//�z��̍X�V
	m_nPriorityObjNum[nLastPriority - 1]--;
	m_nPriorityObjNum[m_nPriority - 1]++;
}

//===============================================================================
//
//								�ÓI�֐�
//
//===============================================================================

//=============================================================================
//�S���̏I������
//=============================================================================
void CObject::ReleaseAll(void)
{
	for (int nCnt = 0; nCnt < MaxObject; nCnt++)
	{
		if (m_pObject[nCnt] != nullptr)
		{//�|�C���^��null�ł͂Ȃ�������
			delete m_pObject[nCnt];				//���������������
			m_pObject[nCnt] = nullptr;			//null�ɂ���
		}
	}

	m_nNumAll = 0;								//���݂��Ă���I�u�W�F�N�g��0�ɂ���

	for (int nCnt = 0; nCnt < Max_Priority; nCnt++)
	{
		m_nPriorityObjNum[nCnt] = 0;
	}	
}

//=============================================================================
//�S���̍X�V����
//=============================================================================
void CObject::UpdateAll(void)
{
	for (int nCnt = 0; nCnt < MaxObject; nCnt++)
	{
		if (m_pObject[nCnt] != nullptr)
		{//�|�C���^��null�ł͂Ȃ�������

			if (!m_bPause || m_pObject[nCnt]->m_type == OBJTYPE_MENU)
			{
				m_pObject[nCnt]->Update();				//�C���X�^���X�̍X�V����
			}
		}
	}
}

//=============================================================================
//�S���̕`�揈��
//=============================================================================
void CObject::DrawAll(void)
{
	for (int a = 1; a <= Max_Priority; a++)
	{
		for (int nCnt = 0; nCnt < MaxObject; nCnt++)
		{
			int nPriorityObj = 0;

			if (m_pObject[nCnt] != nullptr)
			{//�|�C���^��null�ł͂Ȃ�������
				if (m_pObject[nCnt]->m_nPriority == a)
				{
					m_pObject[nCnt]->Draw();				//�C���X�^���X�̕`�揈��

					nPriorityObj++;

					if (nPriorityObj >= m_nPriorityObjNum[a - 1])
					{
						break;
					}
				}
			}
		}
	}
}



//�I�u�W�F�N�g�̎擾����
CObject** CObject::GetObj(void)
{
	return m_pObject;
}

//�v���C���[�̃C���f�b�N�X�̕ۑ�����
void CObject::SavePlayerIdx(CPlayer* ptr)
{
	for (int nCnt = 0; nCnt < MaxObject; nCnt++)
	{
		if (m_pObject[nCnt] == ptr)
		{
			m_PlayerIdx = nCnt;
		}
	}
}

//�|�[�Y��Ԃ̐ݒ菈��
void CObject::SetPause(const bool bPause)
{
	m_bPause = bPause;
}

//�����蔻��(��)
bool CObject::CircleHit(D3DXVECTOR3* pos1, D3DXVECTOR3* pos2, float fRadius1, float fRadius2)
{
	float radius = (fRadius1 * fRadius1) + (fRadius2 * fRadius2);

	float deltaX = (pos2->x - pos1->x) * (pos2->x - pos1->x);
	float deltaY = (pos2->y - pos1->y) * (pos2->y - pos1->y);

	if (deltaX + deltaY <= radius)
	{
		return true;
	}

	return false;
}

bool CObject::CircleHit(D3DXVECTOR3* pos1, D3DXVECTOR3* pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2)
{
	float fRadius1 = 0.5f * ((size1.x) + (size1.y));
	float fRadius2 = 0.5f * ((size2.x) + (size2.y));

	float radius = (fRadius1 * fRadius1) + (fRadius2 * fRadius2);

	float deltaX = (pos2->x - pos1->x) * (pos2->x - pos1->x);
	float deltaY = (pos2->y - pos1->y) * (pos2->y - pos1->y);

	if ((deltaX + deltaY) <= radius)
	{
		return true;
	}

	return false;
}

//�����蔻��(�l�p�`)
bool CObject::HitBox(D3DXVECTOR3* pos1, D3DXVECTOR3* pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2)
{
	float top, bottom, right, left;
	left = pos2->x - (size1.x + size2.x);
	right = pos2->x + (size1.x + size2.x);
	top = pos2->y - (size1.y + size2.y);
	bottom = pos2->y + (size1.y + size2.y);

	if (pos1->x >= left && pos1->x <= right &&
		pos1->y >= top && pos1->y <= bottom)
	{
		return true;
	}

	return false;
}

D3DXVECTOR3 CObject::GetPerpendicularVersor(D3DXVECTOR3 V)
{
	D3DXVECTOR3 Result, Unit;
	float fHalfPi = D3DX_PI * 0.5f;

	Unit = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	if (V.y > Unit.y)
	{
		fHalfPi *= -1.0f;
	}

	D3DXVec3Normalize(&V, &V);

	float fDot = D3DXVec3Dot(&V, &Unit);

	float fAngle = (float)acos(fDot);

	Result = D3DXVECTOR3(cosf(fAngle + fHalfPi), sinf(fAngle + fHalfPi), 0.0f);

	return Result;
}

std::random_device rd;
std::mt19937 gen(rd());

//������Ԃ��֐�
int CObject::random(const int low, const int high)
{
	std::uniform_int_distribution<> dist(low, high);
	return dist(gen);
}