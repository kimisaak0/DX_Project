#include "10a_SceneLobby_DX.h"

SceneLobby_DX::SceneLobby_DX()
{

}

bool	SceneLobby_DX::Init()
{
	m_iSceneID = 0;
	m_iNextSceneID = 0;
	m_bNextScene = false;
	m_bBGM = true;

	m_bg.setBgImage(L"image/startBg.png");
	
	m_btnStart.setBtnImage({ 600,200,300,75 }, L"image/btnStart.png");
	m_btnBGM.setBtnImage({ 600,300, 300,75 }, L"image/btnBGM.png");
	
	return true;
}


bool	SceneLobby_DX::Frame()
{
	if (m_btnStart.Frame()) {
		m_bNextScene = true;
	}

	if (m_btnBGM.Frame()) {
		m_bBGM = !m_bBGM;
	}

	if (m_bBGM) {
		I_SoundMgr.Play(0,true, true);
	}
	else {
		I_SoundMgr.Stop(0);
	}

	return true;
}

bool	SceneLobby_DX::Render()
{
	m_bg.Render();
	
	m_btnStart.Render();

	m_btnBGM.Render();

	return true;
}

bool	SceneLobby_DX::Release()
{
	m_bg.Release();
	m_btnStart.Release();
	m_btnBGM.Release();

	return true;
}

	
SceneLobby_DX::~SceneLobby_DX()
{

}