#include "ING/ING.h"
#include <iostream>
#include "ING/Material.h"

using namespace Infinite;
using namespace DirectX;


class INGApp:public ING {
public:
	INGApp();
	~INGApp();

public:
	virtual void Run() override;
	virtual void Update() override;

};


INGApp::INGApp() {

}

INGApp::~INGApp() {

}




Shader* pShader;
Renderer* pRenderer;
Mesh* pMesh;
Material* pMat;

void INGApp::Run() {



	//Create Renderer
	pRenderer = pGraphics->pRenderSystem->CreateRenderer();



	//Create Mesh

	MeshData* pMeshDataDemo = pResourcesManager->IModelImportMeshData("G:/Downloads/d3d11CodeSet1 (1)/Chapter 6 Drawing in Direct3D/LightingDemo2/Models/skull.txt");

	pMesh = new Mesh();
	pMesh->pData = pMeshDataDemo;

	/*
	pMesh->pData->vertices = std::vector<Vertex>(3);

	pMesh->pData->vertices[0] = {
		XMFLOAT3(-0.5f,-0.5f,0),
		XMFLOAT3(0,0,0),
		XMFLOAT2(0,0)
	};

	pMesh->pData->vertices[1] = {
		XMFLOAT3(0,0.5f,0),
		XMFLOAT3(0,0,0),
		XMFLOAT2(0,0)
	};
	pMesh->pData->vertices[1] = {
		XMFLOAT3(0.5f,-0.5f,0),
		XMFLOAT3(0,0,0),
		XMFLOAT2(0,0)
	};


	pMesh->pData->indices = std::vector<UINT>(3);

	pMesh->pData->indices[0] = 0;
	pMesh->pData->indices[1] = 1;
	pMesh->pData->indices[2] = 2;
	*/
	
	pRenderer->RegisterMesh(pMesh);
	pRenderer->pMesh = pMesh;



	//Create Shader
	pShader = pGraphics->CreateShader(L"demo.fx");
	pGraphics->RegisterShader(pShader);
	pRenderer->SetShader(pShader);

	//Create Material
	pMat = new Material();
	pMat->pShader = pShader;

	struct MaterialInput {
		XMMATRIX mWorld;
		XMMATRIX mView;
		XMMATRIX mProjection;
		XMVECTOR viewPos;
		XMVECTOR time;
	};

	MaterialInput input1;


	XMVECTOR pos = XMVectorSet(20, 10, 0, 1.0f);

	XMVECTOR target = XMVectorZero();
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	XMMATRIX V = XMMatrixTranspose(XMMatrixLookAtLH(pos, target, up));
	float PI= 3.141592653589793f;

	XMMATRIX P = XMMatrixTranspose(XMMatrixPerspectiveFovLH(0.25f * PI, (FLOAT)(pWindow->clientWidth)/ (FLOAT)(pWindow->clientHeight), 1.0f, 1000.0f));

	XMMATRIX I = XMMatrixTranspose(XMMatrixIdentity());

	XMMATRIX worldViewProj = I*V*P;

	input1.mWorld = I;
	input1.mView = V;
	input1.mProjection = P;
	input1.viewPos = pos;
	input1.time = XMVectorSet(0.5f, 0, 0, 0);

	pMat->cbInputs.resize(1);

	pMat->cbInputs[0].pointer = &input1;
	pMat->cbInputs[0].size = sizeof(MaterialInput);

	pRenderer->RegisterMaterial(pMat);

	pRenderer->UpdateMaterial(pMat);

	pRenderer->SetMaterial(pMat);

}

void INGApp::Update() {
	//Set RSState
	pRenderer->UseInverseSolidRSState();

	//enable depth
	pRenderer->EnableDepth();
	
	struct MaterialInput {
		XMMATRIX mWorld;
		XMMATRIX mView;
		XMMATRIX mProjection;
		XMVECTOR viewPos;
		XMVECTOR time;
	};

	MaterialInput input1;


	XMVECTOR pos = XMVectorSet(20, 10, 0, 1.0f);

	XMVECTOR target = XMVectorZero();
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	XMMATRIX V = XMMatrixTranspose(XMMatrixLookAtLH(pos, target, up));
	float PI = 3.141592653589793f;

	XMMATRIX P = XMMatrixTranspose(XMMatrixPerspectiveFovLH(0.25f * PI, (FLOAT)(pWindow->clientWidth) / (FLOAT)(pWindow->clientHeight), 1.0f, 1000.0f));

	XMMATRIX I = XMMatrixTranspose(XMMatrixIdentity());

	XMMATRIX worldViewProj = I * V * P;

	input1.mWorld = I;
	input1.mView = V;
	input1.mProjection = P;
	input1.viewPos = pos;

	input1.time = XMVectorSet(1,0,0,0);

	pMat->cbInputs[0].pointer = &input1;
	pMat->cbInputs[0].size = sizeof(MaterialInput);

	pRenderer->UpdateMaterial(pMat);


	//Draw
	pRenderer->Draw();
}



int main() {

	INGApp* pApp = new INGApp();

	pApp->pWindow->clientWidth = 800;
	pApp->pWindow->clientHeight = 600;
	pApp->pWindow->name = L"ING app";

	if (!pApp->baseInit()) {
		return 0;
	}

	if (!pApp->baseRun()) {
		return 0;
	}

	

	return 0;
}