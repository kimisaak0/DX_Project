#pragma once
#include "08_Object_DX.h"

class shot1 : public Object_DX
{
protected:
	float m_fSpeedX;
	float m_fSpeedY;

	float m_BefCenterY;

	timerC_DX m_ExistTimer;
public:
	int   m_iDamage;;

public:
	void setSpeed(float dx, float dy);

	bool getExist();

public:
	bool Frame();

public:
	shot1();
	virtual ~shot1();
};