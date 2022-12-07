//=============================================================================
//
// button.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef BUTTON_H
#define BUTTON_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "object.h"

//=============================================================================
//前方宣言
//=============================================================================
class CLetter;
class CObject_2D;

class CButton
{
public:
	CButton();									//コンストラクタ
	~CButton();									//デストラクタ

	HRESULT Init(void);							//初期化処理
	void Uninit(void);							//終了処理
	void Update(void);							//更新処理
	void Draw(void);							//描画処理

	void SetPos(const D3DXVECTOR3 pos);			//位置の設定処理
	const D3DXVECTOR2 GetSize(void);			//サイズの取得処理
	const D3DXVECTOR3 GetPos(void);				//位置の設定処理
	const bool GetTriggerState(void);

	static CButton* Create(const D3DXVECTOR3 pos, const 
		D3DXVECTOR2 size, const D3DXCOLOR BgCol, const char* Word);									//生成処理
	static CButton* Create(const D3DXVECTOR3 pos, const
		D3DXVECTOR2 size, const D3DXCOLOR BgCol, const D3DXCOLOR LettersCol, const char* Word);		//生成処理

private:

	static const int MaxWordLenght = 24;			//文字の最大数

	D3DXVECTOR3 m_pos;								//位置
	D3DXVECTOR2 m_size;								//サイズ
	D3DXVECTOR2 m_originalSize;						//初期化のサイズ
													
	float m_fCntAnim;								//アニメションカウンター
	bool m_bTriggered;								//マウスカーソルと重なっているかどうか
													
	CObject_2D* m_pBack;							//背景へのポインタ
	CLetter* m_pLetter[MaxWordLenght];				//ボタンの文字へのポインタ
};


#endif