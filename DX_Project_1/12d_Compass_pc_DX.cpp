#include "12d_Compass_pc_DX.h"

compass_PC_UI::compass_PC_UI()
{
	befSpeedX = 0;
	befSpeedY = 0;
	befscale = 1;
}

void compass_PC_UI::updateArrow()
{
	m_Arrow.scale(1 / befscale);

	float dx = g_PCSpeedX - befSpeedX;
	float dy = g_PCSpeedY - befSpeedY;
	float distance = sqrt(pow(dx, 2) + pow(dy, 2));

	D3DXVECTOR2 vDirection = { dx, dy };
	//D3DXVec2Normalize(&vDirection, &vDirection);
	vDirection /= distance;

	D3DXVECTOR2 vUp = { 0.0f, 1.0f };
	D3DXVECTOR2 vRight = { 1.0f, 0.0f };
	float radian = acos(D3DXVec2Dot(&vUp, &vDirection));

	if (D3DXVec2Dot(&vRight, &vDirection) < 0)
		radian = -radian;

	m_Arrow.spin(radian);

	befscale = 1 + (distance - 1) / 10;

	m_Arrow.scale(befscale);
}

bool compass_PC_UI::Init()
{
	CreateFullImgObj({ 600, 25, 100, 100 }, L"../INPUT/DATA/image/compass_back.png");

	m_Arrow.CreateFullImgObj({ 638,43, 27,63 }, L"../INPUT/DATA/image/Direction_arrow_pc.png");

	if (g_iWaveX != 0 || g_iWaveY != 0) {
		updateArrow();
	}

	Object_DX::Init();
	return true;
}

bool compass_PC_UI::Frame()
{

	m_Arrow.Frame();

	if (befSpeedX != g_PCSpeedX || befSpeedY != g_PCSpeedY) {
		updateArrow();
		befSpeedX = g_PCSpeedX;
		befSpeedY = g_PCSpeedY;
	}


	Object_DX::Frame();
	return true;
}

bool compass_PC_UI::Render()
{
	Object_DX::Render();
	m_Arrow.Render();

	return true;
}

bool compass_PC_UI::Release()
{

	Object_DX::Release();
	return true;
}



compass_PC_UI::~compass_PC_UI()
{

}