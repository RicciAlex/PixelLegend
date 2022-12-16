//=============================================================================
//
// wrath.cpp
// Author : Ricci Alex
//
//=============================================================================

//�C���N���[�h�t�@�C��
#include "wrath.h"
#include "enemyWrathBody.h"
#include "handFlamethrower.h"
#include "handGun.h"
#include "handCharger.h"
#include "player.h"
#include "enemyLife.h"

//�R���X�g���N�^
CWrath::CWrath()
{
	//�����o�[�ϐ����N���A����
	m_bEnd = false;
	m_bDeath = false;
	m_pBody = nullptr;
	m_pLife = nullptr;
}

//�f�X�g���N�^
CWrath::~CWrath()
{

}

//����������
HRESULT CWrath::Init(void)
{
	//�����o�[�ϐ�������������
	if (FAILED(CEnemy::Init()))
	{//��{�N���X�̏���������
		return -1;
	}

	m_bEnd = false;
	m_bDeath = false;
	m_pBody = nullptr;
	m_pLife = nullptr;

	return S_OK;
}

//�I������
void CWrath::Uninit(void)
{
	//�̃C���X�^���X�̔j������
	if (m_pBody != nullptr)
	{//null�`�F�b�N
		m_pBody->Release();				//���������������
		m_pBody = nullptr;				//null�ɂ���
	}

	//�̗�UI�̔j������
	if (m_pLife != nullptr)
	{//null�`�F�b�N
		m_pLife->Release();				//���������������
		m_pLife = nullptr;				//null�ɂ���
	}

	//��{�N���X�̏I������
	CEnemy::Uninit();
}

//�X�V����
void CWrath::Update(void)
{
	int nLife = GetLife();										//�̗͂̎擾
	D3DXVECTOR3 playerPos = CPlayer::GetPlayer()->GetPos();		//�v���C���[�̈ʒu�̎擾
	
	if (nLife <= 0)
	{//�̗͂�0�ȉ��ɂȂ�����A���S������Ԃɂ���
		m_bDeath = true;
	}

	//�̃C���X�^���X�̍X�V����
	if (m_pBody != nullptr)
	{//null�`�F�b�N
		if (m_pBody->GetDeath())
		{//���񂾂��ǂ������m�F����
			m_pBody->Release();					//�̃C���X�^���X��j������
			m_pBody = nullptr;					//�|�C���^��null�ɂ���
		}
	}
	else
	{//�̃C���X�^���X�����񂾂�

		m_nShootDelay++;			//�U���J�E���^�[���X�V����

		if (m_nShootDelay >= 500)
		{//��莞�Ԃ��o������
			if (nLife >= 12500)
			{//�̗͂����܂����l�ȏゾ������

				int nSelect = random(0, 200);				//�U���̎�ނ������_���Ō��߂�(25%���Ƃ̊m��)

				if (nSelect < 50)
				{
					//������΂̎���X�|�[������
					CHandFlamethrower* pEnemy = CHandFlamethrower::Create(D3DXVECTOR3(-100.0f, playerPos.y, 0.0f), D3DXVECTOR3(2.0f, 0.0f, 0.0f));
					pEnemy->SetParent(this);
				}
				else if (nSelect >= 50 && nSelect < 100)
				{
					//�E����΂̎���X�|�[������
					CHandFlamethrower* pEnemy = CHandFlamethrower::Create(D3DXVECTOR3((float)SCREEN_WIDTH + 100.0f, playerPos.y, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f));
					pEnemy->SetParent(this);
				}
				else if (nSelect >= 100 && nSelect < 150)
				{
					//�����瑼�̎���X�|�[������
					CHandGun* pEnemy = CHandGun::Create(D3DXVECTOR3(-100.0f, playerPos.y, 0.0f), D3DXVECTOR3(2.0f, 0.0f, 0.0f));
					pEnemy->SetParent(this);
				}
				else
				{
					//�E���瑼�̎���X�|�[������
					CHandGun* pEnemy = CHandGun::Create(D3DXVECTOR3((float)SCREEN_WIDTH + 100.0f, playerPos.y, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f));
					pEnemy->SetParent(this);
				}
			}
			else if (nLife < 12500 && nLife >= 10000)
			{//�̗͂�12500�����A10000�ȏゾ������A�����_����2�̃p�^�[���̒������_���őI��
				int nSelect = random(0, 100);

				//�E��������������̎�^�̓G������āA�U������
				if (nSelect < 50)
				{
					CHandFlamethrower* pEnemy = CHandFlamethrower::Create(D3DXVECTOR3(-100.0f, playerPos.y, 0.0f), D3DXVECTOR3(2.0f, 0.0f, 0.0f));
					pEnemy->SetParent(this);
					CHandGun* pEnemy2 = CHandGun::Create(D3DXVECTOR3((float)SCREEN_WIDTH + 100.0f, playerPos.y, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f));
					pEnemy2->SetParent(this);
				}
				else
				{
					CHandFlamethrower* pEnemy = CHandFlamethrower::Create(D3DXVECTOR3((float)SCREEN_WIDTH + 100.0f, playerPos.y, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f));
					pEnemy->SetParent(this);
					CHandGun* pEnemy2 = CHandGun::Create(D3DXVECTOR3(-100.0f, playerPos.y, 0.0f), D3DXVECTOR3(2.0f, 0.0f, 0.0f));
					pEnemy2->SetParent(this);
				}
			}
			else
			{//�̗͂�10000������������A��^�̓G3��ތ���āA�U������

				int nSelect = random(0, 100);

				if (nSelect < 50)
				{
					CHandFlamethrower* pEnemy = CHandFlamethrower::Create(D3DXVECTOR3(-100.0f, playerPos.y, 0.0f), D3DXVECTOR3(2.0f, 0.0f, 0.0f));
					pEnemy->SetParent(this);
					CHandGun* pEnemy2 = CHandGun::Create(D3DXVECTOR3((float)SCREEN_WIDTH + 100.0f, playerPos.y, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f));
					pEnemy2->SetParent(this);
				}
				else
				{
					CHandFlamethrower* pEnemy = CHandFlamethrower::Create(D3DXVECTOR3((float)SCREEN_WIDTH + 100.0f, playerPos.y, 0.0f), D3DXVECTOR3(-2.0f, 0.0f, 0.0f));
					pEnemy->SetParent(this);
					CHandGun* pEnemy2 = CHandGun::Create(D3DXVECTOR3(-100.0f, playerPos.y, 0.0f), D3DXVECTOR3(2.0f, 0.0f, 0.0f));
					pEnemy2->SetParent(this);
				}

				CHandCharger* pEnemy = CHandCharger::Create(D3DXVECTOR3(playerPos.x, -100.0f, 0.0f));
				pEnemy->SetParent(this);
			}

			m_nShootDelay = 0;				//�U���J�E���^�[��0�ɖ߂�
		}
	}

	if (m_bDeath)
	{//���S�����ꍇ
		m_nCntMove++;			//�ړ��J�E���^�[���X�V����

		if (m_nCntMove >= 60)
		{//1�b���o������
			m_bEnd = true;		//�I�������Ԃɂ���
		}
	}
}

