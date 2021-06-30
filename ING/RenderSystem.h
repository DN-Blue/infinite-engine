#ifndef RENDERERSYSTEM_H
#define RENDERERSYSTEM_H

#include "INGLib.h"

namespace Infinite {

	class Renderer;

	class Graphics;

	class RenderSystem {
	public:
		RenderSystem();
		~RenderSystem();

	public:
		friend class Renderer;

		Graphics* pGraphics;

		Renderer* CreateRenderer();

	};

}


#endif