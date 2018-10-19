//#include "10b_SceneOver_DX.h"
//
//SceneOver_DX::SceneOver_DX()
//{
//
//}
//
//bool	SceneOver_DX::Init()
//{
//	m_iSceneID = 0;
//	m_iNextSceneID = 0;
//	m_bNextScene = false;
//
//	m_bg.setBgImage(L"../INPUT/DATA/image/Over.png");
//
//	m_btnStart.setBtnImage({ 500,300,300,75 }, L"../INPUT/DATA/image/startBtn.png");
//	return true;
//
//}
//
//
//bool	SceneOver_DX::Frame()
//{
//	if (m_btnStart.Frame()) {
//		m_bNextScene = true;
//	}
//	return true;
//}
//
//bool	SceneOver_DX::Render()
//{
//	m_bg.Render();
//
//	m_btnStart.Render();
//
//	return true;
//}
//
//bool	SceneOver_DX::Release()
//{
//	m_bg.Release();
//
//	m_btnStart.Release();
//	return true;
//}
//
//
//SceneOver_DX::~SceneOver_DX()
//{
//
//}