#include "12b_BtnObjC_1_DX.h"

BtnObjC_1_DX::BtnObjC_1_DX()
{

}

bool BtnObjC_1_DX::setBtnImage(uXYWH _uXYWH,  const TCHAR* pTexFile)
{
	CreatePartImgObj(_uXYWH, { 0,0,300,75 }, { 300,225 }, pTexFile);

	return true;
}

bool BtnObjC_1_DX::Init()
{
	Object_DX::Init();
	return true;
}

bool BtnObjC_1_DX::Frame()
{
	if(I_ClsMgr.RectInPt(m_uSRegion, I_Input.getMouseInfo().xy)) {
		ImagePartialChange({ 0,75,300,75 });
		if (I_Input.getMouseInfo().left == p_HOLD) {
			ImagePartialChange({ 0,150,300,75 });
			return true;
		}
	}
	else {
		ImagePartialChange({ 0,0,300,75 });
	}

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