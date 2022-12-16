//=============================================================================
//
// object2D.h
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "object2D.h"
#include "rendering.h"
#include "application.h"
#include "inputKeyboard.h"

//静的メンバー変数の宣言
LPDIRECT3DTEXTURE9 CObject_2D::m_pTextureAll[CObject_2D::TextTypeMax] = {};

char* CObject_2D::m_paTextPass[CObject::TextTypeMax] =
{
	"data\\TEXTURE\\Bullet\\Balloon.png",									//TextureBalloon	
	"data\\TEXTURE\\Enemy\\BalloonEnemy.png",								//TextureBalloonEnemy
	"data\\TEXTURE\\Bullet\\BlackHole.png",									//TextureBlackHole
	"data\\TEXTURE\\Bullet\\Bone.png",										//TextureBone
	"data\\TEXTURE\\Enemy\\BubbleBat.png",									//TextureBubbleBat

	"data\\TEXTURE\\Candle.png",											//TextureCandle	
	"data\\TEXTURE\\Clock.png",												//TextureClock
	"data\\TEXTURE\\Bullet\\ClockNeedle.png",								//TextureClockNeedle
	"data\\TEXTURE\\Cloud.png",												//TextureCloud
	"data\\TEXTURE\\Bullet\\Coin.png",										//TextureCoin

	"data\\TEXTURE\\DifficultyStar.png",									//TextureDifficultyIcon
	"data\\TEXTURE\\DiffLogo.png",											//TextureDifficultyLogo
	"data\\TEXTURE\\Player.png",											//TextureDragon	

	"data\\TEXTURE\\Explosion.png",											//TextureExplosion
	"data\\TEXTURE\\Bg\\EnvyBg.png",										//TextureEnvyBg

	"data\\TEXTURE\\Enemy\\Envy\\Face.png",									//TextureFace
	"data\\TEXTURE\\Bullet\\Fireball_Sprite.png",							//TextureFireball

	"data\\TEXTURE\\Enemy\\Envy\\Gear_Sprite.png",							//TextureGear
	"data\\TEXTURE\\Enemy\\Gluttony\\GluttonyBackMaw.png",					//TextureGluttonyBackMaw
	"data\\TEXTURE\\Bg\\GluttonyBg.png",									//TextureGluttonyBg
	"data\\TEXTURE\\Enemy\\Gluttony\\GluttonyHeart.png",					//TextureGluttonyHeart
	"data\\TEXTURE\\Enemy\\Gluttony\\GluttonyMaw.png",						//TextureGluttonyMaw
	"data\\TEXTURE\\Enemy\\GluttonySkeleton.png",							//TextureGluttonyMinion
	"data\\TEXTURE\\Enemy\\Greed\\Greed.png",								//TextureGreed
	"data\\TEXTURE\\Bg\\GreedBg.png",										//TextureGreedBg

	"data\\TEXTURE\\Enemy\\Hand.png",										//TextureHand
	"data\\TEXTURE\\Bullet\\HandBlade.png",									//TextureHandBlade
	"data\\TEXTURE\\Bullet\\HandFireball.png",								//TextureHandFireball

	"data\\TEXTURE\\Icons\\AIcon.png",										//TextureIconA
	"data\\TEXTURE\\Icons\\DIcon.png",										//TextureIconD
	"data\\TEXTURE\\Icons\\MouseIcon.png",									//TextureIconMouse
	"data\\TEXTURE\\Icons\\SIcon.png",										//TextureIconS
	"data\\TEXTURE\\Icons\\WIcon.png",										//TextureIconW

	"data\\TEXTURE\\Bullet\\Jewel.png",										//TextureJewel

	"data\\TEXTURE\\Icons\\EIcon.png",										//TextureLateralEIcon
	"data\\TEXTURE\\Icons\\QIcon.png",										//TextureLateralQIcon
	"data\\TEXTURE\\Bullet\\Laugh.png",										//TextureLaugh
	"data\\TEXTURE\\PixelAlphabet.png",										//TextureLetters
	"data\\TEXTURE\\LifeIcon.png",											//TextureLifeIcon

	"data\\TEXTURE\\MenuBg.png",											//TextureMenuBg
	"data\\TEXTURE\\Bullet\\Missile.png",									//TextureMissile

	"data\\TEXTURE\\Effect\\effect105.png",									//TextureNormalEffect
	" ",																	//TextureNull
	"data\\TEXTURE\\Numbers.png",											//TextureNumbers

	"data\\TEXTURE\\Enemy\\Envy\\Pipe.png",									//TexturePipe
	"data\\TEXTURE\\Icons\\PressSpaceIcon.png",								//TexturePressSpaceIcon
	"data\\TEXTURE\\Enemy\\PrideSprite.png",								//TexturePride
	"data\\TEXTURE\\Bg\\PrideBg.png",										//TexturePrideBg

	"data\\TEXTURE\\Effect\\tex_eff_light02.png",							//TextureRoundEffect

	"data\\TEXTURE\\Enemy\\Scylla\\ScyllaBody.png",							//TextureScyllaBody
	"data\\TEXTURE\\Bullet\\Scythe.png",									//TextureScythe
	"data\\TEXTURE\\BG\\Sea.png",											//TextureSeaBG
	"data\\TEXTURE\\Enemy\\Scylla\\WivernSkull_Sprite.png",					//TextureSkull
	"data\\TEXTURE\\Bullet\\SkullFireball.png",								//TextureSkullFireball
	"data\\TEXTURE\\Enemy\\SkullShield.png",								//TextureSkullShield
	"data\\TEXTURE\\Enemy\\SlothSprite.png",								//TextureSloth
	"data\\TEXTURE\\BG\\SlothBg.png",										//TextureSlothBG
	"data\\TEXTURE\\Bullet\\Spike.png",										//TextureSpike
	"data\\TEXTURE\\Bullet\\SpikeBomb.png",									//TextureSpikeBomb
	"data\\TEXTURE\\Bullet\\SpringAndScrew.png",							//TextureSpringAndScrew

	"data\\TEXTURE\\Target.png",											//TextureTarget
	"data\\TEXTURE\\Bullet\\Tear.png",										//TextureTeardrop
	"data\\TEXTURE\\Enemy\\Thanatos.png",									//TextureThanatos
	"data\\TEXTURE\\BG\\ThanatosBg.png",									//TextureThanatosBG
	"data\\TEXTURE\\Bullet\\Thunder.png",									//TextureThunder
	"data\\TEXTURE\\Enemy\\Envy\\TopHat.png",								//TextureTopHat

	"data\\TEXTURE\\Enemy\\Scylla\\Vertebra.png",							//TextureVertebra

	"data\\TEXTURE\\Wing.png",												//TextureWing
	"data\\TEXTURE\\Enemy\\Wrath.png",										//TextureWrath
	"data\\TEXTURE\\WrathArm.png",											//TextureWrathArm
	"data\\TEXTURE\\BG\\WrathBg.png",										//TextureWrathBg
	"data\\TEXTURE\\WrathBody.png",											//TextureWrathBody

};

