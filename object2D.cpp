//=============================================================================
//
// object2D.h
// Author : Ricci Alex
//
//=============================================================================

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "object2D.h"
#include "rendering.h"
#include "application.h"
#include "inputKeyboard.h"

//�ÓI�����o�[�ϐ��̐錾
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
//�R���X�g���N�^
//=============================================================================
CObject_2D::CObject_2D()
{
	m_pVtxBuff = nullptr;								//���_�o�b�t�@
	m_dimension = D3DXVECTOR2(0.0f, 0.0f);				//�|���S���̕��ƍ���
	m_dir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�|���S���̌���
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�ړ���
	m_acc = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//����
	m_fRot = 0.0f;										//�|���S���̉�]�p�x
	m_fAngle = 0.0f;									//�|���S���̉�]�p�̊p�x
	m_fFrameRot = 0.0f;									//1�t���[���̉�]�p�x
	m_revolutionCenter = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//���]�̒��S�_
	m_fRevolutionSpeed = 0.0f;							//���]�̃X�s�[�h
	m_fRevolutionAngle = 0.0f;							//���]�̌��݊p�x
	m_fRevolutionRadius = 0.0f;							//���]�̔��a
	m_posPolygon = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�|���S���̈ʒu
	m_nCountAnim = 0;									//���݂̃e�N�X�`���p�^�[��
	m_nAnimPattern = 0;									//�A�j���[�V�����J�E���^�[
	m_nMaxTexPattern = 0;								//�e�N�X�`���̃p�^�[����
	m_nMaxTexColumn = 0;								//�e�N�X�`���̍s��
	m_nTexLine = 0;										//�e�N�X�`���̗�
	m_nAnimFrame = 0;									//�A�j���[�V�����p�^�[���̕ύX�t���[����
	m_textureTranslation = D3DXVECTOR2(0.0f, 0.0f);
	m_bFlipX = false;
	m_bFlipY = false;
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_textType = CObject::TextTypeMax;					//�e�N�X�`���̎��

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_VtxCol[nCnt] = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	}
}														  

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CObject_2D::~CObject_2D()
{

}

