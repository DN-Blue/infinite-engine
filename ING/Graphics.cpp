#include "Graphics.h"
#include "Shader.h"
#include "ING.h"
#include "Material.h"

using namespace Infinite;


Graphics::Graphics() :
	pING(0),
	pd3dDevice(0),
	pDeviceContext(0),
	pdxgiDevice(0),
	pdxgiAdapter(0),
	pdxgiFactory(0)
{
	pRenderSystem = new RenderSystem();
	pRenderSystem->pGraphics = this;
	pSwapChain = new SwapChain();
	pSwapChain->pGraphics = this;
}

Graphics::~Graphics() {

}




bool Graphics::InitDirectX() {
	D3D_DRIVER_TYPE driver_types[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};
	UINT num_driver_types = ARRAYSIZE(driver_types);

	D3D_FEATURE_LEVEL feature_levels[] =
	{
		D3D_FEATURE_LEVEL_11_0
	};
	UINT num_feature_levels = ARRAYSIZE(feature_levels);

	HRESULT res = 0;
	ID3D11DeviceContext* m_imm_context;

	for (UINT driver_type_index = 0; driver_type_index < num_driver_types;)
	{
		res = D3D11CreateDevice(NULL, driver_types[driver_type_index], NULL, NULL, feature_levels,
			num_feature_levels, D3D11_SDK_VERSION, &pd3dDevice, &featureLevel, &m_imm_context);
		if (SUCCEEDED(res))
			break;
		++driver_type_index;
	}
	if (FAILED(res))
	{
		return false;
	}

	pDeviceContext = new DeviceContext(m_imm_context);
	pDeviceContext->pGraphics = this;

	pd3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&pdxgiDevice);
	pdxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&pdxgiAdapter);
	pdxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&pdxgiFactory);


	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = pING->pWindow->clientWidth;
	descDepth.Height = pING->pWindow->clientHeight;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;

	pd3dDevice->CreateTexture2D(&descDepth, 0, &mDepthStencilBuffer);


	HRESULT hrr = pd3dDevice->CreateDepthStencilView(mDepthStencilBuffer,0,&mDepthStencilView);



	return true;
}





bool Graphics::Init() {

	if(!InitDirectX()){
		return false;
	}

	if (!pSwapChain->Init()) {
		return false;
	}


	pDeviceContext->pImmContext->OMSetRenderTargets(1, &pSwapChain->pRenderTargetView, mDepthStencilView);


	return true;
}


void Graphics::SetScreenSize(UINT width,UINT height) {
	pSwapChain->Resize(width, height);


}


Shader* Graphics::CreateShader(LPCWSTR srcPath) {
	Shader* shader=0;

	ID3DBlob* m_vsblob = nullptr;
	ID3DBlob* m_psblob = nullptr;
	ID3DBlob* errblob = nullptr;

	ID3D11VertexShader* m_vs = nullptr;
	ID3D11PixelShader* m_ps = nullptr;

	HRESULT hr = D3DCompileFromFile(srcPath, nullptr, nullptr, "vsmain", "vs_5_0", NULL, NULL, &m_vsblob, &errblob);
	HRESULT hr2 = D3DCompileFromFile(srcPath, nullptr, nullptr, "psmain", "ps_5_0", NULL, NULL, &m_psblob, &errblob);

	if (errblob != 0) {
		MessageBoxA(0, (char*)errblob->GetBufferPointer(), 0, 0);
	}
	
	
	pd3dDevice->CreateVertexShader(m_vsblob->GetBufferPointer(), m_vsblob->GetBufferSize(), nullptr, &m_vs);
	pd3dDevice->CreatePixelShader(m_psblob->GetBufferPointer(), m_psblob->GetBufferSize(), nullptr, &m_ps);

	shader = new Shader();

	shader->pVS = m_vs;
	shader->pPS = m_ps;

	shader->pvsblob = m_vsblob;
	shader->ppsblob = m_psblob;

	return shader;
}




void Graphics::RegisterShader(Shader* pShader) {
	CreateVertexInputLayout(pShader);
}


