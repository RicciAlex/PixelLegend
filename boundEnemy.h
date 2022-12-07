////=============================================================================
////
//// boundEnemy.h
//// Author : Ricci Alex
////
////=============================================================================
//
////�C���N���[�h�t�@�C��
//#include "enemy.h"
//
////�K�w�\���A�j���[�V�����̓G�N���X(�G�N���X�̔h���N���X)
//class CBoundEnemy : public CEnemy
//{
//public:
//
//	static const int MAX_BOUND_OBJECT = 5;										//�K�w�\���̃����o�[�̍ő吔
//
//	CBoundEnemy();																//�R���X�g���N�^		
//	~CBoundEnemy();																//�f�X�g���N�^
//																				
//	HRESULT Init(void) override;												//����������
//	void Uninit(void) override;													//�I������
//	void Update(void) override;													//�X�V����
//	void Draw(void) override;													//�`�揈��
//																				
//	static CBoundEnemy* Create(CObject::EnemyType type, D3DXVECTOR3 pos);		//��������
//
//
//private:
//
//	void UpdateClock(void);										//���v�^�G�̍X�V����
//	void RespawnNeedle(void);									//���v�^�G�̒e�̃��X�|�[������
//																
//	CObject_2D* m_pBoundObject[MAX_BOUND_OBJECT];				//�K�w�\���̃I�u�W�F�N�g�ւ̃|�C���^
//	bool m_bBound[MAX_BOUND_OBJECT];							//�K�w�\���̃I�u�W�F�N�g�̓����[�X���ꂽ���ǂ���
//	int m_nCntBoundAnimation;									//�K�w�\���A�j���[�V�����p�̃J�E���^�[
//
//};
//
