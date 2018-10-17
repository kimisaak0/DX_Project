#include "12b_BtnObjC_1_DX.h"

BtnObjC_1_DX::BtnObjC_1_DX()
{

}

bool BtnObjC_1_DX::setBtnImage(iXYWH _uXYWH,  const TCHAR* pTexFile)
{
	CreatePartImgObj(_uXYWH, { 0,0,300,70 }, { 300,210 }, pTexFile);

	return true;
}

bool BtnObjC_1_DX::Init()
{
	Object_DX::Init();
	return true;
}

bool BtnObjC_1_DX::Frame()
{
	MouseInfo mi = I_Input.getMouseInfo();

	if(I_ClsMgr.RectInPt(m_uSRegion, mi.xy)) {
		if (mi.left == p_DOWN) {
			//ImagePartialChange({ 0,140,300,70 });
			//사운드 추가
			return true;
		}
		else if(mi.left == p_FREE) {
			ImagePartialChange({ 0,70,300,70 });
		}
	}
	else {
		ImagePartialChange({ 0,0,300,70 });
	}

	Object_DX::Frame();
	return false;
}

bool BtnObjC_1_DX::Render()
{
	Object_DX::Render();
	return true;
}

bool BtnObjC_1_DX::Release()
{
	Object_DX::Release();
	return true;
}

BtnObjC_1_DX::~BtnObjC_1_DX()
{

}