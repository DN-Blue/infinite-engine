#include "ING.h"

using namespace Infinite;


ING::ING() {
	pGraphics = new Graphics();
	pGraphics->pING = this;

	pWindow = new Window();
	pWindow->pING = this;

	pTime = new Time();
	pTime->pING = this;

	pResourcesManager = new ResourcesManager();
	pResourcesManager->pING = this;
}

ING::~ING() {

}



bool ING::baseInit() {


	if (!pWindow->Init()) {
		return false;
	}

	if (!pGraphics->Init()) {
		return false;
	}

	if (!pResourcesManager->Init()) {
		return false;
	}

	Init();

	return true;
}


bool ING::baseRun() {


	pGraphics->pDeviceContext->SetViewPortSize(pWindow->clientWidth, pWindow->clientHeight);
	Run();

	pTime->Start();

	while (pWindow->isRunning) {

		pWindow->Boardcast();
		float color[] = { 0,0,0,1 };
		pGraphics->pDeviceContext->ClearRenderTargetView(color);
		Update();
		pGraphics->pSwapChain->Present();

	}

	return true;
}


void ING::Init() {

}

void ING::Run() {

}

void ING::Update() {

}

void ING::Draw() {

}
