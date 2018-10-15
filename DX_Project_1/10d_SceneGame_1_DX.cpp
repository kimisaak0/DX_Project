#include "10d_SceneGame_1_DX.h"

SceneGame_1_DX::SceneGame_1_DX()
{

}

bool	SceneGame_1_DX::Init()
{
	m_iSceneID = 0;
	m_iNextSceneID = 0;
	m_bNextScene = false;

	m_Actor.CreateFullImgObj({ 350,350,50,50 }, L"Koala.jpg");


	return true;
}

bool	SceneGame_1_DX::Frame()
{
	m_Actor.Frame();

	return true;
}

bool	SceneGame_1_DX::Render()
{

	m_Actor.Render();


	return true;
}

bool	SceneGame_1_DX::Release()
{
	m_Actor.Release();

	return true;
}


SceneGame_1_DX::~SceneGame_1_DX()
{

}