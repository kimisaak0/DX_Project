#include "14a_shot1.h"

shot1::shot1()
{
	m_BefCentery = m_v3Center.y;
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
	MoveX(m_fSpeedX);
	MoveY(m_fSpeedY);

	g_pD3dContext->UpdateSubresource(m_pVertexBuffer, 0, NULL, m_pVertexList, 0, 0);

	scale(m_v3Center.y - m_BefCentery);
	m_BefCentery = m_v3Center.y;

	if (m_ExistTimer.tickAlram(2)) {
		m_bExist = false;
	}

	return true;
}

shot1::~shot1()
{

}