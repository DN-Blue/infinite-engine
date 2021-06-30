#ifndef RASTERIZERSTATE_H
#define RASTERIZERSTATE_H

#include "INGLib.h"

namespace Infinite {

	struct RasterizerState {
		ID3D11RasterizerState* state;
		D3D11_RASTERIZER_DESC desc;



	};
}


#endif