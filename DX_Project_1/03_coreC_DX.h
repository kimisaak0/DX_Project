#pragma once
#include "02_wndC_DX.h"
#include "04_timerC_DX.h"
#include "05_writeC_DX.h"
#include "06_inputC_DX.h"
#include "08b_Actor_DX.h"

class coreC_DX : public wndC_DX
{
	timerC_DX m_GameTimer;
	writeC_DX m_Font;

	Actor_DX   m_Actor;
	PCT_VERTEX m_FrameVertexList[6];
	ID3D11RasterizerState* m_pRSSolid;

private:
	bool m_swTimerRender;
	bool m_swKeyRender;

public:
	//Ŭ���� ������ ���� ó�� ������ ���� �Լ���. 
	bool Init();
	bool Frame();
	bool Render();
	bool Release();

	HRESULT SetRasterizerState();

public:
	//���� ��ü���� ó�� ������ ���� �Լ���. ���ӿ� ���� �κа� ������ ������ ���� �κ��� �и�
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

