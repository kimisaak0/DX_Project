#pragma once
#include "08_Object_DX.h"

class mapObj_1 : public Object_DX
{
	LONG m_uSpriteX;
	LONG m_uSpriteY;

	float m_fSpeedX;
	float m_fSpeedY;

	float m_BefCenterY;

public:
	bool  m_bExist;

	int   m_iHP;

public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();

public:
	mapObj_1();
	virtual ~mapObj_1();
};