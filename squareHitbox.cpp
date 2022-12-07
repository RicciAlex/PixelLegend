//=============================================================================
//
// squareHitbox.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "squareHitbox.h"

//コンストラクタ
CSquareHitbox::CSquareHitbox()
{
	//メンバー変数をクリアする
	m_size = D3DXVECTOR2(0.0f, 0.0f);
}

//デストラクタ
CSquareHitbox::~CSquareHitbox()
{

}

//初期化処理
HRESULT CSquareHitbox::Init(void)
{
	//基本クラスの初期化処理
	if (FAILED(CHitbox::Init()))
	{
		return -1;
	}

	//メンバー変数の初期化
	m_size = D3DXVECTOR2(0.0f, 0.0f);
	SetShape(shape_Square);

	return S_OK;
}

//終了処理
void CSquareHitbox::Uninit(void)
{
	//基本クラスの終了処理
	CHitbox::Uninit();
}

//当たり判定
bool CSquareHitbox::Hit(void)
{
	CHitbox** pHitbox = GetAllHitbox();

	//if (GetType() != Type_Player && GetType() != Type_Enemy)
	//{
	//	SetHitState(false);
	//}

	for (int nCnt = 0; nCnt < CHitbox::MaxHitbox; nCnt++)
	{
		if (pHitbox[nCnt] != nullptr)
		{
			CHitbox::Type type = pHitbox[nCnt]->GetType();					//種類の取得処理

			if (type == Type_Enemy && this->GetType() == Type_Player ||
				type == Type_Player && this->GetType() == Type_Enemy ||
				type == Type_Enemy && this->GetType() == Type_PlayerBullet ||
				type == Type_Player && this->GetType() == Type_EnemyBullet)
			{
				Shape shape = pHitbox[nCnt]->GetShape();					//形の取得処理

				switch (shape)
				{
				case shape_Square:

				{
					D3DXVECTOR3 pos = pHitbox[nCnt]->GetPos();				//位置の取得
					D3DXVECTOR2 size = pHitbox[nCnt]->GetSize();			//サイズの取得

					if (SquareSquareHit(pos, size))
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
					D3DXVECTOR3 pos = pHitbox[nCnt]->GetPos();				//位置の取得
					float radius = pHitbox[nCnt]->GetRadius();				//半径の取得

					if (SquareCircleHit(pos, radius))
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

//サイズの取得処理
const D3DXVECTOR2 CSquareHitbox::GetSize(void)
{
	return m_size;
}

const float CSquareHitbox::GetRadius(void)
{
	return 0.0f;
}

//サイズの設定処理
void CSquareHitbox::SetSize(const D3DXVECTOR2 size)
{
	m_size = size;
}

//四角形と四角形の当たり判定
bool CSquareHitbox::SquareSquareHit(const D3DXVECTOR3 pos, const D3DXVECTOR2 size)
{
	D3DXVECTOR2 Size = GetSize();
	float fUp, fDown, fRight, fLeft;
	fUp = GetPos().y - size.y - Size.y;
	fDown = GetPos().y + size.y + Size.y;
	fRight = GetPos().x + size.x + Size.x;
	fLeft = GetPos().x - size.x - Size.x;

	if (pos.x >= fLeft && pos.x <= fRight && pos.y >= fUp && pos.y <= fDown)
	{
		return true;
	}

	return false;
}

//四角形と丸の当たり判定
bool CSquareHitbox::SquareCircleHit(const D3DXVECTOR3 center, const float radius)
{
	float fUp, fDown, fRight, fLeft;
	D3DXVECTOR2 size = GetSize();
	fUp = GetPos().y - radius - size.y;
	fDown = GetPos().y + radius + size.y;
	fRight = GetPos().x + radius + size.x;
	fLeft = GetPos().x - radius - size.x;

	if (center.x >= fLeft && center.x <= fRight && center.y >= fUp && center.y <= fDown)
	{
		return true;
	}

	return false;
}


//=============================================================================
//静的関数 
//=============================================================================


//生成処理
CSquareHitbox* CSquareHitbox::Create(const D3DXVECTOR3 pos, const D3DXVECTOR2 size, const Type type)
{
	CSquareHitbox* pHitbox = new CSquareHitbox;			//生成

	//初期化処理
	if (FAILED(pHitbox->Init()))
	{
		return nullptr;
	}

	pHitbox->SetPos(pos);								//位置の設定
	pHitbox->SetSize(size);								//サイズの設定
	pHitbox->SetType(type);								//種類の取得

	return pHitbox;
}