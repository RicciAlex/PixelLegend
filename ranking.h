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
	~CRanking();						//デストラクタ

	HRESULT Init(void);					//初期化処理
	void Uninit(void);					//終了処理

	void SetStage(CStageSelection::stage stage);	//現在のステージの設定処理
	int GetStage(void);								//現在のステージの取得処理
	int SetRanking(CStageSelection::stage stage, const int nScore);	//ランキングの設定処理
	int* GetRanking(CStageSelection::stage stage);					//ランキングの取得処理
	void SaveRanking(void);				//ランキングの書き出し処理
	void LoadRanking(void);				//ランキングの読み込む処理


	static CRanking* Create(void);		//生成処理

private:

	static const int MaxRank = 5;		//スコアの数

	int m_aRanking[CStageSelection::stage_Max][MaxRank];		//スコアの配列
	int m_nSelectedStage;										//現在のステージ
	int m_nCntDelay;											//ディレイ
};



#endif