//=============================================================================
//コンストラクタ
//=============================================================================
CObject_2D::CObject_2D()
{
	m_pVtxBuff = nullptr;								//頂点バッファ
	m_dimension = D3DXVECTOR2(0.0f, 0.0f);				//ポリゴンの幅と高さ
	m_dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//ポリゴンの向き
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//移動量
	m_acc = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//加速
	m_fRot = 0.0f;										//ポリゴンの回転角度
	m_fAngle = 0.0f;									//ポリゴンの回転用の角度
	m_fFrameRot = 0.0f;									//1フレームの回転角度
	m_revolutionCenter = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//公転の中心点
	m_fRevolutionSpeed = 0.0f;							//公転のスピード
	m_fRevolutionAngle = 0.0f;							//公転の現在角度
	m_fRevolutionRadius = 0.0f;							//公転の半径
	m_posPolygon = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//ポリゴンの位置
	m_nCountAnim = 0;									//現在のテクスチャパターン
	m_nAnimPattern = 0;									//アニメーションカウンター
	m_nMaxTexPattern = 0;								//テクスチャのパターン数
	m_nMaxTexColumn = 0;								//テクスチャの行数
	m_nTexLine = 0;										//テクスチャの列数
	m_nAnimFrame = 0;									//アニメーションパターンの変更フレーム数
	m_textureTranslation = D3DXVECTOR2(0.0f, 0.0f);
	m_bFlipX = false;
	m_bFlipY = false;
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_textType = CObject::TextTypeMax;					//テクスチャの種類

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_VtxCol[nCnt] = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	}
}														  

