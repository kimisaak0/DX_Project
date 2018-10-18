#include "15a_mapObj_1.h"

mapObj_1::mapObj_1()
{
	m_bExist = true;

	m_iHP = 30;
}

bool mapObj_1::Init()
{
	m_BefCenterY = m_v3Center.y;
	m_fSpeedX = 1 / ((float)(rand() % 10000) + 500.f);
	return true;
}

bool mapObj_1::Frame()
{
	if (m_uSRegion.right < 0 || m_uSRegion.bottom < 200 || m_uSRegion.top > 750) {
		m_bExist = false;
	}

	if (m_iHP < 0) {
		m_bExist = false;
	}

	scale(1-(m_v3Center.y - m_BefCenterY));
	m_BefCenterY = m_v3Center.y;

	if (m_bExist) {
		MoveX(-m_fSpeedX);

		Object_DX::Frame();
	}
	return true;
}

bool mapObj_1::Render()
{
	if (m_bExist) {
		Object_DX::Render();
	}
	return true;
}

bool mapObj_1::Release()
{
	Object_DX::Release();
	return true;
}

mapObj_1::~mapObj_1()
{

}