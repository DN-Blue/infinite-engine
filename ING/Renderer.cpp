#include "Renderer.h"
#include "Shader.h"
#include "Mesh.h"
#include "Material.h"
#include "RasterizerState.h"

using namespace Infinite;


Renderer::Renderer():
	pSolidRSState(nullptr)
{

}

Renderer::~Renderer() {

}


void Renderer::RegisterMesh(Mesh* pMesh) {

	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(Vertex) * pMesh->pData->vertices.size();
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = &pMesh->pData->vertices[0];


	pSystem->pGraphics->pd3dDevice->CreateBuffer(&vbd, &vinitData, &pMesh->buffers.pVertexBuffer);



	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(UINT) * pMesh->pData->indices.size();
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = &pMesh->pData->indices[0];

	pSystem->pGraphics->pd3dDevice->CreateBuffer(&ibd, &iinitData, &pMesh->buffers.pIndexBuffer);
}

void Renderer::DrawMesh(Mesh* pMesh2) {
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	pSystem->pGraphics->pDeviceContext->pImmContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	pSystem->pGraphics->pDeviceContext->pImmContext->IASetVertexBuffers(0, 1, &pMesh2->buffers.pVertexBuffer, &stride, &offset);
	pSystem->pGraphics->pDeviceContext->pImmContext->IASetIndexBuffer(pMesh2->buffers.pIndexBuffer, DXGI_FORMAT_R32_UINT,0);

	pSystem->pGraphics->pDeviceContext->pImmContext->DrawIndexed(pMesh2->pData->indices.size(),0,0);

}


void Renderer::Draw() {
	DrawMesh(pMesh);
}

void Renderer::RegisterMaterial(Material* pMat) {

	UINT cbInputsCount = pMat->cbInputs.size();

	pMat->cbs.resize(cbInputsCount);

	pMat->isRegisted = true;
	
	for (UINT i = 0; i < cbInputsCount; i++) {




		D3D11_BUFFER_DESC cbDesc;
		cbDesc.ByteWidth = pMat->cbInputs[i].size;
		cbDesc.Usage = D3D11_USAGE_DEFAULT;
		cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbDesc.CPUAccessFlags = 0;
		cbDesc.MiscFlags = 0;
		cbDesc.StructureByteStride = 0;

		
		D3D11_SUBRESOURCE_DATA InitData;
		InitData.pSysMem = pMat->cbInputs[i].pointer;
		InitData.SysMemPitch = 0;
		InitData.SysMemSlicePitch = 0;

		HRESULT hr = pSystem->pGraphics->pd3dDevice->CreateBuffer(&cbDesc, &InitData,&pMat->cbs[i]);

	}
}

void Renderer::SetShader(Shader* pShader) {
	this->pSystem->pGraphics->pDeviceContext->SetShader(pShader);

}


void Renderer::UpdateMaterial(Material* pMat) {
	UINT cbInputsCount = pMat->cbInputs.size();




	for (UINT i = 0; i < cbInputsCount; i++) {
		pSystem->pGraphics->pDeviceContext->pImmContext->UpdateSubresource(pMat->cbs[i],0,nullptr,pMat->cbInputs[i].pointer,0,0);
	}
}


void Renderer::SetMaterial(Material* pMat) {

	//SetShader(pMat->pShader);

	this->pMaterial = pMat;

	UINT cbInputsCount = pMat->cbInputs.size();


	for (UINT i = 0; i < cbInputsCount; i++) {
		pSystem->pGraphics->pDeviceContext->pImmContext->VSSetConstantBuffers(0,1,&pMat->cbs[i]);
		pSystem->pGraphics->pDeviceContext->pImmContext->PSSetConstantBuffers(0, 1, &pMat->cbs[i]);
	}
}


void Renderer::UseSolidRSState() {
	if (pSolidRSState == nullptr) {


		pSolidRSState = new RasterizerState();

		pSolidRSState->desc.FillMode = D3D11_FILL_SOLID;
		pSolidRSState->desc.CullMode = D3D11_CULL_BACK;
		pSolidRSState->desc.FrontCounterClockwise = true;
		pSolidRSState->desc.DepthBias = false;
		pSolidRSState->desc.DepthBiasClamp = 0;
		pSolidRSState->desc.SlopeScaledDepthBias = 0;
		pSolidRSState->desc.DepthClipEnable = true;
		pSolidRSState->desc.ScissorEnable = false;
		pSolidRSState->desc.MultisampleEnable = false;
		pSolidRSState->desc.AntialiasedLineEnable = false;

		pSystem->pGraphics->pDeviceContext->RegisterRSState(pSolidRSState);
	}
	pSystem->pGraphics->pDeviceContext->SetRSState(pSolidRSState);
}

