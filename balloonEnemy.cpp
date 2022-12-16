//=============================================================================
//
// enemy.cpp
// Author : Ricci Alex
//
//=============================================================================

//�C���N���[�h�t�@�C��
#include "balloonEnemy.h"
#include "circleHitbox.h"
#include "player.h"
#include "explosion.h"
#include "application.h"
#include "sound.h"

//�R���X�g���N�^
CBalloonEnemy::CBalloonEnemy()
{
	//�����o�[�ϐ����N���A����
	m_pHitbox = nullptr;
}

CBalloonEnemy::~CBalloonEnemy()
{

}

//����������
HRESULT CBalloonEnemy::Init(void)
{
	//�����o�[�ϐ�������������
	if (FAILED(CEnemy::Init()))
	{
		return -1;
	}

	m_pHitbox = nullptr;

	return S_OK;
}

//�I������
void CBalloonEnemy::Uninit(void)
{
	//�q�b�g�{�b�N�X�̔j������
	if (m_pHitbox != nullptr)
	{//null�`�F�b�N
		m_pHitbox->Release();			//���������������
		m_pHitbox = nullptr;			//null�ɂ���
	}

	//��{�N���X�̏I������
	CEnemy::Uninit();
}

//�X�V����
void CBalloonEnemy::Update(void)
{
	//���x�̌v�Z
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 playerPos = CPlayer::GetPlayer()->GetPos();
	D3DXVECTOR3 target = playerPos - pos;
	D3DXVec3Normalize(&target, &target);
	target.x *= 2.5f;
	target.y *= 2.5f;
	target += GetMove();
	D3DXVec3Normalize(&target, &target);
	target.x *= 2.5f;
	target.y *= 2.5f;

	//���x�̐ݒ�
	SetMove(target);

	//�q�b�g�{�b�N�X�X�V
	if (m_pHitbox)
	{//null�`�F�b�N
		m_pHitbox->SetPos(pos);			//�ʒu�̐ݒ�
	}	

	int nLife = GetLife();				//�̗͂̎擾
	nLife--;							//�̗͂̍X�V

	if (nLife <= 0)
	{//�̗͂�0�ȉ��ɂȂ�����
		CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_EXPLOSION);		//�����̃T�E���h�G�t�F�N�g
		CExplosion* pExplosion = CExplosion::Create();							//�����𐶐�����
		pExplosion->SetPos(pos);												//�����̈ʒu�̐ݒ�
		pExplosion->SetSize(D3DXVECTOR2(30.0f, 30.0f));							//�����̃T�C�Y�̐ݒ�

		Release();				//�C���X�^���X��j������
		return;
	}
	else
	{
		SetLife(nLife);			//�̗͂̐ݒ�
	}

	//��{�N���X�̍X�V����
	CObject_2D::Update();
}

//�`�揈��
void CBalloonEnemy::Draw(void)
{
	CEnemy::Draw();
}


//��������
CBalloonEnemy* CBalloonEnemy::Create(D3DXVECTOR3 pos)
{
	CBalloonEnemy* pEnemy = new CBalloonEnemy;				//�C���X�^���X�𐶐�����

	if (FAILED(pEnemy->Init()))
	{//����������
		return nullptr;
	}

	pEnemy->SetPos(pos);								//�ʒu�̐ݒ�
	pEnemy->SetStartingRot(D3DX_PI * 0.5f);				//�����̏����l�̐ݒ�
	pEnemy->SetSize(D3DXVECTOR2(25.0f, 25.0f));			//�T�C�Y�̐ݒ�
	pEnemy->SetTexture(CObject::TextureBalloonEnemy);	//�e�N�X�`���̐ݒ�
	pEnemy->SetTextureParameter(1, 1, 1, INT_MAX);		//�e�N�X�`���p�����[�^�̐ݒ�
	pEnemy->SetLife(random(120, 360));					//�̗͂̐ݒ�

	//���x�̌v�Z
	D3DXVECTOR3 playerPos = CPlayer::GetPlayer()->GetPos();
	D3DXVECTOR3 target = playerPos - pos;
	D3DXVec3Normalize(&target, &target);
	target.x *= 2.5f;
	target.y *= 2.5f;

	pEnemy->SetMove(target);				//���x�̐ݒ�
		

	//�q�b�g�{�b�N�X�𐶐�����
	pEnemy->m_pHitbox = CCircleHitbox::Create(pos, 25.0f, CHitbox::Type_Enemy);

	//�F�̐ݒ菈��
	int nColor = random(0, 5);
	D3DXCOLOR col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	switch (nColor)
	{
	case 0:
		col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		break;
	case 1:
		col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
		break;
	case 2:
		col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
		break;
	case 3:
		col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
		break;
	case 4:
		col = D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f);
		break;
	case 5:
		col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
		break;
	default:
		break;
	}

	pEnemy->SetColor(col);

	return pEnemy;					//���������C���X�^���X��Ԃ�
}