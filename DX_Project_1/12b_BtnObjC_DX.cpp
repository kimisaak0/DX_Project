#include "12b_BtnObjC_DX.h"

BtnObjC_DX::BtnObjC_DX()
{

}

bool BtnObjC_DX::Init()
{
	Object_DX::Init();
	return true;
}

bool BtnObjC_DX::Frame(ID3D11DeviceContext* pContext)
{
	Object_DX::Frame(pContext);
	return true;
}

bool BtnObjC_DX::Render(ID3D11DeviceContext* pContext)
{
	Object_DX::Render(pContext);
	return true;
}

bool BtnObjC_DX::Release()
{
	Object_DX::Release();
	return true;
}

BtnObjC_DX::~BtnObjC_DX()
{

}