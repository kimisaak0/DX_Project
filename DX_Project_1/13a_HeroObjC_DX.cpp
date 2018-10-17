#include "13a_HeroObjC_DX.h"

HeroObjC_DX::HeroObjC_DX()
{
	m_uSpriteX = 128;
	m_uSpriteY = 0;
	m_fSpeedX = 0.0001;
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
	m_BefCenterY = m_v3Center.y;
	return true;
}

bool HeroObjC_DX::Frame() 
{
	//�Ѿ� �߻�
	if (I_Input.getMouseInfo().left == p_DOWN) {
		Shot1Fire(I_Input.getMouseInfo().xy);
	}

	//�Ѿ� ������
	list<shot1>::iterator shot1It;
	for (shot1It = shot1_list.begin(); shot1It != shot1_list.end(); shot1It++) {
		shot1It->Frame();
	}

	//�Ѿ� �����ϱ�
	for (shot1It = shot1_list.begin(); shot1It != shot1_list.end(); ) {
		if (!shot1It->getExist()) {
			shot1It = shot1_list.erase(shot1It);
		}
		else {
			shot1It++;
		}
	}

	//�̵�
	MoveX(m_fSpeedX);
	MoveY(m_fSpeedY);


	//���ӵ� ����
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


	//��������Ʈ
	if (m_fSpeedX > 0) {
		if (m_fSpeedY > 0) {
			if (abs(m_fSpeedX) > abs(m_fSpeedY) * 2) {
				m_uSpriteX = 128; //��
			}
			else if (abs(m_fSpeedY) > abs(m_fSpeedX) * 2) {
				m_uSpriteX = 256; //��
			}
			else {
				m_uSpriteX = 192; //���
			}
		}
		else {
			if (abs(m_fSpeedX) > abs(m_fSpeedY) * 2) {
				m_uSpriteX = 128; //��
			}
			else if (abs(m_fSpeedY) > abs(m_fSpeedX) * 2) {
				m_uSpriteX = 0; //��
			}
			else {
				m_uSpriteX = 64; //����
			}
		}
	}
	else {
		if (m_fSpeedY > 0) {
			if (abs(m_fSpeedX) > abs(m_fSpeedY) * 2) {
				m_uSpriteX = 384; // ��
			}
			else if (abs(m_fSpeedY) > abs(m_fSpeedX) * 2) {
				m_uSpriteX = 256; //��
			}
			else {
				m_uSpriteX = 320; //�»�
			}
		}
		else {
			if (abs(m_fSpeedX) > abs(m_fSpeedY) * 2) {
				m_uSpriteX = 384; //��
			}
			else if (abs(m_fSpeedY) > abs(m_fSpeedX) * 2) {
				m_uSpriteX = 0; //��
			}
			else {
				m_uSpriteX = 448; //����
			}
		}
	}

	static int pm = 1;
	if (m_Timer.tickAlram(0.2)) {
		m_uSpriteY += 64 * pm;
		if (m_uSpriteY == 192) {
			pm *= -1;
			m_uSpriteY += 64 * pm * 2;
		} 
		if (m_uSpriteY == 0) {
			pm *= -1;
		}

	
	}

	scale(m_v3Center.y - m_BefCenterY);
	m_BefCenterY = m_v3Center.y;

	ImagePartialChange({ m_uSpriteX,m_uSpriteY,64,64 });


	if (I_Input.IsKeyDown(DIK_1)) { //Down
		spin(0.01f);
	}

	Object_DX::Frame();
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