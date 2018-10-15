#include "12a_BgObjC_DX.h"

BgObc_DX::BgObc_DX()
{

}

bool BgObc_DX::setBgImage(const TCHAR* pTexFile)
{
	CreateFullImgObj({ 0,0,g_uClientWidth, g_uClientHeight }, pTexFile);
	return true;
}

bool BgObc_DX::Init()
{
	Object_DX::Init();
	return true;
}

bool BgObc_DX::Frame()
{
	Object_DX::Frame();
	return true;
}

bool BgObc_DX::Render()
{
	Object_DX::Render();
	return true;
}

bool BgObc_DX::Release()
{
	Object_DX::Release();
	return true;
}

BgObc_DX::~BgObc_DX()
{

}