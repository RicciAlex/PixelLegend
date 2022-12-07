//=============================================================================
//
// ranking.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef RANKING_H
#define RANKING_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "stageSelection.h"

class CRanking
{
public:
	CRanking();							//コンストラクタ
	~CRanking();				//デストラクタ

	HRESULT Init(void);					//初期化処理
	void Uninit(void);					//終了処理

	void SetStage(CStageSelection::stage stage);
	int GetStage(void);
	int SetRanking(CStageSelection::stage stage, const int nScore);	//ランキングの設定処理
	int* GetRanking(CStageSelection::stage stage);					//ランキングの取得処理
	void SaveRanking(void);				//ランキングの書き出し処理
	void LoadRanking(void);				//ランキングの読み込む処理


	static CRanking* Create(void);

private:

	//void UpdateMenu(void);

	static const int MaxRank = 5;
	//static const int MaxDigit = 8;


	int m_aRanking[CStageSelection::stage_Max][MaxRank];
	int m_nSelectedStage;
	int m_nCntDelay;

	/*CBg* m_pBg;
	CLetter* m_pStageName[24];
	CLetter* m_pRank[MaxRank][MaxDigit];
	CButton* m_pLateralButton[2];
	CLetter* m_pLateralIcon[2];*/
};



#endif