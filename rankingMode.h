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
	CRankingMode();						//コンストラクタ
	~CRankingMode() override;			//デストラクタ

	HRESULT Init(void) override;		//初期化処理
	void Uninit(void) override;			//終了処理
	void Update(void) override;			//更新処理

	static CRankingMode* Create(const int nStage);			//生成処理

private:

	void UpdateMenu(void);				//メニューの更新処理

	static const int MaxRank = 5;		//スコアの数
	static const int MaxDigit = 8;		//スコアの桁数

	int m_nSelectedStage;				//現在のステージ
	int m_nCntDelay;					//ディレイ

	CBg* m_pBg;							//背景へのポインタ
	CLetter* m_pStageName[24];			//ステージの名前へのポインタ
	CLetter* m_pRank[MaxRank][MaxDigit];//スコアへのポインタ
	CButton* m_pLateralButton[2];		//ボタンへのポインタ
	CLetter* m_pLateralIcon[2];			//UIへのポインタ
};

#endif