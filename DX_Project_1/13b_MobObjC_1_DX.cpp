#include "13b_MobObjC_1_DX.h"

MobC_1::MobC_1()
{
	m_bExist = true;
}

void MobC_1::Shot1Fire(POINT HeroPos)
{

}

bool MobC_1::Init()
{
	m_BefCenterY = m_v3Center.y;
	m_fSpeedX = 1 / ((float)(rand() % 3000) + 500.f);

	m_iMAXHP = m_iCURHP = 100;
	
	return true;
}

bool MobC_1::Frame()
{
	if (m_uSRegion.right < 0 || m_uSRegion.bottom < 220 || m_uSRegion.top > 750) {
		m_bExist = false;
	}


	if (m_iCURHP <= 0) {
		m_bExist = false;
	}

	scale(1-(m_v3Center.y - m_BefCenterY));
	m_BefCenterY = m_v3Center.y;

	float HPPercent = m_iCURHP / m_iMAXHP;

	ColorChange(1,HPPercent, HPPercent, 1);

	if (m_bExist) {
		MoveX(-m_fSpeedX);

		Object_DX::Frame();
	}
	return true;
}

bool MobC_1::Render()
{
	if (m_bExist) {
		Object_DX::Render();
	}
	return true;
}

bool MobC_1::Release()
{
	Object_DX::Release();
	return true;
}

MobC_1::~MobC_1()
{

}