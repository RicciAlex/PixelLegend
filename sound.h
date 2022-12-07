//=============================================================================
//
// sound.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef SOUND_H
#define SOUND_H

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"
#include "xaudio2.h"					// 音楽処理に必要

class CSound
{
public:

	enum SOUND_LABEL
	{
		SOUND_LABEL_BGM_GAME = 0,
		SOUND_LABEL_BGM_RESULTS,
		SOUND_LABEL_BGM_STAGE_SELECTION,	
		SOUND_LABEL_BGM_THANATOS,			
		SOUND_LABEL_BGM_TITLE,				
		SOUND_LABEL_BGM_WAVES,

		SOUND_LABEL_SE_BALLOON_POP,
		SOUND_LABEL_SE_BEAM_CHARGE,
		SOUND_LABEL_SE_BIG_EXPLOSION,		
		SOUND_LABEL_SE_BITE,
		SOUND_LABEL_SE_CANNON,
		SOUND_LABEL_SE_CLICK,
		SOUND_LABEL_SE_COIN,
		SOUND_LABEL_SE_EXPLOSION,			
		SOUND_LABEL_SE_FIRE,
		SOUND_LABEL_SE_GLUTTONY_ROAR,
		SOUND_LABEL_SE_GOAT,
		SOUND_LABEL_SE_HAND_HIT,
		SOUND_LABEL_SE_HAND_WOOSH,
		SOUND_LABEL_SE_LAUGH,
		SOUND_LABEL_SE_ROAR,
		SOUND_LABEL_SE_ROCKET_START,
		SOUND_LABEL_SE_SCYTHE,
		SOUND_LABEL_SE_SHOT,				
		SOUND_LABEL_SE_STAR_BULLET,
		SOUND_LABEL_SE_THUNDER,	
		SOUND_LABEL_SE_WRATH_DEATH,
		SOUND_LABEL_MAX
	};

	CSound();							//コンストラクタ
	~CSound();							//デストラクタ

	HRESULT Init(HWND hWnd);			//初期化処理
	void Uninit(void);					//終了処理
	HRESULT Play(SOUND_LABEL label);	//再生処理
	void Stop(SOUND_LABEL label);		//停止処理
	void Stop(void);					//停止処理

	static CSound* Create(HWND hWnd);	//生成処理

private:

	typedef struct
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウント
	} SOUNDPARAM;


	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);


	static SOUNDPARAM g_aParam[SOUND_LABEL_MAX];

	IXAudio2 *g_pXAudio2 = nullptr;								// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *g_pMasteringVoice = nullptr;		// マスターボイス
	IXAudio2SourceVoice *g_apSourceVoice[SOUND_LABEL_MAX] = {};	// ソースボイス
	BYTE *g_apDataAudio[SOUND_LABEL_MAX] = {};					// オーディオデータ
	DWORD g_aSizeAudio[SOUND_LABEL_MAX] = {};					// オーディオデータサイズ

};

#endif