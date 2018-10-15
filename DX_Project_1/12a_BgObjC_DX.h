#pragma once
#include "08_Object_DX.h"

class BgObc_DX : public Object_DX
{
public:
	bool setBgImage(ID3D11Device* pd3dDevice, const TCHAR* pTexFile);

public:
	virtual bool Init();
	virtual bool Frame(ID3D11DeviceContext* pContext);
	virtual bool Render(ID3D11DeviceContext* pContext);
	virtual bool Release();

public:
	BgObc_DX();
	virtual ~BgObc_DX();
};