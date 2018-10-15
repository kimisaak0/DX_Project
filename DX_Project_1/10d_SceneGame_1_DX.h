#pragma once
#include "10_SceneC_DX.h"

#include "08_Object_DX.h"

class SceneGame_1_DX : public SceneC_DX
{
	Object_DX       m_Actor;
	Object_DX       m_Image;
	Object_DX       m_sky;
	Object_DX       m_statue;

public:
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release();

public:
	SceneGame_1_DX();
	virtual ~SceneGame_1_DX();
};