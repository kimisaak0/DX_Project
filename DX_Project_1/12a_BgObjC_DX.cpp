#include "12a_BgObjC_DX.h"

BgObc_DX::BgObc_DX()
{

}

bool BgObc_DX::setBgImage(ID3D11Device* pd3dDevice,const TCHAR* pTexFile)
{
	SetPosition(0, 0, g_uClientWidth, g_uClientHeight);
	Create(pd3dDevice, pTexFile);
	return true;
}

bool BgObc_DX::Init()
{
	Object_DX::Init();
	return true;
}

bool BgObc_DX::Frame(ID3D11DeviceContext* pContext)
{
	Object_DX::Frame(pContext);
	return true;
}

bool BgObc_DX::Render(ID3D11DeviceContext* pContext)
{
	Object_DX::Render(pContext);
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