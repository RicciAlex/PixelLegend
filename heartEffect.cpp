//=============================================================================
//
// heartEffect.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "heartEffect.h"
#include "circleHitbox.h"

//�R���X�g���N�^
CHeartEffect::CHeartEffect()
{
	//�����o�[�ϐ����N���A����
	m_fAngleStart = 0.0f;
	m_fAngleSpeed = 0.0f;
	m_bActive = false;

	m_pHitbox = nullptr;
}

//�f�X�g���N�^
CHeartEffect::~CHeartEffect()
{

}

//����������
HRESULT CHeartEffect::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CEffect::Init()))
	{
		return -1;
	}

	//�����o�[�ϐ��̏�����
	m_fAngleStart = 0.0f;
	m_fAngleSpeed = 0.0f;
	m_bActive = true;

	return S_OK;
}

//�I������
void CHeartEffect::Uninit(void)
{
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}

	//��{�N���X�̏I������
	CEffect::Uninit();
}

//�X�V����
void CHeartEffect::Update(void)
{
	//�ʒu�̌v�Z�Ɛݒ�
	float fX, fY, x, y;

	m_fAngleStart += m_fAngleSpeed;

	x = sinf(m_fAngleStart + m_fAngleSpeed);
	y = cosf(m_fAngleStart + m_fAngleSpeed);
	fX = m_center.x + 30.0f * (x * x * x);
	fY = m_center.y - 30.0f * (0.5f + y - (y * y * y * y));

	SetPos(D3DXVECTOR3(fX, fY, 0.0f));

	//��{�N���X�̍X�V����
	CObject_2D::Update();

	int life = GetLife();		//���C�t�̎擾

	life--;						//���C�t�̍X�V

	if (life <= 0)
	{//���C�t��0�ɂȂ�����A����
		m_bActive = false;
		return;
	}
	else
	{
		SetLife(life);			//���C�t�̐ݒ�
	}

	m_pHitbox->SetPos(GetPos());

	if (m_pHitbox->Hit())
	{//�v���C���[�Ɠ��������ꍇ�A����
		m_bActive = false;
	}
}

////�I������
//void CHeartEffect::Draw(void)
//{
//	//��{�N���X�̕`�揈��
//	CEffect::Draw();
//}

//���S�_�̐ݒ菈��
void CHeartEffect::SetCenterPos(const D3DXVECTOR3 center)
{
	m_center = center;
}

void CHeartEffect::SetAngleMove(const float fAngle)
{
	m_fAngleStart = fAngle;
}

bool CHeartEffect::GetActiveState(void)
{
	return m_bActive;
}


//==================================================================================================================
//
//		�ÓI�֐� 
//
//==================================================================================================================

//��������
CHeartEffect* CHeartEffect::Create(const D3DXVECTOR3 center, const float fAngleStart, const float fAngleMove, const D3DXCOLOR col, const D3DXVECTOR2 size, const int Life)
{
	CHeartEffect* pEffect = new CHeartEffect;			//�V�����G�t�F�N�g�𐶐�����

	//����������
	if (FAILED(pEffect->Init()))
	{
		return nullptr;
	}

	pEffect->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));						//���x�̐ݒ�
	pEffect->SetColor(col);													//�J�[���[�̐ݒ�
	pEffect->SetLife(Life);													//���C�t�̐ݒ�
	pEffect->SetSize(size);													//�T�C�Y�̐ݒ�
	pEffect->m_center = center;												//���S�_�̐ݒ�
	pEffect->m_fAngleStart = fAngleStart;									
	pEffect->m_fAngleSpeed = fAngleMove * 0.02f;							

	//�ʒu�̌v�Z�Ɛݒ�
	float fX, fY, x, y;

	x = sinf(pEffect->m_fAngleStart + pEffect->m_fAngleSpeed);
	y = cosf(pEffect->m_fAngleStart + pEffect->m_fAngleSpeed);
	fX = center.x + 30.0f * (x * x * x);
	fY = center.y + 30.0f * (0.5f + y - (y * y * y * y));

	pEffect->SetPos(D3DXVECTOR3(fX, fY, 0.0f));

	pEffect->SetTexture(CObject::TextureNormalEffect);						//�e�N�X�`���̐ݒ�
	pEffect->SetTextureParameter(1, 1, 1, INT_MAX);							//�e�N�X�`���p�����[�^�̐ݒ�

	pEffect->m_pHitbox = CCircleHitbox::Create(center, size.x * 0.5f, CHitbox::Type_EnemyBullet);

	return pEffect;															//�G�t�F�N�g��Ԃ�
}	