//=============================================================================
//
// Thanatos.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef THANATOS_H
#define THANATOS_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "enemy.h"

//=============================================================================
//�O���錾
//=============================================================================
class CSquareHitbox;
class CCandle;
class CBg;
class CEnemyLife;

class CThanatos : public CEnemy
{
public:

	enum state
	{
		state_Spawn = 0,
		state_Normal,
		state_Hide,
		state_ShowEyes,
		state_Hidden,
		state_Vulnerable,
		state_Death,
		state_Max
	};

	CThanatos();									//�R���X�g���N�^
	~CThanatos() override;							//�f�X�g���N�^

	virtual HRESULT Init(void) override;			//����������
	virtual void Uninit(void) override;				//�I������
	virtual void Update(void) override;				//�X�V����
	virtual void Draw(void) override;				//�`�揈��

	const bool GetEnd(void);

	void SetBgPointer(CBg* pPointer);
	void AddLitCandle(void);

	static CThanatos* Create(void);

private:

	const static int Max_Candle = 4;

	bool m_bEnd;
	int m_nTargetLife;
	int m_nLitCandle;
	int m_nCntState;
	state m_state;

	CBg* m_pBg;
	CCandle* m_pCandle[Max_Candle];
	CEnemyLife* m_pLife;

	CSquareHitbox* m_pHitbox;
};




#endif