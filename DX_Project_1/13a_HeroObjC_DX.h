#pragma once
#include "08_Object_DX.h"
#include "14a_shot1.h"

class HeroObjC_DX : public Object_DX
{
	LONG m_uSpriteX;
	LONG m_uSpriteY;

	float m_fSpeedX;
	float m_fSpeedY;

	float m_BefCenterY;

	float m_BulletTimer;

	int   m_iMAXHP;

public:
	list<shot1> shot1_list;

	bool  m_bExist;
	int   m_iCURHP;

public:
	void Shot1Fire(POINT mousePos);

public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();

public:
	HeroObjC_DX();
	virtual ~HeroObjC_DX();
};