//=============================================================================
//デストラクタ
//=============================================================================
CObject_2D::~CObject_2D()
{

}

//=============================================================================
// ポリゴンの初期化
//=============================================================================
HRESULT CObject_2D::Init(void)
{
	CRenderer* Render = CApplication::GetRenderer();			//レンディングインスタンスの取得処理
	LPDIRECT3DDEVICE9 pDevice = Render->GetDevice();			//デバイスの取得処理

	m_dimension = D3DXVECTOR2(0.0f, 0.0f);						//ポリゴンの幅と高さの設定
	m_dir = D3DXVECTOR3(1.0f, 0.0f, 0.0f);						//ポリゴンの向き
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						//移動量
	m_acc = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						//加速
	m_fRot = 0.0f;												//回転角度の設定
	m_fAngle = 0.0f;											//回転用の角度を計算する
	m_fFrameRot = 0.0f;											//1フレームの回転角度
	m_revolutionCenter = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//公転の中心点
	m_fRevolutionSpeed = 0.0f;									//公転のスピード
	m_fRevolutionAngle = 0.0f;									//公転の現在角度
	m_fRevolutionRadius = 0.0f;									//公転の半径
	m_posPolygon = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//位置の設定
	m_nCountAnim = 0;											//現在のテクスチャパターン
	m_nAnimPattern = 0;											//アニメーションカウンター
	m_nMaxTexPattern = 1;										//テクスチャのパターン数
	m_nMaxTexColumn = 1;										//テクスチャの行数
	m_nTexLine = 1;												//テクスチャの列数
	m_textureTranslation = D3DXVECTOR2(0.0f, 0.0f);
	m_bFlipX = false;
	m_bFlipY = false;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_nAnimFrame = 0;											//アニメーションパターンの変更フレーム数

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_VtxCol[nCnt] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D* pVtx = nullptr;					//頂点情報へのポインタ

	//頂点バッファのロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定

	pVtx[0].pos.x = (m_posPolygon.x) + sinf(m_fRot + (m_fAngle + 2.0f * (D3DX_PI * 0.5f - m_fAngle))) * (m_dimension.x);
	pVtx[0].pos.y = (m_posPolygon.y) + cosf(m_fRot + (m_fAngle + 2.0f * (D3DX_PI * 0.5f - m_fAngle))) * (m_dimension.x);
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = (m_posPolygon.x) + sinf(m_fRot + m_fAngle) * (m_dimension.x);
	pVtx[1].pos.y = (m_posPolygon.y) + cosf(m_fRot + m_fAngle) * (m_dimension.x);
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = (m_posPolygon.x) + sinf(m_fRot - (m_fAngle + 2.0f * (D3DX_PI * 0.5f - m_fAngle))) * (m_dimension.x);
	pVtx[2].pos.y = (m_posPolygon.y) + cosf(m_fRot - (m_fAngle + 2.0f * (D3DX_PI * 0.5f - m_fAngle))) * (m_dimension.x);
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = (m_posPolygon.x) + sinf(m_fRot - m_fAngle) * (m_dimension.x);
	pVtx[3].pos.y = (m_posPolygon.y) + cosf(m_fRot - m_fAngle) * (m_dimension.x);
	pVtx[3].pos.z = 0.0f;

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		// rhwの設定
		pVtx[nCnt].rhw = 1.0f;
		// 頂点カラーの設定
		pVtx[nCnt].col = m_col;
	}

	//テクスチャとテクスチャパラメータの初期化
	SetTexture(TextureNull);
	SetTextureParameter(1, 1, 1, INT_MAX);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// ポリゴンの終了
