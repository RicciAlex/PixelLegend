//=============================================================================
//
// candle.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "candle.h"
#include "squareHitbox.h"
#include "bg.h"
#include "skullShield.h"
#include "Thanatos.h"

//�R���X�g���N�^
CCandle::CCandle()
{
	//�����o�[�ϐ����N���A����
	m_state = state_spawn;
	m_nCntState = 0;
	m_nIdx = 0;

	m_pParent = nullptr;
	m_pHitbox = nullptr;
	m_pBg = nullptr;
	m_pShield[0] = nullptr;
	m_pShield[1] = nullptr;
}

//�f�X�g���N�^
CCandle::~CCandle()
{

}

//����������
HRESULT CCandle::Init(void)
{
	//�����o�[�ϐ�������������
	if (FAILED(CEnemy::Init()))
	{
		return -1;
	}

	m_nCntState = 0;
	m_nIdx = -1;
	m_state = state_spawn;
	SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	m_pParent = nullptr;
	m_pHitbox = nullptr;
	m_pBg = nullptr;
	m_pShield[0] = nullptr;
	m_pShield[1] = nullptr;

	return S_OK;
}

//�I������
void CCandle::Uninit(void)
{
	//�q�b�g�{�b�N�X�̔j������
	if (m_pHitbox != nullptr)
	{//null�`�F�b�N
		m_pHitbox->Release();		//���������������
		m_pHitbox = nullptr;		//null�ɂ���
	}
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pShield[nCnt] != nullptr)
		{//null�`�F�b�N
			m_pShield[nCnt]->Release();			//���������������
			m_pShield[nCnt] = nullptr;			//null�ɂ���
		}
	}

	//�w�i�ւ̃|�C���^�Ɛe�ւ̃|�C���^��null�ɂ���
	if (m_pBg != nullptr)
	{
		m_pBg = nullptr;
	}
	if (m_pParent != nullptr)
	{
		m_pParent = nullptr;
	}

	//��{�N���X�̏I������
	CEnemy::Uninit();
}

//�X�V����
void CCandle::Update(void)
{
	switch (m_state)
	{//��Ԃɂ���čX�V����
	case CCandle::state_spawn:

	{//�X�|�[�����

		D3DXCOLOR col = GetColor();		//�F�̎擾

		col.a += 0.01f;					//���l�̍X�V

		SetColor(col);					//�F�̐ݒ�

		if (col.a >= 0.9f)
		{//���l��0.9f�𒴂�����
			m_state = state_off;		//��Ԃ��X�V����
		}
	}

		break;

	case CCandle::state_off:

	{//�΂����������

		if (m_pHitbox)
		{//null�`�F�b�N
			m_pHitbox->SetPos(GetPos());			//�ʒu�̐ݒ�

			if (m_pHitbox->GetHitState())
			{//����������
				m_pHitbox->SetHitState(false);		//�����Ă��Ȃ���Ԃɖ߂�
				int nLife = GetLife();				//�̗͂̎擾
				nLife += 100;						//�̗͂̍X�V
				SetLife(nLife);						//�̗͂̐ݒ�

				if (nLife >= 1500)
				{//�̗͂�1500�𒴂�����

					m_state = state_on;					//��Ԃ��X�V����
					SetAnimPattern(0);					//�A�j���V�����p�^�[���̐ݒ�
					SetTextureParameter(4, 5, 1, 10);	//�A�j���[�V�����p�����[�^�̐ݒ�

					if (m_pParent != nullptr)
					{//null�`�F�b�N
						m_pParent->AddLitCandle();		//�e�̂������E�\�N�̐����X�V����
					}

					if (m_pBg != nullptr)
					{//null�`�F�b�N
						m_pBg->SetVtxColor(m_nIdx, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));			//�w�i�̐F���X�V����
					}
				}
			}
		}
	}

		break;

	case CCandle::state_on:
		break;

	default:
		break;
	}

	//��{�N���X�̍X�V����
	CObject_2D::Update();
}

//�`�揈��
void CCandle::Draw(void)
{
	//��{�N���X�̕`�揈��
	CObject_2D::Draw();
}

//�e�ւ̃|�C���^�̐ݒ�
void CCandle::SetParent(CThanatos* pParent)
{
	m_pParent = pParent;
}

//�w�i�ւ̃|�C���^�̐ݒ菈��
void CCandle::SetBgPointer(CBg* pointer)
{
	m_pBg = pointer;
}

//��Ԃ̎擾����
CCandle::state CCandle::GetCandleState(void)
{
	return m_state;
}

//�΂���������
void CCandle::Unlit(void)
{
	m_state = state_off;												//��Ԃ̍X�V
	SetTextureParameter(1, 5, 1, INT_MAX);								//�e�N�X�`���p�����[�^�̐ݒ�
	SetAnimPattern(4);													//�A�j���V�����p�^�[���̐ݒ�
	m_pBg->SetVtxColor(m_nIdx, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));		//�w�i�̒��_�̐F�̐ݒ�
	SetLife(0);															//�̗͂̐ݒ�

	m_pShield[0]->AddRevolutionSpeed(D3DX_PI * 0.01f);					
	m_pShield[1]->AddRevolutionSpeed(D3DX_PI * 0.01f);					
}

