//=============================================================================
//
// balloon.cpp
// Author : Ricci Alex
//
//=============================================================================

//�C���N���[�h�t�@�C��
#include "balloon.h"
#include "circleHitbox.h"
#include "application.h"
#include "sound.h"

//�R���X�g���N�^
CBalloonBullet::CBalloonBullet()
{
	m_pHitbox = nullptr;
}

//�f�X�g���N�^
CBalloonBullet::~CBalloonBullet()
{

}

//����������
HRESULT CBalloonBullet::Init(void)
{
	if (FAILED(CBullet::Init()))
	{
		return -1;
	}

	m_pHitbox = nullptr;

	return S_OK;
}

//�I������
void CBalloonBullet::Uninit(void)
{
	if (m_pHitbox != nullptr)
	{
		m_pHitbox->Release();
		m_pHitbox = nullptr;
	}

	CBullet::Uninit();
}

//�X�V����
void CBalloonBullet::Update(void)
{
	m_pHitbox->SetPos(GetPos());

	if (m_pHitbox->Hit())
	{
		CApplication::GetSound()->Play(CSound::SOUND_LABEL_SE_EXPLOSION);		//�����̃T�E���h�G�t�F�N�g
		Release();
		return;
	}

	CBullet::Update();
}



//��������
CBalloonBullet* CBalloonBullet::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, D3DXCOLOR col)
{
	CBalloonBullet* pBullet = new CBalloonBullet;

	if (FAILED(pBullet->Init()))
	{
		return nullptr;
	}

	pBullet->SetPos(pos);
	pBullet->SetMove(move);
	pBullet->SetSize(D3DXVECTOR2(25.0f, 45.0f));
	pBullet->SetLife(random(120, 300));
	pBullet->SetColor(col);
	pBullet->SetTexture(CObject::TextureBalloon);
	pBullet->SetTextureParameter(1, 1, 1, INT_MAX);
	pBullet->SetStartingRot(D3DX_PI * 0.5f);

	pBullet->m_pHitbox = CCircleHitbox::Create(pos, 25.0f, CHitbox::Type_EnemyBullet);

	return pBullet;
}