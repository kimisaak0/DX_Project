#include "03_coreC_DX.h"

#pragma region temp

HRESULT coreC_DX::SetRasterizerState()
{
	HRESULT hr;
	D3D11_RASTERIZER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));
	desc.FillMode = D3D11_FILL_SOLID;
	desc.CullMode = D3D11_CULL_NONE;
	desc.DepthClipEnable = TRUE;

	hr = m_pD3dDevice->CreateRasterizerState(&desc, &m_pRSSolid);
	return hr;
}

bool coreC_DX::Init()
{
	SetRasterizerState();

	m_Actor.SetPosition(0, 0, g_rtClient.right * 0.1f, g_rtClient.bottom * 0.2f);
	m_Actor.Create(m_pD3dDevice, L"VertexShader.vsh", L"PixelShader.psh", L"skybox_top.JPG");

	m_Image.SetPosition(10,10,110,110);
	m_Image.Create(m_pD3dDevice, L"VertexShader.vsh", L"PixelShader.psh", L"Koala.jpg");

	return true;
}

bool coreC_DX::Frame()
{
	//m_Actor.Frame(m_pImmediateContext);
	m_Image.Frame(m_pImmediateContext);

	return true;
}

bool coreC_DX::Render()
{
	assert(m_pImmediateContext);
	m_pImmediateContext->OMSetBlendState(0, 0, 0xffffffff);

	m_pImmediateContext->RSSetState(m_pRSSolid);

	m_Actor.Render(m_pImmediateContext);

	m_Image.Render(m_pImmediateContext);

	return true;
}

bool coreC_DX::Release()
{
	m_Actor.Release();

	return true;
}

#pragma endregion


coreC_DX::coreC_DX(LPCTSTR LWndName) : wndC_DX(LWndName)
{
	m_swTimerRender = false;
	m_swKeyRender = false;
}

bool coreC_DX::gameInit()
{
	//디바이스 생성 작업 실행.
	InitDevice();
	m_GameTimer.Init();

	//SwapChain의 백버퍼 정보로 DXWrite객체 생성 
	IDXGISurface1* pBackBuffer = nullptr;
	HRESULT hr = getSwapChain()->GetBuffer(0, __uuidof(IDXGISurface), (void**)&pBackBuffer);
	m_Font.Init();
	m_Font.Set(pBackBuffer);

	if (pBackBuffer) {
		pBackBuffer->Release();
	}

	//DXInput Device 생성
	if (!I_Input.InitDirectInput(true, true)) {
		return false;
	}
	
	//DXInput 초기화
	if (!I_Input.Init()) {
		return false;
	}


	g_pWindow->CenterWindow(g_hWnd); //윈도우를 화면 중앙으로 이동시킨다.

	 //생성된 크기를 전역 변수에 대입한다.
	GetWindowRect(g_hWnd, &g_rtWindow);
	GetClientRect(g_hWnd, &g_rtClient);

	Init();

	
	return true;
}

bool coreC_DX::gameRun()
{
	gameFrame();
	gamePreRender();
	gameRender();
	gamePostRender();
	return true;
}

bool coreC_DX::gameFrame()
{
	m_GameTimer.Frame();
	I_Input.Frame();
	
	if (I_Input.IsKeyDownOnce(0x0d)) {
		m_swTimerRender = !m_swTimerRender;
		
	}

	if (I_Input.IsKeyDownOnce(DIK_0)) {
		m_swKeyRender = !m_swKeyRender;
	}

	Frame();

	return true;
}

bool coreC_DX::gamePreRender()
{
	//DXGI_SWAP_CHAIN_DESC CurrentSD;
//	m_pSwapChain->GetDesc(&CurrentSD);
	//GetClientRect(g_hWnd, &g_rtClient);

	m_Font.DrawTextBegin();
	return true;
}

