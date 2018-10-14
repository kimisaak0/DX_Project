#pragma once
#include "10_SceneC_DX.h"

class SceneLobby_DX : public SceneC_DX
{
public:
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release();

public:
	SceneLobby_DX();
	virtual	~SceneLobby_DX();
};