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

	//��Ԃ̗񋓌^
	enum state
	{
		state_spawn = 0,		//�X�|�[��
		state_off,				//������
		state_on,				//����
		state_max
	};

	CCandle();											//�R���X�g���N�^
	~CCandle() override;								//�f�X�g���N�^
														
	virtual HRESULT Init(void) override;				//����������
	virtual void Uninit(void) override;					//�I������
	virtual void Update(void) override;					//�X�V����
	virtual void Draw(void) override;					//�`�揈��

	void SetParent(CThanatos* pParent);					//�e�̐ݒ菈��
	void SetBgPointer(CBg* pointer);					//�w�i�ւ̃|�C���^�̐ݒ菈��
														
	state GetCandleState(void);							//��Ԃ̎擾����
														
	void Unlit(void);									//�΂���������
	void Despawn(void);									//�j������

	static CCandle* Create(const D3DXVECTOR3 pos);						//��������
	static CCandle* Create(const D3DXVECTOR3 pos, CBg* pointer);		//��������

private:

	int m_nCntState;						//��ԃJ�E���^�[
	int m_nIdx;								//�C���f�b�N�X
	state m_state;							//���
											
	CThanatos* m_pParent;					//�e�ւ̃|�C���^
	CSquareHitbox* m_pHitbox;				//�q�b�g�{�b�N�X�ւ̃|�C���^
	CBg* m_pBg;								//�w�i�ւ̃|�C���^
	CSkullShield* m_pShield[2];				

};

#endif