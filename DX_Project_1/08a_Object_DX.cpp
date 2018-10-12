#include "08a_Object_DX.h"

Object_DX::Object_DX()
{

}

// 정점 버퍼 생성
HRESULT Object_DX::CreateVertexBuffer(ID3D11Device* pd3dDevice, PCT_VERTEX* pVertexList, int iNumCount)
{
	HRESULT hr;

	D3D11_BUFFER_DESC sDesc;
	ZeroMemory(&sDesc, sizeof(D3D11_BUFFER_DESC));
	sDesc.Usage = D3D11_USAGE_DEFAULT;
	sDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	sDesc.ByteWidth = sizeof(PCT_VERTEX) * iNumCount;

	D3D11_SUBRESOURCE_DATA sInitData;
	ZeroMemory(&sInitData, sizeof(D3D11_SUBRESOURCE_DATA));
	sInitData.pSysMem = pVertexList;

	if (FAILED(hr = pd3dDevice->CreateBuffer(&sDesc, &sInitData, &m_pVertexBuffer))) {
		return hr;
	}

	m_iNumVertex = iNumCount;

	return hr;
}

//정점 쉐이더 생성
HRESULT Object_DX::CreateVSandInputLayout(ID3D11Device* pd3dDevice, const TCHAR* pName)
{
	HRESULT hr;
	ID3DBlob*  pErrorBlob;
	ID3DBlob*  pVSBlob;

	hr = D3DX11CompileFromFile(pName, NULL, NULL, "VS", "vs_5_0", NULL, NULL, NULL, &pVSBlob, &pErrorBlob, NULL);
	if (FAILED(hr)) {
		OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
		return false;
	}

	hr = pd3dDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &m_pVS);
	if (FAILED(hr)) {
		return hr;
	}

	if (pVSBlob == NULL) { return E_FAIL; }

	D3D11_INPUT_ELEMENT_DESC ied[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	int iNumElement = sizeof(ied) / sizeof(D3D11_INPUT_ELEMENT_DESC);

	hr = pd3dDevice->CreateInputLayout(ied, iNumElement, pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), &m_pInputLayout);
	if (FAILED(hr)) {
		return hr;
	}

	SAFE_RELEASE(pErrorBlob);
	SAFE_RELEASE(pVSBlob);

	return hr;
}

//픽셀 쉐이더 생성
HRESULT Object_DX::CreatePS(ID3D11Device* pd3dDevice, const TCHAR* pName)
{
	HRESULT hr;
	ID3DBlob*  pPSBlop;
	ID3DBlob*  pErrorBlob;

	hr = D3DX11CompileFromFile(pName, NULL, NULL, "PS", "ps_5_0", NULL, NULL, NULL, &pPSBlop, &pErrorBlob, NULL);
	if (FAILED(hr)) {
		OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
		return false;
	}

	hr = pd3dDevice->CreatePixelShader(pPSBlop->GetBufferPointer(), pPSBlop->GetBufferSize(), NULL, &m_pPS);
	if (FAILED(hr)) {
		SAFE_RELEASE(pPSBlop);
		return NULL;
	}

	SAFE_RELEASE(pErrorBlob);
	SAFE_RELEASE(pPSBlop);
	return hr;
}

//텍스쳐 불러오기
HRESULT Object_DX::LoadTexture(ID3D11Device* pd3dDevice, const TCHAR* pLoadFile)
{
	HRESULT hr;

	hr = D3DX11CreateShaderResourceViewFromFile(pd3dDevice, pLoadFile, NULL, NULL, &m_pTextureSRV, NULL);
	if (FAILED(hr)) {
		return hr;
	}

	return hr;
}

//그리기
bool Object_DX::Render(ID3D11DeviceContext* pContext)
{
	UINT pStrides = sizeof(PCT_VERTEX);
	UINT pOffsets = 0;

	pContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &pStrides, &pOffsets);
	pContext->IASetInputLayout(m_pInputLayout);
	pContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	pContext->VSSetShader(m_pVS, NULL, NULL);
	pContext->PSSetShader(m_pPS, NULL, NULL);
	pContext->PSSetShaderResources(0, 1, &m_pTextureSRV);

	pContext->Draw(m_iNumVertex, 0);

	return true;
}

bool Object_DX::Release()
{
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pVS);
	SAFE_RELEASE(m_pPS);
	SAFE_RELEASE(m_pInputLayout);
	SAFE_RELEASE(m_pTextureSRV);

	return true;
}

Object_DX::~Object_DX()
{

}