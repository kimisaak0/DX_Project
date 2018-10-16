#include "12a_BgObjC_DX.h"

BgObc_DX::BgObc_DX()
{

}

bool BgObc_DX::setBgImage(const TCHAR* pTexFile)
{
	CreateFullImgObj({ 0,0,(UINT)g_rtClient.right, (UINT)g_rtClient.bottom }, pTexFile);
	return true;
}

bool BgObc_DX::Init()
{
	Object_DX::Init();
	return true;
}

bool BgObc_DX::Frame()
{
	g_pD3dContext->UpdateSubresource(m_pVertexBuffer, 0, NULL, m_pVertexList, 0, 0);
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