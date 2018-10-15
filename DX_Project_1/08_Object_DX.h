#pragma once
#include "00_header_DX.h"
#include "06_inputC_DX.h"
#include "04_timerC_DX.h"

class Object_DX
{
private:
	ID3D11Buffer*               m_pVertexBuffer;   // ���� ����
	ID3D11VertexShader*         m_pVS;             // ���� ���̴�
	ID3D11PixelShader*          m_pPS;             // �ȼ� ���̴�
	ID3D11InputLayout*          m_pInputLayout;    // ��ǲ ���̾ƿ�
	ID3D11ShaderResourceView*   m_pTextureSRV;     // �ؽ��� SRV

private:
	PCT_VERTEX m_pVertexList[4];
	
	uWH   m_uImageSize;
	uLTRB m_uImagePart;

	uLTRB m_uSRegion;
	fLTRB m_fPRegion;

	POINT m_ptCenter;
	D3DXVECTOR3 m_v3Center;

private:
	void transStoP(); //ȭ�� -> ����
	void transPtoS(); //���� -> ȭ��
	void UpdateCP(); //���� ����
	void UpdateVertexList(); //���� ����Ʈ ����

	void SetPosition(uXYWH _xywh);
	void ImagePartialSelect(uXYWH imgXYWH, uWH imgSize);
	HRESULT Create(const TCHAR* pTexFile);

public:
	void CreateFullImgObj(uXYWH _xywh, const TCHAR* pTexFile);
	void CreatePartImgObj(uXYWH _xywh, uXYWH imgXYWH, uWH imgSize, const TCHAR* pTexFile);

	void MoveX(UINT uDis);
	void MoveY(UINT fDis);

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