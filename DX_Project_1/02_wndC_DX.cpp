#pragma once
#include "02_wndC_DX.h"

//���������� ����
HINSTANCE    g_hInst;              //�������� �ν��Ͻ� �ڵ鰪
HWND         g_hWnd;			   //������ �������� �ڵ鰪
RECT         g_rtWindow;		   //������ ����
RECT         g_rtClient;		   //Ŭ���̾�Ʈ ���� (�۾�����)
UINT         g_uClientWidth;	   //�۾����� ����
UINT         g_uClientHeight;	   //�۾����� ����

wndC_DX* g_pWindow;            //���� ������ �����쿡 ���� ������

wndC_DX::wndC_DX(LPCTSTR LWndName)
{
	//������ ������ Ŭ����. �ڱ��ڽ��� ���� ������.
	g_pWindow = this;

	//������ ��� �� ������ �����ϸ� ����
	//assert()�� ���ڰ��� true�� �Ѿ��, false�� ������ ����.
	bool debug = registWnd(LWndName);
	assert(debug);

	GetWindowRect(g_hWnd, &g_rtWindow);   //������ RECT ��������
	GetWindowRect(g_hWnd, &g_rtClient);   //Ŭ���̾�Ʈ RECT ��������
}

//static�Լ� (���� �ܺ� �Լ�)
//������ ���ν��� Static�Լ�
LRESULT CALLBACK wndC_DX::MsgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	assert(g_pWindow);

	switch (iMsg) {

		//�����츦 ������ �� �߻��ϴ� �޽���
		case WM_CREATE: {

		}break;

		//�����츦 ������ �� �߻��ϴ� �޽��� (���α׷� ����ʹ� ����)
		case WM_DESTROY: {
			PostQuitMessage(0);
		}break;
	}

	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}


//�����츦 �߾����� �ű�� �Լ�.
void wndC_DX::CenterWindow(HWND hwnd)
{
	// ȭ�� ��ũ���� �ػ�(���̿� ����)�� ��´�.
	int iScreenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
	int iScreenHeight = GetSystemMetrics(SM_CYFULLSCREEN);

	// ������ Ŭ���̾�Ʈ �߾Ӱ� ȭ�� ��ũ�� �߾��� �����.
	int iDestX = (iScreenWidth - (g_rtWindow.right - g_rtWindow.left)) / 2;
	int iDestY = (iScreenHeight - (g_rtWindow.bottom - g_rtWindow.top)) / 2;

	// �����츦 ȭ���߾����� �̵���Ų��.
	MoveWindow(hwnd, iDestX, iDestY,
		g_rtWindow.right - g_rtWindow.left,
		g_rtWindow.bottom - g_rtWindow.top,
		true);
}

//������ ��� �� ����
bool wndC_DX::registWnd(LPCTSTR LWndName)
{
	//Regist wndClass
	ZeroMemory(&m_wndC, sizeof(WNDCLASSEX));
	m_wndC.cbSize = sizeof(WNDCLASSEX);
	m_wndC.hInstance = g_hInst;
	m_wndC.lpfnWndProc = MsgProc;
	m_wndC.lpszClassName = LWndName;
	//m_wndC.style = CS_NOCLOSE; //�������α׷��� ��Ÿ�� �Ӽ� �� (���� ����)
	//�� ���� �ǹ̴� ���� ����
	if (!RegisterClassEx(&m_wndC)) {
		return false;
	}

	g_hWnd = CreateWindowEx(NULL, //WS_EX_TOPMOST,     // ������ â Ȯ�� ��Ÿ��
		m_wndC.lpszClassName, m_wndC.lpszClassName,	   // ������ Ŭ���� �̸�(�߿�), Ÿ��Ʋ �ٿ� ��Ÿ�� ���ڿ�.
		WS_SYSMENU | WS_BORDER | WS_VISIBLE,           // ������ ������ â�� ��Ÿ�� ���� 
		CW_USEDEFAULT, CW_USEDEFAULT,				   // ������ X,Y ��ǥ
		800, 800,		                               // ������ ����, ���� ũ�� (�ȼ� ����)
		NULL, NULL, g_hInst, 			               // �θ� �������� �ڵ� ����, �޴� �ڵ� ����, �����츦 �����ϴ� �ν��Ͻ� �ڵ�
		NULL);                                         // WM_CREATE�޽����� lParam���� ���޵� CREATESTRUCT����ü ������
		//â ��Ÿ�ϰ� â Ȯ�� ��Ÿ�Ͽ� ���� �κ��� ���� ����

	//�����찡 �������� �ʾ����� false�� �����Ѵ�.
	if (g_hWnd == NULL) {
		return false;
	}

	return true;
}


//������ ������
bool wndC_DX::runWindow()
{
	if (!gameInit()) { return false; }

	//Main message loop
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while (true) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT) {
				break;
			}
		}
		else {
			gameRun();
		}
	}

	if (!gameRelease()) { return false; }

	return true;
}

wndC_DX::~wndC_DX()
{

}