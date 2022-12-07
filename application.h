//=============================================================================
//
// application.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef APPLICATION_H
#define APPLICATION_H

//インクルードファイル
#include "object.h"

//前方宣言
class CRenderer;
class CInput;
class CInputMouse;
class CMode;
class CScore;
class CSound;
class CRanking;
class CFade;

//アプリケーションのクラス
class CApplication
{
public:

	enum Mode
	{
		Mode_Title = 0,					//タイトル
		Mode_StageSelection,			//ステージ選択
		Mode_Tutorial,					//チュートリアル
		Mode_Game,						//ゲーム
		Mode_Game_Scylla,				//ステージ1
		Mode_Game_Thanatos,				//ステージ2
		Mode_Game_Pride,				//ステージ3
		Mode_Game_Envy,					//ステージ4
		Mode_Game_Wrath,				//ステージ5
		Mode_Game_Sloth,				//ステージ6
		Mode_Game_Greed,				//ステージ7
		Mode_Game_Gluttony,				//ステージ8
		Mode_Result,					//リザルト
		Mode_Ranking,					//ランキング
		Mode_Max
	};

	CApplication();										//コンストラクタ
	~CApplication();									//デストラクタ
														
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);		//初期化処理
	void Uninit(void);									//終了処理
	void Update(void);									//更新処理
	void Draw(void);									//描画処理
	static CRenderer* GetRenderer(void);				//レンディングインスタンスの取得処理
	static CInputMouse* GetMouse(void);					//マウスインスタンスの取得処理
	static HWND GetWindow(void);						//ウインドウの取得処理
	static void SetDifficulty(const int difficulty);	//難易度の設定処理
	static const int GetDifficulty(void);				//難易度の取得処理
	static void SetRemainingLife(const int nLife);		//残った体力の設定処理
	static Mode GetMode(void);							//モードの取得処理
	static void SetMode(Mode mode);						//モードの設定処理
	static CSound* GetSound(void);						//サウンドの取得処理
	static CRanking* GetRanking(void);					//ランキングの取得処理
	static void SetFade(Mode mode);						//フェードの設定処理
	static void SetFade(const bool bFade);				//フェードの設定処理
	static const bool GetFade(void);					//フェードの取得処理

private:
	static HWND m_hWnd;									//クライエント画面
	static CRenderer* m_pRenderer;						//レンディングインスタンスへのポインタ
	static CInput* m_pInput[2];							//インプットデバイスへのポインタ
	static CInputMouse* m_pMouse;						//マウスインスタンス
	static Mode m_mode;									//モード
	static CScore* m_pScore;							//スコアへのポインタ
	static CRanking* m_pRanking;						//ランキングへのポインタ
	static CSound* m_pSound;							//サウンドへのポインタ
	static CFade* m_pFade;								//フェードへのポインタ
														
	static CMode* m_pMode;								//モードへのポインタ
	static bool m_bFade;								//フェード中であるかどうか
	static int m_nDifficulty;							//難易度
};



#endif // !APPLICATION_H
