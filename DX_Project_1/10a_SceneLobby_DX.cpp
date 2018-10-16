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
	
	m_btnStart.setBtnImage({ 500,300,300,75 }, L"../INPUT/DATA/image/startBtn.png");
	return true;

}

bool	SceneLobby_DX::Frame()
{
	if (m_btnStart.Frame()) {
		m_bNextScene = true;
	}
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

	m_btnStart.Release();
	return true;
}

	
SceneLobby_DX::~SceneLobby_DX()
{

}