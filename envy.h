//=============================================================================
//
// envy.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef ENVY_H
#define ENVY_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "enemy.h"

//=============================================================================
//�O���錾
//=============================================================================
class CSquareHitbox;
class CEnemyLife;


class CEnvy : public CEnemy
{
public:

	enum state
	{
		state_spawn = 0,
		state_normal,
		state_hide,
		state_strike,
		state_death,
		state_max
	};

	CEnvy();
	~CEnvy() override;								//�f�X�g���N�^

	HRESULT Init(void) override;				//����������
	void Uninit(void) override;					//�I������
	void Update(void) override;					//�X�V����
	void Draw(void) override;					//�`�揈��

	const bool GetEnd(void);

	static CEnvy* Create(void);								//��������

private:

	void UpdateState(void);
	void UpdatePointers(void);

	static const int nGearNum = 6;
	static const int nPipeNum = 2;

	void CreateGears(void);

	D3DXVECTOR3 m_gearRelativePos[nGearNum];
	D3DXVECTOR3 m_hatRelativePos;
	D3DXVECTOR3 m_pipeRelativePos[nPipeNum];
	D3DXVECTOR3 m_cannonRelativePos;

	int m_nCntState;
	state m_state;
	bool m_bEnd;

	CObject_2D* m_pGear[nGearNum];
	CObject_2D* m_pHat;
	CObject_2D* m_pPipe[nPipeNum];
	CObject_2D* m_pCannon;
	CSquareHitbox* m_pHitbox;
	CSquareHitbox* m_pHatHitbox;
	CEnemyLife* m_pLife;
};


#endif