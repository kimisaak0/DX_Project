#include "13b_MobObjC_1_DX.h"

MobC_1::MobC_1()
{

}

void MobC_1::Shot1Fire(POINT HeroPos)
{

}

bool MobC_1::Init()
{
	m_BefCenterY = m_v3Center.y;

	return true;
}

bool MobC_1::Frame()
{
	Object_DX::Frame();
	return true;
}

bool MobC_1::Render()
{
	Object_DX::Render();
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