#pragma once
#include "08_Object_DX.h"

class BtnObjC_DX : public Object_DX
{

public:
	virtual bool Init();
	virtual bool Frame(ID3D11DeviceContext* pContext);
	virtual bool Render(ID3D11DeviceContext* pContext);
	virtual bool Release();

public:
	BtnObjC_DX();
	virtual ~BtnObjC_DX();
};