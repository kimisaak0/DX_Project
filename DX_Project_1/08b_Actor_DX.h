#pragma once
#include "08a_Object_DX.h"

class Actor_DX
{
public:
	Object_DX m_dxObj;
	D3DXVECTOR3 m_v3Center;

	RECT m_rtInit;
	PCT_VERTEX m_vertexList[4];

	int iVertexNum;

public:

	bool Create(ID3D11Device* pd3dDevice, const TCHAR* pVsFile, const TCHAR* pPsFile, const TCHAR* pTexFile);

	D3DXVECTOR3 Get(float x, float y);
	void GetCenter();
	void SetVertexData();
	bool SetData(RECT rt);
	bool SetData(UINT left, UINT top, UINT width, UINT height);
	void MoveX(float fDis);
	void MoveY(float fDis);


	virtual bool Init();
	virtual bool Frame(float fGameTimer, float fFps);
	virtual bool Render(ID3D11DeviceContext* pContext);
	virtual bool Release();

public:
	Actor_DX();
	virtual ~Actor_DX();
};