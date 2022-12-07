//=============================================================================
//
// player.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef PLAYER_H
#define PLAYER_H

//�C���N���[�h�t�@�C��
#include "object2D.h"

//�O���錾
class CSquareHitbox;
class CLifeIcon;

//�v���C���[�N���X(CObject_2D�̔h���N���X)
class CPlayer : public CObject_2D
{
public:
	CPlayer();								//�R���X�g���N�^
	~CPlayer() override;					//�f�X�g���N�^
											
	HRESULT Init(void) override;			//����������
	void Uninit(void) override;				//�I������
	void Update(void) override;				//�X�V����
	void Draw(void) override;				//�`�揈��

	void SetConfusion(const int nTime);		//

	void SetAttack(const int nAttack);		//�U���͂̐ݒ菈��

	const int GetLife(void);				//���C�t�̎擾����
	const int GetAttack(void);				//�U���͂̎擾����
	const bool GetEnd(void);				//����ł��邩�ǂ����̎擾����

	static CPlayer* Create(void);			//��������

	static CPlayer* GetPlayer(void);		//�v���C���[���̎擾����

private:

	int m_nAnimCnt;							//�A�j���V�����J�E���^�[
	int m_nShootDelay;						//�e�̔����J�E���^�[
	int m_nStateCnt;						//��ԃJ�E���^�[
	int m_nDamageCnt;						//�_���[�W�J�E���^�[
	int m_nAttack;							//�U����
	bool m_bConfused;						
	int m_nDir;								//����
	int m_nLife;							//�̗�
	bool m_bDead;							//����ł��邩�ǂ���
	bool m_bEnd;							//�Q�[���I�[�o�[�̃t���O

	CSquareHitbox* m_pHitbox;				//�q�b�g�{�b�N�X
	static CPlayer* m_pPlayer;				//�v���C���[�̃A�h���X
	CLifeIcon* m_pIcon;						//�̗͂�UI�ւ̃|�C���^
};

#endif // !PLAYER_H