#include "RenderSystem.h"

using namespace Infinite;

RenderSystem::RenderSystem() {

}

RenderSystem::~RenderSystem() {

}

Renderer* RenderSystem::CreateRenderer() {
	Renderer* result=new Renderer();
	result->pSystem = this;
	return result;
}