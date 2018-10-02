#pragma once
#include "00_header_DX.h"

//1 :DirectInput 개체의 생성  
//2 : DirectInput 키보드 장치의 생성 / DirectInput 마우스 장치의 생성
//3 : 키보드 및 마우스의 데이터 형식의 설정  
//4 : 키보드 및 마우스의 동작의 설정  
//5 : 키보드의 액세스 권한의 취득  
//6 : 키보드 및 마우스로부터의 데이터의 취득  
//7 : DirectInput 시스템의 종료

#define KeyStateCount 256
#define DataBufferSize 16



//뭔가 머리가 안 돌아... 문제있음.
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

	//즉시 처리가 아닌 버퍼링 처리를 할 때 필요.
	DIDEVICEOBJECTDATA m_sDidod[DataBufferSize];

	// 이게 뭘까?
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

