#pragma once
#include "08_Object_DX.h"
#include "14a_shot1.h"

class MobC_1 : public Object_DX
{
	LONG m_uSpriteX;
	LONG m_uSpriteY;

	float m_fSpeedX;
	float m_fSpeedY;

	float m_BefCenterY;

public:
	float   m_iCURHP;
	float   m_iMAXHP;

	list<shot1> shot1_list;

public:
	void Shot1Fire(POINT mousePos);

public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();

public:
	MobC_1();
	virtual ~MobC_1();
};