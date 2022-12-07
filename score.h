//=============================================================================
//
// score.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef SCORE_H
#define SCORE_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "stageSelection.h"

class CScore
{
public:
	CScore();													//コンストラクタ
	~CScore();													//デストラクタ
																
	HRESULT Init(void);											//初期化処理
	void Uninit(void);											//終了処理
																
	void SetBaseScore(const int nBase);							//基本点数の設定処理
	void SetDifficulty(const int nDifficulty);					//難易度の設定処理
	void SetLife(const int nLife);								//プレイヤーの残したライフ
	void Clear(void);											//クリア処理

	void SetLevel(CStageSelection::stage stage);				//ステージの設定処理

	CStageSelection::stage GetStage(void);						//ステージの取得処理
	const int GetFinalScore(void);								//スコアの取得処理


	static CScore* Create(void);								//生成処理

private:

	void CalcScore(void);										//スコアの計算処理

	int m_nScore;												//スコア
																
	CStageSelection::stage m_stage;								//現在のステージ
	int m_nBaseScore;											//基本のスコア
	int m_nDifficulty;											//難易度
	int m_nRemainingLife;										//残った体力
	int m_nStartingTime;										//初めの時間
	int m_nTime;												//現在時間
};




#endif