#include "Graphics.h"
#include "INGLib.h"
#include "Shader.h"

using namespace Infinite;

bool Graphics::CreateVertexInputLayout(Shader* pShader) {

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL",    0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	pd3dDevice->CreateInputLayout(layout,3,pShader->pvsblob->GetBufferPointer(),pShader->pvsblob->GetBufferSize(),&pShader->pVertexInputLayout);

	return true;
}