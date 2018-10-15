#pragma once
#include "00_header_DX.h"
#include "06_inputC_DX.h"
#include "04_timerC_DX.h"

class Object_DX
{
public:
	ID3D11Buffer*               m_pVertexBuffer;   // Á¤Á¡ ¹öÆÛ
	ID3D11VertexShader*         m_pVS;             // Á¤Á¡ ½¦ÀÌ´õ
	ID3D11PixelShader*          m_pPS;             // ÇÈ¼¿ ½¦ÀÌ´õ
	ID3D11InputLayout*          m_pInputLayout;    // ÀÎÇ² ·¹ÀÌ¾Æ¿ô
	ID3D11ShaderResourceView*   m_pTextureSRV;     // ÅØ½ºÃÄ SRV

public:
	PCT_VERTEX m_pVertexList[4];
	D3DXVECTOR2 m_lt;
	D3DXVECTOR2 m_rb;
	
	RECT m_rtSRegion;
	fRect m_frtPRegion;

	POINT m_ptCenter;
	D3DXVECTOR3 m_v3Center;

public:
	timerC_DX m_timer;

public:
	HRESULT CreateVertexBuffer();
	HRESULT CreateVSandInputLayout();
	HRESULT CreatePS();
	HRESULT LoadTexture(const TCHAR* pLoadFile);

	HRESULT Create(const TCHAR* pTexFile);

	void transStoP();
	void transPtoS();

	void UpdateCP();

	void SetUV(UINT l, UINT t, UINT r, UINT b, UINT imgW, UINT imgH);
	void SetPosition(UINT sl, UINT st, UINT width, UINT height);


	void MoveX(float fDis);
	void MoveY(float fDis);
	void spin();
	void scale(float size);

public:
	virtual bool Init();
	virtual bool Frame(ID3D11DeviceContext* pContext);
	virtual bool Render(ID3D11DeviceContext* pContext);
	virtual bool Release();

public:
	Object_DX();
	virtual ~Object_DX();

};