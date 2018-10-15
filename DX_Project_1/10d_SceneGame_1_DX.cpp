#include "10d_SceneGame_1_DX.h"

SceneGame_1_DX::SceneGame_1_DX()
{

}

bool	SceneGame_1_DX::Init()
{
	m_iSceneID = 0;
	m_iNextSceneID = 0;
	m_bNextScene = false;

	m_Actor.SetPosition(350, 350, 50, 50);
	m_Actor.Create(L"Koala.jpg");

	m_Image.SetPosition(300, 300, 200, 200);
	m_Image.Create(L"../INPUT/DATA/image/Rock.png");

	m_sky.SetPosition(0, 0, 1500, 150);
	m_sky.Create(L"../INPUT/DATA/image/st00_cm_front.bmp");

	m_statue.SetPosition(500, 500, 300, 500);
	m_statue.Create(L"../INPUT/DATA/image/statue.png");

	return true;
}

bool	SceneGame_1_DX::Frame()
{
	m_Actor.Frame(g_pD3dContext);

	return true;
}

bool	SceneGame_1_DX::Render()
{
	m_sky.Render(g_pD3dContext);

	m_Actor.Render(g_pD3dContext);

	m_Image.Render(g_pD3dContext);

	m_statue.Render(g_pD3dContext);

	return true;
}

bool	SceneGame_1_DX::Release()
{
	m_sky.Release();
	m_Actor.Release();
	m_Image.Release();
	m_statue.Release();

	return true;
}


SceneGame_1_DX::~SceneGame_1_DX()
{

}