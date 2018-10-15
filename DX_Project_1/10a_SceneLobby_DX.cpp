#include "10a_SceneLobby_DX.h"

SceneLobby_DX::SceneLobby_DX()
{

}

bool	SceneLobby_DX::Init()
{
	m_iSceneID = 0;
	m_iNextSceneID = 0;
	m_bNextScene = false;

	m_bg.setBgImage(L"../INPUT/DATA/image/startBg.png");

	m_btnStart.CreateFullImgObj( { 1000, 550, 1330, 630 }, L"../INPUT/DATA/image/btnStart.bmp");

	return true;

}

bool	SceneLobby_DX::Frame()
{
	return true;
}

bool	SceneLobby_DX::Render()
{
	m_bg.Render();

	m_btnStart.Render();
	return true;
}

bool	SceneLobby_DX::Release()
{
	m_bg.Release();

	return true;
}

	
SceneLobby_DX::~SceneLobby_DX()
{

}