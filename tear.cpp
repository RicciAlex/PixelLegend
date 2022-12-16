//=============================================================================
//
// tear.cpp
// Author : Ricci Alex
//
//=============================================================================

//�C���N���[�h�t�@�C��
#include "tear.h"
#include "circleHitbox.h"

//�R���X�g���N�^
CTearBullet::CTearBullet()
{
	//�����o�[�ϐ����N���A����
	m_pHitbox = nullptr;
}

//�f�X�g���N�^
CTearBullet::~CTearBullet()
{

}

//����������
HRESULT CTearBullet::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CBullet::Init()))
	{
		return -1;
	}

	return S_OK;
}

//�I������
void CTearBullet::Uninit(void)
{
	//�q�b�g�{�b�N�X�̔j��
	if (m_pHitbox != nullptr)
	{//null�`�F�b�N
		m_pHitbox->Release();			//���������������
		m_pHitbox = nullptr;			//�|�C���^��null�ɂ���
	}

	//��{�N���X�̏I������
	CBullet::Uninit();
}

//�X�V����
void CTearBullet::Update(void)
{
	D3DXVECTOR3 move = GetMove();								//���x�̎擾
	D3DXVECTOR3 Vec, unit;
	unit = D3DXVECTOR3(0.0f, -1.0f, 0.0f);						//�P�ʃ��F�N�g����錾����
	D3DXVec3Normalize(&Vec, &move);								//���x�𐳋K������
	float fAngle = (float)acos(D3DXVec3Dot(&Vec, &unit));		//�P�ʃ��F�N�g���Ƒ��x�̃��F�N�g���̊Ԃ̊p�x���v�Z����

	//�p�x�̐��K��
	if (Vec.y < unit.y)
	{
		fAngle *= -1.0f;
	}

	//�e�̊p�x�̍X�V����
	if (move.x <= 0.0f)
	{
		SetStartingRot(fAngle + (-D3DX_PI * 0.5f));
	}
	else
	{
		SetStartingRot(-fAngle + (-D3DX_PI * 0.5f));
	}	

	//���x�̍X�V
	move.y += 0.08f;			
	SetMove(move);

	//��{�N���X�̍X�V����
	CObject_2D::Update();

	m_pHitbox->SetPos(GetPos());

	if (m_pHitbox->Hit())
	{//�v���C���[�Ɠ��������ꍇ�A�e������
		Release();
		return;
	}

	D3DXVECTOR3 pos = GetPos();				//�ʒu�̎擾
	D3DXVECTOR2 size = GetSize();			//�T�C�Y�̎擾

	if (pos.x + size.x <= 0.0f || pos.x + size.x >= (float)SCREEN_WIDTH || pos.y - size.y >= (float)SCREEN_HEIGHT)
	{//��ʂ��o����A����
		Release();
		return;
	}
}

//=============================================================================
//�ÓI�֐�
//=============================================================================

//��������
CTearBullet* CTearBullet::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move)
{
	CTearBullet* pBullet = new CTearBullet;				//�V�����e�𐶐�����

	//����������
	if (FAILED(pBullet->Init()))
	{
		return nullptr;
	}
		
	pBullet->SetPos(pos);								//�ʒu�̐ݒ�
	pBullet->SetMove(move);								//���x�̐ݒ�

	pBullet->SetTexture(CObject::TextureTeardrop);		//�e�N�X�`���̐ݒ�
	pBullet->SetTextureParameter(1, 1, 1, INT_MAX);		//�e�N�X�`���p�����[�^�̐ݒ菈��
	pBullet->SetSize(D3DXVECTOR2(15.0f, 15.0f));		//�T�C�Y�̐ݒ�

	//�e�̉�]�p�x�̌v�Z�Ɛݒ�
	D3DXVECTOR3 Vec, unit;
	unit = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	D3DXVec3Normalize(&Vec, &move);
	float fAngle = (float)acos(D3DXVec3Dot(&Vec, &unit));

	if (Vec.y < unit.y)
	{
		fAngle *= -1.0f;
	}

	pBullet->SetStartingRot(fAngle + (D3DX_PI * 0.25f));		//�����̏����l�̐ݒ�

	pBullet->m_pHitbox = CCircleHitbox::Create(pos, 13.0f, CHitbox::Type_EnemyBullet);		//�q�b�g�{�b�N�X�̐���

	return pBullet;									//�e��Ԃ�
} 
