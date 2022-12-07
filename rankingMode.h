//=============================================================================
//
// rankingMode.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef RANKING_MODE_H
#define RANKING_MODE_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "mode.h"
#include "stageSelection.h"

//=============================================================================
//前方宣言
//=============================================================================
class CLetter;
class CBg;
class CButton;

class CRankingMode : public CMode
{
public:
	CRankingMode();							//コンストラクタ
	~CRankingMode() override;				//デストラクタ

	HRESULT Init(void) override;		//初期化処理
	void Uninit(void) override;			//終了処理
	void Update(void) override;			//更新処理

	static CRankingMode* Create(const int nStage);

private:

	void UpdateMenu(void);

	static const int MaxRank = 5;
	static const int MaxDigit = 8;

	int m_nSelectedStage;
	int m_nCntDelay;

	CBg* m_pBg;
	CLetter* m_pStageName[24];
	CLetter* m_pRank[MaxRank][MaxDigit];
	CButton* m_pLateralButton[2];
	CLetter* m_pLateralIcon[2];
};

#endif