#pragma once
#include "10_SceneC_DX.h"

class SceneOver_DX : public SceneC_DX
{

public:
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release();

public:
	SceneOver_DX();
	virtual ~SceneOver_DX();
};