//=============================================================================
//
// spine.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef SPINE_H
#define SPINE_H

//=============================================================================
//インクルードファイルと前方宣言
//=============================================================================
#include "object.h"
class CVertebra;

class CSpine : public CObject
{
public:

	static const int VertebraNumber = 8;					//骨の数


	CSpine();												//コンストラクタ
	~CSpine() override;										//デストラクタ
															
	HRESULT Init(void) override;							//初期化処理
	void Uninit(void) override;								//終了処理
	void Update(void) override;								//更新処理
	void Draw(void) override;								//描画処理

	void SetPos(const D3DXVECTOR3 pos);						//位置の設定処理
	void SetHeadPos(const D3DXVECTOR3 pos);					//頭の位置の設定処理

	const D3DXVECTOR2 GetSize(void) override;				//サイズの取得処理
	const D3DXVECTOR3 GetPos(void) override;				//位置の設定処理

	void Kill(void);										//死亡アニメーションの設定処理
	void Flip(void);

	static CSpine* Create(D3DXVECTOR3 anchor, D3DXVECTOR3 head);		//生成処理

private:

	CVertebra* m_pVertebra[VertebraNumber];
	D3DXVECTOR3 m_anchor;									//位置の設定処理
	D3DXVECTOR3 m_head;										//頭の位置の設定処理
	int m_nCntDestroy;										//死亡アニメーション用のカウンター
	bool m_bDead;											//死んでいるかどうか
};															



#endif