//�j������
void CCandle::Despawn(void)
{
	D3DXCOLOR col = m_pShield[0]->GetColor();		//�F�̎擾

	if (col.a > 0.0f)
	{//�F�̃��l��0.0�ȏゾ������

		col.a -= 0.005f;				//���l���X�V����
		m_pShield[0]->SetColor(col);	//�F�̐ݒ�
	}

	col = m_pShield[1]->GetColor();					//�F�̎擾

	if (col.a > 0.0f)
	{//�F�̃��l��0.0�ȏゾ������
		col.a -= 0.005f;				//���l���X�V����
		m_pShield[1]->SetColor(col);	//�F�̐ݒ�
	}
}




//��������
CCandle* CCandle::Create(const D3DXVECTOR3 pos)
{
	CCandle* pCandle = new CCandle;				//�C���X�^���X�𐶐�����

	if (FAILED(pCandle->Init()))
	{//����������
		return nullptr;
	}

	pCandle->SetPos(pos);										//�ʒu�̐ݒ�
	pCandle->SetSize(D3DXVECTOR2(22.5f, 28.5f));				//�T�C�Y�̐ݒ�
	pCandle->SetTexture(CObject::TextureCandle);				//�e�N�X�`���̐ݒ�
	pCandle->SetTextureParameter(1, 5, 1, INT_MAX);				//�e�N�X�`���p�����[�^�̐ݒ�
	pCandle->SetAnimPattern(4);									//�A�j���V�����p�^�[���̐ݒ�
	pCandle->SetStartingRot(D3DX_PI * 0.5f);					//�����̏����l�̐ݒ�

	//�q�b�g�{�b�N�X�̐�������
	pCandle->m_pHitbox = CSquareHitbox::Create(pos, D3DXVECTOR2(12.0f, 13.0f), CHitbox::Type_Enemy);

	//���E�\�N�̃C���f�b�N�X�̐ݒ�
	if (pos.x < (float)SCREEN_WIDTH * 0.5f && pos.y < (float)SCREEN_HEIGHT * 0.5f)
	{
		pCandle->m_nIdx = 0;
	}
	else if (pos.x > (float)SCREEN_WIDTH * 0.5f && pos.y < (float)SCREEN_HEIGHT * 0.5f)
	{
		pCandle->m_nIdx = 1;
	}
	else if (pos.x < (float)SCREEN_WIDTH * 0.5f && pos.y > (float)SCREEN_HEIGHT * 0.5f)
	{
		pCandle->m_nIdx = 2;
	}
	else if (pos.x > (float)SCREEN_WIDTH * 0.5f && pos.y > (float)SCREEN_HEIGHT * 0.5f)
	{
		pCandle->m_nIdx = 3;
	}

	pCandle->m_pShield[0] = CSkullShield::Create(D3DXVECTOR3(pos.x, pos.y + 5.0f, 0.0f), 0.0f);
	pCandle->m_pShield[1] = CSkullShield::Create(D3DXVECTOR3(pos.x, pos.y + 10.0f, 0.0f), D3DX_PI);

	return pCandle;					//���������C���X�^���X��Ԃ�
}

CCandle* CCandle::Create(const D3DXVECTOR3 pos, CBg* pointer)
{
	CCandle* pCandle = new CCandle;				//�C���f�b�N�X�𐶐�����

	if (FAILED(pCandle->Init()))
	{//����������
		return nullptr;
	}

	pCandle->SetPos(pos);									//�ʒu�̐ݒ�
	pCandle->SetSize(D3DXVECTOR2(30.0f, 38.0f));			//�T�C�Y�̐ݒ�
	pCandle->SetTexture(CObject::TextureCandle);			//�e�N�X�`���̐ݒ�
	pCandle->SetTextureParameter(1, 5, 1, INT_MAX);			//�e�N�X�`���p�����[�^�̐ݒ�
	pCandle->SetAnimPattern(4);								//�A�j���V�����p�^�[���̐ݒ�
	pCandle->SetStartingRot(D3DX_PI * 0.5f);				//�����̏����l�̐ݒ�

															//�q�b�g�{�b�N�X�̐�������
	pCandle->m_pHitbox = CSquareHitbox::Create(pos, D3DXVECTOR2(12.0f, 13.0f), CHitbox::Type_Enemy);
	pCandle->m_pBg = pointer;				//���E�\�N�̔w�i�ւ̃|�C���^�̐ݒ�

	//���E�\�N�̃C���f�b�N�X�̐ݒ�
	if (pos.x < (float)SCREEN_WIDTH * 0.5f && pos.y < (float)SCREEN_HEIGHT * 0.5f)
	{
		pCandle->m_nIdx = 0;
	}
	else if (pos.x >(float)SCREEN_WIDTH * 0.5f && pos.y < (float)SCREEN_HEIGHT * 0.5f)
	{
		pCandle->m_nIdx = 1;
	}
	else if (pos.x < (float)SCREEN_WIDTH * 0.5f && pos.y >(float)SCREEN_HEIGHT * 0.5f)
	{
		pCandle->m_nIdx = 2;
	}
	else if (pos.x >(float)SCREEN_WIDTH * 0.5f && pos.y > (float)SCREEN_HEIGHT * 0.5f)
	{
		pCandle->m_nIdx = 3;
	}

	pCandle->m_pShield[0] = CSkullShield::Create(D3DXVECTOR3(pos.x, pos.y + 5.0f, 0.0f), 0.0f);
	pCandle->m_pShield[1] = CSkullShield::Create(D3DXVECTOR3(pos.x, pos.y + 10.0f, 0.0f), D3DX_PI);

	return pCandle;						//���������C���X�^���X��Ԃ�
}