//=============================================================================
void CObject_2D::Uninit()
{
	//頂点バッファの破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//=============================================================================
// ポリゴンの更新
//=============================================================================
void CObject_2D::Update()
{
	VERTEX_2D* pVtx = nullptr;					//頂点情報へのポインタ

	//頂点バッファをロックする
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_nCountAnim++;								//アニメーションカウンターの更新

	if (m_nCountAnim >= m_nAnimFrame)
	{
		m_nCountAnim = 0;						//アニメーションカウンターを0に戻す
		m_nAnimPattern++;						//アニメーションパターンの更新

		if (m_nAnimPattern >= m_nMaxTexPattern)
		{//アニメーションの最後のパターンを超えた場合
			m_nAnimPattern = 0;					//アニメーションパターンを0に戻す
		}
	}

	//公転があったら
	if (m_fRevolutionRadius != 0.0f)
	{
		m_revolutionCenter += GetMove();			//中心点の位置の更新

		//位置の更新
		m_posPolygon.x = m_revolutionCenter.x + (cosf(m_fRevolutionAngle) * (m_fRevolutionRadius));
		m_posPolygon.y = m_revolutionCenter.y + (sinf(m_fRevolutionAngle) * (m_fRevolutionRadius));
	}

	float dim = sqrtf((m_dimension.x * m_dimension.x) + (m_dimension.y * m_dimension.y));

	//頂点座標の更新
	pVtx[0].pos.x = (m_posPolygon.x) + sinf(m_fRot + (m_fAngle + 2.0f * (D3DX_PI * 0.5f - m_fAngle))) * (dim);
	pVtx[0].pos.y = (m_posPolygon.y) + cosf(m_fRot + (m_fAngle + 2.0f * (D3DX_PI * 0.5f - m_fAngle))) * (dim);
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = (m_posPolygon.x) + sinf(m_fRot + m_fAngle) * (dim);
	pVtx[1].pos.y = (m_posPolygon.y) + cosf(m_fRot + m_fAngle) * (dim);
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = (m_posPolygon.x) + sinf(m_fRot - (m_fAngle + 2.0f * (D3DX_PI * 0.5f - m_fAngle))) * (dim);
	pVtx[2].pos.y = (m_posPolygon.y) + cosf(m_fRot - (m_fAngle + 2.0f * (D3DX_PI * 0.5f - m_fAngle))) * (dim);
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = (m_posPolygon.x) + sinf(m_fRot - m_fAngle) * (dim);
	pVtx[3].pos.y = (m_posPolygon.y) + cosf(m_fRot - m_fAngle) * (dim);
	pVtx[3].pos.z = 0.0f;

	//公転角度の更新
	m_fRevolutionAngle += m_fRevolutionSpeed;

	//テクスチャ座標の更新処理
	UpdateTexture();

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	m_posPolygon += m_move;
	m_move += m_acc;

	//回転角度の更新
	m_fRot += m_fFrameRot;
	if (m_fRot >= D3DX_PI * 2.0f)
	{
		m_fRot -= D3DX_PI * 2.0f;
	}
}

//=============================================================================
// ポリゴンの描画
//=============================================================================
void CObject_2D::Draw()
{
	CRenderer* Render = CApplication::GetRenderer();							//レンディングインスタンスの取得処理
	LPDIRECT3DDEVICE9 pDevice = Render->GetDevice();							//デバイスの取得処理

	//頂点バッファをデータストリームに設定する
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTextureAll[m_textType]);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
//位置の設定処理
//=============================================================================
void CObject_2D::SetPos(const D3DXVECTOR3 pos)
{
	m_posPolygon = pos;
}

//ポリゴンの幅と高さの設定処理
void CObject_2D::SetSize(const D3DXVECTOR2 dim)
{
	m_dimension = dim;
	m_fAngle = atan2f(m_dimension.y, m_dimension.x);
}

//速度の取得処理
const D3DXVECTOR3 CObject_2D::GetMove(void)
{
	return m_move;
}

//速度の設定処理
void CObject_2D::SetMove(const D3DXVECTOR3 move)
{
	m_move = move;
}

//加速の取得処理
const D3DXVECTOR3 CObject_2D::GetAcceleration(void)
{
	return m_acc;
}

//加速の設定処理
void CObject_2D::SetAcceleration(const D3DXVECTOR3 acc)
{
	m_acc = acc;
}

//サイズの取得処理
const D3DXVECTOR2 CObject_2D::GetSize(void)
{
	return m_dimension;
}

//回転の設定処理
void CObject_2D::SetRotation(const float fFrameRot)
{
	m_fFrameRot = fFrameRot;
}

//回転速度の加算処理
void CObject_2D::AddAngularSpeed(const float fSpeed)
{
	m_fFrameRot += fSpeed;
}

//回転速度の取得処理
const float CObject_2D::GetAngularSpeed(void)
{
	return m_fFrameRot;
}

//回転角度の初期値の取得処理
void CObject_2D::SetStartingRot(const float fStartRot)
{
	m_fRot = fStartRot;
}

//回転角度の取得処理 
const float CObject_2D::GetRot(void)
{
	return m_fRot;
}

//公転の設定処理
void CObject_2D::SetRevolution(const D3DXVECTOR3 Center,
	const float fAngularSpeed, const float fRadius)
{
	m_revolutionCenter = Center;			//中心点の設定
	m_fRevolutionSpeed = fAngularSpeed;		//公転速度の設定
	m_fRevolutionRadius = fRadius;			//公転の半径の設定
}

//公転の中心点の設定処理
void CObject_2D::SetRevolutionCenter(const D3DXVECTOR3 Center)
{
	m_revolutionCenter = Center;
}

//現在の公転角度の設定処理
void CObject_2D::SetPresentRevolutionAngle(const float fAngle)
{
	m_fRevolutionAngle = fAngle;
}

//公転の中心点の取得処理
const D3DXVECTOR3 CObject_2D::GetRevolutionCenter(void)
{
	return m_revolutionCenter;
}

//公転速度の加算処理
void CObject_2D::AddRevolutionSpeed(const float fSpeed)
{
	m_fRevolutionSpeed += fSpeed;
}

//オブジェクトの位置取得処理
const D3DXVECTOR3 CObject_2D::GetPos(void)
{
	return m_posPolygon;
}

//テクスチャアニメーション用のパラメータ設定処理
void CObject_2D::SetTextureParameter(const int MaxPattern, const int LinePattern, const int ColumnPattern, const int nAnimFrame)
{
	m_nMaxTexColumn = ColumnPattern;				//行数の設定
	m_nTexLine = LinePattern;						//列数の設定
	m_nMaxTexPattern = MaxPattern;					//アニメーションパターンの最大数の設定
	m_nAnimFrame = nAnimFrame;						//アニメーションフレーム数の設定

	float fX = 1.0f / m_nTexLine;				
	float fY = 1.0f / m_nMaxTexColumn;

	VERTEX_2D* pVtx = nullptr;

	//頂点バッファのロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	UpdateTexture();

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//現在のアニメーションパターンの取得処理
const int CObject_2D::GetPresentAnimPattern(void)
{
	return m_nAnimPattern;				//アニメーションパターンを返す
}

//アニメションパターンの設定処理
void CObject_2D::SetAnimPattern(const int PatternNum)
{
	m_nAnimPattern = PatternNum;
}

void CObject_2D::MoveTexCoordinates(const D3DXVECTOR2 move)
{
	m_textureTranslation += move;
}

bool CObject_2D::GetFlipX(void)
{
	return m_bFlipX;
}

void CObject_2D::FlipX(void)
{
	m_bFlipX = !m_bFlipX;

	VERTEX_2D* pVtx = nullptr;
	VERTEX_2D Vtx;

	ZeroMemory(&Vtx, sizeof(VERTEX_2D));

	//頂点バッファのロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	Vtx.tex = pVtx[0].tex;
	pVtx[0].tex = pVtx[1].tex;
	pVtx[1].tex = Vtx.tex;
	Vtx.tex = pVtx[2].tex;
	pVtx[2].tex = pVtx[3].tex;
	pVtx[3].tex = Vtx.tex;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

void CObject_2D::FlipY(void)
{
	m_bFlipY = !m_bFlipY;

	VERTEX_2D* pVtx = nullptr;
	VERTEX_2D Vtx;

	ZeroMemory(&Vtx, sizeof(VERTEX_2D));

	//頂点バッファのロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	Vtx.tex = pVtx[0].tex;
	pVtx[0].tex = pVtx[2].tex;
	pVtx[2].tex = Vtx.tex;
	Vtx.tex = pVtx[1].tex;
	pVtx[1].tex = pVtx[3].tex;
	pVtx[3].tex = Vtx.tex;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//カーラーの取得処理
const D3DXCOLOR CObject_2D::GetColor(void)
{
	return m_col;
}

//カーラーの設定処理
void CObject_2D::SetColor(const D3DXCOLOR col)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxbuff();		//頂点バッファの取得処理
	VERTEX_2D* pVtx = nullptr;								//頂点情報へのポインタ

	m_col = col;											//カーラーの設定

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_VtxCol[nCnt] = col;
	}

															//頂点バッファのロック
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//カラーの設定
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//頂点バッファをアンロックする
	pVtxBuff->Unlock();
}

//頂点１つのカーラー設定処理
void CObject_2D::SetVtxColor(const int nVtxIdx, const D3DXCOLOR col)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxbuff();		//頂点バッファの取得処理
	VERTEX_2D* pVtx = nullptr;								//頂点情報へのポインタ

	m_VtxCol[nVtxIdx] = col;

	//頂点バッファのロック
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//カラーの設定
	pVtx[nVtxIdx].col = m_VtxCol[nVtxIdx];

	//頂点バッファをアンロックする
	pVtxBuff->Unlock();
}

//テクスチャの種類の設定処理
void CObject_2D::SetTexture(TextType textType)
{
	m_textType = textType;				//テクスチャの種類の設定
}

//頂点バッファの取得処理
LPDIRECT3DVERTEXBUFFER9 CObject_2D::GetVtxbuff(void)
{
	return m_pVtxBuff;
}

//テクスチャ全部のロード処理
void CObject_2D::LoadTextures(void)
{
	CRenderer* Render = CApplication::GetRenderer();			//レンディングインスタンスの取得処理
	LPDIRECT3DDEVICE9 pDevice = Render->GetDevice();			//デバイスの取得処理

	for (int nCnt = 0; nCnt < TextTypeMax; nCnt++)
	{
		if (m_pTextureAll[nCnt] != nullptr)
		{//ポインタのnullチェック
			m_pTextureAll[nCnt]->Release();
			m_pTextureAll[nCnt] = nullptr;
		}

		//テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			m_paTextPass[nCnt],
			&m_pTextureAll[nCnt]);
	}
}

