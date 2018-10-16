#pragma once
#include "10_SceneC_DX.h"
#include "10a_SceneLobby_DX.h"
#include "10d_SceneGame_1_DX.h"

class SceneMgrC_DX
{
	SceneC_DX*  m_pScene;

	SceneC_DX*  m_pLobby;
	SceneC_DX*  m_pGame1;

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();

public:
	SceneMgrC_DX();
	virtual ~SceneMgrC_DX();
};