//=============================================================================
//
// object.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef OBJECT_H
#define OBJECT_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
class CPlayer;

//=============================================================================
// �I�u�W�F�N�g�N���X
//=============================================================================
class CObject
{
public:

	// ���_�f�[�^
	struct VERTEX_2D
	{
		D3DXVECTOR3 pos;			//xyz���W
		float rhw;					//rhw
		D3DCOLOR col;				//�J�[���[
		D3DXVECTOR2 tex;			//�e�N�X�`�����W
	};

	//�I�u�W�F�N�g�̎��
	enum EObjType
	{
		OBJECT2D = 0,						//2D�|���S��
		OBJTYPE_PLAYER,						//�v���C���[
		OBJTYPE_BULLET,						//�e
		OBJTYPE_EXPLOSION,					//����
		OBJTYPE_ENEMY,						//�G
		OBJTYPE_EFFECT,						//�G�t�F�N�g
		OBJTYPE_LETTER,						//����
		OBJTYPE_MENU,						
		OBJECT_MAX
	};

	//�e�N�X�`���̎��
	enum TextType
	{
		TextureBalloon = 0,
		TextureBalloonEnemy,
		TextureBlackHole,
		TextureBone,
		TextureBubbleBat,

		TextureCandle,
		TextureClock,
		TextureClockNeedle,
		TextureCloud,
		TextureCoin,

		TextureDifficultyIcon,
		TextureDifficultyLogo,
		TextureDragon,

		TextureExplosion,
		TextureEnvyBg,

		TextureFace,
		TextureFireball,

		TextureGear,
		TextureGluttonyBackMaw,
		TextureGluttonyBg,
		TextureGluttonyHeart,
		TextureGluttonyMaw,
		TextureGluttonyMinion,
		TextureGreed,
		TextureGreedBg,

		TextureHand,
		TextureHandBlade,
		TextureHandFireball,

		TextureIconA,
		TextureIconD,
		TextureIconMouse,
		TextureIconS,
		TextureIconW,

		TextureJewel,

		TextureLateralEIcon,
		TextureLateralQIcon,
		TextureLaugh,
		TextureLetters,
		TextureLifeIcon,

		TextureMenuBg,
		TextureMissile,

		TextureNormalEffect,
		TextureNull,
		TextureNumbers,

		TexturePipe,
		TexturePressSpaceIcon,
		TexturePride,
		TexturePrideBg,

		TextureRoundEffect,

		TextureScyllaBody,		
		TextureScythe,			
		TextureSeaBG,			
		TextureSkull,			
		TextureSkullFireball,	
		TextureSkullShield,		
		TextureSloth,
		TextureSlothBg,
		TextureSpike,			
		TextureSpikeBomb,		
		TextureSpringAndScrew,

		TextureTarget,
		TextureTeardrop,  	
		TextureThanatos,	
		TextureThanatosBG,	
		TextureThunder,		
		TextureTopHat,	

		TextureVertebra,

		TextureWing,
		TextureWrath,
		TextureWrathArm,
		TextureWrathBg,
		TextureWrathBody,	

		TextTypeMax
	};

	//�G�̎��
	enum EnemyType
	{
		ENEMYTYPE_CLOCK = 0,
		ENEMYTYPE_CLOUD,
		ENEMYTYPE_BOUND_CLOCK,
		ENEMYTYPE_WRATH_ARM,
		ENEMYTYPE_WRATH_BODY,
		ENEMYTYPE_VERTEBRA,
		ENEMYTYPE_SKULL,
		ENEMYTYPE_SCYLLA_BODY,
		ENEMYTYPE_MAX
	};

	static const int MaxObject = 2048;					//�I�u�W�F�N�g�̍ő吔

	CObject();											//�R���X�g���N�^
	virtual~CObject();									//�f�X�g���N�^
														
	virtual HRESULT Init(void) = 0;						//����������
	virtual void Uninit(void) = 0;						//�I������
	virtual void Update(void) = 0;						//�X�V����
	virtual void Draw(void) = 0;						//�`�揈��
														
	virtual void SetPos(const D3DXVECTOR3 pos) = 0;		//�ʒu�̐ݒ菈��
	
	void Release(void);									//�C���X�^���X��̏I������
	const EObjType GetObjType(void);					//��ނ̎擾����
	void SetObjType(const EObjType type);
	virtual const D3DXVECTOR2 GetSize(void) = 0;		//�T�C�Y�̎擾����
	virtual const D3DXVECTOR3 GetPos(void) = 0;			//�ʒu�̎擾����
	void SetPriority(int nPriority);					//�v���C�I���e�B�̐ݒ菈��
														
	//�ÓI�֐�
	static void ReleaseAll(void);						//�S���̏I������
	static void UpdateAll(void);						//�S���̍X�V����
	static void DrawAll(void);							//�S���̕`�揈��
	//static CPlayer* GetPlayer(void);					//�v���C���[���̎擾����
	static CObject** GetObj(void);						//�I�u�W�F�N�g�̎擾����
	static void SavePlayerIdx(CPlayer* ptr);			//
	static void SetPause(const bool bPause);			//�|�[�Y�̐ݒ菈��

	//�����蔻��֐�
	static bool CircleHit(D3DXVECTOR3* pos1, 
		D3DXVECTOR3* pos2, float fRadius1, float fRadius2);
	static bool CircleHit(D3DXVECTOR3* pos1,
		D3DXVECTOR3* pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2);
	static bool HitBox(D3DXVECTOR3* pos1,
		D3DXVECTOR3* pos2, D3DXVECTOR2 size1, D3DXVECTOR2 size2);

	static D3DXVECTOR3 GetPerpendicularVersor(D3DXVECTOR3 V);			//�����x�N�g����Ԃ�
	static int random(const int low, const int high);					//������Ԃ�
														
private:								

	static const int Max_Priority = 5;					//�ő�v���C�I���e�B

	static int m_nNumAll;								//���݂���|���S����
	static CObject* m_pObject[MaxObject];				//�I�u�W�F�N�g�ւ̃|���^
	static int m_nPriorityObjNum[Max_Priority];			//���݂��Ă���v���C�I���e�B�̃I�u�W�F�N�g��
	static int m_PlayerIdx;								//�v���C���[�̃C���f�b�N�X
	static bool m_bPause;								//�|�[�Y���ł��邩�ǂ���
	int m_nIdx;											//���̃C���X�^���X�̔z��̃C���f�b�N�X
	int m_nPriority;									//�`�揇
	EObjType m_type;									//���
};



#endif