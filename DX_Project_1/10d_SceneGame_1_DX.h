#pragma once
#include "10_SceneC_DX.h"

#include "12a_BgObjC_DX.h"
#include "12c_Compass_DX.h"
#include "12d_Compass_pc_DX.h"

#include "13a_HeroObjC_DX.h"
#include "13b_MobObjC_1_DX.h"
#include "15a_mapObj_1.h"



class SceneGame_1_DX : public SceneC_DX
{
	timerC_DX    m_Timer;
	timerC_DX    m_Timer_mapobj;
	timerC_DX    m_Timer_wave;

private:
	compass_UI    m_UI_compass;
	compass_PC_UI m_UI_pc_compass;

	BgObj_DX     m_gameBg1;
	BgObj_DX     m_gameBg2;

	HeroObjC_DX  m_Hero;

	list<MobC_1> m_Mob1_List;

	list<mapObj_1> m_mapObj1_List;
	
		
public:
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release();

public:
	SceneGame_1_DX();
	virtual ~SceneGame_1_DX();
};