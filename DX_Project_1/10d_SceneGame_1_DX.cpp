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
	m_gameBg2.CreateFullImgObj({ g_rtClient.right, 0, (UINT)g_rtClient.right, (UINT)g_rtClient.bottom}, L"../INPUT/DATA/image/GameBg.png");
	
	m_Hero.CreatePartImgObj({ 300,450,80,80 }, { 0,200,99,99 }, { 300,400 }, L"../INPUT/DATA/image/ship.png");
	m_Hero.Init();

	m_mob1.CreatePartImgObj({ 1000, 450, 96, 96 }, { 0, 0, 96, 96 }, { 288, 288 }, L"../INPUT/DATA/image/monster1.png");
	m_mob1.Init();
	
	return true;
}

bool	SceneGame_1_DX::Frame()
{
	m_gameBg1.Frame();
	m_gameBg2.Frame();

	m_Hero.MoveX(m_iWaveX);
	m_Hero.MoveY(m_iWaveY);

	m_Hero.Frame();
	
	m_mob1.Frame();

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
		
		m_mob1.Render();
	}




	return true;
}

bool	SceneGame_1_DX::Release()
{
	
	m_mob1.Release();

	m_Hero.Release();

	m_gameBg1.Release();
	m_gameBg2.Release();


	return true;
}


SceneGame_1_DX::~SceneGame_1_DX()
{

}