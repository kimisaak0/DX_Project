#pragma once
#include "10_SceneC_DX.h"

class SceneVictory_DX : public SceneC_DX
{

public:
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release();

public:
	SceneVictory_DX();
	virtual ~SceneVictory_DX();
};