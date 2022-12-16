//=============================================================================
//
// object.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "object.h"
#include "object2D.h"
#include "player.h"
#include <random>

//=============================================================================
//静的メンバー変数の宣言 
//=============================================================================
int CObject::m_nNumAll = 0;										//存在するポリゴン数
CObject* CObject::m_pObject[CObject::MaxObject] = {};			//オブジェクトへのポンタ
int CObject::m_PlayerIdx = -1;
int CObject::m_nPriorityObjNum[CObject::Max_Priority] = {};
bool CObject::m_bPause = false;

//=============================================================================
//コンストラクタ
//=============================================================================
CObject::CObject()
{
	m_nNumAll++;							//ポリゴン数の更新処理
	m_type = OBJECT_MAX;

	for (int nCnt = 0; nCnt < MaxObject; nCnt++)
	{
		if (m_pObject[nCnt] == nullptr)
		{
			m_pObject[nCnt] = this;
			m_pObject[nCnt]->m_nIdx = nCnt;
			break;
		}
	}

	m_nPriority = 3;

	m_nPriorityObjNum[m_nPriority - 1]++;
}

//=============================================================================
//デストラクタ
//=============================================================================
CObject::~CObject()
{

}

//オブジェクトを消す処理
void CObject::Release(void)
{
	m_nPriorityObjNum[m_nPriority - 1]--;
	int Idx = m_nIdx;					//配列のインデックスを保存する
	m_pObject[Idx]->Uninit();			//オブジェクトの終了処理
	delete m_pObject[Idx];				//オブジェクトを消す
	m_pObject[Idx] = nullptr;			//ポインタをnullにする
}

//オブジェクトの種類の取得処理
const  CObject::EObjType CObject::GetObjType(void)
{
	return m_type;			//種類を返す
}

//オブジェクトの種類の設定処理
void CObject::SetObjType(const EObjType type)
{
	m_type = type;
}

//プライオリティの設定処理
void CObject::SetPriority(int nPriority)
{
	if (nPriority < 1)
	{//プライオリティが0以下だったら、1に設定する
		nPriority = 1;
	}
	else if(nPriority > 5)
	{//プライオリティが6以上だったら、5に設定する
		nPriority = 5;
	}

	int nLastPriority = m_nPriority;

	m_nPriority = nPriority;					//プライオリティの設定

	//配列の更新
	m_nPriorityObjNum[nLastPriority - 1]--;
	m_nPriorityObjNum[m_nPriority - 1]++;
}

//===============================================================================
//
//								静的関数
//
//===============================================================================

//=============================================================================
//全部の終了処理
//=============================================================================
void CObject::ReleaseAll(void)
{
	for (int nCnt = 0; nCnt < MaxObject; nCnt++)
	{
		if (m_pObject[nCnt] != nullptr)
		{//ポインタはnullではなかったら
			delete m_pObject[nCnt];				//メモリを解放する
			m_pObject[nCnt] = nullptr;			//nullにする
		}
	}

	m_nNumAll = 0;								//存在しているオブジェクトを0にする

	for (int nCnt = 0; nCnt < Max_Priority; nCnt++)
	{
		m_nPriorityObjNum[nCnt] = 0;
	}	
}

//=============================================================================
//全部の更新処理
//=============================================================================
void CObject::UpdateAll(void)
{
	for (int nCnt = 0; nCnt < MaxObject; nCnt++)
	{
		if (m_pObject[nCnt] != nullptr)
		{//ポインタはnullではなかったら

			if (!m_bPause || m_pObject[nCnt]->m_type == OBJTYPE_MENU)
			{
				m_pObject[nCnt]->Update();				//インスタンスの更新処理
			}
		}
	}
}

//=============================================================================
//全部の描画処理
//=============================================================================
void CObject::DrawAll(void)
{
	for (int a = 1; a <= Max_Priority; a++)
	{
		for (int nCnt = 0; nCnt < MaxObject; nCnt++)
		{
			int nPriorityObj = 0;

			if (m_pObject[nCnt] != nullptr)
			{//ポインタはnullではなかったら
				if (m_pObject[nCnt]->m_nPriority == a)
				{
					m_pObject[nCnt]->Draw();				//インスタンスの描画処理

					nPriorityObj++;

					if (nPriorityObj >= m_nPriorityObjNum[a - 1])
					{
						break;
					}
				}
			}
		}
	}
}



//オブジェクトの取得処理
CObject** CObject::GetObj(void)
{
	return m_pObject;
}

//プレイヤーのインデックスの保存処理
void CObject::SavePlayerIdx(CPlayer* ptr)
{
	for (int nCnt = 0; nCnt < MaxObject; nCnt++)
	{
		if (m_pObject[nCnt] == ptr)
		{
			m_PlayerIdx = nCnt;
		}
	}
}

//ポーズ状態の設定処理
void CObject::SetPause(const bool bPause)
{
	m_bPause = bPause;
}

//当たり判定(丸)
bool CObject::CircleHit(D3DXVECTOR3* pos1, D3DXVECTOR3* pos2, float fRadius1, float fRadius2)
{
	float radius = (fRadius1 * fRadius1) + (fRadius2 * fRadius2);

	float deltaX = (pos2->x - pos1->x) * (pos2->x - pos1->x);
	float deltaY = (pos2->y - pos1->y) * (pos2->y - pos1->y);

	if (deltaX + deltaY <= radius)
	{
		return true;
	}

	return false;
}

bool CObject::CircleHit(D3DXVECTOR3* pos1, D3DXVECTOR3* pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2)
{
	float fRadius1 = 0.5f * ((size1.x) + (size1.y));
	float fRadius2 = 0.5f * ((size2.x) + (size2.y));

	float radius = (fRadius1 * fRadius1) + (fRadius2 * fRadius2);

	float deltaX = (pos2->x - pos1->x) * (pos2->x - pos1->x);
	float deltaY = (pos2->y - pos1->y) * (pos2->y - pos1->y);

	if ((deltaX + deltaY) <= radius)
	{
		return true;
	}

	return false;
}

//当たり判定(四角形)
bool CObject::HitBox(D3DXVECTOR3* pos1, D3DXVECTOR3* pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2)
{
	float top, bottom, right, left;
	left = pos2->x - (size1.x + size2.x);
	right = pos2->x + (size1.x + size2.x);
	top = pos2->y - (size1.y + size2.y);
	bottom = pos2->y + (size1.y + size2.y);

	if (pos1->x >= left && pos1->x <= right &&
		pos1->y >= top && pos1->y <= bottom)
	{
		return true;
	}

	return false;
}

D3DXVECTOR3 CObject::GetPerpendicularVersor(D3DXVECTOR3 V)
{
	D3DXVECTOR3 Result, Unit;
	float fHalfPi = D3DX_PI * 0.5f;

	Unit = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	if (V.y > Unit.y)
	{
		fHalfPi *= -1.0f;
	}

	D3DXVec3Normalize(&V, &V);

	float fDot = D3DXVec3Dot(&V, &Unit);

	float fAngle = (float)acos(fDot);

	Result = D3DXVECTOR3(cosf(fAngle + fHalfPi), sinf(fAngle + fHalfPi), 0.0f);

	return Result;
}

std::random_device rd;
std::mt19937 gen(rd());

//乱数を返す関数
int CObject::random(const int low, const int high)
{
	std::uniform_int_distribution<> dist(low, high);
	return dist(gen);
}