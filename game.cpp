////=============================================================================
////
//// game.cpp
//// Author : Ricci Alex
////
////=============================================================================
//
////=============================================================================
////�C���N���[�h�t�@�C��
////=============================================================================
//#include "game.h"
//#include "Scylla.h"
//#include "player.h"
//#include "inputKeyboard.h"
//#include "inputMouse.h"
//#include "bg.h"
//
////�R���X�g���N�^
//CGame::CGame()
//{
//	m_pBg = nullptr;
//	m_pPlayer = nullptr;
//	m_pEnemy = nullptr;
//}
//
////�f�X�g���N�^
//CGame::~CGame()
//{
//
//}
//
////����������
//HRESULT CGame::Init(void)
//{
//	m_pBg = nullptr;
//	m_pPlayer = nullptr;
//	m_pEnemy = nullptr;
//
//	return S_OK;
//}
//
////�I������
//void CGame::Uninit(void)
//{
//	if (m_pBg != nullptr)
//	{
//		m_pBg->Release();
//		m_pBg = nullptr;
//	}
//
//	if (m_pPlayer != nullptr)
//	{
//		m_pPlayer->Release();
//		m_pPlayer = nullptr;
//	}
//
//	if (m_pEnemy != nullptr)
//	{
//		m_pEnemy->Release();
//		m_pEnemy = nullptr;
//	}
//}
//
////�X�V����
//void CGame::Update(void)
//{
//
//}
//
//
//
//
//
////��������
//CGame* CGame::Create(void)
//{
//	CGame* pGame = new CGame;
//
//	if (FAILED(pGame->Init()))
//	{
//		return nullptr;
//	}
//
//	pGame->m_pBg = CBg::Create(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.75f), D3DXVECTOR2(0.000025f, -0.000025f));
//
//	if (pGame->m_pBg != nullptr)
//	{
//		pGame->m_pBg->SetTexture(CObject::TextureSeaBG);
//		pGame->m_pBg->SetTextureParameter(2, 1, 2, 30);
//	}
//
//	pGame->m_pPlayer = CPlayer::Create();
//
//	if (pGame->m_pPlayer != nullptr)
//	{
//		pGame->m_pPlayer->SetPos(D3DXVECTOR3(300.0f, (float)SCREEN_HEIGHT * 0.5f, 0.0f));
//	}
//
//	pGame->m_pEnemy = CScylla::Create();
//
//	return pGame;
//}