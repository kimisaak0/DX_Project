#include "11_SceneMgr_DX.h"

SceneMgrC_DX::SceneMgrC_DX()
{

}

bool SceneMgrC_DX::Init()
{
	m_pLobby = new SceneLobby_DX;
	m_pGame1 = new SceneGame_1_DX;

	m_pScene = m_pLobby;

	m_pScene->Init();

	return true;
}

bool SceneMgrC_DX::Frame()
{
	switch (m_pScene->getSceneID()) {
		case 0: {
			if (m_pScene->getNextScene()) {
				m_pScene = m_pGame1;
				m_pScene->Init();
			}
		} break;

	}

	m_pScene->Frame();
	return true;
}

bool SceneMgrC_DX::Render()
{
	m_pScene->Render();
	return true;
}

bool SceneMgrC_DX::Release()
{
	m_pScene->Release();
	return true;
}



SceneMgrC_DX::~SceneMgrC_DX()
{

}