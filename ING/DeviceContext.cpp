#include "DeviceContext.h"
#include "Shader.h"
#include "RasterizerState.h"

using namespace Infinite;


DeviceContext::DeviceContext(ID3D11DeviceContext* pImmContext) 
{
	this->pImmContext = pImmContext;
}


DeviceContext::~DeviceContext() {

}


void DeviceContext::ClearRenderTargetView(float color[]){
	pImmContext->ClearRenderTargetView(pGraphics->pSwapChain->pRenderTargetView,color);
	pImmContext->ClearDepthStencilView(pGraphics->mDepthStencilView,D3D11_CLEAR_DEPTH| D3D11_CLEAR_STENCIL,1.0f,0);
	//pImmContext->OMSetRenderTargets(1, &pGraphics->pSwapChain->pRenderTargetView, pGraphics->mDepthStencilView);
}


void DeviceContext::DrawIndicesList(UINT vertex_count, UINT start_vertex_index)
{
	pImmContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	pImmContext->Draw(vertex_count, start_vertex_index);
}



void DeviceContext::SetViewPortSize(UINT width, UINT height)
{
	D3D11_VIEWPORT screenViewport = {};

	screenViewport.TopLeftX = 0;
	screenViewport.TopLeftY = 0;
	screenViewport.Width = (FLOAT)width;
	screenViewport.Height = (FLOAT)height;
	screenViewport.MinDepth = 0.0f;
	screenViewport.MaxDepth = 1.0f;
	pImmContext->RSSetViewports(1, &screenViewport);
}



void DeviceContext::SetRSState(RasterizerState* pRSState) {
	pImmContext->RSSetState(pRSState->state);
	
	
}

void DeviceContext::RegisterRSState(RasterizerState* pRSState) {
	pGraphics->pd3dDevice->CreateRasterizerState(&pRSState->desc, &pRSState->state);
	

}

void DeviceContext::SetDBState(DepthBufferState* pDBState) {
	pImmContext->OMSetDepthStencilState(pDBState->pSate, 1);

}

void DeviceContext::RegisterDBState(DepthBufferState* pDBState) {

	pGraphics->pd3dDevice->CreateDepthStencilState(&pDBState->desc, &pDBState->pSate);

}

void DeviceContext::SetShader(Shader* pShader) {
	ID3D11VertexShader* m_vs = pShader->pVS;
	ID3D11PixelShader* m_ps = pShader->pPS;
	pImmContext->VSSetShader(m_vs, nullptr, 0);
	pImmContext->PSSetShader(m_ps, nullptr, 0);
	pImmContext->IASetInputLayout(pShader->pVertexInputLayout);
}