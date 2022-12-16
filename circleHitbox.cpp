//=============================================================================
//
// circleHitbox.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "circleHitbox.h"

//コンストラクタ
CCircleHitbox::CCircleHitbox()
{
	//メンバー変数をクリアする
	m_fRadius = 0.0f;
}

//デストラクタ
CCircleHitbox::~CCircleHitbox()
{

}

//初期化処理
HRESULT CCircleHitbox::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CHitbox::Init()))
	{
		return -1;
	}

	//メンバー変数の初期化
	m_fRadius = 0.0f;
	SetShape(shape_Circle);

	return S_OK;
}

//終了処理
void CCircleHitbox::Uninit(void)
{
	//基本クラスの終了処理
	CHitbox::Uninit();
}

//当たり判定
bool CCircleHitbox::Hit(void)
{
	CHitbox** pHitbox = GetAllHitbox();			
	//SetHitState(false);

	for (int nCnt = 0; nCnt < CHitbox::MaxHitbox; nCnt++)
	{
		if (pHitbox[nCnt] != nullptr && pHitbox[nCnt] != this)
		{
			CHitbox::Type type = pHitbox[nCnt]->GetType();				//種類の取得処理

			if (type == Type_Enemy && this->GetType() == Type_Player || 
				type == Type_Player && this->GetType() == Type_Enemy ||
				type == Type_Enemy && this->GetType() == Type_PlayerBullet ||
				type == Type_Player && this->GetType() == Type_EnemyBullet)
			{//種類の確認
				Shape shape = pHitbox[nCnt]->GetShape();				//形の取得処理

				switch (shape)
				{
				case shape_Square:

				{
					D3DXVECTOR3 pos = pHitbox[nCnt]->GetPos();			//位置の取得
					D3DXVECTOR2 size = pHitbox[nCnt]->GetSize();		//サイズの取得

					//当たり判定
					if (CircleSquareHit(pos, size))
					{
						SetHitState(true);						//当たった状態にする

						if (type == Type_Enemy && this->GetType() == Type_Player)
						{//プレイヤーは敵に当たった場合、敵にダメージを与えないことにする
							return true;
						}

						pHitbox[nCnt]->SetHitState(true);		//相手を当たった状態にする
						return true;
					}

				}

				break;

				case shape_Circle:

				{
					D3DXVECTOR3 pos = pHitbox[nCnt]->GetPos();			//位置の取得
					float radius = pHitbox[nCnt]->GetRadius();			//半径の取得

					//当たり判定
					if (CircleCircleHit(pos, radius))
					{
						SetHitState(true);						//当たった状態にする

						if (type == Type_Enemy && this->GetType() == Type_Player)
						{//プレイヤーは敵に当たった場合、敵にダメージを与えないことにする
							return true;
						}

						pHitbox[nCnt]->SetHitState(true);		//相手を当たった状態にする
						return true;
					}

				}

				break;

				default:
					break;
				}
			}
		}
	}

	return false;
}

//サイズの取得処理
const D3DXVECTOR2 CCircleHitbox::GetSize(void)
{
	return D3DXVECTOR2(0.0f, 0.0f);
}

//半径の取得処理
const float CCircleHitbox::GetRadius(void)
{
	return m_fRadius;
}

//半径の設定処理
void CCircleHitbox::SetRadius(const float radius)
{
	m_fRadius = radius;
}

//丸と四角形の当たり判定
bool CCircleHitbox::CircleSquareHit(const D3DXVECTOR3 pos, const D3DXVECTOR2 size)
{
	//省略用のローカル変数
	float fUp, fDown, fRight, fLeft;
	fUp = pos.y - m_fRadius - size.y;
	fDown = pos.y + m_fRadius + size.y;
	fRight = pos.x + m_fRadius + size.x;
	fLeft = pos.x - m_fRadius - size.x;

	D3DXVECTOR3 center = GetPos();		//中心点の取得

	if (center.x >= fLeft && center.x <= fRight && center.y >= fUp && center.y <= fDown)
	{//判定
		return true;
	}

	return false;
}

//丸と丸の当たり判定
bool CCircleHitbox::CircleCircleHit(const D3DXVECTOR3 center, const float radius)
{
	D3DXVECTOR3 pos = GetPos();		//位置の取得

	float fResult = ((pos.x - center.x) * (pos.x - center.x)) + (pos.y - center.y) * (pos.y - center.y);	//距離を計算する
	float fRadius = (radius + m_fRadius) * (radius + m_fRadius);			//半径の足し算を計算する

	if (fResult < fRadius)
	{//判定
		return true;
	}

	return false;
}


//=============================================================================
//
//								静的関数 
//
//=============================================================================

//生成処理
CCircleHitbox* CCircleHitbox::Create(const D3DXVECTOR3 pos, const float fRadius, const Type type)
{
	CCircleHitbox* pHitbox = new CCircleHitbox;			//インスタンスを生成する

	//初期化処理
	if (FAILED(pHitbox->Init()))
	{
		return nullptr;
	}

	pHitbox->SetPos(pos);			//位置の設定
	pHitbox->m_fRadius = fRadius;	//半径の設定
	pHitbox->SetType(type);			//種類の設定

	return pHitbox;					//生成したインスタンスを返す							
}	