//=============================================================================
//
// inputMouse.h
// Author : Ricci Alex
//
//=============================================================================

#ifndef INPUT_MOUSE_H
#define INPUT_MOUSE_H

//�C���N���[�h�t�@�C��
#include "input.h"

class CInputMouse : public CInput
{
public:
	CInputMouse();
	~CInputMouse();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, GUID guid) override;
	void Uninit(void) override;
	void Update(void) override;

	DIMOUSESTATE*GetMouseState(void);
	bool GetMouseLeftClick(void);

private:

	DIMOUSESTATE m_MouseState;						// �}�E�X���

};

#endif // !INPUT_MOUSE_H