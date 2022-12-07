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
			{
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
						SetHitState(true);

						if (type == Type_Enemy && this->GetType() == Type_Player)
						{
							return true;
						}

						pHitbox[nCnt]->SetHitState(true);
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
						SetHitState(true);

						if (type == Type_Enemy && this->GetType() == Type_Player)
						{
							return true;
						}

						pHitbox[nCnt]->SetHitState(true);
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
	float fUp, fDown, fRight, fLeft;
	fUp = pos.y - m_fRadius - size.y;
	fDown = pos.y + m_fRadius + size.y;
	fRight = pos.x + m_fRadius + size.x;
	fLeft = pos.x - m_fRadius - size.x;

	D3DXVECTOR3 center = GetPos();

	if (center.x >= fLeft && center.x <= fRight && center.y >= fUp && center.y <= fDown)
	{
		return true;
	}

	return false;
}

//丸と丸の当たり判定
bool CCircleHitbox::CircleCircleHit(const D3DXVECTOR3 center, const float radius)
{
	D3DXVECTOR3 pos = GetPos();

	float fResult = ((pos.x - center.x) * (pos.x - center.x)) + (pos.y - center.y) * (pos.y - center.y);
	float fRadius = (radius + m_fRadius) * (radius + m_fRadius);

	if (fResult < fRadius)
	{
		return true;
	}

	return false;
}


//=============================================================================
//静的関数 
//=============================================================================

//生成処理
CCircleHitbox* CCircleHitbox::Create(const D3DXVECTOR3 pos, const float fRadius, const Type type)
{
	CCircleHitbox* pHitbox = new CCircleHitbox;			//生成処理

	//初期化処理
	if (FAILED(pHitbox->Init()))
	{
		return nullptr;
	}

	pHitbox->SetPos(pos);								//位置の設定
	pHitbox->m_fRadius = fRadius;						//半径の設定
	pHitbox->SetType(type);								//種類の設定

	return pHitbox;										
}