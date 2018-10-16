#pragma once
#include "00_header_DX.h"
#include "06_inputC_DX.h"
#include "04_timerC_DX.h"

#include "09_CollisionC_DX.h"

class Object_DX
{
protected:
	ID3D11Buffer*               m_pVertexBuffer;   // 정점 버퍼
	ID3D11VertexShader*         m_pVS;             // 정점 쉐이더
	ID3D11PixelShader*          m_pPS;             // 픽셀 쉐이더
	ID3D11InputLayout*          m_pInputLayout;    // 인풋 레이아웃
	ID3D11ShaderResourceView*   m_pTextureSRV;     // 텍스쳐 SRV

protected:
	PCT_VERTEX m_pVertexList[4];
	
	uWH   m_uImageSize;
	uLTRB m_uImagePart;

	uLTRB m_uSRegion;
	fLTRB m_fPRegion;

	POINT m_ptCenter;
	D3DXVECTOR3 m_v3Center;

	timerC_DX m_Timer;

private:
	void transStoP(); //화면 -> 투영
	void transPtoS(); //투영 -> 화면
	void UpdateCP(); //중점 갱신
	void UpdateVertexList(); //정점 리스트 갱신

	void SetPosition(uXYWH _xywh);
	void ImagePartialSelect(uXYWH imgXYWH, uWH imgSize);
	HRESULT Create(const TCHAR* pTexFile);

public:
	void CreateFullImgObj(uXYWH _xywh, const TCHAR* pTexFile);
	void CreatePartImgObj(uXYWH _xywh, uXYWH imgXYWH, uWH imgSize, const TCHAR* pTexFile);

	void ImagePartialChange(uXYWH);

	void ImageFileChange(const TCHAR* pTexFile);

	void MoveX(float fDis);
	void MoveY(float fDis);

	uLTRB getPos();

	void spin(float fAngle);
	void scale(float size);

public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();

public:
	Object_DX();
	virtual ~Object_DX();

};