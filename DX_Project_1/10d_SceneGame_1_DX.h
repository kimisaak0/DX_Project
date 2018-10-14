#pragma once
#include "10_SceneC_DX.h"

class SceneGame_1_DX : public SceneC_DX
{

public:
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release();

public:
	SceneGame_1_DX();
	virtual ~SceneGame_1_DX();
};