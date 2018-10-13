#include "03_coreC_DX.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{

	g_uClientWidth = 716;  //원하는 크기 + 16
	g_uClientHeight = 739; //원하는 크기 + 39

	g_hInst = hInst;
	
	coreC_DX GameWnd(_T("GameWindow"));


	GameWnd.runWindow();

	return 0;
}