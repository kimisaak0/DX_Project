#include "12a_BgObjC_DX.h"

BgObj_DX::BgObj_DX()
{

}

bool BgObj_DX::setBgImage(const TCHAR* pTexFile)
{
	CreateFullImgObj({ 0,0,(UINT)g_rtClient.right, (UINT)g_rtClient.bottom }, pTexFile);
	return true;
}

bool BgObj_DX::Init()
{
	Object_DX::Init();
	return true;
}

bool BgObj_DX::Frame()
{
	Object_DX::Frame();
	return true;
}

bool BgObj_DX::Render()
{
	Object_DX::Render();
	return true;
}

bool BgObj_DX::Release()
{
	Object_DX::Release();
	return true;
}

BgObj_DX::~BgObj_DX()
{

}