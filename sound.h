//=============================================================================
//
// sound.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef SOUND_H
#define SOUND_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "xaudio2.h"					// ���y�����ɕK�v

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

	CSound();							//�R���X�g���N�^
	~CSound();							//�f�X�g���N�^

	HRESULT Init(HWND hWnd);			//����������
	void Uninit(void);					//�I������
	HRESULT Play(SOUND_LABEL label);	//�Đ�����
	void Stop(SOUND_LABEL label);		//��~����
	void Stop(void);					//��~����

	static CSound* Create(HWND hWnd);	//��������

private:

	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} SOUNDPARAM;


	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);


	static SOUNDPARAM g_aParam[SOUND_LABEL_MAX];

	IXAudio2 *g_pXAudio2 = nullptr;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *g_pMasteringVoice = nullptr;		// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *g_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X
	BYTE *g_apDataAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^
	DWORD g_aSizeAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y

};

#endif