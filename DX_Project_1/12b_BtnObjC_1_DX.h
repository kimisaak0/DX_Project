#pragma once
#include "08_Object_DX.h"

class BtnObjC_1_DX : public Object_DX
{
public:
	bool setBtnImage(uXYWH _uXYWH, const TCHAR* pTexFile);

public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();

public:
	BtnObjC_1_DX();
	virtual ~BtnObjC_1_DX();
};