void Renderer::UseInverseSolidRSState() {
	if (pInverseSolidRSState == nullptr) {


		pInverseSolidRSState = new RasterizerState();

		pInverseSolidRSState->desc.FillMode = D3D11_FILL_SOLID;
		pInverseSolidRSState->desc.CullMode = D3D11_CULL_FRONT;
		pInverseSolidRSState->desc.FrontCounterClockwise = true;
		pInverseSolidRSState->desc.DepthBias = false;
		pInverseSolidRSState->desc.DepthBiasClamp = 0;
		pInverseSolidRSState->desc.SlopeScaledDepthBias = 0;
		pInverseSolidRSState->desc.DepthClipEnable = true;
		pInverseSolidRSState->desc.ScissorEnable = false;
		pInverseSolidRSState->desc.MultisampleEnable = false;
		pInverseSolidRSState->desc.AntialiasedLineEnable = false;

		pSystem->pGraphics->pDeviceContext->RegisterRSState(pInverseSolidRSState);
	}
	pSystem->pGraphics->pDeviceContext->SetRSState(pInverseSolidRSState);
}


void Renderer::UseNoCullSolidRSState() {
	if (pNoCullSolidRSState == nullptr) {


		pNoCullSolidRSState = new RasterizerState();

		pNoCullSolidRSState->desc.FillMode = D3D11_FILL_SOLID;
		pNoCullSolidRSState->desc.CullMode = D3D11_CULL_NONE;
		pNoCullSolidRSState->desc.FrontCounterClockwise = true;
		pNoCullSolidRSState->desc.DepthBias = false;
		pNoCullSolidRSState->desc.DepthBiasClamp = 0;
		pNoCullSolidRSState->desc.SlopeScaledDepthBias = 0;
		pNoCullSolidRSState->desc.DepthClipEnable = true;
		pNoCullSolidRSState->desc.ScissorEnable = false;
		pNoCullSolidRSState->desc.MultisampleEnable = false;
		pNoCullSolidRSState->desc.AntialiasedLineEnable = false;

		pSystem->pGraphics->pDeviceContext->RegisterRSState(pNoCullSolidRSState);
	}
	pSystem->pGraphics->pDeviceContext->SetRSState(pNoCullSolidRSState);
}

void Renderer::UseWireframeRSState() {
	if (pWireframeRSState == nullptr) {


		pWireframeRSState = new RasterizerState();

		pWireframeRSState->desc.FillMode = D3D11_FILL_WIREFRAME;
		pWireframeRSState->desc.CullMode = D3D11_CULL_NONE;
		pWireframeRSState->desc.FrontCounterClockwise = true;
		pWireframeRSState->desc.DepthBias = false;
		pWireframeRSState->desc.DepthBiasClamp = 0;
		pWireframeRSState->desc.SlopeScaledDepthBias = 0;
		pWireframeRSState->desc.DepthClipEnable = true;
		pWireframeRSState->desc.ScissorEnable = false;
		pWireframeRSState->desc.MultisampleEnable = false;
		pWireframeRSState->desc.AntialiasedLineEnable = false;

		pSystem->pGraphics->pDeviceContext->RegisterRSState(pWireframeRSState);
	}
	pSystem->pGraphics->pDeviceContext->SetRSState(pWireframeRSState);
}



void Renderer::EnableDepth() {
	if (pEDepthBufferSate == nullptr) {
		pEDepthBufferSate = new DepthBufferState();


		pEDepthBufferSate->desc.DepthEnable = true;
		pEDepthBufferSate->desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		pEDepthBufferSate->desc.DepthFunc = D3D11_COMPARISON_LESS;


		pSystem->pGraphics->pDeviceContext->RegisterDBState(pEDepthBufferSate);
	}
	pSystem->pGraphics->pDeviceContext->SetDBState(pEDepthBufferSate);
}


void Renderer::DisableDepth() {
	if (pDDepthBufferSate == nullptr) {
		pDDepthBufferSate = new DepthBufferState();


		pDDepthBufferSate->desc.DepthEnable = false;
		pDDepthBufferSate->desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		pDDepthBufferSate->desc.DepthFunc = D3D11_COMPARISON_LESS;


		pSystem->pGraphics->pDeviceContext->RegisterDBState(pDDepthBufferSate);
	}
	pSystem->pGraphics->pDeviceContext->SetDBState(pDDepthBufferSate);
}





Material* Renderer::CreateTransformationMaterial() {
	Material* pMat = new Material();

	DefaultResources::TransformationMaterialInput input;

	pMat->cbInputs.resize(1);

	pMat->cbInputs[0].pointer = &input;
	pMat->cbInputs[0].size = sizeof(DefaultResources::TransformationMaterialInput);

	RegisterMaterial(pMat);

	return pMat;
}



void Renderer::UpdateTransformationMaterial(Material* pMat) {

}