//テクスチャ全部の破棄処理
void CObject_2D::DestroyLoadedTextures(void)
{
	for (int nCnt = 0; nCnt < TextTypeMax; nCnt++)
	{
		if (m_pTextureAll[nCnt] != nullptr)
		{
			m_pTextureAll[nCnt]->Release();
			m_pTextureAll[nCnt] = nullptr;
		}
	}
}

//生成処理
CObject_2D* CObject_2D::Create(void)
{
	CObject_2D* pObj2D = nullptr;			

	pObj2D = new CObject_2D;	//インスタンスを生成する

	if (FAILED(pObj2D->Init()))
	{//初期化処理
		return nullptr;
	}

	return pObj2D;				//インスタンスを返す
}

//テクスチャ座標の更新処理
void CObject_2D::UpdateTexture(void)
{
	VERTEX_2D* pVtx = nullptr;					//頂点情報へのポインタ

												//頂点バッファをロックする
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	float fX = 1.0f / m_nTexLine;
	float fY = 1.0f / m_nMaxTexColumn;

	//反転の状態によってテクスチャ座標を更新する
	if (!m_bFlipX && !m_bFlipY)
	{
		pVtx[0].tex = D3DXVECTOR2(m_textureTranslation.x + 0.0f + fX * (m_nAnimPattern % m_nTexLine), m_textureTranslation.y + 0.0f + fY * (m_nAnimPattern / m_nTexLine));
		pVtx[1].tex = D3DXVECTOR2(m_textureTranslation.x + fX + fX * (m_nAnimPattern % m_nTexLine), m_textureTranslation.y + 0.0f + fY * (m_nAnimPattern / m_nTexLine));
		pVtx[2].tex = D3DXVECTOR2(m_textureTranslation.x + 0.0f + fX * (m_nAnimPattern % m_nTexLine), m_textureTranslation.y + fY + fY * (m_nAnimPattern / m_nTexLine));
		pVtx[3].tex = D3DXVECTOR2(m_textureTranslation.x + fX + fX * (m_nAnimPattern % m_nTexLine), m_textureTranslation.y + fY + fY * (m_nAnimPattern / m_nTexLine));
	}
	else if(m_bFlipX && !m_bFlipY)
	{
		pVtx[1].tex = D3DXVECTOR2(m_textureTranslation.x + 0.0f + fX * (m_nAnimPattern % m_nTexLine), m_textureTranslation.y + 0.0f + fY * (m_nAnimPattern / m_nTexLine));
		pVtx[0].tex = D3DXVECTOR2(m_textureTranslation.x + fX + fX * (m_nAnimPattern % m_nTexLine), m_textureTranslation.y + 0.0f + fY * (m_nAnimPattern / m_nTexLine));
		pVtx[3].tex = D3DXVECTOR2(m_textureTranslation.x + 0.0f + fX * (m_nAnimPattern % m_nTexLine), m_textureTranslation.y + fY + fY * (m_nAnimPattern / m_nTexLine));
		pVtx[2].tex = D3DXVECTOR2(m_textureTranslation.x + fX + fX * (m_nAnimPattern % m_nTexLine), m_textureTranslation.y + fY + fY * (m_nAnimPattern / m_nTexLine));
	}
	else if (!m_bFlipX && m_bFlipY)
	{
		pVtx[2].tex = D3DXVECTOR2(m_textureTranslation.x + 0.0f + fX * (m_nAnimPattern % m_nTexLine), m_textureTranslation.y + 0.0f + fY * (m_nAnimPattern / m_nTexLine));
		pVtx[3].tex = D3DXVECTOR2(m_textureTranslation.x + fX + fX * (m_nAnimPattern % m_nTexLine), m_textureTranslation.y + 0.0f + fY * (m_nAnimPattern / m_nTexLine));
		pVtx[0].tex = D3DXVECTOR2(m_textureTranslation.x + 0.0f + fX * (m_nAnimPattern % m_nTexLine), m_textureTranslation.y + fY + fY * (m_nAnimPattern / m_nTexLine));
		pVtx[1].tex = D3DXVECTOR2(m_textureTranslation.x + fX + fX * (m_nAnimPattern % m_nTexLine), m_textureTranslation.y + fY + fY * (m_nAnimPattern / m_nTexLine));
	}
	else
	{
		pVtx[3].tex = D3DXVECTOR2(m_textureTranslation.x + 0.0f + fX * (m_nAnimPattern % m_nTexLine), m_textureTranslation.y + 0.0f + fY * (m_nAnimPattern / m_nTexLine));
		pVtx[2].tex = D3DXVECTOR2(m_textureTranslation.x + fX + fX * (m_nAnimPattern % m_nTexLine), m_textureTranslation.y + 0.0f + fY * (m_nAnimPattern / m_nTexLine));
		pVtx[1].tex = D3DXVECTOR2(m_textureTranslation.x + 0.0f + fX * (m_nAnimPattern % m_nTexLine), m_textureTranslation.y + fY + fY * (m_nAnimPattern / m_nTexLine));
		pVtx[0].tex = D3DXVECTOR2(m_textureTranslation.x + fX + fX * (m_nAnimPattern % m_nTexLine), m_textureTranslation.y + fY + fY * (m_nAnimPattern / m_nTexLine));
	}
	
	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}