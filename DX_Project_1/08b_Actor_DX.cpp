#include "08b_Actor_DX.h"

Actor_DX::Actor_DX()
{
	iVertexNum = sizeof(m_vertexList) / sizeof(m_vertexList[0]);
}

bool Actor_DX::Create(ID3D11Device* pd3dDevice, const TCHAR* pVsFile, const TCHAR* pPsFile, const TCHAR* pTexFile)
{
	m_dxObj.CreateVertexBuffer(pd3dDevice, m_vertexList, iVertexNum);
	m_dxObj.CreateVSandInputLayout(pd3dDevice, pVsFile);
	m_dxObj.CreatePS(pd3dDevice, pPsFile);
	m_dxObj.LoadTexture(pd3dDevice, pTexFile);

	return true;
}

D3DXVECTOR3 Actor_DX::Get(float x, float y)
{
	D3DXVECTOR3 vRet;

	vRet.x = x / g_uClientWidth;
	vRet.y = y / g_uClientHeight;

	vRet.x = vRet.x * 2.0f - 1.0f;
	vRet.y = -(vRet.y * 2.0f - 1.0f);

	return vRet;
}

void Actor_DX::GetCenter()
{
	m_v3Center.x = 0.0f;
	m_v3Center.y = 0.0f;

	for (int iV = 0; iV < iVertexNum; iV++) {
		D3DXVECTOR3 vertex = m_vertexList[iV].p;
		m_v3Center.x += vertex.x;
		m_v3Center.y += vertex.y;
	}

	m_v3Center.x /= iVertexNum;
	m_v3Center.y /= iVertexNum;
}

void Actor_DX::MoveX(float fDis)
{
	for (int iV = 0; iV < iVertexNum; iV++) {
		m_vertexList[iV].p.x += fDis;
	}

	GetCenter();
}

void Actor_DX::MoveY(float fDis)
{
	for (int iV = 0; iV < iVertexNum; iV++) {
		m_vertexList[iV].p.y += fDis;
	}

	GetCenter();
}

void Actor_DX::SetVertexData()
{
	D3DXVECTOR3 pos;

	pos = Get(m_rtInit.left, m_rtInit.top);
	m_vertexList[0].p = D3DXVECTOR3(pos.x, pos.y, 0.0f);
	m_vertexList[0].t = D3DXVECTOR2(0.0f, 0.0f);
	m_vertexList[0].c = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);

	pos = Get(m_rtInit.left + m_rtInit.right, m_rtInit.top);
	m_vertexList[1].p = D3DXVECTOR3(pos.x, pos.y, 0.0f);
	m_vertexList[1].t = D3DXVECTOR2(1.0f, 0.0f);
	m_vertexList[1].c = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f);

	pos = Get(m_rtInit.left, m_rtInit.top + m_rtInit.bottom);
	m_vertexList[2].p = D3DXVECTOR3(pos.x, pos.y, 0.0f);
	m_vertexList[2].t = D3DXVECTOR2(0.0f, 1.0f);
	m_vertexList[2].c = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);

	pos = Get(m_rtInit.left + m_rtInit.right, m_rtInit.top + m_rtInit.bottom);
	m_vertexList[3].p = D3DXVECTOR3(pos.x, pos.y, 0.0f);
	m_vertexList[3].t = D3DXVECTOR2(1.0f, 1.0f);
	m_vertexList[3].c = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);

	GetCenter();
}

bool Actor_DX::SetData(RECT rt)
{
	m_rtInit.left = rt.left;
	m_rtInit.top = rt.top;
	m_rtInit.right = rt.right;
	m_rtInit.bottom = rt.bottom;

	SetVertexData();

	return true;

}

bool Actor_DX::SetData(UINT left, UINT top, UINT width, UINT height)
{
	RECT rt;
	rt.left = left;
	rt.top = top;
	rt.right = width;
	rt.bottom = height;

	SetData(rt);

	return true;
}


bool Actor_DX::Init()
{
	return true;
}

bool Actor_DX::Frame(float fGameTimer, float fFps)
{
	return true;
}

bool Actor_DX::Render(ID3D11DeviceContext* pContext)
{
	m_dxObj.Render(pContext);
	return true;
}

bool Actor_DX::Release()
{
	m_dxObj.Release();
	return true;
}


Actor_DX::~Actor_DX()
{

}