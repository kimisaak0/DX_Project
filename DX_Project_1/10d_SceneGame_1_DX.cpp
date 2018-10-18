#include "10d_SceneGame_1_DX.h"

SceneGame_1_DX::SceneGame_1_DX()
{
	m_iWaveX = -0.0005f;
	m_iWaveY = 0.0f;
}

bool	SceneGame_1_DX::Init()
{
	m_iSceneID = 0;
	m_iNextSceneID = 0;
	m_bNextScene = false;

	m_gameBg1.setBgImage(L"../INPUT/DATA/image/GameBg.png");
	m_gameBg2.CreateFullImgObj({ g_rtClient.right, 0, (UINT)g_rtClient.right, (UINT)g_rtClient.bottom}, L"../INPUT/DATA/image/GameBg.png");
	
	m_Hero.CreatePartImgObj({ 300,450,100,100 }, { 128,0,64,64 }, { 512,192 }, L"../INPUT/DATA/image/hero_no_wing.png");
	m_Hero.Init();

	m_Timer.Init();
	m_Timer_mapobj.Init();
	
	return true;
}

bool	SceneGame_1_DX::Frame()
{
#pragma region //���̳� �� ������Ʈ ����
	
	if (m_Timer_mapobj.tickAlram(1)) {
		if (m_mapObj1_List.size() < 25) {
			mapObj_1 objTemp;
			objTemp.CreatePartImgObj({ 1510, 200 + rand() % 500, 50, 50 }, { 0, (rand() % 4) * 100 , 100, 100 }, { 100, 400 }, L"../INPUT/DATA/image/mapObj.png");
			objTemp.Init();
			m_mapObj1_List.push_back(objTemp);
		}
	}

	if (m_Mob1_List.size() < 20) {
		if (m_Timer.tickAlram(1)) {
			MobC_1 mobATemp;
			mobATemp.CreatePartImgObj({ 1510, 200 + rand() % 500, 40, 40 }, { 0, 100, 95, 95 }, { 288, 288 }, L"../INPUT/DATA/image/monster1.png");
			mobATemp.Init();
			m_Mob1_List.push_back(mobATemp);
		}
	}
#pragma endregion

#pragma region // Frame
	m_gameBg1.Frame();
	m_gameBg2.Frame();

	m_Hero.MoveX(m_iWaveX);
	m_Hero.MoveY(m_iWaveY);

	m_Hero.Frame();

	list<MobC_1>::iterator Mob1It;
	for (Mob1It = m_Mob1_List.begin(); Mob1It != m_Mob1_List.end(); Mob1It++) {
		Mob1It->Frame();
	}

	list<mapObj_1>::iterator MapObj1It;
	for (MapObj1It = m_mapObj1_List.begin(); MapObj1It != m_mapObj1_List.end(); MapObj1It++) {
		MapObj1It->Frame();
	}


	
#pragma endregion

#pragma region //�浹 ó��

	//���� �ε������� ������ HP�� �ް� �� ��.

	ClsInfo cls;

	//Hero �浹
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
			}
		}
	}

	//��1 �浹
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

	//��obj1 �浹
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

#pragma region // ���̳� �� ������Ʈ ����

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
	//��� 
	{
		//�� ��ũ��
		m_gameBg1.MoveX(-0.0005f);
		m_gameBg2.MoveX(-0.0005f);
		if (m_gameBg1.getPos().right == 0) {
			m_gameBg1.MoveX(4);
		}
		if (m_gameBg2.getPos().right == 0) {
			m_gameBg2.MoveX(4);
		}
		m_gameBg1.Render();
		m_gameBg2.Render();
	}

	//ĳ���� 
	{
		m_Hero.Render();
		
		list<MobC_1>::iterator Mob1It;
		for (Mob1It = m_Mob1_List.begin(); Mob1It != m_Mob1_List.end(); Mob1It++) {
			Mob1It->Render();
		}
	}

	//�� ������Ʈ
	list<mapObj_1>::iterator MapObj1It;
	for (MapObj1It = m_mapObj1_List.begin(); MapObj1It != m_mapObj1_List.end(); MapObj1It++) {
		MapObj1It->Render();
	}


	return true;
}

bool	SceneGame_1_DX::Release()
{
	
	list<MobC_1>::iterator Mob1It;
	for (Mob1It = m_Mob1_List.begin(); Mob1It != m_Mob1_List.end(); Mob1It++) {
		Mob1It->Release();
	}

	list<mapObj_1>::iterator MapObj1It;
	for (MapObj1It = m_mapObj1_List.begin(); MapObj1It != m_mapObj1_List.end(); MapObj1It++) {
		MapObj1It->Release();
	}

	m_Hero.Release();

	m_gameBg1.Release();
	m_gameBg2.Release();


	return true;
}


SceneGame_1_DX::~SceneGame_1_DX()
{

}