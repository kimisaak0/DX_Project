#pragma once
#include "08_Object_DX.h"

class BgObc_DX : public Object_DX
{
public:
	bool setBgImage( const TCHAR* pTexFile);

public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();

public:
	BgObc_DX();
	virtual ~BgObc_DX();
};