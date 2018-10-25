#include "10d_SceneGame_1_DX.h"

int g_iWaveX;
int g_iWaveY;

SceneGame_1_DX::SceneGame_1_DX()
{


}

bool	SceneGame_1_DX::Init()
{
	m_iSceneID = 1;
	m_iNextSceneID = 0;
	m_bNextScene = false;
	m_bBGM = true;

	m_gameBg1.setBgImage(L"image/GameBg.png");
	m_gameBg2.CreateFullImgObj({ g_rtClient.right, 0, (UINT)g_rtClient.right, (UINT)g_rtClient.bottom}, L"image/GameBg.png");
	
	m_Hero.CreatePartImgObj({ 300,450,100,100 }, { 128,0,64,64 }, { 512,192 }, L"image/hero_no_wing.png");
	m_Hero.Init();

	m_Timer.Init();
	m_Timer_mapobj.Init();
	m_Timer_wave.Init();

	m_btnBGM.setBtnImage({ 50,50, 300,75 }, L"image/btnBGM.png");

	m_UI_compass.Init();
	m_UI_pc_compass.Init();

	return true;
}

bool	SceneGame_1_DX::Frame()
{
	if (m_btnBGM.Frame()) {
		m_bBGM = !m_bBGM;
	}

	if (m_bBGM) {
		I_SoundMgr.Play(0, true, true);
	}
	else {
		I_SoundMgr.Stop(0);
	}

	if (!(m_Hero.m_bExist)) {
		I_SoundMgr.PlayEffect(2);
		m_bNextScene = true;
	}

#pragma region //파도 변화
	if (m_Timer_wave.tickAlram(5 + rand()%10)) {
		I_SoundMgr.PlayEffect(3);
		g_iWaveX = rand() % 5;
		g_iWaveY = rand() % 5;
	}

#pragma endregion

#pragma region //몹이나 맵 오브젝트 생성
	
	if (m_Timer_mapobj.tickAlram(1)) {
		if (m_mapObj1_List.size() < 25) {
			mapObj_1 objTemp;
			objTemp.CreatePartImgObj({ 1510, 200 + rand() % 500, 50, 50 }, { 0, (rand() % 4) * 100 , 100, 100 }, { 100, 400 }, L"image/mapObj.png");
			objTemp.Init();
			m_mapObj1_List.push_back(objTemp);
		}
	}

	if (m_Mob1_List.size() < 20) {
		if (m_Timer.tickAlram(1)) {
			MobC_1 mobATemp;
			mobATemp.CreatePartImgObj({ 1510, 200 + rand() % 500, 40, 40 }, { 0, 100, 95, 95 }, { 288, 288 }, L"image/monster1.png");
			mobATemp.Init();
			m_Mob1_List.push_back(mobATemp);
		}
	}
#pragma endregion

#pragma region // Frame
	m_gameBg1.Frame();
	m_gameBg2.Frame();

	m_UI_compass.Frame();
	m_UI_pc_compass.Frame();

	m_Hero.MoveX(g_iWaveX/50000.f);
	m_Hero.MoveY(g_iWaveY/50000.f);

	m_Hero.Frame();

	list<MobC_1>::iterator Mob1It;
	for (Mob1It = m_Mob1_List.begin(); Mob1It != m_Mob1_List.end(); Mob1It++) {
		Mob1It->MoveX(g_iWaveX / 50000.f);
		Mob1It->MoveY(g_iWaveY / 10000.f);
		Mob1It->Frame();
	}

	list<mapObj_1>::iterator MapObj1It;
	for (MapObj1It = m_mapObj1_List.begin(); MapObj1It != m_mapObj1_List.end(); MapObj1It++) {
		MapObj1It->MoveX(g_iWaveX / 50000.f);
		MapObj1It->MoveY(g_iWaveY / 10000.f);
		MapObj1It->Frame();
	}

#pragma endregion

#pragma region //충돌 처리

	//서로 부딪혔을때 서로의 HP가 달게 할 것.

	ClsInfo cls;

	//Hero 충돌
	{
		list<MobC_1>::iterator Mob1It_2;
		for (Mob1It_2 = m_Mob1_List.begin(); Mob1It_2 != m_Mob1_List.end(); Mob1It_2++) {
			cls = I_ClsMgr.RectInRect(m_Hero.m_uSRegion, Mob1It_2->m_uSRegion);
			if (cls.bDoCls) {
				if (cls.drClsDest == d_RIGHT) {
					m_Hero.MoveX(stpX((cls.ptInLength.x) * -1));
				}
				else if (cls.drClsDest == d_LEFT) {
					m_Hero.MoveX(stpX((cls.ptInLength.x) * -1));
				}
				else if (cls.drClsDest == d_TOP) {
					m_Hero.MoveY(stpX((cls.ptInLength.y) * 1));
				}
				else if (cls.drClsDest == d_BOTTOM) {
					m_Hero.MoveY(stpX((cls.ptInLength.y) * 1));
				}
				I_SoundMgr.PlayEffect(7);
				Mob1It_2->m_bExist = false;
				m_Hero.m_iCURHP -= 25;
			}
		}

		list<mapObj_1>::iterator MapObj1It_2;
		for (MapObj1It_2 = m_mapObj1_List.begin(); MapObj1It_2 != m_mapObj1_List.end(); MapObj1It_2++) {
			cls = I_ClsMgr.RectInRect(m_Hero.m_uSRegion, MapObj1It_2->m_uSRegion);
			if (cls.bDoCls) {
				if (cls.drClsDest == d_RIGHT) {
					m_Hero.MoveX(stpX((cls.ptInLength.x) * -1));
				}
				else if (cls.drClsDest == d_LEFT) {
					m_Hero.MoveX(stpX((cls.ptInLength.x) * -1));
				}
				else if (cls.drClsDest == d_TOP) {
					m_Hero.MoveY(stpX((cls.ptInLength.y) * 1));
				}
				else if (cls.drClsDest == d_BOTTOM) {
					m_Hero.MoveY(stpX((cls.ptInLength.y) * 1));
				}
				I_SoundMgr.PlayEffect(7);
				MapObj1It_2->m_bExist = false;
				m_Hero.m_iCURHP -= 10;
			}
		}
	}

	//몹1 충돌
	for (Mob1It = m_Mob1_List.begin(); Mob1It != m_Mob1_List.end(); Mob1It++) {
		list<MobC_1>::iterator Mob1It_2; 
		for (Mob1It_2 = m_Mob1_List.begin(); Mob1It_2 != m_Mob1_List.end(); Mob1It_2++) {
			if (Mob1It != Mob1It_2) {
				cls = I_ClsMgr.RectInRect(Mob1It->m_uSRegion, Mob1It_2->m_uSRegion);
				if (cls.bDoCls) {
					if (cls.drClsDest == d_RIGHT) {
						Mob1It->MoveX(stpX((cls.ptInLength.x) * -1)); 
					}
					else if (cls.drClsDest == d_LEFT) {
						Mob1It->MoveX(stpX((cls.ptInLength.x) * -1));
					}
					else if (cls.drClsDest == d_TOP) {
						Mob1It->MoveY(stpX((cls.ptInLength.y) * 1));
					}
					else if (cls.drClsDest == d_BOTTOM) {
						Mob1It->MoveY(stpX((cls.ptInLength.y) * 1));
					}
				}
			}
		}

		list<mapObj_1>::iterator MapObj1It_2;
		for (MapObj1It_2 = m_mapObj1_List.begin(); MapObj1It_2 != m_mapObj1_List.end(); MapObj1It_2++) {
			cls = I_ClsMgr.RectInRect(Mob1It->m_uSRegion, MapObj1It_2->m_uSRegion);
			if (cls.bDoCls) {
				if (cls.drClsDest == d_RIGHT) {
					Mob1It->MoveX(stpX((cls.ptInLength.x) * -1));
				}
				else if (cls.drClsDest == d_LEFT) {
					Mob1It->MoveX(stpX((cls.ptInLength.x) * -1));
				}
				else if (cls.drClsDest == d_TOP) {
					Mob1It->MoveY(stpX((cls.ptInLength.y) * 1));
				}
				else if (cls.drClsDest == d_BOTTOM) {
					Mob1It->MoveY(stpX((cls.ptInLength.y) * 1));
				}
			}
		}

		list<shot1>::iterator shot1It;
		for (shot1It = m_Hero.shot1_list.begin(); shot1It != m_Hero.shot1_list.end(); shot1It++) {
			cls = I_ClsMgr.RectInRect(Mob1It->m_uSRegion, shot1It->m_uSRegion);
			if (cls.bDoCls) {
				I_SoundMgr.PlayEffect(6);
				shot1It->m_bExist = false;
				if (cls.drClsDest == d_RIGHT) {
					Mob1It->MoveX(stpX((cls.ptInLength.x) * -1));
					}
				else if (cls.drClsDest == d_LEFT) {
					Mob1It->MoveX(stpX((cls.ptInLength.x) * -1));
				}
				else if (cls.drClsDest == d_TOP) {
					Mob1It->MoveY(stpX((cls.ptInLength.y) * 1));
				}
				else if (cls.drClsDest == d_BOTTOM) {
					Mob1It->MoveY(stpX((cls.ptInLength.y) * 1));
				}
				Mob1It->m_iCURHP -= shot1It->m_iDamage;
			}
		}

		cls = I_ClsMgr.RectInRect(Mob1It->m_uSRegion, m_Hero.m_uSRegion);
		if (cls.bDoCls) {
			if (cls.drClsDest == d_RIGHT) {
				Mob1It->MoveX(stpX((cls.ptInLength.x) * -1));
			}
			else if (cls.drClsDest == d_LEFT) {
				Mob1It->MoveX(stpX((cls.ptInLength.x) * -1));
			}
			else if (cls.drClsDest == d_TOP) {
				Mob1It->MoveY(stpX((cls.ptInLength.y) * 1));
			}
			else if (cls.drClsDest == d_BOTTOM) {
				Mob1It->MoveY(stpX((cls.ptInLength.y) * 1));
			}
		}
	}

	//맵obj1 충돌
	for (MapObj1It = m_mapObj1_List.begin(); MapObj1It != m_mapObj1_List.end(); MapObj1It++) {
		list<MobC_1>::iterator Mob1It_2;
		for (Mob1It_2 = m_Mob1_List.begin(); Mob1It_2 != m_Mob1_List.end(); Mob1It_2++) {
			cls = I_ClsMgr.RectInRect(MapObj1It->m_uSRegion, Mob1It_2->m_uSRegion);
			if (cls.bDoCls) {
				if (cls.drClsDest == d_RIGHT) {
					MapObj1It->MoveX(stpX((cls.ptInLength.x) * -1));
				}
				else if (cls.drClsDest == d_LEFT) {
					MapObj1It->MoveX(stpX((cls.ptInLength.x) * -1));
				}
				else if (cls.drClsDest == d_TOP) {
					MapObj1It->MoveY(stpX((cls.ptInLength.y) * 1));
				}
				else if (cls.drClsDest == d_BOTTOM) {
					MapObj1It->MoveY(stpX((cls.ptInLength.y) * 1));
				}
			}
			
		}

		list<mapObj_1>::iterator MapObj1It_2;
		for (MapObj1It_2 = m_mapObj1_List.begin(); MapObj1It_2 != m_mapObj1_List.end(); MapObj1It_2++) {
			cls = I_ClsMgr.RectInRect(MapObj1It->m_uSRegion, MapObj1It_2->m_uSRegion);
			if (MapObj1It != MapObj1It_2) {
				if (cls.bDoCls) {
					if (cls.drClsDest == d_RIGHT) {
						MapObj1It->MoveX(stpX((cls.ptInLength.x) * -1));
					}
					else if (cls.drClsDest == d_LEFT) {
						MapObj1It->MoveX(stpX((cls.ptInLength.x) * -1));
					}
					else if (cls.drClsDest == d_TOP) {
						MapObj1It->MoveY(stpX((cls.ptInLength.y) * 1));
					}
					else if (cls.drClsDest == d_BOTTOM) {
						MapObj1It->MoveY(stpX((cls.ptInLength.y) * 1));
					}
				}
			}
		}

		list<shot1>::iterator shot1It;
		for (shot1It = m_Hero.shot1_list.begin(); shot1It != m_Hero.shot1_list.end(); shot1It++) {
			cls = I_ClsMgr.RectInRect(MapObj1It->m_uSRegion, shot1It->m_uSRegion);
			if (cls.bDoCls) {
				I_SoundMgr.PlayEffect(5);
				shot1It->m_bExist = false;
				if (cls.drClsDest == d_RIGHT) {
					MapObj1It->MoveX(stpX((cls.ptInLength.x) * -1));
				}
				else if (cls.drClsDest == d_LEFT) {
					MapObj1It->MoveX(stpX((cls.ptInLength.x) * -1));
				}
				else if (cls.drClsDest == d_TOP) {
					MapObj1It->MoveY(stpX((cls.ptInLength.y) * 1));
				}
				else if (cls.drClsDest == d_BOTTOM) {
					MapObj1It->MoveY(stpX((cls.ptInLength.y) * 1));
				}
				MapObj1It->m_iHP -= shot1It->m_iDamage;
			}
		}

		cls = I_ClsMgr.RectInRect(MapObj1It->m_uSRegion, m_Hero.m_uSRegion);
		if (cls.bDoCls) {
			if (cls.drClsDest == d_RIGHT) {
				MapObj1It->MoveX(stpX((cls.ptInLength.x) * -1));
			}
			else if (cls.drClsDest == d_LEFT) {
				MapObj1It->MoveX(stpX((cls.ptInLength.x) * -1));
			}
			else if (cls.drClsDest == d_TOP) {
				MapObj1It->MoveY(stpX((cls.ptInLength.y) * 1));
			}
			else if (cls.drClsDest == d_BOTTOM) {
				MapObj1It->MoveY(stpX((cls.ptInLength.y) * 1));
			}
		}
	}

#pragma endregion

#pragma region // 몹이나 맵 오브젝트 삭제

	for (Mob1It = m_Mob1_List.begin(); Mob1It != m_Mob1_List.end(); ) {
		if (!(Mob1It->m_bExist)) {
			Mob1It = m_Mob1_List.erase(Mob1It);
		}
		else {
			Mob1It++;
		}
	}

	for (MapObj1It = m_mapObj1_List.begin(); MapObj1It != m_mapObj1_List.end(); ) {
		if (!(MapObj1It->m_bExist)) {
			MapObj1It = m_mapObj1_List.erase(MapObj1It);
		}
		else {
			MapObj1It++;
		}
	}

#pragma endregion

	return true;
}

