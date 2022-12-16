//=============================================================================
//
// missile.h
// Author : Ricci Alex
//
//=============================================================================
#ifndef MISSILE_H
#define MISSILE_H

//=============================================================================
//�C���N���[�h�t�@�C��
//=============================================================================
#include "bullet.h"

//=============================================================================
//�O���錾
//=============================================================================
class CSquareHitbox;

class CMissile : public CBullet
{
public:

	//��Ԃ̗񋓌^
	enum state
	{
		state_ascend = 0,		//��ɂ��낷
		state_descend,			//������
		state_strike,			//�X�g���C�N
		state_max
	};

	CMissile();							//�R���X�g���N�^
	~CMissile() override;				//�f�X�g���N�^

	HRESULT Init(void) override;		//����������
	void Uninit(void) override;			//�I������
	void Update(void) override;			//�X�V����


	static CMissile* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move);									//��������
	static CMissile* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 move, const D3DXVECTOR3 acc);			//��������

private:

	state m_state;						//���

	CSquareHitbox* m_pHitbox;			//�q�b�g�{�b�N�X�ւ̃|�C���^
};


#endif