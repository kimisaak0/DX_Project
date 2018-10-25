#pragma once
#include "08_Object_DX.h"

class compass_UI : public Object_DX
{
	Object_DX m_Arrow;

	float       befWaveX;
	float       befWaveY;

	float     befscale;

public:
	void updateArrow();

public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();

public:
	compass_UI();
	virtual ~compass_UI();
};