//=============================================================================
//
// gluttony.cpp
// Author : Ricci Alex
//
//=============================================================================

//インクルードファイル
#include "gluttony.h"
#include "squareHitbox.h"
#include "maw.h"
#include "backMaw.h"
#include "heart.h"
#include "application.h"

//コンストラクタ
CGluttony::CGluttony()
{
	//メンバー変数をクリアする
	m_pHitbox = nullptr;

	for (int nCnt = 0; nCnt < MaxMaw; nCnt++)
	{
		m_pMaw[nCnt] = nullptr;
	}

	m_nCntState = 0;
	m_nTargetFrame = 0;
	m_nPhase = 0;

	m_pBackMaw = nullptr;
	m_pHeart = nullptr;
}

//デストラクタ
CGluttony::~CGluttony()
{

}

//初期化処理
HRESULT CGluttony::Init(void)
{
	//メンバー変数を初期化する
	m_pHitbox = nullptr;

	for (int nCnt = 0; nCnt < MaxMaw; nCnt++)
	{
		m_pMaw[nCnt] = nullptr;
	}

	m_nCntState = 0;
	m_nTargetFrame = 0;
	m_nPhase = 0;

	m_pBackMaw = nullptr;
	m_pHeart = nullptr;

	return S_OK;
}

//終了処理
void CGluttony::Uninit(void)
{
	//ヒットボックスの破棄処理
	if (m_pHitbox != nullptr)
	{//nullチェック
		m_pHitbox->Release();			//メモリを解放する
		m_pHitbox = nullptr;			//ポインタをnullにする
	}

	//周りの敵の破棄処理
	for (int nCnt = 0; nCnt < MaxMaw; nCnt++)
	{
		if (m_pMaw[nCnt] != nullptr)
		{//nullチェック
			m_pMaw[nCnt]->Release();	//メモリを解放する
			m_pMaw[nCnt] = nullptr;		//ポインタをnullにする
		}
	}

	//背景の敵の破棄処理
	if (m_pBackMaw != nullptr)
	{//nullチェック
		m_pBackMaw->Release();			//メモリを解放する
		m_pBackMaw = nullptr;			//ポインタをnullにする
	}

	//心の破棄処理
	if (m_pHeart != nullptr)
	{//nullチェック
		m_pHeart->Release();			//メモリを解放する
		m_pHeart = nullptr;				//ポインタをnullにする
	}
}

//更新処理
void CGluttony::Update(void)
{
	m_nCntState++;				//攻撃カウンターをインクリメントする

	//心の更新処理
	if (m_pHeart != nullptr)
	{//nullチェック

		if (m_pHeart->GetLife() <= 6250 && m_nPhase == 0)
		{
			m_nPhase++;
		}
		
		if (m_pHeart->GetEnd())
		{//終わったら、リザルト画面に切り替える
			CApplication::SetFade(CApplication::Mode_Result);
		}
	}

	if (m_nCntState % 1000 == 999)
	{//1000フレームごと周りの敵、又は背景の敵の状態を設定する

		if (m_nPhase == 0)
		{//体力が6250以上だったら
			int nIdx = CObject::random(0, 2);

			if (m_pMaw[nIdx] != nullptr)
			{//ランダムで周りの敵を1匹選択して、攻撃させる
				m_pMaw[nIdx]->Open();
			}
		}
		else
		{//体力が6250未満だったら
			if (m_pBackMaw != nullptr)
			{//背景の敵を攻撃させる
				m_pBackMaw->SetState(CBackMaw::state_awake);
			}
		}

		if (m_nCntState >= m_nTargetFrame)
		{//目的のフレームを超えたら、

			m_nCntState = 0;										//状態カウンターを0に戻す
			m_nTargetFrame = CObject::random(3, 5) * 1000;			//次の目的のフレームをランダムで設定する

			//心がnullではなかったら、起きるように設定する
			if (m_pHeart != nullptr)
			{
				m_pHeart->SetActive();
			}
		}
	}
}

//終わったかどうかの取得処理
const bool CGluttony::GetEnd(void)
{
	if (m_pHeart != nullptr)
	{//心がnullではなかったら

		return m_pHeart->GetEnd();
	}

	return false;
}


//=============================================================================
//
//									静的関数
//
//=============================================================================


//生成処理
CGluttony* CGluttony::Create(void)
{
	CGluttony* pEnemy = new CGluttony;				//インスタンスを生成する

	if (pEnemy == nullptr)
	{//初期化処理
		return nullptr;
	}

	pEnemy->m_pBackMaw = CBackMaw::Create();				//背景の敵の生成
	pEnemy->m_pMaw[0] = CMaw::Create(CMaw::left);			//左の敵の生成
	pEnemy->m_pMaw[1] = CMaw::Create(CMaw::down);			//下の敵の生成
	pEnemy->m_pMaw[2] = CMaw::Create(CMaw::right);			//右の敵の生成
	pEnemy->m_pHeart = CHeart::Create();					//心の生成
	pEnemy->m_nCntState = 700;								//状態カウンターを設定する
	pEnemy->m_nTargetFrame = CObject::random(1, 3) * 1000;	//目的のフレームを設定する

	return pEnemy;					//生成したインスタンスを返す
}