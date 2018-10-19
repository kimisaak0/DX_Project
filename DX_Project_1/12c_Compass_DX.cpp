#include "12c_Compass_DX.h"

compass_UI::compass_UI()
{
	befWaveX = 0;
	befWaveY = 0;
	befscale = 1;
}

void compass_UI::updateArrow()
{
	m_Arrow.scale(1 / befscale);

	float dx = g_iWaveX - befWaveX;
	float dy = g_iWaveY - befWaveY;
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

bool compass_UI::Init()
{
	CreateFullImgObj({ 600, 25, 100, 100 }, L"image/compass_back.png");
	
	m_Arrow.CreateFullImgObj({ 638,43, 27,63 }, L"image/Direction_arrow.png");
	
	if (g_iWaveX != 0  || g_iWaveY != 0) {
		updateArrow();
	}

	Object_DX::Init();
	return true;
}

bool compass_UI::Frame()
{
	
	m_Arrow.Frame();

	if (befWaveX != g_iWaveX || befWaveY != g_iWaveY) {
		updateArrow();
		befWaveX = g_iWaveX;
		befWaveY = g_iWaveY;
	}


	Object_DX::Frame();
	return true;
}

bool compass_UI::Render()
{
	Object_DX::Render();
	m_Arrow.Render();

	return true;
}

bool compass_UI::Release()
{

	Object_DX::Release();
	return true;
}



compass_UI::~compass_UI()
{

}