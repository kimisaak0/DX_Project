#include "10d_SceneGame_1_DX.h"

SceneGame_1_DX::SceneGame_1_DX()
{
	m_iWaveX = -0.0005f;
	m_iWaveY = 0.0f;
}

bool	SceneGame_1_DX::Init()
{
	m_iSceneID = 0;
	m_iNextSceneID = 0;
	m_bNextScene = false;

	m_gameBg1.setBgImage(L"../INPUT/DATA/image/GameBg.png");
	m_gameBg2.CreateFullImgObj({ g_uClientWidth,0,g_uClientWidth, g_uClientHeight}, L"../INPUT/DATA/image/GameBg.png");

	m_Actor.CreatePartImgObj({ 100,100,50,50 }, { 20,6,50,50 }, { 350,272 }, L"../INPUT/DATA/image/Rock.png");

	m_Hero.CreatePartImgObj({ 300,450,80,80 }, { 0,200,100,100 }, { 300,400 }, L"../INPUT/DATA/image/ship.png");
	m_Hero.Init();
	
	return true;
}

bool	SceneGame_1_DX::Frame()
{
	m_gameBg1.Frame();
	m_gameBg2.Frame();

	m_Hero.MoveX(m_iWaveX);
	m_Hero.MoveY(m_iWaveY);

	m_Hero.Frame();
	

	m_Actor.Frame();


	return true;
}

bool	SceneGame_1_DX::Render()
{
	//배경 
	{
		//맵 스크롤
		m_gameBg1.MoveX(-0.0005f);
		m_gameBg2.MoveX(-0.0005f);
		if (m_gameBg1.getPos().right == 0) {
			m_gameBg1.MoveX(4);
		}
		if (m_gameBg2.getPos().right == 0) {
			m_gameBg2.MoveX(4);
		}
		m_gameBg1.Render();
		m_gameBg2.Render();
	}

	//캐릭터 
	{
		m_Hero.Render();
	}


	//맵 오브젝트
	{
		m_Actor.Render();
	}


	return true;
}

bool	SceneGame_1_DX::Release()
{
	m_Actor.Release();

	m_Hero.Release();

	m_gameBg1.Release();
	m_gameBg2.Release();

	return true;
}


SceneGame_1_DX::~SceneGame_1_DX()
{

}