#include "SwapChain.h"
#include "ING.h"

using namespace Infinite;


SwapChain::SwapChain():
	pSwapChain(0)
{

}

SwapChain::~SwapChain() {

}


bool SwapChain::Init() {
	
	ID3D11Device* device = pGraphics->pd3dDevice;

	clientWidth = pGraphics->pING->pWindow->clientWidth;
	clientHeight = pGraphics->pING->pWindow->clientHeight;
	hwnd = pGraphics->pING->pWindow->hwnd;

	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.BufferCount = 1;
	desc.BufferDesc.Width = clientWidth;
	desc.BufferDesc.Height = clientHeight;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = hwnd;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Windowed = TRUE;

	HRESULT hr = pGraphics->pdxgiFactory->CreateSwapChain(device, &desc, &pSwapChain);


	if (FAILED(hr))
	{
		return false;
	}

	ID3D11Texture2D* buffer = NULL;
	hr = pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);

	if (FAILED(hr))
	{
		return false;
	}

	hr = device->CreateRenderTargetView(buffer, NULL, &pRenderTargetView);
	buffer->Release();

	if (FAILED(hr))
	{
		return false;
	}

	return true;
}



void SwapChain::Resize(UINT width, UINT height) {

}

void SwapChain::Present() {
	pSwapChain->Present(0,0);
}