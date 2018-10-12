#pragma once
#include "00_header_DX.h"

struct PCT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR4 c;
	D3DXVECTOR2 t;

	bool operator==  (const PCT_VERTEX& Vertex)
	{
		if (p == Vertex.p && c == Vertex.c && t == Vertex.t) {
			return true;
		}
		else {
			return false;
		}
	}

	PCT_VERTEX() {}

	PCT_VERTEX(D3DXVECTOR3 vp, D3DXVECTOR4 vc, D3DXVECTOR2 vt)
	{
		p = vp;
		c = vc;
		t = vt;
	}
};

class Object_DX
{
public:
	ID3D11Buffer*               m_pVertexBuffer;   // Á¤Á¡ ¹öÆÛ
	ID3D11VertexShader*         m_pVS;             // Á¤Á¡ ½¦ÀÌ´õ
	ID3D11PixelShader*          m_pPS;             // ÇÈ¼¿ ½¦ÀÌ´õ
	ID3D11InputLayout*          m_pInputLayout;    // ÀÎÇ² ·¹ÀÌ¾Æ¿ô
	ID3D11ShaderResourceView*   m_pTextureSRV;     // ÅØ½ºÃÄ SRV

public:
	UINT m_iNumVertex;

public:
	HRESULT CreateVertexBuffer(ID3D11Device* pd3dDevice, PCT_VERTEX* pVertexList, int iNumCount);
	HRESULT CreateVSandInputLayout(ID3D11Device* pd3dDevice, const TCHAR* pName);
	HRESULT CreatePS(ID3D11Device* pd3dDevice, const TCHAR* pName);
	HRESULT LoadTexture(ID3D11Device* pd3dDevice, const TCHAR* pLoadFile);

public:
	bool Render(ID3D11DeviceContext* pContext);
	bool Release();

public:
	Object_DX();
	virtual ~Object_DX();

};