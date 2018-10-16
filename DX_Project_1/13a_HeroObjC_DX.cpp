#include "13a_HeroObjC_DX.h"

HeroObjC_DX::HeroObjC_DX()
{
	m_uSpriteX = 0;
	m_uSpriteY = 200;
	m_fSpeedX = 0;
	m_fSpeedY = 0;

}


bool HeroObjC_DX::Init()
{
	m_y = m_v3Center.y;
	return true;
}

bool HeroObjC_DX::Frame() 
{
	//이동
	
	MoveX(m_fSpeedX);
	MoveY(m_fSpeedY);


	//가속도 조정
	if (I_Input.IsKeyDown(0x1e)) { //Left
		m_fSpeedX += -0.000001f;
	}

	if (I_Input.IsKeyDown(0x20)) { //Right
		m_fSpeedX += 0.000001f;
	}

	if (I_Input.IsKeyDown(0x11)) { //Up
		m_fSpeedY += 0.000001f;
	}

	if (I_Input.IsKeyDown(0x1f)) { //Down
		m_fSpeedY += -0.000001f;
	}


	//스프라이트
	if (abs(m_fSpeedX) >= abs(m_fSpeedY)) {
		if (m_fSpeedX > 0) {
			m_uSpriteY = 200; //우
		}
		else if (m_fSpeedX < 0) {
			m_uSpriteY = 100; //좌
		}
	}
	else {
		if (m_fSpeedY > 0) {
			m_uSpriteY = 300;   //하
		}
		else if (m_fSpeedY < 0) {
			m_uSpriteY = 0; //상
		}
	}

	m_uSpriteX += 100;
	if (m_uSpriteX >= 300) {
		m_uSpriteX = 0;
	}

	scale(m_v3Center.y - m_y);
	m_y = m_v3Center.y;

	ImagePartialChange({ m_uSpriteX,m_uSpriteY,100,100 });


	if (I_Input.IsKeyDown(DIK_1)) { //Down
		spin(0.01f);
	}

	g_pD3dContext->UpdateSubresource(m_pVertexBuffer, 0, NULL, m_pVertexList, 0, 0);

	return true;
}

bool HeroObjC_DX::Render()
{
	Object_DX::Render();
	return true;
}

bool HeroObjC_DX::Release()
{
	Object_DX::Release();
	return true;
}


HeroObjC_DX::~HeroObjC_DX()
{

}