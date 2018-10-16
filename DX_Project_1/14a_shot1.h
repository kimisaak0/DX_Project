#pragma once
#include "08_Object_DX.h"

class shot1 : public Object_DX
{
protected:
	bool m_bExist;

	float m_fSpeedX;
	float m_fSpeedY;

public:
	void setSpeed(float dx, float dy);

public:
	bool Frame();

public:
	shot1();
	virtual ~shot1();
};