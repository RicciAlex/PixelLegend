//=============================================================================
//
// heartBullet.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "heartBullet.h"
#include "heartEffect.h"

//�R���X�g���N�^
CHeartBullet::CHeartBullet()
{
	//�����o�[�ϐ����N���A����
	for (int nCnt = 0; nCnt < MaxEffect; nCnt++)
	{
		m_pEffect[nCnt] = nullptr;
	}
}

//�f�X�g���N�^
CHeartBullet::~CHeartBullet()
{
	
}

//����������
HRESULT CHeartBullet::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CBullet::Init()))
	{
		return -1;
	}

	//�|�C���^��null�ɂ���
	for (int nCnt = 0; nCnt < MaxEffect; nCnt++)
	{
		if (m_pEffect[nCnt] != nullptr)
		{
			m_pEffect[nCnt]->Release();
			m_pEffect[nCnt] = nullptr;
		}
	}

	return S_OK;
}

//�I������
void CHeartBullet::Uninit(void)
{
	//��{�N���X�̏I������
	CBullet::Uninit();

	for (int nCnt = 0; nCnt < MaxEffect; nCnt++)
	{
		if (m_pEffect[nCnt] != nullptr)
		{
			m_pEffect[nCnt]->Release();
			m_pEffect[nCnt] = nullptr;
		}
	}
}

//�X�V����
void CHeartBullet::Update(void)
{
	//��{�N���X�̍X�V����
	CObject_2D::Update();

	D3DXVECTOR3 pos = GetPos();		//�ʒu�̎擾����

	for (int nCnt = 0; nCnt < 40; nCnt++)
	{
		if (m_pEffect[nCnt] != nullptr)
		{
			if (m_pEffect[nCnt]->GetActiveState())
			{
				m_pEffect[nCnt]->SetCenterPos(pos);
			}
			else
			{
				m_pEffect[nCnt]->Release();
				m_pEffect[nCnt] = nullptr;
			}
		}
	}

	int nLife = GetLife() - 1;

	if (nLife <= 0)
	{
		Release();
		return;
	}
	else
	{
		SetLife(nLife);
	}

	if (pos.x <= -50.0f || pos.y <= -50.0f || pos.x >= (float)SCREEN_WIDTH + 50.0f || pos.y >= (float)SCREEN_HEIGHT + 50.0f)
	{
		Release();
		return;
	}
}


//=============================================================================
//�ÓI�֐�
//=============================================================================

//��������
CHeartBullet* CHeartBullet::Create(const D3DXVECTOR3 CenterPos, const D3DXVECTOR3 move, const D3DXCOLOR col)
{
	CHeartBullet* pBullet = new CHeartBullet;		//�e�𐶐�����

	//��{�N���X�̏���������
	if (FAILED(pBullet->Init()))
	{
		return nullptr;
	}

	pBullet->SetPos(CenterPos);			//�ʒu�̐ݒ�
	pBullet->SetMove(move);				//���x�̐ݒ�

	for (int nCnt = 0; nCnt < 40; nCnt++)
	{
		pBullet->m_pEffect[nCnt] = CHeartEffect::Create(CenterPos, D3DX_PI * 0.05f * nCnt, D3DX_PI, col, D3DXVECTOR2(10.0f, 10.0f), 480);
	}

	return pBullet;						//�e��Ԃ�
} 