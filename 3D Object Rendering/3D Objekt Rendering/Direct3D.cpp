#include "Direct3D.h"

Direct3D::Direct3D(HWND windowHandle, int width, int height, bool isFullscreen)
{
	// Create Device and Swap Chain.
	
	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
	swapChainDesc.OutputWindow = windowHandle;
	swapChainDesc.Windowed = !isFullscreen;
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.SampleDesc.Count = 1;						
	
	D3D_FEATURE_LEVEL supportedFeatureLevels[] = {
		D3D_FEATURE_LEVEL_12_1,
		D3D_FEATURE_LEVEL_12_0,
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	
	D3D_FEATURE_LEVEL featureLevel = {};
	
	D3D11CreateDeviceAndSwapChain(
		nullptr,													
		D3D_DRIVER_TYPE_HARDWARE, nullptr,							
		0,															
		supportedFeatureLevels, std::size(supportedFeatureLevels),	
		D3D11_SDK_VERSION,
		&swapChainDesc, &swapChain, &Device, &featureLevel, &Context
	);
	
	// Create Render Target View.
	
	ID3D11Texture2D* backBufferTexture = nullptr;
	
	swapChain->GetBuffer(0, IID_PPV_ARGS(&backBufferTexture));
	if (backBufferTexture != nullptr) Device->CreateRenderTargetView(backBufferTexture, nullptr, &renderTargetView);
	
	backBufferTexture->Release();
	
	// Create Depth Stencil View.
	
	ID3D11Texture2D* depthStencilTexture = nullptr;
	
	D3D11_TEXTURE2D_DESC depthStencilTextureDesc = {};
	depthStencilTextureDesc.Width = width;
	depthStencilTextureDesc.Height = height;
	depthStencilTextureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilTextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilTextureDesc.ArraySize = 1;							
	depthStencilTextureDesc.SampleDesc.Count = 1;					
	
	Device->CreateTexture2D(&depthStencilTextureDesc, nullptr, &depthStencilTexture);
	if (depthStencilTexture != nullptr) Device->CreateDepthStencilView(depthStencilTexture, nullptr, &depthStencilView);
	
	depthStencilTexture->Release();
	
	// Create Rasterizer State
	
	D3D11_RASTERIZER_DESC rasterizerDesc = {};
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_BACK;
	
	Device->CreateRasterizerState(&rasterizerDesc, &rasterizerState);
	
	// Set View Port
	
	D3D11_VIEWPORT viewPort = {};	
	viewPort.TopLeftX = 0;
	viewPort.TopLeftY = 0;
	viewPort.Width = width;
	viewPort.Height = height;
	viewPort.MinDepth = 0.0f;
	viewPort.MaxDepth = 1.0f;
	
	// Set up render pipeline
	
	Context->OMSetRenderTargets(1, &renderTargetView, depthStencilView);
	Context->RSSetViewports(1, &viewPort);
	Context->RSSetState(rasterizerState);
}

void Direct3D::StartRender()
{
	float backgroundColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	Context->ClearRenderTargetView(renderTargetView, backgroundColor);

	Context->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0xffffffff);
}

void Direct3D::EndRender(bool vSyncIsOn)
{
	swapChain->Present(vSyncIsOn, 0);
}
