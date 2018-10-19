#pragma once
#include "00_header_DX.h"

#include "04_timerC_DX.h"
#include "05_writeC_DX.h"
#include "06_inputC_DX.h"
#include "09_CollisionC_DX.h"
#include "07_soundC_DX.h"



class SceneC_DX
{
protected:
	int   m_iSceneID;
	bool  m_bNextScene;
	int   m_iNextSceneID;
	
public:
	int getSceneID();
	bool getNextScene();
	int getNextSceneID();

public:
	virtual bool	Init() { return true; };
	virtual bool	Frame() { return true; };
	virtual bool	Render() { return true; };
	virtual bool	Release() { return true; };

public:
	SceneC_DX();
	virtual ~SceneC_DX();

};