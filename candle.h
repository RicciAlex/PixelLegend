//=============================================================================
//
// candle.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef CANDLE_H
#define CANDLE_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "enemy.h"

//=============================================================================
//�O���錾
//=============================================================================
class CSquareHitbox;
class CBg;
class CThanatos;
class CSkullShield;


class CCandle : public CEnemy
{
public:

	enum state
	{
		state_spawn = 0,
		state_off,
		state_on,
		state_max
	};

	CCandle();
	~CCandle() override;								//�f�X�g���N�^
														
	virtual HRESULT Init(void) override;				//����������
	virtual void Uninit(void) override;					//�I������
	virtual void Update(void) override;					//�X�V����
	virtual void Draw(void) override;					//�`�揈��

	void SetParent(CThanatos* pParent);
	void SetBgPointer(CBg* pointer);

	state GetCandleState(void);

	void Unlit(void);
	void Despawn(void);

	static CCandle* Create(const D3DXVECTOR3 pos);		//��������
	static CCandle* Create(const D3DXVECTOR3 pos, CBg* pointer);		//��������

private:

	int m_nCntState;
	int m_nIdx;
	state m_state;

	CThanatos* m_pParent;
	CSquareHitbox* m_pHitbox;
	CBg* m_pBg;
	CSkullShield* m_pShield[2];

};

#endif