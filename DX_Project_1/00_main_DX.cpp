#include "03_coreC_DX.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{

	g_uClientWidth = 1516;  //���ϴ� ũ�� + 16
	g_uClientHeight = 789; //���ϴ� ũ�� + 39

	g_hInst = hInst;
	
	coreC_DX GameWnd(_T("GameWindow"));


	GameWnd.runWindow();

	return 0;
}