//=============================================================================
//
// clockNeedle.cpp
// Author : Ricci Alex
//
//=============================================================================

//�C���N���[�h�t�@�C��
#include "clockNeedle.h"
#include "player.h"

CClockNeedle::CClockNeedle()
{

}

CClockNeedle::~CClockNeedle()
{

} 

//����������
HRESULT CClockNeedle::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CObject_2D::Init()))
	{
		return -1;
	}

	SetBulletType(CBullet::BULLET_CLOCK_NEEDLE);

	SetTexture(CObject::TextureClockNeedle);	//�e�N�X�`���̐ݒ�
	SetTextureParameter(1, 1, 1, INT_MAX);		//�e�N�X�`���p�����[�^�̐ݒ菈��

	return S_OK;
}

//�I������
void CClockNeedle::Uninit(void)
{
	//��{�N���X�̏I������
	CObject_2D::Uninit();
}

//�X�V����
void CClockNeedle::Update(void)
{
	int nLife = GetLife();

	nLife--;											//�����̍X�V

	if (nLife <= 0)
	{//������0�ɂȂ�����

		DestroyBullet();

		return;
	}

	SetLife(nLife);										//���C�t�̐ݒ�

	CObject_2D::Update();								//��{�N���X�̍X�V����

	D3DXVECTOR3 move = GetMove();
	D3DXVECTOR3 pos = GetPos() + move;					//�ʒu�̍X�V

	SetPos(pos);										//�ʒu�̐ݒ�

	move += GetAcceleration();							//�ړ��ʂ̍X�V
	SetMove(move);		

	if (pos.x > SCREEN_WIDTH || pos.x < 0.0f || pos.y > SCREEN_HEIGHT || pos.y < 0.0f)
	{//��ʂ��o����

		Release();										//�e������
		return;
	}
}

//�����蔻��
bool CClockNeedle::Hit(void)
{
	D3DXVECTOR3 pos = GetPos();								//�e�̈ʒu�̎擾

	CPlayer* pPlayer = CPlayer::GetPlayer();					//�v���C���[���̎擾
	D3DXVECTOR3 PosPlayer = pPlayer->GetPos();					//�v���C���[�̈ʒu�̎擾
	D3DXVECTOR2 size = GetSize();								//�e�̃T�C�Y�̎擾
	D3DXVECTOR2 SizePlayer = pPlayer->GetSize();				//�v���C���[�̃T�C�Y�̎擾

																//�����蔻��
	if (CObject::HitBox(&pos, &PosPlayer, size, SizePlayer))
	{
		return true;
	}

	return false;
}

//==================================================================================================================
//
//		�ÓI�֐�
//
//==================================================================================================================

//��������
CClockNeedle* CClockNeedle::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const D3DXVECTOR3 acc, const D3DXVECTOR2 Size)
{
	CClockNeedle* pBullet = new CClockNeedle;				//�e�𐶐�����

	if (pBullet != nullptr)
	{
		//����������
		if (FAILED(pBullet->Init()))
		{
			return nullptr;			//null��Ԃ�
		}

		
		pBullet->SetPos(pos);									//�ʒu�̐ݒ�
		pBullet->SetMove(move);									//�ړ��ʂ̐ݒ�
		pBullet->SetAcceleration(acc);							//�����̐ݒ�

		pBullet->SetSize(Size);								//�T�C�Y�̐ݒ�
		pBullet->SetLife(INT_MAX);							//�����̐ݒ�
		pBullet->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));	//���x�̐ݒ�

	}

	return pBullet;						//�e��Ԃ�
}