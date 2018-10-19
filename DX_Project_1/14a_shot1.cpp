#include "14a_shot1.h"

shot1::shot1()
{
	m_BefCenterY = m_v3Center.y;
	m_iDamage = 30;
	m_ExistTimer.Init();
}

void shot1::setSpeed(float dx, float dy)
{
	m_bExist = true;

	m_fSpeedX = dx;
	m_fSpeedY = dy;
}

bool shot1::getExist()
{
	return m_bExist;
}

bool shot1::Frame()
{
	MoveX(m_fSpeedX*10);
	MoveY(m_fSpeedY*10);

	Object_DX::Frame();

	scale(1-(m_v3Center.y - m_BefCenterY));
	m_BefCenterY = m_v3Center.y;

	if (m_ExistTimer.tickAlram(2)) {
		m_bExist = false;
	}

	static float angle;
	angle += (float)g_dSPF;

	spin(angle);

	return true;
}

shot1::~shot1()
{

}