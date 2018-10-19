#pragma once
#include "10_SceneC_DX.h"
#include "12a_BgObjC_DX.h"
#include "12b_BtnObjC_1_DX.h"

class SceneOver_DX : public SceneC_DX
{
	BgObj_DX m_bg;
	BtnObjC_1_DX m_btnLobby;
	BtnObjC_1_DX m_btnRestart;

public:
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release();

public:
	SceneOver_DX();
	virtual ~SceneOver_DX();
};