//�`�揈��
void CWrath::Draw(void)
{
	//��{�N���X�̕`�揈��
	CObject_2D::Draw();
}


//�I��������ǂ����̎擾����
const bool CWrath::GetEnd(void)
{
	return m_bEnd;
}

//���S�������ǂ����̎擾����
const bool CWrath::GetDeath(void)
{
	return m_bDeath;
}

//�_���[�W���󂯂鏈��
void CWrath::Damage(const int nDamage)
{
	int nLife = GetLife();		//�̗͂̎擾����

	if (nLife > 0)
	{//�̗͂�0�ȏゾ������

		SetLife(nLife - nDamage);			//�̗͂̐ݒ菈��

		//�̗͂�UI�̍X�V
		if (m_pLife != nullptr)
		{//null�`�F�b�N
			m_pLife->SubtractLife(nDamage);	//UI���X�V����
		}
	}
}






//��������
CWrath* CWrath::Create(void)
{
	CWrath* pEnemy = new CWrath;

	if (FAILED(pEnemy->Init()))
	{
		return nullptr;
	}

	pEnemy->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pEnemy->SetSize(D3DXVECTOR2(0.0f, 0.0f));
	pEnemy->SetLife(30000);
	pEnemy->SetTexture(CObject::TextureNull);
	pEnemy->SetTextureParameter(1, 1, 1, INT_MAX);

	pEnemy->m_pBody = CWrathBody::Create(D3DXVECTOR3(1400.0f, 350.0f, 0.0f));
	
	if (pEnemy->m_pBody != nullptr)
	{
		pEnemy->m_pBody->SetParent(pEnemy);
	}

	pEnemy->m_nShootDelay = 440;

	pEnemy->m_pLife = CEnemyLife::Create(D3DXVECTOR3(900.0f, 40.0f, 0.0f), D3DXCOLOR(0.0f, 1.0f, 0.5f, 0.4f), 30000, "wrath");

	return pEnemy;
}

