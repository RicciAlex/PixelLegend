//=============================================================================
//
// starBullet.cpp
// Author : Ricci Alex
//
//=============================================================================

//�C���N���[�h�t�@�C��
#include "starBullet.h"
#include "starEffect.h"

//�R���X�g���N�^
CStarBullet::CStarBullet()
{
	//�����o�[�ϐ����N���A����
	for (int nCnt = 0; nCnt < MaxEffect; nCnt++)
	{
		m_pEffect[nCnt] = nullptr;
	}
}

//�f�X�g���N�^
CStarBullet::~CStarBullet()
{

}

//����������
HRESULT CStarBullet::Init(void)
{
	if (FAILED(CBullet::Init()))
	{//��{�N���X�̏���������
		return -1;
	}

	//�����o�[�ϐ�������������

	for (int nCnt = 0; nCnt < MaxEffect; nCnt++)
	{
		m_pEffect[nCnt] = nullptr;
	}

	return S_OK;
}

//�I������
void CStarBullet::Uninit(void)
{
	//�G�t�F�N�g�̔j������
	for (int nCnt = 0; nCnt < MaxEffect; nCnt++)
	{
		if (m_pEffect[nCnt] != nullptr)
		{//null�`�F�b�N
			m_pEffect[nCnt]->Release();			//���������������
			m_pEffect[nCnt] = nullptr;			//�|�C���^��null�ɂ���
		}
	}

	//��{�N���X�̏I������
	CBullet::Uninit();
}

//�X�V����
void CStarBullet::Update(void)
{
	//�G�t�F�N�g�̍X�V����
	for (int nCnt = 0; nCnt < MaxEffect; nCnt++)
	{
		if (m_pEffect[nCnt] != nullptr)
		{//null�`�F�b�N

			if (m_pEffect[nCnt]->GetActiveState())
			{//�܂���������

				m_pEffect[nCnt]->SetCenterPos(GetPos());			//���S�_�̐ݒ�
			}
			else
			{//�����Ɠ���������

				m_pEffect[nCnt]->Release();							//�G�t�F�N�g��j������
				m_pEffect[nCnt] = nullptr;							//�|�C���^��null�ɂ���
			}
		}
	}

	CBullet::Update();				//��{�N���X�̍X�V����
}



//��������
CStarBullet* CStarBullet::Create(const D3DXVECTOR3 CenterPos, const D3DXVECTOR3 move)
{
	CStarBullet* pBullet = new CStarBullet;			//�C���X�^���X�𐶐�����

	if (FAILED(pBullet->Init()))
	{//����������
		return nullptr;
	}

	pBullet->SetPos(CenterPos);						//���S�_�̐ݒ�
	pBullet->SetMove(move);							//���x�̐ݒ�
	pBullet->SetLife(240);							//�̗͂̐ݒ�

	//�G�t�F�N�g�̐���
	for (int nCnt = 0; nCnt < pBullet->MaxEffect; nCnt++)
	{
		pBullet->m_pEffect[nCnt] = CStarEffect::Create(CenterPos, 6.0f * nCnt * D3DX_PI / 80.0f, 18.0f * D3DX_PI / 40.0f, D3DXCOLOR(1.0f, 1.0f, 0.015f, 0.75f), D3DXVECTOR2(4.0f, 4.0f), 240);
	}

	return pBullet;					//���������C���X�^���X��Ԃ�
}