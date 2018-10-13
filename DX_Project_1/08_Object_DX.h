#pragma once
#include "00_header_DX.h"
#include "06_inputC_DX.h"
#include "04_timerC_DX.h"

class Object_DX
{
public:
	ID3D11Buffer*               m_pVertexBuffer;   // ���� ����
	ID3D11VertexShader*         m_pVS;             // ���� ���̴�
	ID3D11PixelShader*          m_pPS;             // �ȼ� ���̴�
	ID3D11InputLayout*          m_pInputLayout;    // ��ǲ ���̾ƿ�
	ID3D11ShaderResourceView*   m_pTextureSRV;     // �ؽ��� SRV

public:
	PCT_VERTEX m_pVertexList[4];

	PCT_VERTEX m_pVLtemp[4];
	
	RECT m_rtSRegion;
	fRect m_frtPRegion;

	POINT m_ptCenter;
	D3DXVECTOR3 m_v3Center;

public:
	timerC_DX m_timer;

public:
	HRESULT CreateVertexBuffer(ID3D11Device* pd3dDevice, PCT_VERTEX* pVertexList);
	HRESULT CreateVSandInputLayout(ID3D11Device* pd3dDevice, const TCHAR* pName);
	HRESULT CreatePS(ID3D11Device* pd3dDevice, const TCHAR* pName);
	HRESULT LoadTexture(ID3D11Device* pd3dDevice, const TCHAR* pLoadFile);

	HRESULT Create(ID3D11Device* pd3dDevive, const TCHAR* pVsFile, const TCHAR* pPsFile, const TCHAR* pTexFile);

	void transStoP();
	void transPtoS();

	void UpdateCP();

	void SetPosition(UINT sl, UINT st, UINT sr, UINT sb);
	void MoveX(float fDis);
	void MoveY(float fDis);
	void spin();

public:
	bool Frame(ID3D11DeviceContext* pContext);
	bool Render(ID3D11DeviceContext* pContext);
	bool Release();

public:
	Object_DX();
	virtual ~Object_DX();

};