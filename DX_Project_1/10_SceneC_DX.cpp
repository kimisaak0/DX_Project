#include "10_SceneC_DX.h"

SceneC_DX::SceneC_DX()
{
	m_bNextScene = false;
}

int SceneC_DX::getSceneID()
{
	return m_iSceneID;
}

bool SceneC_DX::getNextScene()
{
	return m_bNextScene;
}

int SceneC_DX::getNextSceneID()
{
	return m_iNextSceneID;
}

SceneC_DX::~SceneC_DX()
{

}