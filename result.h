//=============================================================================
//
// result.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef RESULT_H
#define RESULT_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "mode.h"

//=============================================================================
//前方宣言
//=============================================================================
class CLetter;

class CResult : public CMode
{
public:
	CResult();							//コンストラク
	~CResult();							//デストラクタ
										
	HRESULT Init(void) override;		//初期化処理
	void Uninit(void) override;			//終了処理
	void Update(void) override;			//更新処理

	static CResult* Create(const int nScore);		//生成処理

private:

	static const int MaxDigit = 8;		//スコアの桁数

	int m_nDelay;						//ディレイ
	float m_fAnim;						//アニメーション用の変数
										
	CLetter* m_pScore[MaxDigit];		//スコアの桁へのポインタ
	CLetter* m_pUI[12];					//UIへのポインタ
};

#endif