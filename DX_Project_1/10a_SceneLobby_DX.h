#pragma once
#include "10_SceneC_DX.h"
#include "12a_BgObjC_DX.h"
#include "12b_BtnObjC_1_DX.h"

class SceneLobby_DX : public SceneC_DX
{
	bool sw;

	BgObc_DX m_bg;
	BtnObjC_1_DX m_btnStart;

public:
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release();

public:
	SceneLobby_DX();
	virtual	~SceneLobby_DX();
};