//=============================================================================
//
// title.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef TITLE_H
#define TITLE_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "mode.h"

//=============================================================================
//前方宣言
//=============================================================================
class CBg;
class CTitleMenu;
class CButton;
class CSkullCursor;
class CLetter;

class CTitle : public CMode
{
public:

	//タイトルアニメーションの色
	enum TargetCol
	{
		TargetCol_Red = 0,		//赤
		TargetCol_Green,		//緑
		TargetCol_Blue,			//青
		TargetCol_Yellow,		//黄
		TargetCol_Magenta,		//マゼンタ
		TargetCol_Cyan,			//シアン
		TargetCol_Max
	};

	//ボタンの列挙型
	enum Button
	{
		button_play = 0,		//プレイボタン
		button_tutorial,		//チュートリアルボタン
		button_leaderboard,		//ランキングボタン
		button_max
	};

	CTitle();								//コンストラクタ
	~CTitle() override;						//デストラクタ

	HRESULT Init(void) override;			//初期化処理
	void Uninit(void) override;				//終了処理
	void Update(void) override;				//更新処理

	static CTitle* Create(void);			//生成処理

private:

	void UpdateTitleColor(void);			//タイトルの色の更新処理
		
	static D3DXCOLOR targetColors[TargetCol_Max];		//タイトルアニメーションの色

	TargetCol m_TargetCol;				//次の目的の色の番号
	D3DXCOLOR m_changeCol;				//アニメーションの速度(毎フレーム加算されているカラー)
	int m_nChangeFrame;					//アニメーションフレーム

	CBg* m_pBg;							//背景へのポインタ
	CButton* m_pButton[button_max];		//ボタンへのポインタ
	CSkullCursor* m_pCursor[2];			//カーソルへのポインタ
	CLetter* m_pTitle[16];				//タイトルの文字へのポインタ
};

#endif