#pragma once
#include "08_Object_DX.h"
#include "14a_shot1.h"

class HeroObjC_DX : public Object_DX
{
	UINT m_uSpriteX;
	UINT m_uSpriteY;

	float m_fSpeedX;
	float m_fSpeedY;

	float m_BefCentery;


public:
	list<shot1> shot1_list;

public:
	void Shot1Fire(uPOINT mousePos);

public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();

public:
	HeroObjC_DX();
	virtual ~HeroObjC_DX();
};