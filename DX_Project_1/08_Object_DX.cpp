#include "08_Object_DX.h"

Object_DX::Object_DX()
{

}

// 정점 버퍼 생성
HRESULT Object_DX::CreateVertexBuffer(ID3D11Device* pd3dDevice, PCT_VERTEX* pVertexList)
{
	HRESULT hr;

	D3D11_BUFFER_DESC sDesc;
	ZeroMemory(&sDesc, sizeof(D3D11_BUFFER_DESC));
	sDesc.Usage = D3D11_USAGE_DEFAULT;
	sDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	sDesc.ByteWidth = sizeof(PCT_VERTEX) * 4;

	D3D11_SUBRESOURCE_DATA sInitData;
	ZeroMemory(&sInitData, sizeof(D3D11_SUBRESOURCE_DATA));
	sInitData.pSysMem = pVertexList;

	if (FAILED(hr = pd3dDevice->CreateBuffer(&sDesc, &sInitData, &m_pVertexBuffer))) {
		return hr;
	}

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

//전부 생성하기
HRESULT Object_DX::Create(ID3D11Device* pd3dDevice, const TCHAR* pVsFile, const TCHAR* pPsFile, const TCHAR* pTexFile)
{
	HRESULT hr;

	hr = CreateVertexBuffer(pd3dDevice, m_pVertexList); if (hr) { return hr; }
	hr = CreateVSandInputLayout(pd3dDevice, pVsFile); if (hr) { return hr; }
	hr = CreatePS(pd3dDevice, pPsFile); if (hr) { return hr; }
	hr = LoadTexture(pd3dDevice, pTexFile); if (hr) { return hr; }

	return hr;
}


void Object_DX::transStoP()
{
	m_frtPRegion.left = (m_rtSRegion.left / (float)g_uClientWidth) * 2 - 1.0f;
	m_frtPRegion.top = -((m_rtSRegion.top / (float)g_uClientHeight) * 2 - 1.0f);
	m_frtPRegion.right = (m_rtSRegion.right / (float)g_uClientWidth) * 2 - 1.0f;
	m_frtPRegion.bottom = -((m_rtSRegion.bottom / (float)g_uClientHeight) * 2 - 1.0f);
}

void Object_DX::transPtoS()
{
	m_rtSRegion.left = (m_frtPRegion.left+1.0f) / 2 * (float)g_uClientWidth;
	m_rtSRegion.top = (m_frtPRegion.top - 1.0f) / -2 * (float)g_uClientHeight;
	m_rtSRegion.right = (m_frtPRegion.right + 1.0f) / 2 * (float)g_uClientWidth;
	m_rtSRegion.bottom = (m_frtPRegion.bottom - 1.0f) / -2 * (float)g_uClientHeight;
}

void Object_DX::UpdateCP()
{
	m_ptCenter.x = (m_rtSRegion.right - m_rtSRegion.left) / 2;
	m_ptCenter.y = (m_rtSRegion.bottom - m_rtSRegion.top) / 2;

	m_v3Center.x = 0.0f;
	m_v3Center.y = 0.0f;

	for (int iV = 0; iV < 4; iV++) {
		D3DXVECTOR3 vertex = m_pVertexList[iV].p;
		m_v3Center.x += vertex.x;
		m_v3Center.y += vertex.y;
	}

	m_v3Center.x /= 4.0f;
	m_v3Center.y /= 4.0f;

	m_v3Center.z = 0.0f;
}

//위치 지정하기
void Object_DX::SetPosition(UINT sl, UINT st, UINT sr, UINT sb)
{
	//화면 좌표계 저장
	m_rtSRegion.left = sl;
	m_rtSRegion.top = st;
	m_rtSRegion.right = sr;
	m_rtSRegion.bottom = sb;

	//투영 좌표계 저장
	transStoP();

	ZeroMemory(&m_pVertexList, sizeof(m_pVertexList[0])*4);
	m_pVertexList[0].p = D3DXVECTOR3(m_frtPRegion.left, m_frtPRegion.top, 0.0f);
	m_pVertexList[0].t = D3DXVECTOR2(0.0f, 0.0f);

	m_pVertexList[1].p = D3DXVECTOR3(m_frtPRegion.left, m_frtPRegion.bottom, 0.0f);
	m_pVertexList[1].t = D3DXVECTOR2(0.0f, 1.0f);

	m_pVertexList[2].p = D3DXVECTOR3(m_frtPRegion.right, m_frtPRegion.top, 0.0f);
	m_pVertexList[2].t = D3DXVECTOR2(1.0f, 0.0f);

	m_pVertexList[3].p = D3DXVECTOR3(m_frtPRegion.right, m_frtPRegion.bottom, 0.0f);
	m_pVertexList[3].t = D3DXVECTOR2(1.0f, 1.0f);


	//중점 저장
	UpdateCP();

}

void Object_DX::MoveX(float fDis)
{
	for (int iV = 0; iV < 4; iV++) {
		m_pVertexList[iV].p.x += fDis;
	}

	m_frtPRegion.left += fDis;
	m_frtPRegion.right += fDis;

	transPtoS();

	UpdateCP();
}

void Object_DX::MoveY(float fDis)
{
	for (int iV = 0; iV < 4; iV++) {
		m_pVertexList[iV].p.y += fDis;
	}

	m_frtPRegion.top += fDis;
	m_frtPRegion.bottom += fDis;

	transPtoS();

	UpdateCP();
}

void Object_DX::spin()
{
	static float fAngle = 0.0f;
	fAngle += m_timer.GetSPF();

	float S = sinf(fAngle);
	float C = cosf(fAngle);

	for (int iV = 0; iV < 4; iV++) {

		D3DXVECTOR3 vertex = m_pVertexList[iV].p;

		m_pVLtemp[iV].p.x -= m_v3Center.x;
		m_pVLtemp[iV].p.y -= m_v3Center.y;

		vertex.x = m_pVLtemp[iV].p.x * C  + m_pVLtemp[iV].p.y * S;
		vertex.y = m_pVLtemp[iV].p.x * -S + m_pVLtemp[iV].p.y * C;

		vertex.x += m_v3Center.x;
		vertex.y += m_v3Center.y;

		m_pVLtemp[iV].p = vertex;
	}
}

bool Object_DX::Frame(ID3D11DeviceContext* pContext)
{
	m_timer.Frame();

	if (I_Input.IsKeyDown(0xcb)) { //Left
		MoveX(m_timer.GetSPF() * -0.3);
	}

	if (I_Input.IsKeyDown(0xcd)) { //Right
		MoveX(m_timer.GetSPF() * 0.3);
	}

	if (I_Input.IsKeyDown(0xc8)) { //Up
		MoveY(m_timer.GetSPF() * 0.3);
	}

	if (I_Input.IsKeyDown(0xd0)) { //Down
		MoveY(m_timer.GetSPF() * -0.3);
	}

	for (int iV = 0; iV < 4; iV++) {
		m_pVLtemp[iV] = m_pVertexList[iV];
	}

	if (I_Input.IsKeyDown(DIK_1)) { //Down
		spin();
	}
	pContext->UpdateSubresource(m_pVertexBuffer, 0, NULL, m_pVLtemp, 0, 0);

	return true;
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

	pContext->Draw(4, 0);

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