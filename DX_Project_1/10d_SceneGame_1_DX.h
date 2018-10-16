#pragma once
#include "10_SceneC_DX.h"

#include "12a_BgObjC_DX.h"
#include "13a_HeroObjC_DX.h"


class SceneGame_1_DX : public SceneC_DX
{
	float m_iWaveX;
	float m_iWaveY;

	BgObc_DX     m_gameBg1;
	BgObc_DX     m_gameBg2;

	HeroObjC_DX  m_Hero;

	Object_DX    m_Actor;


public:
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release();

public:
	SceneGame_1_DX();
	virtual ~SceneGame_1_DX();
};