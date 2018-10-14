#include "10a_SceneLobby_DX.h"

SceneLobby_DX::SceneLobby_DX()
{

}

bool	SceneLobby_DX::Init()
{
	m_iSceneID = 0;
	m_iNextSceneID = 0;

	m_bNextScene = false;

	return true;

}

bool	SceneLobby_DX::Frame()
{
	return true;
}

bool	SceneLobby_DX::Render()
{
	return true;

}

bool	SceneLobby_DX::Release()
{
	return true;

}

	
SceneLobby_DX::~SceneLobby_DX()
{

}