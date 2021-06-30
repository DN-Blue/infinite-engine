#ifndef DEPTHBUFFERSTATE
#define DEPTHBUFFERSTATE

#include "INGLib.h"

namespace Infinite {



	struct DepthBufferState {
		ID3D11DepthStencilState* pSate;
		D3D11_DEPTH_STENCIL_DESC desc;
	};

}

#endif