#include "12d_Compass_pc_DX.h"

compass_PC_UI::compass_PC_UI()
{
	initNum = 0;
	befscale = 1;
}

void compass_PC_UI::updateArrow()
{
	m_Arrow.spin(D3DX_PI * initNum / 4);

	//스프라이트
	if (g_PCSpeedX > 0) {
		if (g_PCSpeedY > 0) {
			if (abs(g_PCSpeedX) > abs(g_PCSpeedY) * 2) {
				m_Arrow.spin(D3DX_PI / 2);//rigiht
				initNum = 6;
			}
			else if (abs(g_PCSpeedY) > abs(g_PCSpeedX) * 2) {
				initNum = 0; //up
			}
			else {
				m_Arrow.spin(D3DX_PI / 4); //우상
				initNum = 7;
			}
		}
		else {
			if (abs(g_PCSpeedX) > abs(g_PCSpeedY) * 2) {
				m_Arrow.spin(D3DX_PI / 2);//rigiht
				initNum = 6;
			}
			else if (abs(g_PCSpeedY) > abs(g_PCSpeedX) * 2) {
				m_Arrow.spin(D3DX_PI);//down
				initNum = 4;
			}
			else {
				m_Arrow.spin(D3DX_PI * 3 / 4);//rigiht down
				initNum = 5;
			}
		}
	}
	else {
		if (g_PCSpeedY > 0) {
			if (abs(g_PCSpeedX) > abs(g_PCSpeedY) * 2) {
				m_Arrow.spin(D3DX_PI * 3 / 2);// left
				initNum = 2;
			}
			else if (abs(g_PCSpeedY) > abs(g_PCSpeedX) * 2) {
				initNum = 0;
			}
			else {
				m_Arrow.spin(-D3DX_PI / 4);//left up
				initNum = 1;
			}
		}
		else {
			if (abs(g_PCSpeedX) > abs(g_PCSpeedY) * 2) {
				m_Arrow.spin(D3DX_PI * 3 / 2);// left
				initNum = 2;
			}
			else if (abs(g_PCSpeedY) > abs(g_PCSpeedX) * 2) {
				m_Arrow.spin(D3DX_PI);//down
				initNum = 4;
			}
			else {
				m_Arrow.spin(D3DX_PI * 5 / 4);// left down
				initNum = 3;
			}
		}
	}
}

bool compass_PC_UI::Init()
{
	CreateFullImgObj({ 500, 25, 100, 100 }, L"../INPUT/DATA/image/compass_back.png");

	m_Arrow.CreateFullImgObj({ 538,43, 27,63 }, L"../INPUT/DATA/image/Direction_arrow_pc.png");

	Object_DX::Init();
	return true;
}

bool compass_PC_UI::Frame()
{

	m_Arrow.Frame();
	updateArrow();
	

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