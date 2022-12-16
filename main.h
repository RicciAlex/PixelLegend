//=============================================================================
//
// main.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef MAIN_H
#define MAIN_H

//=============================================================================
// ライブラリーリンク
//=============================================================================
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"winmm.lib")

//=============================================================================
// インクルード
//=============================================================================
#include <Windows.h>
#include <tchar.h> // _T
#include <d3dx9.h>

//=============================================================================
// 前方宣言
//=============================================================================
class CRenderer;
class CObject;

//=============================================================================
// 定数定義
//=============================================================================
namespace
{
	// ウインドウのクラス名
	LPCTSTR CLASS_NAME = _T("AppClass");
	// ウインドウのキャプション名
	LPCTSTR WINDOW_NAME = _T("Pixel Legend");
}

// スクリーンの幅
const int SCREEN_WIDTH = 1280;
// スクリーンの高さ
const int SCREEN_HEIGHT = 720;
// 頂点フォーマット
const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);

//=============================================================================
// 構造体定義
//=============================================================================


//=============================================================================
// プロトタイプ宣言
//=============================================================================
int GetFPS(void);							//FPSの取得処理

#endif // !MAIN_H
