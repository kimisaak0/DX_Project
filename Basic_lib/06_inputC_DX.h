#pragma once
#include "00_header_DX.h"

//1 :DirectInput ��ü�� ����  
//2 : DirectInput Ű���� ��ġ�� ���� / DirectInput ���콺 ��ġ�� ����
//3 : Ű���� �� ���콺�� ������ ������ ����  
//4 : Ű���� �� ���콺�� ������ ����  
//5 : Ű������ �׼��� ������ ���  
//6 : Ű���� �� ���콺�κ����� �������� ���  
//7 : DirectInput �ý����� ����

#define KeyStateCount 256
#define DataBufferSize 16



//���� �Ӹ��� �� ����... ��������.
class input_DX
{
public:
	LPDIRECTINPUT8 m_pDxInput;
	LPDIRECTINPUTDEVICE8 m_pDxKeypad;
	LPDIRECTINPUTDEVICE8 m_pDxMouse;

	BYTE  m_KeyCurState[KeyStateCount];
	BYTE  m_KeyBefState[KeyStateCount];
	DIMOUSESTATE m_MouseCurState;
	DIMOUSESTATE m_MouseBefState;

	//��� ó���� �ƴ� ���۸� ó���� �� �� �ʿ�.
	DIDEVICEOBJECTDATA m_sDidod[DataBufferSize];

	// �̰� ����?
	DWORD m_dwElemts;
	//bool m_bImmediate;

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();

	bool ResetDevice();
	bool ResetResource();

public:
	bool InitDirectInput(bool keypad, bool mouse);
	bool KeyProcess();
	bool MouseProcess();
	
	void DeviceAcquire();
	void DeviceUnacquire();

	bool IsKeyDown(DWORD dwKey);
	bool IsKeyUP(DWORD dwKey);

	bool IsKeyDownOnce(DWORD dwKey);

	void PostProcess();
	void SetAcquire(bool bActive);

public:
	static input_DX& GetInstance();
	static input_DX* GetInstancePtr();

private:
	input_DX();
	virtual ~input_DX();
};

#define I_Input input_DX::GetInstance()
#define I_InputPtr input_DX::GetInstancePtr()

