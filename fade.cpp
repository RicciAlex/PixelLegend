//=============================================================================
//
// fade.cpp
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "fade.h"
#include "object2D.h"

//コンストラクタ
CFade::CFade()
{
	//メンバー変数をクリアする
	m_fade = FADE_NONE;
	m_pFade = nullptr;
	m_mode = CApplication::Mode_Title;
}

//デストラクタ
CFade::~CFade()
{

}

//初期化処理
HRESULT CFade::Init(void)
{
	//メンバー変数を初期化する
	m_pFade = nullptr;

	m_mode = CApplication::Mode_Title;

	m_fade = FADE_NONE;

	return S_OK;
}

//終了処理
void CFade::Uninit(void)
{
	//フェード用のポリゴンを破棄する
	if (m_pFade != nullptr)
	{//nullチェック
		m_pFade->Release();			//メモリを解放する
		m_pFade = nullptr;			//nullにする
	}
}

//更新処理
void CFade::Update(void)
{
	switch (m_fade)
	{
	case CFade::FADE_NONE:

		break;

	case CFade::FADE_IN:

	{//フェードインだったら
		if (m_pFade != nullptr)
		{//フェード用のポリゴンがnullではなかったら

			D3DXCOLOR col = m_pFade->GetColor();			//色の取得

			col.a -= 0.025f;			//α値を更新する

			if (col.a <= 0.0f)
			{//α値が0以下になったら
				m_pFade->Release();					//フェード用のポリゴンを破棄する
				m_pFade = nullptr;					//ポインタをnullにする
				m_fade = FADE_NONE;					//フェード状態の設定
				CApplication::SetFade(false);		//フェードが終わったことを設定する
			}
			else
			{
				m_pFade->SetColor(col);				//色の設定
			}
		}
		
	}

		break;

	case CFade::FADE_OUT:

	{//フェードアウトだったら
		if (m_pFade != nullptr)
		{//nullチェック

			D3DXCOLOR col = m_pFade->GetColor();			//色の取得

			col.a += 0.025f;			//α値の更新

			if (col.a >= 1.0f)
			{//α値が
				m_pFade->Release();
				m_pFade = nullptr;
				m_fade = FADE_IN;

				CApplication::SetMode(m_mode);

				SetFadeIn();
			}
			else
			{
				m_pFade->SetColor(col);
			}
		}
	}

		break;

	default:
		break;
	}
}

//描画処理
void CFade::Draw(void)
{
	if (m_pFade != nullptr)
	{
		m_pFade->Draw();
	}
}




//フェードインの設定処理
void CFade::SetFadeIn(void)
{
	m_fade = FADE_IN;

	CApplication::SetFade(true);

	if (m_pFade == nullptr)
	{
		m_pFade = CObject_2D::Create();

		if (m_pFade != nullptr)
		{
			m_pFade->SetTexture(CObject::TextureNull);
			m_pFade->SetTextureParameter(1, 1, 1, INT_MAX);
			m_pFade->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
			m_pFade->SetPos(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f));
			m_pFade->SetSize(D3DXVECTOR2((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f));
			m_pFade->SetStartingRot(D3DX_PI * 0.5f);
			m_pFade->SetPriority(5);
		}
	}
}

//フェードアウトの設定処理
void CFade::SetFadeOut(CApplication::Mode mode)
{
	m_fade = FADE_OUT;

	CApplication::SetFade(true);

	if (m_pFade == nullptr)
	{
		m_pFade = CObject_2D::Create();

		if (m_pFade != nullptr)
		{
			m_pFade->SetTexture(CObject::TextureNull);
			m_pFade->SetTextureParameter(1, 1, 1, INT_MAX);
			m_pFade->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
			m_pFade->SetPos(D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f));
			m_pFade->SetSize(D3DXVECTOR2((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f));
			m_pFade->SetStartingRot(D3DX_PI * 0.5f);
			m_pFade->SetPriority(5);

			m_mode = mode;
		}
	}
}

//生成処理
CFade* CFade::Create(void)
{
	CFade* pFade = new CFade;

	if (FAILED(pFade->Init()))
	{
		return nullptr;
	}

	pFade->SetFadeIn();

	return pFade;
}