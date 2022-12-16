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

	//��Ԃ̗񋓌^
	enum state
	{
		state_Spawn = 0,							//�X�|�[��
		state_Normal,								//����
		state_Hide,									//�B��
		state_ShowEyes,								//�ڂ�������
		state_Hidden,								//�B����
		state_Vulnerable,							//�_���[�W���󂯂�
		state_Death,								//���S
		state_Max
	};

	CThanatos();									//�R���X�g���N�^
	~CThanatos() override;							//�f�X�g���N�^

	virtual HRESULT Init(void) override;			//����������
	virtual void Uninit(void) override;				//�I������
	virtual void Update(void) override;				//�X�V����
	virtual void Draw(void) override;				//�`�揈��

	const bool GetEnd(void);						//�I��������ǂ����̎擾����

	void SetBgPointer(CBg* pPointer);				//�w�i�ւ̃|�C���^�̐ݒ菈��
	void AddLitCandle(void);						//�������E�\�N�̒ǉ�����

	static CThanatos* Create(void);					//��������

private:

	const static int Max_Candle = 4;				//���E�\�N�̍ő吔

	bool m_bEnd;									//�I��������ǂ���
	int m_nTargetLife;								//�ړI�̗̑�
	int m_nLitCandle;								//�������E�\�N�̐�
	int m_nCntState;								//��ԃJ�E���^�[
	state m_state;									//���
													
	CBg* m_pBg;										//�w�i�ւ̃|�C���^
	CCandle* m_pCandle[Max_Candle];					//���E�\�N�ւ̃|�C���^
	CEnemyLife* m_pLife;							//�̗�UI�ւ̃|�C���^
													
	CSquareHitbox* m_pHitbox;						//�q�b�g�{�b�N�X
};




#endif