//=============================================================================
// �|���S���̏�����
//=============================================================================
HRESULT CObject_2D::Init(void)
{
	CRenderer* Render = CApplication::GetRenderer();			//�����f�B���O�C���X�^���X�̎擾����
	LPDIRECT3DDEVICE9 pDevice = Render->GetDevice();			//�f�o�C�X�̎擾����

	m_dimension = D3DXVECTOR2(0.0f, 0.0f);						//�|���S���̕��ƍ����̐ݒ�
	m_dir = D3DXVECTOR3(1.0f, 0.0f, 0.0f);						//�|���S���̌���
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						//�ړ���
	m_acc = D3DXVECTOR3(0.0f, 0.0f, 0.0f);						//����
	m_fRot = 0.0f;												//��]�p�x�̐ݒ�
	m_fAngle = 0.0f;											//��]�p�̊p�x���v�Z����
	m_fFrameRot = 0.0f;											//1�t���[���̉�]�p�x
	m_revolutionCenter = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//���]�̒��S�_
	m_fRevolutionSpeed = 0.0f;									//���]�̃X�s�[�h
	m_fRevolutionAngle = 0.0f;									//���]�̌��݊p�x
	m_fRevolutionRadius = 0.0f;									//���]�̔��a
	m_posPolygon = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				//�ʒu�̐ݒ�
	m_nCountAnim = 0;											//���݂̃e�N�X�`���p�^�[��
	m_nAnimPattern = 0;											//�A�j���[�V�����J�E���^�[
	m_nMaxTexPattern = 1;										//�e�N�X�`���̃p�^�[����
	m_nMaxTexColumn = 1;										//�e�N�X�`���̍s��
	m_nTexLine = 1;												//�e�N�X�`���̗�
	m_textureTranslation = D3DXVECTOR2(0.0f, 0.0f);
	m_bFlipX = false;
	m_bFlipY = false;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_nAnimFrame = 0;											//�A�j���[�V�����p�^�[���̕ύX�t���[����

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_VtxCol[nCnt] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D* pVtx = nullptr;					//���_���ւ̃|�C���^

	//���_�o�b�t�@�̃��b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_����ݒ�

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
		// rhw�̐ݒ�
		pVtx[nCnt].rhw = 1.0f;
		// ���_�J���[�̐ݒ�
		pVtx[nCnt].col = m_col;
	}

	SetTexture(TextureNull);
	SetTextureParameter(1, 1, 1, INT_MAX);

	//�J���[�̐ݒ�
	/*pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);*/

	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[1].tex = D3DXVECTOR2(0.25f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	//pVtx[3].tex = D3DXVECTOR2(0.25f, 0.5f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �|���S���̏I��
//=============================================================================
void CObject_2D::Uninit()
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//=============================================================================
// �|���S���̍X�V
//=============================================================================
void CObject_2D::Update()
{
	VERTEX_2D* pVtx = nullptr;					//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N����
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	m_nCountAnim++;								//�A�j���[�V�����J�E���^�[�̍X�V

	if (m_nCountAnim >= m_nAnimFrame)
	{
		m_nCountAnim = 0;						//�A�j���[�V�����J�E���^�[��0�ɖ߂�
		m_nAnimPattern++;						//�A�j���[�V�����p�^�[���̍X�V

		if (m_nAnimPattern >= m_nMaxTexPattern)
		{//�A�j���[�V�����̍Ō�̃p�^�[���𒴂����ꍇ
			m_nAnimPattern = 0;					//�A�j���[�V�����p�^�[����0�ɖ߂�
		}
	}

	if (m_fRevolutionRadius != 0.0f)
	{
		m_revolutionCenter += GetMove();

		m_posPolygon.x = m_revolutionCenter.x + (cosf(m_fRevolutionAngle) * (m_fRevolutionRadius));
		m_posPolygon.y = m_revolutionCenter.y + (sinf(m_fRevolutionAngle) * (m_fRevolutionRadius));
	}

	float dim = sqrtf((m_dimension.x * m_dimension.x) + (m_dimension.y * m_dimension.y));

	//���_���W�̍X�V
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

	m_fRevolutionAngle += m_fRevolutionSpeed;

	UpdateTexture();

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	m_posPolygon += m_move;
	m_move += m_acc;

	//��]�p�x�̍X�V
	m_fRot += m_fFrameRot;
	if (m_fRot >= D3DX_PI * 2.0f)
	{
		m_fRot -= D3DX_PI * 2.0f;
	}
}

//=============================================================================
// �|���S���̕`��
//=============================================================================
void CObject_2D::Draw()
{
	CRenderer* Render = CApplication::GetRenderer();							//�����f�B���O�C���X�^���X�̎擾����
	LPDIRECT3DDEVICE9 pDevice = Render->GetDevice();							//�f�o�C�X�̎擾����

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ肷��
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTextureAll[m_textType]);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
//�ʒu�̐ݒ菈��
//=============================================================================
void CObject_2D::SetPos(const D3DXVECTOR3 pos)
{
	m_posPolygon = pos;
}

//�|���S���̕��ƍ����̐ݒ菈��
void CObject_2D::SetSize(const D3DXVECTOR2 dim)
{
	m_dimension = dim;
	m_fAngle = atan2f(m_dimension.y, m_dimension.x);
}

//���x�̎擾����
const D3DXVECTOR3 CObject_2D::GetMove(void)
{
	return m_move;
}

//���x�̐ݒ菈��
void CObject_2D::SetMove(const D3DXVECTOR3 move)
{
	m_move = move;
}

//�����̎擾����
const D3DXVECTOR3 CObject_2D::GetAcceleration(void)
{
	return m_acc;
}

//�����̐ݒ菈��
void CObject_2D::SetAcceleration(const D3DXVECTOR3 acc)
{
	m_acc = acc;
}

//�T�C�Y�̎擾����
const D3DXVECTOR2 CObject_2D::GetSize(void)
{
	return m_dimension;
}

//��]�̐ݒ菈��
void CObject_2D::SetRotation(const float fFrameRot)
{
	m_fFrameRot = fFrameRot;
}

//��]���x�̉��Z����
void CObject_2D::AddAngularSpeed(const float fSpeed)
{
	m_fFrameRot += fSpeed;
}

//��]���x�̎擾����
const float CObject_2D::GetAngularSpeed(void)
{
	return m_fFrameRot;
}

//��]�p�x�̏����l�̎擾����
void CObject_2D::SetStartingRot(const float fStartRot)
{
	m_fRot = fStartRot;
}

//��]�p�x�̎擾���� 
const float CObject_2D::GetRot(void)
{
	return m_fRot;
}

//���]�̐ݒ菈��
void CObject_2D::SetRevolution(const D3DXVECTOR3 Center,
	const float fAngularSpeed, const float fRadius)
{
	m_revolutionCenter = Center;
	m_fRevolutionSpeed = fAngularSpeed;
	m_fRevolutionRadius = fRadius;
}

//���]�̒��S�_�̐ݒ菈��
void CObject_2D::SetRevolutionCenter(const D3DXVECTOR3 Center)
{
	m_revolutionCenter = Center;
}

void CObject_2D::SetPresentRevolutionAngle(const float fAngle)
{
	m_fRevolutionAngle = fAngle;
}

//���]�̒��S�_�̎擾����
const D3DXVECTOR3 CObject_2D::GetRevolutionCenter(void)
{
	return m_revolutionCenter;
}

void CObject_2D::AddRevolutionSpeed(const float fSpeed)
{
	m_fRevolutionSpeed += fSpeed;
}

//�I�u�W�F�N�g�̈ʒu�擾����
const D3DXVECTOR3 CObject_2D::GetPos(void)
{
	return m_posPolygon;
}

//�e�N�X�`���A�j���[�V�����p�̃p�����[�^�ݒ菈��
void CObject_2D::SetTextureParameter(const int MaxPattern, const int LinePattern, const int ColumnPattern, const int nAnimFrame)
{
	m_nMaxTexColumn = ColumnPattern;				//�s���̐ݒ�
	m_nTexLine = LinePattern;						//�񐔂̐ݒ�
	m_nMaxTexPattern = MaxPattern;					//�A�j���[�V�����p�^�[���̍ő吔�̐ݒ�
	m_nAnimFrame = nAnimFrame;						//�A�j���[�V�����t���[�����̐ݒ�

	float fX = 1.0f / m_nTexLine;				
	float fY = 1.0f / m_nMaxTexColumn;

	VERTEX_2D* pVtx = nullptr;

	//���_�o�b�t�@�̃��b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	UpdateTexture();

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//���݂̃A�j���[�V�����p�^�[���̎擾����
const int CObject_2D::GetPresentAnimPattern(void)
{
	return m_nAnimPattern;				//�A�j���[�V�����p�^�[����Ԃ�
}

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

	//���_�o�b�t�@�̃��b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	Vtx.tex = pVtx[0].tex;
	pVtx[0].tex = pVtx[1].tex;
	pVtx[1].tex = Vtx.tex;
	Vtx.tex = pVtx[2].tex;
	pVtx[2].tex = pVtx[3].tex;
	pVtx[3].tex = Vtx.tex;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

void CObject_2D::FlipY(void)
{
	m_bFlipY = !m_bFlipY;

	VERTEX_2D* pVtx = nullptr;
	VERTEX_2D Vtx;

	ZeroMemory(&Vtx, sizeof(VERTEX_2D));

	//���_�o�b�t�@�̃��b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	Vtx.tex = pVtx[0].tex;
	pVtx[0].tex = pVtx[2].tex;
	pVtx[2].tex = Vtx.tex;
	Vtx.tex = pVtx[1].tex;
	pVtx[1].tex = pVtx[3].tex;
	pVtx[3].tex = Vtx.tex;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//�J�[���[�̎擾����
const D3DXCOLOR CObject_2D::GetColor(void)
{
	return m_col;
}

//�J�[���[�̐ݒ菈��
void CObject_2D::SetColor(const D3DXCOLOR col)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxbuff();		//���_�o�b�t�@�̎擾����
	VERTEX_2D* pVtx = nullptr;								//���_���ւ̃|�C���^

	m_col = col;											//�J�[���[�̐ݒ�

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_VtxCol[nCnt] = col;
	}

															//���_�o�b�t�@�̃��b�N
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}

//���_�P�̃J�[���[�ݒ菈��
void CObject_2D::SetVtxColor(const int nVtxIdx, const D3DXCOLOR col)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxbuff();		//���_�o�b�t�@�̎擾����
	VERTEX_2D* pVtx = nullptr;								//���_���ւ̃|�C���^

	m_VtxCol[nVtxIdx] = col;

	//���_�o�b�t�@�̃��b�N
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�J���[�̐ݒ�
	pVtx[nVtxIdx].col = m_VtxCol[nVtxIdx];

	//���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}

//�e�N�X�`���̎�ނ̐ݒ菈��
void CObject_2D::SetTexture(TextType textType)
{
	m_textType = textType;				//�e�N�X�`���̎�ނ̐ݒ�
}

//���_�o�b�t�@�̎擾����
LPDIRECT3DVERTEXBUFFER9 CObject_2D::GetVtxbuff(void)
{
	return m_pVtxBuff;
}

//�e�N�X�`���S���̃��[�h����
void CObject_2D::LoadTextures(void)
{
	CRenderer* Render = CApplication::GetRenderer();			//�����f�B���O�C���X�^���X�̎擾����
	LPDIRECT3DDEVICE9 pDevice = Render->GetDevice();			//�f�o�C�X�̎擾����

	for (int nCnt = 0; nCnt < TextTypeMax; nCnt++)
	{
		if (m_pTextureAll[nCnt] != nullptr)
		{//�|�C���^��null�`�F�b�N
			m_pTextureAll[nCnt]->Release();
			m_pTextureAll[nCnt] = nullptr;
		}

		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			m_paTextPass[nCnt],
			&m_pTextureAll[nCnt]);

		//��ނɂ���ăe�N�X�`���𐶐�����
		/*switch (nCnt)
		{
		case TextureFireball:

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				"data\\TEXTURE\\Bullet\\Fireball_Sprite.png",
				&m_pTextureAll[nCnt]);

			break;

		case TextureThunder:

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				"data\\TEXTURE\\Bullet\\Thunder.png",
				&m_pTextureAll[nCnt]);

			break;

		case TextureExplosion:

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				"data\\TEXTURE\\Explosion.png",
				&m_pTextureAll[nCnt]);

			break;

		case TextureWing:

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				"data\\TEXTURE\\Wing.png",
				&m_pTextureAll[nCnt]);

			break;

		case TextureClock:

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				"data\\TEXTURE\\Clock.png",
				&m_pTextureAll[nCnt]);

			break;

		case TextureCloud:

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				"data\\TEXTURE\\Cloud.png",
				&m_pTextureAll[nCnt]);

			break;

		case TextureBlackHole:

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				"data\\TEXTURE\\Bullet\\BlackHole.png",
				&m_pTextureAll[nCnt]);

			break;

		case TextureClockNeedle:

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				"data\\TEXTURE\\Bullet\\ClockNeedle.png",
				&m_pTextureAll[nCnt]);

			break;

		case TextureWrathArm:

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				"data\\TEXTURE\\WrathArm.png",
				&m_pTextureAll[nCnt]);

			break;

		case TextureWrathBody:

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				"data\\TEXTURE\\WrathBody.png",
				&m_pTextureAll[nCnt]);

			break;

		case TextureVertebra:

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				"data\\TEXTURE\\Enemy\\Scylla\\Vertebra.png",
				&m_pTextureAll[nCnt]);

			break;

		case TextureSkull:

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				"data\\TEXTURE\\Enemy\\Scylla\\WivernSkull_Sprite.png",
				&m_pTextureAll[nCnt]);

			break;

		case TextureScyllaBody:

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				"data\\TEXTURE\\Enemy\\Scylla\\ScyllaBody.png",
				&m_pTextureAll[nCnt]);

			break;

		case TextureNormalEffect:

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				"data\\TEXTURE\\Effect\\effect105.png",
				&m_pTextureAll[nCnt]);

			break;

		case TextureSkullFireball:

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				"data\\TEXTURE\\SkullFireball.png",
				&m_pTextureAll[nCnt]);

			break;

		case TextureLetters:

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				"data\\TEXTURE\\Alphabet.png",
				&m_pTextureAll[nCnt]);

			break;

		case TextureSeaBG:

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				"data\\TEXTURE\\BG\\Sea.png",
				&m_pTextureAll[nCnt]);

			break;

		case TextureThanatosBG:

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				"data\\TEXTURE\\BG\\ThanatosBg.png",
				&m_pTextureAll[nCnt]);

			break;

		case TextureRoundEffect:

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				"data\\TEXTURE\\Effect\\tex_eff_light02.png",
				&m_pTextureAll[nCnt]);

			break;

		case TextureTeardrop:

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				"data\\TEXTURE\\Bullet\\Tear.png",
				&m_pTextureAll[nCnt]);

			break;

		case TextureSloth:

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				"data\\TEXTURE\\Enemy\\SlothSprite.png",
				&m_pTextureAll[nCnt]);

			break;

		case TexturePride:

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				"data\\TEXTURE\\Enemy\\PrideSprite.png",
				&m_pTextureAll[nCnt]);

			break;

		case TextureBalloon:

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				"data\\TEXTURE\\Balloon.png",
				&m_pTextureAll[nCnt]);

			break;

		case TextureLaugh:

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				"data\\TEXTURE\\Bullet\\Laugh.png",
				&m_pTextureAll[nCnt]);

			break;

		case TextureBalloonEnemy:

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				"data\\TEXTURE\\Enemy\\BalloonEnemy.png",
				&m_pTextureAll[nCnt]);

			break;

		case TextureCandle:

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				"data\\TEXTURE\\Candle.png",
				&m_pTextureAll[nCnt]);

			break;

		case TextureSkullShield:

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				"data\\TEXTURE\\Enemy\\SkullShield.png",
				&m_pTextureAll[nCnt]);

			break;

		case TextureThanatos:

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				"data\\TEXTURE\\Enemy\\Thanatos.png",
				&m_pTextureAll[nCnt]);

			break;

		case TextureScythe:

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				"data\\TEXTURE\\Bullet\\Scythe.png",
				&m_pTextureAll[nCnt]);

			break;

		case TextureGear:

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				"data\\TEXTURE\\Enemy\\Envy\\Gear_Sprite.png",
				&m_pTextureAll[nCnt]);

			break;

		case TextureFace:

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				"data\\TEXTURE\\Enemy\\Envy\\Face.png",
				&m_pTextureAll[nCnt]);

			break;

		case TexturePipe:

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				"data\\TEXTURE\\Enemy\\Envy\\Pipe.png",
				&m_pTextureAll[nCnt]);

			break;

		case TextureTopHat:

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				"data\\TEXTURE\\Enemy\\Envy\\TopHat.png",
				&m_pTextureAll[nCnt]);

			break;

		case TextureMissile:

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				"data\\TEXTURE\\Bullet\\Missile.png",
				&m_pTextureAll[nCnt]);

			break;

		case TextureSpikeBomb:

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				"data\\TEXTURE\\Bullet\\SpikeBomb.png",
				&m_pTextureAll[nCnt]);

			break;

		case TextureSpike:

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				"data\\TEXTURE\\Bullet\\Spike.png",
				&m_pTextureAll[nCnt]);

			break;

		case TextureSpringAndScrew:

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				"data\\TEXTURE\\Bullet\\SpringAndScrew.png",
				&m_pTextureAll[nCnt]);

			break;

		case TextureLifeIcon:

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				"data\\TEXTURE\\LifeIcon.png",
				&m_pTextureAll[nCnt]);

			break;

		case TextureDragon:

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				"data\\TEXTURE\\Player.png",
				&m_pTextureAll[nCnt]);

			break;

		case TextureGreed:

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				"data\\TEXTURE\\Enemy\\Greed\\Greed.png",
				&m_pTextureAll[nCnt]);

			break;

		case TextureMoneyVolcano:

			//�e�N�X�`���̓ǂݍ���
			D3DXCreateTextureFromFile(pDevice,
				"data\\TEXTURE\\Enemy\\Greed\\MoneyVolcano.png",
				&m_pTextureAll[nCnt]);

			break;

		default:
			break;
		}*/
	}
}

//�e�N�X�`���S���̔j������
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

//��������
CObject_2D* CObject_2D::Create(void)
{
	CObject_2D* pObj2D = nullptr;

	pObj2D = new CObject_2D;

	if (FAILED(pObj2D->Init()))
	{
		if (pObj2D != nullptr)
		{
			delete pObj2D;
			pObj2D = nullptr;
		}

		return nullptr;
	}

	return pObj2D;
}


void CObject_2D::UpdateTexture(void)
{
	VERTEX_2D* pVtx = nullptr;					//���_���ւ̃|�C���^

												//���_�o�b�t�@�����b�N����
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	float fX = 1.0f / m_nTexLine;
	float fY = 1.0f / m_nMaxTexColumn;

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
	
	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}