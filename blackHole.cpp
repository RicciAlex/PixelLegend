//=============================================================================
//
// blackHole.cpp
// Author : Ricci Alex
//
//=============================================================================

//�C���N���[�h�t�@�C��
#include "blackHole.h"
#include "player.h"

CBlackHole::CBlackHole()
{

}

CBlackHole::~CBlackHole()
{
	 
}

//����������
HRESULT CBlackHole::Init(void)
{
	//��{�N���X�̏���������
	if (FAILED(CObject_2D::Init()))
	{
		return -1;
	}

	return S_OK;
}

//�I������
void CBlackHole::Uninit(void)
{
	CObject_2D::Uninit();
}

//�X�V����
void CBlackHole::Update(void)
{
	CObject_2D::Update();								//��{�N���X�̍X�V����

	CPlayer* pPlayer = CPlayer::GetPlayer();			//�v���C���[���̎擾����
	D3DXVECTOR3 pos, PosPlayer, Dir;
	pos = GetPos();										//�e�̈ʒu�̎擾
	PosPlayer = pPlayer->GetPos();						//�v���C���[�̈ʒu�̎擾
	Dir = pos - PosPlayer;								//�������v�Z����
	D3DXVec3Normalize(&Dir, &Dir);						//�����𐳋K������
	Dir.x *= 3.0f;
	Dir.y *= 3.0f;
	PosPlayer += Dir;									//�v���C���[�̈ʒu�̍X�V
	pPlayer->SetPos(PosPlayer);							//�v���C���[�̈ʒu�̐ݒ�

	int nLife = GetLife();
	nLife--;											//�����̍X�V

	if (nLife <= 0)
	{//������0�ɂȂ�����

		DestroyBullet();

		return;
	}
	
	SetLife(nLife);
}

//��������
CBlackHole* CBlackHole::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const D3DXVECTOR3 acc, const D3DXVECTOR2 size, const int nLife)
{
	CBlackHole* pBullet = new CBlackHole;				//�e�𐶐�����

	if (pBullet != nullptr)
	{
		//����������
		if (FAILED(pBullet->Init()))
		{
			delete pBullet;			//���������������
			return nullptr;			//null��Ԃ�
		}

		pBullet->SetBulletType(CBullet::BULLET_BLACKHOLE);
		pBullet->SetPos(pos);									//�ʒu�̐ݒ�
		pBullet->SetMove(move);									//�ړ��ʂ̐ݒ�
		pBullet->SetAcceleration(acc);							//�����̐ݒ�

		pBullet->SetTexture(CObject::TextureBlackHole);		//�e�N�X�`���̐ݒ�
		pBullet->SetTextureParameter(1, 1, 1, INT_MAX);		//�e�N�X�`���p�����[�^�̐ݒ菈��
		pBullet->SetSize(size);								//�T�C�Y�̐ݒ�
		pBullet->SetLife(nLife);							//�����̐ݒ�

	}

	return pBullet;						//�e��Ԃ�
}