bool coreC_DX::gameRender()
{
	//ID3D11RenderTargetView 객체에 컬러를 채운다. (BackBuffer를 지운다.)
	float r = 0.21f;
	float g = 0.32f;
	float b = 0.45f;

	float ClearColor[4] = { r, g, b, 0.0f }; //r,g,b,a
	m_pImmediateContext->ClearRenderTargetView(m_pRenderTagetView, ClearColor);

	TCHAR pBuffer[256];
	memset(pBuffer, 0, sizeof(TCHAR) * 256);	

	m_Font.SetTextPos();
	m_Font.SetlayoutRt(0, 0, (FLOAT)g_uClientWidth, (FLOAT)g_uClientHeight);

	if (m_swTimerRender) {
		m_Font.SetAlignment(DWRITE_TEXT_ALIGNMENT_LEADING, DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
		m_Font.SetTextColor(ColorF(1, 1, 1, 1));

		_stprintf_s(pBuffer, _T("FPS:%d, SPF:%10.5f, GameTime:%10.2f"),
			m_GameTimer.GetFPS(), m_GameTimer.GetSPF(), m_GameTimer.GetGameTime());
		m_Font.DrawText(pBuffer);
	}

	if (m_swKeyRender) {
		m_Font.SetAlignment(DWRITE_TEXT_ALIGNMENT_LEADING, DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
		//m_Font.SetTextPos(Matrix3x2F::Rotation(g_GameTimer*100, Point2F(400, 300)));
		m_Font.SetTextColor(ColorF(1, 0.3f, 0, 1));


		int iCount = 0;

		static LONG MousePosX = I_Input.m_MouseCurState.lX;
		static LONG MousePosY = I_Input.m_MouseCurState.lY;
		static LONG MousePosZ = I_Input.m_MouseCurState.lZ;

		MousePosX += I_Input.m_MouseCurState.lX;
		MousePosY += I_Input.m_MouseCurState.lY;
		MousePosZ += I_Input.m_MouseCurState.lZ;

		_stprintf_s(pBuffer, _T("Mouse X:%ld, Y:%ld, Z:%ld"), MousePosX, MousePosY, MousePosZ);

		UINT iStartX = 0;
		UINT iStartY = 30 + (20 * iCount);
		m_Font.SetlayoutRt((FLOAT)iStartX, (FLOAT)iStartY, (FLOAT)g_uClientWidth, (FLOAT)g_uClientHeight);
		m_Font.DrawText(pBuffer);
		iCount++;

		for (int iKey = 0; iKey < KeyStateCount; iKey++) {
			if (I_Input.m_KeyCurState[iKey] & 0x80) {
				_stprintf_s(pBuffer, _T("Key State : 0x%02x : %d"), iKey, I_Input.m_KeyCurState[iKey]);
				UINT iStartX = 0;
				UINT iStartY = 30 + (20 * iCount);
				m_Font.SetlayoutRt((FLOAT)iStartX, (FLOAT)iStartY, (FLOAT)g_uClientWidth, (FLOAT)g_uClientHeight);
				m_Font.DrawText(pBuffer);

				iCount++;
			}
		}

		for (int iKey = 0; iKey < 4; iKey++) {
			if (I_Input.m_MouseCurState.rgbButtons[iKey] & 0x80) {
				_stprintf_s(pBuffer, _T("Mouse Button State : %02d"), iKey);
				UINT iStartX = 0;
				UINT iStartY = 30 + (20 * iCount);
				m_Font.SetlayoutRt((FLOAT)iStartX, (FLOAT)iStartY, (FLOAT)g_uClientWidth, (FLOAT)g_uClientHeight);
				m_Font.DrawText(pBuffer);

				iCount++;
			}
		}
	}

	Render();

	return true;
}

bool coreC_DX::gamePostRender()
{
	//IDXGISwapChain 객체를 사용하여 시연(출력)한다.
	//모든 렌더링 작업들은 present앞에서 이뤄져야 한다.
	m_Font.DrawTextEnd();
	m_pSwapChain->Present(0, 0);
	return true;
}

bool coreC_DX::gameRelease()
{
	Release();

	if (!I_Input.Release()) { return false; }
	if (!m_Font.Release()) { return false; }
	if (!m_GameTimer.Release()) { return false; }
	if (!CreanupDevice()) { return false; }
	return true;
}

bool coreC_DX::ResetRT()
{
	IDXGISurface1* pBackBuffer = nullptr;
	HRESULT hr = getSwapChain()->GetBuffer(0, __uuidof(IDXGISurface), (void**)&pBackBuffer);
	m_Font.Set(pBackBuffer);

	if (pBackBuffer) {
		pBackBuffer->Release();
	}

	return true;
}


coreC_DX::~coreC_DX()
{
}
