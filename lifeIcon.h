//=============================================================================
//
// lifeIcon.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef LIFE_ICON_H
#define LIFE_ICON_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "object.h"

//=============================================================================
//前方宣言
//=============================================================================
class CObject_2D;

class CLifeIcon : public CObject
{
public:

	CLifeIcon();										//コンストラクタ
	~CLifeIcon() override;								//デストラクタ

	HRESULT Init(void) override;						//初期化処理
	void Uninit(void) override;							//終了処理
	void Update(void) override;							//更新処理
	void Draw(void) override;							//描画処理

	void SetPos(const D3DXVECTOR3 pos) override;		//位置の設定処理

	const D3DXVECTOR2 GetSize(void) override;			//サイズの取得処理
	const D3DXVECTOR3 GetPos(void) override;			//位置の取得処理

	static CLifeIcon* Create(const D3DXVECTOR3 pos);	//生成処理

private:

	static const int MaxHeart = 5;						//アイコンの最大数
														
	D3DXVECTOR3 m_pos;									//位置
	D3DXVECTOR2 m_size;									//サイズ
														
	CObject_2D* m_pHeart[MaxHeart];						//アイコンへのポインタ

};

#endif