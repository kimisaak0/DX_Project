#include "13a_HeroObjC_DX.h"

HeroObjC_DX::HeroObjC_DX()
{
	m_uSpriteX = 0;
	m_uSpriteY = 200;
	m_fSpeedX = 0;
	m_fSpeedY = 0;

}

void HeroObjC_DX::Shot1Fire(POINT mousePos)
{
	iXYWH pos = { m_ptCenter.x, m_ptCenter.y, 30,30 };

	float dx = mousePos.x - m_ptCenter.x;
	float dy = (mousePos.y - m_ptCenter.y) * 2;
	double distance = sqrt(pow(dx, 2) + pow(dy, 2));

	shot1 shot;
	shot.CreateFullImgObj(pos, L"../INPUT/DATA/image/shot1.png");
	shot.setSpeed((dx / distance) / 1000 , (-dy / distance) / 1000);

	shot1_list.push_back(shot);
}

bool HeroObjC_DX::Init()
{
	m_BefCentery = m_v3Center.y;
	return true;
}

bool HeroObjC_DX::Frame() 
{
	//총알 발사
	if (I_Input.getMouseInfo().left == p_DOWN) {
		Shot1Fire(I_Input.getMouseInfo().xy);
	}

	//총알 프레임
	list<shot1>::iterator shot1It;
	for (shot1It = shot1_list.begin(); shot1It != shot1_list.end(); shot1It++) {
		shot1It->Frame();
	}

	//총알 삭제하기
	for (shot1It = shot1_list.begin(); shot1It != shot1_list.end(); ) {
		if (!shot1It->getExist()) {
			shot1It = shot1_list.erase(shot1It);
		}
		else {
			shot1It++;
		}
	}

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

	scale(m_v3Center.y - m_BefCentery);
	m_BefCentery = m_v3Center.y;

	ImagePartialChange({ m_uSpriteX,m_uSpriteY,99,99 });


	if (I_Input.IsKeyDown(DIK_1)) { //Down
		spin(0.01f);
	}

	g_pD3dContext->UpdateSubresource(m_pVertexBuffer, 0, NULL, m_pVertexList, 0, 0);

	return true;
}

bool HeroObjC_DX::Render()
{
	list<shot1>::iterator shot1It;
	for (shot1It = shot1_list.begin(); shot1It != shot1_list.end(); shot1It++) {
		shot1It->Render();
	}

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