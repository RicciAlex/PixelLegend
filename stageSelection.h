//=============================================================================
//
// stageSelection.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef STAGE_SELECTION_H
#define STAGE_SELECTION_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "mode.h"

//=============================================================================
//前方宣言
//=============================================================================
class CStageSelectionMenu;
class CBg;
class CButton;
class CLetter;
class CObject_2D;

class CStageSelection : public CMode
{
public:

	//ステージの列挙型
	enum stage
	{
		stage_Scylla = 0,
		stage_Thanatos,
		stage_Pride,
		stage_Envy,
		stage_Wrath,
		stage_Sloth,
		stage_Greed,
		stage_Gluttony,
		stage_Max
	};

	//ボタンの列挙型
	enum Button
	{
		button_play = 0,			//プレイボタン
		button_leaderboard,			//ランキングボタン
		button_title,				//タイトルボタン
		button_Max
	};

	static const char m_aStage[stage_Max][24];	//ステージの名前の配列

	CStageSelection();							//コンストラクタ
	~CStageSelection() override;				//デストラクタ

	HRESULT Init(void) override;				//初期化処理
	void Uninit(void) override;					//終了処理
	void Update(void) override;					//更新処理

	static CStageSelection* Create(void);		//生成処理

private:

	void UpdateMenu(void);				//メニューの更新処理

	int m_nSelectedStage;				//現在のステージ
	int m_nCntDelay;					//ディレイ
	int m_nDifficulty;					//難易度
										
	CBg* m_pBg;							//背景へのポインタ
	CButton* m_pButton[button_Max];		//ボタンへのポインタ
	CButton* m_pLateralButton[2];		//ボタンへのポインタ
	CLetter* m_pStageName[24];			//ステージの名前へのポインタ
	CLetter* m_pLateralIcon[2];			//UIへのポインタ
	CLetter* m_pStageSelectTitle[16];	//文字へのポインタ
	CObject_2D* m_pDifficultyIcon[5];	//難易度UIへのポインタ
};

#endif