bool	SceneGame_1_DX::Render()
{
	//배경 
	{
		//맵 스크롤
		m_gameBg1.MoveX(-0.00005f);
		m_gameBg2.MoveX(-0.00005f);
		if (m_gameBg1.getPos().right == 0) {
			m_gameBg1.MoveX(4);
		}
		if (m_gameBg2.getPos().right == 0) {
			m_gameBg2.MoveX(4);
		}
		m_gameBg1.Render();
		m_gameBg2.Render();
	}


	//캐릭터 
	{
		m_Hero.Render();
		
		list<MobC_1>::iterator Mob1It;
		for (Mob1It = m_Mob1_List.begin(); Mob1It != m_Mob1_List.end(); Mob1It++) {
			Mob1It->Render();
		}
	}

	//맵 오브젝트
	list<mapObj_1>::iterator MapObj1It;
	for (MapObj1It = m_mapObj1_List.begin(); MapObj1It != m_mapObj1_List.end(); MapObj1It++) {
		MapObj1It->Render();
	}

	//UI
	{
		m_btnBGM.Render();
		m_UI_compass.Render();
		m_UI_pc_compass.Render();
	}

	return true;
}

bool	SceneGame_1_DX::Release()
{
	
	list<MobC_1>::iterator Mob1It;
	for (Mob1It = m_Mob1_List.begin(); Mob1It != m_Mob1_List.end(); ) {
		Mob1It->Release();
		Mob1It = m_Mob1_List.erase(Mob1It);
	}

	list<mapObj_1>::iterator MapObj1It;
	for (MapObj1It = m_mapObj1_List.begin(); MapObj1It != m_mapObj1_List.end(); ) {
		MapObj1It->Release();
		MapObj1It = m_mapObj1_List.erase(MapObj1It);
	}

	m_Hero.Release();

	m_UI_compass.Release();
	m_UI_pc_compass.Release();
	m_btnBGM.Release();

	m_gameBg1.Release();
	m_gameBg2.Release();

	return true;
}


SceneGame_1_DX::~SceneGame_1_DX()
{

}