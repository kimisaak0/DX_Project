#pragma once
#include "02_wndC_DX.h"
#include "04_timerC_DX.h"
#include "05_writeC_DX.h"
#include "06_inputC_DX.h"
#include "08_Object_DX.h"
#include "09_CollisionC_DX.h"

#include "10_SceneC_DX.h"
#include "10a_SceneLobby_DX.h"
#include "10d_SceneGame_1_DX.h"

class coreC_DX : public wndC_DX
{
	timerC_DX m_GameTimer;
	writeC_DX m_Font;

	ID3D11RasterizerState* m_pRSSolid;

	SceneC_DX*  m_pScene;

	SceneC_DX*  m_pLobby;
	SceneC_DX*  m_pGame1;


private:
	bool m_swTimerRender;
	bool m_swKeyRender;

public:
	//클래스 각각에 대한 처리 순서에 관한 함수들. 
	bool Init();
	bool Frame();
	bool Render();
	bool Release();

	HRESULT SetRasterizerState();

public:
	//게임 전체적인 처리 순서에 대한 함수들. 게임에 관한 부분과 윈도우 생성에 관한 부분을 분리
	bool gameInit() override;
	bool gameRun() override;
	bool gameFrame() override;
	bool gamePreRender() override;
	bool gameRender() override;
	bool gamePostRender() override;
	bool gameRelease() override;


public:
	bool ResetRT();

public:
	coreC_DX(LPCTSTR LWndName);
	virtual ~coreC_DX();
};

